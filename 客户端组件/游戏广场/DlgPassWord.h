#ifndef DLG_PASSWORD_HEAD_FILE
#define DLG_PASSWORD_HEAD_FILE


#pragma once
#include "Stdafx.h"

// CDlgPassWord �Ի���

class CDlgPassWord : public CSkinDialog
{
//	DECLARE_DYNAMIC(CDlgPassWord)

public:
	CDlgPassWord();   // ��׼���캯��
	virtual ~CDlgPassWord();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOCKMACHINE };
//����
public:
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
//�ؼ�
protected:
	CSkinButton						m_btOk;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť


	CPasswordControl				m_CtrPasswordControl;					//�û�����


	DECLARE_MESSAGE_MAP()
};


#endif