// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��

# pragma warning (disable:4819)
#pragma comment (lib,"strmiids.lib")
#pragma comment (lib,"dsound.lib")
#pragma comment (lib,"Winmm.lib")
#pragma comment (lib,"lib/STRMBASE.lib")

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCore.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCore.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"lib/STRMBASE.LIB")
// #pragma comment (lib,"winmm.lib")
// #pragma comment (lib,"quartz.lib")
// #pragma comment (lib,"uuid.lib")

//#pragma comment (lib,"C:\\Program Files\\Microsoft Visual Studio\\VC98\\Lib\\strmbase.lib")
//#pragma comment (lib,"strmbase.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCoreD.lib")
#endif
#endif

#endif // _AFX_NO_AFXCMN_SUPPORT


