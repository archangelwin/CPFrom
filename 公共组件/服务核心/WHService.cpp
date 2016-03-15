#include "StdAfx.h"
#include "WHService.h"
#include "WHEncrypt.h"
#include "Resource.h"
//#include <shellapi.h>
//////////////////////////////////////////////////////////////////////////////////

//ѹ���ļ�
#include "Compress\ZLib.h"

#include<windows.h>
#include<wininet.h>
#include<iostream>
#include <afxinet.h>
#pragma comment(lib,"wininet.lib")

#define agent_name "codegurubrowser1.0"

//�����ļ�
#ifndef _DEBUG
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLib.lib")
#else
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLibD.lib")
#endif

//////////////////////////////////////////////////////////////////////////////////

//״̬��Ϣ
struct tagAstatInfo
{
	ADAPTER_STATUS					AdapterStatus;						//����״̬
	NAME_BUFFER						NameBuff[16];						//���ֻ���
};


typedef struct _THttpPostParam
{
	_THttpPostParam()
	{
		sResponse = "";
		szServer = NULL;
		nPort = 0;
		szObject = NULL;
		szData = NULL;
		dwHttpStatus = 0;
		bAutoRedirect = FALSE;	
	}
	CString sResponse;//����,���������Ҫ��
	const char *szServer;//������
	WORD nPort;//�˿�
	const char* szObject;//URI
	const char *szData; //��������
	DWORD dwHttpStatus;//״̬��
	BOOL bAutoRedirect;
}HttpPostParam;

//////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI HttpPostApp(PVOID pParam);
//���캯��
CWHService::CWHService()
{
}

//�����ַ�
bool CWHService::SetClipboardString(LPCTSTR pszString)
{
	//��������
	HANDLE hData=NULL;
	BOOL bOpenClopboard=FALSE;

	//ִ���߼�
	__try
	{
		//�򿪿���
		bOpenClopboard=OpenClipboard(AfxGetMainWnd()->m_hWnd);
		if (bOpenClopboard==FALSE) __leave;

		//��տ���
		if (EmptyClipboard()==FALSE) __leave;

		//�����ڴ�
		HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,CountStringBuffer(pszString));
		if (hData==NULL) __leave;

		//��������
		lstrcpy((LPTSTR)GlobalLock(hData),pszString);
		GlobalUnlock(hData);

		//��������
		#ifndef _UNICODE
			::SetClipboardData(CF_TEXT,hData);
		#else
			::SetClipboardData(CF_UNICODETEXT,hData);
		#endif
	}

	//��ֹ����
	__finally
	{
		//�ͷ��ڴ�
		if (hData!=NULL) GlobalUnlock(hData);

		//�رտ���
		if (bOpenClopboard==TRUE) CloseClipboard();

		//�����ж�
		if (AbnormalTermination()==TRUE)
		{
			ASSERT(FALSE);
		}
	}

	return true;
}

//������ʶ
bool CWHService::GetMachineID(TCHAR szMachineID[LEN_MACHINE_ID])
{
	//��������
	TCHAR szMACAddress[LEN_NETWORK_ID]=TEXT("");

	//������ʶ
	GetMACAddress(szMACAddress);

	//ת����Ϣ
	ASSERT(LEN_MACHINE_ID>=LEN_MD5);
	CWHEncrypt::MD5Encrypt(szMACAddress,szMachineID);

	return true;
}

//������ʶ
bool CWHService::GetMachineIDEx(TCHAR szMachineID[LEN_MACHINE_ID])
{
	//��������
	TCHAR szMACAddress[LEN_NETWORK_ID]=TEXT("");

	//������ʶ
	WORD wMacSize=GetMACAddress(szMACAddress);

	//Ӳ�̱�ʶ
	DWORD *pbuf=(DWORD*)szMACAddress;
	WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
	LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
	for (WORD i=wIndex;i<CountArray(pszHardDisk);i++)
	{
		ASSERT(CountArray(pszHardDisk)>(i-wIndex));
		GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,pbuf+i,NULL,NULL,0,NULL);
	}

	//ת����Ϣ
	ASSERT(LEN_MACHINE_ID>=LEN_MD5);
	CWHEncrypt::MD5Encrypt(szMACAddress,szMachineID);

	return true;
}

//������ַ
bool CWHService::GetMACAddress(TCHAR szMACAddress[LEN_NETWORK_ID])
{
	//��������
	HINSTANCE hInstance=NULL;

	//ִ���߼�
	__try
	{
		//���� DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) __leave;

		//��ȡ����
		typedef BYTE __stdcall NetBiosProc(NCB * Ncb);
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) __leave;

		//��������
		NCB Ncb;
		LANA_ENUM LanaEnum;
		ZeroMemory(&Ncb,sizeof(Ncb));
		ZeroMemory(&LanaEnum,sizeof(LanaEnum));

		//ö������
		Ncb.ncb_command=NCBENUM;
		Ncb.ncb_length=sizeof(LanaEnum);
		Ncb.ncb_buffer=(BYTE *)&LanaEnum;
		if ((pNetBiosProc(&Ncb)!=NRC_GOODRET)||(LanaEnum.length==0)) __leave;

		//��ȡ��ַ
		if (LanaEnum.length>0)
		{
			//��������
			tagAstatInfo Adapter;
			ZeroMemory(&Adapter,sizeof(Adapter));

			//��������
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[0];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) __leave;

			//��ȡ״̬
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[0];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) __leave;

			//��ȡ��ַ
			for (INT i=0;i<6;i++)
			{
				ASSERT((i*2)<LEN_NETWORK_ID);
				_stprintf(&szMACAddress[i*2],TEXT("%02X"),Adapter.AdapterStatus.adapter_address[i]);
			}
		}
	}

	//��������
	__finally
	{
		//�ͷ���Դ
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}

		//�������
		if (AbnormalTermination()==TRUE)
		{
			ASSERT(FALSE);
		}
	}

	return true;
}

//ע���ȼ�
bool CWHService::UnRegisterHotKey(HWND hWnd, UINT uKeyID)
{
	//ע���ȼ�
	BOOL bSuccess=::UnregisterHotKey(hWnd,uKeyID);

	return (bSuccess==TRUE)?true:false;
}

//ע���ȼ�
bool CWHService::RegisterHotKey(HWND hWnd, UINT uKeyID, WORD wHotKey)
{
	//��������
	BYTE cbModifiers=0;
	if (HIBYTE(wHotKey)&HOTKEYF_ALT) cbModifiers|=MOD_ALT;
	if (HIBYTE(wHotKey)&HOTKEYF_SHIFT) cbModifiers|=MOD_SHIFT;
	if (HIBYTE(wHotKey)&HOTKEYF_CONTROL) cbModifiers|=MOD_CONTROL;

	//ע���ȼ�
	BOOL bSuccess=::RegisterHotKey(hWnd,uKeyID,cbModifiers,LOBYTE(wHotKey));

	return (bSuccess==TRUE)?true:false;
}

//����Ŀ¼
bool CWHService::GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount)
{
	//ģ��·��
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szModulePath,CountArray(szModulePath));

	//�����ļ�
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//���ý��
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;
}

VOID CWHService::GetGameResDirectory(tagGameKind &GameKind,TCHAR szResDirectory[], WORD wBufferCount)
{
	//��������
	WORD wStringIndex=0;

	//����Ŀ¼
	ZeroMemory(szResDirectory,wBufferCount*sizeof(TCHAR));
	lstrcpyn(szResDirectory,GameKind.szProcessName,wBufferCount);
	while ((szResDirectory[wStringIndex]!=0)&&(szResDirectory[wStringIndex]!=TEXT('.'))) wStringIndex++;

	//�ַ���ֹ
	szResDirectory[wStringIndex]=0;

	return;
}

//�ļ��汾
bool CWHService::GetModuleVersion(LPCTSTR pszModuleName, DWORD & dwVersionInfo)
{
	//���ý��
	dwVersionInfo=0L;

	//���ջ���
	BYTE cbInfoBuffer[1024];
	ZeroMemory(cbInfoBuffer,sizeof(cbInfoBuffer));

	//ģ����Ϣ
    DWORD dwFileHandle=NULL;
	if (GetFileVersionInfo(pszModuleName,dwFileHandle,sizeof(cbInfoBuffer),cbInfoBuffer)==FALSE) return false;

	//��ȡ��Ϣ
	UINT uQuerySize=0;
	VS_FIXEDFILEINFO * pFixedFileInfo=NULL;
    if (VerQueryValue(cbInfoBuffer,TEXT("\\"),(VOID * *)&pFixedFileInfo,&uQuerySize)==FALSE) return false;

	//���ý��
	if ((pFixedFileInfo!=NULL)&&(uQuerySize==sizeof(VS_FIXEDFILEINFO)))
	{
		//���ð汾
		WORD wVersion1=HIWORD(pFixedFileInfo->dwFileVersionMS);
		WORD wVersion2=LOWORD(pFixedFileInfo->dwFileVersionMS);
		WORD wVersion3=HIWORD(pFixedFileInfo->dwFileVersionLS);
		WORD wVersion4=LOWORD(pFixedFileInfo->dwFileVersionLS);
		dwVersionInfo=MAKELONG(MAKEWORD(wVersion4,wVersion3),MAKEWORD(wVersion2,wVersion1));

		return true;
	}

	return false;
}

//ѹ������
ULONG CWHService::CompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//ѹ������
	if (compress(cbResultData,&lResultSize,pcbSourceData,lSourceSize)==0L)
	{
		return lResultSize;
	}

	return 0L;
}

//��ѹ����
ULONG CWHService::UnCompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//��ѹ����
	if (uncompress(cbResultData,&lResultSize,pcbSourceData,lSourceSize)==0L)
	{
		return lResultSize;
	}

	return 0L;
}

LONG CWHService::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

	if (retval == ERROR_SUCCESS) {
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		lstrcpy(retdata,data);
		RegCloseKey(hkey);
	}

	return retval;
}

HINSTANCE CWHService::GotoURL(LPCTSTR url, int showcmd)
{
	//������Դ
//	AfxSetResourceHandle(GetModuleHandle(SERVICE_CORE_DLL_NAME));
	TCHAR key[MAX_PATH + MAX_PATH];
	// ���ú���ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

	// �����������ע�����.htm�ļ���ע���ֵ
	if ((UINT)result <= HINSTANCE_ERROR) {

		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
			lstrcat(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) {                     // û�з���
					pos = strstr(key, _T("%1"));       // ���%1
					if (pos == NULL)                   // û�в���
						pos = key+lstrlen(key)-1;
					else
						*pos = '\0';                   // ɾ������
				}
				else
					*pos = '\0';                       // ɾ������

				lstrcat(pos, _T(" "));
				lstrcat(pos, url);
				result = (HINSTANCE) WinExec(key,showcmd);
			}
		}
	}
	//AfxSetResourceHandle(AfxGetResourceHandle());
	return result;
}

bool CWHService::BAllNumber(LPCTSTR pszNumString)
{
	//�����ж�
	UINT nCharLength=lstrlen(pszNumString);
	if(nCharLength==0L) 
	{
		return false;
	}

	//��������
	bool bNumber=true;

	//�����ж�
	for (UINT i=0;i<nCharLength;i++)
	{
		if ((pszNumString[i]<TEXT('0'))||(pszNumString[i]>TEXT('9')))
		{
				bNumber=false;
				break;
		}
	}
	return bNumber;
}

VOID CWHService::HtmlFilter(CString &sContent)
{
	if(sContent == "")
		return;
	CString sFilterSrc[3] = {"&","<",">"};
	CString sFilterDes[3] = {"&amp;","&lt;","&gt;"};
	for(int i(0) ; i < 3 ; i ++)
	{	
		sContent.Replace(sFilterSrc[i],sFilterDes[i]);
	}
}

//bool CWHService::Post(CString& csResponse,//����,���������Ҫ��
//								   const char *szServer,//������
//								   WORD& nPort,//�˿�
//								   const char* szObject,//URI
//								   const char *szData, //��������
//								   DWORD& dwHttpStatus,//״̬��
//								   BOOL bAutoRedirect)//�Ƿ��Զ�ת��
//{
//	HINTERNET hSession = NULL;
//	HINTERNET hHttpFile;
//	char szSizeBuffer[32] = {0};
//	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
//	DWORD dwFileSize;
//	DWORD dwBytesRead;
//	bool bSuccessful =false;
//	CString contents;
//
//	CString url;
//	url.Format("%s%s%s%s%s","http://", szServer ,"/" , szObject , szData);
//
//	hSession = ::InternetOpen(agent_name,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
//	hHttpFile = ::InternetOpenUrl(hSession,(const char *)url,NULL,0,0,0);//new CInternetSession(	
//	bool bquery = ::HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH,szSizeBuffer,&dwLengthSizeBuffer,NULL);
//	if (bquery)
//	{
//		//���㱾���ڴ�ռ��С
//		dwFileSize = atol(szSizeBuffer);
//		LPSTR szContents = contents.GetBuffer(dwFileSize);
//		//��ȡhttp�ļ�
//		bool bread = ::InternetReadFile(hHttpFile,szContents,dwFileSize,&dwBytesRead);
//		if (bread)
//			bSuccessful = true;	
//	}
//	else
//		bSuccessful = false; 
//
//	::InternetCloseHandle(hHttpFile);
//	csResponse.Format("%s",contents);
//	return bSuccessful;
//}

bool CWHService::Post(CString& csResponse,//����,���������Ҫ��
					   const char *szServer,//������
					   INTERNET_PORT& nPort,//�˿�
					   const char* szObject,//URI
					   const char *szData, //��������
					   DWORD& dwHttpStatus,//״̬��
					   BOOL bAutoRedirect)//�Ƿ��Զ�ת��
{
	//Post(csResponses,sUrl,nPort,"99cu_get_userinfo.aspx",sContent,dwRes,true);
	HttpPostParam postParam;
	postParam.szServer = szServer;
	postParam.nPort = nPort;
	postParam.szObject = szObject;
	postParam.szData = szData;
	postParam.bAutoRedirect = bAutoRedirect;	

	DWORD dID;
	HANDLE handle = ::CreateThread(NULL, NULL,
		HttpPostApp, (LPVOID)&postParam,
		NULL, &dID);

	if (handle == NULL)
		return false;

	int i = 0;
	DWORD dExit;
	for (i = 0; i < 30; i ++)
	{
		GetExitCodeThread(handle, &dExit);
		if (dExit != STILL_ACTIVE)
			break;
		Sleep(500);
	}

	if (i >= 30)
	{
		csResponse = "";
		GetExitCodeThread(handle, &dExit);
		if (dExit == STILL_ACTIVE)
			::TerminateThread(handle, dExit);
	}
	else		//succeed
	{	
		csResponse = postParam.sResponse;
		nPort = postParam.nPort;
		dwHttpStatus = 	postParam.dwHttpStatus;
	}
   return true;
}
DWORD WINAPI HttpPostApp(PVOID pParam)
{	
	HttpPostParam *pHttpPostParam = (HttpPostParam *)pParam;

	CInternetSession* pSession = NULL;
	CHttpConnection* pConnection = NULL;
	CHttpFile* pHttpFile = NULL;

	try 
	{	
		pSession = new CInternetSession(
			NULL,
			1,
			INTERNET_OPEN_TYPE_PRECONFIG);

		pConnection = pSession->GetHttpConnection(pHttpPostParam->szServer,
			pHttpPostParam->nPort,
			NULL,
			NULL);

		DWORD dwFlag= INTERNET_FLAG_EXISTING_CONNECT
			| INTERNET_FLAG_RELOAD
			| INTERNET_FLAG_DONT_CACHE;

		if(!pHttpPostParam->bAutoRedirect)
		{
			dwFlag = dwFlag| INTERNET_FLAG_NO_AUTO_REDIRECT;
		}

		pHttpFile = pConnection->OpenRequest(
			CHttpConnection::HTTP_VERB_POST,
			pHttpPostParam->szObject,
			pHttpPostParam->szServer,
			1,
			NULL,
			NULL,
			dwFlag);

		pHttpFile->AddRequestHeaders("Content-Type: application/x-www-form-urlencoded",HTTP_ADDREQ_FLAG_ADD_IF_NEW,-1L);

		pHttpFile->SendRequest(NULL,0,(void *)pHttpPostParam->szData,strlen(pHttpPostParam->szData));
		if (pHttpFile) 
		{	
			if (pHttpFile->QueryInfoStatusCode(pHttpPostParam->dwHttpStatus)!=0)
			{	
				if (pHttpPostParam->dwHttpStatus < 400)
				{	
					int nRead = 0;
					LPSTR pBuffer = new char[1024];				
					do 
					{	
						nRead = pHttpFile->Read(pBuffer, 1023);
						if (nRead != 0) 
						{
							pBuffer[nRead] = 0;
							pHttpPostParam->sResponse += pBuffer;
						} 
					} while (nRead != 0);

					if(pBuffer)
					{
						delete pBuffer;
						pBuffer = NULL;
					}	
				} 
			}
		} 	
	} 

	catch (CInternetException* e) 
	{
		e->Delete();		
	} 
	catch (...) 
	{	
	} 

	if (pHttpFile != NULL) 
	{
		pHttpFile->Close();
		delete pHttpFile; 
	} 

	if (pConnection != NULL) 
	{
		pConnection->Close();
		delete pConnection; 
	} 

	if (pSession != NULL) 
	{
		pSession->Close();
		delete pSession; 
	} 	
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
