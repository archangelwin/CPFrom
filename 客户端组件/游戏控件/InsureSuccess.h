#pragma once
#include "Resource.h"
#include "ShareControlHead.h"

// CInsureSuccess �Ի���
//���ͳɹ���ʾ
class CInsureSuccess : public CDialog
{
	DECLARE_DYNAMIC(CInsureSuccess)

public:
	CInsureSuccess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInsureSuccess();

public:
	void SetInfo(DWORD dwGameID, char *szNickName, DWORD dwTargetGameID, char *szTargetNickName, char *szDate, DWORD dwRecordID, SCORE lScore, char *szScore);
// �Ի�������
	enum { IDD = IDD_INSURE_SUCCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	CPngImageSB		m_Image;
public:
	virtual BOOL OnInitDialog();
private:
	DWORD m_dwGameID;
	char m_szNickName[32];
	DWORD m_dwTargetGameID;
	char m_szTargetNickName[32];
	char m_szDate[32];
	DWORD m_dwRecordID;
	SCORE m_lScore;
	char m_szScore[128];
	int m_nBeginTop;
	int m_nTopSpace;
	//CBitImage m_ImageBuffer;
	CBitmap m_BitBuffer;
	CFont         m_Font;                             //�ؼ�����
	CSkinButton						m_btCloseButton;               //��֤����
public:
	afx_msg void OnBnClickedClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
