#pragma once
#include "Resource.h"
#include "Stdafx.h"
#include "DlgStatus.h"
#include "DlgWhisper.h"
#include "ServerListData.h"
#include "ProcessManager.h"
#include "DlgSearchTable.h"
#include "TableViewFrame.h"
#include "DlgServerManager.h"
#include "PlatformPublicize.h"
#include "ChatHistory.h"
#include "DlgManageUser.h"
// CUserInfoDlg �Ի���

class CUserInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserInfoDlg();

// �Ի�������
	enum { IDD = IDD_USERINFO_DLG };

public:
	void UpdateUI(IClientUserItem * pIClientUserItem,LPCTSTR pszGameLevel);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//��ʼ������
	virtual BOOL OnInitDialog();

	VOID RectifyControl();

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CBrush      m_brBack;
};
