
// UserHangUp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUserHangUpApp:
// �йش����ʵ�֣������ UserHangUp.cpp
//

class CUserHangUpApp : public CWinAppEx
{
public:
	CUserHangUpApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUserHangUpApp theApp;