#pragma once

#include "Stdafx.h"
// CAlmsDlg �Ի���

class CAlmsDlg : public CSkinDialog, public CMissionItem
{
public:
	CAlmsDlg();   // ��׼���캯��
	virtual ~CAlmsDlg();

protected:
	CSkinButton						m_btGetAlms;
	CWebPublicize					m_WebPublicize;						//������� 	
	CMissionManager					m_MissionManager;					//�������
	//�ػ���Ϣ
	//VOID OnPaint();
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnBnClickedButtonAlms();

public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};
