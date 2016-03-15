#ifndef DLG_PASSID_HEAD_FILE
#define DLG_PASSID_HEAD_FILE

#pragma once
#include "Stdafx.h"

// CDlgPassID 对话框

class CDlgPassID : public CSkinDialog
{
//	DECLARE_DYNAMIC(CDlgPassID)

public:
	CDlgPassID();   // 标准构造函数
	virtual ~CDlgPassID();

// 对话框数据
	enum { IDD = IDD_DIALOG_PASSID };
	//变量定义
public:
	TCHAR							m_szPassword[LEN_PASSWORD];			//用户密码
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];	//证件号码

	//控件变量
protected:
	CSkinButton						m_btOk;								//确定按钮
	CSkinButton						m_btCancel;							//取消按钮

	CSkinEdit						m_edPassID;						     //身份证号

	CPasswordControl				m_CtrPasswordControl;					//用户密码
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();

	DECLARE_MESSAGE_MAP()
};


#endif