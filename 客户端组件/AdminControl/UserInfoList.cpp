#include "StdAfx.h"
#include "UserInfoList.h"
#include "atltime.h"
#include "MissionUserInfo.h"
#include "UserRemarks.h"
#include "UserRemarksInfo.h"
#include "DlgHideUser.h"
#include "DlgUserInfo.h"
#include "CDlgFrezon.h"

CUserInfoList::CUserInfoList(void)
{
	m_IsSysFault = false;
	m_nPlat = 0;
	m_nPlatKind = 0;
	m_settype = MAXDEFAULT;
	m_IsSort = false;
	m_ImageList = new CImageList;

	m_IsFirstList = false;
}

CUserInfoList::~CUserInfoList(void)
{
}


BEGIN_MESSAGE_MAP(CUserInfoList, CGridListCtrlGroups)
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
	ON_COMMAND(ID_SETVIP, &CUserInfoList::OnSetvip)
	ON_COMMAND(ID_DEVIP, &CUserInfoList::OnDevip)
	ON_COMMAND(ID_SET, &CUserInfoList::OnUserSet)
	ON_COMMAND(ID_SET_1, &CUserInfoList::OnUserSet1)
	ON_COMMAND(ID_SET_2, &CUserInfoList::OnUserSet2)
	ON_COMMAND(ID_SET_3, &CUserInfoList::OnUserSet3)
	ON_COMMAND(ID_SET_DEFAULT, &CUserInfoList::OnSetDefault)
	ON_COMMAND(ID_SET_DEFAULT1, &CUserInfoList::OnSetDefault1)
	ON_COMMAND(ID_SET_DEFAULT2, &CUserInfoList::OnSetDefault2)
	ON_COMMAND(ID_SET_DEFAULT3, &CUserInfoList::OnSetDefault3)

	ON_COMMAND(ID_TH10, &CUserInfoList::OnTh10)
	ON_COMMAND(ID_TH20, &CUserInfoList::OnTh20)
	ON_COMMAND(ID_TH30, &CUserInfoList::OnTh30)
	ON_COMMAND(ID_TH40, &CUserInfoList::OnTh40)
	ON_COMMAND(ID_TH50, &CUserInfoList::OnTh50)
	ON_COMMAND(ID_TH60, &CUserInfoList::OnTh60)
	ON_COMMAND(ID_TH70, &CUserInfoList::OnTh70)
	ON_COMMAND(ID_TH80, &CUserInfoList::OnTh80)
	ON_COMMAND(ID_TH90, &CUserInfoList::OnTh90)
	ON_COMMAND(ID_TH100, &CUserInfoList::OnTh100)

	ON_COMMAND(ID_LTH10, &CUserInfoList::OnLth10)
	ON_COMMAND(ID_LTH20, &CUserInfoList::OnLth20)
	ON_COMMAND(ID_LTH30, &CUserInfoList::OnLth30)
	ON_COMMAND(ID_LTH40, &CUserInfoList::OnLth40)
	ON_COMMAND(ID_LTH50, &CUserInfoList::OnLth50)
	ON_COMMAND(ID_LTH60, &CUserInfoList::OnLth60)
	ON_COMMAND(ID_LTH70, &CUserInfoList::OnLth70)
	ON_COMMAND(ID_LTH80, &CUserInfoList::OnLth80)
	ON_COMMAND(ID_LTH90, &CUserInfoList::OnLth90)
	ON_COMMAND(ID_LTH100, &CUserInfoList::OnLth100)

	ON_COMMAND(ID_THW10, &CUserInfoList::OnThw10)
	ON_COMMAND(ID_THW20, &CUserInfoList::OnThw20)
	ON_COMMAND(ID_THW30, &CUserInfoList::OnThw30)
	ON_COMMAND(ID_THW40, &CUserInfoList::OnThw40)
	ON_COMMAND(ID_THW50, &CUserInfoList::OnThw50)
	ON_COMMAND(ID_THW60, &CUserInfoList::OnThw60)
	ON_COMMAND(ID_THW70, &CUserInfoList::OnThw70)
	ON_COMMAND(ID_THW80, &CUserInfoList::OnThw80)
	ON_COMMAND(ID_THW90, &CUserInfoList::OnThw90)
	ON_COMMAND(ID_THW100, &CUserInfoList::OnThw100)

	ON_COMMAND(ID_LTHA10, &CUserInfoList::OnLtha10)
	ON_COMMAND(ID_LTHA20, &CUserInfoList::OnLtha20)
	ON_COMMAND(ID_LTHA30, &CUserInfoList::OnLtha30)
	ON_COMMAND(ID_LTHA40, &CUserInfoList::OnLtha40)
	ON_COMMAND(ID_LTHA50, &CUserInfoList::OnLtha50)
	ON_COMMAND(ID_LTHA60, &CUserInfoList::OnLtha60)
	ON_COMMAND(ID_LTHA70, &CUserInfoList::OnLtha70)
	ON_COMMAND(ID_LTHA80, &CUserInfoList::OnLtha80)
	ON_COMMAND(ID_LTHA90, &CUserInfoList::OnLtha90)
	ON_COMMAND(ID_LTHA100, &CUserInfoList::OnLtha100)
	ON_COMMAND(ID_SET_SELF, &CUserInfoList::OnSetSelf)
	ON_COMMAND(ID_SET_500W, &CUserInfoList::OnSet500w)
	ON_COMMAND(ID_SET_1000W, &CUserInfoList::OnSet1000w)
	ON_COMMAND(ID_SET_2000W, &CUserInfoList::OnSet2000w)
	ON_COMMAND(ID_SET_5000W, &CUserInfoList::OnSet5000w)
	ON_COMMAND(ID_SET_1E, &CUserInfoList::OnSet1e)
	ON_COMMAND(ID_SET_2E, &CUserInfoList::OnSet2e)
	ON_COMMAND(ID_SET_5E, &CUserInfoList::OnSet5e)
	ON_COMMAND(ID_SET_8000W, &CUserInfoList::OnSet8000w)
	ON_COMMAND(ID_VIP_32911, &CUserInfoList::OnSetUserRemarks)
	ON_COMMAND(ID_MARK1, &CUserInfoList::OnMark1)
//	ON_NOTIFY(NM_CLICK, IDC_GAME_USER_LIST, &CUserInfoList::OnNMClickGameUserList)
ON_COMMAND(ID_USER_HIDE, &CUserInfoList::OnUserHide)
ON_COMMAND(ID_CHECK_HIDE_USER, &CUserInfoList::OnCheckHideUser)
ON_COMMAND(ID_FROZEN, &CUserInfoList::OnFrozen)
ON_COMMAND(ID_Kick, &CUserInfoList::OnKick)
END_MESSAGE_MAP()

BOOL CUserInfoList::OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	CellHitTest(pItem->ptAction, nRow, nCol);

	if (nRow != -1)
	{
		m_nItem = nRow;
		//tagUMUserScoreSet lUserScoreSet = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet;
		m_UserScoreSet = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet;

		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;

		ASSERT(CMissionUserInfo::GetInstance()!=NULL);
		CMissionUserInfo::GetInstance()->OnGetSameMachine(m_UserScoreSet.dwUserID);

// 		CDlgUserInfo UserInfoDlg;
// 		UserInfoDlg.m_tagUserInfo = m_UserScoreSet;
// 
// 		if (UserInfoDlg.DoModal() == IDOK)
// 		{
// 			//return FALSE;
// 			CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;
// 
// 			if (UserInfoDlg.m_AllowSet == 1)
// 			{
// 				if (_ttoi64(WinLoseScore)>_ttoi64(WinMax) || _ttoi64(WinLoseScore)<_ttoi64(LoseMax))
// 				{
// 					AfxMessageBox("������Ӯ�������ܸ���Ӯ���,���ߵ�������ߣ�");
// 					return FALSE;
// 				}
// 				OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
// 					UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
// 			}else
// 			{
// // 				int pos = UserInfoDlg.m_CombState.GetCurSel();
// // 				if (pos < 0)
// // 				{
// // 					ntype = MAXDEFAULT;
// // 				}
// 				OnSetUserScoreInfo(UserInfoDlg.m_tagUserInfo.dwUserID,UserInfoDlg.WinMax,UserInfoDlg.LoseMax,UserInfoDlg.NotifyWin,
// 					UserInfoDlg.NotifyLose,UserInfoDlg.lRate,UserInfoDlg.WinLoseScore,UserInfoDlg.ntype);
// 			}
// 		}

	}

	return FALSE;	// Let parent-dialog get chance
}

VOID CUserInfoList::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[64]=TEXT("");
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

VOID CUserInfoList::InitUserInfoList()
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
		if (Col == 20)
		{
			pTrait = new CGridColumnTraitDateTime;
		}
		if (Col == 15 || Col == 25 || Col == 26 || Col == 27 || Col == 28)
		{
			pTrait = new CGridColumnTraitEdit;
		}else 
			pTrait = new CGridColumnTraitText;
		if (Col == 1 || Col == 4 || Col == 5 /*|| Col == 21*/ || Col == 22/* || Col == 23 || Col == 24*/)
		{
			ShowColumn(Col,false);
		}
	
		InsertColumnTrait(Col+1, title, LVCFMT_LEFT, 69, Col, pTrait);

		if (Col != 1 && Col != 2 && Col!=3 /*&& Col!=6*/ && Col!=7 && /*Col!=8 &&*/ Col!=5 && Col!=19 && Col!=20)
		{
			pTrait->SetSortFormatNumber(true);
		}
	}

	SetColumnWidth(1,40);
	SetColumnWidth(9,100);
	SetColumnWidth(10,100);
	SetColumnWidth(11,100);
	SetColumnWidth(15,100);
	SetColumnWidth(17,100);
	SetColumnWidth(20,100);
	SetColumnWidth(21,100);
	SetColumnWidth(22,100);
	SetColumnWidth(23,100);
	SetColumnWidth(24,100);
	SetColumnWidth(26,100);
	SetColumnWidth(27,100);
	SetColumnWidth(28,100);
	SetColumnWidth(29,100);
//	SetColumnWidth(32,120);
	
	const CString& title = GetColTitle(Col);

	CGridColumnTrait* pTrait = NULL;
	InsertColumnTrait(++Col, "ip", LVCFMT_LEFT, 40, Col, pTrait);
	InsertColumnTrait(++Col, "������", LVCFMT_LEFT, 40, Col, pTrait);
	InsertColumnTrait(Col+1, "Ԥ������", LVCFMT_LEFT, 40, Col, pTrait);
	ShowColumn(++Col,false);
	InsertColumnTrait(++Col,"��ע",LVCFMT_LEFT, 40, Col, pTrait);
	
	SetCellMargin(1.2);
	SetColumnWidth(35,150);

	OnOpenFilterFile();
	
	m_GameInfo.SelectUserInfo();
	m_GameInfo.SeleteHideUser();

}


void CUserInfoList::OnGameUserInfoFinish()
{
}

void CUserInfoList::OnGameUserInfoUpdateFinish()
{
}

void CUserInfoList::OnSetServerID(DWORD ServerID)
{
	m_nPlat = ServerID;
}
VOID CUserInfoList::OnSetKindID(DWORD KindID)
{
	m_nPlatKind = KindID;
}
void CUserInfoList::OnRedraw(BOOL nRedraw)
{
	SetRedraw(nRedraw);
}

VOID CUserInfoList::OnSetUserRemarks(DWORD UserID,CString Remarks)
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

VOID CUserInfoList::OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type)
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

CString CUserInfoList::GetModuleDir() 
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

void CUserInfoList::OnOpenFilterFile()
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

void CUserInfoList::OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem)
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
		case 12:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllOutScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 13:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllInScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 14:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lDifference,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 15://���Ƹ���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(nItem,++Col,szItemText);

			}
		case 16://��ֵ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 17://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(nItem,++Col,szItemText);

			}
		case 18:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(nItem,++Col,szItemText);
			}
		case 19://���һ��ת��
			{

 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 20://���һ��ת��
			{
 				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 21://�ۼ���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 22://������Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 23://���ú���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);


			}
		case 24://��ʼʱ��
			{
 				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
 				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
 				SetItemText(nItem,++Col,strTime);
			}
		case 25://Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 26://�����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 27://Ԥ��Ӯ
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 28://Ԥ����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

 				szItemText.Format(_T("%s"),szControl);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 29://Ӯ��
			{
 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 30://���
			{
 				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
 				SetItemText(nItem,++Col,szItemText);

			}
		case 31://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(nItem,++Col,szClientAddr);

			}
		case 32://����ID
			{
				SetItemText(nItem,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

			}
		case 33:
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
		case 34://��ע
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
		case 12:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllOutScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 13:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllInScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 14:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lDifference,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 15://���Ƹ���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
				SetItemText(iLine,++Col,szItemText);

			}
		case 16://��ֵ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);


			}
		case 17://����
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
				SetItemText(iLine,++Col,szItemText);

			}
		case 18:
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);
			}
		case 19://���һ��ת��
			{

				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
				SetItemText(iLine,++Col,szItemText);

			}
		case 20://���һ��ת��
			{
				szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
				SetItemText(iLine,++Col,szItemText);

			}
		case 21://�ۼ���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);


			}
		case 22://������Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 23://���ú���Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 24://��ʼʱ��
			{
				CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
				CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
				SetItemText(iLine,++Col,strTime);

			}
		case 25://Ӯ���
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 26://�����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 27://Ԥ��Ӯ
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 28://Ԥ����
			{
				SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

				szItemText.Format(_T("%s"),szControl);
				SetItemText(iLine,++Col,szItemText);

			}
		case 29://Ӯ��
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
				SetItemText(iLine,++Col,szItemText);

			}
		case 30://���
			{
				szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
				SetItemText(iLine,++Col,szItemText);


			}
		case 31://ip
			{
				TCHAR szClientAddr[16]=TEXT("");
				BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
				_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
				SetItemText(iLine,++Col,szClientAddr);

			}
		case 32://����ID
			{
				SetItemText(iLine,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

			}
		case 33:
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
		case 34://��ע
			{
				CString szText,strRemarks;
				strRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(pGameUserInfoItem->m_tagUMUserScoreSet.dwUserID);
				SetItemText(iLine,++Col,strRemarks);
			}
		}
	}

	return;
}

int CUserInfoList::OnGetUserCount()
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

int CUserInfoList::OnGetMobileCount(int& nMobileOx,int& nMobileFish)
{
	int n = GetItemCount();
	int nIndex = 0;

	for (int i=0;i<n;i++)
	{
		CString strMobile = GetItemText(i,33);
		if (strMobile.Find("mobile")!=-1)
		{
			CString strGameName = GetItemText(i,2);

			if (strGameName.Find(_T("ͨ��ţţ"))!=-1 || strGameName.Find(_T("6�˻���"))!=-1 || strGameName.Find(_T("����ţţ"))!=-1)
			{
				nMobileOx++;
			}
			if (strGameName.Find(_T("��������"))!=-1 || strGameName.Find(_T("�����칬"))!=-1 || strGameName.Find(_T("��󸲶��"))!=-1)
			{
				nMobileFish++;
			}
			nIndex++;
		}
	}

	return nIndex;
}

int CUserInfoList::OnGetMobliePlazaCount()
{
	int n = GetItemCount();
	int nIndex = 0;

	for (int i=0;i<n;i++)
	{
		CString strMobile = GetItemText(i,33);
		if (strMobile.Find("plaza")!=-1)
		{
			nIndex++;
		}
	}

	
	return nIndex;
}

DWORD CUserInfoList::OnGetUserRecharge()
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

VOID CUserInfoList::OnDelAllUserData()
{
	DeleteAllItems();
}

INT CUserInfoList::OnUpDataUserData(DWORD UserID)
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
void CUserInfoList::OnGameUserInfoUpdate(CUserInfoItem * pGameUserInfoItem)
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
// 					if (pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate1 == 0)
// 					{
// 						SetItemText(nItem,++Col,"����");
// 					}else
// 						SetItemText(nItem,++Col,"����վ");

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
			case 12:
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllOutScore,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 13:
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lAllInScore,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);
				}
			case 14:
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lDifference,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);
				}
			case 15://���Ƹ���
				{
					szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinOrLostRate);
					SetItemText(nItem,++Col,szItemText);

				}
			case 16://��ֵ���
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose1,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 17://����
				{
					szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwTableID);
					SetItemText(nItem,++Col,szItemText);

				}
			case 18:
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lSetWinOrLose,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);
				}
			case 19://���һ��ת��
				{

					szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastOut);
					SetItemText(nItem,++Col,szItemText);

				}
			case 20://���һ��ת��
				{
					szItemText.Format(_T("%s"),pGameUserInfoItem->m_tagUMUserScoreSet.szLastIn);
					SetItemText(nItem,++Col,szItemText);

				}
			case 21://�ۼ���Ӯ���
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lWinScore,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 22://������Ӯ���
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin1,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 23://���ú���Ӯ���
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lTempScore,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 24://��ʼʱ��
				{
					CTime tm(pGameUserInfoItem->m_tagUMUserScoreSet.dwBeginTime);
					CString strTime = tm.Format(_T("%m-%d %H:%M:%S"));
					SetItemText(nItem,++Col,strTime);

				}
			case 25://Ӯ���
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxWin,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 26://�����
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lMaxLose,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 27://Ԥ��Ӯ
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxWin,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 28://Ԥ����
				{
					SwitchScoreFormat(pGameUserInfoItem->m_tagUMUserScoreSet.lNotifyMaxLost,3L,szControl,CountArray(szControl));

					szItemText.Format(_T("%s"),szControl);
					SetItemText(nItem,++Col,szItemText);

				}
			case 29://Ӯ��
				{
					szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwWinCount);
					SetItemText(nItem,++Col,szItemText);

				}
			case 30://���
				{
					szItemText.Format(_T("%d"),pGameUserInfoItem->m_tagUMUserScoreSet.dwLoseCount);
					SetItemText(nItem,++Col,szItemText);

				}
			case 31://ip
				{
					TCHAR szClientAddr[16]=TEXT("");
					BYTE * pClientAddr=(BYTE *)&pGameUserInfoItem->m_tagUMUserScoreSet.dwClientAddr;
					_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);
					SetItemText(nItem,++Col,szClientAddr);

				}
			case 32://����ID
				{
					SetItemText(nItem,++Col,pGameUserInfoItem->m_tagUMUserScoreSet.szMachineID);

				}
			case 33:
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
			case 34://��ע
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
void CUserInfoList::OnGameUserInfoDelete(CUserInfoItem * pGameUserInfoItem)
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

SCORE CUserInfoList::GetUserControlScore(CString pScore)
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

VOID CUserInfoList::OnGetUserListInfo()
{
	int m_nSubItem = 1;

	m_UserScoreSet = ((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet;

}

void CUserInfoList::OnUserSort()
{
	CString szIndex;
	int k = 1;
	for (int i=0;i<=GetItemCount();++i)
	{
		szIndex.Format(_T("%d"),k++);
		SetItemText(i,1,szIndex);
	}
}

// LRESULT CUserInfoList::OnButtonClick( WPARAM wParam, LPARAM lParam )
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
void CUserInfoList::OnClSetUserVIP()
{
	m_tabUserVip.dwUserID = m_UserScoreSet.dwUserID;
	m_tabUserVip.nType = 1;
//	((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 1;

 
	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetUserVip(m_tabUserVip);

}
//ɾ��VIP
void CUserInfoList::OnClDelUserVIP()
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

		m_tabUserVip.dwUserID = m_UserScoreSet.dwUserID;
		m_tabUserVip.nType = 0;
//		((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 0;

		if (((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType == 3)
		{
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

	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->SetDLUserVip(m_tabUserVip);

}

//�������Ӯ
void CUserInfoList::OnSetUserWin()
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
void CUserInfoList::OnSetUserLose()
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
void CUserInfoList::OnSetUserWin1()
{
	OnSetUserWin();
}
//���������
void CUserInfoList::OnSetUserLose2()
{
	OnSetUserLose();
}
//Ԥ������
VOID CUserInfoList::OnWarningSort()
{
	SetRedraw(FALSE);
	SortColumn(31,false);
//	OnUserSort();
//	m_IsSort = true;
	SetRedraw(TRUE);
}

void CUserInfoList::OnRButtonDown(UINT nFlags, CPoint point)
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

// void CUserInfoList::OnLButtonDown(UINT nFlags, CPoint point)
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
VOID CUserInfoList::OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	//return;

	if( GetFocus() != this )
		SetFocus();	// Force focus to finish editing
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	m_SelectUser.RemoveAll();

	POSITION pos=GetFirstSelectedItemPosition();
	while(pos)
	{
		int index=GetNextSelectedItem(pos);
		m_SelectUser.Add(index);
	}

	m_strSelectUser=TEXT("");
	CString szUser;
	DWORD UserID;
	for (int i=0;i<m_SelectUser.GetCount();i++)
	{
		DWORD userid=((CUserInfoItem * )GetItemData(m_SelectUser.GetAt(i)))->m_tagUMUserScoreSet.dwUserID;
		szUser.Format("%d",userid);

		m_strSelectUser.Append(szUser);
		m_strSelectUser.Append(",");

// 		if (i==0)
// 		{
// 			m_strSelectUser.Format("%d",userid);
// 		}else
// 		{
// 			m_strSelectUser.Append(",");
// 			m_strSelectUser.Append(szUser);
// 		}
	}



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

void CUserInfoList::OnSetvip()
{
	// TODO: �ڴ���������������
	OnClSetUserVIP();
}

void CUserInfoList::OnDevip()
{
	// TODO: �ڴ���������������
	OnClDelUserVIP();
}

void CUserInfoList::OnUserSet()
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

void CUserInfoList::OnUserSet1()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void CUserInfoList::OnUserSet2()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void CUserInfoList::OnUserSet3()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void CUserInfoList::OnSetDefault()
{
	// TODO: �ڴ���������������
	int m_nSubItem = 1;

	m_GameUserInfo.m_Event = GetItemText(m_nItem,++m_nSubItem);
	m_GameUserInfo.m_WinOrLose = GetItemText(m_nItem,++m_nSubItem);
	m_GameUserInfo.m_User = GetItemText(m_nItem,++m_nSubItem);


	ASSERT(CMissionUserInfo::GetInstance()!=NULL);
	CMissionUserInfo::GetInstance()->OnSetDeFault();

}

void CUserInfoList::OnSetDefault1()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void CUserInfoList::OnSetDefault2()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void CUserInfoList::OnSetDefault3()
{
	// TODO: �ڴ���������������
	OnSetDefault();
}

void CUserInfoList::OnTh10()
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

void CUserInfoList::OnTh20()
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

void CUserInfoList::OnTh30()
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

void CUserInfoList::OnTh40()
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

void CUserInfoList::OnTh50()
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

void CUserInfoList::OnTh60()
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

void CUserInfoList::OnTh70()
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

void CUserInfoList::OnTh80()
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

void CUserInfoList::OnTh90()
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

void CUserInfoList::OnTh100()
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

void CUserInfoList::OnLth10()
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

void CUserInfoList::OnLth20()
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

void CUserInfoList::OnLth30()
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

void CUserInfoList::OnLth40()
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

void CUserInfoList::OnLth50()
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

void CUserInfoList::OnLth60()
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

void CUserInfoList::OnLth70()
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

void CUserInfoList::OnLth80()
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

void CUserInfoList::OnLth90()
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

void CUserInfoList::OnLth100()
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

void CUserInfoList::OnThw10()
{
	// TODO: �ڴ���������������
	OnTh10();
}

void CUserInfoList::OnThw20()
{
	// TODO: �ڴ���������������
	OnTh20();
}

void CUserInfoList::OnThw30()
{
	// TODO: �ڴ���������������
	OnTh30();
}

void CUserInfoList::OnThw40()
{
	// TODO: �ڴ���������������
	OnTh40();
}

void CUserInfoList::OnThw50()
{
	// TODO: �ڴ���������������
	OnTh50();
}

void CUserInfoList::OnThw60()
{
	// TODO: �ڴ���������������
	OnTh60();
}

void CUserInfoList::OnThw70()
{
	// TODO: �ڴ���������������
	OnTh70();
}

void CUserInfoList::OnThw80()
{
	// TODO: �ڴ���������������
	OnTh80();
}

void CUserInfoList::OnThw90()
{
	// TODO: �ڴ���������������
	OnTh90();
}

void CUserInfoList::OnThw100()
{
	// TODO: �ڴ���������������
	OnTh100();
}

void CUserInfoList::OnLtha10()
{
	// TODO: �ڴ���������������
	OnLth10();
}

void CUserInfoList::OnLtha20()
{
	// TODO: �ڴ���������������
	OnLth20();
}

void CUserInfoList::OnLtha30()
{
	// TODO: �ڴ���������������
	OnLth30();
}

void CUserInfoList::OnLtha40()
{
	// TODO: �ڴ���������������
	OnLth40();
}

void CUserInfoList::OnLtha50()
{
	// TODO: �ڴ���������������
	OnLth50();
}

void CUserInfoList::OnLtha60()
{
	// TODO: �ڴ���������������
	OnLth60();
}

void CUserInfoList::OnLtha70()
{
	// TODO: �ڴ���������������
	OnLth70();
}

void CUserInfoList::OnLtha80()
{
	// TODO: �ڴ���������������
	OnLth80();
}

void CUserInfoList::OnLtha90()
{
	// TODO: �ڴ���������������
	OnLth90();
}

void CUserInfoList::OnLtha100()
{
	// TODO: �ڴ���������������
	OnLth100();
}

void CUserInfoList::OnSetSelf()
{
	// TODO: �ڴ���������������
	OnUserSet();
}

void CUserInfoList::OnSet500w()
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

void CUserInfoList::OnSet1000w()
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

void CUserInfoList::OnSet2000w()
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

void CUserInfoList::OnSet5000w()
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

void CUserInfoList::OnSet1e()
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

void CUserInfoList::OnSet2e()
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

void CUserInfoList::OnSet5e()
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

void CUserInfoList::OnSet8000w()
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

void CUserInfoList::OnSetUserRemarks()
{
	// TODO: �ڴ���������������

	CUserRemarksInfo UserRrmarksInfoDlg;
	UserRrmarksInfoDlg.m_UMUserInfo = m_UserScoreSet;

	UserRrmarksInfoDlg.DoModal();

}

void CUserInfoList::OnMark1()
{
	// TODO: �ڴ���������������
	//SetItem(m_nItem,7,LVIF_IMAGE|LVIF_TEXT,m_UserScoreSet.szNickName,1,NULL,NULL,1);
}

// void CUserInfoList::OnNMClickGameUserList(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	*pResult = 0;
// }

void CUserInfoList::OnUserHide()
{
	// TODO: �ڴ���������������

	m_tabUserVip.dwUserID = m_UserScoreSet.dwUserID;
	m_tabUserVip.nType = 3;
//	((CUserInfoItem * )GetItemData(m_nItem))->m_tagUMUserScoreSet.nVipType = 3;

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

void CUserInfoList::OnCheckHideUser()
{
	// TODO: �ڴ���������������
// 	CDlgHideUser dlg;
// 	dlg.DoModal();
}

VOID CUserInfoList::ShowUserInfo(tagUMUserScoreSet* userInfo)
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
void CUserInfoList::OnFrozen()
{
	// TODO: �ڴ���������������
	CString strFresonReason;
	CCDlgFrezon FrezonDlg;
	if (FrezonDlg.DoModal()==IDOK)
	{
//		strFresonReason=FrezonDlg.m_strFrezonReason;

		tagUserID* UserID;
		ZeroMemory(UserID,sizeof(UserID));

//		CString str;
		m_strSelectUser.Delete(m_strSelectUser.GetLength()-1,1);
		UserID->dwType=0;
		sprintf(UserID->szUserID,m_strSelectUser);
		sprintf(UserID->szForzen,FrezonDlg.m_strFrezonReason);


		ASSERT(CMissionUserInfo::GetInstance()!=NULL);
		CMissionUserInfo::GetInstance()->OnFrezon(UserID);

	}else
		return;
	
}

void CUserInfoList::OnKick()
{
	// TODO: �ڴ���������������
	CString strFresonReason;
	CCDlgFrezon FrezonDlg;
	//if (FrezonDlg.DoModal()==IDOK)
	//{
		//		strFresonReason=FrezonDlg.m_strFrezonReason;

		tagUserID* UserID;
		ZeroMemory(UserID,sizeof(UserID));

		//		CString str;
		m_strSelectUser.Delete(m_strSelectUser.GetLength()-1,1);
		UserID->dwType=1;
		sprintf(UserID->szUserID,m_strSelectUser);
	//	sprintf(UserID->szForzen,FrezonDlg.m_strFrezonReason);


		ASSERT(CMissionUserInfo::GetInstance()!=NULL);
		CMissionUserInfo::GetInstance()->OnFrezon(UserID);

	//}else
	//	return;
}

void CUserInfoList::OnShowUserInfoDlg(tagUMSameMachine *pSameMachine)
{
	CDlgUserInfo UserInfoDlg;
	UserInfoDlg.m_tagUserInfo = m_UserScoreSet;
	UserInfoDlg.m_tagSameMachine.dwCount = pSameMachine->dwCount;

	for (int i=0;i<pSameMachine->dwCount;i++)
	{
		UserInfoDlg.m_tagSameMachine.SameMachineItem[i] = pSameMachine->SameMachineItem[i];
	}


	if (UserInfoDlg.DoModal() == IDOK)
	{
		//return FALSE;
		CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;

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