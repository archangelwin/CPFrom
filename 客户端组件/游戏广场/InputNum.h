#pragma once

#include "Resource.h"
class CAuthenDlg;
// CInputNum 对话框

class CInputNum : public CDialog
{
	DECLARE_DYNAMIC(CInputNum)

public:
	CInputNum(CAuthenDlg* pParent = NULL);   // 标准构造函数
	virtual ~CInputNum();

// 对话框数据
	enum { IDD = IDD_INPUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	CSkinButton 	m_btNum1;
	CSkinButton 	m_btNum2;
	CSkinButton 	m_btNum3;
	CSkinButton 	m_btNum4;
	CSkinButton 	m_btNum5;
	CSkinButton 	m_btNum6;
	CSkinButton 	m_btNum7;
	CSkinButton 	m_btNum8;
	CSkinButton 	m_btNum9;
	CSkinButton 	m_btNum10;
	CSkinButton 	m_btNum11;
	CSkinButton 	m_btDel;
	CSkinButton 	m_btReset;
	CAuthenDlg*     m_pAuthenDlg;

private:
	void AddNumToEidt(int nID);

public:
	afx_msg void OnBnClickedBtnNum1();
	afx_msg void OnBnClickedBtnNum2();
	afx_msg void OnBnClickedBtnNum3();
	afx_msg void OnBnClickedBtnNum4();
	afx_msg void OnBnClickedBtnNum5();
	afx_msg void OnBnClickedBtnNum6();
	afx_msg void OnBnClickedBtnNum7();
	afx_msg void OnBnClickedBtnNum8();
	afx_msg void OnBnClickedBtnNum9();
	afx_msg void OnBnClickedBtnNum10();
	afx_msg void OnBnClickedBtnNum11();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnDoubleclickedBtnNum1();
	afx_msg void OnBnDoubleclickedBtnNum2();
	afx_msg void OnBnDoubleclickedBtnNum3();
	afx_msg void OnBnDoubleclickedBtnNum4();
	afx_msg void OnBnDoubleclickedBtnNum5();
	afx_msg void OnBnDoubleclickedBtnNum6();
	afx_msg void OnBnDoubleclickedBtnNum7();
	afx_msg void OnBnDoubleclickedBtnNum8();
	afx_msg void OnBnDoubleclickedBtnNum9();
	afx_msg void OnBnDoubleclickedBtnNum10();
	afx_msg void OnBnDoubleclickedBtnNum11();
};
