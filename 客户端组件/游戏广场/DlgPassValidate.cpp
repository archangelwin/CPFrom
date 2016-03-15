// DlgPassValidate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgPassValidate.h"


// CDlgPassValidate �Ի���

IMPLEMENT_DYNAMIC(CDlgPassValidate, CSkinDialog)

CDlgPassValidate::CDlgPassValidate(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CDlgPassValidate::IDD, pParent)
{
	m_sValidateCode = "";
}

CDlgPassValidate::~CDlgPassValidate()
{
}

void CDlgPassValidate::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_PASSVALI, m_btEnSure);
	DDX_Control(pDX, IDC_STATIC_PASSVALI, m_cTitleValidate);
	DDX_Control(pDX, IDC_EDIT_PASS_VALIDATE, m_eValidate);
}


BEGIN_MESSAGE_MAP(CDlgPassValidate, CSkinDialog)
	ON_BN_CLICKED(IDC_BUTTON_PASSVALI, &CDlgPassValidate::OnBnClickedButtonPassvali)
END_MESSAGE_MAP()


// CDlgPassValidate ��Ϣ�������

BOOL CDlgPassValidate::OnInitDialog()
{
	__super::OnInitDialog();
	if (m_nValidateType == 8)
	{
		SetWindowText(TEXT("�ֻ���֤"));
		m_cTitleValidate.SetWindowText("�������ֻ���֤�룺");		
	}
	else if (m_nValidateType ==9)
	{
		SetWindowText(TEXT("���֤��֤"));
		m_cTitleValidate.SetWindowText("���������֤���룺");		
	}
	else
	{
		SetWindowText(TEXT("ϵͳ��¼��֤"));
		m_cTitleValidate.SetWindowText("��������֤�룺");	
	}
	MoveWindow(0,0,392,204);
	m_cTitleValidate.SetCustomFont(true,false,false,false,-12);
	m_cTitleValidate.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_cTitleValidate.MoveWindow(20,50,180,16);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgPassValidate::OnBnClickedButtonPassvali()
{
	m_eValidate.GetWindowText(m_sValidateCode);

	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	if (m_nValidateType == 9)
	{	//���֤��
		if (pUserItemElement->EfficacyPassPortID(m_sValidateCode,szDescribe,CountArray(szDescribe))==false)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

			//���ý���
			m_eValidate.SetFocus();
			return;
		}
	}

	__super::OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgPassValidate::SetValidateType(int nType)
{
	m_nValidateType = nType;
}
