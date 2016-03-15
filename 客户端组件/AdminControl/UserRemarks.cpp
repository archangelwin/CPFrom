#include "StdAfx.h"
#include "UserRemarks.h"


CUserRemarks * CUserRemarks::m_pUserRemarks=NULL;						//对象指针

CUserRemarks::CUserRemarks(void)
{
}

CUserRemarks::~CUserRemarks(void)
{
}


bool CUserRemarks::CreatrUserRemarksTable()
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString createtable = "CREATE TABLE IF NOT EXISTS [UserRemarks]([UserID] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,[Remarks] TEXT(500))";
	if (m_AdminControlSQL.ExcuteQuery(createtable)==true)
	{
		m_AdminControlSQL.CloseDatabase();
		return true;
	}
// 	else
// 		MessageBox(NULL,"创建表失败",NULL,MB_OK);

	m_AdminControlSQL.CloseDatabase();

	return false;
}

bool CUserRemarks::DropUserRemarksTable()
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString droptable = "drop table UserRemarks";
	if (m_AdminControlSQL.ExcuteQuery(droptable) == true)
	{
		m_AdminControlSQL.CloseDatabase();
		return true;
	}

	m_AdminControlSQL.CloseDatabase();
	return false;
}

bool CUserRemarks::InsertUserRemarksInfo(DWORD UserID,CString Remarks)
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("INSERT INTO UserRemarks(UserID,Remarks) VALUES('%ld','%s')",
		UserID,Remarks);

	if (m_AdminControlSQL.ExcuteQuery(szSQL)==true)
	{
		m_AdminControlSQL.CloseDatabase();
		return true;
	}

	m_AdminControlSQL.CloseDatabase();
	return false;
}

bool CUserRemarks::UpdateUserInfo(DWORD UserID,CString Remarks)
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	szSQL.Format("update UserRemarks set Remarks = '%s' where UserID = %ld",
		Remarks,UserID);

	if (m_AdminControlSQL.ExcuteQuery(szSQL)==true)
	{
		m_AdminControlSQL.CloseDatabase();
		return true;
	}else
		MessageBox(NULL,"未查找到该数据,更新失败!",NULL,MB_OK);

	m_AdminControlSQL.CloseDatabase();
	return false;
}

bool CUserRemarks::DeleteUserRemarksInfo(DWORD UserID)
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szDelSQL;
	szDelSQL.Format("delete from UserRemarks where UserID = %ld",UserID);
	if (m_AdminControlSQL.ExcuteQuery(szDelSQL)==true)
	{
		m_AdminControlSQL.CloseDatabase();
		return true;
	}

	m_AdminControlSQL.CloseDatabase();
	return false;
}

CString CUserRemarks::SelectUserRemarks(DWORD UserID)
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	CString szResultRemark = "";
	szSQL.Format("select * from UserRemarks where UserID = %ld",UserID);

	sqlite3_stmt *statement;

	if(sqlite3_prepare_v2(m_AdminControlSQL.m_pDB, szSQL, -1, &statement, NULL) == SQLITE_OK)
	{
		while(sqlite3_step(statement) == SQLITE_ROW)
		{
			//m_stgUserRemarks.UserID = (DWORD)sqlite3_column_text(statement,0);
			szResultRemark = (CString)sqlite3_column_text(statement,1);
		}

		sqlite3_finalize(statement);
		m_AdminControlSQL.CloseDatabase();
		return szResultRemark;
	}

	sqlite3_finalize(statement);
	m_AdminControlSQL.CloseDatabase();
	return "";

}

DWORD CUserRemarks::SelectUser(DWORD UserID)
{
	if (m_AdminControlSQL.m_open == false)
	{
		if (m_AdminControlSQL.ConnectDatabase()==false)
		{
			return false;
		}
	}

	CString szSQL;
	DWORD szResultUser = 0;
	szSQL.Format("select * from UserRemarks");

	sqlite3_stmt *statement;

	if(sqlite3_prepare_v2(m_AdminControlSQL.m_pDB, szSQL, -1, &statement, NULL) == SQLITE_OK)
	{
		while(sqlite3_step(statement) == SQLITE_ROW)
		{
			//m_stgUserRemarks.UserID = (DWORD)sqlite3_column_text(statement,0);
			szResultUser = _ttoi((CString)sqlite3_column_text(statement,0));
			if (UserID == szResultUser)
			{
				sqlite3_finalize(statement);
				m_AdminControlSQL.CloseDatabase();
				return szResultUser;
			}else
				continue;
		}

// 		sqlite3_finalize(statement);
// 		m_AdminControlSQL.CloseDatabase();
// 		return 0;
	}

	sqlite3_finalize(statement);
	m_AdminControlSQL.CloseDatabase();
	return 0;
}