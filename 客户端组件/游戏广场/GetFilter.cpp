// GetFilter.cpp: implementation of the CGetFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "hall.h"
#include "GetFilter.h"
#include "Wininet.h"
#include "UnzipFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGetFilter::CGetFilter()
{	
	ClearZipCommand();
}

CGetFilter::~CGetFilter()
{
	
}

void CGetFilter::StartTread(CWnd* pParentWnd)
{
	AfxBeginThread((AFX_THREADPROC)CreThread,pParentWnd);
}


UINT CGetFilter::CreThread(LPVOID Ppream)
{
	CWnd * pParentWnd  = (CWnd *)Ppream;
	
	if(CGetFilter::m_nZipCount > 0)
	{
		for(int i = 0; i < CGetFilter::m_nZipCount; i++)
		{
			CString ps = CGetFilter::m_sZipUrl.GetAt(i);
			CGetFilter::InternetGetFile(CGetFilter::m_sZipUrl.GetAt(i), CGetFilter::m_sZipFile.GetAt(i));
		}
		if(CGetFilter::m_bZipFilter)
		{
			::PostMessage(pParentWnd->GetSafeHwnd(),WM_UPDATE_RESOUCE,0,0);
			//m_pConfigInfo->InitArrayFitler();
		}
		CGetFilter::ClearZipCommand();
	}
	return 0;
}

void CGetFilter::AddZipCommand(CString sUrl, CString sFile, bool isFilter)
{
	CGetFilter::m_sZipUrl.Add(sUrl);
	CGetFilter::m_sZipFile.Add(sFile);
	CGetFilter::m_nZipCount++;
	if(isFilter) CGetFilter::m_bZipFilter = true;
}

void CGetFilter::ClearZipCommand()
{
	CGetFilter::m_sZipUrl.RemoveAll();
	CGetFilter::m_sZipFile.RemoveAll();
	CGetFilter::m_nZipCount = 0;
	CGetFilter::m_bZipFilter = false;
}

int CGetFilter::InternetGetFile (CString szUrl,CString szFileName)
{
	//网络下载文件
	CInternetSession	session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 13);
	session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT,5*1000);   
    session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,5*1000);   
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,5*1000);
    session.SetOption(INTERNET_OPTION_CONNECT_RETRIES,2);
	CHttpFile *pHttpFile = NULL;
	try
	{
		pHttpFile = (CHttpFile *)session.OpenURL(szUrl, 1, INTERNET_FLAG_RELOAD | INTERNET_FLAG_TRANSFER_ASCII);
	}
	catch(...)
	{
	
		if (pHttpFile != NULL)
			delete pHttpFile;
		session.Close();
		return -1;
	}

	CFile file;
	if  (file.Open(szFileName,CFile::modeCreate | CFile::modeWrite)==FALSE )
	{
		return -1;
	}
	try
	{
		byte tmp[1024]={0};
		int n=0;
		do 
		{
			n= pHttpFile->Read(tmp,sizeof(tmp));
			if (n>0)
			{
				file.Write(tmp,n);
			}
			
		} while(n>0);


	}
	catch(...)
	{
		file.Close();
		if (pHttpFile != NULL)
			delete pHttpFile;
		session.Close();
		return -1;
	}
		
    file.Close();
	pHttpFile->Close();
	delete pHttpFile;
	session.Close();
	
	//下载后解压文件
	
	try
	{
		const int BUF_SIZE = 128;
		CUnzipFile uf(szFileName);
		uf.GoToFirstFile();
		unz_file_info ui;
		TCHAR szDir[_MAX_DIR];
		TCHAR szDrive[_MAX_DRIVE];
		_tsplitpath(szFileName, szDrive, szDir,NULL, NULL);
		CString szPath = CString(szDrive) + szDir;
		do
		{
			uf.GetCurrentFileInfo(&ui);
			int iNameSize = ui.size_filename + 1;
			char* pName = new char [iNameSize];
			
			uf.GetCurrentFileInfo(NULL, pName, iNameSize);

			
			CString sName = pName;
			delete[]pName;
			
			/// sea add
			CString sFileName = szPath+sName;			
			char szFileName[MAX_PATH + 1];
			memset(szFileName,0,MAX_PATH + 1);
			memcpy(szFileName,sFileName,sFileName.GetLength());
			int nLen = lstrlen(szFileName);		
			while (nLen--)
			{
				if (szFileName[nLen] == '/')
					szFileName[nLen] = '\\';
			}
			BOOL bFolder = (szFileName[lstrlen(szFileName) - 1] == '\\');
			if(bFolder) // 文件夹
				continue;			
			if (!CreateFilePath(szFileName))   // 创建文件的完整目录
				return -1;
		/// sea end 

			CFile f( szPath + sName, CFile::modeWrite | CFile::modeCreate);
			
			uf.OpenCurrentFile();
			char buf[BUF_SIZE];
			
			int size_read;
			do
			{
				size_read = uf.ReadCurrentFile(buf, BUF_SIZE);
				if (size_read > 0)
					f.Write(buf, size_read);
			}
			while (size_read == BUF_SIZE);
			
			uf.UpdateFileStatus(f, ui);
	
		}
		while(uf.GoToNextFile());
		
		uf.Close();
	}
	catch (CException*)
	{
		return 0;
	}
	
	return 0;
}

BOOL CGetFilter::CreateFolder(LPCTSTR szFolder)
{
	if (!szFolder || !lstrlen(szFolder))
		return FALSE;
	
	DWORD dwAttrib = GetFileAttributes(szFolder);
	
	// already exists ?
	if (dwAttrib != 0xffffffff)
		return ((dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
	
	// recursively create from the top down
	char* szPath = _strdup(szFolder);
	char* p = strrchr(szPath, '\\');
	if (p) 
	{
		// The parent is a dir, not a drive
		*p = '\0';
		
		// if can't create parent
		if (!CreateFolder(szPath))
		{
			free(szPath);
			return FALSE;
		}
		free(szPath);
		
		if (!::CreateDirectory(szFolder, NULL)) 
			return FALSE;
	}
	
	return TRUE;
}

BOOL CGetFilter::CreateFilePath(LPCTSTR szFilePath)
{
	char* szPath = _strdup(szFilePath);    
	char* p = strrchr(szPath,'\\');       	
	BOOL bRes = FALSE;	
	if (p)
	{
		*p = '\0'; 		
		bRes = CreateFolder(szPath);
	}	
	free(szPath);	
	return bRes;
}
int  CGetFilter::m_nZipCount = 0;
bool CGetFilter::m_bZipFilter = false;
CStringArray CGetFilter::m_sZipUrl;
CStringArray CGetFilter::m_sZipFile;