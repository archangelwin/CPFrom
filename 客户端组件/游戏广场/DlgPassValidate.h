#pragma once

#include "Stdafx.h"
#include "Resource.h"
// CDlgPassValidate �Ի���

class CDlgPassValidate : public CSkinDialog
{
	DECLARE_DYNAMIC(CDlgPassValidate)

public:
	CDlgPassValidate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPassValidate();
	void SetValidateType(int nType);
	CString m_sValidateCode;

// �Ի�������
	enum { IDD = IDD_DIALOG_PASSVALIDATE };

protected:
	CSkinButton						m_btEnSure;								//ȷ����ť
	CSkinHyperLink                  m_cTitleValidate;
	CSkinEdit                       m_eValidate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPassvali();

private:
	int m_nValidateType; //8У���ֻ�,9У�����֤
};
