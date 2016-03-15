
// AdminControlDlg.h : ͷ�ļ�
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
// CAdminControlDlg �Ի���
class CAdminControlDlg : public CDialog
{
// ����
public:
	CAdminControlDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CAdminControlDlg();

// �Ի�������
	enum { IDD = IDD_ADMINCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:
	LRESULT OnUserOnlinePrompt(WPARAM wParam, LPARAM lParam);
// ʵ��
protected:
	HICON m_hIcon;
	CRect m_rect;
	void ChangeSize(UINT nID, int x, int y);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	LRESULT OnChangeDlg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CGameUserListDlg	m_GameUserListDlg;        //�û��б�Ի���
//	CDlgWeb				m_WebDlg;
	CDlgStock			m_StockDlg;
	CDlgLog				m_LogDlg;
	CDlgUserOnLineSort  m_OnLineUserSortDlg;
	CUserOfflineDlg     m_OffLineUserDlg;
	CDlgSilver          m_SilverDlg;

	CUserOnLinePrompt* m_pUserPromptDlg;

	CDlgHideUser* m_HideUserdlg;

	CServerListView m_ServerList;			//��Ϸ�б�
	CServerListData m_ServerData;           //��Ϸ�б���Ϣ
	CImageList	m_ImageList;             
	CTabCtrl m_TablePag;				
	CTabSheet m_TabSheet;                    //�û��б�tabҳ 
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckHideUser();
};
