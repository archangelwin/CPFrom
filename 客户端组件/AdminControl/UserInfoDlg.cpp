// UserInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserInfoDlg.h"


// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialog)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
END_MESSAGE_MAP()


// CUserInfoDlg 消息处理程序
BOOL CUserInfoDlg::OnInitDialog()
{
	__super::OnInitDialog();


	return TRUE;
}
