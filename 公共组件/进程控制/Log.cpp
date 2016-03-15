// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLogs theLog;

CLogs::CLogs()
{	
	m_bOpen = false;
}

CLogs::~CLogs()
{
	m_file.Abort();
}

void CLogs::Write(BYTE *pData, int nLen)
{
	ASSERT(pData != NULL);

	if (m_file.m_hFile == NULL || pData == NULL)
		return ;
	try
	{
		m_file.Write(pData, nLen);
	}
	catch(CFileException ex)
	{
		char aa[100] = {0};
		ex.GetErrorMessage(aa, 99);
		//AfxMessageBox(aa);
	}
}

bool CLogs::Init(LPCTSTR sFileName)
{
	m_nType = 0;
	if (!m_file.Open(sFileName, CFile::modeWrite | CFile::shareDenyNone))
	{
		if (m_file.Open(sFileName, CFile::modeCreate | CFile::modeWrite))
		{
			m_file.Close();
			m_file.Open(sFileName, CFile::modeWrite | CFile::shareDenyNone);
	        m_bOpen = true;
			m_nType = 1;
		}
		else
		{
			m_bOpen = false;
			m_nType = 0;
		}		
	}
	else
	{		
	    m_bOpen = true;
		m_file.SeekToEnd();
		if( m_file.GetLength() == 0 )
		{
			m_nType = 3;
		}
		else
			m_nType = 2;
	}
	return m_bOpen;
}

void CLogs::Write(LPCTSTR sData)
{
	if (!m_bOpen)
		return;
	CTime time = CTime::GetCurrentTime();
	CString sCurrentTime = time.Format("%Y-%m-%d %H:%M:%S	");
	m_crtFile.Lock();
	Write((BYTE *)(LPCTSTR)sCurrentTime, sCurrentTime.GetLength());
	Write((BYTE *)sData, strlen(sData));
	Write((BYTE *)"\r\n", strlen("\r\n"));
	m_crtFile.Unlock();
}

void CLogs::WriteData(LPCTSTR szData)
{
	m_crtFile.Lock();
	theLog.Write(szData);
}

void CLogs::WriteMsg(LPCTSTR sData)
{
	if (!m_bOpen)
		return;
	m_crtFile.Lock();
	Write((BYTE *)sData, strlen(sData));
	Write((BYTE *)"\r\n", strlen("\r\n"));	
	m_crtFile.Unlock();
}

void CLogs::ClearFile(LPCTSTR sFileName)
{
	m_crtFile.Lock();
	m_file.SetLength(0);
	m_crtFile.Unlock();
}

void CLogs::CloseFile(LPCTSTR sFileName)
{
	m_crtFile.Lock();
	m_file.Close();
	m_bOpen = false;
	m_crtFile.Unlock();
}
