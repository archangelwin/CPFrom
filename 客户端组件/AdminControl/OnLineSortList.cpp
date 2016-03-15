#include "StdAfx.h"
#include "UserInfoList.h"
#include "atltime.h"
#include "MissionUserInfo.h"
#include "UserRemarks.h"
#include "UserRemarksInfo.h"
#include "DlgHideUser.h"
#include "DlgUserInfo.h"
#include "OnLineSortList.h"

COnLineSortList::COnLineSortList(void)
{
	m_IsSysFault = false;
	m_nPlat = 0;
	m_nPlatKind = 0;
	m_settype = MAXDEFAULT;
	m_IsSort = false;
	m_ImageList = new CImageList;

	m_IsFirstList = false;
}

COnLineSortList::~COnLineSortList(void)
{
}


BEGIN_MESSAGE_MAP(COnLineSortList, CGridListCtrlGroups)
	//{{AFX_MSG_MAP(CGridListCtrlEx)
	//	ON_MESSAGE(WM_BN_CLICK, OnButtonClick)
	ON_COMMAND(ID_SET_USER_VIP, OnClSetUserVIP)
	ON_COMMAND(ID_DLVIP,OnClDelUserVIP)
	ON_COMMAND(ID_SET_USERWIN, OnSetUserWin)
	ON_COMMAND(ID_SET_USERLOSE, OnSetUserLose)
	ON_COMMAND(ID_SET_USERWIN1, OnSetUserWin1)
	ON_COMMAND(ID_SET_USERLOSE1, OnSetUserLose2)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRClick)

	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnItemDblClick)

	ON_WM_RBUTTONDOWN()
	//	ON_WM_LBUTTONDOWN()

	//	ON_WM_MEASUREITEM_REFLECT()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_SETVIP, &COnLineSortList::OnSetvip)
	ON_COMMAND(ID_DEVIP, &COnLineSortList::OnDevip)
	ON_COMMAND(ID_SET, &COnLineSortList::OnUserSet)
	ON_COMMAND(ID_SET_1, &COnLineSortList::OnUserSet1)
	ON_COMMAND(ID_SET_2, &COnLineSortList::OnUserSet2)
	ON_COMMAND(ID_SET_3, &COnLineSortList::OnUserSet3)
	ON_COMMAND(ID_SET_DEFAULT, &COnLineSortList::OnSetDefault)
	ON_COMMAND(ID_SET_DEFAULT1, &COnLineSortList::OnSetDefault1)
	ON_COMMAND(ID_SET_DEFAULT2, &COnLineSortList::OnSetDefault2)
	ON_COMMAND(ID_SET_DEFAULT3, &COnLineSortList::OnSetDefault3)

	ON_COMMAND(ID_TH10, &COnLineSortList::OnTh10)
	ON_COMMAND(ID_TH20, &COnLineSortList::OnTh20)
	ON_COMMAND(ID_TH30, &COnLineSortList::OnTh30)
	ON_COMMAND(ID_TH40, &COnLineSortList::OnTh40)
	ON_COMMAND(ID_TH50, &COnLineSortList::OnTh50)
	ON_COMMAND(ID_TH60, &COnLineSortList::OnTh60)
	ON_COMMAND(ID_TH70, &COnLineSortList::OnTh70)
	ON_COMMAND(ID_TH80, &COnLineSortList::OnTh80)
	ON_COMMAND(ID_TH90, &COnLineSortList::OnTh90)
	ON_COMMAND(ID_TH100, &COnLineSortList::OnTh100)

	ON_COMMAND(ID_LTH10, &COnLineSortList::OnLth10)
	ON_COMMAND(ID_LTH20, &COnLineSortList::OnLth20)
	ON_COMMAND(ID_LTH30, &COnLineSortList::OnLth30)
	ON_COMMAND(ID_LTH40, &COnLineSortList::OnLth40)
	ON_COMMAND(ID_LTH50, &COnLineSortList::OnLth50)
	ON_COMMAND(ID_LTH60, &COnLineSortList::OnLth60)
	ON_COMMAND(ID_LTH70, &COnLineSortList::OnLth70)
	ON_COMMAND(ID_LTH80, &COnLineSortList::OnLth80)
	ON_COMMAND(ID_LTH90, &COnLineSortList::OnLth90)
	ON_COMMAND(ID_LTH100, &COnLineSortList::OnLth100)

	ON_COMMAND(ID_THW10, &COnLineSortList::OnThw10)
	ON_COMMAND(ID_THW20, &COnLineSortList::OnThw20)
	ON_COMMAND(ID_THW30, &COnLineSortList::OnThw30)
	ON_COMMAND(ID_THW40, &COnLineSortList::OnThw40)
	ON_COMMAND(ID_THW50, &COnLineSortList::OnThw50)
	ON_COMMAND(ID_THW60, &COnLineSortList::OnThw60)
	ON_COMMAND(ID_THW70, &COnLineSortList::OnThw70)
	ON_COMMAND(ID_THW80, &COnLineSortList::OnThw80)
	ON_COMMAND(ID_THW90, &COnLineSortList::OnThw90)
	ON_COMMAND(ID_THW100, &COnLineSortList::OnThw100)

	ON_COMMAND(ID_LTHA10, &COnLineSortList::OnLtha10)
	ON_COMMAND(ID_LTHA20, &COnLineSortList::OnLtha20)
	ON_COMMAND(ID_LTHA30, &COnLineSortList::OnLtha30)
	ON_COMMAND(ID_LTHA40, &COnLineSortList::OnLtha40)
	ON_COMMAND(ID_LTHA50, &COnLineSortList::OnLtha50)
	ON_COMMAND(ID_LTHA60, &COnLineSortList::OnLtha60)
	ON_COMMAND(ID_LTHA70, &COnLineSortList::OnLtha70)
	ON_COMMAND(ID_LTHA80, &COnLineSortList::OnLtha80)
	ON_COMMAND(ID_LTHA90, &COnLineSortList::OnLtha90)
	ON_COMMAND(ID_LTHA100, &COnLineSortList::OnLtha100)
	ON_COMMAND(ID_SET_SELF, &COnLineSortList::OnSetSelf)
	ON_COMMAND(ID_SET_500W, &COnLineSortList::OnSet500w)
	ON_COMMAND(ID_SET_1000W, &COnLineSortList::OnSet1000w)
	ON_COMMAND(ID_SET_2000W, &COnLineSortList::OnSet2000w)
	ON_COMMAND(ID_SET_5000W, &COnLineSortList::OnSet5000w)
	ON_COMMAND(ID_SET_1E, &COnLineSortList::OnSet1e)
	ON_COMMAND(ID_SET_2E, &COnLineSortList::OnSet2e)
	ON_COMMAND(ID_SET_5E, &COnLineSortList::OnSet5e)
	ON_COMMAND(ID_SET_8000W, &COnLineSortList::OnSet8000w)
	ON_COMMAND(ID_VIP_32911, &COnLineSortList::OnSetUserRemarks)
	ON_COMMAND(ID_MARK1, &COnLineSortList::OnMark1)
	//	ON_NOTIFY(NM_CLICK, IDC_GAME_USER_LIST, &COnLineSortList::OnNMClickGameUserList)
	ON_COMMAND(ID_USER_HIDE, &COnLineSortList::OnUserHide)
	ON_COMMAND(ID_CHECK_HIDE_USER, &COnLineSortList::OnCheckHideUser)
END_MESSAGE_MAP()

BOOL COnLineSortList::OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	CellHitTest(pItem->ptAction, nRow, nCol);

	if (nRow != -1)
	{
		m_nItem = nRow;
		tagUMUserScoreSet lUserScoreSet = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet;
		m_UserScoreSet = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet;

		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;
		CDlgUserInfo UserInfoDlg;
		UserInfoDlg.m_tagUserInfo = lUserScoreSet;

		if (UserInfoDlg.DoModal() == IDOK)
		{
			//return FALSE;
			CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;

			if (UserInfoDlg.m_AllowSet == 1)
			{
				if (_ttoi64(WinLoseScore)>_ttoi(WinMax) || _ttoi64(WinLoseScore)<_ttoi64(LoseMax))
				{
					AfxMessageBox("������Ӯ�������ܸ���Ӯ���,���ߵ�������ߣ�");
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

	return FALSE;	// Let parent-dialog get chance
}

VOID COnLineSortList::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}

VOID COnLineSortList::InitUserInfoList()
{
	//	SetExtendedStyle(GetExtendedStyle()/*|LVS_EX_DOUBLEBUFFER*//*| LVS_EX_FULLROWSELECT*/| LVS_EX_HEADERDRAGDROP| LVS_EX_GRIDLINES| LVS_EX_SUBITEMIMAGES);

	//m_MarkBmp1.LoadBitmap(IDI_ICON8);
	m_ImageList->Create(1, 35, /*ILC_COLOR16 | */ILC_MASK, 10, 4);
	// 	SetImageList(m_ImageList, LVSIL_SMALL);
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	// 	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));
	// 	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON9));
	SetImageList(m_ImageList, LVSIL_SMALL);

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
		if (Col == 12 || Col == 22 || Col == 23 || Col == 24 || Col == 25)
		{
			pTrait = new CGridColumnTraitEdit;
		}else 
			pTrait = new CGridColumnTraitText;
		if (Col == 1 || Col == 4 || Col == 5 /*|| Col == 21*/ || Col == 22 ||
			/*Col == 3 ||*/ Col == 6  || Col == 9 || Col == 10 ||
			Col == 11 || Col == 12 /*|| Col == 13*/ ||Col == 14 || Col == 15 ||
			Col == 16 || Col == 17 || Col == 18 || Col == 19 ||
			/*Col == 21 ||*/ Col == 22 || Col ==23 || Col == 24 || Col == 25 || 
			Col == 26 || Col == 27 || Col ==28 || Col == 29 || Col == 30)
		{
			ShowColumn(Col,false);
		}

		InsertColumnTrait(Col+1, title, LVCFMT_LEFT, 69, Col, pTrait);

		if (Col != 1 && Col != 2 && Col!=3 /*&& Col!=6*/ && Col!=7 && /*Col!=8 &&*/ Col!=5 && Col!=18 && Col!=17)
		{
			pTrait->SetSortFormatNumber(true);
		}
	}

	SetColumnWidth(1,40);
	SetColumnWidth(9,100);
	SetColumnWidth(10,100);
	SetColumnWidth(11,100);
	SetColumnWidth(12,100);
	SetColumnWidth(14,100);
	SetColumnWidth(17,100);
	SetColumnWidth(18,100);
	SetColumnWidth(19,100);
	SetColumnWidth(20,100);
	SetColumnWidth(21,100);
	SetColumnWidth(23,100);
	SetColumnWidth(24,100);
	SetColumnWidth(25,100);
	SetColumnWidth(26,100);
	SetColumnWidth(29,120);

	const CString& title = GetColTitle(Col);

	CGridColumnTrait* pTrait = NULL;
	ShowColumn(Col,false);
	InsertColumnTrait(Col+1, "Ԥ������", LVCFMT_LEFT, 40, Col, pTrait);
	ShowColumn(++Col,false);
	InsertColumnTrait(++Col,"��ע",LVCFMT_LEFT, 40, Col, pTrait);
	ShowColumn(Col,false);

	SetCellMargin(1.2);
	SetColumnWidth(32,150);

	OnOpenFilterFile();

	m_GameInfo.SelectUserInfo();
	m_GameInfo.SeleteHideUser();

}


void COnLineSortList::OnGameUserInfoFinish()
{
}

void COnLineSortList::OnGameUserInfoUpdateFinish()
{
}

void COnLineSortList::OnSetServerID(DWORD ServerID)
{
	m_nPlat = ServerID;
}
VOID COnLineSortList::OnSetKindID(DWORD KindID)
{
	m_nPlatKind = KindID;
}
void COnLineSortList::OnRedraw(BOOL nRedraw)
{
	SetRedraw(nRedraw);
}

VOID COnLineSortList::OnSetUserRemarks(DWORD UserID,CString Remarks)
{
	DWORD userID = 0;
	int nListCount = GetItemCount();
	for (int i=0;i<nListCount;i++)
	{
		userID = _ttoi(GetItemText(i,4));
		if (userID == UserID)
		{
			SetItemText(i,35,Remarks);
		}
	}
}

VOID COnLineSortList::OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type)
{
	DWORD userID = 0;
	int nListCount = GetItemCount();
	TCHAR szControl[128]=TEXT("");
	CString szItemText;

	m_UserScoreSet.dwWinOrLostRate = _ttoi(lRate);
	m_UserScoreSet.lSetWinOrLose = _ttoi(WinLoseScore);
	m_UserScoreSet.lMaxWin = _ttoi(WinMax);
	m_UserScoreSet.lMaxLose = _ttoi(LoseMax);
	m_UserScoreSet.lNotifyMaxWin = _ttoi(NotifyWin);
	m_UserScoreSet.lNotifyMaxLost = _ttoi(NotifyLose);

	if (m_UserScoreSet.lMaxLose > 0 || m_UserScoreSet.lNotifyMaxLost > 0)
	{
		AfxMessageBox("����߻���Ԥ�������С���㣡");

		return;
	}
	if (m_UserScoreSet.lMaxWin < 0 || m_UserScoreSet.lNotifyMaxWin < 0)
	{
		AfxMessageBox("Ӯ��߻���Ԥ��Ӯ��������㣡");

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

CString COnLineSortList::GetModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 

	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath.Left( nPos ); 
}

void COnLineSortList::OnOpenFilterFile()
{
	CStdioFile file;
	CString filePathName;
	int row;
	CString result;

	filePathName = GetModuleDir();
	CString filename = "/AccountsInfo.txt";
	filePathName += filename;

	if(filePathName == "")  return;
	if(!file.Open(filePathName,CFile::modeRead))
	{
		return;
	}

	CString strLine,strTemp,sMid;
	row = 0;
	CString          FilterUserID;

	while(file.ReadString(strLine))
	{
		int iLen = strLine.GetLength();
		int iSpaceIndex = strLine.Find(",");
		FilterUserID = strLine.Left(iSpaceIndex);
		strTemp = strLine.Right(iLen - iSpaceIndex - 1);

		m_FilterUserID = _ttoi(FilterUserID);
		m_tagFilterUser.UserID = m_FilterUserID;
		m_FilterUserArray.Add(m_tagFilterUser);

		row++;
	}
}

void COnLineSortList::OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem)
{

	// 	if (pGameUserInfoItem->m_tagUMUserScoreSet.nVipType == 3 && m_IsFirstList == true)
	// 	{
	// 		return;
	// 	}
	for (int i=0;i<m_GameInfo.m_UserInfo.GetCount();i++)
	{
		if (pGameUserInfoItem->GetdwUserID() == _ttoi(m_GameInfo.m_UserInfo[i]->UserID))
		{
			return;
		}
	}
	// 	for (int p=0;p<m_GameInfo.m_HideUser.GetCount();p++)
	// 	{
	// 		if (pGameUserInfoItem->GetdwUserID() == _ttoi(m_GameInfo.m_HideUser[p]->UserID))
	// 		{
	// 			return;
	// 		}
	// 	}
	if ((pGameUserInfoItem->m_tagUMUserScoreSet.dwIsSet&LC_USER)>1)
	{
		m_IsSet = 1;
	}

	ASSERT(pGameUserInfoItem!=NULL);
	if (pGameUserInfoItem==NULL) return;

	if (pGameUserInfoItem->m_tagUMUserScoreSet.dwKindID != m_nPlatKind && m_nPlatKind != 0)
	{
		return;
	}else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwServerID != m_nPlat && m_nPlat != 0)
	{
		return;
	}

	CString szItemText;
	TCHAR szControl[128]=TEXT("");
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
		case 1://����
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->szServerName);
				SetItemText(nItem,++Col,szItemText);
			}
		case 2://״̬
			{

				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXWIN)
				{
					szItemText.Format(_T("���Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXLOSE)
				{
					szItemText.Format(_T("�����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == OPFINISH)
				{
					szItemText.Format(_T("���"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYWIN)
				{
					szItemText.Format(_T("Ԥ��Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYLOSE)
				{
					szItemText.Format(_T("Ԥ����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXWIN)
				{
					szItemText.Format(_T("�Զ�Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXLOSE)
				{
					szItemText.Format(_T("�Զ���"));
				}else
					szItemText.Format(_T("Ĭ��"));

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
		case 5://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1);
				SetItemText(nItem,++Col,szItemText);
// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 				{
// 					SetItemText(nItem,++Col,"����");
// 				}else
// 					SetItemText(nItem,++Col,"����վ");

			}
		case 6://GameID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				SetItemText(nItem,++Col,szItemText);
			}
		case 7://�ǳ�
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				SetItemText(nItem,++Col,szItemText);

			}
		case 8://���
			{

				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 9://����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInsure,3L,szControl,CountArray(szControl));
				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 10://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore,3L,szControl,CountArray(szControl));
				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 11://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 12://���Ƹ���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(nItem,++Col,szItemText);

			}
		case 13://��ֵ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 14://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(nItem,++Col,szItemText);

			}
		case 15:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 16://���һ��ת��
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(nItem,++Col,szItemText);

			}
		case 17://���һ��ת��
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(nItem,++Col,szItemText);

			}
		case 18://�ۼ���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 19://������Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 20://���ú���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);


			}
		case 21://��ʼʱ��
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				SetItemText(nItem,++Col,strTime);
			}
		case 22://Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 23://�����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 24://Ԥ��Ӯ
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 25://Ԥ����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 26://Ӯ��
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(nItem,++Col,szItemText);

			}
		case 27://���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(nItem,++Col,szItemText);

			}
		case 28://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(nItem,++Col,szClientAddr);

			}
		case 29://����ID
			{
				SetItemText(nItem,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

			}
		case 30:
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
		case 31://��ע
			{
				CString szText,strRemarks;
				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);

				SetItemText(nItem,++Col,strRemarks);
			}
		}

	}
	else
	{
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
		case 1://����
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->szServerName);
				SetItemText(iLine,++Col,szItemText);
			}
		case 2://״̬
			{

				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXWIN)
				{
					szItemText.Format(_T("���Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXLOSE)
				{
					szItemText.Format(_T("�����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == OPFINISH)
				{
					szItemText.Format(_T("���"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYWIN)
				{
					szItemText.Format(_T("Ԥ��Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYLOSE)
				{
					szItemText.Format(_T("Ԥ����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXWIN)
				{
					szItemText.Format(_T("�Զ�Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXLOSE)
				{
					szItemText.Format(_T("�Զ���"));
				}else
					szItemText.Format(_T("Ĭ��"));

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
		case 5://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1);
				SetItemText(iLine,++Col,szItemText);
// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 				{
// 					SetItemText(iLine,++Col,"����");
// 				}else
// 					SetItemText(iLine,++Col,"����վ");

			}
		case 6://GameID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				SetItemText(iLine,++Col,szItemText);

			}
		case 7://�ǳ�
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				SetItemText(iLine,++Col,szItemText);

			}
		case 8://���
			{

				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 9://����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInsure,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 10://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 11://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);


			}
		case 12://���Ƹ���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(iLine,++Col,szItemText);

			}
		case 13://��ֵ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);


			}
		case 14://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(iLine,++Col,szItemText);

			}
		case 15:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);
			}
		case 16://���һ��ת��
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(iLine,++Col,szItemText);

			}
		case 17://���һ��ת��
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(iLine,++Col,szItemText);

			}
		case 18://�ۼ���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);


			}
		case 19://������Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 20://���ú���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 21://��ʼʱ��
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				SetItemText(iLine,++Col,strTime);

			}
		case 22://Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 23://�����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 24://Ԥ��Ӯ
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 25://Ԥ����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 26://Ӯ��
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(iLine,++Col,szItemText);

			}
		case 27://���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(iLine,++Col,szItemText);


			}
		case 28://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(iLine,++Col,szClientAddr);

			}
		case 29://����ID
			{
				SetItemText(iLine,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

			}
		case 30:
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
		case 31://��ע
			{
				CString szText,strRemarks;
				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				SetItemText(iLine,++Col,strRemarks);
			}
		}
	}

	return;
}

int COnLineSortList::OnGetUserCount()
{
	int n = GetItemCount();
	int nIndex = 0;
	for (int i=0;i<n;i++)
	{
		CString strChannel = GetItemText(i,6);
		if (strChannel == "����")
		{
			nIndex++;
		}
	}

	return nIndex;
}

DWORD COnLineSortList::OnGetUserRecharge()
{
	int n = GetItemCount();
	DWORD AllRecharge = 0;
	for (int i = 0;i<n;i++)
	{
		DWORD k = ((CUserInfoItem * )GetItemData(i))->m_tagUMUserScoreSet.lMaxLose1;
		AllRecharge += k;
	}

	return AllRecharge;
}

VOID COnLineSortList::OnDelAllUserData()
{
	DeleteAllItems();
}

INT COnLineSortList::OnUpDataUserData(DWORD UserID)
{
	int nItem = 0;
	int i = GetItemCount();
	for (nItem;nItem<i;nItem++)
	{
		DWORD n = _ttoi(GetItemText(nItem,4));
		if (UserID == n)
		{
			return nItem;
		}
	}

	return -1;
}

//�û���Ϣ����
void COnLineSortList::OnGameUserInfoUpdate(CUserInfoItem * pGameUserInfoItem)
{

	CString szItemText;
	TCHAR szControl[128]=TEXT("");
	int Col = 1;
	int nItem = OnUpDataUserData(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
	if (nItem != -1)
	{
		switch(Col)
		{
		case 1://����
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->szServerName);
				SetItemText(nItem,++Col,szItemText);
			}
		case 2://״̬
			{

				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXWIN)
				{
					szItemText.Format(_T("���Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXLOSE)
				{
					szItemText.Format(_T("�����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == OPFINISH)
				{
					szItemText.Format(_T("���"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYWIN)
				{
					szItemText.Format(_T("Ԥ��Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == MAXNOTIFYLOSE)
				{
					szItemText.Format(_T("Ԥ����"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXWIN)
				{
					szItemText.Format(_T("�Զ�Ӯ"));
				}
				else if (pGameUserInfoItem->m_tagUMUserScoreSet.dwType == SYSMAXLOSE)
				{
					szItemText.Format(_T("�Զ���"));
				}else
					szItemText.Format(_T("Ĭ��"));

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
		case 5://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1);
				SetItemText(nItem,++Col,szItemText);

// 				if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 				{
// 					SetItemText(nItem,++Col,"����");
// 				}else
// 					SetItemText(nItem,++Col,"����վ");

			}
		case 6://GameID
			{

				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwGameID);
				SetItemText(nItem,++Col,szItemText);

			}
		case 7://�ǳ�
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szNickName);
				SetItemText(nItem,++Col,szItemText);

			}
		case 8://���
			{

				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 9://����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInsure,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 10://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lOutScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 11://ת��
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lInScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 12://���Ƹ���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(nItem,++Col,szItemText);

			}
		case 13://��ֵ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 14://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(nItem,++Col,szItemText);

			}
		case 15:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 16://���һ��ת��
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(nItem,++Col,szItemText);

			}
		case 17://���һ��ת��
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(nItem,++Col,szItemText);

			}
		case 18://�ۼ���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 19://������Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 20://���ú���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 21://��ʼʱ��
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				SetItemText(nItem,++Col,strTime);

			}
		case 22://Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 23://�����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 24://Ԥ��Ӯ
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 25://Ԥ����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);

			}
		case 26://Ӯ��
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(nItem,++Col,szItemText);

			}
		case 27://���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(nItem,++Col,szItemText);

			}
		case 28://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(nItem,++Col,szClientAddr);

			}
		case 29://����ID
			{
				SetItemText(nItem,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

			}
		case 30:
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
		case 31://��ע
			{
				CString szText,strRemarks;
				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				SetItemText(nItem,++Col,strRemarks);
			}
		}
	}
	else
	{
		OnGameUserInfoInsert(pGameUserInfoItem);	

	}
} 

//ɾ���û���Ϣ
void COnLineSortList::OnGameUserInfoDelete(CUserInfoItem * pGameUserInfoItem)
{
	if (GetItemCount()==0)
	{
		return;
	}
	CString m_szText;
	m_szText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
	int Col = 4;
	int nItem;
	for (nItem=0;nItem<GetItemCount();++nItem)
	{
		DWORD n = ((CUserInfoItem * )GetItemData(nItem))->m_tagUMUserScoreSet.dwUserID;
		if (n == pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID)
		{
			DeleteItem(nItem);
		}

	}
	return;
}

SCORE COnLineSortList::GetUserControlScore(CString pScore)
{
	//��������
	WORD wIndex=0;
	SCORE lScore=0L;

	//��ȡ��ֵ
	TCHAR szBuffer[32]=TEXT("");
	lstrcpyn(szBuffer,pScore,sizeof(szBuffer));

	//������ֵ
	while (szBuffer[wIndex]!=0)
	{
		//��������
		WORD wCurrentIndex=wIndex++;

		//������ֵ
		if ((szBuffer[wCurrentIndex]>=TEXT('0'))&&(szBuffer[wCurrentIndex]<=TEXT('9')))
		{
			lScore=lScore*10L+(szBuffer[wCurrentIndex]-TEXT('0'));
		}
	}

	return lScore; 
}

VOID COnLineSortList::OnGetUserListInfo()
{
	int m_nSubItem = 1;

	m_UserScoreSet = ((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet;

}

void COnLineSortList::OnUserSort()
{
	CString szIndex;
	int k = 1;
	for (int i=0;i<=GetItemCount();++i)
	{
		szIndex.Format(_T("%d"),k++);
		SetItemText(i,1,szIndex);
	}
}

// LRESULT COnLineSortList::OnButtonClick( WPARAM wParam, LPARAM lParam )
// {
// 	int nItem = (int)wParam; //��
// 	int nSubItem = (int)lParam; //��
// 
// #ifdef USE_TOPINDEX_BUTTON
// 	int iTopIndex = GetTopIndex();
// 	nItem = iTopIndex + nItem;
// #endif
// 	int m_nSubItem = 1;
// 	switch (nSubItem)
// 	{
// 	case 18:
// 		{
// 			m_GameUserInfo.m_Event = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_RoomID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_User = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_NickName = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_UserGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_BankGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameLose = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinLoseGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_StartTimer = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_LoseHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_ChangeCardPro = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningLose = GetItemText(nItem,++m_nSubItem);
// 
// 			m_settype = MAXDEFAULT;
// 
// 			m_IsSysFault = true;
// 
// 			ASSERT(CMissionUserInfo::GetInstance()!=NULL);
// 			CMissionUserInfo::GetInstance()->SetUserInfo();
// 
// 			
// 			return 1;
// 		}
// 	case 19:
// 		{
// 			m_GameUserInfo.m_Event = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_RoomID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_User = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_NickName = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_UserGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_BankGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameLose = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinLoseGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_StartTimer = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_LoseHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_ChangeCardPro = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningLose = GetItemText(nItem,++m_nSubItem);
// 			
// 			m_settype = MAXLOSE;
// 
// 			m_IsSysFault = false;
// 
// 			DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
// 			if (CardPro > 100 || CardPro < 0)
// 			{
// 				AfxMessageBox("���Ƹ������ô���");
// 			}
// 
// 			ASSERT(CMissionUserInfo::GetInstance()!=NULL);
// 			CMissionUserInfo::GetInstance()->SetUserInfo();
// 
// 			return 1;
// 		}
// 	case 20:
// 		{
// 			m_GameUserInfo.m_Event = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_RoomID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameID = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_User = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_NickName = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_UserGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_BankGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_GameLose = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinLoseGold = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_StartTimer = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WinHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_LoseHighest = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_ChangeCardPro = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningWin = GetItemText(nItem,++m_nSubItem);
// 			m_GameUserInfo.m_WarningLose = GetItemText(nItem,++m_nSubItem);
// 
// 			m_settype = MAXWIN;
// 
// 			m_IsSysFault = false;
// 
// 			DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
// 			if (CardPro > 100 || CardPro < 0)
// 			{
// 				AfxMessageBox("���Ƹ������ô���");
// 			}
// 
// 			ASSERT(CMissionUserInfo::GetInstance()!=NULL);
// 			CMissionUserInfo::GetInstance()->SetUserInfo();
// 
// 			return 1;
// 		}
// 	}
// 
// 	return 0;
// }


//����VIP
void COnLineSortList::OnClSetUserVIP()
{
	m_tabUserVip.dwUserID = ((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.dwUserID;
	m_tabUserVip.nType = 1;
	((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 1;


	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserVip(m_tabUserVip);

}
//ɾ��VIP
void COnLineSortList::OnClDelUserVIP()
{
	// 	if (((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType == 3)
	// 	{
	// 		int nItem;
	// 		for (nItem=0;nItem<GetItemCount();++nItem)
	// 		{
	// 			DWORD n = ((CUserInfoItem * )GetItemData(nItem))->m_tagUMUserScoreSet.dwUserID;
	// 			if (n == m_UserScoreSet.dwUserID)
	// 			{
	// 				DeleteItem(nItem);
	// 			}
	// 		}
	// 	}
	//		tabUserVip* ptabUserVip = new tabUserVip;

	m_tabUserVip.dwUserID = ((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.dwUserID;
	m_tabUserVip.nType = 0;
	((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 0;

	// 		if (((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType == 3)
	// 		{
	int nItem;
	for (nItem=0;nItem<GetItemCount();++nItem)
	{
		DWORD n = ((CUserInfoItem * )GetItemData(nItem))->m_tagUMUserScoreSet.dwUserID;
		if (n == m_UserScoreSet.dwUserID)
		{
			DeleteItem(nItem);
		}
	}
	//		}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetDLUserVip(m_tabUserVip);

}

//�������Ӯ
void COnLineSortList::OnSetUserWin()
{
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();

}
//���������
void COnLineSortList::OnSetUserLose()
{
	OnGetUserListInfo();


	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}
//�������Ӯ
void COnLineSortList::OnSetUserWin1()
{
	OnSetUserWin();
}
//���������
void COnLineSortList::OnSetUserLose2()
{
	OnSetUserLose();
}
//Ԥ������
VOID COnLineSortList::OnWarningSort()
{
	SetRedraw(FALSE);
	SortColumn(31,false);
	//	OnUserSort();
	//	m_IsSort = true;
	SetRedraw(TRUE);
}

void COnLineSortList::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetFocus() != this )
		SetFocus();	// Force focus to finish editing

	// Find out what subitem was clicked
	// 	CellHitTest(point, nRow, nCol);
	// // 
	// // 	// If not right-clicking on an actual row, then don't update focus cell
	//  	if (nRow!=-1)
	//  	{
	//  		m_nItem = nRow;
	// // 		// Update the focused cell before calling CListCtrl::OnRButtonDown()
	// // 		// as it might cause a row-repaint
	//   		CUserInfoItem * pGameUserInfoItem = (CUserInfoItem * )GetItemData(nRow);
	//  		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;
	//  	}

	CListCtrl::OnRButtonDown(nFlags, point);
}

// void COnLineSortList::OnLButtonDown(UINT nFlags, CPoint point)
// {
// 	if( GetFocus() != this )
// 		SetFocus();	// Force focus to finish editing
// 
// 	// Find out what subitem was clicked
// 	CellHitTest(point, nRow, nCol);
// 	// 
// 	// 	// If not right-clicking on an actual row, then don't update focus cell
// 	if (nRow!=-1)
// 	{
// 		
// 	}
// 
// 	CListCtrl::OnRButtonDown(nFlags, point);
// }

//�Ҽ��б�
VOID COnLineSortList::OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	//return;
	if( GetFocus() != this )
		SetFocus();	// Force focus to finish editing
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;
	// Find out what subitem was clicked
	// 	CPoint point;
	// 	::GetCursorPos(&point);
	// 	int nRow, nCol;
	// 	CellHitTest(point, nRow, nCol);

	// If not right-clicking on an actual row, then don't update focus cell
	if (nRow!=-1)
	{
		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;
		m_nItem = nRow;
		CString nrow;
		nrow.Format("%d",nRow);
		//	AfxMessageBox(nrow);
		m_UserScoreSet = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet;
		if (m_UserScoreSet.wOnline == 0)
		{
			return;
		}
		if (((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.nVipType == 1)
		{
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU3);
			if (((((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwIsSet)&LC_USER) > 0)
			{
				pPopup = menu.GetSubMenu(0); 
			}else
				pPopup = menu.GetSubMenu(1);

			CPoint myPoint;  
			ScreenToClient(&myPoint);  
			GetCursorPos(&myPoint); //���λ�� 
			//ClientToScreen(&myPoint);
			pPopup->SetMenuItemBitmaps(ID_MARK1,MF_BYPOSITION,&m_MarkBmp1,&m_MarkBmp1); 
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);

		}
		else if(((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.nVipType == 0){
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU2);  
			if (((((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwIsSet)&LC_USER) > 0)
			{
				pPopup = menu.GetSubMenu(0); 
			}else
				pPopup = menu.GetSubMenu(1);

			CPoint myPoint;  
			ScreenToClient(&myPoint);  
			GetCursorPos(&myPoint); //���λ�� 
			//ScreenToClient(&myPoint);
			pPopup->SetMenuItemBitmaps(ID_MARK1,MF_BYCOMMAND,&m_MarkBmp1,&m_MarkBmp1);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);

		}
		else if (((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.nVipType == 3)
		{
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU3);
			if (((((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwIsSet)&LC_USER) > 0)
			{
				pPopup = menu.GetSubMenu(2); 
			}else
				pPopup = menu.GetSubMenu(3);

			CPoint myPoint;  
			ScreenToClient(&myPoint);  
			GetCursorPos(&myPoint); //���λ�� 
			//ClientToScreen(&myPoint);
			pPopup->SetMenuItemBitmaps(ID_MARK1,MF_BYPOSITION,&m_MarkBmp1,&m_MarkBmp1); 
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);
		}
	}
}

void COnLineSortList::OnSetvip()
{
	// TODO: �ڴ���������������
	OnClSetUserVIP();
}

void COnLineSortList::OnDevip()
{
	// TODO: �ڴ���������������
	OnClDelUserVIP();
}

void COnLineSortList::OnUserSet()
{
	// TODO: �ڴ���������������

	OnGetUserListInfo();

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();

}

void COnLineSortList::OnUserSet1()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void COnLineSortList::OnUserSet2()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void COnLineSortList::OnUserSet3()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void COnLineSortList::OnSetDefault()
{
	// TODO: �ڴ���������������
	int m_nSubItem = 1;

	m_GameUserInfo.m_Event = GetItemText(m_nItem,++m_nSubItem);
	m_GameUserInfo.m_WinOrLose = GetItemText(m_nItem,++m_nSubItem);
	m_GameUserInfo.m_User = GetItemText(m_nItem,++m_nSubItem);


	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->OnSetDeFault();

}

void COnLineSortList::OnSetDefault1()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void COnLineSortList::OnSetDefault2()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void COnLineSortList::OnSetDefault3()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void COnLineSortList::OnTh10()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 10;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 10;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh20()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 20;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 20;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh30()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 30;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 30;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh40()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 40;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 40;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh50()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 50;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 50;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh60()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();
	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 60;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 60;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh70()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();
	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 70;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 70;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh80()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 80;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 80;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh90()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 90;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 90;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnTh100()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXWIN;

	m_IsSysFault = false;

	DWORD CardPro = 100;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 100;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxWin;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����ΪӮ��");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth10()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 10;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 10;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth20()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 20;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 20;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth30()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 30;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 30;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth40()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 40;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 40;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth50()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 50;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 50;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth60()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 60;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 60;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth70()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 70;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 70;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth80()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 80;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 80;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth90()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 90;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 90;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnLth100()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_settype = MAXLOSE;

	m_IsSysFault = false;

	DWORD CardPro = 100;//_ttoi(m_GameUserInfo.m_ChangeCardPro);
	m_UserScoreSet.dwWinOrLostRate = 100;
	m_UserScoreSet.lSetWinOrLose = m_UserScoreSet.lMaxLose;
	if (CardPro == 0)
	{
		AfxMessageBox("���Ƹ���Ϊ0���޷�����Ϊ�䣡");
		return;
	}
	if (CardPro > 100 || CardPro < 0)
	{
		AfxMessageBox("���Ƹ������ô���");

		return;
	}
	m_GameUserInfo.m_ChangeCardPro.Format("%d",CardPro);

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnThw10()
{
	// TODO: �ڴ���������������
	OnTh10();
}

void COnLineSortList::OnThw20()
{
	// TODO: �ڴ���������������
	OnTh20();
}

void COnLineSortList::OnThw30()
{
	// TODO: �ڴ���������������
	OnTh30();
}

void COnLineSortList::OnThw40()
{
	// TODO: �ڴ���������������
	OnTh40();
}

void COnLineSortList::OnThw50()
{
	// TODO: �ڴ���������������
	OnTh50();
}

void COnLineSortList::OnThw60()
{
	// TODO: �ڴ���������������
	OnTh60();
}

void COnLineSortList::OnThw70()
{
	// TODO: �ڴ���������������
	OnTh70();
}

void COnLineSortList::OnThw80()
{
	// TODO: �ڴ���������������
	OnTh80();
}

void COnLineSortList::OnThw90()
{
	// TODO: �ڴ���������������
	OnTh90();
}

void COnLineSortList::OnThw100()
{
	// TODO: �ڴ���������������
	OnTh100();
}

void COnLineSortList::OnLtha10()
{
	// TODO: �ڴ���������������
	OnLth10();
}

void COnLineSortList::OnLtha20()
{
	// TODO: �ڴ���������������
	OnLth20();
}

void COnLineSortList::OnLtha30()
{
	// TODO: �ڴ���������������
	OnLth30();
}

void COnLineSortList::OnLtha40()
{
	// TODO: �ڴ���������������
	OnLth40();
}

void COnLineSortList::OnLtha50()
{
	// TODO: �ڴ���������������
	OnLth50();
}

void COnLineSortList::OnLtha60()
{
	// TODO: �ڴ���������������
	OnLth60();
}

void COnLineSortList::OnLtha70()
{
	// TODO: �ڴ���������������
	OnLth70();
}

void COnLineSortList::OnLtha80()
{
	// TODO: �ڴ���������������
	OnLth80();
}

void COnLineSortList::OnLtha90()
{
	// TODO: �ڴ���������������
	OnLth90();
}

void COnLineSortList::OnLtha100()
{
	// TODO: �ڴ���������������
	OnLth100();
}

void COnLineSortList::OnSetSelf()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void COnLineSortList::OnSet500w()
{
	// TODO: �ڴ���������������

	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "5000000";
	m_GameUserInfo.m_LoseHighest = "-5000000";

	m_UserScoreSet.lMaxWin = 5000000;
	m_UserScoreSet.lMaxLose = -5000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet1000w()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "10000000";
	m_GameUserInfo.m_LoseHighest = "-10000000";

	m_UserScoreSet.lMaxWin = 10000000;
	m_UserScoreSet.lMaxLose = -10000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet2000w()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "20000000";
	m_GameUserInfo.m_LoseHighest = "-20000000";

	m_UserScoreSet.lMaxWin = 20000000;
	m_UserScoreSet.lMaxLose = -20000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet5000w()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "50000000";
	m_GameUserInfo.m_LoseHighest = "-50000000";

	m_UserScoreSet.lMaxWin = 50000000;
	m_UserScoreSet.lMaxLose = -50000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet1e()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "100000000";
	m_GameUserInfo.m_LoseHighest = "-100000000";

	m_UserScoreSet.lMaxWin = 100000000;
	m_UserScoreSet.lMaxLose = -100000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet2e()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "200000000";
	m_GameUserInfo.m_LoseHighest = "-200000000";

	m_UserScoreSet.lMaxWin = 200000000;
	m_UserScoreSet.lMaxLose = -200000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet5e()
{
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "500000000";
	m_GameUserInfo.m_LoseHighest = "-500000000";

	m_UserScoreSet.lMaxWin = 500000000;
	m_UserScoreSet.lMaxLose = -500000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSet8000w()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	OnGetUserListInfo();

	m_GameUserInfo.m_WinHighest = "80000000";
	m_GameUserInfo.m_LoseHighest = "-80000000";

	m_UserScoreSet.lMaxWin = 80000000;
	m_UserScoreSet.lMaxLose = -80000000;

	m_settype = MAXDEFAULT;

	m_IsSysFault = false;

	DWORD CardPro = _ttoi(m_GameUserInfo.m_ChangeCardPro);
	if (CardPro != 0)
	{
		AfxMessageBox("���Ƹ��ʱ���Ϊ0");

		return;
	}

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserInfo();
}

void COnLineSortList::OnSetUserRemarks()
{
	// TODO: �ڴ���������������

	CUserRemarksInfo UserRrmarksInfoDlg;
	UserRrmarksInfoDlg.m_UMUserInfo = m_UserScoreSet;

	UserRrmarksInfoDlg.DoModal();

}

void COnLineSortList::OnMark1()
{
	// TODO: �ڴ���������������
	//SetItem(m_nItem,7,LVIF_IMAGE|LVIF_TEXT,m_UserScoreSet.szNickName,1,NULL,NULL,1);
}

// void COnLineSortList::OnNMClickGameUserList(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	*pResult = 0;
// }

void COnLineSortList::OnUserHide()
{
	// TODO: �ڴ���������������

	m_tabUserVip.dwUserID = ((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.dwUserID;
	m_tabUserVip.nType = 3;
	((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 3;

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserVip(m_tabUserVip);

	DWORD userID =m_UserScoreSet.dwUserID;/* _ttoi(m_GameUserInfo.m_User);*/
	CString nickName = m_UserScoreSet.szNickName;/*m_GameUserInfo.m_NickName;*/
	m_GameInfo.CreateHideUserTable();
	m_GameInfo.InsertHideUser(userID,nickName);
	m_GameInfo.SeleteHideUser();

	int nItem;
	for (nItem=0;nItem<GetItemCount();++nItem)
	{
		DWORD n = ((CUserInfoItem * )GetItemData(nItem))->m_tagUMUserScoreSet.dwUserID;
		if (n == m_UserScoreSet.dwUserID)
		{
			DeleteItem(nItem);
		}

	}

}

void COnLineSortList::OnCheckHideUser()
{
	// TODO: �ڴ���������������
	// 	CDlgHideUser dlg;
	// 	dlg.DoModal();
}

VOID COnLineSortList::ShowUserInfo(tagUMUserScoreSet* userInfo)
{
	CDlgUserInfo UserInfoDlg;
	UserInfoDlg.m_tagUserInfo = *userInfo;

	m_UserScoreSet = *userInfo;
	if (UserInfoDlg.DoModal() == IDOK)
	{
		//return;
		CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;
		/*int ntype;*/

		if (UserInfoDlg.m_AllowSet == 1)
		{
			if (_ttoi64(WinLoseScore)>_ttoi64(WinMax) || _ttoi64(WinLoseScore)<_ttoi64(LoseMax))
			{
				AfxMessageBox("������Ӯ�������ܸ���Ӯ���,���ߵ�������ߣ�");
				return;
			}
			OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
				UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
		}else
		{
			OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
				UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
		}
	}
}