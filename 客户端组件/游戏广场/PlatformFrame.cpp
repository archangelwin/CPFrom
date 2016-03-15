#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgEnquire.h"
#include "DlgSearchUser.h"
#include "PlatformFrame.h"
#include ".\platformframe.h"
#include "MessagePop.h"
#include "DlgMobileBind.h"
#include "DlgLockMachine.h"
#include "DlgService.h"
#include "VerifyInsurePass.h"

//////////////////////////////////////////////////////////////////////////////////

//圆角大小手机拔掉
#define ROUND_CX					4									//圆角宽度
#define ROUND_CY					4									//圆角高度

//屏幕位置
#define BORAD_SIZE					5									//边框大小
#define CAPTION_SIZE				79									//标题大小

//屏幕限制
//#define LESS_LIST_CX				267/*285*/									//列表宽度
#define LIST_HALL_SPACE             6
#define LESS_LIST_CX				266+4									//列表宽度
#define SPLITTER_WIDTH				0									//拆分宽度

//屏幕限制
#define LESS_SCREEN_CY				740									//最小高度
#define LESS_SCREEN_CX				1024								//最小宽度

//////////////////////////////////////////////////////////////////////////////////

//控制按钮
#define IDC_MIN						100									//最小按钮
#define IDC_MAX						101									//最大按钮
#define IDC_SKIN					102									//皮肤按钮
#define IDC_CLOSE					103									//关闭按钮
#define IDC_CERTIFICATE		    	104									//证件

//控制按钮
#define IDC_CONTROL					110									//控制按钮
#define IDC_LOCK_LIST				111									//锁定按钮

//控件标识
#define IDC_SERVER_LIST				300									//游戏列表
#define IDC_WEB_PUBLICIZE			301									//浏览控件
#define IDC_SKIN_SPLITTER			302									//拆分控件
#define IDC_SYSTEM_TRAY_ICON		303									//任务图标
#define IDC_BUTTON_GAMELIST			304								    //游戏
#define IDC_BUTTON_GAMEMATCH		305									//比赛

//控件标识
#define IDC_VIEW_ITEM_CTRL			310									//子项框架
#define IDC_USER_INFO_CTRL			311									//用户信息
#define IDC_MATCH_LIST              299                                 //游戏列表

//范围按钮
#define IDC_PLATFORM				400									//平台按钮
#define IDC_NAVIGATION				500									//导航按钮

//////////////////////////////////////////////////////////////////////////////////

//房间数目
#define MAX_SERVER_COUNT			5									//房间数目

//时间标识
#define IDI_FLASH_TRAY_ICON			10									//闪动图标
#define IDI_MESSAGE_POP				11									//公告内容
#define IDI_CLOSE_PAZZA				12									//关闭客户端
#define IDI_REM_INSUREPASS			13									//保存保险柜密码

//时间标识
#define IDI_TIMER_WEB               17
#define IDI_UPDATA_ONLINE			16									//更新人数
#define TIME_UPDATA_ONLINE			10000								//更新人数

//////////////////////////////////////////////////////////////////////////////////

#define IDM_RESTORE                 106                                 //还原显示
#define IDM_MINIMIZE                107                                 //最小化显示
#define IDM_MAXIMIZE                108                                 //最大化显示

//////////////////////////////////////////////////////////////////////////////////

#define WM_INSUREPLAZA_UPDATA      (WM_USER+1680)                       //银行更新消息
#define WM_INSTALL_CANCEL_EVENT     8888                                //安装事件

struct tagInsurePlazaUpdata
{
	SCORE  lUserScore;
	SCORE  lUserInsure;
};

//////////////////////////////////////////////////////////////////////////////////
//静态变量

CPlatformFrame * CPlatformFrame::m_pPlatformFrame=NULL;					//框架指针

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)

	//系统消息
//	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_GETMINMAXINFO()
	ON_WM_SETTINGCHANGE()

	//按钮消息
	ON_BN_CLICKED((IDC_PLATFORM+0), OnBnClickedPlatform1)
//	ON_BN_CLICKED((IDC_PLATFORM+1), OnBnClickedPlatform2)
	ON_BN_CLICKED((IDC_PLATFORM+2), OnBnClickedPlatform3)

	//自定消息
	ON_MESSAGE(WM_HOTKEY, OnMessageHotKey)
	ON_MESSAGE(WM_TRAY_ICON, OnMessageTrayIcon)
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)
	ON_MESSAGE(WM_INSTALL_CANCEL_EVENT, OnMessageInstallCancelEvent)

	//自定消息
	ON_MESSAGE(WM_INSUREPLAZA_UPDATA, OnMessageInsurePlazaEvent)
	ON_MESSAGE(WM_SAFA_BIND,OnSafeBind)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CListEncircle::CListEncircle()
{
}

//析构函数
CListEncircle::~CListEncircle()
{
}

//绘画处理
bool CListEncircle::PreDrawEncircleImage(tagEncircleBMP & EncircleImage)
{
	return true;
	//变量定义
	CDC * pDCL=CDC::FromHandle(EncircleImage.ImageTL.GetDC());
	CDC * pDCM=CDC::FromHandle(EncircleImage.ImageTM.GetDC());
	CDC * pDCR=CDC::FromHandle(EncircleImage.ImageTR.GetDC());
		
// 	CPngImageSB StationQQ;
// 	StationQQ.LoadImage(AfxGetInstanceHandle(),TEXT("QQ_INFO"));
// 	StationQQ.DrawImage(pDCR,30,0);
	//加载资源
	CPngImageSB ListTitleL;
	CPngImageSB ListTitleM;
	CPngImageSB ListTitleR;
	ListTitleL.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_L"));
	ListTitleM.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_M"));
	ListTitleR.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_R"));

	//构造资源
	//ListTitleL.DrawImage(pDCL,0,0);
	//ListTitleM.DrawImage(pDCM,0,0);
	//ListTitleR.DrawImage(pDCR,0,0);
	

	//释放资源
	EncircleImage.ImageTL.ReleaseDC();
	EncircleImage.ImageTM.ReleaseDC();
	EncircleImage.ImageTR.ReleaseDC();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CFrameEncircle::CFrameEncircle()
{
}

//析构函数
CFrameEncircle::~CFrameEncircle()
{
}

//绘画处理
bool CFrameEncircle::PreDrawEncircleImage(tagEncircleBMP & EncircleImage)
{
	//变量定义
	CDC * pDC=CDC::FromHandle(EncircleImage.ImageTL.GetDC());
	CDC * pDCR = CDC::FromHandle(EncircleImage.ImageTR.GetDC());

// 	CRect rcClient;
// 	GetClientRect(,&rcClient);
	//加载资源
	CPngImageSB StationLogo;
	CPngImageSB StationSmallLogo;
	CPngImageSB StationQQ;
	StationSmallLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_SMALL_LOGO"));
	StationLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_LOGO"));
	StationQQ.LoadImage(AfxGetInstanceHandle(),TEXT("QQ_INFO"));

	pDC->SetTextColor(RGB(255,255,255));
	//pDC->TextOut(28,7,TEXT("龙马游棋牌·业界资质认证齐全：中国好棋牌"));
	//构造标志
	StationSmallLogo.DrawImage(pDC,2,2);
	StationLogo.DrawImage(pDC,10,16);
	StationQQ.DrawImage(pDCR,320,40);
	EncircleImage.ImageTL.ReleaseDC();
	EncircleImage.ImageTR.ReleaseDC();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPlatformFrame::CPlatformFrame()
{
	//界面变量
	m_bMaxShow=false;
	m_bRectify=false;
	m_rcNormalSize.SetRect(0,0,0,0);
	m_dwAllOnLineCount=0;

	//状态变量
	m_bWhisperIcon=false;
	m_bHideGameList=false;
	m_bLockGameList=false;
	m_bAutoMenuEnable=FALSE;

	//房间变量
	m_pServerViewItem=NULL;

	//任务组件
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);

	//平台变量
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

	//设置接口
	CCustomFaceManager * pCustomFaceManager=CCustomFaceManager::GetInstance();
	pCustomFaceManager->SetCustomFaceEvent(QUERY_OBJECT_PTR_INTERFACE(this,IUnknownEx));

	//子项资源
	tagEncircleResource	EncircleItem;
	EncircleItem.pszImageTL=MAKEINTRESOURCE(IDB_ITEM_FRAME_TL);
	EncircleItem.pszImageTM=MAKEINTRESOURCE(IDB_ITEM_FRAME_TM);
	EncircleItem.pszImageTR=MAKEINTRESOURCE(IDB_ITEM_FRAME_TR);
	EncircleItem.pszImageML=MAKEINTRESOURCE(IDB_ITEM_FRAME_ML);
	EncircleItem.pszImageMR=MAKEINTRESOURCE(IDB_ITEM_FRAME_MR);
	EncircleItem.pszImageBL=MAKEINTRESOURCE(IDB_ITEM_FRAME_BL);
	EncircleItem.pszImageBM=MAKEINTRESOURCE(IDB_ITEM_FRAME_BM);
	EncircleItem.pszImageBR=MAKEINTRESOURCE(IDB_ITEM_FRAME_BR);
	m_ItemEncircle.InitEncircleResource(EncircleItem,AfxGetInstanceHandle());

	//列表资源
	tagEncircleResource	EncircleList;
	EncircleList.pszImageTL=MAKEINTRESOURCE(IDB_SERVER_LIST_TL);
	EncircleList.pszImageTM=MAKEINTRESOURCE(IDB_SERVER_LIST_TM);
	EncircleList.pszImageTR=MAKEINTRESOURCE(IDB_SERVER_LIST_TR);
	EncircleList.pszImageML=MAKEINTRESOURCE(IDB_SERVER_LIST_ML);
	EncircleList.pszImageMR=MAKEINTRESOURCE(IDB_SERVER_LIST_MR);
	EncircleList.pszImageBL=MAKEINTRESOURCE(IDB_SERVER_LIST_BL);
	EncircleList.pszImageBM=MAKEINTRESOURCE(IDB_SERVER_LIST_BM);
	EncircleList.pszImageBR=MAKEINTRESOURCE(IDB_SERVER_LIST_BR);
	m_ListEncircle.InitEncircleResource(EncircleList,AfxGetInstanceHandle());

	//框架环绕
	tagEncircleResource	EncircleFrame;
	EncircleFrame.pszImageTL=MAKEINTRESOURCE(IDB_FRAME_TL);
	EncircleFrame.pszImageTM=MAKEINTRESOURCE(IDB_FRAME_TM);
	EncircleFrame.pszImageTR=MAKEINTRESOURCE(IDB_FRAME_TR);
	EncircleFrame.pszImageML=MAKEINTRESOURCE(IDB_FRAME_ML);
	EncircleFrame.pszImageMR=MAKEINTRESOURCE(IDB_FRAME_MR);
	EncircleFrame.pszImageBL=MAKEINTRESOURCE(IDB_FRAME_BL);
	EncircleFrame.pszImageBM=MAKEINTRESOURCE(IDB_FRAME_BM);
	EncircleFrame.pszImageBR=MAKEINTRESOURCE(IDB_FRAME_BR);
	m_FrameEncircle.InitEncircleResource(EncircleFrame,AfxGetInstanceHandle());

	m_wAVServerPort=0;
	m_dwAVServerAddr=0;
	m_pInsurePlaza = NULL;
	m_bShowVerify = true;

	return;
}

//析构函数
CPlatformFrame::~CPlatformFrame()
{
	//平台变量
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) 
		m_pPlatformFrame=NULL;

	if (m_pInsurePlaza!=NULL)
	{
		SafeDelete(m_pInsurePlaza);
		m_pInsurePlaza = NULL;
	}
	return;
}

//接口查询
VOID * CPlatformFrame::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ICustomFaceEvent,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ICustomFaceEvent,Guid,dwQueryVer);
	return NULL;
}

//子项事件
VOID CPlatformFrame::OnViewItemEvent(WORD wItemIndex, CWnd * pItemView)
{
	//房间控制
	bool bShowList=true;
	bool bPlazaView=(m_PlazaViewItem.m_hWnd==pItemView->GetSafeHwnd());

	//房间判断
	if (bPlazaView==false) bShowList=m_bLockGameList;

	//列表控制
	ControlServerList((bShowList==true)?ServerListControl_Show:ServerListControl_Hide,false);

	return;
}

//拆分事件
VOID CPlatformFrame::OnSplitterEvent(UINT uControlID, INT nXPos, INT nYPos)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//显示控件
	if (m_bHideGameList==true)
	{
		//设置变量
		m_bRectify=true;
		m_bHideGameList=false;
	
		//设置按钮
		HINSTANCE hInstance=AfxGetInstanceHandle();
		//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,(m_bHideGameList==true)?TEXT("BT_GAME_LIST_SHOW"):TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);
	}

	//调整控件
	RectifyControl(rcClient.Width(),rcClient.Height());

	return;
}

//下载失败
VOID CPlatformFrame::OnEventSystemFace(DWORD dwUserID, WORD wFaceID)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//自我数据
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//设置变量
		pGlobalUserData->wFaceID=wFaceID;

		//清理数据
		pGlobalUserData->dwCustomID=0L;
		ZeroMemory(&pGlobalUserData->CustomFaceInfo,sizeof(pGlobalUserData->CustomFaceInfo));

		//发送事件
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	return;
}

//头像数据
VOID CPlatformFrame::OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//自我数据
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//设置变量
		pGlobalUserData->dwCustomID=dwCustomID;
		CopyMemory(&pGlobalUserData->CustomFaceInfo,&CustomFaceInfo,sizeof(CustomFaceInfo));

		//发送事件
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	//当前房间
	if (m_pServerViewItem!=NULL)
	{
		m_pServerViewItem->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	//更新房间
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		m_ServerViewItemArray[i]->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	return;
}

//消息过虑
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//命令函数
BOOL CPlatformFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);

	//功能按钮
	switch (nCommandID)
	{
	case IDC_BUTTON_GAMEMATCH:
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			m_btGameList.SetButtonImage(IDB_BT_GAMELIST1,hInstance,true,false);
			m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH,hInstance,true,false);
			m_ServerListView.ShowWindow(SW_HIDE);
			m_ServerMatchList.ShowWindow(SW_SHOW);
			return TRUE;
		}
	case  IDC_BUTTON_GAMELIST:
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			m_btGameList.SetButtonImage(IDB_BT_GAMELIST,hInstance,true,false);
			m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH1,hInstance,true,false);
			m_ServerMatchList.ShowWindow(SW_HIDE);
			m_ServerListView.ShowWindow(SW_SHOW);
			return TRUE;
		}
	case IDC_MIN:				//最小按钮
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_MAX:				//最大按钮
		{
			//窗口控制
			if (m_bMaxShow==true)
			{
				RestoreWindow();
			}
			else
			{
				MaxSizeWindow();
			}

			//更新界面
			RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW);

			return TRUE;
		}
	case IDC_CLOSE:				//关闭按钮
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_SKIN:				//界面控制
		{
			//创建窗口
			if (m_DlgSkinControl.m_hWnd==NULL)
			{
				m_DlgSkinControl.Create(IDD_SKIN_CONTROL,this);
			}

			//获取位置
			CRect rcButton;
			CRect rcControl;
			m_btSkin.GetWindowRect(&rcButton);
			m_DlgSkinControl.GetWindowRect(&rcControl);

			//显示窗口
			UINT uFlags=SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;
			m_DlgSkinControl.SetWindowPos(NULL,rcButton.right-rcControl.Width(),rcButton.bottom,0,0,uFlags);

			return TRUE;
		}
	case IDC_CONTROL:			//控制按钮
		{
			//控制列表
			ControlServerList(ServerListControl_Turn,true);

			return TRUE;
		}
	case IDC_LOCK_LIST:			//锁定列表
		{
			//设置变量
			//m_bLockGameList=!m_bLockGameList;

			////设置按钮
			//HINSTANCE hInstance=AfxGetInstanceHandle();
			//m_btLockList.SetButtonImage(IDB_BK_LIST,(m_bLockGameList==true)?TEXT("BT_UNLOCK_LIST"):TEXT("BT_LOCK_LIST"),hInstance,true,false);

			return TRUE;
		}
	case IDC_NAVIGATION+2:
		{
			if(m_ServerViewItemArray.GetCount()<1)
			{
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				UINT wServerID = pGlobalServer->GetPlatInfo("PlatInfo","GSerVerID",0);
				if (wServerID>0)
				{
					CServerListData * pServerListData=CServerListData::GetInstance();
					if (pServerListData!=NULL) 
					{
						CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
						if (pGameServerItem!=NULL) 
						{
							EntranceServerItem(pGameServerItem,true);
							return true;
						}
					}
				}
			}
			OpenInSureDlg();
			return TRUE;
		}
	case IDC_NAVIGATION+0:
		{
			PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

			return TRUE;
		}
	case IDC_NAVIGATION+1:
		{
			//变量定义
 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
 			//构造地址
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			TCHAR szPayServer[MAX_PATH]=TEXT("");
			CString sPayUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"PayServer",szPayServer,MAX_PATH);
	
 			//连接地址
 			WebBrowse(sPayUrl,true);
 
 			return TRUE;
		}
	case IDC_NAVIGATION+3:       //商城按钮
		{
			//变量定义
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//构造地址
// 			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),pGlobalServer->GetPlatformServer(3),(nCommandID-IDC_NAVIGATION)+1);
// 
// 			//连接地址
// 			WebBrowse(szNavigation,true);

			//个人设置
// 			CDlgService DlgService;
// 			DlgService.DoModal();
			//CInformation Information(this);
			//Information.ShowMessageBox(TEXT("商城系统维护中，敬请期待！"),MB_ICONINFORMATION,10);

			//打开页面
			//构造地址
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			TCHAR szBrowseUrl[256]=TEXT("");
			_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/Shop/MallClient.aspx?type=0"),pGlobalServer->GetPlatformServer(3));

			CMessagePop DlgMobileBind ;
			DlgMobileBind.SetWindowSize(695,540,695,/*210-107+100*/540);
			DlgMobileBind.InitWebDlg(szBrowseUrl,"游戏商城",true,false,0);
			//CDlgMobileBind DlgMobileBind;
			DlgMobileBind.DoModal();

			//构造地址
			//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			//TCHAR szNavigation[256]=TEXT("");
			//_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Shop/OnLineMall.aspx"),pGlobalServer->GetPlatformServer(3));
			//CMessagePop DlgMobileBind ;
			//DlgMobileBind.SetWindowSize(700,490,700,/*210-107+100*/450);
			//DlgMobileBind.InitWebDlg(szNavigation,"游戏商城",true,false,0);
			//DlgMobileBind.DoModal();

			return TRUE;
		}
	case IDC_NAVIGATION+4:		//联系客服
		{

			ASSERT(CParameterGlobal::GetInstance()!=NULL);
			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

			//联系客服
			TCHAR szService[MAX_PATH]=TEXT("");
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sServiceUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"QQService",szService,MAX_PATH,false);
			//ShellExecute(NULL,TEXT("OPEN"),sServiceUrl,NULL,NULL,SW_NORMAL);
			ShellExecute(NULL,TEXT("open"), TEXT("iexplore.exe"),sServiceUrl, NULL, SW_NORMAL); 

			//构造地址
			TCHAR szNavigation[256]=TEXT("");
			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),pGlobalServer->GetPlatformServer(3));
			//连接地址
			WebBrowse(szNavigation,true);

			return TRUE;

		}
	case IDC_NAVIGATION+5://
		{
			//变量定义
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//构造地址
// 			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/AskService.aspx"),pGlobalServer->GetPlatformServer(3));
// 			//打开页面
// 			ShellExecute(NULL,TEXT("OPEN"),szNavigation,NULL,NULL,SW_NORMAL);
// 
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),pGlobalServer->GetPlatformServer(3));
// 			//连接地址
// 			WebBrowse(szNavigation,true);
			return TRUE;
		}
	}

	//菜单命令
	switch (nCommandID)
	{
	case IDM_USER_LOGON:		//用户登录
		{
			m_MissionLogon.ShowLogon();

			return TRUE;
		}
	case IDM_SWITCH_ACCOUNTS:	//切换帐号
		{
			//切换询问
			if ((m_ServerViewItemArray.GetCount()>0L)||(m_pServerViewItem!=NULL))
			{
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("所有的游戏房间即将关闭，确实要“切换帐号”吗？ "),MB_YESNO)!=IDYES) return TRUE;
			}

			//激活连接
			KillTimer(IDI_MESSAGE_POP);
			m_MissionLogon.SetLoginSocketType(2);
			//if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
			//{
				//连接失败，关闭大厅
				ClosePazza(2);
			//}
			return TRUE;
		}
	case IDM_RESTORE:   //还原
		{
			if(IsIconic())
			{
				ShowWindow(SW_RESTORE);
			}
			return TRUE;
		}
	case IDM_MINIMIZE:  //最小化
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDM_MAXIMIZE:  //最大化
		{
			if(IsIconic())
			{
				ShowWindow(SW_RESTORE);
			}
			MaxSizeWindow();
			return TRUE;
		}
	//case SC_RESTORE :
	//	{
	//		if(IsIconic())
	//		{
	//			ShowWindow(SW_RESTORE);
	//		}
	//		return TRUE;
	//	}
	}

	return __super::OnCommand(wParam,lParam);
}

VOID CPlatformFrame::OpenInSureDlg()
{
	//变量定义
	bool bGoldServer=false;
	CServerViewItem * pServerViewGold=NULL;

	//查找房间
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//获取房间
		ASSERT(m_ServerViewItemArray[i]!=NULL);
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];

		//房间类型
		WORD wServerType=pServerViewItem->GetServerType();
		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();

		//体验房
		if(CServerRule::IsTrainRoom(pServerViewItem->GetServerRule()))
		{
			//提示消息
			CInformation Information(this);
			if (Information.ShowMessageBox(TEXT("您所在的游戏房间暂不支持保险柜功能"),MB_OK|MB_ICONWARNING,10)!=IDYES)
			{
				return;
			}		
			return;
		}
		//房间判断
		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
		{
			//设置变量
			bGoldServer=true;
			pServerViewGold=pServerViewItem;

			break;
		}
	}
			//m_sRemInsurePwd = "1234567";
	if (m_sRemInsurePwd == "") //没有保存保险柜密码
	{
		CVerifyInsurePass dlgVefifyPass;
		int nRet;
		if((nRet=dlgVefifyPass.DoModal()) == 1)
		{
			int aa = 2;
		}
		else
		{
			return;
		}
	}



	//设置资源
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

	//银行中心
	if (bGoldServer==false)
	{
		//广场银行
		/*			CDlgInsurePlaza DlgInsurePlaza;
		_sntprintf(DlgInsurePlaza.m_szSaveInsurePass,CountArray(DlgInsurePlaza.m_szSaveInsurePass),m_sRemInsurePwd);
		INT_PTR nResult=DlgInsurePlaza.DoModal();*/
		if (m_pInsurePlaza!=NULL)
		{
			m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
			m_pInsurePlaza->SwitchInsureModeView(1);
			m_pInsurePlaza->QueryUserInsureInfo();
			m_pInsurePlaza->CenterWindow();
			m_pInsurePlaza->ShowWindow(SW_SHOW);
		}
		else
		{
			m_pInsurePlaza = new CDlgInsurePlaza;
			//_sntprintf(m_pInsurePlaza->m_szSaveInsurePass,CountArray(m_pInsurePlaza->m_szSaveInsurePass),m_sRemInsurePwd);
			m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
			m_pInsurePlaza->Create(424,this);
			m_pInsurePlaza->CenterWindow();
			m_pInsurePlaza->SetForegroundWindow();
			m_pInsurePlaza->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		if (m_pInsurePlaza!=NULL)
		{
			m_pInsurePlaza->DestroyWindow();
			m_pInsurePlaza= NULL;
		}
		//房间银行
		ASSERT(pServerViewGold!=NULL);
		pServerViewGold->ShowInsureView(m_sRemInsurePwd);
	}
	AfxSetResourceHandle(hInstResourceClient);
}

//调整控件
VOID CPlatformFrame::RectifyControl(INT nWidth, INT nHeight)
{
	//状态判断
	if ((nWidth==0)||(nHeight==0)) return;

	//拆分位置
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//环绕信息
	tagEncircleInfo EncircleInfoList;
	tagEncircleInfo EncircleInfoItem;
	tagEncircleInfo EncircleInfoFrame;
	m_ListEncircle.GetEncircleInfo(EncircleInfoList);
	m_ItemEncircle.GetEncircleInfo(EncircleInfoItem);
	m_FrameEncircle.GetEncircleInfo(EncircleInfoFrame);

	//获取位置
	ScreenToClient(&rcSplitter);

	//拆分控件
	if (m_bHideGameList==false)
	{
		//拆分范围
		INT nLessPos=nWidth*28/100,nMaxPos=nWidth/2;
		if (nLessPos>=LESS_LIST_CX) 
			nLessPos=LESS_LIST_CX;

		//调整拆分
		if (m_bRectify==false)
		{
			m_bRectify=true;
			rcSplitter.left=nLessPos;
			rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
		}

		//拆分范围
		m_SkinSplitter.SetSplitterRange(nLessPos,nMaxPos);

		//调整位置
		if ((nWidth!=0)&&(nHeight!=0))
		{
			if (rcSplitter.left<nLessPos)
			{
				rcSplitter.left=nLessPos;
				rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
			}
			if (rcSplitter.right>nMaxPos)
			{
				rcSplitter.right=nMaxPos;
				rcSplitter.left=rcSplitter.right-SPLITTER_WIDTH;
			}
		}
	}
	else 
	{
		//拆分位置
		rcSplitter.left=EncircleInfoFrame.nLBorder;
		rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
	}

	//位置调整
	rcSplitter.top=EncircleInfoFrame.nTBorder;
	rcSplitter.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//控件位置
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//控制按钮
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-37,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-72,1,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-98,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSkin,NULL,nWidth-130,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btCertificate,NULL,nWidth-162,3,0,0,uFlags|SWP_NOSIZE);

	//导航按钮
	CRect rcNavigation;
	m_btNavigation[0].GetWindowRect(&rcNavigation);

	//导航按钮
	INT nNavigationArea=rcNavigation.Width()*CountArray(m_btNavigation);
	INT nSpace=__min(__max((nWidth-nNavigationArea-890)/(CountArray(m_btNavigation)+1),0),30);


	//导航按钮
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		INT nIndex=CountArray(m_btNavigation)-i;
		if (nSpace == 30)
		{	
			int nSp = nSpace - 10;
			//m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,AfxGetInstanceHandle(),true,false);	
			//m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION3,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,AfxGetInstanceHandle(),true,false);
			
			INT nXExcursion=nWidth-(rcNavigation.Width()+nSp)*nIndex-nSp-215-55+120;
			DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,32,0,0,uFlags|SWP_NOSIZE);
		}else
		{
			//m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,AfxGetInstanceHandle(),true,false);	
			//m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION3,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,AfxGetInstanceHandle(),true,false);
			
			INT nXExcursion=nWidth-(rcNavigation.Width()+nSpace+17)*nIndex-nSpace-210;
			DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,32,0,0,uFlags|SWP_NOSIZE);
		}
	}

	//平台按钮
	CRect rcPlatform;
//	m_btPlatform[0].GetWindowRect(&rcPlatform);

	//平台按钮
//	INT nYPlatform=EncircleInfoFrame.nTBorder+2L;
//	DeferWindowPos(hDwp,m_btPlatform[0],NULL,nWidth-(rcPlatform.Width()+7)*3-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[0],NULL,nWidth-(rcPlatform.Width()+7)*2-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[1],NULL,nWidth-(rcPlatform.Width()+7)*2-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[2],NULL,nWidth-(rcPlatform.Width()+7)*1-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);

	//锁定按钮
	//CRect rcLockList;
	//m_btLockList.GetWindowRect(&rcLockList);
	//DeferWindowPos(hDwp,m_btLockList,NULL,rcSplitter.left-rcLockList.Width()-13,EncircleInfoFrame.nTBorder+rcUserInfoCtrl.Height()+4,
	//	rcLockList.Width(),rcLockList.Height(),uFlags); 

	//页面位置
	//m_WndViewItemCtrl.SetViewItemPostion(rcSplitter.right+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder,
	//	nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItem.nRBorder-EncircleInfoItem.nLBorder-rcSplitter.right,
	//	nHeight-EncircleInfoFrame.nTBorder-EncircleInfoFrame.nBBorder-EncircleInfoItem.nTBorder-EncircleInfoItem.nBBorder);

	//子项框架 
	//CSize SizeItemFrame; 
	//m_WndViewItemCtrl.GetViewItemSize(SizeItemFrame);
	//DeferWindowPos(hDwp,m_WndViewItemCtrl,NULL,rcSplitter.right+10,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder-SizeItemFrame.cy,
	//	SizeItemFrame.cx,SizeItemFrame.cy,uFlags);

	//页面位置
	m_WndViewItemCtrl.SetViewItemPostion(rcSplitter.right+LIST_HALL_SPACE+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder/*-SizeItemFrame.cy*/,
		nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItem.nRBorder-EncircleInfoItem.nLBorder-rcSplitter.right-LIST_HALL_SPACE,
		nHeight-EncircleInfoFrame.nTBorder-EncircleInfoFrame.nBBorder-EncircleInfoItem.nTBorder-EncircleInfoItem.nBBorder);

	//子项框架 
	CSize SizeItemFrame; 
	m_WndViewItemCtrl.GetViewItemSize(SizeItemFrame);
	DeferWindowPos(hDwp,m_WndViewItemCtrl,NULL,rcSplitter.right+LIST_HALL_SPACE+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder-SizeItemFrame.cy,
		SizeItemFrame.cx,SizeItemFrame.cy,uFlags);


	//其他控件
	DeferWindowPos(hDwp,m_SkinSplitter,NULL,rcSplitter.left,rcSplitter.top,rcSplitter.Width(),rcSplitter.Height(),uFlags);
	DeferWindowPos(hDwp,m_WndUserInfoCtrl,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder,rcSplitter.left-EncircleInfoFrame.nLBorder,rcUserInfoCtrl.Height(),uFlags);
	DeferWindowPos(hDwp,m_PlatformPublicize,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+rcUserInfoCtrl.Height(),rcSplitter.left-EncircleInfoFrame.nLBorder,27,uFlags);

	DeferWindowPos(hDwp,m_btGameList,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+rcUserInfoCtrl.Height(),(rcSplitter.left - EncircleInfoFrame.nLBorder)/2,32,uFlags);
	DeferWindowPos(hDwp,m_btGameMatch,NULL,EncircleInfoFrame.nLBorder+ (rcSplitter.left - EncircleInfoFrame.nLBorder)/2,EncircleInfoFrame.nTBorder+27+rcUserInfoCtrl.Height(),(rcSplitter.left - EncircleInfoFrame.nLBorder)/2,32,uFlags);
	
	DeferWindowPos(hDwp,m_ServerListView,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+32+rcUserInfoCtrl.Height(),
		rcSplitter.left-EncircleInfoFrame.nLBorder,nHeight-/*EncircleInfoFrame.nTBorder-*/rcUserInfoCtrl.bottom-27-32-EncircleInfoFrame.nBBorder-1,uFlags);

	DeferWindowPos(hDwp,m_ServerMatchList,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+32+rcUserInfoCtrl.Height(),
		rcSplitter.left-EncircleInfoFrame.nLBorder,nHeight-/*EncircleInfoFrame.nTBorder-*/rcUserInfoCtrl.bottom-27-32-EncircleInfoFrame.nBBorder-1,uFlags);
	//m_WndUserInfoCtrl.ShowWindow(SW_HIDE);
	CRect rcList;
    m_ServerListView.GetWindowRect(&rcList);
	//m_ServerListView.ShowWindow(SW_HIDE);
	//m_btGameMatch.ShowWindow(SW_HIDE);
	//m_btGameList.ShowWindow(SW_HIDE);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	//控制按钮
	CRect rcControl;
	//m_btControl.GetClientRect(&rcControl);
	//m_btControl.SetWindowPos(NULL,(rcSplitter.Width()-rcControl.Width())/2,(rcSplitter.Height()-rcControl.Height())/2,0,0,uFlags|SWP_NOSIZE);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return;
}

//浏览页面
bool CPlatformFrame::WebBrowse(LPCTSTR pszURL, bool bAutoFullView)
{
	//浏览页面
	CPlazaViewItem::GetInstance()->WebBrowse(pszURL);

	//激活大厅
	m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

	//界面控制
	if (bAutoFullView==true)
	{
		CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
		if (pParameterGlobal->m_bFullScreenBrowse==true) ControlServerList(ServerListControl_Hide,false);
	}

	return true;
}

//列表控制
bool CPlatformFrame::ControlServerList(enServerListControl ServerListControl, bool bFocusControl)
{
	//位置控制
	bool bHideGameList=false;
	switch (ServerListControl)
	{
	case ServerListControl_Hide: { bHideGameList=true; break; }
	case ServerListControl_Show: { bHideGameList=false; break; }
	case ServerListControl_Turn: { bHideGameList=!m_bHideGameList; break; }
	}

	//控制过滤
	if ((bHideGameList==true)&&(bFocusControl==false)&&(m_bLockGameList==true))
	{
		return true;
	}

	//调整判断
	if (bHideGameList!=m_bHideGameList)
	{
		//设置变量
		m_bRectify=false;
		m_bHideGameList=bHideGameList;

		//设置按钮
		HINSTANCE hInstance=AfxGetInstanceHandle();
		//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,(m_bHideGameList==true)?TEXT("BT_GAME_LIST_SHOW"):TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);

		//调整界面
		CRect rcClient;
		GetClientRect(&rcClient);
		RectifyControl(rcClient.Width(),rcClient.Height());
	}

	return true;
}

//提取私聊
bool CPlatformFrame::ShowWhisperItem()
{
	//提取消息
	if (m_DlgWhisperItemArray.GetCount()>0L)
	{
		//获取子项
		CDlgWhisper * pDlgWhisper=m_DlgWhisperItemArray[0];

		//显示窗口
		pDlgWhisper->ShowWindow(SW_RESTORE);

		//置顶窗口
		pDlgWhisper->SetActiveWindow();
		pDlgWhisper->BringWindowToTop();
		pDlgWhisper->SetForegroundWindow();

		//删除子项
		m_DlgWhisperItemArray.RemoveAt(0L);

		//删除图标
		if (m_DlgWhisperItemArray.GetCount()==0L)
		{
			//设置变量
			m_bWhisperIcon=false;

			//删除时间
			KillTimer(IDI_FLASH_TRAY_ICON);

			//设置图标
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
		}

		return true;
	}

	return false;
}

//插入私聊
bool CPlatformFrame::InsertWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//参数效验
	ASSERT((pDlgWhisper!=NULL)&&(pDlgWhisper->m_hWnd!=NULL));
	if ((pDlgWhisper==NULL)||(pDlgWhisper->m_hWnd==NULL)) return false;

	//状态判断
	if (pDlgWhisper->IsWindowVisible()) return false;

	//存在搜索
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper) return false;
	}

	//插入私聊
	m_DlgWhisperItemArray.Add(pDlgWhisper);

	//设置图标
	if (m_DlgWhisperItemArray.GetCount()==1L)
	{
		//设置变量
		m_bWhisperIcon=true;

		//设置时间
		SetTimer(IDI_FLASH_TRAY_ICON,500,NULL);

		//设置图标
		m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_WHISPER)));
	}

	return true;
}

//删除私聊
bool CPlatformFrame::RemoveWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//存在搜索
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper)
		{
			//删除子项
			m_DlgWhisperItemArray.RemoveAt(i);

			//删除图标
			if (m_DlgWhisperItemArray.GetCount()==0L)
			{
				//设置变量
				m_bWhisperIcon=false;

				//删除时间
				KillTimer(IDI_FLASH_TRAY_ICON);

				//设置图标
				m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
			}

			return true;
		}
	}

	return false;
}

//激活房间
bool CPlatformFrame::ActiveServerViewItem(CServerViewItem * pServerViewItem)
{
	//插入判断
	if (m_pServerViewItem==pServerViewItem)
	{
		//设置变量
		m_pServerViewItem=NULL;

		//插入房间
		m_ServerViewItemArray.Add(pServerViewItem);

		//插入标签
		LPCTSTR pszKindName(pServerViewItem->GetKindName());
		m_WndViewItemCtrl.InsertViewItem(pServerViewItem,pszKindName);
	}

	//激活房间
	m_WndViewItemCtrl.ActiveViewItem(pServerViewItem);

	return true;
}

//删除房间
bool CPlatformFrame::DeleteServerViewItem(CServerViewItem * pServerViewItem)
{
	//当前房间
	if ((m_pServerViewItem!=NULL)&&(m_pServerViewItem==pServerViewItem))
	{
		//状态判断
		if(pServerViewItem->IsPlayingMySelf() && pServerViewItem->GetServiceStatus() !=ServiceStatus_NetworkDown)
		{
			//提示消息
			CInformation Information(this);
			if (Information.ShowMessageBox(TEXT("您正在游戏中，强行退出将被扣分，确实要强退吗？"),MB_ICONQUESTION|MB_YESNO,0)!=IDYES)
			{
				return false;
			}
			pServerViewItem->OnGameProcessClose(0);
		}

		//设置变量
		m_pServerViewItem=NULL;

		//销毁房间
		pServerViewItem->DestroyWindow();

		return true;
	}

	//搜索房间
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		if (m_ServerViewItemArray[i]==pServerViewItem)
		{ 
			//状态判断
			if(pServerViewItem->IsPlayingMySelf() && pServerViewItem->GetServiceStatus() !=ServiceStatus_NetworkDown)
			{
				//提示消息
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("您正在游戏中，强行退出将被扣分，确实要强退吗？"),MB_ICONQUESTION|MB_YESNO,0)!=IDYES)
				{
					return false;
				}
				pServerViewItem->OnGameProcessClose(0);
			}

			//销毁房间
			pServerViewItem->DestroyWindow();
			m_ServerViewItemArray.RemoveAt(i);

			//删除房间
			m_WndViewItemCtrl.RemoveViewItem(pServerViewItem);
			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//搜索通知
			CDlgSearchUser * pDlgSearchUser=CDlgSearchUser::GetInstance();
			if (pDlgSearchUser!=NULL) pDlgSearchUser->OnViewItemDelete(pServerViewItem);

			return true;
		}
	}

	return false;
}

//枚举房间
CServerViewItem * CPlatformFrame::EmunServerViewItem(WORD wIndex)
{
	//索引判断
	if (wIndex<m_ServerViewItemArray.GetCount())
	{
		return m_ServerViewItemArray[wIndex];
	}

	return NULL;
}

//查找房间
CServerViewItem * CPlatformFrame::SearchServerViewItem(WORD wServerID)
{
	//查找房间
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem->GetServerID()==wServerID) return pServerViewItem;
	}

	return NULL;
}

//进入房间
CServerViewItem * CPlatformFrame::EntranceServerItem(CGameKindItem * pGameKindItem)
{
	return NULL;
}

//进入房间
CServerViewItem * CPlatformFrame::EntranceServerItem(CGameServerItem * pGameServerItem,bool bOpenInsureDlg)
{
	//效验参数
	ASSERT(pGameServerItem!=NULL);
	if (pGameServerItem==NULL) return NULL;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	//登录判断
	if (pGlobalUserData->dwUserID==0L) return NULL;

	//变量定义
	tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
	tagGameKind * pGameKind=&pGameServerItem->m_pGameKindItem->m_GameKind;

	//查找房间
	WORD wServerID=pGameServer->wServerID;
	CServerViewItem * pServerViewItem=SearchServerViewItem(wServerID);

	//激活房间
	if (pServerViewItem!=NULL)
	{
		ActiveServerViewItem(pServerViewItem);
		return pServerViewItem;
	}

	//当前判断
	if (m_pServerViewItem!=NULL)
	{
		if(m_pServerViewItem->GetServiceStatus() == ServiceStatus_NetworkDown)
		{
			DeleteServerViewItem(m_pServerViewItem);
		}
		else
		{
			//相同判断
			if (wServerID==m_pServerViewItem->GetServerID()) 
				return pServerViewItem;

			//提示消息
			TCHAR szBuffer[256]=TEXT("");
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("正在进入 [ %s ] 游戏房间中，请稍后等待片刻..."),m_pServerViewItem->GetServerName());

			//提示消息
			CInformation Information(this);
			Information.ShowMessageBox(szBuffer,MB_OK|MB_ICONWARNING,30);

			return m_pServerViewItem;

		}
	}

	//会员房间
	if (m_ServerViewItemArray.GetCount()>=MAX_SERVER_COUNT)
	{
		//提示消息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("您进入的游戏房间太多了，请关闭部分后再次尝试！"),MB_ICONQUESTION,60);

		return NULL;
	}

	//安装判断
	if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
	{
		//获取版本
		CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;
		CWHService::GetModuleVersion(pGameKind->szProcessName,pGameKindItem->m_dwProcessVersion);

		//下载游戏
		if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
		{
			CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
			pCGlobalUnits->DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,wServerID,pGameKind->szProcessName);

			return NULL;
		}

		//更新列表
		m_ServerListView.OnGameItemUpdate(pGameKindItem);
	}

	//绑定操作
	SCORE myTotalScore = pGlobalUserData->lUserScore + pGlobalUserData->lUserInsure;
	if (m_bShowVerify && myTotalScore > 1000000 && (!pGlobalUserData->cbMoorMachine || !pIndividualUserData->cbMoorPassPortID || !pIndividualUserData->cbMoorPhone))
	{
		//构造提示
		CString sCoinStr;
		sCoinStr = "您当前金币总额过多，为了您的金币安全，请绑定本机、身份证及手机再进行游戏，点击‘确定’进行绑定。";
		//退出判断
		m_bShowVerify = false;
		CInformation Information(CPlatformFrame::GetInstance());
		if(Information.ShowMessageBox(sCoinStr,MB_ICONINFORMATION|MB_OKCANCEL,0,false) == IDOK)
		{			//显示窗口
			CDlgLockMachine DlgLockMachine;
			DlgLockMachine.DoModal();
			return NULL;
		}
	}

	//创建房间
	try
	{
		//创建房间
		m_pServerViewItem=new CServerViewItem;
		m_pServerViewItem->Create(IDD_GAME_SERVER,this);

		//配置房间
		m_pServerViewItem->InitServerViewItem(pGameServerItem,m_wAVServerPort,m_dwAVServerAddr,false,bOpenInsureDlg);
	}
	catch (LPCTSTR pszString)
	{
		//销毁房间
		if (m_pServerViewItem!=NULL)
		{
			if (m_pServerViewItem->m_hWnd!=NULL)
			{
				m_pServerViewItem->DestroyWindow();
			}
			//else
			//{
				SafeDelete(m_pServerViewItem);
			//}
		}

		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(pGameServer->szServerName,pszString,MB_ICONERROR);

		return NULL;
	}

	return m_pServerViewItem;
}

//还原窗口
bool CPlatformFrame::RestoreWindow()
{
	//状态判断
	if (m_bMaxShow==true)
	{
		//设置变量
		m_bMaxShow=false;
		m_bRectify=false;

		//设置按钮
		m_btMax.SetButtonImage(IDB_BT_MAX,AfxGetInstanceHandle(),true,false);

		//移动窗口
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//最大窗口
bool CPlatformFrame::MaxSizeWindow()
{
	//状态判断
	if (m_bMaxShow==false)
	{
		//设置变量
		m_bMaxShow=true;
		m_bRectify=false;

		//默认位置
		GetWindowRect(&m_rcNormalSize);

		//设置按钮
		m_btMax.SetButtonImage(IDB_BT_RESORE,AfxGetInstanceHandle(),true,false);

		//获取位置
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//移动窗口
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//关闭消息
VOID CPlatformFrame::OnClose()
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//关闭提示
	if ((pGlobalUserData->dwUserID!=0L)&&(m_MissionLogon.GetActiveStatus()==false))
	{
		//显示窗口
		CDlgEnquire DlgEnquire;
		INT_PTR nResult=DlgEnquire.DoModal();

		//命令处理
		switch (nResult)
		{
		case IDCANCEL:				//取消动作
			{
				return;
			}
		case IDC_CLOSE_SERVER:		//退出房间
			{
				//关闭房间
				ASSERT(m_WndViewItemCtrl.GetActiveItem()>0);
				WORD wActiveItem=m_WndViewItemCtrl.GetActiveItem();
				
				//关闭房间
				if (wActiveItem>=1)
				{
					ASSERT((wActiveItem-1)<m_ServerViewItemArray.GetCount());
					DeleteServerViewItem(m_ServerViewItemArray[wActiveItem-1]);
				}

				return;
			}
		case IDC_SWITCH_ACCOUNTS:	//切换帐号
			{
				//投递消息
				PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

				return;
			}
		//case IDC_CLOSE_PLAZA:	//关闭大厅
		//	{
		//		//全局设置
		//		KillTimer(IDI_MESSAGE_POP);
		//		//激活连接
		//		m_MissionLogon.SetLoginInOrOut(true);
		//		if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
		//		{
		//			//连接失败，关闭大厅
		//			ClosePazza();
		//		}
		//		return;
		//	}
		}
	}

	KillTimer(IDI_MESSAGE_POP);
	//////////////////////////////////////////////////////////////////////////
	CGlobalUnits::GetInstance()->DeleteUserCookie();
	CGlobalUserInfo::GetInstance()->ResetUserInfoData();
	UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

	__super::OnClose();
	return;
	//////////////////////////////////////////////////////////////////////////
	if (m_MissionLogon.BHaveLogonIn()) //已经登录
	{
		//激活连接
		m_MissionLogon.SetLoginSocketType(1);
		if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
		{
			//连接失败，关闭大厅
			ClosePazza(1);
		}
		return;
	}
	ClosePazza(1);
	//注销热键
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

	//__super::OnClose();
}

//绘画背景
BOOL CPlatformFrame::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,RGB(10,111,167));

	//框架位置5
	tagEncircleInfo ItemEncircleInfo;
	tagEncircleInfo FrameEncircleInfo;
	m_ItemEncircle.GetEncircleInfo(ItemEncircleInfo);
	m_FrameEncircle.GetEncircleInfo(FrameEncircleInfo);

	//拆分位置
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//广告位置
	CRect rcWebPublicize;
	//m_PlatformPublicize.GetWindowRect(&rcWebPublicize);

	//位置转换
	ScreenToClient(&rcSplitter);
	ScreenToClient(&rcWebPublicize);

	//控件位置
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);
/*
	//游戏列表
	if (false)
	//if (m_bHideGameList==false)
	{
		//列表位置
		CRect rcList;
		rcList.right=rcSplitter.left;
		rcList.left=FrameEncircleInfo.nLBorder;
		rcList.top=FrameEncircleInfo.nTBorder+rcUserInfoCtrl.Height();
		rcList.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;
		//m_ServerListView.GetWindowRect(&rcList);

		ScreenToClient(&rcList);
		//建立缓冲
		CImage ImageBuffer;
		ImageBuffer.Create(rcList.Width(),rcList.Height(),32);

		//创建 DC
		CDC BufferDC;
		BufferDC.CreateCompatibleDC(pDC);
		BufferDC.SelectObject(ImageBuffer);

		//设置环境
		BufferDC.SetBkMode(TRANSPARENT);
		BufferDC.SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

		//绘画列表
		CRect rcBuffer(0,0,rcList.Width(),rcList.Height());
		//m_ListEncircle.DrawEncircleFrame(&BufferDC,rcBuffer);


		//BufferDC.FillSolidRect(&rcList,RGB(236,243,249));
		BufferDC.FillSolidRect(&rcList,RGB(0,255,0));
		//构造字符
		//TCHAR szOnLineInfo[32]=TEXT("");
		//_sntprintf(szOnLineInfo,CountArray(szOnLineInfo),TEXT("龙马游祝您游戏愉快"),m_dwAllOnLineCount);

		//绘画信息
		//BufferDC.SetTextColor(RGB(0,0,0));
		//BufferDC.TextOut(10,7,szOnLineInfo,lstrlen(szOnLineInfo));

		//绘画界面
		pDC->BitBlt(rcList.left,rcList.top,rcList.Width(),rcList.Height(),&BufferDC,0,0,SRCCOPY);

		//清理资源
		BufferDC.DeleteDC();
		ImageBuffer.Destroy();
	}
*/
	//子项框架
	CRect rcItem;
	rcItem.left=rcSplitter.right+LIST_HALL_SPACE;
	rcItem.top=FrameEncircleInfo.nTBorder;
	rcItem.right=rcClient.Width()-FrameEncircleInfo.nRBorder;
	rcItem.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;

	//绘画框架
	m_ItemEncircle.DrawEncircleFrame(pDC,rcItem);
	m_FrameEncircle.DrawEncircleFrame(pDC,rcClient);
	//////////////////////////////////////////////////////////////////////////
	//CRect rcList;
	//rcList.right=rcSplitter.left;
	//rcList.left=FrameEncircleInfo.nLBorder;
	//rcList.top=FrameEncircleInfo.nTBorder+rcUserInfoCtrl.Height()+27+32;
	//rcList.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;

	//CDC dcMem;
	//CBitmap bmp; //内存中承载临时图象的位图

	//dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC
	////创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
	//bmp.CreateCompatibleBitmap(pDC,rcList.Width(),rcList.Height());
	//CBitmap *pOldBit=dcMem.SelectObject(&bmp);
	////按原来背景填充客户区，不然会是黑色
	//dcMem.FillSolidRect(rcList,RGB(255,255,255));
	////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////
	//pDC->BitBlt(rcList.left,rcList.top,rcList.Width(),rcList.Height(),&dcMem,0,0,SRCCOPY);
	////将内存DC上的图象拷贝到前台
	////绘图完成后的清理
	//dcMem.DeleteDC();     //删除DC
	//bmp.DeleteObject(); //删除位图
	//////////////////////////////////////////////////////////////////////////

	return TRUE;
}

//按键测试
LRESULT CPlatformFrame::OnNcHitTest(CPoint Point)
{
	//按钮测试
	if (m_bMaxShow==false)
	{
		//获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		//转换位置
		CPoint ClientPoint=Point;
		ScreenToClient(&ClientPoint);

		//左面位置
		if (ClientPoint.x<=BORAD_SIZE)
		{
			if (ClientPoint.y<=CAPTION_SIZE) return HTTOPLEFT;
			if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOMLEFT;
			return HTLEFT;
		}

		//右面位置
		if (ClientPoint.x>=(rcClient.Width()-BORAD_SIZE))
		{
			if (ClientPoint.y<=CAPTION_SIZE) return HTTOPRIGHT;
			if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOMRIGHT;
			return HTRIGHT;
		}

		//上下位置
		if (ClientPoint.y<=BORAD_SIZE) return HTTOP;
		if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOM;
	}
	else
		return HTBORDER; 

	return __super::OnNcHitTest(Point);
}

//时间消息
VOID CPlatformFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_FLASH_TRAY_ICON:	//任务图标
		{
			//设置变量
			m_bWhisperIcon=!m_bWhisperIcon;

			//设置图标
			UINT uIconID=(m_bWhisperIcon==true)?IDI_WHISPER:IDR_MAINFRAME;
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(uIconID)));

			return;
		}
	case IDI_UPDATA_ONLINE:
		{
			UpDataAllOnLineCount();
			return;
		}	
	case IDI_TIMER_WEB:
		 {
			 KillTimer(IDI_TIMER_WEB);
			 //打开主页
			 CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			 ASSERT(CPlatformFrame::GetInstance()!=NULL);
/*			 CString sMainUrl;
			 sMainUrl.Format("%s/index.aspx",pGlobalServer->GetPlatformServer(3))*/;
			 CPlatformFrame::GetInstance()->WebBrowse(m_sMainUrl,false);
		 }

	case IDI_MESSAGE_POP:
		{
			KillTimer(IDI_MESSAGE_POP);
			PopSysMessage();
			return;
		}
	case IDI_CLOSE_PAZZA:
		{
			KillTimer(IDI_CLOSE_PAZZA);

			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
			UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
			UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

			__super::OnClose();
			return;
		}
	case IDI_REM_INSUREPASS:
		{
			KillTimer(IDI_REM_INSUREPASS);
			m_sRemInsurePwd = "";
		}

	}

	__super::OnTimer(nIDEvent);
}

//位置消息
VOID CPlatformFrame::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	//创建区域
	CRgn WindowRgn;
	WindowRgn.CreateRoundRectRgn(0,0,cx+1,cy+1,ROUND_CX,ROUND_CY);

	//设置区域
	SetWindowRgn(WindowRgn,TRUE);

	return;
}

//位置信息
VOID CPlatformFrame::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);

	//窗口位置
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//设置位置
	lpMMI->ptMinTrackSize.x=__min(LESS_SCREEN_CX,rcArce.Width());
	lpMMI->ptMinTrackSize.y=__min(LESS_SCREEN_CY,rcArce.Height());

	return;
}

//建立消息
INT CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置窗口
	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);
	//注册dll
	RegisterDll();

	//构造地址
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();

	TCHAR szMainUrl[MAX_PATH]=TEXT("");
	m_sMainUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"MainUrl",szMainUrl,MAX_PATH,false);
	if (m_sMainUrl == "")
	{
		m_sMainUrl = "http://www.999qp.com/index.aspx";
	}
	//创建广场
	CRect rcCreate(0,0,0,0);
	m_PlazaViewItem.SetMainUrl(m_sMainUrl);
	m_PlazaViewItem.Create(IDD_GAME_PLAZA,this);

	//创建控件
	m_ServerListView.Create(WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SERVER_LIST);
	m_SkinSplitter.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN_SPLITTER);
//m_ServerListView.ShowWindow(SW_HIDE);
	//窗口控件
	m_WndViewItemCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_VIEW_ITEM_CTRL);
	m_WndUserInfoCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_USER_INFO_CTRL);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	//创建按钮
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MAX);
	m_btSkin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLOSE);
	m_btCertificate.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CERTIFICATE);
	//m_btControl.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CONTROL);
	//m_btLockList.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_LOCK_LIST);
	m_btGameList.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BUTTON_GAMELIST);
	m_btGameMatch.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BUTTON_GAMEMATCH);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btMin.SetButtonImage(IDB_BT_MIN,hInstance,true,false);
	m_btMax.SetButtonImage(IDB_BT_MAX,hInstance,true,false);
	m_btSkin.SetButtonImage(IDB_BT_SKIN,hInstance,true,false);
	m_btClose.SetButtonImage(IDB_BT_CLOSE,hInstance,true,false);
	m_btCertificate.SetButtonImage(IDB_BT_CERTIFICATE,hInstance,true,false);

	//m_btLockList.SetButtonImage(IDB_BK_LIST,TEXT("BT_LOCK_LIST"),hInstance,true,false);
	//m_btLockList.ShowWindow(SW_HIDE);

	//控制按钮
	//m_btControl.SetParent(&m_SkinSplitter);
	//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);

	//平台按钮
// 	for (INT i=0;i<CountArray(m_btPlatform);i++)
// 	{
// 		//不创建原保险柜按钮
// 		if (i == 1)
// 		{
// 			continue;
// 		}
// 
// 		m_btPlatform[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLATFORM+i);
// 	}

	//导航按钮
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		m_btNavigation[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_NAVIGATION+i);
	}

	//平台按钮
	//m_btPlatform[0].SetButtonImage(IDB_BK_PLATFORM_1,TEXT("BT_PLATFORM_1"),hInstance,true,false);
	//m_btPlatform[1].SetButtonImage(IDB_BK_PLATFORM_2,TEXT("BT_PLATFORM_2"),hInstance,true,false);
	//m_btPlatform[2].SetButtonImage(IDB_BK_PLATFORM_3,TEXT("BT_PLATFORM_3"),hInstance,true,false);

	//导航按钮
	m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,hInstance,true,false);
	m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,hInstance,true,false);
	m_btNavigation[2].SetButtonImage(IDB_BK_NAVIGATION3,hInstance,true,false);
	m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION4,hInstance,true,false);
	m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,hInstance,true,false);

	//拆分设置
	m_SkinSplitter.SetSplitterEvent(this);
	m_SkinSplitter.SetSplitterColor(0.67,0.95);
	m_SkinSplitter.SetSplitterType(SplitterType_Vor);

	///////////////////比赛列表///////////////////////////////////////////////////////
	m_ServerMatchList.Create(/*WS_CHILD|*/LVS_REPORT|LVS_OWNERDRAWFIXED|LVS_NOSCROLL|LVS_NOCOLUMNHEADER,rcCreate, this, IDC_MATCH_LIST);
    m_ServerMatchList.SetBkColor(RGB(236,237,255));
	m_ServerMatchList.SetItemHeight(64);
	m_ServerMatchList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_ServerMatchList.ModifyStyle(0,LVS_EX_TRACKSELECT);
	m_ServerMatchList.InsertColumn(0,TEXT("编号"),LVCFMT_LEFT,0,0);
	m_ServerMatchList.InsertColumn(1,TEXT("对方用户名"),LVCFMT_LEFT,266,1);
	//m_ServerMatchList.SetListColor(RGB(255,0,0),RGB(0,255,0),RGB(255,255,255),RGB(101,101,255));
	//int nPos = 0;

	//for(int nIndex = 3;nIndex<40;nIndex++)
	//{
	//	CString strTemp;
	//	strTemp.Format("Index %d",nIndex);
	//	m_ServerMatchList.InsertItem(nPos,(LPCTSTR)strTemp);

	//	m_ServerMatchList.SetItemText(nPos,1,(LPCTSTR)"aaa");

	//	m_ServerMatchList.SetItemData(nPos,nIndex);
	//}
//////////////////////////////////////////////////////////////////////////

	//游戏列表
	m_ServerListView.InitServerTreeView();
	CServerListData::GetInstance()->SetServerListDataSink(&m_ServerListView,&m_ServerMatchList);

	//提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.SetMaxTipWidth(320);
	m_ToolTipCtrl.SetDelayTime(100);
	m_ToolTipCtrl.AddTool(&m_btMin,TEXT("最小化"));
	m_ToolTipCtrl.AddTool(&m_btMax,TEXT("最大化"));
	m_ToolTipCtrl.AddTool(&m_btSkin,TEXT("界面换肤"));
	m_ToolTipCtrl.AddTool(&m_btClose,TEXT("关闭游戏"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[0],TEXT("用户登录"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[1],TEXT("帐号充值"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[2],TEXT("保险柜"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[3],TEXT("游戏商城"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[4],TEXT("游戏客服"));
	//m_ToolTipCtrl.AddTool(&m_btControl,TEXT("隐藏（显示）游戏列表"));
	CString sTip = "文网游备字[2014]C-CBG022号\r\n浙网文[2013]1114-104号\r\n浙ICP备2235390号\r\n软署登字第0697404号\r\nICP证：浙B2-20140068";
	//sTip.Replace("#","\r\n");
	m_ToolTipCtrl.AddTool(&m_btCertificate,sTip);

	//系统控制
	m_WndViewItemCtrl.SetViewItemEvent(this);
	m_WndViewItemCtrl.InsertViewItem(&m_PlazaViewItem,TEXT("游戏广场"));

	//注册事件
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//设置位置
	CSize SizeRestrict;
	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);

	//窗口位置
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//读取位置
	CWHRegKey InfoKeyItem;
	if (InfoKeyItem.OpenRegKey(REG_INTERFACE_INFO,false)==true)
	{
		SizeRestrict.cx=InfoKeyItem.GetValue(TEXT("ScreenWidth"),rcArce.Width()/2);
		SizeRestrict.cy=InfoKeyItem.GetValue(TEXT("ScreenHeight"),rcArce.Height()/2);
	}

	//位置调整
	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);

	//移动窗口
	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
	m_rcNormalSize.right=m_rcNormalSize.left+SizeRestrict.cx;
	m_rcNormalSize.bottom=m_rcNormalSize.top+SizeRestrict.cy;
	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Games/CustomerNew.aspx"),pGlobalServer->GetPlatformServer(3));

	//连接广告
	//m_PlatformPublicize.Navigate("http://61.174.50.46:8090/Games/CustomerNew.aspx");
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetBoradColor(RGB(215,235,255));

	//if(theApp.m_bsSpreader)
	//{
	//	m_btGameList.SetButtonImage(IDB_BT_GAMELIST1,hInstance,true,false);
	//	m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH,hInstance,true,false);
	//	m_ServerListView.ShowWindow(SW_HIDE);
	//	m_ServerMatchList.ShowWindow(SW_SHOW);
	//}
	//else
	//{
		m_btGameList.SetButtonImage(IDB_BT_GAMELIST,hInstance,true,false);
		m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH1,hInstance,true,false);
		m_ServerListView.ShowWindow(SW_SHOW);
		m_ServerMatchList.ShowWindow(SW_HIDE);
	//}

	InitData();	

	//显示窗口
	MaxSizeWindow();

	//登录系统
	PostMessage(WM_COMMAND,IDM_USER_LOGON,0);

	//注册热键
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
	//CWHService::RegisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS,pParameterGlobal->m_wBossHotKey);
	//CWHService::RegisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER,pParameterGlobal->m_wWhisperHotKey);

	//设置托盘
	m_SystemTrayIcon.InitTrayIcon(m_hWnd,IDC_SYSTEM_TRAY_ICON);
	m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)),pGlobalServer->GetPlatformProduct(1));

	//更新人数
	SetTimer(IDI_UPDATA_ONLINE, TIME_UPDATA_ONLINE, NULL);
//	SetTimer(IDI_TIMER_WEB, 5*1000, NULL);
	//设置字体
	CSkinDialog::SetWndFont(this,NULL);

	return 0;
}

//鼠标消息
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟按标题
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//鼠标消息
VOID CPlatformFrame::OnLButtonDblClk(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDblClk(nFlags,Point);

	//状态判断
	if (Point.y>CAPTION_SIZE) return;

	//窗口控制
	if (m_bMaxShow==true)
	{
		RestoreWindow();
	}
	else
	{
		MaxSizeWindow();
	}
	
	return;
}

//设置改变
VOID CPlatformFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags,lpszSection);

	//窗口控制
	if (m_bMaxShow==true)
	{
		m_bMaxShow=false;
		MaxSizeWindow();
	}
	else
	{
		m_bMaxShow=true;
		RestoreWindow();
	}

	return;
}

//平台按钮
VOID CPlatformFrame::OnBnClickedPlatform1()
{
	//查找用户
	CDlgSearchUser DlgSearchUser;
	DlgSearchUser.DoModal();

	return;
}

//平台按钮
VOID CPlatformFrame::OnBnClickedPlatform2()
{
	//变量定义
// 	bool bGoldServer=false;
// 	CServerViewItem * pServerViewGold=NULL;
// 
// 	//查找房间
// 	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
// 	{
// 		//获取房间
// 		ASSERT(m_ServerViewItemArray[i]!=NULL);
// 		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
// 
// 		//房间类型
// 		WORD wServerType=pServerViewItem->GetServerType();
// 		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();
// 
// 		//房间判断
// 		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
// 		{
// 			//设置变量
// 			bGoldServer=true;
// 			pServerViewGold=pServerViewItem;
// 
// 			break;
// 		}
// 	}
// 
// 	//设置资源
// 	AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
// 
// 	//银行中心
// 	if (bGoldServer==false)
// 	{
// 		//广场银行
// 		CDlgInsurePlaza DlgInsurePlaza;
// 		INT_PTR nResult=DlgInsurePlaza.DoModal();
// 	}
// 	else
// 	{
// 		//房间银行
// 		ASSERT(pServerViewGold!=NULL);
// 		pServerViewGold->ShowInsureView();
// 	}

	return;
}

//平台按钮
VOID CPlatformFrame::OnBnClickedPlatform3()
{
	//变量定义
	CParameterGame * pParameterGame=NULL;
	CParameterServer * pParameterServer=NULL;

	//房间变量
	WORD wActiveItem=m_WndViewItemCtrl.GetActiveItem();
	tagViewItemInfo * pViewItemInfo=m_WndViewItemCtrl.GetViewItemInfo(wActiveItem);

	//房间搜索
	if ((wActiveItem>=1)&&(pViewItemInfo!=NULL))
	{
		//获取窗口
		CWnd * pItemView=pViewItemInfo->pItemView;
		CServerViewItem * pServerViewItem=(CServerViewItem *)pItemView;

		//设置变量
		if (pServerViewItem!=NULL)
		{
			pParameterGame=pServerViewItem->GetParameterGame();
			pParameterServer=pServerViewItem->GetParameterServer();
		}

	}

	//构造变量
	CDlgCollocate DlgCollocate;
	DlgCollocate.InitCollocate(pParameterGame,pParameterServer);

	//显示配置
	if (DlgCollocate.DoModal()==IDOK)
	{
		//发送规则
		for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
		{
			//获取窗口
			CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
			if (pServerViewItem->GetServiceStatus()==ServiceStatus_ServiceIng) pServerViewItem->SendUserRulePacket();
		}
	}

	return;
}

//热键消息
LRESULT CPlatformFrame::OnMessageHotKey(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//老板热键
		{
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//登录判断
			if (pGlobalUserData->dwUserID!=0L)
			{
				//变量定义
				bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

				//隐藏窗口
				if (bBossCome==false)
				{
					//还原窗口
					ShowWindow(SW_RESTORE);
					ShowWindow(SW_SHOW);

					//置顶窗口
					SetActiveWindow();
					BringWindowToTop();
					SetForegroundWindow();

					//显示图标
					m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
				}
				else
				{
					//隐藏窗口
					ShowWindow(SW_MINIMIZE);
					ShowWindow(SW_HIDE);

					//隐藏图标
					m_SystemTrayIcon.HideTrayIcon();
				}

				//发送消息
				for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
				{
					ASSERT(m_ServerViewItemArray[i]!=NULL);
					m_ServerViewItemArray[i]->NotifyBossCome(bBossCome);
				}
			}

			return 0;
		}
	case IDI_HOT_KEY_WHISPER:	//私聊热键
		{
			//提取消息
			if (m_DlgWhisperItemArray.GetCount()>0L)
			{
				ShowWhisperItem();
				return 1;
			}

			return 0;
		}
	}

	return 0;
}

//图标消息
LRESULT CPlatformFrame::OnMessageTrayIcon(WPARAM wParam, LPARAM lParam)
{
	//事件处理
	switch (lParam)
	{
	case WM_LBUTTONDOWN:		//鼠标单击
	case WM_LBUTTONDBLCLK:		//鼠标双击
		{
			//提取消息
			if (m_DlgWhisperItemArray.GetCount()>0L)
			{
				ShowWhisperItem();
				return 1;
			}

			return 1;
		}
	case WM_RBUTTONDOWN:		//鼠标单击
	case WM_RBUTTONDBLCLK:		//鼠标双击
		{
			//创建菜单
			CSkinMenu Menu;
			Menu.CreateMenu();

			//构造菜单
			Menu.AppendMenu(IDM_RESTORE,TEXT("还原"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
			Menu.AppendMenu(IDM_MINIMIZE,TEXT("最小化"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
			Menu.AppendMenu(IDM_MAXIMIZE,TEXT("最大化"));
			Menu.AppendSeparator();
			Menu.AppendMenu(IDC_CLOSE,TEXT("退出广场"));
			//Menu.AppendSeparator();
			//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("关于..."));

			//显示菜单
			CPoint MousePoint;
			GetCursorPos(&MousePoint);
			Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

			return 1;
		}
	}

	return 0;
}

//事件消息
LRESULT CPlatformFrame::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//事件处理
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//登录完成
		{
			//显示窗口
			ShowWindow(SW_SHOW);
			SetForegroundWindow();

			//游戏列表
			ControlServerList(ServerListControl_Show,false);

			SetTimer(IDI_TIMER_WEB, 1*1000, NULL);

			//用户甜饼
			ASSERT(CGlobalUnits::GetInstance()!=NULL);
			if (CGlobalUnits::GetInstance()->DeleteUserCookie())
			{
				CGlobalUnits::GetInstance()->WriteUserCookie();
			}
	
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();
			if(pGlobalUserInfo->GetUserAccountType()>0 && (!pIndividualUserData->cbMoorPhone || !pIndividualUserData->cbMoorPassPortID)) //第三方用户，且没有绑定
			{
				CInformation Information(CPlatformFrame::GetInstance());
				if(Information.ShowMessageBox(TEXT("亲爱的QQ账号用户,为了您的账户安全,请立即绑定身份证及手机，点‘确定’进行绑定 "),MB_ICONINFORMATION|MB_OKCANCEL,0) == IDOK)
				{			//显示窗口
					CDlgLockMachine DlgLockMachine;
					DlgLockMachine.DoModal();
				}
				PopSysMessage();
			}
			else if (!pIndividualUserData->cbMoorPhone) //绑定手机
			{
// 				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 				TCHAR szBillUrl[256]=TEXT("");
// 				_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/UserBindMachine2.aspx"),pGlobalServer->GetPlatformServer(3));
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/MachineBind/UserBindMachine.aspx?userId=%d"),pGlobalServer->GetPlatformServer(3),pGlobalUserData->dwUserID);

				CMessagePop DlgMobileBind ;
				DlgMobileBind.SetWindowSize(490,210,490,/*210-107*/210);
				DlgMobileBind.InitWebDlg(szBrowseUrl,"手机绑定",true,false,0);
				//CDlgMobileBind DlgMobileBind;
				DlgMobileBind.DoModal();
				PopSysMessage();
			}
			else
			{
				SetTimer(IDI_MESSAGE_POP,1000*3,NULL);
			}
	
			return 0L;
		}
	case EVENT_USER_LOGOUT:			//注销成功
		{
			//激活广场
			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//关闭房间
			if (m_pServerViewItem!=NULL)
			{
				if(!DeleteServerViewItem(m_pServerViewItem))return 0L;
			}

			//关闭房间
			while (m_ServerViewItemArray.GetCount()>0)
			{
				if(!DeleteServerViewItem(m_ServerViewItemArray[0]))
					return 0L;
			}
			//关闭保险柜
			if (m_pInsurePlaza!=NULL)
			{
				SafeDelete(m_pInsurePlaza);
				m_pInsurePlaza = NULL;
			}
			m_ServerMatchList.ResetData();
			m_ServerListView.ResetData();
			m_ServerListData.ResetDate();


			//隐藏窗口
			ShowWindow(SW_HIDE);

			//重新初始化登录信息
			m_sRemInsurePwd = "";
			m_bShowVerify = true;
			//////////////////////////////////////////////////////////////////////////
			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
			m_MissionLogon.SetHaveLogonIn(false);
			m_MissionLogon.SetLoginSocketType(0);
			//显示登录
			m_MissionLogon.ShowLogon();

			return 0L;
		}
	case EVENT_DOWN_LOAD_FINISH:	//下载完成
		{
			//获取参数
			WORD wKindID=LOWORD(lParam);
			WORD wServerID=HIWORD(lParam);

			//更新列表
			CServerListData * pServerListData=CServerListData::GetInstance();
			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);

			//进入房间
			if ((wKindID!=0)&&(wServerID!=0))
			{
				CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
				if (pGameServerItem!=NULL) EntranceServerItem(pGameServerItem);
			}

			return 0L;
		}
	}

	return 0L;
}

//事件消息
LRESULT CPlatformFrame::OnMessageInstallCancelEvent(WPARAM wParam, LPARAM lParam)
{
	//显示登录
	m_MissionLogon.ShowLogon();
	return 0L;
}

void CPlatformFrame::SetVideoOption(WORD wAVServerPort, DWORD dwAVServerAddr)
{
	m_wAVServerPort=wAVServerPort;
	m_dwAVServerAddr=dwAVServerAddr;
}

//事件消息
LRESULT CPlatformFrame::OnMessageInsurePlazaEvent(WPARAM wParam, LPARAM lParam)
{
	tagInsurePlazaUpdata *pUpdata = (tagInsurePlazaUpdata*)wParam;
	if(pUpdata)
	{
		//变量定义
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//更新
		pGlobalUserData->lUserScore = pUpdata->lUserScore;
		pGlobalUserData->lUserInsure = pUpdata->lUserInsure;

		m_WndUserInfoCtrl.InvalidateRect(NULL);
	}

	return 0;
}

//更新总在线人数
void CPlatformFrame::UpDataAllOnLineCount()
{
	DWORD dwAllOnLineCount = GetAllOnLineCount();
	if(m_dwAllOnLineCount != dwAllOnLineCount)
	{
		m_dwAllOnLineCount = dwAllOnLineCount;
		RedrawWindow();
	}
}

//获取总在线人数
DWORD CPlatformFrame::GetAllOnLineCount()
{
	return m_ServerListData.GetAllOnLineCount();
}

//添加最后游戏
void CPlatformFrame::AddLastPlayGame(WORD wServerID)
{
	//return; // lhm 20149119 add
	//查找房间
	CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);

	//插入记录
	m_ServerListView.AddLastPlayGame(wServerID, pGameServerItem);

	return;
}

//房间失效
bool CPlatformFrame::ListGameServerInvalidation(WORD wKindID, WORD wServerID)
{
	//删除房间
	m_ServerListData.DeleteGameServer(wServerID);

	//获取类型
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//更新类型
	if(pGameKindItem!=NULL && m_ServerListView.IsEmptySubitem(wKindID))
	{
		m_ServerListView.OnGameItemDelete(pGameKindItem);
		m_ServerListView.OnGameItemInsert(pGameKindItem);
		m_ServerListView.OnGameKindFinish(wKindID);
	}

	return true;
}

//消息函数
LRESULT CPlatformFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(message==0x0313)
	{
		//创建菜单
		CSkinMenu Menu;
		Menu.CreateMenu();

		//构造菜单
		Menu.AppendMenu(IDM_RESTORE,TEXT("还原"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
		Menu.AppendMenu(IDM_MINIMIZE,TEXT("最小化"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
		Menu.AppendMenu(IDM_MAXIMIZE,TEXT("最大化"));
		Menu.AppendSeparator();
		Menu.AppendMenu(IDC_CLOSE,TEXT("退出广场"));
		//Menu.AppendSeparator();
		//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("关于..."));

		//显示菜单
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

		return 0;
	}

	return __super::WindowProc(message, wParam, lParam);
}

//void CPlatformFrame::OnSysCommand(UINT nID,LPARAM lParam)
//{
//	switch(nID)
//	{
//	case SC_MAXIMIZE :
//		ShowWindow(SW_SHOWMAXIMIZED);
//		return;
//		break;
//	case SC_MINIMIZE :
//		ShowWindow(SW_MINIMIZE);
//		return;
//		break;
//	case SC_RESTORE :
//		//	 AfxMessageBox("Restore");
//		ShowWindow(SW_RESTORE);
//		return;
//		break;
//	}
//	CPlatformFrame::OnSysCommand(nID,lParam );
//}

bool CPlatformFrame::RegisterDll()
{
	int dllnum = 1;
	CString dllpath[1]={"ImageOle.dll"};
	BOOL bsResult = false ;
	//检查是否支持注册
	int i=0;
	for(i=0;i<dllnum;i++)
	{
		CString strOcxPath;
		if(dllpath[i] == "")
		{
			continue;
		}
		CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
		strOcxPath  =pCGlobalUnits->m_sAppPath +dllpath[i];
		if(true)
		//if (SupportsSelfRegister(strOcxPath))
		{
			HMODULE hModule = ::LoadLibrary(strOcxPath) ;
			if (LOADLIBRARY_FAILED(hModule)) return FALSE ;

			//获得注册函数地址
			CTLREGPROC DLLRegisterServer =
				(CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer") ;
			if (DLLRegisterServer != NULL)
			{
				HRESULT regResult = DLLRegisterServer() ;
				bsResult = (regResult == NOERROR) ;
			}
			::FreeLibrary(hModule) ;
		}
	}
	return true;
}

bool CPlatformFrame::GetPlayingGameServer(int &nGameServerID)
{
	bool bPlaying = false;
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//获取窗口
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL)
		{
			bPlaying = pServerViewItem->IsPlayingMySelf();
			nGameServerID = pServerViewItem->GetGameServer().wServerID;
			break;
		}
	}
	return bPlaying;
}

void CPlatformFrame::ExitGameServer(int nGameServerID)
{
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//获取窗口
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL && pServerViewItem->GetGameServer().wServerID == nGameServerID)
		{
			DeleteServerViewItem(pServerViewItem);
			break;
		}
	}
}

void CPlatformFrame::ActiveGameServe(int nGameServerID)
{
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//获取窗口
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL && pServerViewItem->GetGameServer().wServerID == nGameServerID)
		{
			ActiveServerViewItem(pServerViewItem);
			break;
		}
	}
}

void CPlatformFrame::PopSysMessage()
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	CString sContent;
	sContent.Format("ID=%d",pGlobalUserInfo->GetGlobalUserData()->dwGameID);
	CString csResponse;
	unsigned short nPort = pGlobalServer->GetPostPort();
	DWORD dwRes = 0;
	CWHService::Post(csResponse,pGlobalServer->GetPlatformServer(4),nPort,"GetPopMsg.aspx",sContent,dwRes,TRUE);
	CString sPopMsgUrl = csResponse;
	if (sPopMsgUrl.Find("http://")!=-1)
	{
		CMessagePop *m_pPopDlg = new CMessagePop;
		m_pPopDlg->SetWindowSize(480,380,480,380-72-55);
		m_pPopDlg->InitWebDlg(sPopMsgUrl,"系统公告",false,true,10);

		m_pPopDlg->Create(IDD_DIALOG_MSGPOP,this);
		m_pPopDlg->SetForegroundWindow();
		m_pPopDlg->ShowWindow(SW_SHOW);
	}
}

void CPlatformFrame::ClosePazza(int nType)//1,关闭客户端;2,切换账号
{
	if (nType == 1)
	{
		SetTimer(IDI_CLOSE_PAZZA,500,NULL);;
	}
	else if (nType==2)
	{
		//发送事件
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);
	}
	//CGlobalUnits::GetInstance()->DeleteUserCookie();
	//CGlobalUserInfo::GetInstance()->ResetUserInfoData();
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);
	//__super::OnClose();
}

LRESULT CPlatformFrame::OnSafeBind(WPARAM wParam, LPARAM lParam)
{
	//构造提示
	CString sCoinStr;
	sCoinStr = "您当前金币总额过多，为了您的金币安全，请绑定本机、身份证及手机再进行游戏，点击‘确认’进行绑定。";
	//退出判断
	CInformation Information(CPlatformFrame::GetInstance());
	if(Information.ShowMessageBox(sCoinStr,MB_ICONINFORMATION|MB_OKCANCEL,0) == IDOK)
	{			//显示窗口
		CDlgLockMachine DlgLockMachine;
		DlgLockMachine.DoModal();
	}
	return true;
}

void CPlatformFrame::SetRemInsurePwd(CString sNewInsurePwd)
{
	if (m_sRemInsurePwd == "") //不保存
		return;
	m_sRemInsurePwd = sNewInsurePwd;
	if (m_pInsurePlaza!=NULL && m_pInsurePlaza->m_hWnd!=NULL)
	{
		m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
	}
	CServerViewItem * pServerViewGold=NULL;
	//查找房间
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//获取房间
		ASSERT(m_ServerViewItemArray[i]!=NULL);
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];

		//房间类型
		WORD wServerType=pServerViewItem->GetServerType();
		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();

		//房间判断
		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
		{
			//设置变量
			pServerViewGold=pServerViewItem;
			//房间银行
			ASSERT(pServerViewGold!=NULL);
			if (pServerViewGold->m_pDlgInsureServer!=NULL && pServerViewGold->m_pDlgInsureServer->m_hWnd!=NULL)
			{
				pServerViewGold->m_pDlgInsureServer->SetInsurePass(m_sRemInsurePwd);
			}

			break;
		}
	}
}

void CPlatformFrame::SaveInsurePwd(int nType,int nMinute,LPCTSTR pszInsurePwd)
{
	if (nType == 2) //自动注销
	{
		m_sRemInsurePwd = pszInsurePwd;
		SetTimer(IDI_REM_INSUREPASS,nMinute*1000*60,NULL);
	}
	else if(nType == 3) //保存到本次登录
	{
		m_sRemInsurePwd = pszInsurePwd;
	}
	else //立即注销
	{
		m_sRemInsurePwd = pszInsurePwd;
		SetTimer(IDI_REM_INSUREPASS,1000*3,NULL);
	}
}

void CPlatformFrame::InitData()
{
	CString sGameKindInfoPath;
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	sGameKindInfoPath = pGlobalServer->GetAppPath()+"\\GameKind\\"+"GameKindInfo.xml";
	CCressXML xml;
	if(!xml.LoadFile(sGameKindInfoPath))
	{
		return;
	}
	xml.SelectNodeToList("//items/item");
	while(xml.QueryNode() != NULL)
	{
		CGameKindInfo *pGameKindInfo = new CGameKindInfo;
		pGameKindInfo->nKindID = atoi(xml.GetValueByName("ID"));
		pGameKindInfo->sKindTypePath = xml.GetValueByName("HP");
		pGameKindInfo->sStarLevelPath = xml.GetValueByName("LP");
		m_ServerListData.InsertGameKinfInfo(pGameKindInfo);
	}
}
//////////////////////////////////////////////////////////////////////////////////

