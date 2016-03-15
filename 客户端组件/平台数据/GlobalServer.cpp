#include "StdAfx.h"
#include "GlobalServer.h"

//////////////////////////////////////////////////////////////////////////////////
#define	SERVER_INFO_FILE	 "\\LobbyDate\\ServerInfo.INI"
#define	PLATFORM_INFO_FILE	 "\\LobbyDate\\Platform.INI"

//��̬����
CGlobalServer * CGlobalServer::m_pGlobalServer=NULL;				//ƽ̨��Ϣ

//���캯��
CGlobalServer::CGlobalServer()
{
	//���ö���
	ASSERT(m_pGlobalServer==NULL);
	if (m_pGlobalServer==NULL) 
		m_pGlobalServer=this;
}

//��������
CGlobalServer::~CGlobalServer()
{
	//�ͷŶ���
	ASSERT(m_pGlobalServer==this);
	if (m_pGlobalServer==this) m_pGlobalServer=NULL;
}

//������Ŀ
WORD CGlobalServer::GetItemCount()
{
	//��ȡ��Ŀ
	WORD wItemCount=ReadFileValue(TEXT("ServerInfo"),TEXT("ItemCount"),0);

	return wItemCount;
}

//��������
VOID CGlobalServer::GetServerItemName(WORD wIndex, TCHAR szResult[LEN_SERVER])
{
	//��������
	TCHAR szItemName[LEN_SERVER]=TEXT("");
	_sntprintf(szItemName,CountArray(szItemName),TEXT("ItemDescribe%d"),wIndex+1);

	//��ȡ����
	ReadFileString(TEXT("ServerInfo"),szItemName,szResult,LEN_SERVER);

	return;
}

//�ϴε�¼
VOID CGlobalServer::SetLastServerName(LPCTSTR pszLastServer)
{
	//д������
	WriteFileString(TEXT("GlobalInfo"),TEXT("LastServerName"),pszLastServer);

	return;
}

//�ϴε�¼
VOID CGlobalServer::GetLastServerName(TCHAR szResult[LEN_SERVER])
{
	//��ȡ����
	ReadFileString(TEXT("GlobalInfo"),TEXT("LastServerName"),szResult,LEN_SERVER);

	return;
}

//��ȡ��Դ�汾
UINT CGlobalServer::GetPlatInfo(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault)
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s\\%s"),szDirectory,PLATFORM_INFO_FILE);

	//��ȡ����
	UINT nValue=GetPrivateProfileInt(pszKeyName,pszItemName,nDefault,szServerInfoPath);

	return nValue;
}

//������Ϣ
bool CGlobalServer::GetServerItemInfo(LPCTSTR pszServerName, tagServerItem & ServerItem)
{
	//Ч�����
	ASSERT(pszServerName!=NULL);
	if (pszServerName==NULL) return false;

	//��������
	TCHAR szServerName[LEN_MD5];
	CWHEncrypt::MD5Encrypt(pszServerName,szServerName);

	//��ȡ��Ϣ
	ServerItem.wServerPort=ReadFileValue(szServerName,TEXT("ServerPort"),PORT_LOGON);
	ServerItem.dwServerAddr=ReadFileValue(szServerName,TEXT("ServerAddr"),INADDR_NONE);
	ReadFileString(szServerName,TEXT("ServerDomain"),ServerItem.szServerHost,CountArray(ServerItem.szServerHost));

	//��ַת��
	if (ServerItem.dwServerAddr==0L)
		ServerItem.dwServerAddr=INADDR_NONE;

	return ((ServerItem.dwServerAddr!=INADDR_NONE)||(ServerItem.szServerHost[0]!=0));
}

//д����ֵ
VOID CGlobalServer::WriteFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nValue)
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s\\%s"),szDirectory,SERVER_INFO_FILE);

	//��������
	TCHAR szString[16]=TEXT("");
	_sntprintf(szString,CountArray(szString),TEXT("%d"),nValue);

	//д������
	WritePrivateProfileString(pszKeyName,pszItemName,szString,szServerInfoPath);

	return;
}

//д������
VOID CGlobalServer::WriteFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, LPCTSTR pszString)
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s\\%s"),szDirectory,SERVER_INFO_FILE);

	//��������
	TCHAR szResultEncrypt[MAX_ENCRYPT_LEN];
	ZeroMemory(szResultEncrypt,sizeof(szResultEncrypt));

	//д������
	CWHEncrypt::XorEncrypt(pszString,szResultEncrypt,CountArray(szResultEncrypt));
	WritePrivateProfileString(pszKeyName,pszItemName,szResultEncrypt,szServerInfoPath);

	return;
}

//��ȡ��ֵ
UINT CGlobalServer::ReadFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault)
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s\\%s"),szDirectory,SERVER_INFO_FILE);

	//��ȡ����
	UINT nValue=GetPrivateProfileInt(pszKeyName,pszItemName,nDefault,szServerInfoPath);

	return nValue;
}

//��ȡ����
CString CGlobalServer::ReadFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, TCHAR szResult[], WORD wMaxCount,bool bCrevasse)
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s\\%s"),szDirectory,SERVER_INFO_FILE);

	//��ȡ����
	TCHAR szResultEncrypt[MAX_ENCRYPT_LEN];
	GetPrivateProfileString(pszKeyName,pszItemName,TEXT(""),szResultEncrypt,CountArray(szResultEncrypt),szServerInfoPath);

	if (bCrevasse)
	{
		//��������
		szResult[0]=0;
		CWHEncrypt::XorCrevasse(szResultEncrypt,szResult,wMaxCount);
		return szResult;
	}
	else
	{
		CString sResult = szResultEncrypt;
		return sResult;
	}
}

//��ȡ����
CString CGlobalServer::ReadPlatFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, TCHAR szResult[], WORD wMaxCount,bool bCrevasse)
{
	//����·��
	TCHAR szPlatInfoPath[MAX_PATH]=TEXT("");
	_sntprintf(szPlatInfoPath,CountArray(szPlatInfoPath),TEXT("%s\\%s"),m_strAppPath,PLATFORM_INFO_FILE);

	//��ȡ����
	TCHAR szResultEncrypt[MAX_ENCRYPT_LEN];
	GetPrivateProfileString(pszKeyName,pszItemName,TEXT(""),szResultEncrypt,CountArray(szResultEncrypt),szPlatInfoPath);

	if (bCrevasse)
	{
		//��������
		szResult[0]=0;
		CWHEncrypt::XorCrevasse(szResultEncrypt,szResult,wMaxCount);
		return szResult;
	}
	else
	{
		CString sResult = szResultEncrypt;
		return sResult;
	}
}

void CGlobalServer::InitPlatInfo()
{
	//��ȡĿ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));
	m_strAppPath.Format(_T("%s"),szDirectory);

	//��Ʒ���
	TCHAR szTmpProduct[MAX_PATH];
	ReadPlatFileString("ProductInfo","Product",szTmpProduct,MAX_PATH);
	m_strProduct = szTmpProduct;
	if (m_strProduct == "")
	{
		m_strProduct = szProduct;
	}

	//TCHAR szTmpProductClass[MAX_PATH];
	//ReadPlatFileString("ProductInfo","ProductClass",szTmpProductClass,MAX_PATH);
	//m_strProductClass = szTmpProductClass;
	if (m_strProductClass == "")
	{
		m_strProductClass = szPlazaClass;
	}

	TCHAR szTmpProductKey[MAX_PATH];
	ReadPlatFileString("ProductInfo","ProductKey",szTmpProductKey,MAX_PATH);
	m_strProductKey = szTmpProductKey;
	if (m_strProductKey == "")
	{
		m_strProductKey = szProductKey;
	}

	//���������
	TCHAR szLogonServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","LogonServer",szLogonServer,MAX_PATH);
	m_strLogonServer = szLogonServer;
	if (m_strLogonServer == "")
	{
		m_strLogonServer = szLogonUrl;
	}

	TCHAR szCookieServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","CookieServer",szCookieServer,MAX_PATH);
	m_strCookieServer = szCookieServer;
	if (m_strCookieServer == "")
	{
		m_strCookieServer = szCookieUrl;
	}

	TCHAR szPlatformLink[MAX_PATH];
	ReadPlatFileString("ServerInfo","PlatformLink",szPlatformLink,MAX_PATH);
	m_strPlatformLink = szPlatformLink;
	if (m_strPlatformLink == "")
	{
		m_strPlatformLink = szPlatformUrl;
	}

	TCHAR szWebPostServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","WebPostServer",szWebPostServer,MAX_PATH);
	m_strWebPostServer = szWebPostServer;
	if (m_strWebPostServer == "")
	{
		m_strWebPostServer = szWebPostUrl;
	}

	TCHAR szZipPostServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","ZipPostServer",szZipPostServer,MAX_PATH);
	m_strZipPostServer = szZipPostServer;
	if (m_strWebPostServer == "")
	{
		m_strZipPostServer = szWebPostUrl;
	}

	TCHAR szDownLoadServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","DownLoadServer",szDownLoadServer,MAX_PATH);
	m_sDownLowdServer = szDownLoadServer;
	if (m_sDownLowdServer == "")
	{
		m_sDownLowdServer = m_strPlatformLink;
	}

	TCHAR szPayServer[MAX_PATH];
	ReadPlatFileString("ServerInfo","PayServer",szPayServer,MAX_PATH);
	m_sPayServer = szPayServer;
	if (m_sPayServer == "")
	{
		m_sPayServer = szPayUrl;
	}

	TCHAR szQQUrl[MAX_PATH];
	ReadPlatFileString("ServerInfo","QQServer",szQQUrl,MAX_PATH);
	m_strQQUrl = szQQUrl;
	if (m_strQQUrl == "" || m_strQQUrl.Find("http://")==-1)
	{
		m_strQQUrl.Format("%s/QQLogin.aspx",m_strPlatformLink);
	}

	TCHAR szWebPostPost[MAX_PATH];
	ReadPlatFileString("ServerInfo","WebPostPort",szWebPostPost,MAX_PATH);
	m_nWebPostPort = atoi(szWebPostPost);
	if (m_nWebPostPort < 80 || m_nWebPostPort>65534)
	{
		m_nWebPostPort = 80;
	}

	TCHAR szQQLogon[MAX_PATH];
	ReadPlatFileString("ServerInfo","QQLogon",szQQLogon,MAX_PATH);
	m_nWebPostPort = atoi(szQQLogon);
	if (m_nWebPostPort < 80 || m_nWebPostPort>65534)
	{
		m_nWebPostPort = 80;
	}

	int nQQ = GetPlatInfo(TEXT("PlatInfo"),TEXT("bHaveQQ"),0);
	if (nQQ == 0)
		m_bHaveQQLogon = false;
	else
		m_bHaveQQLogon = true;

	//��ʾ��Ϸ�ȼ�
	int nLevel = GetPlatInfo(TEXT("PlatInfo"),TEXT("bGameLevelShow "),0);
	if (nLevel == 0)
		m_bGameLevel = false;
	else
		m_bGameLevel = true;
}

CString CGlobalServer::GetPlatformProduct(int nType)
{
	switch (nType)
	{
	case 1:
		{
			return m_strProduct;
			break;
		}	
	case 2:
		{
			return m_strProductClass;
			break;
		}	
	case 3:
		{
			return m_strProductKey;
			break;
		}	
	default:
		{
			return "";
			break;
		}
	}
}

CString CGlobalServer::GetPlatformServer(int nType)
{
	switch (nType)
	{
	case 1:
		{
			return m_strLogonServer;
			break;
		}	
	case 2:
		{
			return m_strCookieServer;
			break;
		}	
	case 3:
		{
			return m_strPlatformLink;
			break;
		}	
	case 4:
		{
			return m_strWebPostServer;
			break;
		}	
	case 5:
		{
			return m_sDownLowdServer;
			break;
		}	
	case 6:
		{
			return m_sPayServer;
			break;
		}	
	case 7:
		{
			return m_strZipPostServer;
			break;
		}
	default:
		{
			return "";
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
