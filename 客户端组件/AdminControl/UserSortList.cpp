#include "StdAfx.h"
#include "UserSortList.h"

CUserSortList::CUserSortList(void)
{
}

CUserSortList::~CUserSortList(void)
{
}


VOID CUserSortList::InitUserInfoList()
{
	//	SetExtendedStyle(GetExtendedStyle()/*|LVS_EX_DOUBLEBUFFER*//*| LVS_EX_FULLROWSELECT*/| LVS_EX_HEADERDRAGDROP| LVS_EX_GRIDLINES| LVS_EX_SUBITEMIMAGES);

	//m_MarkBmp1.LoadBitmap(IDI_ICON8);
	m_ImageSortList.Create(1, 35, ILC_COLOR16 | ILC_MASK, 1, 0);
	SetImageList(&m_ImageSortList, LVSIL_SMALL);
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON9));
	//	SetImageList(m_ImageList, LVSIL_SMALL);

	// 	SetCellMargin(1.2);
	// 	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	// 	SetDefaultRowTrait(pRowTrait);

	InsertHiddenLabelColumn();

	int Col;
	for (Col=0;Col<this->GetColCount();++Col)
	{
		const CString& title = GetColTitle(Col);
		CGridColumnTraitText* pTrait = NULL;

		//	pTrait = new CGridColumnTraitText;
		if (Col == 17)
		{
			pTrait = new CGridColumnTraitDateTime;
		}
		if (Col == 18 || Col == 19 || Col == 20 || Col == 21 || Col == 22)
		{
			pTrait = new CGridColumnTraitEdit;
		}else 
			pTrait = new CGridColumnTraitText;
		if (Col == 1 || Col == 4 || Col == 5 /*|| Col == 21*/ || Col == 21/* || Col == 23 || Col == 24*/)
		{
			ShowColumn(Col,false);
		}

		// 		if (Col == 7)
		// 		{
		// 			pTrait->SetSortFormatNumber(false);
		// 		}
		InsertColumnTrait(Col+1, title, LVCFMT_LEFT, 69, Col, pTrait);

		if (Col != 1 && Col != 2 && Col!=3 /*&& Col!=6*/ && Col!=7 && /*Col!=8 &&*/ Col!=5 && Col!=16 && Col!=15)
		{
			pTrait->SetSortFormatNumber(true);
		}
	}

	SetColumnWidth(1,40);
	//	SetColumnWidth(8,100);
	SetColumnWidth(9,100);
	SetColumnWidth(10,100);
	SetColumnWidth(11,100);
	SetColumnWidth(12,100);
	//	SetColumnWidth(13,100);
	SetColumnWidth(14,100);
	//	SetColumnWidth(15,100);
	SetColumnWidth(16,100);
	SetColumnWidth(17,100);
	SetColumnWidth(18,100);
	SetColumnWidth(19,100);
	SetColumnWidth(20,100);
	SetColumnWidth(22,100);
	SetColumnWidth(23,100);
	SetColumnWidth(24,100);
	SetColumnWidth(25,100);
	SetColumnWidth(28,120);

	const CString& title = GetColTitle(Col);

	//	const CString& title = GetColTitle(Col);
	CGridColumnTrait* pTrait = NULL;
	InsertColumnTrait(Col+1, "预警排序", LVCFMT_LEFT, 40, Col, pTrait);
	ShowColumn(++Col,false);
	InsertColumnTrait(++Col,"备注",LVCFMT_LEFT, 40, Col, pTrait);

	SetCellMargin(1.2);
	SetColumnWidth(31,150);

//	OnOpenFilterFile();

	m_GameInfo.SelectUserInfo();
	m_GameInfo.SeleteHideUser();
}


INT CUserSortList::OnUpDataUserData(DWORD UserID)
{
	int nItem = 0;
	int i = GetItemCount();
	for (nItem;nItem<i;nItem++)
	{
		int n = _ttoi(GetItemText(nItem,4));
		if (UserID == n)
		{
			return nItem;
		}
	}

	return -1;
}


void CUserSortList::OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem)
{
	/*CString strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);*/

	// 	for (int i=0;i<m_FilterUserArray.GetCount();i++)
	// 	{
	// 		if (pGameUserInfoItem->GetdwUserID() == m_FilterUserArray[i].UserID)
	// 		{
	// 			return;
	// 		}
	// 	}
	// 	m_GameInfo.SelectUserInfo();
	// 	m_GameInfo.SeleteHideUser();
	for (int i=0;i<m_GameInfo.m_UserInfo.GetCount();i++)
	{
		if (pGameUserInfoItem->GetdwUserID() == _ttoi(m_GameInfo.m_UserInfo[i]->UserID))
		{
			return;
		}
	}
	for (int p=0;p<m_GameInfo.m_HideUser.GetCount();p++)
	{
		if (pGameUserInfoItem->GetdwUserID() == _ttoi(m_GameInfo.m_HideUser[p]->UserID))
		{
			return;
		}
	}
	if ((pGameUserInfoItem->m_tagUMUserScoreSet.dwIsSet&LC_USER)>1)
	{
		m_IsSet = 1;
	}

	ASSERT(pGameUserInfoItem!=NULL);
	if (pGameUserInfoItem==NULL) return;

// 	if (pGameUserInfoItem->m_tagUMUserScoreSet.dwKindID != m_nPlatKind && m_nPlatKind != 0)
// 	{
// 		return;
// 	}else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwServerID != m_nPlat && m_nPlat != 0)
// 	{
// 		return;
// 	}

	CString szItemText;
	int Col = 1;
	int nItem = OnUpDataUserData(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);

	if (nItem != -1)
	{
		switch(Col)
		{
			// 		case 0:
			// 			{
			// 				SetItemText(nItem,++Col,szItemText);
			// 			}
		case 1://场次
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->szServerName);
				SetItemText(nItem,++Col,szItemText);
				//SetItem(nItem,++Col,LVIF_IMAGE|LVIF_TEXT,szItemText,0,NULL,NULL,0);
			}
		case 2://状态
			{

				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXWIN)
				{
					szItemText.Format(_T("玩家赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXLOSE)
				{
					szItemText.Format(_T("玩家输"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == OPFINISH)
				{
					szItemText.Format(_T("完成"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYWIN)
				{
					szItemText.Format(_T("预警赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYLOSE)
				{
					szItemText.Format(_T("预警输"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXWIN)
				{
					szItemText.Format(_T("自动赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXLOSE)
				{
					szItemText.Format(_T("自动输"));
				}else
					szItemText.Format(_T("默认"));

				SetItemText(nItem,++Col,szItemText);

			}
		case 3://UserID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				SetItemText(nItem,++Col,szItemText);

			}
		case 4://ServerID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwServerID);
				SetItemText(nItem,++Col,szItemText);


			}
		case 5://渠道
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1);
				SetItemText(nItem,++Col,szItemText);
// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 				{
// 					SetItemText(nItem,++Col,"正常");
// 				}else
// 					SetItemText(nItem,++Col,"试玩站");

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 6://GameID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				SetItemText(nItem,++Col,szItemText);


				// 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 7://昵称
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				// 				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lScore);
				// 				SetItemText(iLine,++Col,szItemText);

			}
		case 8://金币
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lScore);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 9://银行
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInsure);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 10://转出
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInsure);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 11://转入
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInScore);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 12://换牌概率
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 13://充值金额
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1);
				SetItemText(nItem,++Col,szItemText);
			}
		case 14://桌号
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 15://最后一次转出
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 16://最后一次转入
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 17://累计输赢金币
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore);
				SetItemText(nItem,++Col,szItemText);

				// 				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				// 				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				// 				//szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				// 				SetItemText(nItem,++Col,strTime);
			}
		case 18://当日输赢金币
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 19://设置后输赢金币
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 20://开始时间
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				//szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				SetItemText(nItem,++Col,strTime);
			}
		case 21://赢最高
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 22://输最高
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 23://预警赢
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 24://预警输
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost);
				SetItemText(nItem,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 25://赢局
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(nItem,++Col,szItemText);

				// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
				// 				{
				// 					SetItemText(nItem,++Col,"正常");
				// 				}else
				// 					SetItemText(nItem,++Col,"试玩站");
			}
		case 26://输局
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(nItem,++Col,szItemText);


				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 27://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(nItem,++Col,szClientAddr);

				// 				SCORE m_Win = pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1;
				// 				SCORE m_WarningWin = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin;
				// 				SCORE m_WarningLose = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost;
				// 				if (m_Win >= m_WarningWin || m_Win <= m_WarningLose)
				// 				{
				// 					SetItemText(iLine,++Col,"1");
				// 				}else
				// 					SetItemText(iLine,++Col,"0");

			}
		case 28://机器ID
			{
				SetItemText(nItem,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

				// 				CString strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				// 				if (strRemarks != "")
				// 				{
				// 					SetItemText(iLine,++Col,strRemarks);
				// 				}
			}
		case 29:
			{
				SCORE m_Win = pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1;
				SCORE m_WarningWin = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin;
				SCORE m_WarningLose = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost;
				if (m_Win >= m_WarningWin || m_Win <= m_WarningLose)
				{
					SetItemText(nItem,++Col,"1");
				}else
					SetItemText(nItem,++Col,"0");
			}
		case 30://备注
			{
// 				CString szText,strRemarks;
// 				// 				szText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 
// 				// 				if ((CUserRemarks::GetInstance()->SelectUser(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID)) == 0)
// 				// 				{
// 				// 					CUserRemarks::GetInstance()->InsertUserRemarksInfo(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID,pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 				}else 
// 				// 				{
// 				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
// 				// 					if (szText != strRemarks)
// 				// 					{
// 				// 						CUserRemarks::GetInstance()->UpdateUserInfo(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID,pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 					}
// 				// 				}
// 
// 				// 				if (strRemarks != "")
// 				// 				{
// 				SetItemText(nItem,++Col,strRemarks);
				//				}
			}
		}
	}
	else
	{
		//m_UserScoreSet = pGameUserInfoItem->m_tagUMUserScoreSet;
		int iLine = GetItemCount();
		CString szItemText;
		szItemText.Format(_T("%d"),iLine+1);
		InsertItem(iLine,szItemText);
		SetItemData(iLine, (DWORD)pGameUserInfoItem);

		int Col = 0;
		switch(Col)
		{
		case 0:
			{
				SetItemText(iLine,++Col,szItemText);
			}
		case 1://场次
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->szServerName);
				SetItemText(iLine,++Col,szItemText);
				//SetItem(nItem,++Col,LVIF_IMAGE|LVIF_TEXT,szItemText,0,NULL,NULL,0);
			}
		case 2://状态
			{

				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXWIN)
				{
					szItemText.Format(_T("玩家赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXLOSE)
				{
					szItemText.Format(_T("玩家输"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == OPFINISH)
				{
					szItemText.Format(_T("完成"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYWIN)
				{
					szItemText.Format(_T("预警赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYLOSE)
				{
					szItemText.Format(_T("预警输"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXWIN)
				{
					szItemText.Format(_T("自动赢"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXLOSE)
				{
					szItemText.Format(_T("自动输"));
				}else
					szItemText.Format(_T("默认"));

				SetItemText(iLine,++Col,szItemText);

			}
		case 3://UserID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				SetItemText(iLine,++Col,szItemText);

			}
		case 4://ServerID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwServerID);
				SetItemText(iLine,++Col,szItemText);


			}
		case 5://渠道
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1);
				SetItemText(iLine,++Col,szItemText);
// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 				{
// 					SetItemText(iLine,++Col,"正常");
// 				}else
// 					SetItemText(iLine,++Col,"试玩站");

			}
		case 6://GameID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				SetItemText(iLine,++Col,szItemText);

			}
		case 7://昵称
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 8://金币
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lScore);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 9://银行
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInsure);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 10://转出
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInsure);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 11://转入
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInScore);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 12://换牌概率
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lInScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 13://充值金额
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin);
				// 				SetItemText(iLine,++Col,szItemText);

			}
		case 14://桌号
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 15://最后一次转出
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 16://最后一次转入
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 17://累计输赢金币
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore);
				SetItemText(iLine,++Col,szItemText);

				// 				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				// 				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				// 				//szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				// 				SetItemText(nItem,++Col,strTime);

			}
		case 18://当日输赢金币
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 19://设置后输赢金币
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 20://开始时间
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				//szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				SetItemText(iLine,++Col,strTime);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 21://赢最高
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 22://输最高
			{
				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 23://预警赢
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 24://预警输
			{

				szItemText.Format(_T("%lld"),pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost);
				SetItemText(iLine,++Col,szItemText);

				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				// 				SetItemText(nItem,++Col,szItemText);

			}
		case 25://赢局
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(iLine,++Col,szItemText);

				// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
				// 				{
				// 					SetItemText(nItem,++Col,"正常");
				// 				}else
				// 					SetItemText(nItem,++Col,"试玩站");
			}
		case 26://输局
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(iLine,++Col,szItemText);


				// 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				// 				SetItemText(nItem,++Col,szItemText);
			}
		case 27://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(iLine,++Col,szClientAddr);

				// 				SCORE m_Win = pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1;
				// 				SCORE m_WarningWin = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin;
				// 				SCORE m_WarningLose = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost;
				// 				if (m_Win >= m_WarningWin || m_Win <= m_WarningLose)
				// 				{
				// 					SetItemText(iLine,++Col,"1");
				// 				}else
				// 					SetItemText(iLine,++Col,"0");

			}
		case 28://机器ID
			{
				SetItemText(iLine,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

				// 				CString strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				// 				if (strRemarks != "")
				// 				{
				// 					SetItemText(iLine,++Col,strRemarks);
				// 				}
			}
		case 29:
			{
				SCORE m_Win = pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1;
				SCORE m_WarningWin = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin;
				SCORE m_WarningLose = pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost;
				if (m_Win >= m_WarningWin || m_Win <= m_WarningLose)
				{
					SetItemText(iLine,++Col,"1");
				}else
					SetItemText(iLine,++Col,"0");
			}
		case 30://备注
			{
// 				CString szText,strRemarks;
// 				// 				szText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 
// 				// 				if ((CUserRemarks::GetInstance()->SelectUser(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID)) == 0)
// 				// 				{
// 				// 					CUserRemarks::GetInstance()->InsertUserRemarksInfo(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID,pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 				}else 
// 				// 				{
// 				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
// 				// 					if (szText != strRemarks)
// 				// 					{
// 				// 						CUserRemarks::GetInstance()->UpdateUserInfo(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID,pGameUserInfoItem->m_tagUMUserScoreSet.szRemarks);
// 				// 					}
// 				// 				}
// 
// 				// 				if (strRemarks != "")
// 				// 				{
// 				SetItemText(iLine,++Col,strRemarks);
// 				//				}
			}
		}
	}

	return;
}