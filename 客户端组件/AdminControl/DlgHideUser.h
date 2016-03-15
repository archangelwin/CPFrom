#pragma once
#include "HideUserList.h"
#include "afxcmn.h"
#include "GameInfo.h"
// CDlgHideUser �Ի���

class CDlgHideUser : public CDialog
{
	DECLARE_DYNAMIC(CDlgHideUser)

public:
	CDlgHideUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHideUser();

// �Ի�������
	enum { IDD = IDD_HIDE_USER_DLG };
protected:
		virtual BOOL OnInitDialog();

public:
	CHideUserList   m_HideUserList;

	int nRow, nCol;
	int m_nItem;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_HideList;
	GameInfo      m_GameInfo;

	void OnInsertHideUser();

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtrefush();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDeleteHideUser();
};
