// DlgMobileBind.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgMobileBind.h"


//�ؼ���ʶ
#define IDC_WEB_PUBLICIZE			300									//����ؼ�

// CDlgMobileBind �Ի���
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


// CDlgMobileBind ��Ϣ�������

//��������
BOOL CDlgMobileBind::OnInitDialog()
{
	__super::OnInitDialog();
	MoveWindow(0,0,480,430);
	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//���ñ���
	SetWindowText(TEXT("�ֻ���"));


	//���ؼ�
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);
	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/LogonLogo.aspx"),pGlobalServer->GetPlatformServer(3));
	//���ù��
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetWindowPos(NULL,0,0,400,420,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	return true;
}
