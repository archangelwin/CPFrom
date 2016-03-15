#ifndef TRACE_SERVICE_HEAD_FILE
#define TRACE_SERVICE_HEAD_FILE

#pragma once

#include "KernelEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//׷�ٷ���
class KERNEL_ENGINE_CLASS CTraceService
{
	//��������
protected:
	//����ܸ߿�www.cnyjwl.com�캯��
	CTraceService();

	//������ܸ߿�www.cnyjwl.com����
public:
	//���÷���ܸ߿�www.cnyjwl.com��
	static bool SetTraceService(IUnknownEx * pIUnknownEx);
	//����ܸ߿�www.cnyjwl.comȡ����
	static VOID * GetTraceService(const IID & Guid, DWORD dwQueryVer);
	//��ȡ��ܸ߿�www.cnyjwl.com����
	static VOID * GetTraceServiceManager(const IID & Guid, DWORD dwQueryVer);

	//״̬����
public:
	//׷��״̬
	static bool IsEnableTrace(enTraceLevel TraceLevel);
	//׷�ٿ���
	static bool EnableTrace(enTraceLevel TraceLevel, bool bEnableTrace);

	//���ܺ���
public:
	//׷����Ϣ
	static bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////

//׷�ٷ���ܸ߿�www.cnyjwl.com��
class KERNEL_ENGINE_CLASS CTraceServiceControl : public CRichEditCtrl, public ITraceService
{
	//��������ܸ߿�www.cnyjwl.com��
protected:
	LONG							m_lMaxLineCount;					//�������
	LONG							m_lReserveLineCount;				//��������
	BYTE							m_cbBuffer[MAX_ASYNCHRONISM_DATA];	//��ʱ����

	//�������
protected:
	CWHDataQueue					m_DataQueue;						//���ݶ���
	CCriticalSection				m_CriticalSection;					//ͬ������

	//����ܸ߿�www.cnyjwl.com������
public:
	//������ܸ߿�www.cnyjwl.com����
	CTraceServiceControl();
	//��������ܸ߿�www.cnyjwl.com��
	virtual ~CTraceServiceControl();

	//�����ӿ���ܸ߿�www.cnyjwl.com
public:

	virtual VOID Release(){};
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//��Ϣ�ӿ�
public:
	//׷����Ϣ
	virtual bool __cdecl TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);

	//���غ���
protected:
	//�󶨺���
	virtual VOID PreSubclassWindow();

	//���ܺ���
public:
	//������Ϣ
	bool LoadMessage(LPCTSTR pszFileName);
	//������Ϣ
	bool SaveMessage(LPCTSTR pszFileName);
	//���ò���
	bool SetParameter(LONG lMaxLineCount, LONG lReserveLineCount);

	//��������
private:
	//���÷���
	VOID InitializeService();
	//��ȡ��ɫ
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//�����ִ�
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

	//�ص�����
private:
	//��ܸ߿�www.cnyjwl.com���ػص�
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//��ܸ߿�www.cnyjwl.com����ص�
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	//��ܸ߿�www.cnyjwl.com�˵�����
protected:
	//ɾ����Ϣ
	VOID OnClearAll();
	//ȫ��ѡ��
	VOID OnSelectAll();
	//�����ַ�
	VOID OnCopyString();
	//������Ϣ
	VOID OnSaveString();
	//ɾ���ַ�
	VOID OnDeleteString();

	//��Ϣӳ��
protected:
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�Ҽ���Ϣ
	VOID OnRButtonDown(UINT nFlags, CPoint point);
	//׷����Ϣ
	LRESULT OnTraceServiceMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif