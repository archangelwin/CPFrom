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

struct CListCtrl_DataUserStock
{
	CListCtrl_DataUserStock()
	{}
	CListCtrl_DataUserStock(const CString& GameID,const CString& NickName,const CString& UserGold)
		:m_GameID(GameID)
		,m_NickName(NickName)
		,m_UserGold(UserGold)
	{}

	CString  m_GameID;
	CString  m_NickName;
	CString  m_UserGold;

	const CString& GetCellText(int col, bool title) const
	{
		switch(col)
		{
		case 0:{ static CString title0(L"GameID"); return title ? title0 : m_GameID; }
		case 1:{ static CString title1(L"êÇ³Æ"); return title ? title1 : m_NickName; }
		case 2:{ static CString title2(L"½ð±Ò"); return title ? title2 : m_UserGold; }
		default:{ static CString emptyStr; return emptyStr; }
		}
	}

	int  GetColCount() const { return 3; }

};

class CStockUserList : public CGridListCtrlGroups
{
public:
	CStockUserList(void);
	~CStockUserList(void);

public:
	CListCtrl_DataUserStock m_StockUserData;
	CImageList m_ImageList;
	tagUMUserScoreSet m_UMUserScoreSet;

public:
	VOID InitStockInfoList();

	VOID OnInsertStockDataInfo(tagQueryGameScore pUserScore);

	VOID OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type);


protected:
	const CString& GetColTitle(int col) const { return CListCtrl_DataUserStock().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_DataUserStock().GetColCount(); }

	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg BOOL OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult);


	DECLARE_MESSAGE_MAP();
};
