#pragma once
#include "afxwin.h"


// CCDlgFrezon �Ի���

class CCDlgFrezon : public CDialog
{
	DECLARE_DYNAMIC(CCDlgFrezon)

public:
	CCDlgFrezon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCDlgFrezon();

public:
	CString   m_strFrezonReason;
// �Ի�������
	enum { IDD = IDD_FREZON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	afx_msg void OnBnClickedOk();
};
