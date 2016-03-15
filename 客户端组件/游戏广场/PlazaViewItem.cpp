#include "StdAfx.h"
#include "ExDispID.h"
#include "GamePlaza.h"
#include "PlazaViewItem.h"
#include "WndViewItemCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//控件标识
#define IDC_PLAZA_BROWSER			100									//浏览控件
#define IDC_PLAZA_MESSAGE           101                                 //消息提示
//////////////////////////////////////////////////////////////////////////////////

//静态变量
CPlazaViewItem * CPlazaViewItem::m_pPlazaViewItem=NULL;					//广场指针

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlazaViewItem, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPlazaBrowser, CHtmlView)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CPlazaBrowser, CHtmlView)
	ON_EVENT(CPlazaBrowser, AFX_IDW_PANE_FIRST, DISPID_WINDOWCLOSING, OnWindowClosing,VTS_BOOL VTS_PBOOL)   
END_EVENTSINK_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPlazaBrowser::CPlazaBrowser()
{
}

//析构函数
CPlazaBrowser::~CPlazaBrowser()
{
}

//绑定函数
VOID CPlazaBrowser::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//设置背景
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return;
}

//消耗处理
VOID CPlazaBrowser::PostNcDestroy()
{
	return;
}

//创建函数
BOOL CPlazaBrowser::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT & rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	//设置变量
	m_pCreateContext=pContext;

	//创建窗口
	if (CView::Create(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID,pContext)==FALSE)
	{
		return FALSE;
	}

	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建窗口
	if (m_wndBrowser.CreateControl(CLSID_WebBrowser,lpszWindowName,WS_VISIBLE|WS_CHILD,rcClient,this,AFX_IDW_PANE_FIRST)==FALSE)
	{
		DestroyWindow();
		return FALSE;
	}

	//查询接口
	LPUNKNOWN lpUnknown=m_wndBrowser.GetControlUnknown();
	lpUnknown->QueryInterface(IID_IWebBrowser2,(VOID **)&m_pBrowserApp);

	return TRUE;
}

//关闭事件
void CPlazaBrowser::OnWindowClosing(BOOL IsChildWindow, BOOL *bCancel)   
{   
	//禁止关闭
	if ((IsChildWindow==FALSE)&&(bCancel!=NULL))
	{
		*bCancel=TRUE;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPlazaViewItem::CPlazaViewItem() : CDialog(IDD_GAME_PLAZA)
{
	//设置变量
	m_bCreateFlag=false;

	//设置对象
	ASSERT(m_pPlazaViewItem==NULL);
	if (m_pPlazaViewItem==NULL) m_pPlazaViewItem=this;

	//浏览资源
	//tagEncircleResource	EncircleBrowser;
	//EncircleBrowser.pszImageTL=MAKEINTRESOURCE(IDB_BROWSER_TL);
	//EncircleBrowser.pszImageTM=MAKEINTRESOURCE(IDB_BROWSER_TM);
	//EncircleBrowser.pszImageTR=MAKEINTRESOURCE(IDB_BROWSER_TR);
	//EncircleBrowser.pszImageML=MAKEINTRESOURCE(IDB_BROWSER_ML);
	//EncircleBrowser.pszImageMR=MAKEINTRESOURCE(IDB_BROWSER_MR);
	//EncircleBrowser.pszImageBL=MAKEINTRESOURCE(IDB_BROWSER_BL);
	//EncircleBrowser.pszImageBM=MAKEINTRESOURCE(IDB_BROWSER_BM);
	//EncircleBrowser.pszImageBR=MAKEINTRESOURCE(IDB_BROWSER_BR);
	//m_BrowserEncircle.InitEncircleResource(EncircleBrowser,AfxGetInstanceHandle());

	return;
}

//析构函数
CPlazaViewItem::~CPlazaViewItem()
{
}

//接口查询
VOID * CPlazaViewItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//控件绑定
VOID CPlazaViewItem::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GOOD_NUM, m_btGoodNum);
	DDX_Control(pDX, IDC_VIP_MEMBER, m_btVIP);
	DDX_Control(pDX, IDC_MOBILE_GAME, m_btMobileGame);
	DDX_Control(pDX, IDC_WEB_HOME, m_btWebHome);
	DDX_Control(pDX, IDC_GET_PRIZE, m_btGetPrize);
}

//创建函数
BOOL CPlazaViewItem::OnInitDialog()
{
	__super::OnInitDialog();

	//创建控件
	CRect rcCreate(0,0,0,0);
	m_PlazaBrowser.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLAZA_BROWSER,NULL);
//	m_PlazaMessage.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLAZA_MESSAGE,NULL);
	//m_PlazaBrowser.ShowWindow(SW_HIDE);

	//网页按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btGoodNum.SetButtonImage(IDB_BT_GOODNUM,hInstance,true,false);
	m_btVIP.SetButtonImage(IDB_BT_VIPMEMBER,hInstance,true,false);
	m_btMobileGame.SetButtonImage(IDB_BT_MOBILEGAME,hInstance,true,false);
	m_btWebHome.SetButtonImage(IDB_BT_BROWSER_HOME,hInstance,true,false);
	m_btGetPrize.SetButtonImage(IDB_BT_GET_PRIZE,hInstance,true,false);

	//提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btGoodNum,TEXT("靓号"));
	m_ToolTipCtrl.AddTool(&m_btVIP,TEXT("VIP"));
	m_ToolTipCtrl.AddTool(&m_btMobileGame,TEXT("手机游戏"));
	m_ToolTipCtrl.AddTool(&m_btWebHome,TEXT("主页"));
	m_ToolTipCtrl.AddTool(&m_btGetPrize,TEXT("抽奖"));

	//设置变量
	m_bCreateFlag=true;

	return TRUE;
}

//消息过虑
BOOL CPlazaViewItem::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
	if (m_ToolTipCtrl.m_hWnd!=NULL) 
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//命令函数
BOOL CPlazaViewItem::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);

	//菜单命令
	switch (nCommandID)
	{
	case IDC_GOOD_NUM:		//后退按钮
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Service/NiceNumberPlaz.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.GoBack();
			return TRUE;
		}
	case IDC_VIP_MEMBER:		//前进按钮
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Shop/Mall.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.GoForward();
			return TRUE;
		}
	case IDC_MOBILE_GAME:		//停止按钮
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Games/PhoneGame.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.Stop();
			return TRUE;
		}
	case IDC_WEB_HOME:		//主页按钮
		{
			//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			//CString sMainUrl;
			//sMainUrl.Format("%s/index.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(m_sMainUrl);
			return TRUE;
		}
	case IDC_GET_PRIZE:	//抽奖按钮
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Roulette/Default.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//位置消息
VOID CPlazaViewItem::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	return;
}

//绘画背景
BOOL CPlazaViewItem::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,RGB(255,255,255));
	//pDC->FillSolidRect(&rcClient,RGB(255,0,0));

	//pDC->Draw3dRect(rcClient,RGB(255,0,0),RGB(255,0,0));

	//绘画网页
	//CRect rcBrowse;
	//rcBrowse.top=0;
	//rcBrowse.left=0;
	//rcBrowse.right=rcClient.Width();
	//rcBrowse.bottom=rcClient.Height();
	//m_BrowserEncircle.DrawEncircleFrame(pDC,rcBrowse);

	//建立缓冲
	CImage ImageBuffer;
	if(ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32) == FALSE) return TRUE;

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//变量定义
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	CBitImage ImageTitleL,ImageTitleM,ImageTitleR;
	//ImageTitleL.LoadFromResource(hInstance,IDB_BROWSER_TL);
	ImageTitleM.LoadFromResource(hInstance,IDB_BROWSER_TM);
	//ImageTitleR.LoadFromResource(hInstance,IDB_BROWSER_TR);

	//渲染资源
	//pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	//pSkinRenderManager->RenderImage(ImageTitleR);

	//绘画背景
	//ImageTitleL.BitBlt(BufferDC,0,0);
	//填充中间
	for (INT nXPos=0;nXPos<rcClient.Width();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}
	//绘画背景
	//ImageTitleR.BitBlt(BufferDC,rcClient.Width()-ImageTitleR.GetWidth(),0);

	//绘画衔接
	ASSERT(CWndViewItemCtrl::GetInstance()!=NULL);
	CWndViewItemCtrl::GetInstance()->DrawLinkBoradLine(this,pDC);
	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//浏览页面
bool CPlazaViewItem::WebBrowse(LPCTSTR pszURL)
{
	m_PlazaBrowser.Navigate(pszURL,NULL,NULL,NULL,NULL);

	return true;
}

//调整控件
VOID CPlazaViewItem::RectifyControl(INT nWidth, INT nHeight)
{
	//状态判断
	if (m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(32);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//网页区域
	CRect rcWebButton;
	m_btGoodNum.GetWindowRect(&rcWebButton);
	CSkinButton * pSkinButtons[]={&m_btWebHome,&m_btGoodNum,&m_btVIP,&m_btMobileGame,&m_btGetPrize};

	//调整位置
	for (INT i=0;i<CountArray(pSkinButtons);i++)
	{ 
		INT nXPos=i*(rcWebButton.Width()+8)+3;
		DeferWindowPos(hDwp,pSkinButtons[i]->m_hWnd,NULL,nXPos,2,0,0,uFlags|SWP_NOSIZE);
		//pSkinButtons[i]->ShowWindow(SW_HIDE);
	}

	//浏览控件
	//CRect rcWebBrowse(0,0,nWidth,nHeight);
	//DeferWindowPos(hDwp,m_PlazaBrowser.m_hWnd,NULL,0,0,nWidth,nHeight,uFlags|SWP_NOSIZE);
	m_PlazaBrowser.MoveWindow(0,30,nWidth,nHeight);

	//m_BrowserEncircle.DeferWindowPos(&m_PlazaBrowser,hDwp,rcWebBrowse);

	//移动结束
	EndDeferWindowPos(hDwp);

	//重画界面
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW);

	return;
}

//////////////////////////////////////////////////////////////////////////////////
