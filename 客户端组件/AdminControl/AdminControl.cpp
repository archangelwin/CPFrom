
// AdminControl.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "AdminControl.h"
#include "PlatformEvent.h"
#include "DlgLogon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Բ�Ǵ�С
#define ROUND_CX					4									//Բ�ǿ��
#define ROUND_CY					4									//Բ�Ǹ߶�

//��Ļ����
#define LESS_SCREEN_CY				740									//��С�߶�
#define LESS_SCREEN_CX				1024								//��С���

//��Ļλ��
#define BORAD_SIZE					5									//�߿��С
#define CAPTION_SIZE				79									//�����С
//�ؼ���ʶ
#define IDC_SERVER_LIST				300									//��Ϸ�б�

//////////////////////////////////////////////////////////////////////////////////

//���ư�ť
#define IDC_MIN						100									//��С��ť
#define IDC_MAX						101									//���ť
#define IDC_SKIN					102									//Ƥ����ť
#define IDC_CLOSE					103									//�رհ�ť


#define IDM_RESTORE                 106                                 //��ԭ��ʾ
#define IDM_MINIMIZE                107                                 //��С����ʾ
#define IDM_MAXIMIZE                108                                 //�����ʾ

// CAdminControlApp

BEGIN_MESSAGE_MAP(CAdminControlApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAdminControlApp ����

CAdminControlApp::CAdminControlApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CAdminControlApp::~CAdminControlApp()
{
	int nUninstRes = crUninstall(); // Uninstall exception handlers
}


// Ψһ��һ�� CAdminControlApp ����

CAdminControlApp theApp;


// CAdminControlApp ��ʼ��

BOOL CAdminControlApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�

	//������ʼ��
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
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	m_ParameterGlobal.LoadParameter();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
// 		// TODO: �ڴ˷��ô����ʱ��
// 		//  ��ȷ�������رնԻ���Ĵ���
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: �ڴ˷��ô����ʱ��
// 		//  ��ȡ�������رնԻ���Ĵ���
// 	}
	const TCHAR szPlazaClass[]=TEXT("UM");
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//ע�ᴰ��
	WndClasss.style=CS_DBLCLKS;
	WndClasss.hIcon=NULL;
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName=szPlazaClass;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_HAND_CUR));
	if (AfxRegisterClass(&WndClasss)==FALSE) AfxThrowResourceException();

	AfxInitRichEdit();
	//��������
	CMyFrameWnd * pPlatformFrame=new CMyFrameWnd;
	pPlatformFrame->Create(szPlazaClass,szProduct,WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_SYSMENU,CRect(0,0,0,0));

	m_pMainWnd = pPlatformFrame;
	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////

CMyFrameWnd * CMyFrameWnd::m_pPlatformFrame=NULL;					//���ָ��


CMyFrameWnd::CMyFrameWnd()  
{  
// 	CString strMyClass;  
// 	strMyClass  = "A Win";  
// 	Create(NULL, strMyClass, WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX, CRect(40,60, 240, 460), NULL, NULL);  

	//�������
	m_bMaxShow=false;
	m_bRectify=false;
	m_rcNormalSize.SetRect(0,0,0,0);
	m_dwAllOnLineCount=0;

// 	//�������
// 	m_pServerViewItem=NULL;
	
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);
	m_MissionManager.InsertMissionItem(&m_MissionUserInfo);

	//ƽ̨����
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

}  
//----------------------------------------------------------  
//Ӧ�ó����������ʱ���ڽ����������֮ǰ����  
//-----------------------------------------------------------  

CMyFrameWnd::~CMyFrameWnd()  
{  
	//ƽ̨����
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) m_pPlatformFrame=NULL;

	exit(0);

	return;
}  

//-------------------------------------------------  
//������Ϣ����Ӧ�Ĵ��������ڳ�����CMyFrameWnd����  
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
	//�¼�����
	switch (wParam)
	{
	case EVENT_ADMIN_LOGON:			//��¼���
		{
			//��ʾ����
			ShowWindow(SW_HIDE);
			m_PlazaViewItem.ShowWindow(SW_SHOWMAXIMIZED);
//			m_PlazaViewItem.ShowWindow(SW_SHOW);
//			m_PlazaViewItem.Create(IDD_ADMINCONTROL_DIALOG,this);

//			SetForegroundWindow();

			//��Ϸ�б�
			//			ControlServerList(ServerListControl_Show,false);

			//�û����
			// 			ASSERT(CGlobalUnits::GetInstance()!=NULL);
			// 			if (CGlobalUnits::GetInstance()->DeleteUserCookie())
			// 			{
			// 				CGlobalUnits::GetInstance()->WriteUserCookie();
			// 			}

			//�ж����֤��������
			//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			//tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

			//if (pIndividualUserData->cbMoorPassPortID == FALSE || pGlobalUserData->cbMoorMachine == 0)
			//{
			//	CInformation Information(this);
			//	Information.ShowMessageBox(TEXT("��ܰ��ʾ����δ�󶨱��������֤���������󶨱��������֤��ȷ���˺���Ϣ��ȫ���Ա��ܼ�ʱ�һ����룡"),MB_ICONERROR,30);
			//}

// 			m_PlazaViewItem.m_ServerList.InitServerTreeView();
// 			CServerListData::GetInstance()->SetServerListDataSink(&m_PlazaViewItem.m_ServerList);

			return 0;
		}
	case EVENT_USER_LOGOUT:			//ע���ɹ�
		{
			//����㳡
			//			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//�رշ���
			// 			if (m_pServerViewItem!=NULL)
			// 			{
			// 				if(!DeleteServerViewItem(m_pServerViewItem))return 0L;
			// 			}

			//�رշ���
			// 			while (m_ServerViewItemArray.GetCount()>0)
			// 			{
			// 				if(!DeleteServerViewItem(m_ServerViewItemArray[0]))return 0L;
			// 			}

			//���ش���
			//			ShowWindow(SW_HIDE);

			//��ʾ��¼
			//m_MissionLogon.ShowLogon();

			return 0;
		}
	case EVENT_DOWN_LOAD_FINISH:	//�������
		{
			//��ȡ����
			// 			WORD wKindID=LOWORD(lParam);
			// 			WORD wServerID=HIWORD(lParam);
			// 
			// 			//�����б�
			// 			CServerListData * pServerListData=CServerListData::GetInstance();
			// 			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);
			// 
			// 			//���뷿��
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

//�����ؼ�
VOID CMyFrameWnd::RectifyControl(INT nWidth, INT nHeight)
{

	//״̬�ж�
	if ((nWidth==0)||(nHeight==0)) return;

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//���ư�ť
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-94,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-66,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-38,0,0,0,uFlags|SWP_NOSIZE);

//	DeferWindowPos(hDwp,m_ServerListView,NULL,0,0,100,100,uFlags);

	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	return;
}

//λ����Ϣ
VOID CMyFrameWnd::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	//��������
//	CRgn WindowRgn;
//	GetWindowRect(&WindowRgn);
//	WindowRgn.CreateRoundRectRgn(0,0,cx+1,cy+1,ROUND_CX,ROUND_CY);

	//��������
//	SetWindowRgn(WindowRgn,TRUE);
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	MoveWindow(WindowRect);

	return;
}


//�ر���Ϣ
VOID CMyFrameWnd::OnClose()
{


	__super::OnClose();
}

//λ����Ϣ
VOID CMyFrameWnd::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);

	//����λ��
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//����λ��
	lpMMI->ptMinTrackSize.x=__min(LESS_SCREEN_CX,rcArce.Width());
	lpMMI->ptMinTrackSize.y=__min(LESS_SCREEN_CY,rcArce.Height());

	return;
}

//�����Ϣ
VOID CMyFrameWnd::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//�����Ϣ
VOID CMyFrameWnd::OnLButtonDblClk(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDblClk(nFlags,Point);

	//״̬�ж�
	if (Point.y>CAPTION_SIZE) return;

	//���ڿ���
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


//ʱ����Ϣ
VOID CMyFrameWnd::OnTimer(UINT_PTR nIDEvent)
{

	__super::OnTimer(nIDEvent);
}

//
BOOL CMyFrameWnd::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
// 	if (m_ToolTipCtrl.m_hWnd!=NULL)
// 	{
// 		m_ToolTipCtrl.RelayEvent(pMsg);
// 	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL CMyFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//���ܰ�ť
	switch (nCommandID)
	{
	case IDC_MIN:				//��С��ť
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_MAX:				//���ť
		{
			//���ڿ���
			if (m_bMaxShow==true)
			{
				RestoreWindow();
			}
			else
			{
				MaxSizeWindow();
			}

			//���½���
			RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW);

			return TRUE;
		}
	case IDC_CLOSE:				//�رհ�ť
		{
			//PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_SKIN:				//�������
		{
			//��������
// 			if (m_DlgSkinControl.m_hWnd==NULL)
// 			{
// 				m_DlgSkinControl.Create(IDD_SKIN_CONTROL,this);
// 			}
// 
// 			//��ȡλ��
// 			CRect rcButton;
// 			CRect rcControl;
// 			m_btSkin.GetWindowRect(&rcButton);
// 			m_DlgSkinControl.GetWindowRect(&rcControl);
// 
// 			//��ʾ����
// 			UINT uFlags=SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;
// 			m_DlgSkinControl.SetWindowPos(NULL,rcButton.right-rcControl.Width(),rcButton.bottom,0,0,uFlags);

			return TRUE;
		}
// 	case IDC_CONTROL:			//���ư�ť
// 		{
// 			//�����б�
// 			ControlServerList(ServerListControl_Turn,true);
// 
// 			return TRUE;
// 		}
// 	case IDC_LOCK_LIST:			//�����б�
// 		{
// 			//���ñ���
// 			m_bLockGameList=!m_bLockGameList;
// 
// 			//���ð�ť
// 			HINSTANCE hInstance=AfxGetInstanceHandle();
// 			m_btLockList.SetButtonImage(IDB_BK_LIST,(m_bLockGameList==true)?TEXT("BT_UNLOCK_LIST"):TEXT("BT_LOCK_LIST"),hInstance,true,false);
// 
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+2:
// 		{
// 			//��������
// 			bool bGoldServer=false;
// 			CServerViewItem * pServerViewGold=NULL;
// 
// 			//���ҷ���
// 			for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
// 			{
// 				//��ȡ����
// 				ASSERT(m_ServerViewItemArray[i]!=NULL);
// 				CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
// 
// 				//��������
// 				WORD wServerType=pServerViewItem->GetServerType();
// 				enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();
// 
// 				//�����ж�
// 				if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
// 				{
// 					//���ñ���
// 					bGoldServer=true;
// 					pServerViewGold=pServerViewItem;
// 
// 					break;
// 				}
// 			}
// 
// 			//������Դ
// 			AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
// 
// 			//��������
// 			if (bGoldServer==false)
// 			{
// 				//�㳡����
// 				CDlgInsurePlaza DlgInsurePlaza;
// 				INT_PTR nResult=DlgInsurePlaza.DoModal();
// 			}
// 			else
// 			{
// 				//��������
// 				ASSERT(pServerViewGold!=NULL);
// 				pServerViewGold->ShowInsureView();
// 			}
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+0:
// 	case IDC_NAVIGATION+1:
// 		{
// 			//��������
// 			// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 			// 
// 			// 			//�����ַ
// 			// 			TCHAR szNavigation[256]=TEXT("");
// 			// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),szPlatformLink,(nCommandID-IDC_NAVIGATION)+1);
// 			// 
// 			// 			//���ӵ�ַ
// 			// 			WebBrowse(szNavigation,true);
// 			// 
// 			// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+3:       //������ť
// 		{
// 			//��������
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//�����ַ
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),szPlatformLink,(nCommandID-IDC_NAVIGATION)+1);
// 
// 			//���ӵ�ַ
// 			WebBrowse(szNavigation,true);
// 
// 			return TRUE;
// 		}
// 	case IDC_NAVIGATION+4:		//�ͷ���ť
// 		{
// 			//��������
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//�����ַ
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),szPlatformLink);
// 			/*_sntprintf(szNavigation,CountArray(szNavigation),TEXT("http://wpa.qq.com/msgrd?v=3&uin=653969305&site=qq&menu=yes"));*/
// 
// 			//���ӵ�ַ
// 			WebBrowse(szNavigation,true);
// 
// 			return TRUE;
// 
// 		}
 	}

	//�˵�����
	switch (nCommandID)
	{
	case IDM_USER_LOGON:		//�û���¼
		{
			m_MissionLogon.ShowLogon();

			return TRUE;
		}
	case IDM_SWITCH_ACCOUNTS:	//�л��ʺ�
		{
			//�л�ѯ��
// 			if ((m_ServerViewItemArray.GetCount()>0L)||(m_pServerViewItem!=NULL))
// 			{
// // 				CInformation Information(this);
// // 				if (Information.ShowMessageBox(TEXT("���е���Ϸ���伴���رգ�ȷʵҪ���л��ʺš��� "),MB_YESNO)!=IDYES) return TRUE;
// 
// 			}

			//ȫ������
// 			CGlobalUnits::GetInstance()->DeleteUserCookie();
// 			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
// 
// 			//�����¼�
// 			CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
// 			if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);

			return TRUE;
		}
	case IDM_RESTORE:   //��ԭ
		{
			if(IsIconic())
			{
				ShowWindow(SW_RESTORE);
			}
			return TRUE;
		}
	case IDM_MINIMIZE:  //��С��
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDM_MAXIMIZE:  //���
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

	//���ô���
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
// 	m_ToolTipCtrl.AddTool(&m_btMin,TEXT("��С��"));
// 	m_ToolTipCtrl.AddTool(&m_btMax,TEXT("���"));
// 	m_ToolTipCtrl.AddTool(&m_btClose,TEXT("�ر���Ϸ"));

	//ע���¼�
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//����λ��
// 	CSize SizeRestrict;
// 	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);
// 
// 	//����λ��
// 	CRect rcArce;
// 	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);
// 
// 	//��ȡλ��
// 	CWHRegKey InfoKeyItem;
// 	if (InfoKeyItem.OpenRegKey(REG_INTERFACE_INFO,false)==true)
// 	{
// 		SizeRestrict.cx=InfoKeyItem.GetValue(TEXT("ScreenWidth"),rcArce.Width()/2);
// 		SizeRestrict.cy=InfoKeyItem.GetValue(TEXT("ScreenHeight"),rcArce.Height()/2);
// 	}
// 
// 	//λ�õ���
// 	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
// 	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
// 	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
// 	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);
// 
// 	//�ƶ�����
// 	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
// 	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
// 	m_rcNormalSize.right=m_rcNormalSize.left+SizeRestrict.cx;
// 	m_rcNormalSize.bottom=m_rcNormalSize.top+SizeRestrict.cy;
// 	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	MaxSizeWindow();


	//��¼ϵͳ
	SendMessage(WM_COMMAND,IDM_USER_LOGON,0);


	m_MissionUserInfo.m_GameUserListDlg = &m_PlazaViewItem.m_GameUserListDlg;
	m_MissionUserInfo.m_StockDlg = &m_PlazaViewItem.m_StockDlg;
	m_MissionUserInfo.m_pLogDlg = &m_PlazaViewItem.m_LogDlg;
	m_MissionUserInfo.m_pOnLineUserSortDlg = &m_PlazaViewItem.m_OnLineUserSortDlg;
	m_MissionUserInfo.m_pOffLineUserDlg = &m_PlazaViewItem.m_OffLineUserDlg;
	m_MissionUserInfo.m_pSilverDlg = &m_PlazaViewItem.m_SilverDlg;

	return 0;
}

//��ԭ����
bool CMyFrameWnd::RestoreWindow()
{
	//״̬�ж�
	if (m_bMaxShow==true)
	{
		//���ñ���
		m_bMaxShow=false;
		m_bRectify=false;

		//���ð�ť
//		m_btMax.SetButtonImage(IDB_BT_MAX,AfxGetInstanceHandle(),true,false);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//��󴰿�
bool CMyFrameWnd::MaxSizeWindow()
{
	//״̬�ж�
	if (m_bMaxShow==false)
	{
		//���ñ���
		m_bMaxShow=true;
		m_bRectify=false;

		//Ĭ��λ��
		GetWindowRect(&m_rcNormalSize);

		//���ð�ť
//		m_btMax.SetButtonImage(IDB_BT_RESORE,AfxGetInstanceHandle(),true,false);

		//��ȡλ��
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

LRESULT CMyFrameWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(message==0x0313)
	{
		//�����˵�
// 		CSkinMenu Menu;
// 		Menu.CreateMenu();
// 
// 		//����˵�
// 		Menu.AppendMenu(IDM_RESTORE,TEXT("��ԭ"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
// 		Menu.AppendMenu(IDM_MINIMIZE,TEXT("��С��"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
// 		Menu.AppendMenu(IDM_MAXIMIZE,TEXT("���"));
// 		Menu.AppendSeparator();
// 		Menu.AppendMenu(IDC_CLOSE,TEXT("�˳��㳡"));
// 		//Menu.AppendSeparator();
// 		//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("����..."));
// 
// 		//��ʾ�˵�
// 		CPoint MousePoint;
// 		GetCursorPos(&MousePoint);
// 		Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

		return 0;
	}

	return __super::WindowProc(message, wParam, lParam);
}

//��������������
void CMyFrameWnd::UpDataAllOnLineCount()
{
	DWORD dwAllOnLineCount = GetAllOnLineCount();
	if(m_dwAllOnLineCount != dwAllOnLineCount)
	{
		m_dwAllOnLineCount = dwAllOnLineCount;
		RedrawWindow();
	}
}

//��ȡ����������
DWORD CMyFrameWnd::GetAllOnLineCount()
{
//	return m_PlazaViewItem.m_ServerData.GetAllOnLineCount();

	return 0;
}