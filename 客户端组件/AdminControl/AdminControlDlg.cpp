
// AdminControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "AdminControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#define IDC_SERVER_LIST				300									//游戏列表

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAdminControlDlg 对话框

CAdminControlDlg::CAdminControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_pUserPromptDlg = new CUserOnLinePrompt;
	m_HideUserdlg = new CDlgHideUser;
}
CAdminControlDlg::~CAdminControlDlg()
{
	if (m_pUserPromptDlg!=NULL)
	{
		SafeDelete(m_pUserPromptDlg);
	}

	if (m_HideUserdlg!=NULL)
	{
		SafeDelete(m_HideUserdlg);
	}

}
void CAdminControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TREE, m_ServerList);
	DDX_Control(pDX, IDC_TAB_PAG, m_TabSheet);
}

BEGIN_MESSAGE_MAP(CAdminControlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
//	ON_WM_HSCROLL()
	ON_MESSAGE(WM_USER_ONLINE_PROMPT,OnUserOnlinePrompt)
	ON_MESSAGE(WM_DLG_CHANGE,OnChangeDlg)

	ON_WM_WINDOWPOSCHANGED()
	ON_COMMAND(ID_CHECK_HIDE_USER, &CAdminControlDlg::OnCheckHideUser)
END_MESSAGE_MAP()


// CAdminControlDlg 消息处理程序

BOOL CAdminControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	GetClientRect(&m_rect);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_GameUserListDlg.Create(IDD_GAMEUSERLISTDLG);
	
 	m_ServerList.InitServerTreeView();
 	CServerListData::GetInstance()->SetServerListDataSink(&m_ServerList);
	m_StockDlg.Create(IDD_DLG_SET_STOCK);
	m_pUserPromptDlg->Create(IDD_FORMVIEW,this);

	m_HideUserdlg->Create(IDD_HIDE_USER_DLG,this);
//	m_pUserPromptDlg->ShowWindow(SW_SHOW);
	m_TabSheet.AddPage("玩家列表",&m_GameUserListDlg,IDD_GAMEUSERLISTDLG);
//	m_TabSheet.AddPage("网页后台",&m_WebDlg,IDD_WEB);
	m_TabSheet.AddPage("库存情况",&m_StockDlg,IDD_DLG_SET_STOCK);
	m_TabSheet.AddPage("当日输赢用户排名",&m_OnLineUserSortDlg,IDD_DIALOG3);
	m_TabSheet.AddPage("离线用户",&m_OffLineUserDlg,IDD_USER_OFFLINE_DLG);
	m_TabSheet.AddPage("代理",&m_SilverDlg,IDD_DIALOG_SILVER);
	m_TabSheet.AddPage("日志",&m_LogDlg,IDD_LOG);
	m_TabSheet.Show();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAdminControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAdminControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAdminControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAdminControlDlg::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
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

void CAdminControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
			//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

// 	if(nType!=SIZE_MINIMIZED ) 
// 	{
// 		ChangeSize(IDC_GAME_TREE,cx,cy);
// 		ChangeSize(IDC_TAB_PAG,cx,cy);
// 	}
	if(m_ServerList || m_TablePag || m_GameUserListDlg)
	{
		m_TabSheet.MoveWindow(rcClient.left+210,rcClient.top+10,rcClient.Width()-200,rcClient.Height()-10);
		m_ServerList.MoveWindow(rcClient.left+5,rcClient.top+10,rcClient.left+199,rcClient.Height()-30);
		CRect rect;
		m_TabSheet.GetClientRect(&rect);
		m_GameUserListDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
//		m_WebDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
		m_StockDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
		m_LogDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
		m_OnLineUserSortDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
		m_OffLineUserDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);
		m_SilverDlg.MoveWindow(0,20,rect.Width(),rect.Height()-20);

 		CRect rcRect;
// 		m_pUserPromptDlg->GetClientRect(&rcRect);
		GetWindowRect(&rcRect);
		m_pUserPromptDlg->MoveWindow(rcRect.right-m_pUserPromptDlg->m_Rect.Width()-10,rcRect.bottom-m_pUserPromptDlg->m_Rect.Height()-10,m_pUserPromptDlg->m_Rect.Width(),m_pUserPromptDlg->m_Rect.Height());
	}
	
}


//取消消息
VOID CAdminControlDlg::OnCancel()
{
	//关闭窗口
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

//	__super::OnClose();

	return;
}

BOOL CAdminControlDlg::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CAdminControlDlg::OnUserOnlinePrompt(WPARAM wParam, LPARAM lParam)
{
	m_pUserPromptDlg->ShowWindow(SW_SHOW);

	return TRUE;
}
//
//void CAdminControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
//{
//	// TODO: Add your message handler code here and/or call default
//
//	SCROLLINFO scrollinfo; 
//	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//	switch (nSBCode) 
//	{ 
//	case SB_LEFT: 
//		ScrollWindow((scrollinfo.nPos-scrollinfo.nMin)*10,0); 
//		scrollinfo.nPos = scrollinfo.nMin; 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		break; 
//	case SB_RIGHT: 
//		ScrollWindow((scrollinfo.nPos-scrollinfo.nMax)*10,0); 
//		scrollinfo.nPos = scrollinfo.nMax; 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		break; 
//	case SB_LINELEFT: 
//		scrollinfo.nPos -= 1; 
//		if (scrollinfo.nPos<scrollinfo.nMin) 
//		{ 
//			scrollinfo.nPos = scrollinfo.nMin; 
//			break; 
//		} 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		ScrollWindow(10,0); 
//		break; 
//	case SB_LINERIGHT: 
//		scrollinfo.nPos += 1; 
//		if (scrollinfo.nPos>scrollinfo.nMax) 
//		{ 
//			scrollinfo.nPos = scrollinfo.nMax; 
//			break; 
//		} 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		ScrollWindow(-10,0); 
//		break; 
//	case SB_PAGELEFT: 
//		scrollinfo.nPos -= 5; 
//		if (scrollinfo.nPos<scrollinfo.nMin) 
//		{ 
//			scrollinfo.nPos = scrollinfo.nMin; 
//			break; 
//		} 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		ScrollWindow(10*5,0); 
//		break; 
//	case SB_PAGERIGHT: 
//		scrollinfo.nPos += 5; 
//		if (scrollinfo.nPos>scrollinfo.nMax) 
//		{ 
//			scrollinfo.nPos = scrollinfo.nMax; 
//			break; 
//		} 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		ScrollWindow(-10*5,0); 
//		break; 
//	case SB_THUMBPOSITION: 
//		break; 
//	case SB_THUMBTRACK: 
//		ScrollWindow((scrollinfo.nPos-nPos)*10,0); 
//		scrollinfo.nPos = nPos; 
//		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
//		break; 
//	case SB_ENDSCROLL: 
//		break; 
//	} 
//
//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar); 
//}
void CAdminControlDlg::OnCheckHideUser()
{
	// TODO: 在此添加命令处理程序代码
	m_HideUserdlg->ShowWindow(SW_SHOW);
}


LRESULT CAdminControlDlg::OnChangeDlg(WPARAM wParam, LPARAM lParam)
{
	m_TabSheet.ShowWindow(3);
	
	return true;
}
