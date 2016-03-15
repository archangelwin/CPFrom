#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PlatformPublicize.h"
// CMessagePop 对话框

class CMessagePop : public CSkinDialog
{
	DECLARE_DYNAMIC(CMessagePop)

public:
	CMessagePop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessagePop();
	void SetWindowSize(int nwindowcx,int nWindowcy,int nWebBrowsercx,int nWebBrowsercy);
	void InitWebDlg(CString sUrl,CString sCaption,bool bDoModal,bool bMsgPop=true,int nElapse=0);
	void UpdateUrl(CString sUrl);
	
protected:
	CWebBrowser2				    m_BroswerMsg;				//浏览控件
	CSkinButton                     m_btSubmit;

private:
	int m_nWindowcx;
	int m_nWindowcy;
	int m_nWebBrowsercx;
	int m_nWebBrowsercy;
	CString m_sUrl;
	CString m_strCaption;
	bool m_bDoModal;
	bool m_bMsgPop;
	int	m_nElapse;

// 对话框数据
	enum { IDD = IDD_DIALOG_MSGPOP };

protected:
	afx_msg void OnBnClickedButtonPopMsg();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//重画消息
	//VOID OnPaint();
	virtual VOID OnCancel();
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();	
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
