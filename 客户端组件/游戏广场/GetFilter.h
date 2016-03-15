// GetFilter.h: interface for the CGetFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETFILTER_H__5997A175_E410_4F26_BD4A_D8FF141778EC__INCLUDED_)
#define AFX_GETFILTER_H__5997A175_E410_4F26_BD4A_D8FF141778EC__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlobalUnits.h"
class CGetFilter   
{
public:
	CGetFilter();
	virtual ~CGetFilter();
	void  StartTread(CWnd* pParentWnd);    //启动线程
	
	int static InternetGetFile (CString szUrl,CString szFileName); //网络下载文件
	BOOL static CreateFolder(LPCTSTR szFolder);
	BOOL static CreateFilePath(LPCTSTR szFilePath);
	UINT static CreThread(LPVOID Ppream);

//public:
	 CWnd * m_pParentWnd;
	static CStringArray m_sZipUrl;
	static CStringArray m_sZipFile;
	static int          m_nZipCount;
	static bool         m_bZipFilter;

	void static AddZipCommand(CString sUrl, CString sFile, bool isFilter);
	void static ClearZipCommand();
	
};

#endif // !defined(AFX_GETFILTER_H__5997A175_E410_4F26_BD4A_D8FF141778EC__INCLUDED_)