// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__7C1A903F_165D_4B73_A347_8B598F7CD57D__INCLUDED_)
#define AFX_LOG_H__7C1A903F_165D_4B73_A347_8B598F7CD57D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxmt.h>
#include "ServiceCoreHead.h"
class SERVICE_CORE_CLASS CLog  
{
public:
	void WriteData(LPCTSTR szData);
	void Write(LPCTSTR sData);	
	void WriteMsg(LPCTSTR sData);
	bool Init(LPCTSTR sFileName);
	void Write(BYTE *pData, int nLen);
	void CloseFile(LPCTSTR sFileName); //�ر��ļ�
	void ClearFile(LPCTSTR sFileName); //����ļ�
	
	CLog();
	virtual ~CLog();
	bool   m_bOpen;
	int m_nType;//0ʧ�� 1 ���� 2�� 3�ļ�Ϊ�� 
	
protected:
private:
	CFile  m_file;
	CCriticalSection m_crtFile;
};

#endif // !defined(AFX_LOG_H__7C1A903F_165D_4B73_A347_8B598F7CD57D__INCLUDED_)
