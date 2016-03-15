#pragma once
#include "Resource.h"
#include "WndValidateCode.h"
#include "InputNum.h"

// CAuthenDlg 对话框

class CAuthenDlg : public CSkinDialog
{
	DECLARE_DYNAMIC(CAuthenDlg)

public:
	CAuthenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuthenDlg();

// 对话框数据
	enum { IDD = IDD_AUTHEN_DLG };

public:
	//输入
	void AddCharToEdit(const CString& strChar);
	//重置
	void ResetEdit();
	//删除
	void DelLastCharInEdit();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//初始化函数
	virtual BOOL OnInitDialog();

	//确定函数
	virtual void OnOK();
	//取消消息
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

private:
	//移动键盘
	void MoveInPutNumDlg();
	//验证码验证
	void GetVerifyCode();

public:
	CSkinButton				m_btOK;						//登录按钮
	CSkinButton				m_btCancel;					//取消按钮
	CSkinEdit               m_edInputNum;               //身份证输入框
	CSkinEdit               m_edCheckNum;               //验证码
	CSkinHyperLink			m_staGetPic;				//重新获取验证码
	CWndValidateCode		m_WndValidateCode;					//验证控件


	CString                 m_sValidateCode;                  //生分证号

private:
	CInputNum				m_InputNumDlg;                 //数字键
	CString					m_strCode;                     //

public:
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStaGetpic();
	afx_msg void OnDestroy();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
};
