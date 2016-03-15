#pragma once


// CUserOnLinePrompt 对话框

class CUserOnLinePrompt : public CDialog
{
	DECLARE_DYNAMIC(CUserOnLinePrompt)

public:
	CUserOnLinePrompt(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserOnLinePrompt();

// 对话框数据
	enum { IDD = IDD_FORMVIEW };

public:
	CRect  m_Rect;

protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
