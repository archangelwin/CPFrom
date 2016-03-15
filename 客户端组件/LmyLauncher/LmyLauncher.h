
// LmyLauncher.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
//#include "LmyLauncherDlg.h"

#define	UPDATE_INFO_FILE	 "LobbyDate\\Update.INI"
// CLmyLauncherApp:
// 有关此类的实现，请参阅 LmyLauncher.cpp
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

// 重写
	public:
	virtual BOOL InitInstance();
	//退出函数
	virtual INT ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CLmyLauncherApp theApp;