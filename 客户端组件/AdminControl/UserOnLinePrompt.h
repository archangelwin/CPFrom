#pragma once


// CUserOnLinePrompt �Ի���

class CUserOnLinePrompt : public CDialog
{
	DECLARE_DYNAMIC(CUserOnLinePrompt)

public:
	CUserOnLinePrompt(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserOnLinePrompt();

// �Ի�������
	enum { IDD = IDD_FORMVIEW };

public:
	CRect  m_Rect;

protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
