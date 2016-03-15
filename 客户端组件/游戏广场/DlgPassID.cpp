// DlgPassID.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgPassID.h"


// CDlgPassID 对话框

//IMPLEMENT_DYNAMIC(CDlgPassID, CSkinDialog)

CDlgPassID::CDlgPassID()
	: CSkinDialog(IDD_DIALOG_PASSID)
{

}

CDlgPassID::~CDlgPassID()
{
}

void CDlgPassID::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);

	//绑定控件
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT_PASSID, m_edPassID);
	DDX_Control(pDX, IDC_CTRPASSWORD, m_CtrPasswordControl);
}


BEGIN_MESSAGE_MAP(CDlgPassID, CSkinDialog)
END_MESSAGE_MAP()


// CDlgPassID 消息处理程序
//创建函数
BOOL CDlgPassID::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("绑定设置"));

	return TRUE;
}

//确定函数
VOID CDlgPassID::OnOK()
{
	m_edPassID.GetWindowText(m_szPassPortID,CountArray(m_szPassPortID));
	m_CtrPasswordControl.GetUserPassword(m_szPassword);

	CDialog::OnOK();
}