#include "KernelEngineHead.h"
#pragma once


typedef struct tagDataBaseContext
{
	DWORD			dwIndex;									//����
	IDataBaseEngineSink   *pDataBaseEngineSink;
	DWORD			dwDataBaseStatus;
#define DATABASE_IS_WAITING		0								// ���ݿ�����,�ȴ�״̬,��ʱ˵�����ӿ��Ա�ʹ��
#define DATABASE_IS_RUNNING		1								// ���ݿ�����,����״̬,ֻ�����н���������ȴ�״̬,���ܱ�ʹ��
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
	DATABASEPOOL			*m_pIDataBaseEngineSink;			//֪ͨ����
	CRITICAL_SECTION		m_DataBasePoolLock;	
};