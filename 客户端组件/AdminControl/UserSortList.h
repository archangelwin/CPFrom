#pragma once
#include "Stdafx.h"
#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "..\CGridListCtrlEx\ButtonEx.h"
#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "..\CGridListCtrlEx\CGridColumnTraitImage.h"
#include "UserInfoList.h"
#include "GameInfo.h"

class CUserSortList : public CGridListCtrlGroups
{
public:
	CUserSortList(void);
	virtual ~CUserSortList(void);

public:
public:
	CListCtrl_DataRecord m_GameUserInfo;

	CImageList m_ImageSortList;

	GameInfo        m_GameInfo;

	DWORD   m_IsSet;

	DWORD   m_nPlatKind;

	DWORD   m_nPlat;
public:
	//初始化列表
	VOID InitUserInfoList();

	INT OnUpDataUserData(DWORD UserID);

	VOID OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem);

protected:

	const CString& GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }
};
