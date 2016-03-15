#pragma once
#include "AdminControlSQL.h"

struct stgUserRemarks
{
	DWORD     UserID;
	CString   Remarks;
};

class CUserRemarks
{
public:
	CUserRemarks(void);
	virtual ~CUserRemarks(void);

public:
	stgUserRemarks   m_stgUserRemarks;

	static CUserRemarks* m_pUserRemarks;

protected:
	CAdminControlSQL     m_AdminControlSQL;

public:
	bool CreatrUserRemarksTable();
	
	bool DropUserRemarksTable();

	bool InsertUserRemarksInfo(DWORD UserID,CString Remarks);

	bool UpdateUserInfo(DWORD UserID,CString Remarks);

	bool DeleteUserRemarksInfo(DWORD UserID);

	CString SelectUserRemarks(DWORD UserID);

	DWORD SelectUser(DWORD UserID);

public:
	static CUserRemarks* GetInstance()
	{
		if (m_pUserRemarks == NULL)
		{
			m_pUserRemarks = new CUserRemarks;
		}
		return m_pUserRemarks; 
	}
};
