#include "StdAfx.h"
#include "GameInfo.h"

GameInfo::GameInfo(void)
{
	m_row = 0;
	m_column = 0;
}

GameInfo::~GameInfo(void)
{
	for (int i=0;i<m_UserInfo.GetCount();i++)
	{
		if (m_UserInfo[i]!=NULL)
		{
			SafeDelete(m_UserInfo[i]);
		}
	}
	for (int i=0;i<m_GameInfo.GetCount();i++)
	{
		if (m_GameInfo[i]!=NULL)
		{
			SafeDelete(m_GameInfo[i]);
		}
	}

}

bool GameInfo::CreateUserInfoTable()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString createtable = "CREATE TABLE IF NOT EXISTS [GameUserInfo]([UserID] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,[PASSWORD] TEXT(500),[GameID] INT,[PORT] INT)";
	if (m_GameSQL.ExcuteQuery(createtable)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"创建表失败",NULL,MB_OK);

	m_GameSQL.CloseDatabase();
	
	return false;
}

bool GameInfo::CreateGameInfoTable()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString createtable = "CREATE TABLE IF NOT EXISTS [GameInfo]([PORT] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,[GameID] INT,[Version] INT,[GameName] TEXT(500))";
	if (m_GameSQL.ExcuteQuery(createtable)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"创建表失败",NULL,MB_OK);

	m_GameSQL.CloseDatabase();

	return false;
}

bool GameInfo::CreateHideUserTable()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString createtable = "CREATE TABLE IF NOT EXISTS [GameHideUser]([UserID] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,[NICKNAME] TEXT(500))";
	if (m_GameSQL.ExcuteQuery(createtable)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"创建表失败",NULL,MB_OK);

	m_GameSQL.CloseDatabase();

	return false;
}

bool GameInfo::DropUserInfoTalbe()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString droptable = "drop table GameUserInfo";
	if (m_GameSQL.ExcuteQuery(droptable) == true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::DropGameInfoTable()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString droptable = "drop table GameInfo";
	if (m_GameSQL.ExcuteQuery(droptable) == true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::InsertUserInfo(INT UserID,CString PassWord,INT GameID,INT Port)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("INSERT INTO GameUserInfo(UserID,PASSWORD,GameID,PORT) VALUES('%d','%s','%d','%d')",
				UserID,PassWord,GameID,Port);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::InsertGameInfo(INT GameID,INT Port,INT Version,CString GameName)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("INSERT INTO GameInfo(PORT,GameID,Version,GameName) VALUES('%d','%d','%d','%s')",
		Port,GameID,Version,GameName);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::InsertHideUser(INT userID,CString NickName)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;

	szSQL.Format("INSERT INTO GameHideUser(UserID,NICKNAME) VALUES('%d','%s')",
		userID,NickName);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::UpdataUserInfo(INT UserID,CString PassWord,INT GameID,INT Port)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("update GameUserInfo set PASSWORD = '%s',GameID = %d,PORT = %d where UserID = %d",
		PassWord,GameID,Port,UserID);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"未查找到该数据,更新失败!",NULL,MB_OK);

	m_GameSQL.CloseDatabase();
	return false;

}

bool GameInfo::UpdateGameInfo(INT GameID,INT Port,INT Version,CString GameName)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("update GameInfo set GameID = %d,Version = %d,GameName = '%s' where PORT = %d",
		GameID,Version,GameName,Port);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"未查找到该数据,更新失败!",NULL,MB_OK);

	m_GameSQL.CloseDatabase();
	return false;

}

bool GameInfo::UpdateHideUser(INT userID,CString NickName)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("update GameHideUser set NICKNAME = %s where UserID = %d",
		NickName,userID);

	if (m_GameSQL.ExcuteQuery(szSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"未查找到该数据,更新失败!",NULL,MB_OK);

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::DeleteUserInfo(INT UserID)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szDelSQL;
	szDelSQL.Format("delete from GameUserInfo where UserID = %d",UserID);
	if (m_GameSQL.ExcuteQuery(szDelSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::DeleteGameInfo(INT Port)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szDelSQL;
	szDelSQL.Format("delete from GameInfo where PORT = %d",Port);
	if (m_GameSQL.ExcuteQuery(szDelSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::DeleteHideUser(INT userID)
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szDelSQL;
	szDelSQL.Format("delete from GameHideUser where UserID = %d",userID);
	if (m_GameSQL.ExcuteQuery(szDelSQL)==true)
	{
		m_GameSQL.CloseDatabase();
		return true;
	}

	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::SelectUserInfo()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	m_UserInfo.RemoveAll();
	for (int i=0;i<m_UserInfo.GetCount();i++)
	{
		if (m_UserInfo[i]!=NULL)
		{
			SafeDelete(m_UserInfo[i]);
		}
	}


	CString szSQL;
	szSQL.Format("select * from GameUserInfo");
//	char** autoResult = NULL;
	sqlite3_stmt *statement;

//	int result = sqlite3_get_table(m_GameSQL.m_pDB, szSQL, &autoResult, &m_row,&m_column, &m_GameSQL.zErrMsg );

	if(sqlite3_prepare_v2(m_GameSQL.m_pDB, szSQL, -1, &statement, NULL) == SQLITE_OK)
	{
		while(sqlite3_step(statement) == SQLITE_ROW)
		{
			tgUserInfo* pUserInfo = new tgUserInfo;
			pUserInfo->UserID = (CString)sqlite3_column_text(statement,0);
			pUserInfo->PassWord = (CString)sqlite3_column_text(statement,1);
			pUserInfo->GameID = (CString)sqlite3_column_text(statement,2);
			pUserInfo->Port = (CString)sqlite3_column_text(statement,3);
			m_UserInfo.Add(pUserInfo);
		}

//		delete[] autoResult;
		sqlite3_finalize(statement);
		m_GameSQL.CloseDatabase();
		return true;
	}

//	delete[] autoResult;
	sqlite3_finalize(statement);
	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::SelectGameInfo()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}
	
	
	for (int i=0;i<m_GameInfo.GetCount();i++)
	{
		if (m_GameInfo[i]!=NULL)
		{
			SafeDelete(m_GameInfo[i]);
		}
	}
	m_GameInfo.RemoveAll();


	CString szSQL;
	szSQL.Format("select * from GameInfo");
//	char** autoResult = NULL;
	sqlite3_stmt *statement;

	if(sqlite3_prepare_v2(m_GameSQL.m_pDB, szSQL, -1, &statement, NULL) == SQLITE_OK)
	{
		while(sqlite3_step(statement) == SQLITE_ROW)
		{
			tgGameInfo* pGameInfo = new tgGameInfo;
			pGameInfo->Port = (CString)sqlite3_column_text(statement,0);
			pGameInfo->GameID = (CString)sqlite3_column_text(statement,1);
			pGameInfo->Version = (CString)sqlite3_column_text(statement,2);
			pGameInfo->GameName = (CString)sqlite3_column_text(statement,3);
			m_GameInfo.Add(pGameInfo);
		}
		//		delete[] autoResult;
		sqlite3_finalize(statement);
		m_GameSQL.CloseDatabase();
		return true;
	}

	//	delete[] autoResult;
	sqlite3_finalize(statement);
	m_GameSQL.CloseDatabase();
	return false;
}

bool GameInfo::SeleteHideUser()
{
	if (m_GameSQL.m_open == false)
	{
		if (m_GameSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	m_HideUser.RemoveAll();
	for (int i=0;i<m_HideUser.GetCount();i++)
	{
		if (m_HideUser[i]!=NULL)
		{
			SafeDelete(m_HideUser[i]);
		}
	}

	CString szSQL;
	szSQL.Format("select * from GameHideUser");
	//	char** autoResult = NULL;
	sqlite3_stmt *statement;


	if(sqlite3_prepare_v2(m_GameSQL.m_pDB, szSQL, -1, &statement, NULL) == SQLITE_OK)
	{
		while(sqlite3_step(statement) == SQLITE_ROW)
		{
			tgHideUser* pHideUser = new tgHideUser;
			pHideUser->UserID = (CString)sqlite3_column_text(statement,0);
			pHideUser->NickName = (CString)sqlite3_column_text(statement,1);
			m_HideUser.Add(pHideUser);
		}
		//		delete[] autoResult;
		sqlite3_finalize(statement);
		m_GameSQL.CloseDatabase();
		return true;
	}

	//	delete[] autoResult;
	sqlite3_finalize(statement);
	m_GameSQL.CloseDatabase();
	return false;
}