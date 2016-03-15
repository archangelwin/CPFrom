#include "KernelEngineHead.h"
#pragma once


typedef struct tagDataBaseContext
{
	DWORD			dwIndex;									//索引
	IDataBaseEngineSink   *pDataBaseEngineSink;
	DWORD			dwDataBaseStatus;
#define DATABASE_IS_WAITING		0								// 数据库连接,等待状态,此时说明连接可以被使用
#define DATABASE_IS_RUNNING		1								// 数据库连接,运行状态,只有运行结束后回来等待状态,才能被使用
}DATABASEPOOL,*PDATABASEPOOL;

class CDataBasePool
{
public:
	CDataBasePool();
	virtual ~CDataBasePool();

public:
	bool InitiDataBasePool(IDataBaseEngineSink * pIUnknownEx[], WORD wSinkCount);
	bool DataBaseEngineStart(IUnknownEx * pIUnknownEx);
	bool DataBaseEngineStop(IUnknownEx * pIUnknownEx);
	bool CloseDataBasePool();
	bool AllocDataBaseConnections(DATABASEPOOL *pIDataBaseEnginePool);
	bool RelexDataBaseConnections(DATABASEPOOL *pIDataBaseEnginePool);
public:		
	int						m_nConnections;				
	DATABASEPOOL			*m_pIDataBaseEngineSink;			//通知钩子
	CRITICAL_SECTION		m_DataBasePoolLock;	
};