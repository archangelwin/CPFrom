// UserInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserInfoDlg.h"


// CUserInfoDlg �Ի���

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


// CUserInfoDlg ��Ϣ�������
BOOL CUserInfoDlg::OnInitDialog()
{
	__super::OnInitDialog();


	return TRUE;
}
