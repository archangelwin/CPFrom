#pragma once
#include "Stdafx.h"
#include "UserManagerHead.h"
#include <map>
#include "ServerListData.h"
//#include "UserInfoList.h"

class CUserInfoItem;

typedef std::map<DWORD, CUserInfoItem *> CUserInfoMap;

//列表接口
interface IServerUserInfoDataSink
{
	//状态通知
public:
	//完成通知
	virtual VOID OnGameUserInfoFinish()=NULL;
	//完成通知
//	virtual VOID OnGameKindFinish(WORD wKindID)=NULL;
	//更新通知
	virtual VOID OnGameUserInfoUpdateFinish()=NULL;

	//更新通知
public:
	//插入通知
	virtual VOID OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem)=NULL;
	//更新通知
	virtual VOID OnGameUserInfoUpdate(CUserInfoItem * pGameUserInfoItem)=NULL;
	//删除通知
	virtual VOID OnGameUserInfoDelete(CUserInfoItem * pGameUserInfoItem)=NULL;

	//删除所有用户信息
	virtual VOID OnDelAllUserData()=NULL;
	//设置UserID
	virtual VOID OnSetServerID(DWORD ServerID)=NULL;

	virtual VOID OnSetKindID(DWORD KindID)=NULL;

	virtual VOID OnRedraw(BOOL nRedraw)=NULL;

	virtual VOID OnSetUserRemarks(DWORD UserID,CString Remarks)=NULL;

	virtual VOID OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type)=NULL;

	virtual VOID ShowUserInfo(tagUMUserScoreSet* userInfo)=NULL;
};


class CUserInfoItem
{

public:
	CUserInfoItem();
	virtual ~CUserInfoItem();
public:
	tagUMUserScoreSet m_tagUMUserScoreSet;  //用户信息

	CString	szServerName;			//房间名称

	CUserInfoItem* m_pCUserInfoItem;

	DWORD GetdwGameID() {return m_tagUMUserScoreSet.dwGameID;}

	DWORD GetdwUserID() {return m_tagUMUserScoreSet.dwUserID;}

};

class CUserServerInfo
{
public:
	CUserServerInfo(void);
	~CUserServerInfo(void);

public:
//	CUserInfoList m_UserInfoList;

public:
//	tagUMUserScoreSet m_tagUMUserScoreSet;
	CUserInfoMap m_UserInfoMap;    
	CUserInfoMap m_UserOffLineMap;
	vector<pair<DWORD,CUserInfoItem*>> tUserVector;
	CString m_szGameName;          //房间名称
	bool m_IsSearch;
//	CUserInfoList m_UserInfoList;
	
public:
	//插入用户
	bool OnInsertUserInfo(tagUMUserScoreSet* pUserInfo);
	//删除用户
	bool OnDeleteUserInfo(tagUMUserScoreSet* pUserInfo);
	//更新用户
	bool OnUpdataGameUserInfo(CGameServerItem * pGameServerItem);
	//插入用户
	bool OnInsertGameUserInfo(CGameServerItem * pGameServerItem);

	bool OnInsertGameKindInfo(CGameKindItem * pGameServerItem);

	BOOL OnSearchUser(CString GameID);

	bool OnDeleteAllUserInfo();

	bool OnInsertOffLineUser(tagUMUserScoreSet* pUserInfo);

	bool OnSreachOffLineUserInfo(tagUMUserScoreSet* pUserInfo);

	/*CUserInfoItem cmp(const pair<DWORD,CUserInfoItem*>& x,const pair<DWORD,CUserInfoItem*>& y);*/
	void OnUserInfoSort();
	void OnMapSort(map<DWORD,CUserInfoItem*>& tMap,vector<pair<DWORD,CUserInfoItem*>>& tVector);

	bool OnSerachUser(CString userID);

	tagUMUserScoreSet OnSerachUserInfo(CString GameID);
	
	//静态变量
public:
	IServerUserInfoDataSink*        m_pIServerUserInfoDataSink;         //
protected:
	static CUserServerInfo *		m_pCUserServerInfo;					//列表数据

public:
	DWORD                           m_dwAllOnLineCount;                 //总在线人数


	//配置函数
public:
	//设置接口
	VOID SetServerUserInfoDataSink(IServerUserInfoDataSink * pIServerUserInfoDataSink);

	//状态通知
public:
	//完成通知
	VOID OnGameUserInfoFinish();
	//完成通知
	//	virtual VOID OnGameKindFinish(WORD wKindID)=NULL;
	//更新通知
	//VOID OnGameUserInfoUpdateFinish();

	void OnUpdateUserRemarks(DWORD UserID,CString Remarks);

	void OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type);
public:
	//获取对象
	static CUserServerInfo * GetInstance()
	{ 
		if (m_pCUserServerInfo == NULL)
		{
			m_pCUserServerInfo = new CUserServerInfo;
		}
		return m_pCUserServerInfo;
	}
};
