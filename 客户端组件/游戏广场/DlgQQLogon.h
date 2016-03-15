#ifndef DLG_QQLOGON_HEAD_FILE
#define DLG_QQLOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PlatformPublicize.h"
// CDlgQQLogon 对话框

class CDlgQQLogon : public CDialog
{
	//friend class CDlgLogon;
	DECLARE_DYNAMIC(CDlgQQLogon)

public:
	CDlgQQLogon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgQQLogon();
	void SetUrl(CString sUrl);
	void MoveDlg(int nWidth, int nHeight);

protected:
	long                            m_hLength;//长度 
	long                            m_hWidth;//宽度
	long                            m_hLeft;//左偏移的长度
	CString                         m_sQQUrl;
	CWebBrowser2				    m_BroswerQQLogon;				//浏览控件
	CSkinButton                     m_btClose;
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件

// 对话框数据
	enum { IDD = IDD_DIALOG_QQLOGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnNavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////////

#endif
