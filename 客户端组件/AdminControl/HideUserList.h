#pragma once

#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "..\CGridListCtrlEx\ButtonEx.h"
#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "GameInfo.h"

struct CListCtrl_HideUser
{
	CListCtrl_HideUser()
	{}
	CListCtrl_HideUser(const CString& UserID,const CString& NickName)
		:m_UserID(UserID)
		,m_NickName(NickName)
	{}

	CString m_UserID;
	CString m_NickName;
	CString  m_STemp;

	const CString& GetCellText(int col, bool title) const
	{
		switch (col)
		{
		case 0:{static CString title0(L"UserID"); return title ? title0 : m_UserID;}
		case 1:{static CString title1(L"Í«≥∆"); return title ? title1 : m_NickName;}
		}
		return m_STemp;
	}

	int  GetColCount() const { return 2; }
};

class CHideUserList : public CGridListCtrlGroups
{
public:
	CHideUserList(void);
	~CHideUserList(void);
public:
	CImageList m_ImageList;
	GameInfo  m_HideUserInfo;

	int nRow, nCol;
public:
	VOID InitHideUserInfo();

	VOID InsertUserInfo();

protected:
	//”“º¸¡–±Ì
	VOID OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult);

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);


	const CString& GetColTitle(int col) const { return CListCtrl_HideUser().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_HideUser().GetColCount(); }
};
