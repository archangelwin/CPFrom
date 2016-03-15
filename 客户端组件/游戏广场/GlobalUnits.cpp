#include "StdAfx.h"
#include "Mmsystem.h"
#include "GlobalUnits.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////
//��̬����
#define	FILTER_STRING_FILE	 "\\LobbyDate\\filter.xml"
#define	FILTER_STRING_NAME	 "\\LobbyDate\\filter.zip"
CGlobalUnits * CGlobalUnits::m_pGlobalUnits=NULL;						//����ָ��

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGlobalUnits::CGlobalUnits()
{
	//���ñ���
	m_pDlgDownLoad=NULL;

	//�汾��Ϣ
	m_dwPlazaVersion=VERSION_PLAZA;
	m_dwFrameVersion=VERSION_FRAME;
	m_dwResouceVersion = 0;
	m_dwLockCoin = 1000000;

	m_szDirWork[0]=0;

	//���ö���
	ASSERT(m_pGlobalUnits==NULL);
	if (m_pGlobalUnits==NULL) m_pGlobalUnits=this;

	return;
}

//��������
CGlobalUnits::~CGlobalUnits()
{
	//�ͷŶ���
	ASSERT(m_pGlobalUnits==this);
	if (m_pGlobalUnits==this) m_pGlobalUnits=NULL;

	return;
}

bool CGlobalUnits::InitGlobalUnits()
{
	//���ù���Ŀ¼
	GetModuleFileName(AfxGetInstanceHandle(),m_szDirWork,sizeof(m_szDirWork));
	int nModuleLen=lstrlen(m_szDirWork);
	int nProcessLen=lstrlen(AfxGetApp()->m_pszExeName)+lstrlen(TEXT(".EXE"));
	m_szDirWork[nModuleLen-nProcessLen]=0;
	SetCurrentDirectory(m_szDirWork);
	m_sAppPath = m_szDirWork;
 
	//���ñ���
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();

	pGlobalServer->InitPlatInfo();
	m_dwResouceVersion = pGlobalServer->GetPlatInfo(TEXT("VerInfo"),TEXT("RVer"),0);
	m_dwLockCoin =  pGlobalServer->GetPlatInfo(TEXT("PlatInfo"),TEXT("LockCoin"),1000000);

	InitArrayFitler();
	return true;
}

//��¼���
bool CGlobalUnits::WriteUserCookie()
{
	//��������
	ASSERT(CParameterGlobal::GetInstance()!=NULL);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

	//��¼���
	if (pParameterGlobal->m_bWriteCookie==true)
	{
		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//�������
		TCHAR szUserID[32]=TEXT("");
		_sntprintf(szUserID,CountArray(szUserID),TEXT("%ld"),pGlobalUserData->dwUserID);

		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		//�û�����
		CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("UserID"),szUserID);
		CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("Accounts"),pGlobalUserData->szAccounts);
		CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("Password"),pGlobalUserData->szPassword);
	}

	return true;
}

//ɾ�����
bool CGlobalUnits::DeleteUserCookie()
{
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//ɾ����Ϣ
	CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("UserID"),TEXT(""));
	CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("Accounts"),TEXT(""));
	CInternetSession::SetCookie(pGlobalServer->GetPlatformServer(2),TEXT("Password"),TEXT(""));

	CString htmlpa;
	htmlpa  = "Logout.aspx";
	CString sContent;
//	sContent.Format("UserID=%s&Accounts=%s&Password=%s",szUserID,pGlobalUserData->szAccounts,pGlobalUserData->szPassword);
	CString csResponse;
	unsigned short nPort = pGlobalServer->GetPostPort();
	DWORD dwRes = 0;
	CWHService::Post(csResponse,pGlobalServer->GetPlatformServer(4),nPort,htmlpa,sContent,dwRes,TRUE);

	return true;
}

//��������
bool CGlobalUnits::PlayGameSound(LPCTSTR pszSoundName)
{
	//��������
	ASSERT(CParameterGlobal::GetInstance()!=NULL);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

	//�����ж�
	if (pParameterGlobal->m_bAllowSound==false) return false;
	if (AfxGetMainWnd()->IsWindowVisible()==FALSE) return false;

	//��������
	PlaySound(pszSoundName,AfxGetInstanceHandle(),SND_ASYNC|SND_NODEFAULT);

	return true;
}

//��������
bool CGlobalUnits::PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName)
{
	//��������
	ASSERT(CParameterGlobal::GetInstance()!=NULL);
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

	//�����ж�
	if (pParameterGlobal->m_bAllowSound==false) return false;
	if (AfxGetMainWnd()->IsWindowVisible()==FALSE) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance,pszSoundName,TEXT("WAVE"));
	if (hResource==NULL) return false;

	//������Դ
	HGLOBAL hGlobal=LoadResource(hInstance,hResource);
	if (hGlobal==NULL) return false;

	//��������
	LPCTSTR pszMemory=(LPCTSTR)LockResource(hGlobal);
	PlaySound(pszMemory,hInstance,SND_ASYNC|SND_MEMORY);

	//������Դ
	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return true;
}

//������Ϸ
bool CGlobalUnits::DownLoadClient(LPCTSTR pszClientName, WORD wKindID, WORD wServerID,LPCTSTR szProcessName)
{
	//��������
	if (m_pDlgDownLoad==NULL)
	{
		m_pDlgDownLoad=new CDlgDownLoad;
		m_pDlgDownLoad->InitDownLoad();
	}
	//if (m_pDlgDownLoad->m_bClosing ==true)
	//{
	//	return false;
	//}

	//��������
	if (m_pDlgDownLoad->m_hWnd==NULL)
	{
		m_pDlgDownLoad->Create(IDD_DLG_DOWNLOAD,CPlatformFrame::GetInstance());
	}

	//������Ϸ
	m_pDlgDownLoad->DownLoadClient(pszClientName,wKindID,wServerID,szProcessName);

	return true;
}
bool CGlobalUnits::InitArrayFitler()
{						
	CString sLocalPath;
	CString sFilterPath;
	sFilterPath=m_sAppPath+FILTER_STRING_NAME;

	sLocalPath = m_sAppPath + FILTER_STRING_FILE;
	CCressXML xml;
	if (xml.LoadFile(sLocalPath))
	{
		//if(m_nClientKey == 0)
		//{
		//	xml.SelectNodeToList("ver");	
		//	if (xml.QueryNode() != NULL)
		//	{
		//		m_nClientKey = atoi(xml.GetValueByName("."));
		//	}
		//}
		m_CriticalFilter.Lock();

		//��ͨ���滻
		m_arrayFitler.RemoveAll();
		xml.SelectNodeToList("strings");
		while (xml.QueryNode() != NULL)	
		{
			CString temp = xml.GetValueByName("string");
			temp.MakeLower();
			m_arrayFitler.Add((LPCTSTR)temp);
		}

		//�ж�URL �Ĺؼ�
		m_arrayFliterUrl.RemoveAll();
		xml.SelectNodeToList("stringurl");
		while (xml.QueryNode() != NULL)	
		{
			CString temp = xml.GetValueByName("string");
			temp.MakeLower();
			m_arrayFliterUrl.Add((LPCTSTR)temp);
		}

		//�ж� Q�Ĺؼ�
		m_arrayQQ.RemoveAll();
		xml.SelectNodeToList("stringqq");
		while (xml.QueryNode() != NULL)	
		{
			CString temp = xml.GetValueByName("string");
			temp.MakeLower();
			m_arrayQQ.Add((LPCTSTR)temp);
		}


		m_CriticalFilter.Unlock();
	}
	return true;
}

bool CGlobalUnits::ReplaceFitler(CString& sFilterString,int ntype)
{
	bool bsrelust = true;

	m_CriticalFilter.Lock();

	CString stmp;
	stmp=sFilterString;
	stmp.MakeLower();
	int i=0;

	//�ж�URL
	int nCountUrl = m_arrayFliterUrl.GetSize();
	for(i=0;i<nCountUrl;i++)
	{
		int nPos;
		nPos=stmp.Find(m_arrayFliterUrl[i]);

		if(ntype == 0)
		{
			while (nPos != -1)
			{
				if(nPos>2 && (sFilterString.GetLength()-nPos>2))
				{
					int startpos = nPos-2;
					for(startpos;startpos<nPos+3;startpos++)
					{  
						if ((TBYTE)stmp.GetAt(startpos) >= 0xA1)
							break;
						else
						{
							m_CriticalFilter.Unlock();
							return false;
						} 
					}
				}
				nPos=stmp.Find(m_arrayFliterUrl[i],nPos+1);
			}
		}

		if(ntype == 1)
		{
			if(nPos != -1)
				return false;
		}
	}

	//�ж�QQ
	int pcountStr = sFilterString.GetLength();
	int ncount = 0 ;//����������6

	//���ȫ����ͬ�����ж�,true ��ʾ��ͬ
	bool bsSame = true;
	CString ptemstrOld;
	int pt=0;
	for(pt =0;pt<pcountStr;pt++)
	{
		CString ptemp;
		if((TBYTE)sFilterString.GetAt(pt) < 0xA1)
		{
			ptemp = sFilterString.GetAt(pt);
		}
		else
		{
			ptemp = sFilterString.Mid(pt,2);
			pt++;
		}
		if(ptemstrOld =="")
			ptemstrOld = ptemp;

		if(ptemstrOld != ptemp)
		{
			bsSame = FALSE;
			break;
		}
	}

	if(bsSame)
	{
		m_CriticalFilter.Unlock();
		return true;
	}

	for(pt =0;pt<pcountStr;pt++)
	{
		CString ptemp;
		if((TBYTE)sFilterString.GetAt(pt) < 0xA1)
		{
			ptemp = sFilterString.GetAt(pt);
		}
		else
		{
			ptemp = sFilterString.Mid(pt,2);
			pt++;
		}

		int nCountQQ = m_arrayQQ.GetSize();

		if(ntype == 0)
		{
			//if(ptemp >=0x41 && ptemp<=0x7a)
			//	ncount++;
			//else
			//{
			//	for(i=0;i<nCountQQ;i++)
			//	{
			//		if(ptemp == m_arrayQQ[i])
			//			ncount++;
			//	}	
			//}
		}
		else
		{
			for(i=0;i<nCountQQ;i++)
			{
				if(ptemp == m_arrayQQ[i])
					ncount++;
			}	
		}

		if(ncount>5)
		{
			bsrelust = false;
			break;
		}
	}
	m_CriticalFilter.Unlock();

	return bsrelust;
}
CString CGlobalUnits::ReplaceFitlerByReturn(CString sFilterString)
{
	sFilterString = OnReplaceQuanBan(sFilterString);
	m_CriticalFilter.Lock();

	int nCount = m_arrayFitler.GetSize();
	CString sReplaceStr;
	CString sSrc;

	CString stmp;
	stmp=sFilterString;
	stmp.MakeLower();

	for (int i = 0; i < nCount; i ++)
	{
		int nPos;
		nPos=stmp.Find(m_arrayFitler[i]);
		if (nPos != -1)
		{
			int nLength=m_arrayFitler[i].GetLength();
			sReplaceStr = "";
			for(int j = 0;j < nLength;j++)
			{  
				if ((TBYTE)m_arrayFitler[i].GetAt(j) < 0x80)
				{
					sReplaceStr += "*";
				}
				else
				{
					sReplaceStr += "*";
					j ++;
					if(j >= m_arrayFitler[i].GetLength())
						break;
				}
			}
			while (nPos != -1) 
			{

				if (sFilterString.GetLength() >= (nPos+nLength)) 
				{
					sFilterString.Delete(nPos,nLength);
					sFilterString.Insert(nPos,sReplaceStr);
					stmp.Delete(nPos,nLength);
					stmp.Insert(nPos,sReplaceStr);

				}
				nPos=stmp.Find(m_arrayFitler[i]);
			}

		}

	}

	m_CriticalFilter.Unlock();
	return sFilterString;
}


CString CGlobalUnits::OnReplaceQuanBan(CString sResult)
{
	int nLength=sResult.GetLength();
	if (nLength==0)
		return "";
	CString str="";
	char *cTmp=new char[nLength+1];
	memset(cTmp,0,nLength+1);
	memcpy(cTmp,sResult,nLength);
	BYTE c1,c2;
	int i;
	for (i=0;i<nLength;i++)
	{
		c1=cTmp[i];
		c2=cTmp[i+1];
		if (c1==163)//�ж��Ƿ�Ϊȫ���ַ�
		{

			str=str+((char)(c2-128));
			i++;
			continue;
		}
		if(c1 >= 161 && c1 < 163)
		{
			if (c2==161)//ȫ�ǿո��Ǹ���������Ӵ���
			{
				str=str+" ";
				i++;
				continue;
			}
			else
			{
				str=str+((char)c1);
				str=str+((char)c2);
				i++;
				continue;
			}
		}

		if (c1>=129)//�ж��Ƿ�Ϊ����GBK���룬163 Ϊ GB2312
		{			
			str=str+((char)c1);
			str=str+((char)c2);
			i++;
			continue;
		}		
		str=str+((char)c1);
	}	
	delete cTmp;
	cTmp=NULL;
	return str;
}
//////////////////////////////////////////////////////////////////////////////////
