#pragma once
#include "Stdafx.h"
class CAdminControlSQL
{
public:
	CAdminControlSQL(void);
	virtual ~CAdminControlSQL(void);

public:
	//���ݿ����
	sqlite3 *m_pDB;
	//���ݿ��Ƿ��
	bool m_open;
	//������Ϣ
	char* zErrMsg;

public:
	//�������ݿ�
	bool ConnectDatabase();
	//�ر����ݿ�
	bool CloseDatabase();
	//ִ��SQL���
	bool ExcuteQuery(const CString &command);
	//����ʼ
	int AffairsBegin();
	//�����ύ
	int AffairsCommit();
	//����ع�
	int AffairsRollBack();

protected:

	CString GetSQLModuleDir(); 

	static void GB2312ToUTF_8(CString& pOut,char *pText, int pLen);

	static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);

	static void UnicodeToUTF_8(char* pOut,wchar_t* pText);
};
