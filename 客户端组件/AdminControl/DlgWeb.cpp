// DlgWeb.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgWeb.h"


// CDlgWeb �Ի���

IMPLEMENT_DYNAMIC(CDlgWeb, CDialog)

CDlgWeb::CDlgWeb(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWeb::IDD, pParent)
{

}

CDlgWeb::~CDlgWeb()
{
}

void CDlgWeb::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebControl);
}


BEGIN_MESSAGE_MAP(CDlgWeb, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CDlgWeb::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_WebControl.put_Silent(TRUE);
	m_WebControl.Navigate("http://www.999qp.net:89/Login.aspx", NULL, NULL, NULL, NULL);
	

	return TRUE;
}

void CDlgWeb::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_WebControl)
	{
		m_WebControl.MoveWindow(rect.left,rect.top,rect.Width()-10,rect.Height());
	}
}
// CDlgWeb ��Ϣ�������

BOOL CDlgWeb::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
