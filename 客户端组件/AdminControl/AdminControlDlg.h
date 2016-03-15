
// AdminControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "GameUserListDlg.h"
#include "TabSheet.h"
#include "DlgLogon.h"
#include "MissionList.h"
#include "ServerListView.h"
#include "MissionManager.h"
#include "DlgSysGameSet.h"
#include "DlgWeb.h"
#include "DlgStock.h"
#include "DlgLog.h"
#include "UserOnLinePrompt.h"
#include "DlgHideUser.h"
#include "DlgUserOnLineSort.h"
#include "UserOfflineDlg.h"
#include "DlgSilver.h"

#define  WM_DLG_CHANGE          WM_USER+200
// CAdminControlDlg 对话框
class CAdminControlDlg : public CDialog
{
// 构造
public:
	CAdminControlDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CAdminControlDlg();

// 对话框数据
	enum { IDD = IDD_ADMINCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:
	LRESULT OnUserOnlinePrompt(WPARAM wParam, LPARAM lParam);
// 实现
protected:
	HICON m_hIcon;
	CRect m_rect;
	void ChangeSize(UINT nID, int x, int y);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//取消消息
	virtual VOID OnCancel();

	LRESULT OnChangeDlg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CGameUserListDlg	m_GameUserListDlg;        //用户列表对话框
//	CDlgWeb				m_WebDlg;
	CDlgStock			m_StockDlg;
	CDlgLog				m_LogDlg;
	CDlgUserOnLineSort  m_OnLineUserSortDlg;
	CUserOfflineDlg     m_OffLineUserDlg;
	CDlgSilver          m_SilverDlg;

	CUserOnLinePrompt* m_pUserPromptDlg;

	CDlgHideUser* m_HideUserdlg;

	CServerListView m_ServerList;			//游戏列表
	CServerListData m_ServerData;           //游戏列表信息
	CImageList	m_ImageList;             
	CTabCtrl m_TablePag;				
	CTabSheet m_TabSheet;                    //用户列表tab页 
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckHideUser();
};
