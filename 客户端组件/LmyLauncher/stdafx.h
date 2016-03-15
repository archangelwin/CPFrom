
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

//MFC �ļ�
#include <GdiPlus.h>
#include <AtlImage.h>

//�����ռ�
using namespace Gdiplus;


// Vector֧��
#include <afxtempl.h>
#include <vector>
//#include <string>

//���������ļ�Ҫ�õ�inetͷ�ļ�
#include "afxinet.h"   

#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
//ɾ��ָ��
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 
//�ӿ��ͷ�
#define SafeRelease(pObject) { if (pObject!=NULL) { pObject->Release(); pObject=NULL; } }

typedef struct _TDownFile
{
	CString sFileName;
	CString sFileVersion;
	UINT    nLength;
	CString sInstallDir;	
	FILETIME m_fileTime;		// �ļ�����
	CString sUrl;
	bool    bRegister;
	bool    bZipFile;
	bool    bForceOverWrite;
	bool    bExecute;
}STDownFile;


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

//��ý���
#pragma comment (lib,"Winmm.lib")
#pragma comment(linker,"/NODEFAULTLIB:libc.lib")

#ifndef _DEBUG
#pragma comment (lib,"../../lib/ZipFunc.lib")
#else
#pragma comment (lib,"../../lib/ZipFunc_D.lib")
#endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


