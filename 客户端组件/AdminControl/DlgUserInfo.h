#pragma once
#include "afxwin.h"


// CDlgUserInfo 对话框

class CDlgUserInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgUserInfo)

public:
	CDlgUserInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserInfo();

// 对话框数据
	enum { IDD = IDD_DLGUSERINFO };
public:
	CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore,ltype;
	int ntype;

	tagUMUserScoreSet  m_tagUserInfo;

	SetType     m_Type;

	INT         m_AllowSet;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	void OnSetUserInfo();

	void SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);

	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_StUserInfo;
	afx_msg void OnBnClickedOk();
// 	CEdit m_EdWinMax;
// 	CEdit m_EdLoseMax;
// 	CEdit m_EdNotifyWin;
// 	CEdit m_EdNotifyLose;
// 	CEdit m_EdRate;
// 	CEdit m_EdWinLoseScore;
	afx_msg void OnBnClickedCancel();
//	CComboBox m_CombState;
	CComboBox m_ComWinMax;
	CComboBox m_ComLoseMax;
	CComboBox m_ComNotifyWin;
	CComboBox m_ComNotifyLose;
	CComboBox m_ComRate;
	CComboBox m_ComSetWinLose;
	CEdit m_EdUserInfo;
	int m_RaUserWin;
	int m_RaUserlose;
	int m_RaUserDefault;
	int m_RaState;
	CButton m_BtRaUserWin;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};
