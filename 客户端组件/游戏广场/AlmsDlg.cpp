// AlmsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "AlmsDlg.h"

#define IDC_BROWSER_ALMS					100									//����ؼ�

// CAlmsDlg �Ի���
CAlmsDlg::CAlmsDlg() : CSkinDialog(IDD_DIALOG_ALMS)
{
	//�������
	m_MissionManager.InsertMissionItem(this);

	return;
}

CAlmsDlg::~CAlmsDlg()
{

}

void CAlmsDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ALMS, m_btGetAlms);
}

BEGIN_MESSAGE_MAP(CAlmsDlg, CSkinDialog)
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ALMS, &CAlmsDlg::OnBnClickedButtonAlms)
END_MESSAGE_MAP()

//��������
BOOL CAlmsDlg::OnInitDialog()
{
	__super::OnInitDialog();
    MoveWindow(0,0,450,390);
	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//���ñ���
	SetWindowText(TEXT("��ȡ�ȼý�"));	
	
	//�����ؼ�
	m_WebPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcClient,this,IDC_BROWSER_ALMS);

	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBrowseUrl[256]=TEXT("");
	_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/Ads/Alms.aspx"),pGlobalServer->GetPlatformServer(3));
	//���ӵ�ַ
	m_WebPublicize.Navigate(szBrowseUrl,NULL,NULL,NULL,NULL); 

	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btGetAlms.SetButtonImage(IDB_BT_ALMS,/*TEXT("BT_GET_ALMS"),*/hInstance,false,false);

    m_WebPublicize.MoveWindow(1,36,448,182);
	m_btGetAlms.MoveWindow(130,243,190,55);

	TCHAR szAlms[MAX_PATH];
	pGlobalServer->ReadPlatFileString("PlatInfo","Alms",szAlms,MAX_PATH);
	GetDlgItem(IDC_STATIC_ALMS)->SetWindowText(szAlms);

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	return TRUE;
}

//��Ϣ����
BOOL CAlmsDlg::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}


// CAlmsDlg ��Ϣ�������
void CAlmsDlg::OnBnClickedButtonAlms()
{
	//�Ƿ����ȡ
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//if (pGlobalUserData->lUserInsure + pGlobalUserData->lUserScore >=1000)
	//{
	//	//��ʾ��ʾ
	//	CInformation Information(this);
	//	Information.ShowMessageBox(TEXT("����ǰ�Ľ��������1000����ʱ�޷���ȡ��"),MB_ICONERROR);
	//	return;
	//}
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
}


//�����¼�
bool CAlmsDlg::OnEventMissionLink(INT nErrorCode)
{
	//������
	if (nErrorCode!=0L)
	{
		//���ÿؼ�
		m_btGetAlms.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������еķ��������޷��ɹ����ӷ���������������վά�����棡"),MB_ICONERROR);
	}
	else
	{
		//��������
		ASSERT(GetMissionManager()!=NULL);
		CMD_GP_GetAlms GetAlms;
		ZeroMemory(&GetAlms,sizeof(GetAlms));
		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

		GetAlms.dwUserID = pGlobalUserData->dwUserID;
		//������ʶ
		CWHService::GetMachineIDEx(GetAlms.szMachineID);
		lstrcpyn(GetAlms.szPassword,pGlobalUserInfo->GetGlobalUserData()->szPassword,CountArray(GetAlms.szPassword));

		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_GET_ALMS,&GetAlms,sizeof(GetAlms));
	}

	return true;
}

//�ر��¼�
bool CAlmsDlg::OnEventMissionShut(BYTE cbShutReason)
{
	//�رմ���
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		//CMissionManager * pMissionManager=GetMissionManager();
		//if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//���ÿؼ�
		m_btGetAlms.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���ڵ�ǰ����������æ����ȡ�ȼý�ʧ�ܣ����Ժ������ԣ�"),MB_ICONERROR);
	}

	return true;
}

//��ȡ�¼�
bool CAlmsDlg::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
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

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//�����ɹ�
			{
				//��������
				CMD_GP_GetAlmsSuccess * pOperateSuccess=(CMD_GP_GetAlmsSuccess *)pData;
				//Ч������
				ASSERT(wDataSize>=(sizeof(CMD_GP_GetAlmsSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_GetAlmsSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//���±��չ�
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pOperateSuccess->lUserInsure;

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
//VOID CAlmsDlg::OnPaint()
//{
//	CPaintDC dc(this);
//
//	//��ȡλ��
//	CRect rcClient;
//	GetClientRect(&rcClient);
//	//CDC *pDC = GetDC();
//	//CPen penColor;
//	//penColor.CreatePen(PS_SOLID,1,RGB(145,168,183));//�߿���ɫ
//	//pDC->SelectObject(penColor);
//	//pDC->MoveTo(20,205);
//	//pDC->LineTo(rcClient.Width()-20,205);
//
//	//penColor.DeleteObject();
//	//ReleaseDC(pDC);
//
//	return;
//}