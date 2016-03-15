#pragma once
#include "StockList.h"
#include "ServerListData.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "StockUserList.h"
// CDlgStock �Ի���

class CDlgStock : public CDialog
{
	DECLARE_DYNAMIC(CDlgStock)

public:
	CDlgStock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStock();

	// �Ի�������
	enum { IDD = IDD_DLG_SET_STOCK };

public:
	CStockList m_StockList;
	CGameServerItem* m_pGameServerItem;
public:
	BOOL m_bClickOnCheck;
	BOOL m_bSelAll;
	SCORE m_cbTotalScore;
	SCORE m_cbYesterdayScore;
	SCORE m_cbdayafterScore;

	WORD OnSetStock(BYTE cbBuffer[], WORD wBufferSize);

public:
	void OnInsertStockInfo(tagUMSysGameSet* ptagUMSysGameSet);

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	CButton m_SetStroag;
	afx_msg void OnBnClickedSetStroag();
	afx_msg void OnBnClickedGetStroage();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCk();
	CStatic m_stTodatScoreTotal;
	CStatic m_stInfo;
	CStockUserList m_StockUserList;
	CStatic m_StWarning;
};
