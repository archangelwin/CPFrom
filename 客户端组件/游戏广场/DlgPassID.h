#ifndef DLG_PASSID_HEAD_FILE
#define DLG_PASSID_HEAD_FILE

#pragma once
#include "Stdafx.h"

// CDlgPassID �Ի���

class CDlgPassID : public CSkinDialog
{
//	DECLARE_DYNAMIC(CDlgPassID)

public:
	CDlgPassID();   // ��׼���캯��
	virtual ~CDlgPassID();

// �Ի�������
	enum { IDD = IDD_DIALOG_PASSID };
	//��������
public:
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];	//֤������

	//�ؼ�����
protected:
	CSkinButton						m_btOk;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

	CSkinEdit						m_edPassID;						     //���֤��

	CPasswordControl				m_CtrPasswordControl;					//�û�����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();

	DECLARE_MESSAGE_MAP()
};


#endif