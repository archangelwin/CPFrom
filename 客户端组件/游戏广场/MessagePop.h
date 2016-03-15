#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PlatformPublicize.h"
// CMessagePop �Ի���

class CMessagePop : public CSkinDialog
{
	DECLARE_DYNAMIC(CMessagePop)

public:
	CMessagePop(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessagePop();
	void SetWindowSize(int nwindowcx,int nWindowcy,int nWebBrowsercx,int nWebBrowsercy);
	void InitWebDlg(CString sUrl,CString sCaption,bool bDoModal,bool bMsgPop=true,int nElapse=0);
	void UpdateUrl(CString sUrl);
	
protected:
	CWebBrowser2				    m_BroswerMsg;				//����ؼ�
	CSkinButton                     m_btSubmit;

private:
	int m_nWindowcx;
	int m_nWindowcy;
	int m_nWebBrowsercx;
	int m_nWebBrowsercy;
	CString m_sUrl;
	CString m_strCaption;
	bool m_bDoModal;
	bool m_bMsgPop;
	int	m_nElapse;

// �Ի�������
	enum { IDD = IDD_DIALOG_MSGPOP };

protected:
	afx_msg void OnBnClickedButtonPopMsg();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//�ػ���Ϣ
	//VOID OnPaint();
	virtual VOID OnCancel();
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();	
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
