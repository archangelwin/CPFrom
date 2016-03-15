#ifndef TIMERENGINE_HEAD_FILE
#define TIMERENGINE_HEAD_FILE

#pragma once

//ϵͳͷ�ļ�

#include "KernelEngineHead.h"
#include "QueueServiceEvent.h"

#define TIMER_SPACE								25				//ʱ����

//��˵��
class CTimerEngine;

//////////////////////////////////////////////////////////////////////////

//��ʱ���߳�
class CTimerThread : public CWHThread
{
	//��������
protected:
	CTimerEngine						* m_pTimerEngine;				//��ʱ������
	//��������
public:
	//���캯��
	CTimerThread(void);
	//��������
	virtual ~CTimerThread(void);

	//���ܺ���
public:
	//���ú���
	bool InitThread(CTimerEngine * pTimerEngine);

	//���غ���
private:
	//���к���
	virtual bool OnEventThreadRun();
};

//////////////////////////////////////////////////////////////////////////

//��ʱ������
struct tagTimerItem
{
	DWORD								wTimerID;						//��ʱ�� ID
	DWORD								dwElapse;						//��ʱʱ��
	DWORD								dwTimeLeave;					//����ʱ��
	DWORD								dwRepeatTimes;					//�ظ�����
	WPARAM								wBindParam;						//�󶨲���
};

//��ʱ���������鶨��
typedef CWHArray<tagTimerItem *> CTimerItemPtr;

//////////////////////////////////////////////////////////////////////////

//��ʱ������
class CTimerEngine : public ITimerEngine
{
	friend class CTimerThread;

	//״̬����
protected:
	bool								m_bService;						//���б�־
	CTimerItemPtr						m_TimerItemFree;				//��������
	CTimerItemPtr						m_TimerItemActive;				//�����

	//�������
protected:
	CCriticalSection					m_CriticalSection; //	//�߳���
	CTimerThread						m_TimerThread;					//��ʱ���߳�
	IQueueServiceSink					*m_pIQueueServiceSink;			//֪ͨ�ص�
	CQueueServiceEvent					m_AttemperEvent;				//֪ͨ���
	//��������
public:
	//���캯��ܸ߿�www.cnyjwl.com��
	CTimerEngine(void);
	//������ܸ߿�www.cnyjwl.com����
	virtual ~CTimerEngine(void);

	//����ܸ߿�www.cnyjwl.com���ӿ�
public:
	//�ͷŶ���
	virtual VOID Release()
	{
		delete this;    //
	}
	//����ܸ߿�www.cnyjwl.com�ڲ�ѯ
	virtual void * QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�ӿں���ܸ߿�www.cnyjwl.com��
public:
	//���ö�ʱ��ܸ߿�www.cnyjwl.com��
	virtual bool __cdecl SetTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM dwBindParameter);
	//ɾ����ʱ��
	virtual bool __cdecl KillTimer(DWORD dwTimerID);
	//ɾ������ܸ߿�www.cnyjwl.comʱ��
	virtual bool __cdecl KillAllTimer();
	//���ýӿ�
	virtual bool __cdecl SetTimerEngineEvent(IUnknownEx * pIUnknownEx);

	//����ӿ�
public:
	//��ʼ����
	virtual bool /*__cdecl*/ StartService();
	//ֹͣ����
	virtual bool /*__cdecl*/ ConcludeService();

	//�ڲ�����
private:
	//��ʱ��ܸ߿�www.cnyjwl.com��֪ͨ
	void OnTimerThreadSink();
};

//////////////////////////////////////////////////////////////////////////

#endif