// DlgQQLogon.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgQQLogon.h"
#include <COMUTIL.H>
#include <mshtml.h>


#define IETIMEVENT								5033
// CDlgQQLogon 对话框

IMPLEMENT_DYNAMIC(CDlgQQLogon, CDialog)

CDlgQQLogon::CDlgQQLogon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQQLogon::IDD, pParent)
{
	m_hLength = 620;
	m_hWidth = 370;
}

CDlgQQLogon::~CDlgQQLogon()
{

}

void CDlgQQLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER_QQ, m_BroswerQQLogon);
	DDX_Control(pDX, IDOK, m_btClose);
}


BEGIN_MESSAGE_MAP(CDlgQQLogon, CDialog)
	ON_WM_MOVE()
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CDlgQQLogon 消息处理程序

BOOL CDlgQQLogon::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btClose.SetButtonImage(IDB_BT_CLOSE_QQ,TEXT("BT_CLOSE_QQ"),hInstance,true,false);

	CRect rectParent;
	::GetWindowRect(GetParent()->m_hWnd, &rectParent);
	m_hLeft = ( m_hLength - 416 ) / 2;
	MoveWindow(rectParent.left-m_hLeft, rectParent.top+127, m_hLength, m_hWidth);

	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btClose,TEXT("关闭"));

	m_BroswerQQLogon.MoveWindow(0,0,m_hLength, m_hWidth);
	m_BroswerQQLogon.Navigate(m_sQQUrl,NULL,NULL,NULL,NULL);

	CRect rect;
	GetClientRect( &rect );
	m_btClose.MoveWindow(rect.right-40,rect.top+8,18,18);

	SetTimer(IETIMEVENT,1000,NULL); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgQQLogon::SetUrl(CString sQQUrl)
{
	m_sQQUrl = sQQUrl;
}

void CDlgQQLogon::MoveDlg(int nWidth, int nHeight)
{
	if(nWidth == 0 || nHeight < 50 || m_BroswerQQLogon.m_hWnd == NULL)
		return;
	if( nHeight > 500 )
		nHeight = 500;
	CRect rect;
	m_BroswerQQLogon.GetClientRect(rect);
	if(rect.Height()  == nHeight )
		return;
	GetWindowRect(rect);
	rect.bottom =  rect.top + nHeight + 2;
	rect.right = rect.left + nWidth;
	MoveWindow(rect);	

	m_BroswerQQLogon.GetClientRect(rect);
	rect.bottom =  rect.top + nHeight;
// 	rt.left = m_ieRt.left;
// 	rt.right = m_ieRt.right;
	rect.top += 1;
	rect.bottom += 1;
	m_BroswerQQLogon.MoveWindow(rect);
	m_btClose.MoveWindow(rect.right-40,rect.top+8,18,18);
}

BOOL CDlgQQLogon::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )
		{
		case VK_ESCAPE://屏蔽掉ESC
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgQQLogon::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
//	::SetWindowPos(  .GetSafeHwnd(),NULL,m_hLength + x - 40,y + 10,0,0,SWP_NOSIZE);
}

void CDlgQQLogon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	long nHight = 0;
	long nWidth = 0;
	KillTimer(IETIMEVENT);
	if (nIDEvent == IETIMEVENT)
	{
		IHTMLDocument2 * pHtmlDocument = NULL;
		IDispatch *document_dispatch = NULL;
		document_dispatch = (IDispatch *)
			m_BroswerQQLogon.GetDocument();	
		if(document_dispatch != NULL)
		{
			HRESULT	hr = document_dispatch->QueryInterface(IID_IHTMLDocument2,
				(void **)&pHtmlDocument);

			if(SUCCEEDED(hr))
			{
				CComQIPtr<IHTMLElement> eleBody;
				pHtmlDocument->get_body(&eleBody);
				long lHeight = 0; 
				if(eleBody != NULL)
				{
					eleBody->get_offsetHeight(&nHight); 
					eleBody->get_offsetWidth(&nWidth);
				}
			}
		}
		MoveDlg(nWidth, nHight);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgQQLogon::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnSysCommand(nID, lParam);QQ登录
	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	//{

	//}
	//else
	//{
		if( SC_CLOSE == nID )
			return;
		CDialog::OnSysCommand(nID, lParam);
	//}
}

BEGIN_EVENTSINK_MAP(CDlgQQLogon, CDialog)
	//{{AFX_EVENTSINK_MAP(CDlgQQLogon)
	ON_EVENT(CDlgQQLogon, IDC_EXPLORER_QQ,252,OnNavigateComplete2Explorer1,VTS_DISPATCH VTS_PVARIANT)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CDlgQQLogon::OnNavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: Add your control notification handler code here
	CString sGet = (LPCTSTR)(_bstr_t)URL;

	int nPos = sGet.Find("Id=");
	int nEnd = sGet.Find("pwd=");

	if(nPos >= 0 && nEnd > 0)
	{
		CString sID = sGet.Mid( nPos + 3, nEnd - nPos - 4 );
		CString sPwd = sGet.Mid( nEnd + 4 );

		TCHAR *cID = new TCHAR[sID.GetLength()+1];
		memset(cID,0,sID.GetLength()+1);
		memcpy(cID,sID,sID.GetLength());

		TCHAR *cpwd = new TCHAR[sPwd.GetLength()+1];
		memset(cpwd,0,sPwd.GetLength()+1);
		memcpy(cpwd,sPwd,sPwd.GetLength());

		::PostMessage(GetParent()->m_hWnd, WM_LOGIN_QQ, (WPARAM)cID,(LPARAM)cpwd);
	}
	//	MessageBox(sGet);
}
