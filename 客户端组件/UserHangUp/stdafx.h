
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

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

//MFC �ļ�
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>
#include <afxcontrolbars.h>
//MFC �ļ�
#include <Nb30.h>
#include <AfxInet.h>
#include <afxdtctl.h>
#include "Resource.h"
#include "sqlite3.h"
#include "CrashRpt.h"
#include "CrashRptProbe.h"
//#include "sqlite3ext.h"

//ƽ̨�ļ�
#include "..\..\ȫ�ֶ���\Platform.h"

//��������
#include "..\..\��Ϣ����\CMD_Commom.h"
#include "..\..\��Ϣ����\CMD_GameServer.h"
#include "..\..\��Ϣ����\CMD_LogonServer.h"

//��������
#include "..\..\��Ϣ����\IPC_GameFrame.h"

#include "..\..\�������\�������\ServiceCoreHead.h"

#include "..\..\�ͻ������\�������\NetworkHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/BBSocket.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/BBSocket.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/BBSocketD.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/BBSocketD.lib")
#endif
#endif

/*#include "vld.h"*/