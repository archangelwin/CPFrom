#include "StdAfx.h"
#include "AdminControlSQL.h"

CAdminControlSQL::CAdminControlSQL(void)
{
	m_pDB = NULL;
	zErrMsg = NULL;
	m_open = false;
}

CAdminControlSQL::~CAdminControlSQL(void)
{
}

CString CAdminControlSQL::GetSQLModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 

	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath.Left( nPos ); 
}

void CAdminControlSQL::GB2312ToUTF_8(CString& pOut,char *pText, int pLen)
{
	char buf[4];
	int nLength = pLen* 3;
	char* rst = new char[nLength];

	memset(buf,0,4);
	memset(rst,0,nLength);

	int i = 0;
	int j = 0;      
	while(i < pLen)
	{
		//如果是英文直接复制就可以
		if( *(pText + i) >= 0)
		{
			rst[j++] = pText[i++];
		}
		else
		{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);

			UnicodeToUTF_8(buf,&pbuffer);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];    

			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';

	//返回结果
	pOut = rst;             
	delete []rst;   

	return;
}
void CAdminControlSQL::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)
{
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
}

void CAdminControlSQL::UnicodeToUTF_8(char* pOut,wchar_t* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}


bool CAdminControlSQL::ConnectDatabase()
{
	CString appPath = GetSQLModuleDir();
	appPath += "\\UMDatabase.db";
	CString  strAppPath;

	GB2312ToUTF_8(strAppPath,(LPSTR)(LPCTSTR)appPath,appPath.GetLength());
	int rc = sqlite3_open(_T(strAppPath),&m_pDB);
	if (rc != SQLITE_OK)
	{
		MessageBox(NULL,"连接数据库失败",NULL,MB_OK);
		return false;
	}else
	{
		m_open = true;
		return true;
	}
}


bool CAdminControlSQL::CloseDatabase()
{
	if (!m_open)
	{
		sqlite3_close(m_pDB);
		m_open = false;
	}
	return false;
}

bool CAdminControlSQL::ExcuteQuery(const CString &command)
{
	if (m_open == false)
	{
		ConnectDatabase();
	}
	int rc = sqlite3_exec(m_pDB,command,NULL,NULL,&zErrMsg);
	if (rc != SQLITE_OK)
	{
		//		CErrorLog::DebugLog(L"语句执行失败");
		return false;
	}

	return true;
}

int CAdminControlSQL::AffairsBegin()
{
	return sqlite3_exec(m_pDB,"begin transaction",NULL,NULL,&zErrMsg);
}


int CAdminControlSQL::AffairsCommit()
{
	return sqlite3_exec(m_pDB,"commit transaction",NULL,NULL,&zErrMsg);
}

int CAdminControlSQL::AffairsRollBack()
{
	return sqlite3_exec(m_pDB,"rollback transaction",NULL,NULL,&zErrMsg);
}