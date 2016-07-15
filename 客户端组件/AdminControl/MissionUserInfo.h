#pragma once
#include "Stdafx.h"
#include "GameUserListDlg.h"
#include "DlgStock.h"
#include "DlgLog.h"
#include "DlgUserOnLineSort.h"
#include "UserOfflineDlg.h"
#include "DlgSilver.h"
//class ICUserManagerItem;

//typedef CMap<DWORD ,DWORD, ICUserManagerItem * ,ICUserManagerItem * &> CUserInfoMap;

// class ICUserManagerItem
// {
// public:
// 	ICUserManagerItem();
// 
// public:
// 	tagUMUserScoreSet m_tagUMUserScoreSet;
// 
// 	virtual DWORD GetdwUserID() {return tagUMUserScoreSet.dwUserID;}
// 
// };

#define   WM_USER_ONLINE_PROMPT          WM_USER+200

class CMissionUserInfo : public CMissionItem ,public CDialog
{
public:
	CMissionUserInfo(void);
	~CMissionUserInfo(void);

public:
	CGameUserListDlg* m_GameUserListDlg;
	CDlgStock*        m_StockDlg;
	CDlgLog*          m_pLogDlg;
	CDlgUserOnLineSort* m_pOnLineUserSortDlg;
	CUserOfflineDlg*     m_pOffLineUserDlg;
	CDlgSilver*          m_pSilverDlg;


	HWND              m_hWnd;
//	CGameServerItem* m_GameServerItem;
//	CDlgSysGameSet*   m_SysGameSetDlg;
	static CMissionUserInfo* m_pMissionUserInfo;

protected:
	bool m_SysScoreSet;
	bool m_OUserSet;
	bool m_SysScoreGameSet;
	bool m_SetUserVip;                 //����VIP
	bool m_SetDLUserVip;               //ɾ��VIP

	bool m_IsAccurateSreach;           

	//���غ���
public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	//�����û���Ϣ
	void SetUserInfo();
	//����ϵͳ��Ϣ
	void SetSysInfo();
	//����ϵͳ��Ϸ��Ϣ
	void SetSysGameInfo();
	//����VIP
	void SetUserVip(tabUserVip ptabUserVip);
	//ɾ��VIP
	void SetDLUserVip(tabUserVip ptabUserVip);

	void OnReRefreshStroage();

	void OnSetDeFault();

	void OnGetStroag();

	void OnSetStroag();

	void OnSetTanking();

	void OnGetOffLineUser();

	void SreachOffLineUser(CString szSreachInfo);

	void OnSreachOffLineUser(CString szUserID);

	void SetOffLineUser(tagUMUserScoreSet offlineuserInfo);

	void OnSetRemarks(DWORD UserID,CString Remarks);

	void OnSetAndroidCount(INT AndroidCount,WORD ServerID);

	void OnGetStockUser(tagQueryGame* QueryGame);

	void OnFrezon(tagUserID* UserId);

	void OnGetSameMachine(DWORD UserId);

	CString GetModuleDir();
public:
	//��ȡ�û�����
	bool GetUserInfoSet();

public:
	static CMissionUserInfo* GetInstance()
	{
		if (m_pMissionUserInfo == NULL)
		{
			m_pMissionUserInfo = new CMissionUserInfo;
		}
		return m_pMissionUserInfo; 
	}

	DECLARE_MESSAGE_MAP()
};
