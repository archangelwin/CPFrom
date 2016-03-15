#ifndef DLG_PASSWORD_HEAD_FILE
#define DLG_PASSWORD_HEAD_FILE


#pragma once
#include "Stdafx.h"

// CDlgPassWord 对话框

class CDlgPassWord : public CSkinDialog
{
//	DECLARE_DYNAMIC(CDlgPassWord)

public:
	CDlgPassWord();   // 标准构造函数
	virtual ~CDlgPassWord();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOCKMACHINE };
//变量
public:
	TCHAR							m_szPassword[LEN_PASSWORD];			//用户密码

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
//控件
protected:
	CSkinButton						m_btOk;								//确定按钮
	CSkinButton						m_btCancel;							//取消按钮


	CPasswordControl				m_CtrPasswordControl;					//用户密码


	DECLARE_MESSAGE_MAP()
};


#endif