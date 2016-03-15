#pragma once
#include "GameSQLite.h"

struct  tgUserInfo
{
	CString UserID;
	CString PassWord;
	CString GameID;
	CString Port;
};

struct tgGameInfo
{
	CString GameID;
	CString Port;
	CString Version;
	CString GameName;
};

struct tgHideUser
{
	CString UserID;
	CString NickName;
};

typedef CWHArray<tgUserInfo*> CUserInfo;
typedef CWHArray<tgGameInfo*> CGameInfo;
typedef CWHArray<tgHideUser*> CHideUser;

class GameInfo
{
public:
	GameInfo(void);
	~GameInfo(void);

public:

	GameSQLite m_GameSQL;

	//查询到的行
	int m_row;
	//查询到的列
	int m_column;

	CUserInfo    m_UserInfo;
	CGameInfo    m_GameInfo;
	CHideUser    m_HideUser;

public:

	bool CreateUserInfoTable();

	bool DropUserInfoTalbe();

	bool InsertUserInfo(INT UserID,CString PassWord,INT GameID,INT Port);

	bool UpdataUserInfo(INT UserID,CString PassWord,INT GameID,INT Port);

	bool DeleteUserInfo(INT UserID);

	bool SelectUserInfo();

public:
	bool CreateGameInfoTable();
	
	bool DropGameInfoTable();

	bool InsertGameInfo(INT GameID,INT Port,INT Version,CString GameName);

	bool UpdateGameInfo(INT GameID,INT Port,INT Version,CString GameName);

	bool DeleteGameInfo(INT Port);

	bool SelectGameInfo();

public:
	bool CreateHideUserTable();

	bool InsertHideUser(INT userID,CString NickName);

	bool UpdateHideUser(INT userID,CString NickName);

	bool DeleteHideUser(INT userID);

	bool SeleteHideUser();


};
