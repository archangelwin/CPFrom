#include "StdAfx.h"
#include "ExDispID.h"
#include "GamePlaza.h"
#include "PlazaViewItem.h"
#include "WndViewItemCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//�ؼ���ʶ
#define IDC_PLAZA_BROWSER			100									//����ؼ�
#define IDC_PLAZA_MESSAGE           101                                 //��Ϣ��ʾ
//////////////////////////////////////////////////////////////////////////////////

//��̬����
CPlazaViewItem * CPlazaViewItem::m_pPlazaViewItem=NULL;					//�㳡ָ��

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

//���캯��
CPlazaBrowser::CPlazaBrowser()
{
}

//��������
CPlazaBrowser::~CPlazaBrowser()
{
}

//�󶨺���
VOID CPlazaBrowser::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//���ñ���
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return;
}

//���Ĵ���
VOID CPlazaBrowser::PostNcDestroy()
{
	return;
}

//��������
BOOL CPlazaBrowser::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT & rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	//���ñ���
	m_pCreateContext=pContext;

	//��������
	if (CView::Create(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID,pContext)==FALSE)
	{
		return FALSE;
	}

	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	if (m_wndBrowser.CreateControl(CLSID_WebBrowser,lpszWindowName,WS_VISIBLE|WS_CHILD,rcClient,this,AFX_IDW_PANE_FIRST)==FALSE)
	{
		DestroyWindow();
		return FALSE;
	}

	//��ѯ�ӿ�
	LPUNKNOWN lpUnknown=m_wndBrowser.GetControlUnknown();
	lpUnknown->QueryInterface(IID_IWebBrowser2,(VOID **)&m_pBrowserApp);

	return TRUE;
}

//�ر��¼�
void CPlazaBrowser::OnWindowClosing(BOOL IsChildWindow, BOOL *bCancel)   
{   
	//��ֹ�ر�
	if ((IsChildWindow==FALSE)&&(bCancel!=NULL))
	{
		*bCancel=TRUE;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPlazaViewItem::CPlazaViewItem() : CDialog(IDD_GAME_PLAZA)
{
	//���ñ���
	m_bCreateFlag=false;

	//���ö���
	ASSERT(m_pPlazaViewItem==NULL);
	if (m_pPlazaViewItem==NULL) m_pPlazaViewItem=this;

	//�����Դ
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

//��������
CPlazaViewItem::~CPlazaViewItem()
{
}

//�ӿڲ�ѯ
VOID * CPlazaViewItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//�ؼ���
VOID CPlazaViewItem::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GOOD_NUM, m_btGoodNum);
	DDX_Control(pDX, IDC_VIP_MEMBER, m_btVIP);
	DDX_Control(pDX, IDC_MOBILE_GAME, m_btMobileGame);
	DDX_Control(pDX, IDC_WEB_HOME, m_btWebHome);
	DDX_Control(pDX, IDC_GET_PRIZE, m_btGetPrize);
}

//��������
BOOL CPlazaViewItem::OnInitDialog()
{
	__super::OnInitDialog();

	//�����ؼ�
	CRect rcCreate(0,0,0,0);
	m_PlazaBrowser.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLAZA_BROWSER,NULL);
//	m_PlazaMessage.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLAZA_MESSAGE,NULL);
	//m_PlazaBrowser.ShowWindow(SW_HIDE);

	//��ҳ��ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btGoodNum.SetButtonImage(IDB_BT_GOODNUM,hInstance,true,false);
	m_btVIP.SetButtonImage(IDB_BT_VIPMEMBER,hInstance,true,false);
	m_btMobileGame.SetButtonImage(IDB_BT_MOBILEGAME,hInstance,true,false);
	m_btWebHome.SetButtonImage(IDB_BT_BROWSER_HOME,hInstance,true,false);
	m_btGetPrize.SetButtonImage(IDB_BT_GET_PRIZE,hInstance,true,false);

	//��ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btGoodNum,TEXT("����"));
	m_ToolTipCtrl.AddTool(&m_btVIP,TEXT("VIP"));
	m_ToolTipCtrl.AddTool(&m_btMobileGame,TEXT("�ֻ���Ϸ"));
	m_ToolTipCtrl.AddTool(&m_btWebHome,TEXT("��ҳ"));
	m_ToolTipCtrl.AddTool(&m_btGetPrize,TEXT("�齱"));

	//���ñ���
	m_bCreateFlag=true;

	return TRUE;
}

//��Ϣ����
BOOL CPlazaViewItem::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
	if (m_ToolTipCtrl.m_hWnd!=NULL) 
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//�����
BOOL CPlazaViewItem::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//�˵�����
	switch (nCommandID)
	{
	case IDC_GOOD_NUM:		//���˰�ť
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Service/NiceNumberPlaz.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.GoBack();
			return TRUE;
		}
	case IDC_VIP_MEMBER:		//ǰ����ť
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Shop/Mall.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.GoForward();
			return TRUE;
		}
	case IDC_MOBILE_GAME:		//ֹͣ��ť
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sUrl;
			sUrl.Format("%s/Games/PhoneGame.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(sUrl);
			//m_PlazaBrowser.Stop();
			return TRUE;
		}
	case IDC_WEB_HOME:		//��ҳ��ť
		{
			//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			//CString sMainUrl;
			//sMainUrl.Format("%s/index.aspx",pGlobalServer->GetPlatformServer(3));
			WebBrowse(m_sMainUrl);
			return TRUE;
		}
	case IDC_GET_PRIZE:	//�齱��ť
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

//λ����Ϣ
VOID CPlazaViewItem::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//�滭����
BOOL CPlazaViewItem::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,RGB(255,255,255));
	//pDC->FillSolidRect(&rcClient,RGB(255,0,0));

	//pDC->Draw3dRect(rcClient,RGB(255,0,0),RGB(255,0,0));

	//�滭��ҳ
	//CRect rcBrowse;
	//rcBrowse.top=0;
	//rcBrowse.left=0;
	//rcBrowse.right=rcClient.Width();
	//rcBrowse.bottom=rcClient.Height();
	//m_BrowserEncircle.DrawEncircleFrame(pDC,rcBrowse);

	//��������
	CImage ImageBuffer;
	if(ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32) == FALSE) return TRUE;

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//��������
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	CBitImage ImageTitleL,ImageTitleM,ImageTitleR;
	//ImageTitleL.LoadFromResource(hInstance,IDB_BROWSER_TL);
	ImageTitleM.LoadFromResource(hInstance,IDB_BROWSER_TM);
	//ImageTitleR.LoadFromResource(hInstance,IDB_BROWSER_TR);

	//��Ⱦ��Դ
	//pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	//pSkinRenderManager->RenderImage(ImageTitleR);

	//�滭����
	//ImageTitleL.BitBlt(BufferDC,0,0);
	//����м�
	for (INT nXPos=0;nXPos<rcClient.Width();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}
	//�滭����
	//ImageTitleR.BitBlt(BufferDC,rcClient.Width()-ImageTitleR.GetWidth(),0);

	//�滭�ν�
	ASSERT(CWndViewItemCtrl::GetInstance()!=NULL);
	CWndViewItemCtrl::GetInstance()->DrawLinkBoradLine(this,pDC);
	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//���ҳ��
bool CPlazaViewItem::WebBrowse(LPCTSTR pszURL)
{
	m_PlazaBrowser.Navigate(pszURL,NULL,NULL,NULL,NULL);

	return true;
}

//�����ؼ�
VOID CPlazaViewItem::RectifyControl(INT nWidth, INT nHeight)
{
	//״̬�ж�
	if (m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(32);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//��ҳ����
	CRect rcWebButton;
	m_btGoodNum.GetWindowRect(&rcWebButton);
	CSkinButton * pSkinButtons[]={&m_btWebHome,&m_btGoodNum,&m_btVIP,&m_btMobileGame,&m_btGetPrize};

	//����λ��
	for (INT i=0;i<CountArray(pSkinButtons);i++)
	{ 
		INT nXPos=i*(rcWebButton.Width()+8)+3;
		DeferWindowPos(hDwp,pSkinButtons[i]->m_hWnd,NULL,nXPos,2,0,0,uFlags|SWP_NOSIZE);
		//pSkinButtons[i]->ShowWindow(SW_HIDE);
	}

	//����ؼ�
	//CRect rcWebBrowse(0,0,nWidth,nHeight);
	//DeferWindowPos(hDwp,m_PlazaBrowser.m_hWnd,NULL,0,0,nWidth,nHeight,uFlags|SWP_NOSIZE);
	m_PlazaBrowser.MoveWindow(0,30,nWidth,nHeight);

	//m_BrowserEncircle.DeferWindowPos(&m_PlazaBrowser,hDwp,rcWebBrowse);

	//�ƶ�����
	EndDeferWindowPos(hDwp);

	//�ػ�����
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW);

	return;
}

//////////////////////////////////////////////////////////////////////////////////
