// CDlgFrezon.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "CDlgFrezon.h"


// CCDlgFrezon 对话框

IMPLEMENT_DYNAMIC(CCDlgFrezon, CDialog)

CCDlgFrezon::CCDlgFrezon(CWnd* pParent /*=NULL*/)
	: CDialog(CCDlgFrezon::IDD, pParent)
{

}

CCDlgFrezon::~CCDlgFrezon()
{
}

void CCDlgFrezon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CCDlgFrezon, CDialog)
	ON_BN_CLICKED(IDOK, &CCDlgFrezon::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CCDlgFrezon::OnInitDialog()
{
	__super::OnInitDialog();

	m_Edit.SetWindowText("管理员冻结!");

	return TRUE;
}

// CCDlgFrezon 消息处理程序

void CCDlgFrezon::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Edit.GetWindowText(m_strFrezonReason);
	OnOK();
}
