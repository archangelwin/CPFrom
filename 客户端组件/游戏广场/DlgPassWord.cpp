// DlgPassWord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "DlgPassWord.h"


// CDlgPassWord �Ի���

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


// CDlgPassWord ��Ϣ�������
//��������
BOOL CDlgPassWord::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("������"));

	return TRUE;
}

//ȷ������
VOID CDlgPassWord::OnOK()
{
	//��ȡ��Ϣ
	m_CtrPasswordControl.GetUserPassword(m_szPassword);

	CDialog::OnOK();
}