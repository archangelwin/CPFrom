// DlgMobileBind.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgMobileBind.h"


//控件标识
#define IDC_WEB_PUBLICIZE			300									//浏览控件

// CDlgMobileBind 对话框
CDlgMobileBind::CDlgMobileBind() : CSkinDialog(IDD_DIALOG_MOBILEBIND)
{

}

CDlgMobileBind::~CDlgMobileBind()
{
}

void CDlgMobileBind::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMobileBind, CSkinDialog)
END_MESSAGE_MAP()


// CDlgMobileBind 消息处理程序

//创建函数
BOOL CDlgMobileBind::OnInitDialog()
{
	__super::OnInitDialog();
	MoveWindow(0,0,480,430);
	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//设置标题
	SetWindowText(TEXT("手机绑定"));


	//广告控件
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);
	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/LogonLogo.aspx"),pGlobalServer->GetPlatformServer(3));
	//设置广告
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetWindowPos(NULL,0,0,400,420,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	return true;
}
