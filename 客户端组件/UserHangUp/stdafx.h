
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0400
#endif

//#ifndef _WIN32_IE
//#define _WIN32_IE 0x0400
//#endif
#ifndef _WIN32_IE // Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0601 // Change this to the appropriate value to target IE 5.0 or later.
#endif


#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS


#define WM_PROGRESS_MESSAGE WM_USER+1
#define WM_PROGRESS_END		WM_USER+2
//////////////////////////////////////////////////////////////////////////////////

//MFC 文件
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>
#include <afxcontrolbars.h>
//MFC 文件
#include <Nb30.h>
#include <AfxInet.h>
#include <afxdtctl.h>
#include "Resource.h"
#include "sqlite3.h"
#include "CrashRpt.h"
#include "CrashRptProbe.h"
//#include "sqlite3ext.h"

//平台文件
#include "..\..\全局定义\Platform.h"

//网络命令
#include "..\..\消息定义\CMD_Commom.h"
#include "..\..\消息定义\CMD_GameServer.h"
#include "..\..\消息定义\CMD_LogonServer.h"

//进程命令
#include "..\..\消息定义\IPC_GameFrame.h"

#include "..\..\公共组件\服务核心\ServiceCoreHead.h"

#include "..\..\客户端组件\网络服务\NetworkHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../链接库/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../链接库/Ansi/BBSocket.lib")
#else
#pragma comment (lib,"../../链接库/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../链接库/Ansi/BBSocket.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../链接库/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../链接库/Ansi/BBSocketD.lib")
#else
#pragma comment (lib,"../../链接库/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../链接库/Ansi/BBSocketD.lib")
#endif
#endif

/*#include "vld.h"*/