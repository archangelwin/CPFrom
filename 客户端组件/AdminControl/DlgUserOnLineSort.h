#pragma once

#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "UserInfoList.h"
#include "UserSortList.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "OnLineSortList.h"

// CDlgUserOnLineSort �Ի���

class CDlgUserOnLineSort : public CDialog
{
	DECLARE_DYNAMIC(CDlgUserOnLineSort)

public:
	CDlgUserOnLineSort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserOnLineSort();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	COnLineSortList m_UserInfoList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonRefush();
	CButton m_BtRefresh;
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	COnLineSortList m_DecList;
};
