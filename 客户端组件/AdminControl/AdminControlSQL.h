#pragma once
#include "Stdafx.h"
class CAdminControlSQL
{
public:
	CAdminControlSQL(void);
	virtual ~CAdminControlSQL(void);

public:
	//数据库对象
	sqlite3 *m_pDB;
	//数据库是否打开
	bool m_open;
	//错误信息
	char* zErrMsg;

public:
	//连接数据库
	bool ConnectDatabase();
	//关闭数据库
	bool CloseDatabase();
	//执行SQL语句
	bool ExcuteQuery(const CString &command);
	//事务开始
	int AffairsBegin();
	//事务提交
	int AffairsCommit();
	//事务回滚
	int AffairsRollBack();

protected:

	CString GetSQLModuleDir(); 

	static void GB2312ToUTF_8(CString& pOut,char *pText, int pLen);

	static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);

	static void UnicodeToUTF_8(char* pOut,wchar_t* pText);
};
