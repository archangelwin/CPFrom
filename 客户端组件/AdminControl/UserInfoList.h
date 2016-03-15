#pragma once
#include "Stdafx.h"
#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "..\CGridListCtrlEx\CGridRowTraitText.h"
#include "..\CGridListCtrlEx\ButtonEx.h"
#include "..\CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\CGridColumnTraitText.h"
#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "..\CGridListCtrlEx\CGridColumnTraitImage.h"

#include "UserRemarksInfo.h"
#include "GameInfo.h"

#define  WM_SEND_USERINFO WM_USER+200


#define LC_USER             0x00000001
#define LC_TANKING          0x00000002

struct tagFilterUser
{
	DWORD    UserID;
};

struct tagUserSelectCount
{
	INT    UserPos;
};

typedef CWHArray<tagFilterUser>         CFilterUser;
typedef CWHArray<INT>                   CSelectUser;

struct CListCtrl_DataRecord
{
	CListCtrl_DataRecord()
	{}

	CListCtrl_DataRecord(const CString& Nub, const CString& Event, const CString& RoomID, const CString& GameID,const CString& User,
		const CString& NickName,const CString& UserGold,const CString& BankGold,const CString& GameWin,const CString& GameLose,
		const CString& WinLoseGold,const CString& StartTimer,const CString& WinHighest,const CString& LoseHighest,
		const CString& ChangeCardPro,const CString& WarningWin,const CString& WarningLose,const CString& SetAfterScore,const CString& lOutScore,const CString& lInScore
		,const CString& Table,const CString& WinOrLose,const CString& IPAddress,const CString& MachineID,const CString& TodayWLGold,const CString& Recharge,
		const CString& Channel,const CString& szLastOut,const CString& szLastIn,const CString& szFixScore,const CString& lAllOutScore, const CString& lAllInScore, const CString& lDifference)
		:m_Nub(Nub)
		,m_Event(Event)
		,m_RoomID(RoomID)
		,m_GameID(GameID)
		,m_User(User)
		,m_NickName(NickName)
		,m_UserGold(UserGold)
		,m_BankGold(BankGold)
		,m_GameWin(GameWin)
		,m_GameLose(GameLose)
		,m_WinLoseGold(WinLoseGold)
		,m_StartTimer(StartTimer)
		,m_WinHighest(WinHighest)
		,m_LoseHighest(LoseHighest)
		,m_ChangeCardPro(ChangeCardPro)
		,m_WarningWin(WarningWin)
		,m_WarningLose(WarningLose)
		,m_SetAfterScore(SetAfterScore)
		,m_lOutScore(lOutScore)
		,m_lInScore(lInScore)
		,m_Table(Table)
		,m_WinOrLose(WinOrLose)
		,m_IPAddress(IPAddress)
		,m_Machine(MachineID)
		,m_TodayWLGold(TodayWLGold)
		,m_Recharge(Recharge)
		,m_Channel(Channel)
		,m_szLastOut(szLastOut)
		,m_szLastIn(szLastIn)
		,m_szFixScore(szFixScore)
		,m_lAllOutScore(lAllOutScore)
		,m_lAllInScore(lAllInScore)
		,m_lDifference(lDifference)
	{}

	CString	m_Nub;
	CString	m_Event;
	CString	m_User;
	CString  m_GameID;
	CString  m_RoomID;
	CString  m_NickName;
	CString  m_UserGold;
	CString  m_BankGold;
	CString  m_GameWin;
	CString  m_GameLose;
	CString  m_WinLoseGold;
	CString  m_StartTimer;
	CString  m_WinHighest;
	CString  m_LoseHighest;
	CString  m_ChangeCardPro;
	CString  m_WarningWin;
	CString  m_WarningLose;
	CString  m_SetAfterScore;
	CString  m_lOutScore;
	CString  m_lInScore;
	CString  m_Table;
	CString  m_WinOrLose;
	CString  m_IPAddress;
	CString  m_Machine;
	CString  m_TodayWLGold;
	CString  m_Recharge;
	CString  m_Channel;
	CString  m_szLastOut;
	CString  m_szLastIn;
	CString  m_szFixScore;
	CString  m_lAllOutScore;
	CString  m_lAllInScore;
	CString  m_lDifference;

	const CString& GetCellText(int col, bool title) const
	{
		switch(col)
		{
		case 0: { static CString title0(L"���"); return title ? title0 : m_Nub; }
		case 1: { static CString title1(L"����"); return title ? title1 : m_Event; }
		case 2: { static CString title2(L"״̬"); return title ? title2 : m_WinOrLose;}
		case 3: { static CString title3(L"UserID"); return title ? title3 : m_User; }
		case 4: { static CString title4(L"ServerID"); return title ? title4 : m_GameID; }

		case 5: { static CString title5(L"����"); return title ? title5 : m_Channel; }

		case 6: { static CString title6(L"GameID"); return title ? title6 : m_RoomID; }
		case 7: { static CString title7(L"�ǳ�"); return title ? title7 : m_NickName;}
		
// 		case 7: { static CString title7(L"���һ��ת��"); return title ? title7 : m_szLastOut;}
// 		case 8: { static CString title8(L"���һ��ת��"); return title ? title8 : m_szLastIn;}
		
// 		case 7: { static CString title7(L"���"); return title ? title7 : m_UserGold; }
// 		case 8: { static CString title8(L"����"); return title ? title8 : m_BankGold; }
		case 8: { static CString title8(L"���"); return title ? title8 : m_UserGold; }
		case 9: { static CString title9(L"����"); return title ? title9 : m_BankGold; }

		case 10: { static CString title10(L"ת��"); return title ? title10 : m_lOutScore; }
		case 11: { static CString title11(L"ת��"); return title ? title11 : m_lInScore; }
		case 12: { static CString title12(L"��ת��"); return title ? title12 : m_lAllOutScore;  }
		case 13: { static CString title13(L"��ת��"); return title ? title13 : m_lAllInScore;  }
		case 14: { static CString title14(L"��ֵ"); return title ? title14 : m_lDifference;  }

				 case 15: { static CString title15(L"���Ƹ���"); return title ? title15 : m_ChangeCardPro; }
				 

		case 16: { static CString title16(L"��ֵ���"); return title ? title16 : m_Recharge; }
				case 17: { static CString title17(L"����"); return title ? title17 : m_Table; }
				case 18: { static CString title18(L"���ù̶���Ӯ����"); return title ? title18 : m_szFixScore;}

				case 19: { static CString title19(L"���һ��ת��"); return title ? title19 : m_szLastOut;}
				case 20: { static CString title20(L"���һ��ת��"); return title ? title20 : m_szLastIn;}
 
// 		case 9: { static CString title9(L"�ۼ���Ӯ���"); return title ? title9 : m_WinLoseGold; }
// 		case 10: {static CString title10(L"������Ӯ���"); return title ? title10 : m_TodayWLGold; }
// 		case 11: {static CString title11(L"���ú���Ӯ���"); return title ? title11 : m_SetAfterScore; }
// 		case 12: { static CString title12(L"��ʼʱ��"); return title ? title12 : m_StartTimer; }
// 		case 13: { static CString title13(L"Ӯ���"); return title ? title13 : m_WinHighest; }
// 		case 14: { static CString title14(L"�����"); return title ? title14 : m_LoseHighest; }
// 		case 15: { static CString title15(L"���Ƹ���"); return title ? title15 : m_ChangeCardPro; }
// 		case 16: { static CString title16(L"Ԥ��Ӯ"); return title ? title16 : m_WarningWin; }
// 		case 17: { static CString title17(L"Ԥ����"); return title ? title17 : m_WarningLose; }
// 		case 18: { static CString title18(L"Ӯ��"); return title ? title18 : m_GameWin; }
// 		case 19: { static CString title19(L"���"); return title ? title19 : m_GameLose; }

// 		case 14: { static CString title14(L"�ۼ���Ӯ���"); return title ? title14 : m_WinLoseGold; }
// 		case 15: {static CString title15(L"������Ӯ���"); return title ? title15 : m_TodayWLGold; }
// 		case 16: {static CString title16(L"���ú���Ӯ���"); return title ? title16 : m_SetAfterScore; }
// 		case 17: { static CString title17(L"��ʼʱ��"); return title ? title17 : m_StartTimer; }
// 		case 18: { static CString title18(L"Ӯ���"); return title ? title18 : m_WinHighest; }
// 		case 19: { static CString title19(L"�����"); return title ? title19 : m_LoseHighest; }
// // 		case 20: { static CString title20(L"���Ƹ���"); return title ? title20 : m_ChangeCardPro; }
// 		case 21: { static CString title21(L"Ԥ��Ӯ"); return title ? title21 : m_WarningWin; }
// 		case 22: { static CString title22(L"Ԥ����"); return title ? title22 : m_WarningLose; }
// 		case 23: { static CString title23(L"Ӯ��"); return title ? title23 : m_GameWin; }
// 		case 24: { static CString title24(L"���"); return title ? title24 : m_GameLose; }
		case 21: { static CString title21(L"�ۼ���Ӯ���"); return title ? title21 : m_WinLoseGold; }
		case 22: {static CString title22(L"������Ӯ���"); return title ? title22 : m_TodayWLGold; }
		case 23: {static CString title23(L"���ú���Ӯ���"); return title ? title23 : m_SetAfterScore; }
		case 24: { static CString title24(L"��ʼʱ��"); return title ? title24 : m_StartTimer; }
		case 25: { static CString title25(L"Ӯ���"); return title ? title25 : m_WinHighest; }
		case 26: { static CString title26(L"�����"); return title ? title26 : m_LoseHighest; }
 // 		case 20: { static CString title20(L"���Ƹ���"); return title ? title20 : m_ChangeCardPro; }
		case 27: { static CString title27(L"Ԥ��Ӯ"); return title ? title27 : m_WarningWin; }
		case 28: { static CString title28(L"Ԥ����"); return title ? title28 : m_WarningLose; }
		case 29: { static CString title29(L"Ӯ��"); return title ? title29 : m_GameWin; }
		case 30: { static CString title30(L"���"); return title ? title30 : m_GameLose; }

// 		case 20: { static CString title20(L"ת��"); return title ? title20 : m_lOutScore; }
// 		case 21: { static CString title21(L"ת��"); return title ? title21 : m_lInScore; }

// 		case 22: { static CString title22(L"��ֵ���"); return title ? title22 : m_Recharge; }
// 		case 23: { static CString title23(L"����"); return title ? title23 : m_Channel; }
// 		case 24: { static CString title24(L"����"); return title ? title24 : m_Table; }
// 		case 25: { static CString title25(L"IP"); return title ? title25 : m_IPAddress;}
// 		case 26: { static CString title26(L"������"); return title ? title26 : m_Machine;}
//		case 24: { static CString title22(L"��ֵ���"); return title ? title22 : m_Recharge; }

// 		case 25: { static CString title25(L"����"); return title ? title25 : m_Channel; }
// 		case 26: { static CString title26(L"����"); return title ? title26 : m_Table; }
		case 31: { /*static*/ CString title31(L"IP"); return title ? title31 : m_IPAddress;}
		case 32: { /*static*/ CString title32(L"������"); return title ? title32 : m_Machine;}
		default:{ /*static*/ CString emptyStr; return emptyStr; }
		}
	}

	int  GetColCount() const { return 31; }
};

class CUserInfoList : public CGridListCtrlGroups, public IServerUserInfoDataSink
{
public:
	CUserInfoList(void);
	~CUserInfoList(void);
public:
	bool                m_IsFirstList;
	CListCtrl_DataRecord m_GameUserInfo; 
	tabUserVip m_tabUserVip;
	SetType m_settype;
	bool    m_IsSysFault;
	DWORD   m_nPlat;
	DWORD   m_nPlatKind;
	DWORD   m_ServerID;
	DWORD   m_IsSet;
	bool    m_IsSort;
	CImageList* m_ImageList;
	tagUMUserScoreSet m_UserScoreSet;

	GameInfo        m_GameInfo;
	CFilterUser      m_FilterUserArray;
	CSelectUser      m_SelectUser;
	tagFilterUser    m_tagFilterUser;
	DWORD            m_FilterUserID;

	CString          m_strSelectUser;

	CBitmap m_MarkBmp1;
	CBitmap m_MarkBmp2;

protected:
	INT m_nItem;
	INT m_nCol;
	//int nRow, nCol;
public:
	//��ʼ���б�
	VOID InitUserInfoList();

	VOID OnGetUserListInfo();
	
	INT OnUpDataUserData(DWORD UserID);

	VOID OnWarningSort();

	void OnUserSort();

	CString GetModuleDir();

	void OnOpenFilterFile();

	int OnGetUserCount();

	int OnGetMobileCount(int& nMobileOx,int& nMobileFish);

	int OnGetMobliePlazaCount();

	DWORD OnGetUserRecharge();

	SCORE GetUserControlScore(CString pScore);

	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);

//	void OnGetUserInfo();

public:
	//���֪ͨ
	virtual VOID OnGameUserInfoFinish();
	//���֪ͨ
	//	virtual VOID OnGameKindFinish(WORD wKindID)=NULL;
	//����֪ͨ
	virtual VOID OnGameUserInfoUpdateFinish();

	//����֪ͨ
public:
	//����֪ͨ
	virtual VOID OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem);
	//����֪ͨ
	virtual VOID OnGameUserInfoUpdate(CUserInfoItem * pGameUserInfoItem);
	//ɾ��֪ͨ
	virtual VOID OnGameUserInfoDelete(CUserInfoItem * pGameUserInfoItem);

	//ɾ�������û�
	virtual VOID OnDelAllUserData();
	//����ServerID
	virtual VOID OnSetServerID(DWORD ServerID);

	virtual VOID OnSetKindID(DWORD KindID);

	virtual VOID OnRedraw(BOOL nRedraw);

	virtual VOID OnSetUserRemarks(DWORD UserID,CString Remarks);

	virtual VOID OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type);

	virtual VOID ShowUserInfo(tagUMUserScoreSet* userInfo);
	//�Ҽ��б�
	VOID OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult);
protected:
	
	const CString& GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }
	int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnClSetUserVIP(); //����VIP
	afx_msg void OnClDelUserVIP();	//ɾ��VIP
	afx_msg void OnSetUserWin();    //�������Ӯ
	afx_msg void OnSetUserLose();	//���������
	afx_msg void OnSetUserWin1();
	afx_msg void OnSetUserLose2();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetvip();
	afx_msg void OnDevip();
	afx_msg void OnUserSet();
	afx_msg void OnUserSet1();
	afx_msg void OnUserSet2();
	afx_msg void OnUserSet3();
	afx_msg void OnSetDefault();
	afx_msg void OnSetDefault1();
	afx_msg void OnSetDefault2();
	afx_msg void OnSetDefault3();
	afx_msg void OnTh10();
	afx_msg void OnTh20();
	afx_msg void OnTh30();
	afx_msg void OnTh40();
	afx_msg void OnTh50();
	afx_msg void OnTh60();
	afx_msg void OnTh70();
	afx_msg void OnTh80();
	afx_msg void OnTh90();
	afx_msg void OnTh100();
	afx_msg void OnLth10();
	afx_msg void OnLth20();
	afx_msg void OnLth30();
	afx_msg void OnLth40();
	afx_msg void OnLth50();
	afx_msg void OnLth60();
	afx_msg void OnLth70();
	afx_msg void OnLth80();
	afx_msg void OnLth90();
	afx_msg void OnLth100();
	afx_msg void OnThw10();
	afx_msg void OnThw20();
	afx_msg void OnThw30();
	afx_msg void OnThw40();
	afx_msg void OnThw50();
	afx_msg void OnThw60();
	afx_msg void OnThw70();
	afx_msg void OnThw80();
	afx_msg void OnThw90();
	afx_msg void OnThw100();
	afx_msg void OnLtha10();
	afx_msg void OnLtha20();
	afx_msg void OnLtha30();
	afx_msg void OnLtha40();
	afx_msg void OnLtha50();
	afx_msg void OnLtha60();
	afx_msg void OnLtha70();
	afx_msg void OnLtha80();
	afx_msg void OnLtha90();
	afx_msg void OnLtha100();
	afx_msg void OnSetSelf();
	afx_msg void OnSet500w();
	afx_msg void OnSet1000w();
	afx_msg void OnSet2000w();
	afx_msg void OnSet5000w();
	afx_msg void OnSet1e();
	afx_msg void OnSet2e();
	afx_msg void OnSet5e();
	afx_msg void OnSet8000w();
	afx_msg void OnSetUserRemarks();
	afx_msg void OnMark1();
//	afx_msg void OnNMClickGameUserList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUserHide();
	afx_msg void OnCheckHideUser();

	virtual afx_msg BOOL OnItemDblClick(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnFrozen();
};
