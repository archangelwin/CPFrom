// CDlgFrezon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "CDlgFrezon.h"


// CCDlgFrezon �Ի���

IMPLEMENT_DYNAMIC(CCDlgFrezon, CDialog)

CCDlgFrezon::CCDlgFrezon(CWnd* pParent /*=NULL*/)
	: CDialog(CCDlgFrezon::IDD, pParent)
{

}

CCDlgFrezon::~CCDlgFrezon()
{
}

void CCDlgFrezon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CCDlgFrezon, CDialog)
	ON_BN_CLICKED(IDOK, &CCDlgFrezon::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CCDlgFrezon::OnInitDialog()
{
	__super::OnInitDialog();

	m_Edit.SetWindowText("����Ա����!");

	return TRUE;
}

// CCDlgFrezon ��Ϣ�������

void CCDlgFrezon::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Edit.GetWindowText(m_strFrezonReason);
	OnOK();
}
