// DlgPassID.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgPassID.h"


// CDlgPassID �Ի���

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

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT_PASSID, m_edPassID);
	DDX_Control(pDX, IDC_CTRPASSWORD, m_CtrPasswordControl);
}


BEGIN_MESSAGE_MAP(CDlgPassID, CSkinDialog)
END_MESSAGE_MAP()


// CDlgPassID ��Ϣ�������
//��������
BOOL CDlgPassID::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("������"));

	return TRUE;
}

//ȷ������
VOID CDlgPassID::OnOK()
{
	m_edPassID.GetWindowText(m_szPassPortID,CountArray(m_szPassPortID));
	m_CtrPasswordControl.GetUserPassword(m_szPassword);

	CDialog::OnOK();
}