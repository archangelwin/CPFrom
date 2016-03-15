
// AdminControl.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AdminControl.h"
#include "PlatformEvent.h"
#include "DlgLogon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//圆角大小
#define ROUND_CX					4									//圆角宽度
#define ROUND_CY					4									//圆角高度

//屏幕限制
#define LESS_SCREEN_CY				740									//最小高度
#define LESS_SCREEN_CX				1024								//最小宽度

//屏幕位置
#define BORAD_SIZE					5									//边框大小
#define CAPTION_SIZE				79									//标题大小
//控件标识
#define IDC_SERVER_LIST				300									//游戏列表

//////////////////////////////////////////////////////////////////////////////////

//控制按钮
#define IDC_MIN						100									//最小按钮
#define IDC_MAX						101									//最大按钮
#define IDC_SKIN					102									//皮肤按钮
#define IDC_CLOSE					103									//关闭按钮


#define IDM_RESTORE                 106                                 //还原显示
#define IDM_MINIMIZE                107                                 //最小化显示
#define IDM_MAXIMIZE                108                                 //最大化显示

// CAdminControlApp

BEGIN_MESSAGE_MAP(CAdminControlApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAdminControlApp 构造

CAdminControlApp::CAdminControlApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

CAdminControlApp::~CAdminControlApp()
{
	int nUninstRes = crUninstall(); // Uninstall exception handlers
}


// 唯一的一个 CAdminControlApp 对象

CAdminControlApp theApp;


// CAdminControlApp 初始化

BOOL CAdminControlApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。

	//崩溃开始处
// 	CR_INSTALL_INFO info = {0};  
// 	info.cb = sizeof(CR_INSTALL_INFO); 
// 	info.pszAppName = TEXT("AdminControl"); 
// 	info.pszAppVersion = TEXT("1.0.0");     
// 	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;  
// 	info.dwFlags |= CR_INST_DONT_SEND_REPORT;  
// 	info.dwFlags |= CR_INST_NO_GUI;
// 	info.pszErrorReportSaveDir = TEXT("./UMErrReport");  
// 
// 	// Install crash handlers
// 	int nInstResult = crInstall(&info);            
// 	//assert(nInstResult==0);
// 	if(nInstResult!=0)
// 	{
// 		TCHAR buff[256];
// 		crGetLastErrorMsg(buff, 256); // Get last error
// 		_tprintf(_T("%s\n"), buff); // and output it to the screen
// 		return 1;
// 	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	m_ParameterGlobal.LoadParameter();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

//	CAdminControlDlg dlg;
// 	CDlgLogin m_login;
// 	if (m_login.DoModal() != IDOK)
// 	{
// 		return FALSE;
// 	}
// 	m_MissionLogon.ShowLogon();
// 	
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: 在此放置处理何时用
// 		//  “确定”来关闭对话框的代码
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: 在此放置处理何时用
// 		//  “取消”来关闭对话框的代码
// 	}
	const TCHAR szPlazaClass[]=TEXT("UM");
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//注册窗口
	WndClasss.style=CS_DBLCLKS;
	WndClasss.hIcon=NULL;
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName=szPlazaClass;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_HAND_CUR));
	if (AfxRegisterClass(&WndClasss)==FALSE) AfxThrowResourceException();

	AfxInitRichEdit();
	//建立窗口
	CMyFrameWnd * pPlatformFrame=new CMyFrameWnd;
	pPlatformFrame->Create(szPlazaClass,szProduct,WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_SYSMENU,CRect(0,0,0,0));

	m_pMainWnd = pPlatformFrame;
	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////

CMyFrameWnd * CMyFrameWnd::m_pPlatformFrame=NULL;					//框架指针


CMyFrameWnd::CMyFrameWnd()  
{  
// 	CString strMyClass;  
// 	strMyClass  = "A Win";  
// 	Create(NULL, strMyClass, WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX, CRect(40,60, 240, 460), NULL, NULL);  

	//界面变量
	m_bMaxShow=false;
	m_bRectify=false;
	m_rcNormalSize.SetRect(0,0,0,0);
	m_dwAllOnLineCount=0;

// 	//房间变量
// 	m_pServerViewItem=NULL;
	
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);
	m_MissionManager.InsertMissionItem(&m_MissionUserInfo);

	//平台变量
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

}  
//----------------------------------------------------------  
//应用程序物件产生时会在进入程序进入点之前运行  
//-----------------------------------------------------------  

CMyFrameWnd::~CMyFrameWnd()  
{  
	//平台变量
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) m_pPlatformFrame=NULL;

	exit(0);

	return;
}  

//-------------------------------------------------  
//声明消息及对应的处理函数，在出窗口CMyFrameWnd类中  
//-------------------------------------------------  
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)  
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

	ON_MESSAGE(WM_PLATFORM_EVENT,OnMessagePlatformEvent)
	
END_MESSAGE_MAP() 

LRESULT CMyFrameWnd::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//事件处理
	switch (wParam)
	{
	case EVENT_ADMIN_LOGON:			//登录完成
		{
			//显示窗口
			ShowWindow(SW_HIDE);
			m_PlazaViewItem.ShowWindow(SW_SHOWMAXIMIZED);
//			m_PlazaViewItem.ShowWindow(SW_SHOW);
//			m_PlazaViewItem.Create(IDD_ADMINCONTROL_DIALOG,this);

//			SetForegroundWindow();

			//游戏列表
			//			ControlServerList(ServerListControl_Show,false);

			//用户甜饼
			// 			ASSERT(CGlobalUnits::GetInstance()!=NULL);
			// 			if (CGlobalUnits::GetInstance()->DeleteUserCookie())
			// 			{
			// 				CGlobalUnits::GetInstance()->WriteUserCookie();
			// 			}

			//判断身份证，本机绑定
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			//tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

			//if (pIndividualUserData->cbMoorPassPortID == FALSE || pGlobalUserData->cbMoorMachine == 0)
			//{
			//	CInformation Information(this);
			//	Information.ShowMessageBox(TEXT("温馨提示：您未绑定本机和身份证，建议您绑定本机和身份证以确保账号信息安全，以便能及时找回密码！"),MB_ICONERROR,30);
			//}

// 			m_PlazaViewItem.m_ServerList.InitServerTreeView();
// 			CServerListData::GetInstance()->SetServerListDataSink(&m_PlazaViewItem.m_ServerList);

			return 0;
		}
	case EVENT_USER_LOGOUT:			//注销成功
		{
			//激活广场
			//			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//关闭房间
			// 			if (m_pServerViewItem!=NULL)
			// 			{
			// 				if(!DeleteServerViewItem(m_pServerViewItem))return 0L;
			// 			}

			//关闭房间
			// 			while (m_ServerViewItemArray.GetCount()>0)
			// 			{
			// 				if(!DeleteServerViewItem(m_ServerViewItemArray[0]))return 0L;
			// 			}

			//隐藏窗口
			//			ShowWindow(SW_HIDE);

			//显示登录
			//m_MissionLogon.ShowLogon();

			return 0;
		}
	case EVENT_DOWN_LOAD_FINISH:	//下载完成
		{
			//获取参数
			// 			WORD wKindID=LOWORD(lParam);
			// 			WORD wServerID=HIWORD(lParam);
			// 
			// 			//更新列表
			// 			CServerListData * pServerListData=CServerListData::GetInstance();
			// 			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);
			// 
			// 			//进入房间
			// 			if ((wKindID!=0)&&(wServerID!=0))
			// 			{
			// 				CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
			// 				if (pGameServerItem!=NULL) EntranceServerItem(pGameServerItem);
			// 			}
			// 
			// 			return 0L;
		}
	}

	return 0;
}

//调整控件
VOID CMyFrameWnd::RectifyControl(INT nWidth, INT nHeight)
{

	//状态判断
	if ((nWidth==0)||(nHeight==0)) return;

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//控制按钮
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-94,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-66,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-38,0,0,0,uFlags|SWP_NOSIZE);

//	DeferWindowPos(hDwp,m_ServerListView,NULL,0,0,100,100,uFlags);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	return;
}

//位置消息
VOID CMyFrameWnd::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	//创建区域
//	CRgn WindowRgn;
//	GetWindowRect(&WindowRgn);
//	WindowRgn.CreateRoundRectRgn(0,0,cx+1,cy+1,ROUND_CX,ROUND_CY);

	//设置区域
//	SetWindowRgn(WindowRgn,TRUE);
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	MoveWindow(WindowRect);

	return;
}


//关闭消息
VOID CMyFrameWnd::OnClose()
{


	__super::OnClose();
}

//位置信息
VOID CMyFrameWnd::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
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

//鼠标消息
VOID CMyFrameWnd::OnLButtonDown(UINT nFlags, CPoint Point)
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
VOID CMyFrameWnd::OnLButtonDblClk(UINT nFlags, CPoint Point)
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


//时间消息
VOID CMyFrameWnd::OnTimer(UINT_PTR nIDEvent)
{

	__super::OnTimer(nIDEvent);
}

//
BOOL CMyFrameWnd::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
// 	if (m_ToolTipCtrl.m_hWnd!=NULL)
// 	{
// 		m_ToolTipCtrl.RelayEvent(pMsg);
// 	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL CMyFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);

	//功能按钮
	switch (nCommandID)
	{
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
			//PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_SKIN:				//界面控制
		{
			//创建窗口
// 			if (m_DlgSkinControl.m_hWnd==NULL)
// 			{
// 				m_DlgSkinControl.Create(IDD_SKIN_CONTROL,this);
// 			}
// 
// 			//获取位置
// 			CRect rcButton;
// 			CRect rcControl;
// 			m_btSkin.GetWindowRect(&rcButton);
// 			m_DlgSkinControl.GetWindowRect(&rcControl);
// 
// 			//显示窗口
// 			UINT uFlags=SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;
// 			m_DlgSkinControl.SetWindowPos(NULL,rcButton.right-rcControl.Width(),rcButton.bottom,0,0,uFlags);

			return TRUE;
		}
// 	case IDC_CONTROL:			//控制按钮
// 		{
// 			//控制列表
// 			ControlServerList(ServerListControl_Turn,true);
// 
// 			return TRUE;
// 		}
// 	case IDC_LOCK_LIST:			//锁定列表
// 		{
// 			//设置变量
// 			m_bLockGameList=!m_bLockGameList;
// 
// 			//设置按钮
// 			HINSTANCE hInstance=AfxGetInstanceHandle();
// 			m_btLockList.SetButtonImage(IDB_BK_LIST,(m_bLockGameList==true)?TEXT("BT_UNLOCK_LIST"):TEXT("BT_LOCK_LIST"),hInstance,true,false);
// 
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+2:
// 		{
// 			//变量定义
// 			bool bGoldServer=false;
// 			CServerViewItem * pServerViewGold=NULL;
// 
// 			//查找房间
// 			for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
// 			{
// 				//获取房间
// 				ASSERT(m_ServerViewItemArray[i]!=NULL);
// 				CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
// 
// 				//房间类型
// 				WORD wServerType=pServerViewItem->GetServerType();
// 				enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();
// 
// 				//房间判断
// 				if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
// 				{
// 					//设置变量
// 					bGoldServer=true;
// 					pServerViewGold=pServerViewItem;
// 
// 					break;
// 				}
// 			}
// 
// 			//设置资源
// 			AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
// 
// 			//银行中心
// 			if (bGoldServer==false)
// 			{
// 				//广场银行
// 				CDlgInsurePlaza DlgInsurePlaza;
// 				INT_PTR nResult=DlgInsurePlaza.DoModal();
// 			}
// 			else
// 			{
// 				//房间银行
// 				ASSERT(pServerViewGold!=NULL);
// 				pServerViewGold->ShowInsureView();
// 			}
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+0:
// 	case IDC_NAVIGATION+1:
// 		{
// 			//变量定义
// 			// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 			// 
// 			// 			//构造地址
// 			// 			TCHAR szNavigation[256]=TEXT("");
// 			// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),szPlatformLink,(nCommandID-IDC_NAVIGATION)+1);
// 			// 
// 			// 			//连接地址
// 			// 			WebBrowse(szNavigation,true);
// 			// 
// 			// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+3:       //导航按钮
// 		{
// 			//变量定义
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//构造地址
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),szPlatformLink,(nCommandID-IDC_NAVIGATION)+1);
// 
// 			//连接地址
// 			WebBrowse(szNavigation,true);
// 
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+4:		//客服按钮
// 		{
// 			//变量定义
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//构造地址
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),szPlatformLink);
// 			/*_sntprintf(szNavigation,CountArray(szNavigation),TEXT("http://wpa.qq.com/msgrd?v=3&uin=653969305&site=qq&menu=yes"));*/
// 
// 			//连接地址
// 			WebBrowse(szNavigation,true);
// 
// 			return TRUE;
// 
// 		}
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
// 			if ((m_ServerViewItemArray.GetCount()>0L)||(m_pServerViewItem!=NULL))
// 			{
// // 				CInformation Information(this);
// // 				if (Information.ShowMessageBox(TEXT("所有的游戏房间即将关闭，确实要“切换帐号”吗？ "),MB_YESNO)!=IDYES) return TRUE;
// 
// 			}

			//全局设置
// 			CGlobalUnits::GetInstance()->DeleteUserCookie();
// 			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
// 
// 			//发送事件
// 			CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
// 			if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);

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
			//MaxSizeWindow();
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

INT CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置窗口
	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);

	CRect rcCreate(0,0,0,0);


	m_PlazaViewItem.Create(IDD_ADMINCONTROL_DIALOG,NULL/*this*/);
//	m_PlazaViewItem.ShowWindow(SW_SHOWMAXIMIZED);


// 	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MIN);
// 	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MAX);
// 	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLOSE);


// 	m_ToolTipCtrl.Create(this);
// 	m_ToolTipCtrl.Activate(TRUE);
// 	m_ToolTipCtrl.AddTool(&m_btMin,TEXT("最小化"));
// 	m_ToolTipCtrl.AddTool(&m_btMax,TEXT("最大化"));
// 	m_ToolTipCtrl.AddTool(&m_btClose,TEXT("关闭游戏"));

	//注册事件
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//设置位置
// 	CSize SizeRestrict;
// 	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);
// 
// 	//窗口位置
// 	CRect rcArce;
// 	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);
// 
// 	//读取位置
// 	CWHRegKey InfoKeyItem;
// 	if (InfoKeyItem.OpenRegKey(REG_INTERFACE_INFO,false)==true)
// 	{
// 		SizeRestrict.cx=InfoKeyItem.GetValue(TEXT("ScreenWidth"),rcArce.Width()/2);
// 		SizeRestrict.cy=InfoKeyItem.GetValue(TEXT("ScreenHeight"),rcArce.Height()/2);
// 	}
// 
// 	//位置调整
// 	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
// 	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
// 	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
// 	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);
// 
// 	//移动窗口
// 	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
// 	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
// 	m_rcNormalSize.right=m_rcNormalSize.left+SizeRestrict.cx;
// 	m_rcNormalSize.bottom=m_rcNormalSize.top+SizeRestrict.cy;
// 	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	MaxSizeWindow();


	//登录系统
	SendMessage(WM_COMMAND,IDM_USER_LOGON,0);


	m_MissionUserInfo.m_GameUserListDlg = &m_PlazaViewItem.m_GameUserListDlg;
	m_MissionUserInfo.m_StockDlg = &m_PlazaViewItem.m_StockDlg;
	m_MissionUserInfo.m_pLogDlg = &m_PlazaViewItem.m_LogDlg;
	m_MissionUserInfo.m_pOnLineUserSortDlg = &m_PlazaViewItem.m_OnLineUserSortDlg;
	m_MissionUserInfo.m_pOffLineUserDlg = &m_PlazaViewItem.m_OffLineUserDlg;
	m_MissionUserInfo.m_pSilverDlg = &m_PlazaViewItem.m_SilverDlg;

	return 0;
}

//还原窗口
bool CMyFrameWnd::RestoreWindow()
{
	//状态判断
	if (m_bMaxShow==true)
	{
		//设置变量
		m_bMaxShow=false;
		m_bRectify=false;

		//设置按钮
//		m_btMax.SetButtonImage(IDB_BT_MAX,AfxGetInstanceHandle(),true,false);

		//移动窗口
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//最大窗口
bool CMyFrameWnd::MaxSizeWindow()
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
//		m_btMax.SetButtonImage(IDB_BT_RESORE,AfxGetInstanceHandle(),true,false);

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

LRESULT CMyFrameWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(message==0x0313)
	{
		//创建菜单
// 		CSkinMenu Menu;
// 		Menu.CreateMenu();
// 
// 		//构造菜单
// 		Menu.AppendMenu(IDM_RESTORE,TEXT("还原"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
// 		Menu.AppendMenu(IDM_MINIMIZE,TEXT("最小化"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
// 		Menu.AppendMenu(IDM_MAXIMIZE,TEXT("最大化"));
// 		Menu.AppendSeparator();
// 		Menu.AppendMenu(IDC_CLOSE,TEXT("退出广场"));
// 		//Menu.AppendSeparator();
// 		//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("关于..."));
// 
// 		//显示菜单
// 		CPoint MousePoint;
// 		GetCursorPos(&MousePoint);
// 		Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

		return 0;
	}

	return __super::WindowProc(message, wParam, lParam);
}

//更新总在线人数
void CMyFrameWnd::UpDataAllOnLineCount()
{
	DWORD dwAllOnLineCount = GetAllOnLineCount();
	if(m_dwAllOnLineCount != dwAllOnLineCount)
	{
		m_dwAllOnLineCount = dwAllOnLineCount;
		RedrawWindow();
	}
}

//获取总在线人数
DWORD CMyFrameWnd::GetAllOnLineCount()
{
//	return m_PlazaViewItem.m_ServerData.GetAllOnLineCount();

	return 0;
}