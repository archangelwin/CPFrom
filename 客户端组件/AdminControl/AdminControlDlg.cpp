
// AdminControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "AdminControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#define IDC_SERVER_LIST				300									//��Ϸ�б�

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAdminControlDlg �Ի���

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


// CAdminControlDlg ��Ϣ�������

BOOL CAdminControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	GetClientRect(&m_rect);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_GameUserListDlg.Create(IDD_GAMEUSERLISTDLG);
	
 	m_ServerList.InitServerTreeView();
 	CServerListData::GetInstance()->SetServerListDataSink(&m_ServerList);
	m_StockDlg.Create(IDD_DLG_SET_STOCK);
	m_pUserPromptDlg->Create(IDD_FORMVIEW,this);

	m_HideUserdlg->Create(IDD_HIDE_USER_DLG,this);
//	m_pUserPromptDlg->ShowWindow(SW_SHOW);
	m_TabSheet.AddPage("����б�",&m_GameUserListDlg,IDD_GAMEUSERLISTDLG);
//	m_TabSheet.AddPage("��ҳ��̨",&m_WebDlg,IDD_WEB);
	m_TabSheet.AddPage("������",&m_StockDlg,IDD_DLG_SET_STOCK);
	m_TabSheet.AddPage("������Ӯ�û�����",&m_OnLineUserSortDlg,IDD_DIALOG3);
	m_TabSheet.AddPage("�����û�",&m_OffLineUserDlg,IDD_USER_OFFLINE_DLG);
	m_TabSheet.AddPage("����",&m_SilverDlg,IDD_DIALOG_SILVER);
	m_TabSheet.AddPage("��־",&m_LogDlg,IDD_LOG);
	m_TabSheet.Show();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAdminControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAdminControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAdminControlDlg::ChangeSize(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left=rec.left*x/m_rect.Width();  //���ձ��������ռ����λ��
		rec.top=rec.top*y/m_rect.Height();
		rec.bottom=rec.bottom*y/m_rect.Height();
		rec.right=rec.right*x/m_rect.Width();
		pWnd->MoveWindow(rec);   //�����ؼ�
	}
}

void CAdminControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
			//��ȡλ��
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


//ȡ����Ϣ
VOID CAdminControlDlg::OnCancel()
{
	//�رմ���
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

//	__super::OnClose();

	return;
}

BOOL CAdminControlDlg::PreTranslateMessage(MSG * pMsg)
{
	//��������
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
	// TODO: �ڴ���������������
	m_HideUserdlg->ShowWindow(SW_SHOW);
}


LRESULT CAdminControlDlg::OnChangeDlg(WPARAM wParam, LPARAM lParam)
{
	m_TabSheet.ShowWindow(3);
	
	return true;
}
