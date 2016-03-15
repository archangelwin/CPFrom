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

struct CListCtrl_DataStock
{
	CListCtrl_DataStock()
	{}
	CListCtrl_DataStock(const CString& ServerID,const CString& StoragStart,const CString& StorageDeduct,const CString& nIsSet,
		const CString& nWeekScore,const CString& nMonthScore,const CString& nAllScore)
						:m_ServerID(ServerID)
						,m_StoragStart(StoragStart)
						,m_StorageDeduct(StorageDeduct)
						,m_nIsSet(nIsSet)
						,m_nWeekScore(nWeekScore)
						,m_nMonthScore(nMonthScore)
						,m_nAllScore(nAllScore)
	{}

	CString  m_ServerID;
	CString  m_StoragStart;
	CString  m_StorageDeduct;
	CString  m_nIsSet;
	CString  m_STemp;
	CString  m_nWeekScore;
	CString  m_nMonthScore;
	CString  m_nAllScore;
	
	const CString& GetCellText(int col, bool title) const
	{
		switch(col)
		{
		case 0:{ static CString title0(L"序号"); return title ? title0 : m_ServerID; }
		case 1:{ static CString title1(L"场次"); return title ? title1 : m_ServerID; }
		case 2:{ static CString title2(L"起始分数"); return title ? title2 : m_StoragStart; }
	    case 3:{ static CString title3(L"衰减值(‰)"); return title ? title3 : m_StorageDeduct; }
	    case 4:{ static CString title4(L"状态"); return title ? title4 : m_nIsSet; }
		case 5:{ static CString title5(L"ServerID"); return title ? title5 : m_ServerID; }
	    case 6:{ static CString title6(L"前天累计"); return title ? title6 : m_nWeekScore; }
		case 7:{ static CString title7(L"昨天累计"); return title ? title7 : m_nMonthScore; }
		case 8:{ static CString title8(L"当天累计"); return title ? title8 : m_nAllScore; }
		}
		return m_STemp;
	}

	int  GetColCount() const { return 9; }

};

class CStockList : public CGridListCtrlGroups
{
public:
	CStockList(void);
	~CStockList(void);

public:
	CListCtrl_DataStock m_DataStick;
	CGameServerItem* m_pGameServerItem;
	tabStoragStartArray m_tabStoragStartArray;
	CImageList m_ImageList;
	
public:
	VOID InitStockInfoList();
	VOID OnInsertStockDataInfo(tagUMSysGameSet* ptagUMSysGameSet);
	void OnSetStockDataInfo();
	SCORE OnGetAllTodatScore();
	SCORE OnGetAllYesterdayScore();
	SCORE OnGetAllYesafterdayScore();

protected:
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);

	afx_msg BOOL OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);


protected:
	const CString& GetColTitle(int col) const { return CListCtrl_DataStock().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_DataStock().GetColCount(); }

	DECLARE_MESSAGE_MAP()
};
