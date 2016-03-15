// DlgPassValidate.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgPassValidate.h"


// CDlgPassValidate 对话框

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


// CDlgPassValidate 消息处理程序

BOOL CDlgPassValidate::OnInitDialog()
{
	__super::OnInitDialog();
	if (m_nValidateType == 8)
	{
		SetWindowText(TEXT("手机验证"));
		m_cTitleValidate.SetWindowText("请输入手机验证码：");		
	}
	else if (m_nValidateType ==9)
	{
		SetWindowText(TEXT("身份证验证"));
		m_cTitleValidate.SetWindowText("请输入身份证号码：");		
	}
	else
	{
		SetWindowText(TEXT("系统登录验证"));
		m_cTitleValidate.SetWindowText("请输入验证码：");	
	}
	MoveWindow(0,0,392,204);
	m_cTitleValidate.SetCustomFont(true,false,false,false,-12);
	m_cTitleValidate.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_cTitleValidate.MoveWindow(20,50,180,16);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgPassValidate::OnBnClickedButtonPassvali()
{
	m_eValidate.GetWindowText(m_sValidateCode);

	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	if (m_nValidateType == 9)
	{	//身份证号
		if (pUserItemElement->EfficacyPassPortID(m_sValidateCode,szDescribe,CountArray(szDescribe))==false)
		{
			//提示信息
			CInformation Information(this);
			Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

			//设置焦点
			m_eValidate.SetFocus();
			return;
		}
	}

	__super::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgPassValidate::SetValidateType(int nType)
{
	m_nValidateType = nType;
}
