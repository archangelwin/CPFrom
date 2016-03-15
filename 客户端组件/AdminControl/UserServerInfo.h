#pragma once
#include "Stdafx.h"
#include "UserManagerHead.h"
#include <map>
#include "ServerListData.h"
//#include "UserInfoList.h"

class CUserInfoItem;

typedef std::map<DWORD, CUserInfoItem *> CUserInfoMap;

//�б�ӿ�
interface IServerUserInfoDataSink
{
	//״̬֪ͨ
public:
	//���֪ͨ
	virtual VOID OnGameUserInfoFinish()=NULL;
	//���֪ͨ
//	virtual VOID OnGameKindFinish(WORD wKindID)=NULL;
	//����֪ͨ
	virtual VOID OnGameUserInfoUpdateFinish()=NULL;

	//����֪ͨ
public:
	//����֪ͨ
	virtual VOID OnGameUserInfoInsert(CUserInfoItem * pGameUserInfoItem)=NULL;
	//����֪ͨ
	virtual VOID OnGameUserInfoUpdate(CUserInfoItem * pGameUserInfoItem)=NULL;
	//ɾ��֪ͨ
	virtual VOID OnGameUserInfoDelete(CUserInfoItem * pGameUserInfoItem)=NULL;

	//ɾ�������û���Ϣ
	virtual VOID OnDelAllUserData()=NULL;
	//����UserID
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
	tagUMUserScoreSet m_tagUMUserScoreSet;  //�û���Ϣ

	CString	szServerName;			//��������

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
	CString m_szGameName;          //��������
	bool m_IsSearch;
//	CUserInfoList m_UserInfoList;
	
public:
	//�����û�
	bool OnInsertUserInfo(tagUMUserScoreSet* pUserInfo);
	//ɾ���û�
	bool OnDeleteUserInfo(tagUMUserScoreSet* pUserInfo);
	//�����û�
	bool OnUpdataGameUserInfo(CGameServerItem * pGameServerItem);
	//�����û�
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
	
	//��̬����
public:
	IServerUserInfoDataSink*        m_pIServerUserInfoDataSink;         //
protected:
	static CUserServerInfo *		m_pCUserServerInfo;					//�б�����

public:
	DWORD                           m_dwAllOnLineCount;                 //����������


	//���ú���
public:
	//���ýӿ�
	VOID SetServerUserInfoDataSink(IServerUserInfoDataSink * pIServerUserInfoDataSink);

	//״̬֪ͨ
public:
	//���֪ͨ
	VOID OnGameUserInfoFinish();
	//���֪ͨ
	//	virtual VOID OnGameKindFinish(WORD wKindID)=NULL;
	//����֪ͨ
	//VOID OnGameUserInfoUpdateFinish();

	void OnUpdateUserRemarks(DWORD UserID,CString Remarks);

	void OnSetUserScoreInfo(DWORD UserID,CString WinMax,CString LoseMax,CString NotifyWin,CString NotifyLose,CString lRate,CString WinLoseScore,int Type);
public:
	//��ȡ����
	static CUserServerInfo * GetInstance()
	{ 
		if (m_pCUserServerInfo == NULL)
		{
			m_pCUserServerInfo = new CUserServerInfo;
		}
		return m_pCUserServerInfo;
	}
};
