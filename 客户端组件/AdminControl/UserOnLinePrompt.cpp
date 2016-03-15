// UserOnLinePrompt.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserOnLinePrompt.h"


// CUserOnLinePrompt 对话框

IMPLEMENT_DYNAMIC(CUserOnLinePrompt, CDialog)

CUserOnLinePrompt::CUserOnLinePrompt(CWnd* pParent /*=NULL*/)
	: CDialog(CUserOnLinePrompt::IDD, pParent)
{

}

CUserOnLinePrompt::~CUserOnLinePrompt()
{
}

void CUserOnLinePrompt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserOnLinePrompt, CDialog)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CUserOnLinePrompt 消息处理程序
BOOL CUserOnLinePrompt::OnInitDialog()
{
	__super::OnInitDialog();
	
	GetClientRect(&m_Rect);

	return TRUE;
}


void CUserOnLinePrompt::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseMove(nFlags, point);
}
