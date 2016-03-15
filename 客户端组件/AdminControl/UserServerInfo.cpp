#include "StdAfx.h"
#include "UserServerInfo.h"
#include "ServerListData.h"
#include <algorithm>
//静态变量

CUserServerInfo * CUserServerInfo::m_pCUserServerInfo=NULL;				//列表数据

CUserInfoItem::CUserInfoItem()
{
	m_pCUserInfoItem=NULL;

	return;
}
CUserInfoItem::~CUserInfoItem()
{
	if (m_pCUserInfoItem != NULL)
	{
		delete m_pCUserInfoItem;
		m_pCUserInfoItem = NULL;
	}
}

/////////////////////////////////////////////////////////////////////


CUserServerInfo::CUserServerInfo(void)
{
	m_IsSearch = false;
}

CUserServerInfo::~CUserServerInfo(void)
{
	CUserInfoMap::iterator it = m_UserInfoMap.begin();

	ASSERT(m_pCUserServerInfo==this);
	if (m_pCUserServerInfo==this)
	{
		m_pCUserServerInfo = NULL;
	}
}


bool CUserServerInfo::OnInsertUserInfo(tagUMUserScoreSet * pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	if (m_IsSearch == true)
	{
		return false;
	}

	CUserInfoItem* pCUserInfoItem = NULL;
	CUserInfoMap::iterator it = m_UserInfoMap.find(pUserInfo->dwUserID);

	if (it == m_UserInfoMap.end())
	{
		pCUserInfoItem = new CUserInfoItem;
		if (pCUserInfoItem==NULL) return false;
		m_UserInfoMap.insert(std::make_pair(pUserInfo->dwUserID,pCUserInfoItem));
	}
	else
		pCUserInfoItem = it->second;

	CopyMemory(&pCUserInfoItem->m_tagUMUserScoreSet,pUserInfo,sizeof(tagUMUserScoreSet));

	CServerListData* pCServerListData = CServerListData::GetInstance();
	CGameServerItem * pGameServerItem = NULL;
	if (pCServerListData == NULL)
	{
		return false;
	}
	if (pCServerListData->m_GameServerItemMap.Lookup(pUserInfo->dwServerID,pGameServerItem)==TRUE)
	{
		if (pGameServerItem == NULL)
		{
			return false;
		}
		pCUserInfoItem->szServerName = pGameServerItem->m_GameServer.szServerName;
		
	}

	if (it == m_UserInfoMap.end())
	{
		
		m_pIServerUserInfoDataSink->OnGameUserInfoInsert(pCUserInfoItem);
	}
 	else
 		m_pIServerUserInfoDataSink->OnGameUserInfoUpdate(pCUserInfoItem);
	

	pCUserInfoItem = NULL;
	return true;
}

bool CUserServerInfo::OnDeleteUserInfo(tagUMUserScoreSet * pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	CUserInfoMap::iterator it = m_UserInfoMap.find(pUserInfo->dwUserID);

	if (it != m_UserInfoMap.end())
	{
		m_pIServerUserInfoDataSink->OnGameUserInfoDelete(it->second);
		m_UserInfoMap.erase(it);
	}
	return true;
}

bool CUserServerInfo::OnSreachOffLineUserInfo(tagUMUserScoreSet* pUserInfo)
{

	m_pIServerUserInfoDataSink->OnSetKindID(0);
	m_pIServerUserInfoDataSink->OnSetServerID(0);

	CUserInfoItem* pCUserInfoItem = NULL;
	pCUserInfoItem = new CUserInfoItem;

	CopyMemory(&pCUserInfoItem->m_tagUMUserScoreSet,pUserInfo,sizeof(tagUMUserScoreSet));

	m_pIServerUserInfoDataSink->OnGameUserInfoInsert(pCUserInfoItem);

	return true;
}

bool CUserServerInfo::OnUpdataGameUserInfo(CGameServerItem * pGameServerItem)
{
	if (pGameServerItem == NULL) return false;

	m_pIServerUserInfoDataSink->OnDelAllUserData();
	m_pIServerUserInfoDataSink->OnSetServerID(pGameServerItem->m_GameServer.wServerID);
	m_pIServerUserInfoDataSink->OnSetKindID(0);
	CUserInfoMap::iterator it = m_UserInfoMap.begin();
	m_pIServerUserInfoDataSink->OnRedraw(FALSE);
	for (it; it != m_UserInfoMap.end(); ++it)
	{	
		if(it->second->m_tagUMUserScoreSet.dwServerID  == pGameServerItem->m_GameServer.wServerID )
		{
			m_pIServerUserInfoDataSink->OnGameUserInfoInsert(it->second);
		}
	}
	m_pIServerUserInfoDataSink->OnRedraw(TRUE);
	return true;
}

bool CUserServerInfo::OnInsertGameUserInfo(CGameServerItem * pGameServerItem)
{
	if (pGameServerItem == NULL) return false;

	m_pIServerUserInfoDataSink->OnDelAllUserData();	
	m_pIServerUserInfoDataSink->OnSetServerID(0);
	m_pIServerUserInfoDataSink->OnSetKindID(0);
	if (m_IsSearch == true)
	{
		m_IsSearch = false;
	}
	CUserInfoMap::iterator it = m_UserInfoMap.begin();
	m_pIServerUserInfoDataSink->OnRedraw(FALSE);
	for (it; it != m_UserInfoMap.end(); ++it)
	{				
			m_pIServerUserInfoDataSink->OnGameUserInfoInsert(it->second);
	}
	m_pIServerUserInfoDataSink->OnRedraw(TRUE);

	return true;
}

bool CUserServerInfo::OnInsertGameKindInfo(CGameKindItem * pGameServerItem)
{
	m_pIServerUserInfoDataSink->OnDelAllUserData();
	m_pIServerUserInfoDataSink->OnSetKindID(pGameServerItem->m_GameKind.wKindID);
	m_pIServerUserInfoDataSink->OnSetServerID(0);
	CUserInfoMap::iterator it = m_UserInfoMap.begin();
	m_pIServerUserInfoDataSink->OnRedraw(FALSE);
	for (it; it != m_UserInfoMap.end(); ++it)
	{	
		if(it->second->m_tagUMUserScoreSet.dwKindID  == pGameServerItem->m_GameKind.wKindID )
		{
			m_pIServerUserInfoDataSink->OnGameUserInfoInsert(it->second);
		}
	}
	m_pIServerUserInfoDataSink->OnRedraw(TRUE);

	return true;
}

BOOL CUserServerInfo::OnSearchUser(CString GameID)
{
	CUserInfoMap::iterator it = m_UserInfoMap.begin();
	CString UserGameID;
	CString NickName;
	bool IsSearched = false;
	for (it; it != m_UserInfoMap.end(); ++it)
	{
		UserGameID.Format("%d",it->second->m_tagUMUserScoreSet.dwGameID);
		NickName.Format("%s",it->second->m_tagUMUserScoreSet.szNickName);
		UserGameID += NickName;
		if(UserGameID.Find(GameID) != -1 )
		{
			if (IsSearched == false)
			{
				m_pIServerUserInfoDataSink->OnDelAllUserData();
				IsSearched = true;
			}
			
			m_pIServerUserInfoDataSink->OnSetKindID(it->second->m_tagUMUserScoreSet.dwKindID);
			m_pIServerUserInfoDataSink->OnSetServerID(it->second->m_tagUMUserScoreSet.dwServerID);
			m_pIServerUserInfoDataSink->OnGameUserInfoInsert(it->second);
		}
	}

	if (IsSearched == false)
	{
		return FALSE;
	}else
		return TRUE;
}

void CUserServerInfo::SetServerUserInfoDataSink(IServerUserInfoDataSink * pIServerUserInfoDataSink)
{
	m_pIServerUserInfoDataSink = pIServerUserInfoDataSink;
}

void CUserServerInfo::OnUpdateUserRemarks(DWORD UserID,CString Remarks)
{
	m_pIServerUserInfoDataSink->OnSetUserRemarks(UserID,Remarks);
}

void CUserServerInfo::OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScoer,int Type)
{
	m_pIServerUserInfoDataSink->OnSetUserScoreInfo(UserID,WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScoer,Type);
}

//清空map，list
bool CUserServerInfo::OnDeleteAllUserInfo()
{
	m_UserInfoMap.clear();
	m_pIServerUserInfoDataSink->OnRedraw(FALSE);
	m_pIServerUserInfoDataSink->OnDelAllUserData();
	m_pIServerUserInfoDataSink->OnRedraw(TRUE);

	return true;
}


//排序
void CUserServerInfo::OnUserInfoSort()
{
//	tUserVector.clear();
	vector <pair<DWORD,CUserInfoItem*>>().swap(tUserVector);

	OnMapSort(m_UserInfoMap,tUserVector);
}

//升序
bool cmpSortAscending(const pair<DWORD,CUserInfoItem*>& x,const pair<DWORD,CUserInfoItem*>& y)
{
	return x.second->m_tagUMUserScoreSet.lMaxWin1 > y.second->m_tagUMUserScoreSet.lMaxWin1;
}

//降序
bool cmpSortDescending(const pair<DWORD,CUserInfoItem*>& x,const pair<DWORD,CUserInfoItem*>& y)
{
	return x.second->m_tagUMUserScoreSet.lMaxWin1 > y.second->m_tagUMUserScoreSet.lMaxWin1;
}

//Map排序
void CUserServerInfo::OnMapSort(map<DWORD,CUserInfoItem*>& tMap,vector<pair<DWORD,CUserInfoItem*>>& tVector)
{
	for (map<DWORD,CUserInfoItem*>::iterator it=tMap.begin();it!=tMap.end();it++)
	{
		tVector.push_back(make_pair(it->first,it->second));
	}

	sort(tVector.begin(),tVector.end(),cmpSortAscending);
}

bool CUserServerInfo::OnInsertOffLineUser(tagUMUserScoreSet* pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	CUserInfoItem* pCUserInfoItem = NULL;
	CUserInfoMap::iterator it = m_UserOffLineMap.find(pUserInfo->dwUserID);

	if (it == m_UserOffLineMap.end())
	{
		pCUserInfoItem = new CUserInfoItem;
		if (pCUserInfoItem==NULL) return false;
		m_UserOffLineMap.insert(std::make_pair(pUserInfo->dwUserID,pCUserInfoItem));
	}

	return true;
}

bool CUserServerInfo::OnSerachUser(CString userID)
{
	DWORD userid = _ttoi(userID);
	CUserInfoMap::iterator it = m_UserInfoMap.find(userid);

	if (it == m_UserInfoMap.end())
	{
		return false;
	}else
	{
		m_pIServerUserInfoDataSink->ShowUserInfo(&it->second->m_tagUMUserScoreSet);
	}
	

	return true;
}

tagUMUserScoreSet CUserServerInfo::OnSerachUserInfo(CString GameID)
{
	tagUMUserScoreSet lUserScoreSet;
	ZeroMemory(&lUserScoreSet,sizeof(tagUMUserScoreSet));

	DWORD nGameID = _ttoi(GameID);
	CUserInfoMap::iterator it = m_UserInfoMap.begin();

	for (it;it!=m_UserInfoMap.end();++it)
	{
		if (it->second->m_tagUMUserScoreSet.dwGameID == nGameID)
		{
			//CopyMemory(&UMUserScoreSet,&it->second->m_tagUMUserScoreSet,sizeof(tagUMUserScoreSet));
			//UMUserScoreSet = it->second->m_tagUMUserScoreSet;
			return it->second->m_tagUMUserScoreSet;
		}
	}

	return lUserScoreSet;

//	DWORD userid = _ttoi(GameID);
// 	CUserInfoMap::iterator it = m_UserInfoMap.find(GameID);
// 
// 	if (it == m_UserInfoMap.end())
// 	{
// 		return false;
// 	}else
// 	{
// 		CopyMemory(&UMUserScoreSet,&it->second->m_tagUMUserScoreSet,sizeof(tagUMUserScoreSet));
// 	}

	//return NULL;
}