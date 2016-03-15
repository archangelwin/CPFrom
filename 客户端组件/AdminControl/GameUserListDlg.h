#pragma once

#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "..\CGridListCtrlEx\ButtonEx.h"
#include "UserServerInfo.h"
#include "UserInfoList.h"
#include "XGroupBox.h"
#include "ServerListData.h"
#include "DlgSysGameSet.h"
#include "afxwin.h"
#include "afxcmn.h"
// CGameUserListDlg �Ի���

//ת���û���Ϣ
struct tagTranferInfo
{
	DWORD    UserId;
	DWORD    GameID;
	CString  NickName;
};

typedef std::map<DWORD,tagTranferInfo*> CTranferUserInfo;

class CGameUserListDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameUserListDlg)

public:
	CGameUserListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameUserListDlg();

// �Ի�������
	enum { IDD = IDD_GAMEUSERLISTDLG };
public:  
	CImageList  m_ImageList;
	CUserInfoList m_GameUserList;                   //�û�list
	CXGroupBox    m_XGroupBox;
	CDlgSysGameSet* m_pSysGameSetDlg;              //ϵͳ���öԻ���
	DWORD     m_WaringWin;                     
	DWORD     m_WaringLose;
	INT       m_WarningLv; 

	CString     m_SearchGameID;

	INT         m_IsTanking;

	WORD       m_ServerID;

	HWND       m_hWnd;

	bool       m_IsHide;

	CTranferUserInfo    m_lTranferInfoMap; //ת���û�MAP
public:
	SCORE    m_lMaxWin;                 //Ӯ����
	SCORE    m_lMaxLose;                 //�����
	SCORE    m_lNotifyMaxWin;             //Ԥ��Ӯ
	SCORE    m_lNotifyMaxLost;           //Ԥ����
	DWORD    m_dwWinOrLostRate;          //���Ʊ���
public:
	CStatic  m_GameEvent;              
	CEdit	 m_WinScore;
	CEdit    m_LoseScore;
	CEdit    m_WarningWin;
	CEdit    m_WarningLose;
	CEdit    m_WinOrLoseRate;
	CButton  m_SysSet;

	CButton m_RoomSet;
	CButton m_SetWin;
	CButton m_SetLose;
	CButton m_WarningSort;

	CRect m_rect;

public:
	//��ȡϵͳ��Ϣ
	bool GetSysSetInformation();
	
	void OnIsConnect(bool IsConnect);
protected:
	CString GetModuleDir();
	//������Ϣ
	void OnButtonGetInfo();
	//���÷�����Ϣ
	void OnButtonRoomSet();

	void OnButtonWarningSort();

	void OnSetStorage(tagUMSysGameSet* ptagUMSysGameSet,LPCTSTR GameName);

	void OnReSetData();

	void ChangeDlgSize(UINT nID, int x, int y);

	CString OnGetUserID(CString strUserInfo);

protected:
	CStatic  m_Game;
	CStatic  m_Win;
	CStatic  m_Lose;
	CStatic  m_WWin;
	CStatic  m_WLose;
//	CStatic  m_WLRate;


	CGameServerItem* m_GameServerItem;
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL PreTranslateMessage(MSG * pMsg);
	const CString& GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }

public:
	//�����û���Ϣ
	WORD SetUserDataInfo(BYTE cbBuffer[], WORD wBufferSize);
	//����ϵͳ����
	WORD SetSysUserDataInfo(BYTE cbBuffer[], WORD wBufferSize);
	//������Ϸ����
	WORD SetSysGameDataInfo(BYTE cbBuffer[], WORD wBufferSize);
	//����VIP
	WORD SetUserVip(BYTE cbBuffer[], WORD wBufferSize);

	WORD OnReFreshStaroge(BYTE cbBuffer[], WORD wBufferSize);
	//ɾ��VIP
	WORD SetDLUserVip(BYTE cbBuffer[], WORD wBufferSize);

	WORD SetDefault(BYTE cbBuffer[], WORD wBufferSize);

	WORD SetTanking(BYTE cbBuffer[], WORD wBufferSize);
	//��ȡ�û���Ϣ
	bool GetSysUserDataInfo(tagUMUserGameSet* ptagUMUserGameSet);
	//��ȡϵͳ��Ϣ
	bool GetSysGameDataInfo(tagUMSysGameSet* ptagUMSysGameSet);

	bool GetTankingDataInfo(tagUMSysGameSet* ptagUMSysGameSet);

	bool OnSerachOffLineUser(tagUMUserScoreSet * pUserInfo);

	bool OnInsertTransferScoreInfo(tagTransferScore* pTransferInfo);

	bool OnInsetWarnningDataBase(tagLog* ptagLog);

	VOID OnSetAndroidCount(tagAndroidCount* ptagAndroidCount);

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_StorageEnable;
	CStatic m_StaticStaorgeStart;
	CStatic m_StaticStorageDe;
	CEdit m_StorageStart;
	CEdit m_StarogeDe;
	CStatic m_StStorage;
	CButton m_StroageSet;
	CButton m_StorageRefresh;
	afx_msg void OnBnClickedStoragAble();
	afx_msg void OnBnClickedStroageSet();
	afx_msg void OnBnClickedStorageRefresh();
	CStatic m_Thru;
	CButton m_SearchUser;
	CEdit m_UserGameID;
	CStatic m_STSearch;
	afx_msg void OnBnClickedSearchUser();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_AllUserOnLine;
	CStatic m_IsConnect;
	CStatic m_STHau;
	//CStatic m_Prompt;
	//CStatic m_STStock;
	//CStatic m_STDamp;
	CStatic m_TankingGroup;
	CStatic m_StTanking;
	CEdit m_EdTanking;
	CStatic m_StTodayScore;
	CStatic m_StTodayTankingScore;
	CStatic m_StCurTankingScore;
	CStatic m_StServerRate;
	CEdit m_EdServerRate;
	CButton m_BtTanking;
	CButton m_ChTanking;
	afx_msg void OnBnClickedChtanking();
	afx_msg void OnBnClickedBttanking();
	CStatic m_StState;
	// ת�˿ؼ�
	CSkinRichEdit m_RichEd;
	CSkinRichEdit m_LookUpRhEd;

	afx_msg void OnEnLinkRichedit21(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_BtSwitching;
	afx_msg void OnBnClickedButtonSwichting();
	
	CButton m_btAndroidCount;
	CEdit m_EdAndroidCount;
	afx_msg void OnBnClickedBtAndroidcount();
};
