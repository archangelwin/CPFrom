#include "StdAfx.h"
#include "GamePlaza.h"
#include "DlgLockMachine.h"
#include "DlgPassWord.h"
#include "DlgPassID.h"
//////////////////////////////////////////////////////////////////////////////////
//�ؼ���ʶ
#define IDC_WEB_PUBLICIZE			300									//����ؼ�

BEGIN_MESSAGE_MAP(CDlgLockMachine, CSkinDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PASSID, &CDlgLockMachine::OnBnClickedButtonPassID)
	ON_BN_CLICKED(IDC_PASSWORDPROTECT, &CDlgLockMachine::OnBnClickedButtonPasswordProtect)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLockMachine::CDlgLockMachine() : CSkinDialog(IDD_DLG_LOCK_MACHINE)
{
	//���ñ���
	m_cbMachine=FALSE;
	ZeroMemory(m_szPassword,sizeof(m_szPassword));
	ZeroMemory(m_szPassword2,sizeof(m_szPassword2));
    m_nType = -1;
	m_bShowPassportID = true;
	//�������
	m_MissionManager.InsertMissionItem(this);

	return;
}

//��������
CDlgLockMachine::~CDlgLockMachine()
{
	if (GetActiveStatus() == true)
	{
		m_MissionManager.ConcludeMissionItem(this,false);
	}
}

//�ؼ���
VOID CDlgLockMachine::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_STATIC_PC, m_cTitlePC);
	DDX_Control(pDX, IDC_STATIC_PWD1, m_cPWD);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);

	DDX_Control(pDX, IDC_BUTTON_PASSID, m_btPassID);
	DDX_Control(pDX, IDC_STATIC_PID, m_cPassID);
	DDX_Control(pDX,IDC_PASSWORDPROTECT,m_btPasswordProtect);
	DDX_Control(pDX, IDC_PASSWORD2, m_PasswordControl2);
	DDX_Control(pDX, IDC_STATIC_PASSID, m_cTitlePassID);
	DDX_Control(pDX, IDC_STATIC_NAME, m_cPassName);	
	DDX_Control(pDX, IDC_STATIC_PWD2, m_cPWD2);
	DDX_Control(pDX, IDC_STATIC_PASS_REMARK, m_cPidRemark);
	DDX_Control(pDX, IDC_INSURELOCK_QQ,m_cInsurePwdQQ);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edName);
	DDX_Control(pDX, IDC_EDIT_PASSID, m_edPassID);
	DDX_Control(pDX, IDC_STATIC_PASSWORD_PROTECT,m_cApplyProtectRemark);
}

//��������
BOOL CDlgLockMachine::OnInitDialog()
{
	__super::OnInitDialog();

	if (m_bShowPassportID)
	{
		MoveWindow(0,0,350,230/*+150+20*/);
	}
	else
	{
		MoveWindow(0,0,350,230);
	}
	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//���ñ���
	SetWindowText(TEXT("��ȫ������"));

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	//���ð�ť
	m_cbMachine=(pGlobalUserData->cbMoorMachine==0)?TRUE:FALSE;
	m_btOk.SetWindowText((pGlobalUserData->cbMoorMachine==0)?TEXT("�󶨱���"):TEXT("�����"));

	if (pIndividualUserData->cbMoorPassPortID == TRUE) //�Ѿ������֤
	{
		m_edPassID.SetWindowText(pIndividualUserData->szPassPortID);
		m_edName.SetWindowText(pIndividualUserData->szCompellation);
		m_edPassID.EnableWindow(FALSE);
		m_btPassID.EnableWindow(FALSE);
		m_btPassID.SetWindowText("�Ѱ�");
		
	}

	m_cTitlePC.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cTitlePassID.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cPassName.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cPassID.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cPWD.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cPWD2.SetHyperLinkTextColor(RGB(35,124,172),RGB(35,124,172),RGB(35,124,172));
	m_cPidRemark.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_cInsurePwdQQ.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_cApplyProtectRemark.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_cInsurePwdQQ.SetBCursor(false);

	m_cTitlePC.SetCustomFont(true,false,false,true,-14);
	m_cTitlePassID.SetCustomFont(true,false,false,true,-14);

	m_cPWD.SetCustomFont(true,false,false,false);
	m_cPWD2.SetCustomFont(true,false,false,false);
	m_cPassName.SetCustomFont(true,false,false,false);
	m_cPassID.SetCustomFont(true,false,false,false);
	m_cPidRemark.SetCustomFont(true,false,false,false);
	m_cApplyProtectRemark.SetCustomFont(true,false,false,false);

	CRect rcButton(0,0,0,0);
	m_btOk.GetWindowRect(&rcButton);

	m_cTitlePC.MoveWindow(27,50,180,16);
	m_PasswordControl.MoveWindow(130,103,185,22);
	m_btOk.MoveWindow(rcClient.left+65,120,rcButton.Width()+5,rcButton.Height()+3,SWP_NOZORDER|SWP_NOMOVE);


	m_cTitlePassID.MoveWindow(27,220,180,16);

	m_cPassName.MoveWindow(27+30,250,75,16);
	m_edName.MoveWindow(132,250,180,22);
	m_cPassName.ShowWindow(SW_HIDE);	
	m_edName.ShowWindow(SW_HIDE);

	m_cPassID.MoveWindow(27+30,250,75,16);
	m_edPassID.MoveWindow(132,250,184,22);
	m_cPWD2.MoveWindow(27+30,310-30,75,22);
	m_PasswordControl2.MoveWindow(132,310-30,184,22);
	m_cPidRemark.MoveWindow(rcClient.left+20,150,210,22);
//	m_cInsurePwdQQ.MoveWindow(27+30+230,355-35,180,22);
	m_cInsurePwdQQ.MoveWindow(rcClient.left+165,165,210,22);
	m_cPidRemark.SetWindowText("��ܰ��ʾ��һ�����ĵ�¼���������仯��ϵͳ������������"); 
	m_cApplyProtectRemark.SetWindowText("�������ͽ�����֤��¼��"); 

	m_edPassID.LimitText(LEN_PASS_PORT_ID-1);
	m_edName.LimitText(LEN_COMPELLATION-1);
	/*m_PasswordControl.LimitText(LEN_PASSWORD-1);
	m_PasswordControl2.LimitText(LEN_PASSWORD-1);*/
	m_btPassID.MoveWindow(rcClient.left+215,120,rcButton.Width()+5,rcButton.Height()+3,SWP_NOZORDER|SWP_NOMOVE);
	m_btPasswordProtect.MoveWindow(rcClient.Width()-100,275-25+30,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

	//���ؼ�
	CRect rcCreate(0,0,0,0);
//	m_WebPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_WEB_PUBLICIZE);	
	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBrowseUrl[256]=TEXT("");
	_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/MachineBind/UserBindMachine.aspx?userId=%d"),pGlobalServer->GetPlatformServer(3),pGlobalUserData->dwUserID);
	//���ù��
//	m_WebPublicize.Navigate(szBrowseUrl);

	if (pGlobalUserInfo->GetUserAccountType()<=0)
	{
		m_cInsurePwdQQ.ShowWindow(SW_HIDE);
	}
	if (!m_bShowPassportID)
	{
		m_edName.ShowWindow(SW_HIDE);
		m_cPassName.ShowWindow(SW_HIDE);
		//
		m_btPassID.ShowWindow(SW_HIDE);
		m_cPassID.ShowWindow(SW_HIDE);
		m_btPasswordProtect.ShowWindow(SW_HIDE);
		m_PasswordControl2.ShowWindow(SW_HIDE);
		m_cTitlePassID.ShowWindow(SW_HIDE);
		m_cPWD2.ShowWindow(SW_HIDE);
		m_cPidRemark.ShowWindow(SW_HIDE);
		m_edName.ShowWindow(SW_HIDE);
		m_edPassID.ShowWindow(SW_HIDE);
//		m_WebPublicize.SetWindowPos(NULL,0,210,480,170,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
		m_cApplyProtectRemark.MoveWindow(rcClient.left+20,165,145,22,SWP_NOZORDER|SWP_NOMOVE);
	}
	else
	{
//		m_WebPublicize.SetWindowPos(NULL,0,365,480,170,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
		m_cApplyProtectRemark.MoveWindow(rcClient.left+20,165,145,22,SWP_NOZORDER|SWP_NOMOVE);
	}
	return TRUE;
}

//ȷ������
VOID CDlgLockMachine::OnOK()
{
	m_nType = 0;
// 	//��ȡ��Ϣ
// 	m_PasswordControl.GetUserPassword(m_szPassword);
// 
// 	//�����ж�
// 	if (m_szPassword[0]==0)
// 	{
// 		//������ʾ
// 		CInformation Information(this);
// 		Information.ShowMessageBox(TEXT("���벻��Ϊ�գ������뱣�չ�������а󶨻��߽���󶨣�"),MB_ICONERROR);
// 
// 		//���ý���
// 		m_PasswordControl.SetFocus();
// 
// 		return;
// 	}
	CDlgPassWord dlg;
	if (dlg.DoModal() == IDCANCEL)
	{
	 	return;
	}
	
	lstrcpyn(m_szPassword,dlg.m_szPassword,CountArray(m_szPassword));

	if (m_szPassword[0]==0)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���벻��Ϊ�գ������뱣�չ�������а󶨻��߽���󶨣�"),MB_ICONERROR);

		// 	 		//���ý���
		// 	 		m_PasswordControl.SetFocus();

		return;
	}

	//��������
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//��������
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����������ʧ�ܣ��������������Լ���������״����"),MB_ICONERROR);

		return;
	}

	//���ÿؼ�
	//m_btOk.EnableWindow(FALSE);

	return;
}

void CDlgLockMachine::OnBnClickedButtonPassID()
{
	m_nType = 1;
	//��ȡ��Ϣ
	m_edName.GetWindowText(m_szCompellation,CountArray(m_szCompellation));
// 	m_edPassID.GetWindowText(m_szPassPortID,CountArray(m_szPassPortID));
// 	m_PasswordControl2.GetUserPassword(m_szPassword2);
	CDlgPassID dlg;
	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	lstrcpyn(m_szPassPortID,dlg.m_szPassPortID,CountArray(m_szPassPortID));
	lstrcpyn(m_szPassword2,dlg.m_szPassword,CountArray(m_szPassword2));
	
	//if (m_edName.IsWindowVisible())
	//{
	//	//�����ж�
	//	if (m_szCompellation[0]==0)
	//	{
	//		//������ʾ
	//		CInformation Information(this);
	//		Information.ShowMessageBox(TEXT("��������Ϊ�գ����������룡"),MB_ICONERROR);
	//		//���ý���
	//		m_edName.SetFocus();
	//		return;
	//	}
	//	else
	//	{
	//		TCHAR szDescribe[128]=TEXT("");
	//		CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	//		//��ʵ�����ж�
	//		if (pUserItemElement->EfficacyRealName(m_szCompellation,szDescribe,CountArray(szDescribe))==false)
	//		{
	//			//��ʾ��Ϣ
	//			CInformation Information(this);
	//			Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

	//			//���ý���
	//			m_edName.SetFocus();
	//			return ;
	//		}
	//	}
	//}
	
	//���֤�ж�
	if (m_szPassPortID[0]==0)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���֤�Ų���Ϊ�գ����������룡"),MB_ICONERROR);
		//���ý���
		//m_edPassID.SetFocus();
		return;
	}
	else 
	{
		TCHAR szDescribe[128]=TEXT("");
		CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
		if (pUserItemElement->EfficacyPassPortID(m_szPassPortID,szDescribe,CountArray(szDescribe))==false)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);
			//���ý���
			//m_edPassID.SetFocus();
			return;
		}
	}
	//�����ж�
	if (m_szPassword2[0]==0)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���벻��Ϊ�գ������뱣�չ�����������֤�󶨣�"),MB_ICONERROR);
		//���ý���
		//m_PasswordControl2.SetFocus();
		return;
	}

	//��������
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//��������
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����������ʧ�ܣ��������������Լ���������״����"),MB_ICONERROR);

		return;
	}
	//���ÿؼ�
	//m_btOk.EnableWindow(FALSE);

	return;
}

//���뱣��
void CDlgLockMachine::OnBnClickedButtonPasswordProtect()
{

	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szPasswordProtectUrl[MAX_PATH]=TEXT("");
	_sntprintf(szPasswordProtectUrl,CountArray(szPasswordProtectUrl),TEXT("%s/Member/ApplyProtect.aspx"),pGlobalServer->GetPlatformServer(3));

	ShellExecute(NULL, TEXT("OPEN"),szPasswordProtectUrl,NULL,NULL,SW_NORMAL);

	return;
}

//�����¼�
bool CDlgLockMachine::OnEventMissionLink(INT nErrorCode)
{
	//������
	if (nErrorCode!=0L)
	{
		//���ÿؼ�
		m_btOk.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������еķ��������޷��ɹ����ӷ���������������վά�����棡"),MB_ICONERROR);
	}
	else
	{
		if (m_nType == 0) //�󶨻���
		{
			//��������
			CMD_GP_ModifyMachine ModifyMachine;
			ZeroMemory(&ModifyMachine,sizeof(ModifyMachine));

			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//���ñ���
			ModifyMachine.cbBind=m_cbMachine;
			ModifyMachine.dwUserID=pGlobalUserData->dwUserID;

			//��������
			CWHService::GetMachineIDEx(ModifyMachine.szMachineID);
			CWHEncrypt::MD5Encrypt(m_szPassword,ModifyMachine.szPassword);

			//��������
			ASSERT(GetMissionManager()!=NULL);
			GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_MACHINE,&ModifyMachine,sizeof(ModifyMachine));
		}
		else if (m_nType==1) //�����֤
		{
			//��������
			CMD_GP_ModifyPassPortID ModifyPassPortID;
			ZeroMemory(&ModifyPassPortID,sizeof(ModifyPassPortID));

			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

			//���ñ���
			ModifyPassPortID.cbBind=!pIndividualUserData->cbMoorPassPortID;
			ModifyPassPortID.dwUserID=pGlobalUserData->dwUserID;

			//��������
			CWHService::GetMachineIDEx(ModifyPassPortID.szMachineID);
			CWHEncrypt::MD5Encrypt(m_szPassword2,ModifyPassPortID.szPassword);

			lstrcpyn(ModifyPassPortID.szPassPortID,m_szPassPortID,CountArray(m_szPassPortID));
			lstrcpyn(ModifyPassPortID.szName,m_szCompellation,CountArray(m_szCompellation));

			//��������
			ASSERT(GetMissionManager()!=NULL);
			GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_PASSPORT_ID,&ModifyPassPortID,sizeof(ModifyPassPortID));
		}
	}

	return true;
}

//�ر��¼�
bool CDlgLockMachine::OnEventMissionShut(BYTE cbShutReason)
{
	//�رմ���
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		//CMissionManager * pMissionManager=GetMissionManager();
		//if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//���ÿؼ�
		m_btOk.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���ڵ�ǰ����������æ���ʺŰ󶨲�������ʧ�ܣ����Ժ������ԣ�"),MB_ICONERROR);
	}

	return true;
}

//��ȡ�¼�
bool CDlgLockMachine::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
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

				//���ÿؼ�
				if (m_nType == 0)
				{
					m_btOk.EnableWindow(TRUE);
					m_PasswordControl.SetFocus();
				}
				else if (m_nType == 1)
				{
					m_PasswordControl2.SetFocus();
				}
				m_nType = -1;

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//�����ɹ�
			{
				//��������
				CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)pData;
				//Ч������
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)))
					return false;
				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//��������
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

				CString sSuccessMsg = pOperateSuccess->szDescribeString;
				if (sSuccessMsg.Find("���֤")!=-1) //���֤�󶨳ɹ�
				{
					pIndividualUserData->cbMoorPassPortID = TRUE;
					lstrcpyn(pIndividualUserData->szPassPortID,m_szPassPortID,CountArray(m_szPassPortID));
					lstrcpyn(pIndividualUserData->szCompellation,m_szCompellation,CountArray(m_szCompellation));

					TCHAR szPassPortTmp[LEN_PASS_PORT_ID];	//֤������
					lstrcpyn(szPassPortTmp,m_szPassPortID,CountArray(m_szPassPortID));
					memcpy(szPassPortTmp+6,"********",8);
					m_edPassID.SetWindowText(szPassPortTmp);

					m_edName.SetWindowText(pIndividualUserData->szCompellation);
					m_btPassID.EnableWindow(FALSE);
					m_edPassID.EnableWindow(FALSE);
					m_btPassID.SetWindowText("�Ѱ�");
				}
				else //�����󶨳ɹ�
				{
				//���ñ���
					pGlobalUserData->cbMoorMachine=(m_cbMachine==TRUE)?TRUE:FALSE;

					m_cbMachine=(pGlobalUserData->cbMoorMachine==0)?TRUE:FALSE;
					m_btOk.SetWindowText((pGlobalUserData->cbMoorMachine==0)?TEXT("�󶨱���"):TEXT("�����"));
					m_PasswordControl.SetUserPassword("");
				}


				//�����¼�
				//CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
				//if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_MOOR_MACHINE,0L);

				//��ʾ��Ϣ
				if (pOperateSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				//�رմ���
		//		__super::OnCancel();

				return true;
			}
		}
	}

	//�������
	ASSERT(FALSE);

	return true;
}

//�ػ���Ϣ
VOID CDlgLockMachine::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

// 	rcClient.top = rcClient.top-200;
// 	
// 	dc.FillSolidRect(rcClient,RGB(222,240,253));

	m_ImageMachine.LoadCImage(AfxGetInstanceHandle(),TEXT("USER_MACHINE"));
	m_ImagePassID.LoadCImage(AfxGetInstanceHandle(),TEXT("USER_PASSID"));

	CDC *pDC = GetDC();

	m_ImageMachine.DrawCImage(pDC,77,50);
	m_ImagePassID.DrawCImage(pDC,220,65);

	
	CPen penColor;
	penColor.CreatePen(PS_SOLID,1,RGB(145,168,183));//�߿���ɫ
//     pDC->SelectObject(penColor);
// 	pDC->MoveTo(20,205);
// 	pDC->LineTo(rcClient.Width()-20,205);
// 
// 	if(m_bShowPassportID)
// 	{
// 		pDC->MoveTo(20,360);
// 		pDC->LineTo(rcClient.Width()-20,360);
// 	}
	//m_cApplyProtectRemark.MoveWindow(27+30,355-30+40,200,22);

	penColor.DeleteObject();
	ReleaseDC(pDC);

	return;
}


//////////////////////////////////////////////////////////////////////////////////
