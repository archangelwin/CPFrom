// GameUserListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "GameUserListDlg.h"
#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"

// CGameUserListDlg 对话框

#define LVS_EX_DOUBLEBUFFER 0x00010000

// #define LC_USER             0x00000001
// #define LC_TANKING          0x00000002

IMPLEMENT_DYNAMIC(CGameUserListDlg, CDialog)

CGameUserListDlg::CGameUserListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameUserListDlg::IDD, pParent)
{
//	m_pSysGameSetDlg = new CDlgSysGameSet;
	m_GameServerItem = NULL;
	m_IsHide = true;

}

CGameUserListDlg::~CGameUserListDlg()
{
	SafeDelete(m_pSysGameSetDlg);
	m_lTranferInfoMap.clear();
}

void CGameUserListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GAME_USER_LIST, m_GameUserList);
	DDX_Control(pDX, IDC_GAME_EVENT, m_GameEvent);
	DDX_Control(pDX, IDC_GAME_WIN,m_WinScore);
	DDX_Control(pDX, IDC_GAME_LOSE,m_LoseScore);
	DDX_Control(pDX, IDC_WARNING_WIN,m_WarningWin);
	DDX_Control(pDX, IDC_WARNING_LOSE,m_WarningLose);
	DDX_Control(pDX, IDC_GAME_RATE,m_WinOrLoseRate);
	DDX_Control(pDX, IDC_SYSSCORE_SET, m_XGroupBox);

	DDX_Control(pDX, IDC_GAME,m_Game);
	DDX_Control(pDX, IDC_WINSCORE,m_Win);
	DDX_Control(pDX, IDC_LOSESCORE,m_Lose);
	DDX_Control(pDX, IDC_WARWIN,m_WWin);
	DDX_Control(pDX, IDC_WARLOSE,m_WLose);
	//	DDX_Control(pDX, IDC_RATE,m_WLRate);

	DDX_Control(pDX, IDC_SYS_SET, m_SysSet);
	DDX_Control(pDX, IDC_ROOM_SET,m_RoomSet);
	DDX_Control(pDX, IDC_SETWIN, m_SetWin);
	DDX_Control(pDX, IDC_SETLOSE, m_SetLose);
	DDX_Control(pDX, IDC_WARSORT, m_WarningSort);
	DDX_Control(pDX, IDC_STORAG_ABLE, m_StorageEnable);
	DDX_Control(pDX, IDC_STORAG_START, m_StaticStaorgeStart);
	DDX_Control(pDX, IDC_STORAGDE, m_StaticStorageDe);
	DDX_Control(pDX, IDC_STORAGESTART, m_StorageStart);
	DDX_Control(pDX, IDC_STORAGEDE, m_StarogeDe);
	DDX_Control(pDX, IDC_STORAG, m_StStorage);
	DDX_Control(pDX, IDC_STROAGE_SET, m_StroageSet);
	DDX_Control(pDX, IDC_STORAGE_REFRESH, m_StorageRefresh);
	DDX_Control(pDX, IDC_THRU, m_Thru);
	DDX_Control(pDX, IDC_SEARCH_USER, m_SearchUser);
	DDX_Control(pDX, IDC_USER_GAMEID, m_UserGameID);
	DDX_Control(pDX, IDC_STSEARCH, m_STSearch);
	DDX_Control(pDX, IDC_ALLUSER, m_AllUserOnLine);
	DDX_Control(pDX, IDC_ISCONNECT, m_IsConnect);
	DDX_Control(pDX, IDC_STHAU, m_STHau);
	//DDX_Control(pDX, IDC_PROMPT, m_Prompt);
	//DDX_Control(pDX, IDC_STSTOCK, m_STStock);
	//DDX_Control(pDX, IDC_STDAMP, m_STDamp);
	DDX_Control(pDX, IDC_TANK, m_TankingGroup);
	DDX_Control(pDX, IDC_STTANKING, m_StTanking);
	DDX_Control(pDX, IDC_EDTANKING, m_EdTanking);
	DDX_Control(pDX, IDC_STTODAYSCORE, m_StTodayScore);
	DDX_Control(pDX, IDC_STTODAY_TANKING, m_StTodayTankingScore);
	DDX_Control(pDX, IDC_STCUR_TANKING, m_StCurTankingScore);
	DDX_Control(pDX, IDC_STSERVER_RATE, m_StServerRate);
	DDX_Control(pDX, IDC_EDSERVER_RATE, m_EdServerRate);
	DDX_Control(pDX, IDC_BTTANKING, m_BtTanking);
	DDX_Control(pDX, IDC_CHTANKING, m_ChTanking);
	DDX_Control(pDX, IDC_STSTATE, m_StState);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEd);
	DDX_Control(pDX, IDC_BUTTON_SWICHTING, m_BtSwitching);
	DDX_Control(pDX, IDC_RICHEDIT_LOOKUP, m_LookUpRhEd);
	DDX_Control(pDX, IDC_BT_ANDROIDCOUNT, m_btAndroidCount);
	DDX_Control(pDX, IDC_ANDROIDCOUNT, m_EdAndroidCount);
}


BEGIN_MESSAGE_MAP(CGameUserListDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_HSCROLL()

	ON_BN_CLICKED(IDC_SYS_SET,OnButtonGetInfo)
	ON_BN_CLICKED(IDC_ROOM_SET,OnButtonRoomSet)
	ON_BN_CLICKED(IDC_WARSORT,OnButtonWarningSort)
	
//	ON_MESSAGE(WM_SYS_GAME_SET,OnSetSysGameData)

	ON_BN_CLICKED(IDC_STORAG_ABLE, &CGameUserListDlg::OnBnClickedStoragAble)
	ON_BN_CLICKED(IDC_STROAGE_SET, &CGameUserListDlg::OnBnClickedStroageSet)
	ON_BN_CLICKED(IDC_STORAGE_REFRESH, &CGameUserListDlg::OnBnClickedStorageRefresh)
	ON_BN_CLICKED(IDC_SEARCH_USER, &CGameUserListDlg::OnBnClickedSearchUser)
	ON_BN_CLICKED(IDC_CHTANKING, &CGameUserListDlg::OnBnClickedChtanking)
	ON_BN_CLICKED(IDC_BTTANKING, &CGameUserListDlg::OnBnClickedBttanking)
	ON_NOTIFY(EN_LINK, IDC_RICHEDIT21, &CGameUserListDlg::OnEnLinkRichedit21)
	ON_BN_CLICKED(IDC_BUTTON_SWICHTING, &CGameUserListDlg::OnBnClickedButtonSwichting)
	ON_BN_CLICKED(IDC_BT_ANDROIDCOUNT, &CGameUserListDlg::OnBnClickedBtAndroidcount)
END_MESSAGE_MAP()


// CGameUserListDlg 消息处理程序
BOOL CGameUserListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rcRect;
	GetWindowRect(&rcRect);
	GetClientRect(&m_rect);

	m_pSysGameSetDlg = new CDlgSysGameSet;
	m_pSysGameSetDlg->Create(IDD_DLGSYSGAMESET);
	m_pSysGameSetDlg->ShowWindow(SW_HIDE);

	m_RoomSet.EnableWindow(FALSE);
	
	m_GameUserList.SetWindowPos(NULL,rcRect.left,rcRect.top,rcRect.right,rcRect.bottom+230,SWP_NOZORDER);

//	m_ImageList.Create(1,20, ILC_COLOR, 0, 0);
//	m_GameUserList.SetImageList(&m_ImageList,LVSIL_SMALL);

	//m_GameUserList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_DOUBLEBUFFER/*|LVS_EX_CHECKBOXES*/);
	m_GameUserList.InitUserInfoList();
//	m_GameUserList.m_IsFirstList = true;
	CUserServerInfo::GetInstance()->SetServerUserInfoDataSink(&m_GameUserList);
	/*CUserServerInfo::GetInstance()->SetServerUserInfoDataSink(&m_)*/

	m_StorageEnable.SetCheck(0);
	m_StorageStart.EnableWindow(FALSE);
	m_StarogeDe.EnableWindow(FALSE);
//	m_StroageSet.EnableWindow(FALSE);
//	m_StorageRefresh.EnableWindow(FALSE);

	m_IsTanking = 0;
	m_ServerID = 0;
	m_StTodayScore.SetWindowText("当天累计输赢:");
	m_StTodayTankingScore.SetWindowText("当天累计放水:");
	m_StCurTankingScore.SetWindowText("当前放水:");

	m_XGroupBox.ShowWindow(SW_SHOW);
	m_Game.ShowWindow(SW_HIDE);
	m_Win.ShowWindow(SW_HIDE);
	m_Lose.ShowWindow(SW_HIDE);
	m_WWin.ShowWindow(SW_HIDE);
	m_WLose.ShowWindow(SW_HIDE);

	m_GameEvent.ShowWindow(SW_HIDE);
	m_WinScore.ShowWindow(SW_HIDE);
	m_LoseScore.ShowWindow(SW_HIDE);
	m_WarningWin.ShowWindow(SW_HIDE);
	m_WarningLose.ShowWindow(SW_HIDE);
	//		m_WinOrLoseRate.ShowWindow(SW_HIDE);
	m_SysSet.ShowWindow(SW_HIDE);

	m_btAndroidCount.ShowWindow(SW_HIDE);
	m_EdAndroidCount.ShowWindow(SW_HIDE);

	m_TankingGroup.ShowWindow(SW_SHOW);

	m_StTodayScore.ShowWindow(SW_SHOW);
	m_StTodayTankingScore.ShowWindow(SW_SHOW);
	m_StCurTankingScore.ShowWindow(SW_SHOW);
	m_StTanking.ShowWindow(SW_SHOW);
	m_EdTanking.ShowWindow(SW_SHOW);
	m_StServerRate.ShowWindow(SW_SHOW);
	m_EdServerRate.ShowWindow(SW_SHOW);
	//m_ChTanking.ShowWindow(SW_HIDE);
	m_BtTanking.ShowWindow(SW_SHOW);
	m_StState.ShowWindow(SW_SHOW);

	m_LookUpRhEd.ShowWindow(SW_SHOW);


	SetTimer(1,3000,NULL);

	//m_Prompt.SetWindowText("换牌：当A,B两人,设置A赢:20%换牌;当A>B时,系统不操作;当A<B时,系统则有20%的概率把两方牌换过来.设置A赢:100%换牌;A 100%赢,设置A输 100%换牌;A 100%输;建议:20-30%");
	//m_STStock.SetWindowText("库存：如库存为0时,第一局玩家必输;当前库存量:A;玩家赢币(开牌前已算好):B;当A>B时:系统不操作,还是玩家赢;当A<B时:玩家输");
	//m_STDamp.SetWindowText("库存衰减:相当玩家玩一局,库存减少的千分比;建议:千分之2");

// 	CString transferscore;
// 	transferscore.Format("%I64d",4000000000);


	return TRUE;

}

CString CGameUserListDlg::GetModuleDir() 
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


bool CGameUserListDlg::GetSysSetInformation()
{
	m_lMaxWin = GetDlgItemInt(IDC_GAME_WIN);
	m_lMaxLose = GetDlgItemInt(IDC_GAME_LOSE);
	m_lNotifyMaxWin = GetDlgItemInt(IDC_WARNING_WIN);
	m_lNotifyMaxLost = GetDlgItemInt(IDC_WARNING_LOSE);
	m_dwWinOrLostRate = GetDlgItemInt(IDC_GAME_RATE,NULL,FALSE);


	if (m_dwWinOrLostRate < 0L || m_dwWinOrLostRate > 100L)
	{
		AfxMessageBox("换牌比率设置错误！");
		return false;
	}


	return true;
}


void CGameUserListDlg::OnButtonGetInfo()
{
	//return;
	if (GetSysSetInformation() == false)
	{
		return;
	}

	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->SetSysInfo();
	}
}

void CGameUserListDlg::OnButtonRoomSet()
{

	if (m_pSysGameSetDlg->m_hWnd == NULL)
	{
		m_pSysGameSetDlg = new CDlgSysGameSet;
	}
	m_pSysGameSetDlg->ShowWindow(SW_MAXIMIZE);

}

void CGameUserListDlg::OnButtonWarningSort()
{
// 	if (m_GameUserList.m_IsSort == false)
// 	{
// 		m_GameUserList.m_IsSort = true;
		m_GameUserList.OnWarningSort();
// 		m_WarningSort.SetWindowText("取消排序");
// 	}else{
// 		m_GameUserList.m_IsSort = false;
// 		m_WarningSort.SetWindowText("预警排序");
// 	}
}

void CGameUserListDlg::ChangeDlgSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
		ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
		rec.left=rec.left*x/m_rect.Width();  //按照比例调整空间的新位置
		rec.top=rec.top*y/m_rect.Height();
		rec.bottom=rec.bottom*y/m_rect.Height();
		rec.right=rec.right*x/m_rect.Width();
		pWnd->MoveWindow(rec);   //伸缩控件
	}
}

void CGameUserListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect m_Rect;
  	GetClientRect(&m_Rect);

// 	if(nType!=SIZE_MINIMIZED ) 
// 	{
// 		ChangeDlgSize(IDC_SYSSCORE_SET,cx,cy);
// 		ChangeDlgSize(IDC_GAME,cx,cy);
// 		ChangeDlgSize(IDC_WINSCORE,cx,cy);
// 		ChangeDlgSize(IDC_LOSESCORE,cx,cy);
// 		ChangeDlgSize(IDC_GAME_WIN,cx,cy);
// 		ChangeDlgSize(IDC_GAME_LOSE,cx,cy);
// 		ChangeDlgSize(IDC_RATE,cx,cy);
// 		ChangeDlgSize(IDC_WARWIN,cx,cy);
// 		ChangeDlgSize(IDC_WARLOSE,cx,cy);
// 		ChangeDlgSize(IDC_GAME_RATE,cx,cy);
// 		ChangeDlgSize(IDC_WARNING_WIN,cx,cy);
// 		ChangeDlgSize(IDC_WARNING_LOSE,cx,cy);
// 		ChangeDlgSize(IDC_SYS_SET,cx,cy);
// 		ChangeDlgSize(IDC_STORAG,cx,cy);
// 		ChangeDlgSize(IDC_STORAG_ABLE,cx,cy);
// 		ChangeDlgSize(IDC_STORAG_START,cx,cy);
// 		ChangeDlgSize(IDC_STORAGDE,cx,cy);
// 		ChangeDlgSize(IDC_STROAGE_SET,cx,cy);
// 	}

	if (m_GameUserList)
	{
		m_GameUserList.MoveWindow(m_Rect.left,m_Rect.top,m_Rect.Width()-10,m_Rect.Height()-200);
		
		m_BtSwitching.MoveWindow(m_Rect.left+370,m_Rect.Height()-200/*+25*/,60,25);
		m_LookUpRhEd.MoveWindow(m_Rect.left,m_Rect.Height()-200+50,220,130);

		m_Game.MoveWindow(m_Rect.left+10,m_Rect.Height()-200+45,60,20);
		m_Win.MoveWindow(m_Rect.left+10,m_Rect.Height()-200+75,60,20);
		m_Lose.MoveWindow(m_Rect.left+10,m_Rect.Height()-200+105,60,20);
// 		m_WWin.MoveWindow(m_Rect.left+220,m_Rect.Height()-200+85,80,20);
// 		m_WLose.MoveWindow(m_Rect.left+220,m_Rect.Height()-200+115,80,20);
		m_WWin.MoveWindow(m_Rect.left+10,m_Rect.Height()-200+135,60,20);
		m_WLose.MoveWindow(m_Rect.left+10,m_Rect.Height()-200+165,60,20);
//		m_WLRate.MoveWindow(m_Rect.left+220,m_Rect.Height()-200+45,80,20);

		m_AllUserOnLine.MoveWindow(m_Rect.left,m_Rect.Height()-200+5,360,20);
		m_IsConnect.MoveWindow(m_Rect.left+440,m_Rect.Height()-200+5,300,20);
		m_XGroupBox.MoveWindow(m_Rect.left,m_Rect.Height()-200+25,230,170);
		
		m_TankingGroup.MoveWindow(m_Rect.left+230,m_Rect.Height()-200+25,240,170);

		m_StTodayScore.MoveWindow(m_Rect.left+235,m_Rect.Height()-200+25+20,200,20);
		m_StTodayTankingScore.MoveWindow(m_Rect.left+235,m_Rect.Height()-200+25+50,230,20);
		m_StCurTankingScore.MoveWindow(m_Rect.left+235,m_Rect.Height()-200+25+80,230,20);
		m_StTanking.MoveWindow(m_Rect.left+235,m_Rect.Height()-200+25+110,60,20);
		m_EdTanking.MoveWindow(m_Rect.left+295,m_Rect.Height()-200+25+110,100,20);
		m_StServerRate.MoveWindow(m_Rect.left+235,m_Rect.Height()-200+25+140,60,20);
		m_EdServerRate.MoveWindow(m_Rect.left+295,m_Rect.Height()-200+25+140,100,20);
		m_ChTanking.MoveWindow(m_Rect.left+430,m_Rect.Height()-200+25+110,50,20);
		m_BtTanking.MoveWindow(m_Rect.left+400,m_Rect.Height()-200+25+140,60,20);
		m_StState.MoveWindow(m_Rect.left+400,m_Rect.Height()-200+25+110,40,20);

		//m_Prompt.MoveWindow(m_Rect.left,m_Rect.Height()-200+25+130+2,560,130);
		//m_STStock.MoveWindow(m_Rect.left+570,m_Rect.Height()-200+25+130+2,370,130);
		//m_STDamp.MoveWindow(m_Rect.left+570+370+10,m_Rect.Height()-200+25+130+2,170,130);

		m_GameEvent.MoveWindow(m_Rect.left+70,m_Rect.Height()-200+45,100,20);
 		m_WinScore.MoveWindow(m_Rect.left+70,m_Rect.Height()-200+75,100,20);
 		m_LoseScore.MoveWindow(m_Rect.left+70,m_Rect.Height()-200+105,100,20);
 		m_WarningWin.MoveWindow(m_Rect.left+70,m_Rect.Height()-200+135,100,20);
 		m_WarningLose.MoveWindow(m_Rect.left+70,m_Rect.Height()-200+165,100,20);
	//	m_WinOrLoseRate.MoveWindow(m_Rect.left+300,m_Rect.Height()-200+45,100,20);

		m_STHau.MoveWindow(m_Rect.left+405,m_Rect.Height()-200+45,20,20);

		m_SysSet.MoveWindow(m_Rect.left+175,m_Rect.Height()-200+75,50,50);
		m_RoomSet.MoveWindow(m_Rect.left+1050,m_Rect.Height()-200+95,100,50);
		m_WarningSort.MoveWindow(m_Rect.left+740,m_Rect.Height()-200+5,80,30);

		m_SetWin.MoveWindow(m_Rect.left+920,m_Rect.Height()-200+35,100,50);
		m_SetLose.MoveWindow(m_Rect.left+960,m_Rect.Height()-200+35,100,50);

		m_StStorage.MoveWindow(m_Rect.left+470,m_Rect.Height()-190+15,230,170);
		m_StorageEnable.MoveWindow(m_Rect.left+480,m_Rect.Height()-190+35,80,20);
		m_StaticStaorgeStart.MoveWindow(m_Rect.left+480,m_Rect.Height()-190+70,100,20);
		m_StaticStorageDe.MoveWindow(m_Rect.left+480,m_Rect.Height()-190+105,100,20);
		m_StorageStart.MoveWindow(m_Rect.left+570,m_Rect.Height()-190+70,100,20);
		m_StarogeDe.MoveWindow(m_Rect.left+570,m_Rect.Height()-190+105,100,20);
		m_StroageSet.MoveWindow(m_Rect.left+480,m_Rect.Height()-190+145,100,30);
		m_StorageRefresh.MoveWindow(m_Rect.left+470+115,m_Rect.Height()-190+145,100,30);

		m_Thru.MoveWindow(m_Rect.left+670,m_Rect.Height()-200+105,20,20);
		
		m_SearchUser.MoveWindow(m_Rect.left+1010,m_Rect.Height()-200+5,100,30);
		m_UserGameID.MoveWindow(m_Rect.left+900,m_Rect.Height()-200+5,100,30);
		m_STSearch.MoveWindow(m_Rect.left+840,m_Rect.Height()-200+10,60,20);

		m_RichEd.MoveWindow(m_Rect.left+700,m_Rect.Height()-200+38,470,160);


		//机器人个数
		m_EdAndroidCount.MoveWindow(m_Rect.left+175+70,m_Rect.Height()-200+135,50+30,30);
		m_btAndroidCount.MoveWindow(m_Rect.left+175+70,m_Rect.Height()-200+165,50+30,30);
	}
}

WORD CGameUserListDlg::SetUserDataInfo(BYTE cbBuffer[], WORD wBufferSize)
{
	if (m_GameUserList.m_IsSysFault == false)
	{
		tagUMUserScoreSet* pUMUserScoreSet = (tagUMUserScoreSet*)cbBuffer;

// 		pUMUserScoreSet->dwUserID = _ttoi(m_GameUserList.m_GameUserInfo.m_User);
// 		pUMUserScoreSet->dwGameID = _ttoi(m_GameUserList.m_GameUserInfo.m_GameID);
// 		sprintf(pUMUserScoreSet->szNickName, m_GameUserList.m_GameUserInfo.m_NickName);
// 		pUMUserScoreSet->dwBeginTime = _ttoi(m_GameUserList.m_GameUserInfo.m_StartTimer);
// 		pUMUserScoreSet->lScore = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_UserGold);//_ttoi(m_GameUserList.m_GameUserInfo.m_UserGold);
// 		pUMUserScoreSet->lInsure = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_BankGold);//_ttoi(m_GameUserList.m_GameUserInfo.m_BankGold);
// 		pUMUserScoreSet->lWinScore = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_WinLoseGold);//_ttoi(m_GameUserList.m_GameUserInfo.m_WinLoseGold);
// 		pUMUserScoreSet->lTempScore = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_SetAfterScore);//_ttoi(m_GameUserList.m_GameUserInfo.m_SetAfterScore);
// 		pUMUserScoreSet->lMaxWin = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_WinHighest);//_ttoi(m_GameUserList.m_GameUserInfo.m_WinHighest);
// 		pUMUserScoreSet->lMaxLose = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_LoseHighest);//_ttoi(m_GameUserList.m_GameUserInfo.m_LoseHighest);
// 		pUMUserScoreSet->lNotifyMaxWin = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_WarningWin);//_ttoi(m_GameUserList.m_GameUserInfo.m_WarningWin);
// 		pUMUserScoreSet->lNotifyMaxLost = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_WarningLose);//_ttoi(m_GameUserList.m_GameUserInfo.m_WarningLose);
// 		pUMUserScoreSet->dwWinOrLostRate = _ttoi(m_GameUserList.m_GameUserInfo.m_ChangeCardPro);
// 		pUMUserScoreSet->lOutScore = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_lOutScore);//_ttoi(m_GameUserList.m_GameUserInfo.m_lOutScore);
// 		pUMUserScoreSet->lInScore = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_lInScore);//_ttoi(m_GameUserList.m_GameUserInfo.m_lInScore);
// 		pUMUserScoreSet->lSetWinOrLose = m_GameUserList.GetUserControlScore(m_GameUserList.m_GameUserInfo.m_szFixScore);
		
		CopyMemory(pUMUserScoreSet,&m_GameUserList.m_UserScoreSet,sizeof(tagUMUserScoreSet));

		pUMUserScoreSet->dwServerID = m_GameUserList.m_ServerID;

		if (pUMUserScoreSet->lMaxLose > 0 || pUMUserScoreSet->lNotifyMaxLost > 0)
		{
			AfxMessageBox("输最高或者预警输必须小于零！");

			return 0;
		}
		if (pUMUserScoreSet->lMaxWin < 0 || pUMUserScoreSet->lNotifyMaxWin < 0)
		{
			AfxMessageBox("赢最高或者预警赢必须大于零！");

			return 0;
		}

		if (m_GameUserList.m_settype != MAXDEFAULT)
		{
			pUMUserScoreSet->dwType = m_GameUserList.m_settype;
		}else
			pUMUserScoreSet->dwType = MAXDEFAULT;

		CTime tmSCan = CTime::GetCurrentTime();
		CString szTime = tmSCan.Format("'%Y-%m-%d %H:%M:%S'");
		pUMUserScoreSet->dwSetTime = _ttoi(szTime);
	}

	return sizeof(tagUMUserScoreSet);
}


WORD CGameUserListDlg::SetDefault(BYTE cbBuffer[], WORD wBufferSize)
{
	tabUserID* pUserID = (tabUserID*)cbBuffer;
	pUserID->dwUserID = m_GameUserList.m_UserScoreSet.dwUserID;/*_ttoi(m_GameUserList.m_GameUserInfo.m_User);*/


	return sizeof(tabUserID);
}

WORD CGameUserListDlg::SetSysUserDataInfo(BYTE cbBuffer[], WORD wBufferSize)
{
	tagUMUserGameSet* ptagUMUserGameSet = (tagUMUserGameSet*)cbBuffer;
	CString szText;
	GetDlgItemText(IDC_GAME_EVENT,szText);
	if (szText == "")
	{
		AfxMessageBox("没有选择游戏!");
		return 0;
	}
	ptagUMUserGameSet->dwServerID = CMissionList::GetInstance()->m_ServerID;
	
	GetDlgItemText(IDC_GAME_WIN,szText);
	ptagUMUserGameSet->lMaxWin = _ttoi(szText);
	
	GetDlgItemText(IDC_GAME_LOSE,szText);
	ptagUMUserGameSet->lMaxLose = _ttoi(szText);
	
	GetDlgItemText(IDC_WARNING_WIN,szText);
	ptagUMUserGameSet->lNotifyMaxWin = _ttoi(szText);

	GetDlgItemText(IDC_WARNING_LOSE,szText);
	ptagUMUserGameSet->lNotifyMaxLost = _ttoi(szText);

	ptagUMUserGameSet->dwWinOrLostRate = m_dwWinOrLostRate;

	if (ptagUMUserGameSet->lMaxLose > 0 || ptagUMUserGameSet->lNotifyMaxLost > 0)
	{
		AfxMessageBox("输分数或者预警输必须小于零！");
		
		return 0;
	}
	if (ptagUMUserGameSet->lMaxWin < 0 || ptagUMUserGameSet->lNotifyMaxWin < 0)
	{
		AfxMessageBox("赢分数或者预警赢必须大于零！");

		return 0;
	}

	CTime tmSCan = CTime::GetCurrentTime();
	CString szTime = tmSCan.Format("'%Y-%m-%d %H:%M:%S'");
	ptagUMUserGameSet->dwSetTime = _ttoi(szTime);


	return sizeof(tagUMUserGameSet);

}

WORD CGameUserListDlg::SetSysGameDataInfo(BYTE cbBuffer[], WORD wBufferSize)
{
	tagUMSysGameSet* ptagUMSysGameSet = (tagUMSysGameSet*)cbBuffer;
	
//	m_pSysGameSetDlg->SetSysGameData();
//	CopyMemory(ptagUMSysGameSet,m_pSysGameSetDlg->m_ptagUMSysGameSet,sizeof(tagUMSysGameSet));
	CString szText;
	GetDlgItemText(IDC_GAME_EVENT,szText);
	if (szText == "" || m_GameServerItem == NULL)
	{
		AfxMessageBox("没有选择游戏!");
		return 0;
	}

	ptagUMSysGameSet->dwServerID = CMissionList::GetInstance()->m_ServerID;
	int n = m_StorageEnable.GetCheck();
	ptagUMSysGameSet->bValid = n;
	if (n == 0)
	{
		CString storage;
		GetDlgItemText(IDC_STORAGESTART,storage);
		ptagUMSysGameSet->dwStoragStart = _ttoi(storage);
		ptagUMSysGameSet->dwStorageDeduct = GetDlgItemInt(IDC_STORAGEDE);

	}else
	{
		CString storage;
		GetDlgItemText(IDC_STORAGESTART,storage);
		ptagUMSysGameSet->dwStoragStart = _ttoi(storage);
		ptagUMSysGameSet->dwStorageDeduct = GetDlgItemInt(IDC_STORAGEDE);
	}
	
	
	return sizeof(tagUMSysGameSet);
}

WORD CGameUserListDlg::OnReFreshStaroge(BYTE cbBuffer[], WORD wBufferSize)
{
	tabServerID* ptabServerID = (tabServerID*)cbBuffer;
	if (m_GameServerItem == NULL)
	{
		return 0;
	}
	ptabServerID->dwServerID = CMissionList::GetInstance()->m_ServerID;

	return sizeof(tabServerID);
}

WORD CGameUserListDlg::SetUserVip(BYTE cbBuffer[], WORD wBufferSize)
{
	tabUserVip* ptabUserVip = (tabUserVip*)cbBuffer;

	ptabUserVip->dwUserID = m_GameUserList.m_tabUserVip.dwUserID;
	ptabUserVip->nType = m_GameUserList.m_tabUserVip.nType;

	return sizeof(tabUserVip);
}

WORD CGameUserListDlg::SetDLUserVip(BYTE cbBuffer[], WORD wBufferSize)
{
	tabUserVip* ptabUserVip = (tabUserVip*)cbBuffer;

	ptabUserVip->dwUserID = m_GameUserList.m_tabUserVip.dwUserID;
	ptabUserVip->nType = m_GameUserList.m_tabUserVip.nType;

	return sizeof(tabUserVip);
}

void CGameUserListDlg::OnReSetData()
{
	m_GameEvent.SetWindowText("");

	m_WinScore.SetWindowText("");

	m_LoseScore.SetWindowText("");

	m_WarningWin.SetWindowText("");

	m_WarningLose.SetWindowText("");

	m_WinOrLoseRate.SetWindowText("");

	m_StorageEnable.SetCheck(0);

	m_StorageStart.SetWindowText("");

	m_StarogeDe.SetWindowText("");

}

bool CGameUserListDlg::GetSysUserDataInfo(tagUMUserGameSet* ptagUMUserGameSet)
{
	ASSERT(ptagUMUserGameSet!=NULL);
	if (ptagUMUserGameSet == NULL) return false;

	if ((ptagUMUserGameSet->dwIsSet&LC_TANKING)>0)
	{
		m_IsTanking = 2;
		m_EdServerRate.EnableWindow(TRUE);
		m_EdTanking.EnableWindow(TRUE);
		m_BtTanking.EnableWindow(TRUE);
	}else{
		m_IsTanking = 0;
// 		m_StTodayScore.SetWindowText("当天累计:");
// 		m_StTodayTankingScore.SetWindowText("当天累计放水:");
// 		m_StCurTankingScore.SetWindowText("当前放水:");
// 		m_EdServerRate.SetWindowText("");
// 		m_EdTanking.SetWindowText("");
		m_EdServerRate.EnableWindow(FALSE);
		m_EdTanking.EnableWindow(FALSE);
		m_BtTanking.EnableWindow(FALSE);
		m_StState.SetWindowText("");
	}

	if ((ptagUMUserGameSet->dwIsSet&LC_USER)>0)
	{
		m_GameUserList.m_IsSet = 1;
	}
	
	CServerListData* pCServerListData = CServerListData::GetInstance();
	if (ptagUMUserGameSet->dwServerID == 0)
	{
		OnReSetData();
		return false;
	}
	m_GameServerItem = pCServerListData->SearchGameServer(CMissionList::GetInstance()->m_ServerID); 
	LPCTSTR m_GameName = m_GameServerItem->m_GameServer.szServerName;
	m_GameEvent.SetWindowText(m_GameName);

	CString szText;
	szText.Format(_T("%lld"),ptagUMUserGameSet->lMaxWin);
	m_WinScore.SetWindowText(szText);

	szText.Format(_T("%lld"),ptagUMUserGameSet->lMaxLose);
	m_LoseScore.SetWindowText(szText);

	szText.Format(_T("%lld"),ptagUMUserGameSet->lNotifyMaxWin);
	m_WarningWin.SetWindowText(szText);

	szText.Format(_T("%lld"),ptagUMUserGameSet->lNotifyMaxLost);
	m_WarningLose.SetWindowText(szText);

	szText.Format(_T("%d"),ptagUMUserGameSet->dwWinOrLostRate);
	m_WinOrLoseRate.SetWindowText(szText);

	return true;
}

bool CGameUserListDlg::GetSysGameDataInfo(tagUMSysGameSet* ptagUMSysGameSet)
{
	ASSERT(ptagUMSysGameSet!=NULL);
	if(ptagUMSysGameSet==NULL) return false;

	ASSERT(m_pSysGameSetDlg!=NULL);
	if(m_pSysGameSetDlg == NULL) return false;

	CServerListData* pCServerListData = CServerListData::GetInstance();
	m_GameServerItem = pCServerListData->SearchGameServer(ptagUMSysGameSet->dwServerID); 

	LPCTSTR m_GameName = m_GameServerItem->m_GameServer.szServerName;

	if (ptagUMSysGameSet->dwServerID!=0)
	{
		//m_RoomSet.EnableWindow(TRUE);
	}

	OnSetStorage(ptagUMSysGameSet,m_GameName);

//	m_pSysGameSetDlg->GetSysGameData(ptagUMSysGameSet,m_GameName);

	return true;
}

void CGameUserListDlg::OnSetStorage(tagUMSysGameSet* ptagUMSysGameSet,LPCTSTR GameName)
{
	CString szText;
	m_ServerID = CMissionList::GetInstance()->m_ServerID;
	if (m_ServerID != ptagUMSysGameSet->dwServerID)
	{
		return;
	}
	if (ptagUMSysGameSet->bValid == 1)
	{

		m_StorageEnable.SetCheck(1);
		m_StorageStart.EnableWindow(TRUE);
		m_StarogeDe.EnableWindow(TRUE);
//		m_StroageSet.EnableWindow(TRUE);
		m_StorageRefresh.EnableWindow(TRUE);

		szText.Format(_T("%d"),ptagUMSysGameSet->dwStoragStart);
		m_StorageStart.SetWindowText(szText);
		szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
		m_StarogeDe.SetWindowText(szText);
	}
	else
	{
		m_StorageEnable.SetCheck(0);
		m_StorageStart.EnableWindow(FALSE);
		m_StarogeDe.EnableWindow(FALSE);
//		m_StroageSet.EnableWindow(FALSE);
//		m_StorageRefresh.EnableWindow(FALSE);

		szText.Format(_T("%d"),ptagUMSysGameSet->dwStoragStart);
		m_StorageStart.SetWindowText(szText);
		szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
		m_StarogeDe.SetWindowText(szText);
	}

	/*m_pSysGameSetDlg->GetSysGameData(ptagUMSysGameSet,GameName);*/
}

BOOL CGameUserListDlg::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

void CGameUserListDlg::OnBnClickedStoragAble()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = m_StorageEnable.GetCheck();
	if (state == 1)
	{
		m_StorageStart.EnableWindow(TRUE);
		m_StarogeDe.EnableWindow(TRUE);
//		m_StroageSet.EnableWindow(TRUE);
//		m_StorageRefresh.EnableWindow(TRUE);
	}
	else{
		m_StorageStart.EnableWindow(FALSE);
		m_StarogeDe.EnableWindow(FALSE);
//		m_StroageSet.EnableWindow(FALSE);
//		m_StorageRefresh.EnableWindow(FALSE);
	}
}

void CGameUserListDlg::OnBnClickedStroageSet()
{
	//return;
	// TODO: 在此添加控件通知处理程序代码
	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->SetSysGameInfo();
	}
}

void CGameUserListDlg::OnBnClickedStorageRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->OnReRefreshStroage();
	}
}

void CGameUserListDlg::OnBnClickedSearchUser()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_USER_GAMEID,m_SearchGameID);
	if (m_SearchGameID == "")
	{
		AfxMessageBox("内容为空！");
		return;
	}
	CUserServerInfo* pCUserServerInfo = CUserServerInfo::GetInstance();
	pCUserServerInfo->m_IsSearch = true;
	if (pCUserServerInfo->OnSearchUser(m_SearchGameID)==FALSE)
	{
		/*m_GameUserList.DeleteAllItems();*/
		CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
		pMissionUserInfo->SreachOffLineUser(m_SearchGameID);

// 		m_hWnd = ::FindWindow("CUserOfflineDlg",NULL);
// 		if (m_hWnd == false)
// 		{
// 			return;
// 		}
// 		
// 		::SendMessage(m_hWnd,WM_DLG_CHANGE,0L,0L);
// 		AfxMessageBox("没有找到用户！");
// 		pCUserServerInfo->m_IsSearch = false;
	}

}

void CGameUserListDlg::OnIsConnect(bool IsConnect)
{
	CString strIsConnect;
	if (IsConnect==true)
	{
		strIsConnect.Format("连接状态：已与服务器连接！");
	}else
	{
		CUserServerInfo::GetInstance()->OnDeleteAllUserInfo();
		strIsConnect.Format("连接状态：与服务器断开连接，正在连接中...");
	}

	m_IsConnect.SetWindowText(strIsConnect);
}

void CGameUserListDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString UserLine;
		int nMobileOx=0;
		int nMobileFish=0;
		int nMPlaza=0;
		int UserOnLine = m_GameUserList.GetItemCount();
		int nUserOnLine = m_GameUserList.OnGetUserCount();
		int nMobileOnLine = m_GameUserList.OnGetMobileCount(nMobileOx,nMobileFish);
		nMPlaza = m_GameUserList.OnGetMobliePlazaCount();
		DWORD AllRecharge = m_GameUserList.OnGetUserRecharge();
		UserLine.Format("人数:%d;手厅:%d;手机:%d(牛:%d)(鱼:%d);在线充值:%d",UserOnLine,nMPlaza,nMobileOnLine,nMobileOx,nMobileFish,AllRecharge);
		m_AllUserOnLine.SetWindowText(UserLine);
	}

}

void CGameUserListDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetClientRect(&rect);

	SCROLLINFO scrollinfo;
// 	scrollinfo.cbSize = sizeof (SCROLLINFO) ; 
// 	scrollinfo.fMask  = SIF_RANGE | SIF_PAGE ; 
// 	scrollinfo.nMin = 0 ; 
// 	scrollinfo.nMax = rect.Width() - 1 ; 
// 	scrollinfo.nPage = 1 ;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
	switch (nSBCode) 
	{ 
	case SB_LEFT: 
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMin)*10,0); 
		scrollinfo.nPos = scrollinfo.nMin; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_RIGHT: 
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMax)*10,0); 
		scrollinfo.nPos = scrollinfo.nMax; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_LINELEFT: 
		scrollinfo.nPos -= 1; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(10,0); 
		break; 
	case SB_LINERIGHT: 
		scrollinfo.nPos += 1; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(-10,0); 
		break; 
	case SB_PAGELEFT: 
		scrollinfo.nPos -= 5; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(10*5,0); 
		break; 
	case SB_PAGERIGHT: 
		scrollinfo.nPos += 5; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(-10*5,0); 
		break; 
	case SB_THUMBPOSITION: 
		break; 
	case SB_THUMBTRACK: 
		ScrollWindow((scrollinfo.nPos-nPos)*10,0); 
		scrollinfo.nPos = nPos; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_ENDSCROLL: 
		break; 
	} 

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar); 
}

void CGameUserListDlg::OnBnClickedChtanking()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = m_ChTanking.GetCheck();
	if (state==1)
	{
		//	m_ChTanking.SetWindowText("关闭");
		m_EdTanking.EnableWindow(TRUE);
		m_EdServerRate.EnableWindow(TRUE);
		m_BtTanking.EnableWindow(TRUE);

	}else
	{
		//		m_ChTanking.SetWindowText("启用");
		m_EdTanking.EnableWindow(FALSE);
		m_EdServerRate.EnableWindow(FALSE);
		m_BtTanking.EnableWindow(FALSE);
	}
}

void CGameUserListDlg::OnBnClickedBttanking()
{
	//return;
	// TODO: 在此添加控件通知处理程序代码
	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	m_StState.SetWindowText(" 已启用!");
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->OnSetTanking();
	}
}

WORD CGameUserListDlg::SetTanking(BYTE cbBuffer[], WORD wBufferSize)
{
	tagUMSysGameSet* ptagUMSysGameSet = (tagUMSysGameSet*)cbBuffer;
	
	if (m_GameServerItem == NULL)
	{
		AfxMessageBox("没有选择游戏!");
		return 0;
	}
	int state = m_StorageEnable.GetCheck();
	if (state == 1)
	{
		DWORD result = MessageBox("是否关闭库存，启用放水？（放水只对默认用户有效）",NULL,MB_YESNO);
		if (result==IDYES)
		{
			m_StorageEnable.SetCheck(0);
			OnBnClickedStroageSet();
		}else
			return 0;
	}

//	m_ServerID = m_GameServerItem->m_GameServer.wServerID;
	ptagUMSysGameSet->dwServerID = CMissionList::GetInstance()->m_ServerID;

	CString szTanking,szRate;
	GetDlgItemText(IDC_EDTANKING,szTanking);
	GetDlgItemText(IDC_EDSERVER_RATE,szRate);
	if (_ttoi(szRate)<0||_ttoi(szRate)>200)
	{
		AfxMessageBox("概率为0到200！");

		return 0;
	}
	ptagUMSysGameSet->TankingScore = _ttoi64(szTanking);
	ptagUMSysGameSet->dwServerRate = _ttoi(szRate);


	return sizeof(tagUMSysGameSet);
}

bool CGameUserListDlg::GetTankingDataInfo(tagUMSysGameSet* ptagUMSysGameSet)
{
	CString szTodayScore,szTodayTankingScore,szTankingScore,szCurTankingScore,szdwServerRate;
	m_ServerID = CMissionList::GetInstance()->m_ServerID;
	if (m_IsTanking == 2 && m_ServerID == ptagUMSysGameSet->dwServerID)
	{
		if (ptagUMSysGameSet->CurTankingScore >= ptagUMSysGameSet->TankingScore)
		{
			m_StState.SetWindowText(" 已停止!");
		}else
			m_StState.SetWindowText(" 已启用!");


		szTodayScore.Format(_T("当天累计输赢: %lld"),ptagUMSysGameSet->TodayScore);
		szTodayTankingScore.Format(_T("当天累计放水: %lld"),ptagUMSysGameSet->TodayTankingScore);
		szCurTankingScore.Format(_T("当前放水: %lld"),ptagUMSysGameSet->CurTankingScore);
		szTankingScore.Format(_T("%lld"),ptagUMSysGameSet->TankingScore);
		szdwServerRate.Format(_T("%d"),ptagUMSysGameSet->dwServerRate);

		m_StTodayTankingScore.ShowWindow(SW_SHOW);
		m_StTodayScore.ShowWindow(SW_SHOW);
		m_EdTanking.EnableWindow(TRUE);
		m_StTodayScore.SetWindowText(szTodayScore);
		m_StTodayTankingScore.SetWindowText(szTodayTankingScore);
		m_StCurTankingScore.SetWindowText(szCurTankingScore);
		m_StServerRate.SetWindowText("放水概率:");

		m_EdTanking.SetWindowText(szTankingScore);
		m_EdServerRate.SetWindowText(szdwServerRate);

		if (ptagUMSysGameSet->dwServerID >= 80)
		{
			m_EdTanking.EnableWindow(FALSE);
			m_StServerRate.SetWindowText("击中概率:");
			m_StCurTankingScore.SetWindowText("击中概率:1为最难,100为最容易!");
			m_StTodayTankingScore.ShowWindow(SW_HIDE);
			//m_StTodayScore.ShowWindow(SW_HIDE);
		}
	}else if (m_IsTanking == 0 && m_ServerID == ptagUMSysGameSet->dwServerID)
	{
		szTodayScore.Format(_T("当天累计输赢: %lld"),ptagUMSysGameSet->TodayScore);
		szTodayTankingScore.Format(_T("当天累计放水: %lld"),ptagUMSysGameSet->TodayTankingScore);
		szCurTankingScore.Format(_T("当前放水: %lld"),ptagUMSysGameSet->CurTankingScore);
		szTankingScore.Format(_T("%lld"),ptagUMSysGameSet->TankingScore);
		szdwServerRate.Format(_T("%d"),ptagUMSysGameSet->dwServerRate);

		m_StTodayTankingScore.ShowWindow(SW_SHOW);
		m_StTodayScore.ShowWindow(SW_SHOW);
	//	m_EdTanking.EnableWindow(TRUE);
		m_StTodayScore.SetWindowText(szTodayScore);
		m_StTodayTankingScore.SetWindowText(szTodayTankingScore);
		m_StCurTankingScore.SetWindowText(szCurTankingScore);
		m_StServerRate.SetWindowText("放水概率:");

		m_EdTanking.SetWindowText(szTankingScore);
		m_EdServerRate.SetWindowText(szdwServerRate);

		if (ptagUMSysGameSet->dwServerID >= 80)
		{
			m_EdTanking.EnableWindow(FALSE);
			m_StServerRate.SetWindowText("击中概率:");
			m_StCurTankingScore.SetWindowText("击中概率:1为最难,100为最容易!");
			m_StTodayTankingScore.ShowWindow(SW_HIDE);
			//m_StTodayScore.ShowWindow(SW_HIDE);
		}
	}
// 	else{
// 		m_StTodayScore.SetWindowText("当天累计输赢:");
// 		m_StTodayTankingScore.SetWindowText("当天累计放水:");
// 		m_StCurTankingScore.SetWindowText("当前放水:");
// 
// 		m_EdTanking.SetWindowText("");
// 		m_EdServerRate.SetWindowText("");
// 	}


	return true;
}

bool CGameUserListDlg::OnSerachOffLineUser(tagUMUserScoreSet * pUserInfo)
{
	/*m_GameUserList.DeleteAllItems();*/
	
	CUserInfoItem* pCUserInfoItem = new CUserInfoItem;

	CopyMemory(&pCUserInfoItem->m_tagUMUserScoreSet,pUserInfo,sizeof(tagUMUserScoreSet));

	m_GameUserList.OnGameUserInfoInsert(pCUserInfoItem);

	return true;
}

bool CGameUserListDlg::OnInsetWarnningDataBase(tagLog* ptagLog)
{
	m_LookUpRhEd.InsertString(ptagLog->szLog,RGB(0,0,0));

	m_LookUpRhEd.InsertString(TEXT("\r\n"),RGB(0,0,0));

	return true;
}

bool CGameUserListDlg::OnInsertTransferScoreInfo(tagTransferScore* pTransferInfo)
{
	

	tagTranferInfo* plTranferInfo = NULL;
	CTranferUserInfo::iterator it = m_lTranferInfoMap.find(pTransferInfo->dwUserID);
	if (it == m_lTranferInfoMap.end())
	{
		plTranferInfo = new tagTranferInfo;
		plTranferInfo->UserId = pTransferInfo->dwUserID;
		plTranferInfo->GameID = pTransferInfo->dwGameID;
		plTranferInfo->NickName.Format("%s",pTransferInfo->szNikeName);
		m_lTranferInfoMap.insert(std::make_pair(plTranferInfo->UserId,plTranferInfo));
	}

	CTranferUserInfo::iterator itor = m_lTranferInfoMap.find(pTransferInfo->dwTargetUserID);
	if (itor == m_lTranferInfoMap.end())
	{
		plTranferInfo = new tagTranferInfo;
		plTranferInfo->UserId = pTransferInfo->dwTargetUserID;
		plTranferInfo->GameID = pTransferInfo->dwTargetGameID;
		plTranferInfo->NickName.Format("%s",pTransferInfo->szTargetNikeName);
		m_lTranferInfoMap.insert(std::make_pair(plTranferInfo->UserId,plTranferInfo));
	}

	CString szuserid,sztargetuserid,sznickname,sztargetnickname,transferscore;
	CString szgameid,sztargetgameid;
	sznickname.Format("%s(%ld)",pTransferInfo->szNikeName,pTransferInfo->dwGameID);
	sztargetnickname.Format("%s(%ld)",pTransferInfo->szTargetNikeName,pTransferInfo->dwTargetGameID);
	transferscore.Format("%I64d",pTransferInfo->lScore);
	
// 	//插入换行
// 	LONG lTextLength=m_RichEd.GetWindowTextLength();
// 	if (lTextLength!=0L) m_RichEd.InsertString(TEXT("\r\n"),RGB(0,0,0));

	m_RichEd.InsertString(TEXT("［"),RGB(0,0,0));
	m_RichEd.InsertHyperLink(sznickname);
	m_RichEd.InsertString(TEXT("］"),RGB(0,0,0));

	m_RichEd.InsertString("转给",RGB(0,0,0));

	m_RichEd.InsertString(TEXT("［"),RGB(0,0,0));
	m_RichEd.InsertHyperLink(sztargetnickname);
	m_RichEd.InsertString(TEXT("］"),RGB(0,0,0));

	m_RichEd.InsertString(transferscore,RGB(255,0,0));

	m_RichEd.InsertString(TEXT("\r\n"),RGB(0,0,0));


	return true;
}

CString CGameUserListDlg::OnGetUserID(CString strUserInfo)
{
	CString strLine,strNickName,strUserID;

	char* pszTmp = strUserInfo.GetBuffer(0);
	char* psz = strrev(pszTmp);
	strUserInfo = psz;

	int iLen = strUserInfo.GetLength();
	int iSpaceIndex = strUserInfo.Find("(");

	strLine = strUserInfo.Left(iSpaceIndex);

	strNickName = strUserInfo.Right(iLen-iSpaceIndex-1);

	iLen = strLine.GetLength();
	iSpaceIndex = strLine.Find(")");

	strUserID = strLine.Right(iLen - iSpaceIndex - 1);

	pszTmp = strUserID.GetBuffer(0);
	psz = strrev(pszTmp);
	strUserInfo = psz;

	return strUserInfo;
}

void CGameUserListDlg::OnEnLinkRichedit21(NMHDR *pNMHDR, LRESULT *pResult)
{
	ENLINK *pEnLink = reinterpret_cast<ENLINK *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString szTransferText;
	CHAR    szLink[128];
	CString szTmplink;
	CString gameID;
	CString userID;
	switch(pNMHDR->code)
	{
	case EN_LINK:
		{
			switch(pEnLink->msg)
			{
			case WM_LBUTTONUP:
				{
					m_RichEd.SetSel(pEnLink->chrg);
					m_RichEd.GetSelText(szLink);
					szTmplink.Format("%s",szLink);

					gameID = OnGetUserID(szTmplink);

					CTranferUserInfo::iterator it = m_lTranferInfoMap.begin();
					for (it;it != m_lTranferInfoMap.end();it++)
					{
						if (it->second->GameID == _ttoi(gameID))
						{
							userID.Format("%ld",it->first);
							if (CUserServerInfo::GetInstance()->OnSerachUser(userID)==false)
							{
								//AfxMessageBox("用户不在线!");
								CMissionUserInfo::GetInstance()->OnSreachOffLineUser(userID);
							}
							break;
						}
					}

// 					if (CUserServerInfo::GetInstance()->OnSerachUser(userID)==false)
// 					{
// 						AfxMessageBox("用户不在线!");
// 	//					CMissionUserInfo::GetInstance()->OnSreachOffLineUser(userID);
// 					}
					break;
				}
			}

			break;
		}
	}
}

void CGameUserListDlg::OnBnClickedButtonSwichting()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_IsHide == false)
	{
		m_XGroupBox.ShowWindow(SW_SHOW);
		m_Game.ShowWindow(SW_HIDE);
		m_Win.ShowWindow(SW_HIDE);
		m_Lose.ShowWindow(SW_HIDE);
		m_WWin.ShowWindow(SW_HIDE);
		m_WLose.ShowWindow(SW_HIDE);

		m_GameEvent.ShowWindow(SW_HIDE);
		m_WinScore.ShowWindow(SW_HIDE);
		m_LoseScore.ShowWindow(SW_HIDE);
		m_WarningWin.ShowWindow(SW_HIDE);
		m_WarningLose.ShowWindow(SW_HIDE);
//		m_WinOrLoseRate.ShowWindow(SW_HIDE);
		m_SysSet.ShowWindow(SW_HIDE);

		m_TankingGroup.ShowWindow(SW_SHOW);

		m_StTodayScore.ShowWindow(SW_SHOW);
		m_StTodayTankingScore.ShowWindow(SW_SHOW);
		m_StCurTankingScore.ShowWindow(SW_SHOW);
		m_StTanking.ShowWindow(SW_SHOW);
		m_EdTanking.ShowWindow(SW_SHOW);
		m_StServerRate.ShowWindow(SW_SHOW);
		m_EdServerRate.ShowWindow(SW_SHOW);
		//m_ChTanking.ShowWindow(SW_HIDE);
		m_BtTanking.ShowWindow(SW_SHOW);
		m_StState.ShowWindow(SW_SHOW);

		m_LookUpRhEd.ShowWindow(SW_SHOW);

		m_btAndroidCount.ShowWindow(SW_HIDE);
		m_EdAndroidCount.ShowWindow(SW_HIDE);

		m_IsHide = true;
	}else
	{
		m_XGroupBox.ShowWindow(SW_HIDE);
		m_Game.ShowWindow(SW_SHOW);
		m_Win.ShowWindow(SW_SHOW);
		m_Lose.ShowWindow(SW_SHOW);
		m_WWin.ShowWindow(SW_SHOW);
		m_WLose.ShowWindow(SW_SHOW);

		m_GameEvent.ShowWindow(SW_SHOW);
		m_WinScore.ShowWindow(SW_SHOW);
		m_LoseScore.ShowWindow(SW_SHOW);
		m_WarningWin.ShowWindow(SW_SHOW);
		m_WarningLose.ShowWindow(SW_SHOW);
//		m_WinOrLoseRate.ShowWindow(SW_SHOW);
		m_SysSet.ShowWindow(SW_SHOW);

		m_TankingGroup.ShowWindow(SW_HIDE);

		m_StTodayScore.ShowWindow(SW_HIDE);
		m_StTodayTankingScore.ShowWindow(SW_HIDE);
		m_StCurTankingScore.ShowWindow(SW_HIDE);
		m_StTanking.ShowWindow(SW_HIDE);
		m_EdTanking.ShowWindow(SW_HIDE);
		m_StServerRate.ShowWindow(SW_HIDE);
		m_EdServerRate.ShowWindow(SW_HIDE);
		//m_ChTanking.ShowWindow(SW_SHOW);
		m_BtTanking.ShowWindow(SW_HIDE);
		m_StState.ShowWindow(SW_HIDE);

		m_LookUpRhEd.ShowWindow(SW_HIDE);

		m_btAndroidCount.ShowWindow(SW_SHOW);
		m_EdAndroidCount.ShowWindow(SW_SHOW);

		m_IsHide = false;
	}
}

VOID CGameUserListDlg::OnSetAndroidCount(tagAndroidCount* ptagAndroidCount)
{
	CString cbAndroidCount;
	cbAndroidCount.Format("%d",ptagAndroidCount->nAndroidCount);

	m_EdAndroidCount.SetWindowText(cbAndroidCount);

	CServerListData* pCServerListData = CServerListData::GetInstance();
	m_GameServerItem = pCServerListData->SearchGameServer(ptagAndroidCount->dwServerID); 

	LPCTSTR m_GameName = m_GameServerItem->m_GameServer.szServerName;

	CString szInfo;
	szInfo.Format("已经为 %s 添加 %d 个机器人！",m_GameName,ptagAndroidCount->nAndroidCount);
	// 	if (ptagAndroidCount->dwServerID != 0 && m_IsSetAndroid == true)
	// 	{
	// 		m_IsSetAndroid = false;
	 //		AfxMessageBox(szInfo);
	// 	}
}

void CGameUserListDlg::OnBnClickedBtAndroidcount()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cbAndroidCount;
	GetDlgItemText(IDC_ANDROIDCOUNT,cbAndroidCount);
	// TODO: 在此添加控件通知处理程序代码
	WORD ServerID = 0;
	ServerID = CMissionList::GetInstance()->m_ServerID;
	if (ServerID == 0 || m_GameServerItem ==NULL || cbAndroidCount=="")
	{
		AfxMessageBox("没有选择游戏！请选择要添加机器人的游戏房间");

		return;
	}

	// 	if (m_IsSetAndroid == false)
	// 	{
	// 		m_IsSetAndroid = true;
	// 	}

	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();

	INT wAndroidCount = _ttoi(cbAndroidCount);
	pMissionUserInfo->OnSetAndroidCount(wAndroidCount,ServerID);

	CServerListData* pCServerListData = CServerListData::GetInstance();
	m_GameServerItem = pCServerListData->SearchGameServer(ServerID); 

	LPCTSTR m_GameName = m_GameServerItem->m_GameServer.szServerName;

	CString szInfo;
	szInfo.Format("已经为 %s 添加 %d 个机器人！",m_GameName,wAndroidCount);

	AfxMessageBox(szInfo);
}
