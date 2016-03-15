// VerifyInsurePass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "VerifyInsurePass.h"
#include "PlatformFrame.h"


// CVerifyInsurePass �Ի���
CVerifyInsurePass::CVerifyInsurePass() : CSkinDialog(IDD_VERIFY_INSUREPASS)
{
	//�������
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

//��������
BOOL CVerifyInsurePass::OnInitDialog()
{
	__super::OnInitDialog();
	MoveWindow(0,0,515,316);
	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//���ñ���
	SetWindowText(TEXT("���е�½"));

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
	m_btVerifyInsurePass.SetWindowText("��  ½");


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

//��Ϣ����
BOOL CVerifyInsurePass::PreTranslateMessage(MSG * pMsg)
{
	//��������
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
	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),pGlobalServer->GetPlatformServer(3));

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}

// CVerifyInsurePass ��Ϣ�������
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
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����뱣�չ����룡"),MB_ICONERROR);
	    return;
	}

	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//��������
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����������ʧ�ܣ��������������Լ���������״����"),MB_ICONERROR);
	}
}

//�����¼�
bool CVerifyInsurePass::OnEventMissionLink(INT nErrorCode)
{
	//������
	if (nErrorCode!=0L)
	{
		//���ÿؼ�
		//m_btVerifyInsurePass.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������еķ��������޷��ɹ����ӷ���������������վά�����棡"),MB_ICONERROR);
	}
	else
	{
	//	__super::OnOK();
		//��������
		ASSERT(GetMissionManager()!=NULL);
		CMD_GP_VERIFY_INSUREPASS VerifyInsurePass;
		ZeroMemory(&VerifyInsurePass,sizeof(VerifyInsurePass));

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		VerifyInsurePass.dwUserID = pGlobalUserData->dwUserID;
		//������ʶ
		CWHService::GetMachineIDEx(VerifyInsurePass.szMachineID);

		TCHAR szPassword[LEN_MD5];
		CWHEncrypt::MD5Encrypt(m_szInsurePassword,szPassword);
		lstrcpyn(VerifyInsurePass.szInsurePass,szPassword,CountArray(VerifyInsurePass.szInsurePass));

		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_VERIFY_INSURE_PASS,&VerifyInsurePass,sizeof(VerifyInsurePass));
	}

	return true;
}

//�ر��¼�
bool CVerifyInsurePass::OnEventMissionShut(BYTE cbShutReason)
{
	//�رմ���
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		//CMissionManager * pMissionManager=GetMissionManager();
		//if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//���ÿؼ�
		//m_btVerifyInsurePass.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���ڵ�ǰ����������æ����֤���չ�����ʧ�ܣ����Ժ������ԣ�"),MB_ICONERROR);
	}

	return true;
}

//��ȡ�¼�
bool CVerifyInsurePass::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_OPERATE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//��ʾ��Ϣ
				if (pOperateFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateFailure->szDescribeString,MB_ICONERROR,60);
				}
				m_PasswordControl.SetFocus();

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//�����ɹ�
			{
				//��������
				CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)pData;
				//Ч������
				//ASSERT(wDataSize>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				//if (wDataSize<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//���汣�չ���Ϣ				
				CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
				pPlatformFrame->SaveInsurePwd(m_nSavePwdType,m_nSaveMinute,m_szInsurePassword);

				//�رմ���
				__super::OnOK();

				return true;
			}
		}
	}

	//�������
	ASSERT(FALSE);

	return true;
}

void CVerifyInsurePass::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);
	m_PasswordControl.SetFocus();

	// TODO: �ڴ˴������Ϣ����������
}