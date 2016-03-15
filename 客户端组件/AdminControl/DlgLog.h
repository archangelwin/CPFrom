#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "EditLog.h"

// CDlgLog �Ի���

class CDlgLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgLog)

public:
	CDlgLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLog();

	UINT      m_Index;

// �Ի�������
	enum { IDD = IDD_LOG };

public:
	bool OnInsertOnLineUser(tagAdmin* ptagAdmin);

	bool OnInsertLog(tagLog* ptagLog);

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_AdminList;
	CEdit m_LogCtrl;

	CEditLog m_EditLog;
};
