#include "StdAfx.h"
#include "StockUserList.h"
#include "UserInfoDlg.h"
#include "UserServerInfo.h"
#include "DlgUserInfo.h"
#include "MissionUserInfo.h"

CStockUserList::CStockUserList(void)
{
}

CStockUserList::~CStockUserList(void)
{
}
BEGIN_MESSAGE_MAP(CStockUserList, CGridListCtrlGroups)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnItemDblClick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CStockUserList::InitStockInfoList()
{
	m_ImageList.Create(1, 20, ILC_COLOR16 | ILC_MASK, 1, 0);
	SetImageList(&m_ImageList, LVSIL_SMALL);

	int Col;
	for (Col=0;Col<this->GetColCount();++Col)
	{
		const CString& title = GetColTitle(Col);
		CGridColumnTrait* pTrait = NULL;
// 		if (Col == 2 || Col == 3)
// 		{
// 			pTrait = new CGridColumnTraitEdit;
// 		}else
			pTrait = new CGridColumnTraitText;

		InsertColumnTrait(Col, title, LVCFMT_LEFT, 97, Col, pTrait);
	}
	SetColumnWidth(0,50);
	SetCellMargin(1);
}

void CStockUserList::OnInsertStockDataInfo(tagQueryGameScore pUserScore)
{
	int nItem = 0;
	CString szText;
	for (nItem;nItem<GetItemCount();nItem++)
	{
		int n = _ttoi(GetItemText(nItem,0));

		if (pUserScore.dwGameID == n)
		{
			int col=0;
			switch(col)
			{
			case 0:
				{
					szText.Format("%d",pUserScore.dwGameID);
					SetItemText(nItem,col++,szText);
				}
			case 1:
				{
					szText.Format("%s",pUserScore.szNickName);
					SetItemText(nItem,col++,szText);
				}
			case 2:
				{
					szText.Format("%I64d",pUserScore.lScore);
					SetItemText(nItem,col++,szText);
				}
			}

			return;
		}
	}

	int iLine = GetItemCount();
	szText.Format(_T("%d"),iLine);
	InsertItem(iLine,szText);
	SetItemData(iLine, (DWORD)&pUserScore);

	int col = 0;
	switch(col)
	{
	case 0:
		{
			szText.Format("%d",pUserScore.dwGameID);
			SetItemText(iLine,col++,szText);
		}
	case 1:
		{
			szText.Format("%s",pUserScore.szNickName);
			SetItemText(iLine,col++,szText);
		}
	case 2:
		{
			szText.Format("%I64d",pUserScore.lScore);
			SetItemText(iLine,col++,szText);
		}
	}

}

void CStockUserList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	int nRow = (int)pLVCD->nmcd.dwItemSpec;

	*pResult = CDRF_DODEFAULT;

	// Allow column-traits to perform their custom drawing
	if (pLVCD->nmcd.dwDrawStage & CDDS_SUBITEM)
	{
		OnCustomDrawRow(nRow, pLVCD, pResult);
		if (*pResult & CDRF_SKIPDEFAULT)
			return;	// Everything is handled by the row-trait

		int nCol = pLVCD->iSubItem;
		OnCustomDrawCell(nRow, nCol, pLVCD, pResult);
		if (*pResult & CDRF_SKIPDEFAULT)
			return;	// Everything is handled by the column-trait
	}

	// Always perform drawing of cell-focus rectangle
	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult |= CDRF_NOTIFYITEMDRAW;
		break;

		// Before painting a row
	case CDDS_ITEMPREPAINT:
		{
			*pResult |= CDRF_NOTIFYPOSTPAINT;	// Ensure row-traits gets called
			*pResult |= CDRF_NOTIFYSUBITEMDRAW;	// Ensure column-traits gets called

// 			SCORE m_Win = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.lMaxWin1/*_ttoi(GetItemText(nRow,11))*/;
// 			SCORE m_Warning = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.lNotifyMaxWin/*_ttoi(GetItemText(nRow,17))*/;
// 			SCORE m_Warning1 = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.lNotifyMaxLost/*_ttoi(GetItemText(nRow,18))*/;
// 
// 			if (m_Win >= m_Warning || m_Win <= m_Warning1)
// 			{
// 				pLVCD->clrText = RGB(255,0, 0);
// 			}
// 			if(((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.nVipType == 1)
// 			{
// 				pLVCD->clrText = RGB(0,0, 255);
// 			}
// 			if(((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.wOnline == 0)
// 			{
// 				pLVCD->clrText = RGB(188,188,173);
// 			}

			//pLVCD->clrText = RGB(0,0,0);

			*pResult = CDRF_DODEFAULT;
			OnCustomDrawRow(nRow, pLVCD, pResult);  
		} break;

		// After painting the entire row
	case CDDS_ITEMPOSTPAINT:
		{
			OnCustomDrawRow(nRow, pLVCD, pResult);
		} break;
	}
}

BOOL CStockUserList::OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	CellHitTest(pItem->ptAction, nRow, nCol);

	CString szText;
	if (nRow != -1)
	{
		szText = GetItemText(nRow,0);
//		tagQueryGameScore *lQueryGameScore = (tagQueryGameScore*)GetItemData(nRow);
		//AfxMessageBox(szText);

		/*tagUMUserScoreSet UMUserScoreSet;*/
		//ZeroMemory(&m_UMUserScoreSet,sizeof(tagUMUserScoreSet));

		ASSERT(CUserServerInfo::GetInstance()!=NULL);
// 		if (CUserServerInfo::GetInstance()->OnSerachUserInfo(szText,m_UMUserScoreSet) == false)
// 		{
// 			AfxMessageBox("没有找到在线用户");
// 
// 			return FALSE;
// 		}

		m_UMUserScoreSet = CUserServerInfo::GetInstance()->OnSerachUserInfo(szText);

		//m_UMUserScoreSet.dwServerID = _ttoi(szText);
// 		if (m_UMUserScoreSet.dwServerID == 0)
// 		{
// 			AfxMessageBox("用户不在线!");
// 
// 			return FALSE;
// 		}
		
		CDlgUserInfo UserInfoDlg;
		UserInfoDlg.m_tagUserInfo = m_UMUserScoreSet;

		if (UserInfoDlg.DoModal() == IDOK)
		{
			//return FALSE;
			CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;

			if (UserInfoDlg.m_AllowSet == 1)
			{
				if (_ttoi64(WinLoseScore)>_ttoi64(WinMax) || _ttoi64(WinLoseScore)<_ttoi64(LoseMax))
				{
					AfxMessageBox("设置输赢分数不能高于赢最高,或者低于输最高！");
					return FALSE;
				}
				OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
					UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
			}else
			{
				// 				int pos = UserInfoDlg.m_CombState.GetCurSel();
				// 				if (pos < 0)
				// 				{
				// 					ntype = MAXDEFAULT;
				// 				}
				OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
					UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
			}
		}

	}

	return FALSE;
}


VOID CStockUserList::OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type)
{
	DWORD userID = 0;
	int nListCount = GetItemCount();
	TCHAR szControl[128]=TEXT("");
	CString szItemText;

	tagUMUserScoreSet m_UserScoreSet;
	CopyMemory(&m_UserScoreSet,&m_UMUserScoreSet,sizeof(tagUMUserScoreSet));

	m_UserScoreSet.dwWinOrLostRate = _ttoi(lRate);
	m_UserScoreSet.lSetWinOrLose = _ttoi(WinLoseScore);
	m_UserScoreSet.lMaxWin = _ttoi(WinMax);
	m_UserScoreSet.lMaxLose = _ttoi(LoseMax);
	m_UserScoreSet.lNotifyMaxWin = _ttoi(NotifyWin);
	m_UserScoreSet.lNotifyMaxLost = _ttoi(NotifyLose);

	if (m_UserScoreSet.lMaxLose > 0 || m_UserScoreSet.lNotifyMaxLost > 0)
	{
		AfxMessageBox("输最高或者预警输必须小于零！");

		return;
	}
	if (m_UserScoreSet.lMaxWin < 0 || m_UserScoreSet.lNotifyMaxWin < 0)
	{
		AfxMessageBox("赢最高或者预警赢必须大于零！");

		return;
	}

	if (Type == MAXWIN)
	{
		m_UserScoreSet.dwType = MAXWIN;
	}else if (Type == MAXLOSE)
	{
		m_UserScoreSet.dwType = MAXLOSE;
	}else if (Type == MAXDEFAULT)
	{
		m_UserScoreSet.dwType = MAXDEFAULT;
	}

	CTime tmSCan = CTime::GetCurrentTime();
	CString szTime = tmSCan.Format("'%Y-%m-%d %H:%M:%S'");
	m_UserScoreSet.dwSetTime = _ttoi(szTime);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetOffLineUser(m_UserScoreSet);
}