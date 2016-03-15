#pragma once
#include "afxwin.h"


// CCDlgFrezon 对话框

class CCDlgFrezon : public CDialog
{
	DECLARE_DYNAMIC(CCDlgFrezon)

public:
	CCDlgFrezon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCDlgFrezon();

public:
	CString   m_strFrezonReason;
// 对话框数据
	enum { IDD = IDD_FREZON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	afx_msg void OnBnClickedOk();
};
