#pragma once
#include "explorer1.h"


// CDlgWeb �Ի���

class CDlgWeb : public CDialog
{
	DECLARE_DYNAMIC(CDlgWeb)

public:
	CDlgWeb(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWeb();

// �Ի�������
	enum { IDD = IDD_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	CExplorer1 m_WebControl;
};
