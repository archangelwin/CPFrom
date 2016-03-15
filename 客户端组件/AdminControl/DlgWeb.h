#pragma once
#include "explorer1.h"


// CDlgWeb 对话框

class CDlgWeb : public CDialog
{
	DECLARE_DYNAMIC(CDlgWeb)

public:
	CDlgWeb(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWeb();

// 对话框数据
	enum { IDD = IDD_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	CExplorer1 m_WebControl;
};
