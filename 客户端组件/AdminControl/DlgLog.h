#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "EditLog.h"

// CDlgLog 对话框

class CDlgLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgLog)

public:
	CDlgLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLog();

	UINT      m_Index;

// 对话框数据
	enum { IDD = IDD_LOG };

public:
	bool OnInsertOnLineUser(tagAdmin* ptagAdmin);

	bool OnInsertLog(tagLog* ptagLog);

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_AdminList;
	CEdit m_LogCtrl;

	CEditLog m_EditLog;
};
