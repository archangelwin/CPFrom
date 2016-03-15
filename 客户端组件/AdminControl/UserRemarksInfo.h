#pragma once
#include "afxwin.h"


// CUserRemarksInfo �Ի���

class CUserRemarksInfo : public CDialog
{
	DECLARE_DYNAMIC(CUserRemarksInfo)

public:
	CUserRemarksInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserRemarksInfo();

// �Ի�������
	enum { IDD = IDD_USERREMARKSINFO };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	static CUserRemarksInfo* m_pUserRemarksInfo;
	tagUMUserScoreSet m_UMUserInfo;
	CString   m_UserRemarks;

public:
	void OnSetUserInfo();

public:
	static CUserRemarksInfo* GetInstance()
	{
		if (m_pUserRemarksInfo == NULL)
		{
			m_pUserRemarksInfo = new CUserRemarksInfo;
		}
		return m_pUserRemarksInfo;
	}
	DECLARE_MESSAGE_MAP()
	CEdit m_EDRemarks;
	CStatic m_STUserInfo;
	afx_msg void OnBnClickedBtadd();
};
