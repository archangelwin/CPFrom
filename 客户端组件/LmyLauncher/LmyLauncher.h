
// LmyLauncher.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "LmyLauncherDlg.h"

#define	UPDATE_INFO_FILE	 "LobbyDate\\Update.INI"
// CLmyLauncherApp:
// �йش����ʵ�֣������ LmyLauncher.cpp
//

class CLmyLauncherApp : public CWinAppEx
{
public:
	CLmyLauncherApp();

public:
	CString m_sLocalPathStart;
	UINT  m_nPlatVer;
	//CLmyLauncherDlg *m_pMainDlg;
	INT KillProcess(LPCSTR pszClassName, LPCSTR pszWindowTitle);

// ��д
	public:
	virtual BOOL InitInstance();
	//�˳�����
	virtual INT ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLmyLauncherApp theApp;