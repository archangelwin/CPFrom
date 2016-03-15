#pragma once
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
#include "afxcmn.h"

// CDlgSilver 对话框

class CDlgSilver : public CDialog
{
	DECLARE_DYNAMIC(CDlgSilver)

public:
	CDlgSilver(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSilver();

// 对话框数据
	enum { IDD = IDD_DIALOG_SILVER };

protected:
	CUserInfoMap    m_SilverMap;

public:
	bool OnInsertSilver(tagUMUserScoreSet* pUserInfo);

	bool OnDeleteSilver(tagUMUserScoreSet* pUserInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CUserInfoList m_SilverList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
