// UserOnLinePrompt.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserOnLinePrompt.h"


// CUserOnLinePrompt �Ի���

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


// CUserOnLinePrompt ��Ϣ�������
BOOL CUserOnLinePrompt::OnInitDialog()
{
	__super::OnInitDialog();
	
	GetClientRect(&m_Rect);

	return TRUE;
}


void CUserOnLinePrompt::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnMouseMove(nFlags, point);
}
