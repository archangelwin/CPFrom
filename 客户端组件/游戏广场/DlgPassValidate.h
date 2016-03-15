#pragma once

#include "Stdafx.h"
#include "Resource.h"
// CDlgPassValidate 对话框

class CDlgPassValidate : public CSkinDialog
{
	DECLARE_DYNAMIC(CDlgPassValidate)

public:
	CDlgPassValidate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPassValidate();
	void SetValidateType(int nType);
	CString m_sValidateCode;

// 对话框数据
	enum { IDD = IDD_DIALOG_PASSVALIDATE };

protected:
	CSkinButton						m_btEnSure;								//确定按钮
	CSkinHyperLink                  m_cTitleValidate;
	CSkinEdit                       m_eValidate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPassvali();

private:
	int m_nValidateType; //8校验手机,9校验身份证
};
