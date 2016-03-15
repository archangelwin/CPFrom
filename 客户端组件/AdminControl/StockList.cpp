#include "StdAfx.h"
#include "StockList.h"
#include "MissionUserInfo.h"
//转换数字
void MakeStringToNum(CString str,SCORE &Num)
{
	CString strNumber = str;
	strNumber.Remove(',');
	strNumber.Trim();

#ifndef _UNICODE
	_snscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#else
	_snwscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#endif
	strNumber.ReleaseBuffer();
}

CStockList::CStockList(void)
{
	m_pGameServerItem = NULL;
	m_tabStoragStartArray.dwCount = 0;
}

CStockList::~CStockList(void)
{
	if (m_pGameServerItem!=NULL)
	{
		SafeDelete(m_pGameServerItem);
	}
}

BEGIN_MESSAGE_MAP(CStockList, CGridListCtrlGroups)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnItemDblClick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CStockList::InitStockInfoList()
{
	m_ImageList.Create(1, 20, ILC_COLOR16 | ILC_MASK, 1, 0);
	SetImageList(&m_ImageList, LVSIL_SMALL);

	int Col;
	for (Col=0;Col<this->GetColCount();++Col)
	{
		const CString& title = GetColTitle(Col);
		CGridColumnTrait* pTrait = NULL;
		if (Col == 2 || Col == 3)
		{
			pTrait = new CGridColumnTraitEdit;
		}else
			pTrait = new CGridColumnTraitText;

		InsertColumnTrait(Col, title, LVCFMT_LEFT, 97, Col, pTrait);
	}
	SetColumnWidth(0,50);
	SetCellMargin(1);
}


void CStockList::OnInsertStockDataInfo(tagUMSysGameSet* ptagUMSysGameSet)
{
	CServerListData* pCServerListData = CServerListData::GetInstance();
	if (pCServerListData == NULL)
	{
		return;
	}

	m_pGameServerItem = pCServerListData->SearchGameServer(ptagUMSysGameSet->dwServerID); 

	LPCTSTR GameName = m_pGameServerItem->m_GameServer.szServerName;
	if (GameName == NULL)
	{
		//AfxMessageBox("没有获取游戏房间！");
		return;
	}

	TCHAR szControl[128]=TEXT("");
	int nItem = 0;
	CString szText;
	for (nItem;nItem<GetItemCount();nItem++)
	{
		DWORD n = _ttoi(GetItemText(nItem,5));
		
		if (ptagUMSysGameSet->dwServerID == n)
		{
			int col = 0;
			switch(col)
			{
			case 0:
				{
// 					CServerListData* pCServerListData = CServerListData::GetInstance();
// 					if (pCServerListData == NULL)
// 					{
// 						break;
// 					}
// 					m_pGameServerItem = pCServerListData->SearchGameServer(ptagUMSysGameSet->dwServerID); 
// 
// 					LPCTSTR GameName = m_pGameServerItem->m_GameServer.szServerName;
// 					if (GameName == NULL)
// 					{
// 						//AfxMessageBox("没有获取游戏房间！");
// 						break;
// 					}

					szText.Format(_T("%s"),GameName);
					SetItemText(nItem,++col,szText);
				}
			case 1:
				{
					SwitchScoreFormat(ptagUMSysGameSet->dwStoragStart,4L,szControl,CountArray(szControl));

					//szText.Format(_T("%lld"),ptagUMSysGameSet->dwStoragStart);
					SetItemText(nItem,++col,szControl);
				}
			case 2:
				{
					szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
					SetItemText(nItem,++col,szText);
				}
			case 3:
				{
					if (ptagUMSysGameSet->bValid==0)
					{
						szText.Format("未启用");
						SetCheck(nItem,FALSE);
					}else{
						szText.Format("启用");
						SetCheck(nItem,TRUE);
					}
					SetItemText(nItem,++col,szText);
				}
			case 4:
				{
					szText.Format(_T("%d"),ptagUMSysGameSet->dwServerID);
					SetItemText(nItem,++col,szText);
				}
			case 5:
				{

					SwitchScoreFormat(ptagUMSysGameSet->WeekScore,4L,szControl,CountArray(szControl));

					//szText.Format(_T("%lld"),ptagUMSysGameSet->WeekScore);
					SetItemText(nItem,++col,szControl);
				}
			case 6:
				{
					SwitchScoreFormat(ptagUMSysGameSet->MonthScore,4L,szControl,CountArray(szControl));

//					szText.Format(_T("%lld"),ptagUMSysGameSet->MonthScore);
					SetItemText(nItem,++col,szControl);
				}
			case 7:
				{
					SwitchScoreFormat(ptagUMSysGameSet->TodayScore,4L,szControl,CountArray(szControl));

					//szText.Format(_T("%lld"),ptagUMSysGameSet->TodayScore);
					SetItemText(nItem,++col,szControl);
				}
			}

			return;
		}
	}
	
//	CServerListData* pCServerListData = CServerListData::GetInstance();
	m_pGameServerItem = pCServerListData->SearchGameServer(ptagUMSysGameSet->dwServerID); 

	/*LPCTSTR */GameName = m_pGameServerItem->m_GameServer.szServerName;
	if (m_pGameServerItem == NULL)
	{
		//AfxMessageBox("没有获取游戏房间！");
		return;
	}
	
	int iLine = GetItemCount();
	szText.Format(_T("%d"),iLine);
	InsertItem(iLine,szText);
	SetItemData(iLine, (DWORD)ptagUMSysGameSet);

	int col = 0;
	switch(col)
	{
	case 0:
		{
			szText.Format(_T("%s"),GameName);
			SetItemText(iLine,++col,szText);
		}
	case 1:
		{
			SwitchScoreFormat(ptagUMSysGameSet->dwStoragStart,4L,szControl,CountArray(szControl));

			//szText.Format(_T("%lld"),ptagUMSysGameSet->dwStoragStart);
			SetItemText(iLine,++col,szControl);
		}
	case 2:
		{
			szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
			SetItemText(iLine,++col,szText);
		}
	case 3:
		{
			if (ptagUMSysGameSet->bValid==0)
			{
				szText.Format("未启用");
				SetCheck(iLine,FALSE);
			}else{
				szText.Format("启用");
				SetCheck(iLine,TRUE);
			}
			SetItemText(iLine,++col,szText);
		}
	case 4:
		{
			szText.Format(_T("%d"),ptagUMSysGameSet->dwServerID);
			SetItemText(iLine,++col,szText);
		}
	case 5:
		{
			SwitchScoreFormat(ptagUMSysGameSet->WeekScore,4L,szControl,CountArray(szControl));

			//szText.Format(_T("%lld"),ptagUMSysGameSet->WeekScore);
			SetItemText(iLine,++col,szControl);
		}
	case 6:
		{
			SwitchScoreFormat(ptagUMSysGameSet->MonthScore,4L,szControl,CountArray(szControl));

			//szText.Format(_T("%d"),ptagUMSysGameSet->MonthScore);
			SetItemText(iLine,++col,szControl);
		}
	case 7:
		{
			SwitchScoreFormat(ptagUMSysGameSet->TodayScore,4L,szControl,CountArray(szControl));

			//szText.Format(_T("%d"),ptagUMSysGameSet->TodayScore);
			SetItemText(iLine,++col,szControl);
		}
	}


	return;
}

SCORE CStockList::OnGetAllTodatScore()
{
	int n = GetItemCount();
	SCORE cbTodayScore = 0;
	CString strtotal;
	SCORE k;
	for (int i=0;i<n;i++)
	{
		//SCORE k=((tagUMSysGameSet*)GetItemData(i))->TodayScore;
		strtotal = GetItemText(i,8);
		MakeStringToNum(strtotal,k);
		//k = _ttoi64(strtotal);
		cbTodayScore+=k;
	}

	return cbTodayScore;
}

SCORE CStockList::OnGetAllYesafterdayScore()
{
	int n = GetItemCount();
	SCORE cbTodayScore = 0;
	CString strtotal;
	SCORE k;
	for (int i=0;i<n;i++)
	{
		//SCORE k=((tagUMSysGameSet*)GetItemData(i))->TodayScore;
		strtotal = GetItemText(i,6);
		MakeStringToNum(strtotal,k);
		//k = _ttoi64(strtotal);
		cbTodayScore+=k;
	}

	return cbTodayScore;
}

SCORE CStockList::OnGetAllYesterdayScore()
{
	int n = GetItemCount();
	SCORE cbTodayScore = 0;
	CString strtotal;
	SCORE k;
	for (int i=0;i<n;i++)
	{
		//SCORE k=((tagUMSysGameSet*)GetItemData(i))->TodayScore;
		strtotal = GetItemText(i,7);
		MakeStringToNum(strtotal,k);
		//k = _ttoi64(strtotal);
		cbTodayScore+=k;
	}

	return cbTodayScore;
}

VOID CStockList::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//转换数值
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//变量定义
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//转换字符
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//拷贝字符
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//插入逗号
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//结束字符
	pszBuffer[wTargetIndex++]=0;

	return;
}

void CStockList::OnSetStockDataInfo()
{
//	tabStoragStartArray* m_tabStoragStartArray = (tabStoragStartArray*)cbBuffer;
	int nItemCount = GetItemCount();
	if (nItemCount==0)
	{
		return;
	}
	BOOL nIsCheck = FALSE;
	int nCount = 0;
	CString szText;
	for (int nItem = 0;nItem<nItemCount;nItem++)
	{
		nIsCheck = GetCheck(nItem);
		if (nIsCheck == TRUE)
		{
			szText = GetItemText(nItem,5);
			m_tabStoragStartArray.StoragStart[nCount].dwServerID = _ttoi(szText);/*((tagUMSysGameSet*)GetItemData(nItem))->dwServerID*/;
			szText = GetItemText(nItem,2);
			m_tabStoragStartArray.StoragStart[nCount].lStoragStart = _ttoi(szText);//((tagUMSysGameSet*)GetItemData(nItem))->dwStoragStart;
			szText = GetItemText(nItem,3);
			m_tabStoragStartArray.StoragStart[nCount].dwStorageDeduct = _ttoi(szText);//((tagUMSysGameSet*)GetItemData(nItem))->dwStorageDeduct;
			m_tabStoragStartArray.StoragStart[nCount].bValid = 1;
		}else{
			szText = GetItemText(nItem,5);
			m_tabStoragStartArray.StoragStart[nCount].dwServerID = _ttoi(szText);//((tagUMSysGameSet*)GetItemData(nItem))->dwServerID;
			szText = GetItemText(nItem,2);
			m_tabStoragStartArray.StoragStart[nCount].lStoragStart = _ttoi(szText);//((tagUMSysGameSet*)GetItemData(nItem))->dwStoragStart;
			szText = GetItemText(nItem,3);
			m_tabStoragStartArray.StoragStart[nCount].dwStorageDeduct = _ttoi(szText);//((tagUMSysGameSet*)GetItemData(nItem))->dwStorageDeduct;
			m_tabStoragStartArray.StoragStart[nCount].bValid = 0;
		}

		nCount++;
	}
		m_tabStoragStartArray.dwCount = nCount;

/*		return sizeof(tabStoragStartArray);*/
}

BOOL CStockList::OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	CellHitTest(pItem->ptAction, nRow, nCol);
	tagQueryGame* QueryGame;
	ZeroMemory(QueryGame,sizeof(QueryGame));

	CString szText;
	if (nRow != -1)
	{
		switch (nCol)
		{
		case 6:
			{
				szText = GetItemText(nRow,5);
				//AfxMessageBox(szText);
				QueryGame->dwServerID = _ttoi(szText);
				QueryGame->dwDay = 2;
				ASSERT(CMissionUserInfo::GetInstance()!=NULL);
				CMissionUserInfo::GetInstance()->OnGetStockUser(QueryGame);
			}
			break;
		case 7:
			{
				szText = GetItemText(nRow,5);
				//AfxMessageBox(szText);

				QueryGame->dwServerID = _ttoi(szText);
				QueryGame->dwDay = 1;
				ASSERT(CMissionUserInfo::GetInstance()!=NULL);
				CMissionUserInfo::GetInstance()->OnGetStockUser(QueryGame);
			}
			break;
		case 8:
			{
				szText = GetItemText(nRow,5);
				//AfxMessageBox(szText);

				QueryGame->dwServerID = _ttoi(szText);
				QueryGame->dwDay = 0;
				ASSERT(CMissionUserInfo::GetInstance()!=NULL);
				CMissionUserInfo::GetInstance()->OnGetStockUser(QueryGame);
			}
			break;
		}
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
/*	CMissionUserInfo::GetInstance()->SetUserVip(m_tabUserVip);*/

	return FALSE;
}

void CStockList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
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