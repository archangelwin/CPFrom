#pragma once
#include "afxcmn.h"
#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "UserInfoList.h"
#include "UserServerInfo.h"
#include "afxwin.h"

// CUserOfflineDlg 对话框

class CUserOfflineDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserOfflineDlg)

public:
	CUserOfflineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserOfflineDlg();

// 对话框数据
	enum { IDD = IDD_USER_OFFLINE_DLG };

public:
	CUserInfoMap m_UserOffLineMap;
	bool         m_GetOffLine;

public:
	bool OnInsertOFFLineUserInfo(tagUMUserScoreSet* pUserInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CUserInfoList m_OffLineList;
	afx_msg void OnBnClickedButtonGetOffline();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_BtGetOffLine;
};
