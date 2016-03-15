// DlgPassWord.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgPassWord.h"


// CDlgPassWord 对话框

//IMPLEMENT_DYNAMIC(CDlgPassWord, CSkinDialog)

CDlgPassWord::CDlgPassWord()
	: CSkinDialog(IDD_DIALOG_LOCKMACHINE)
{

}

CDlgPassWord::~CDlgPassWord()
{
}

void CDlgPassWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CTRPASSWORD, m_CtrPasswordControl);

	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CDlgPassWord, CSkinDialog)
END_MESSAGE_MAP()


// CDlgPassWord 消息处理程序
//创建函数
BOOL CDlgPassWord::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("绑定设置"));

	return TRUE;
}

//确定函数
VOID CDlgPassWord::OnOK()
{
	//获取信息
	m_CtrPasswordControl.GetUserPassword(m_szPassword);

	CDialog::OnOK();
}