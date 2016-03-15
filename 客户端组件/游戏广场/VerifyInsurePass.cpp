// VerifyInsurePass.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "VerifyInsurePass.h"
#include "PlatformFrame.h"


// CVerifyInsurePass 对话框
CVerifyInsurePass::CVerifyInsurePass() : CSkinDialog(IDD_VERIFY_INSUREPASS)
{
	//任务组件
	m_MissionManager.InsertMissionItem(this);
	m_nSavePwdType = 0;

	return;
}

CVerifyInsurePass::~CVerifyInsurePass()
{
}

void CVerifyInsurePass::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MINUTE, m_ComMinutes);
	DDX_Control(pDX, IDC_BUTTON_VERIFYPASS, m_btVerifyInsurePass);
	DDX_Control(pDX, IDC_VERIFY_PASSWORD, m_PasswordControl);

	DDX_Control(pDX, IDC_STATIC_PASSTITLE, m_PassText);
	DDX_Control(pDX, IDC_STATIC_GETPWD, m_GetInsurePwd);
	DDX_Control(pDX, IDC_VERIFYPASS_TITLE, m_VerifyPassTitle);
	DDX_Control(pDX, IDC_STATIC_MINUTE, m_VerifyMinute);
	DDX_Control(pDX, IDC_VERIFY_INSUREPWD_QQ, m_VerifyQQtip);
	
}


BEGIN_MESSAGE_MAP(CVerifyInsurePass, CSkinDialog)
	ON_BN_CLICKED(IDC_BUTTON_VERIFYPASS, &CVerifyInsurePass::OnBnClickedButtonVerifyPass)
	ON_STN_CLICKED(IDC_STATIC_GETPWD, &CVerifyInsurePass::OnBnClickedForgetInsure)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

//创建函数
BOOL CVerifyInsurePass::OnInitDialog()
{
	__super::OnInitDialog();
	MoveWindow(0,0,515,316);
	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//设置标题
	SetWindowText(TEXT("银行登陆"));

	m_VerifyPassTitle.MoveWindow(65,48,300,14);
	m_PassText.MoveWindow(65,90,70,14);
	m_PasswordControl.MoveWindow(135,87,182,22);
	m_GetInsurePwd.MoveWindow(322,90,120,14);
	m_VerifyQQtip.MoveWindow(135,116,170,14);
	GetDlgItem(IDC_RADIO_VERIFY1)->MoveWindow(130,140,80,22);
	GetDlgItem(IDC_RADIO_VERIFY2)->MoveWindow(130,162,90,22);
	GetDlgItem(IDC_RADIO_VERIFY3)->MoveWindow(130,184,100,22);
	((CButton *)GetDlgItem(IDC_RADIO_VERIFY2))->SetCheck(1);
	
	m_ComMinutes.MoveWindow(222,162,63,86);
	m_VerifyMinute.MoveWindow(288,162,40,22);
	m_btVerifyInsurePass.MoveWindow(190,230,68,24);
	m_btVerifyInsurePass.SetWindowText("登  陆");


	//m_PasswordControl.SetDrawBorad(false);

	m_VerifyPassTitle.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_VerifyPassTitle.SetCustomFont(true,false,false,false);

	m_PassText.SetHyperLinkTextColor(RGB(70,125,160),RGB(25,108,162),RGB(25,108,162));
	m_PassText.SetCustomFont(true,false,false,false);
	m_GetInsurePwd.SetHyperLinkTextColor(RGB(70,125,160),RGB(25,108,162),RGB(25,108,162));
	m_GetInsurePwd.SetCustomFont(true,true,true,false);
	m_VerifyQQtip.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_VerifyQQtip.SetCustomFont(true,false,false,false);
	m_VerifyMinute.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_VerifyMinute.SetCustomFont(true,false,false,false);

	INT nItem= m_ComMinutes.AddString("5");
	m_ComMinutes.AddString("10");
	m_ComMinutes.AddString("20");
	m_ComMinutes.AddString("30");
	m_ComMinutes.AddString("60");
	m_ComMinutes.SetCurSel(0);
	m_PasswordControl.SetFocus();
	m_PasswordControl.SetUserPassword(TEXT(""));
	//m_ComMinutes.SetItemData(nItem,5);

	return TRUE;
}

//消息解释
BOOL CVerifyInsurePass::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message == WM_KEYDOWN)
	{
		//if (pMsg->wParam == VK_RETURN)
		//	return TRUE;
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}

void CVerifyInsurePass::OnBnClickedForgetInsure()
{
	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),pGlobalServer->GetPlatformServer(3));

	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}

// CVerifyInsurePass 消息处理程序
void CVerifyInsurePass::OnBnClickedButtonVerifyPass()
{
	if(IsDlgButtonChecked(IDC_RADIO_VERIFY1)==BST_CHECKED)
		m_nSavePwdType = 1;
	else if(IsDlgButtonChecked(IDC_RADIO_VERIFY2)==BST_CHECKED)
		m_nSavePwdType = 2;
	else if(IsDlgButtonChecked(IDC_RADIO_VERIFY3)==BST_CHECKED)
		m_nSavePwdType = 3;
	CString sTemp;
	m_ComMinutes.GetLBText(m_ComMinutes.GetCurSel(), sTemp);
	m_nSaveMinute= atoi(sTemp);

	m_PasswordControl.GetUserPassword(m_szInsurePassword);
	//GetDlgItemText(IDC_INSURE_PASS2,szInsurePass2,CountArray(szInsurePass2));
	if (m_szInsurePassword[0]==0)
	{
		m_PasswordControl.SetFocus();
		//错误提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请输入保险柜密码！"),MB_ICONERROR);
	    return;
	}

	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//发起连接
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//错误提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("服务器连接失败，请检查网络配置以及网络连接状况！"),MB_ICONERROR);
	}
}

//连接事件
bool CVerifyInsurePass::OnEventMissionLink(INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0L)
	{
		//设置控件
		//m_btVerifyInsurePass.EnableWindow(TRUE);

		//显示提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("尝试了所有的服务器都无法成功连接服务器，请留意网站维护公告！"),MB_ICONERROR);
	}
	else
	{
	//	__super::OnOK();
		//发送数据
		ASSERT(GetMissionManager()!=NULL);
		CMD_GP_VERIFY_INSUREPASS VerifyInsurePass;
		ZeroMemory(&VerifyInsurePass,sizeof(VerifyInsurePass));

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		VerifyInsurePass.dwUserID = pGlobalUserData->dwUserID;
		//机器标识
		CWHService::GetMachineIDEx(VerifyInsurePass.szMachineID);

		TCHAR szPassword[LEN_MD5];
		CWHEncrypt::MD5Encrypt(m_szInsurePassword,szPassword);
		lstrcpyn(VerifyInsurePass.szInsurePass,szPassword,CountArray(VerifyInsurePass.szInsurePass));

		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_VERIFY_INSURE_PASS,&VerifyInsurePass,sizeof(VerifyInsurePass));
	}

	return true;
}

//关闭事件
bool CVerifyInsurePass::OnEventMissionShut(BYTE cbShutReason)
{
	//关闭处理
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//重试任务
		//CMissionManager * pMissionManager=GetMissionManager();
		//if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//设置控件
		//m_btVerifyInsurePass.EnableWindow(TRUE);

		//显示提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("由于当前服务器处理繁忙，验证保险柜密码失败，请稍后再重试！"),MB_ICONERROR);
	}

	return true;
}

//读取事件
bool CVerifyInsurePass::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//命令处理
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_OPERATE_FAILURE:	//操作失败
			{
				//效验参数
				CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

				//关闭连接
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//显示消息
				if (pOperateFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateFailure->szDescribeString,MB_ICONERROR,60);
				}
				m_PasswordControl.SetFocus();

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//操作成功
			{
				//变量定义
				CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)pData;
				//效验数据
				//ASSERT(wDataSize>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				//if (wDataSize<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//关闭连接
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//保存保险柜信息				
				CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
				pPlatformFrame->SaveInsurePwd(m_nSavePwdType,m_nSaveMinute,m_szInsurePassword);

				//关闭窗口
				__super::OnOK();

				return true;
			}
		}
	}

	//错误断言
	ASSERT(FALSE);

	return true;
}

void CVerifyInsurePass::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);
	m_PasswordControl.SetFocus();

	// TODO: 在此处添加消息处理程序代码
}