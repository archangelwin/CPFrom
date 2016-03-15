#include "StdAfx.h"
#include "DataBasePool.h"

CDataBasePool::CDataBasePool()
{
	m_nConnections = 0;
	::InitializeCriticalSection(&m_DataBasePoolLock);
	m_pIDataBaseEngineSink = NULL;
}

CDataBasePool::~CDataBasePool()
{
	::DeleteCriticalSection(&m_DataBasePoolLock);
}

bool CDataBasePool::InitiDataBasePool(IDataBaseEngineSink * pIUnknownEx[], WORD wSinkCount)
{
	m_pIDataBaseEngineSink = new DATABASEPOOL[wSinkCount];
	m_nConnections = wSinkCount;
	for (int i=0; i<wSinkCount; i++)
	{
		m_pIDataBaseEngineSink[i].dwIndex = i;
		m_pIDataBaseEngineSink[i].pDataBaseEngineSink = pIUnknownEx[i];
		m_pIDataBaseEngineSink[i].dwDataBaseStatus = DATABASE_IS_WAITING;
	}
	return true;
}
bool CDataBasePool::DataBaseEngineStart(IUnknownEx * pIUnknownEx)
{
	for (int i=0; i<m_nConnections; i++)
	{
		if(!m_pIDataBaseEngineSink[i].pDataBaseEngineSink->OnDataBaseEngineStart(pIUnknownEx))
		{
			CTraceService::TraceString(TEXT("数据库引擎外挂服务启动失败"), TraceLevel_Exception);
			return false;
		}	
	}
	return true;
}
bool CDataBasePool::DataBaseEngineStop(IUnknownEx * pIUnknownEx)
{
	for (int i=0; i<m_nConnections; i++)
	{
		if (m_pIDataBaseEngineSink == NULL)
			return false;

		if(!m_pIDataBaseEngineSink[i].pDataBaseEngineSink->OnDataBaseEngineConclude(pIUnknownEx))
		{
			CTraceService::TraceString(TEXT("数据库引擎外挂服务关闭失败"), TraceLevel_Exception);
			return false;
		}	
	}
	CloseDataBasePool();
	return true;
}
bool CDataBasePool::CloseDataBasePool()
{
	if (m_pIDataBaseEngineSink != NULL)
	{
		delete [] m_pIDataBaseEngineSink;
		m_pIDataBaseEngineSink = NULL;
	}
	return true;
}

bool CDataBasePool::AllocDataBaseConnections(DATABASEPOOL *pIDataBaseEnginePool)
{
	bool bReturn = false;
	::EnterCriticalSection(&m_DataBasePoolLock);
	for (int i=0; i<m_nConnections; i++)
	{
		if (m_pIDataBaseEngineSink[i].dwDataBaseStatus == DATABASE_IS_WAITING )
		{
			m_pIDataBaseEngineSink[i].dwDataBaseStatus = DATABASE_IS_RUNNING;
			*pIDataBaseEnginePool = m_pIDataBaseEngineSink[i];
			bReturn = true;
			break;
		}
	}
	::LeaveCriticalSection(&m_DataBasePoolLock);
	return bReturn;
}

bool CDataBasePool::RelexDataBaseConnections(DATABASEPOOL *pIDataBaseEnginePool)
{
	ASSERT(pIDataBaseEnginePool->dwIndex>=0 && pIDataBaseEnginePool->dwIndex<=m_nConnections);
	::EnterCriticalSection(&m_DataBasePoolLock);
	m_pIDataBaseEngineSink[pIDataBaseEnginePool->dwIndex].dwDataBaseStatus = DATABASE_IS_WAITING;
	::LeaveCriticalSection(&m_DataBasePoolLock);
	return true;
}