// MessagePop.cpp : 实现文件
//

#include "stdafx.h"
#include "MessagePop.h"

#define IDC_WEB_MSGPOP			300									//浏览控件
//时间标识
#define IDI_MESSAGE				301									//消息标识
// CMessagePop 对话框

IMPLEMENT_DYNAMIC(CMessagePop, CSkinDialog)

CMessagePop::CMessagePop(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CMessagePop::IDD, pParent)
{
	m_bDoModal = false;
	m_bMsgPop = true;
	m_nElapse=0;
}

CMessagePop::~CMessagePop()
{
}

void CMessagePop::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_BUTTON_MSGPOP, m_btSubmit);
}


BEGIN_MESSAGE_MAP(CMessagePop, CSkinDialog)
	//ON_WM_PAINT()
	ON_WM_TIMER()
	//ON_WM_SYSCOMMAND() 
	ON_BN_CLICKED(IDC_BUTTON_MSGPOP, &CMessagePop::OnBnClickedButtonPopMsg)
END_MESSAGE_MAP()


// CMessagePop 消息处理程序
//创建函数
BOOL CMessagePop::OnInitDialog()
{
	__super::OnInitDialog();
	//设置标题
	SetWindowText(m_strCaption);
	MoveWindow(0,0,m_nWindowcx,m_nWindowcy);

	CRect rcCreate(0,0,0,0);
	m_BroswerMsg.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_MSGPOP);

	m_BroswerMsg.Navigate(m_sUrl,NULL,NULL,NULL,NULL);
	//m_BroswerMsg.MoveWindow(0,36,m_nWebBrowsercx,m_nWebBrowsercy);
	m_BroswerMsg.SetWindowPos(NULL,(m_nWindowcx-m_nWebBrowsercx)/2,36+3,m_nWebBrowsercx,m_nWebBrowsercy,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
//	m_BroswerMsg.SetWindowPos(NULL,5,37,m_nWebBrowsercx-2*5,m_nWebBrowsercy,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	m_btSubmit.MoveWindow(m_nWindowcx/2-20,m_nWindowcy-36-36,60,24);
	m_btSubmit.SetWindowText("确定");
	if (!m_bMsgPop)
	{
		m_btSubmit.ShowWindow(SW_HIDE);
	}
	CenterWindow();	

	//设置时间
	if (m_nElapse!=0) 
		SetTimer(IDI_MESSAGE,1000,NULL);

	return true;
}

//消息解释
BOOL CMessagePop::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
			return TRUE;
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//重画消息
//VOID CMessagePop::OnPaint()
//{
//	CPaintDC dc(this);
//
//	//获取位置
//	//CRect rcClient;
//	//GetClientRect(&rcClient);
//
//	//CDC *pDC = GetDC();
//	//CPen penColor;
//	//penColor.CreatePen(PS_SOLID,1,RGB(145,168,183));//边框颜色
//	//pDC->SelectObject(penColor);
//	//pDC->MoveTo(20,205);
//	//pDC->LineTo(rcClient.Width()-20,205);
//
//	//penColor.DeleteObject();
//	//ReleaseDC(pDC);
//
//	return;
//}

VOID CMessagePop::OnCancel()
{
	if (!m_bDoModal)
	{
		DestroyWindow();
	}
	else
	{
		EndDialog(IDCANCEL);
	}
//	PostQuitMessage(0);
}

void CMessagePop::OnBnClickedButtonPopMsg()
{
	if (!m_bDoModal)
	{
		DestroyWindow();
	}
	else
	{
		EndDialog(IDCANCEL);
	}
}

void CMessagePop::InitWebDlg(CString sUrl,CString sCaption,bool bDoModal,bool bMsgPop,int nElapse)
{
	m_sUrl = sUrl;
	m_strCaption = sCaption;
	m_bDoModal = bDoModal;
	m_bMsgPop = bMsgPop;
	m_nElapse = nElapse;
}

void CMessagePop::UpdateUrl(CString sUrl)
{
	m_sUrl = sUrl;
	m_BroswerMsg.Navigate(m_sUrl,NULL,NULL,NULL,NULL);
}

void CMessagePop::SetWindowSize(int nwindowcx,int nWindowcy,int nWebBrowsercx,int nWebBrowsercy)
{
	m_nWindowcx = nwindowcx;
	m_nWindowcy = nWindowcy;
	m_nWebBrowsercx = nWebBrowsercx;
	m_nWebBrowsercy = nWebBrowsercy;	
}

//时间消息
VOID CMessagePop::OnTimer(UINT_PTR nIDEvent)
{
	//倒数时间
	if (nIDEvent==IDI_MESSAGE)
	{
		//删除判断
		if (m_nElapse==0)
		{
			KillTimer(IDI_MESSAGE);
			DestroyWindow();
			return;
		}

		//设置界面
		TCHAR szTitle[32]=TEXT("");
		_sntprintf(szTitle,CountArray(szTitle),TEXT("%s （%ld 秒）"),m_strCaption,m_nElapse--);
		SetWindowText(szTitle);

		return;
	}

	__super::OnTimer(nIDEvent);
}

//VOID CMessagePop::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if (nID == SC_MOVE || nID==0xF012)
//		return;
//	else
//		CSkinDialog::OnSysCommand(nID, lParam);
//}


