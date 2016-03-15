#ifndef DLG_QQLOGON_HEAD_FILE
#define DLG_QQLOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PlatformPublicize.h"
// CDlgQQLogon �Ի���

class CDlgQQLogon : public CDialog
{
	//friend class CDlgLogon;
	DECLARE_DYNAMIC(CDlgQQLogon)

public:
	CDlgQQLogon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgQQLogon();
	void SetUrl(CString sUrl);
	void MoveDlg(int nWidth, int nHeight);

protected:
	long                            m_hLength;//���� 
	long                            m_hWidth;//���
	long                            m_hLeft;//��ƫ�Ƶĳ���
	CString                         m_sQQUrl;
	CWebBrowser2				    m_BroswerQQLogon;				//����ؼ�
	CSkinButton                     m_btClose;
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�

// �Ի�������
	enum { IDD = IDD_DIALOG_QQLOGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnNavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////////

#endif
