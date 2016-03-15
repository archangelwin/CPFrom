#include "StdAfx.h"
#include "WHService.h"
#include "WHEncrypt.h"
#include "Resource.h"
//#include <shellapi.h>
//////////////////////////////////////////////////////////////////////////////////

//压缩文件
#include "Compress\ZLib.h"

#include<windows.h>
#include<wininet.h>
#include<iostream>
#include <afxinet.h>
#pragma comment(lib,"wininet.lib")

#define agent_name "codegurubrowser1.0"

//链接文件
#ifndef _DEBUG
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLib.lib")
#else
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLibD.lib")
#endif

//////////////////////////////////////////////////////////////////////////////////

//状态信息
struct tagAstatInfo
{
	ADAPTER_STATUS					AdapterStatus;						//网卡状态
	NAME_BUFFER						NameBuff[16];						//名字缓冲
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
	CString sResponse;//反馈,这个就是你要的
	const char *szServer;//服务器
	WORD nPort;//端口
	const char* szObject;//URI
	const char *szData; //正文内容
	DWORD dwHttpStatus;//状态码
	BOOL bAutoRedirect;
}HttpPostParam;

//////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI HttpPostApp(PVOID pParam);
//构造函数
CWHService::CWHService()
{
}

//拷贝字符
bool CWHService::SetClipboardString(LPCTSTR pszString)
{
	//变量定义
	HANDLE hData=NULL;
	BOOL bOpenClopboard=FALSE;

	//执行逻辑
	__try
	{
		//打开拷贝
		bOpenClopboard=OpenClipboard(AfxGetMainWnd()->m_hWnd);
		if (bOpenClopboard==FALSE) __leave;

		//清空拷贝
		if (EmptyClipboard()==FALSE) __leave;

		//申请内存
		HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,CountStringBuffer(pszString));
		if (hData==NULL) __leave;

		//复制数据
		lstrcpy((LPTSTR)GlobalLock(hData),pszString);
		GlobalUnlock(hData);

		//设置数据
		#ifndef _UNICODE
			::SetClipboardData(CF_TEXT,hData);
		#else
			::SetClipboardData(CF_UNICODETEXT,hData);
		#endif
	}

	//终止程序
	__finally
	{
		//释放内存
		if (hData!=NULL) GlobalUnlock(hData);

		//关闭拷贝
		if (bOpenClopboard==TRUE) CloseClipboard();

		//错误判断
		if (AbnormalTermination()==TRUE)
		{
			ASSERT(FALSE);
		}
	}

	return true;
}

//机器标识
bool CWHService::GetMachineID(TCHAR szMachineID[LEN_MACHINE_ID])
{
	//变量定义
	TCHAR szMACAddress[LEN_NETWORK_ID]=TEXT("");

	//网卡标识
	GetMACAddress(szMACAddress);

	//转换信息
	ASSERT(LEN_MACHINE_ID>=LEN_MD5);
	CWHEncrypt::MD5Encrypt(szMACAddress,szMachineID);

	return true;
}

//机器标识
bool CWHService::GetMachineIDEx(TCHAR szMachineID[LEN_MACHINE_ID])
{
	//变量定义
	TCHAR szMACAddress[LEN_NETWORK_ID]=TEXT("");

	//网卡标识
	WORD wMacSize=GetMACAddress(szMACAddress);

	//硬盘标识
	DWORD *pbuf=(DWORD*)szMACAddress;
	WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
	LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
	for (WORD i=wIndex;i<CountArray(pszHardDisk);i++)
	{
		ASSERT(CountArray(pszHardDisk)>(i-wIndex));
		GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,pbuf+i,NULL,NULL,0,NULL);
	}

	//转换信息
	ASSERT(LEN_MACHINE_ID>=LEN_MD5);
	CWHEncrypt::MD5Encrypt(szMACAddress,szMachineID);

	return true;
}

//网卡地址
bool CWHService::GetMACAddress(TCHAR szMACAddress[LEN_NETWORK_ID])
{
	//变量定义
	HINSTANCE hInstance=NULL;

	//执行逻辑
	__try
	{
		//加载 DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) __leave;

		//获取函数
		typedef BYTE __stdcall NetBiosProc(NCB * Ncb);
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) __leave;

		//变量定义
		NCB Ncb;
		LANA_ENUM LanaEnum;
		ZeroMemory(&Ncb,sizeof(Ncb));
		ZeroMemory(&LanaEnum,sizeof(LanaEnum));

		//枚举网卡
		Ncb.ncb_command=NCBENUM;
		Ncb.ncb_length=sizeof(LanaEnum);
		Ncb.ncb_buffer=(BYTE *)&LanaEnum;
		if ((pNetBiosProc(&Ncb)!=NRC_GOODRET)||(LanaEnum.length==0)) __leave;

		//获取地址
		if (LanaEnum.length>0)
		{
			//变量定义
			tagAstatInfo Adapter;
			ZeroMemory(&Adapter,sizeof(Adapter));

			//重置网卡
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[0];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) __leave;

			//获取状态
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[0];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) __leave;

			//获取地址
			for (INT i=0;i<6;i++)
			{
				ASSERT((i*2)<LEN_NETWORK_ID);
				_stprintf(&szMACAddress[i*2],TEXT("%02X"),Adapter.AdapterStatus.adapter_address[i]);
			}
		}
	}

	//结束清理
	__finally
	{
		//释放资源
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}

		//错误断言
		if (AbnormalTermination()==TRUE)
		{
			ASSERT(FALSE);
		}
	}

	return true;
}

//注销热键
bool CWHService::UnRegisterHotKey(HWND hWnd, UINT uKeyID)
{
	//注销热键
	BOOL bSuccess=::UnregisterHotKey(hWnd,uKeyID);

	return (bSuccess==TRUE)?true:false;
}

//注册热键
bool CWHService::RegisterHotKey(HWND hWnd, UINT uKeyID, WORD wHotKey)
{
	//变量定义
	BYTE cbModifiers=0;
	if (HIBYTE(wHotKey)&HOTKEYF_ALT) cbModifiers|=MOD_ALT;
	if (HIBYTE(wHotKey)&HOTKEYF_SHIFT) cbModifiers|=MOD_SHIFT;
	if (HIBYTE(wHotKey)&HOTKEYF_CONTROL) cbModifiers|=MOD_CONTROL;

	//注册热键
	BOOL bSuccess=::RegisterHotKey(hWnd,uKeyID,cbModifiers,LOBYTE(wHotKey));

	return (bSuccess==TRUE)?true:false;
}

//进程目录
bool CWHService::GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount)
{
	//模块路径
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szModulePath,CountArray(szModulePath));

	//分析文件
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//设置结果
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;
}

VOID CWHService::GetGameResDirectory(tagGameKind &GameKind,TCHAR szResDirectory[], WORD wBufferCount)
{
	//变量定义
	WORD wStringIndex=0;

	//构造目录
	ZeroMemory(szResDirectory,wBufferCount*sizeof(TCHAR));
	lstrcpyn(szResDirectory,GameKind.szProcessName,wBufferCount);
	while ((szResDirectory[wStringIndex]!=0)&&(szResDirectory[wStringIndex]!=TEXT('.'))) wStringIndex++;

	//字符终止
	szResDirectory[wStringIndex]=0;

	return;
}

//文件版本
bool CWHService::GetModuleVersion(LPCTSTR pszModuleName, DWORD & dwVersionInfo)
{
	//设置结果
	dwVersionInfo=0L;

	//接收缓冲
	BYTE cbInfoBuffer[1024];
	ZeroMemory(cbInfoBuffer,sizeof(cbInfoBuffer));

	//模块信息
    DWORD dwFileHandle=NULL;
	if (GetFileVersionInfo(pszModuleName,dwFileHandle,sizeof(cbInfoBuffer),cbInfoBuffer)==FALSE) return false;

	//获取信息
	UINT uQuerySize=0;
	VS_FIXEDFILEINFO * pFixedFileInfo=NULL;
    if (VerQueryValue(cbInfoBuffer,TEXT("\\"),(VOID * *)&pFixedFileInfo,&uQuerySize)==FALSE) return false;

	//设置结果
	if ((pFixedFileInfo!=NULL)&&(uQuerySize==sizeof(VS_FIXEDFILEINFO)))
	{
		//设置版本
		WORD wVersion1=HIWORD(pFixedFileInfo->dwFileVersionMS);
		WORD wVersion2=LOWORD(pFixedFileInfo->dwFileVersionMS);
		WORD wVersion3=HIWORD(pFixedFileInfo->dwFileVersionLS);
		WORD wVersion4=LOWORD(pFixedFileInfo->dwFileVersionLS);
		dwVersionInfo=MAKELONG(MAKEWORD(wVersion4,wVersion3),MAKEWORD(wVersion2,wVersion1));

		return true;
	}

	return false;
}

//压缩数据
ULONG CWHService::CompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//压缩数据
	if (compress(cbResultData,&lResultSize,pcbSourceData,lSourceSize)==0L)
	{
		return lResultSize;
	}

	return 0L;
}

//解压数据
ULONG CWHService::UnCompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//解压数据
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
	//设置资源
//	AfxSetResourceHandle(GetModuleHandle(SERVICE_CORE_DLL_NAME));
	TCHAR key[MAX_PATH + MAX_PATH];
	// 调用函数ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

	// 如果错误，则检查注册表获得.htm文件的注册键值
	if ((UINT)result <= HINSTANCE_ERROR) {

		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
			lstrcat(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) {                     // 没有发现
					pos = strstr(key, _T("%1"));       // 检查%1
					if (pos == NULL)                   // 没有参数
						pos = key+lstrlen(key)-1;
					else
						*pos = '\0';                   // 删除参数
				}
				else
					*pos = '\0';                       // 删除参数

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
	//长度判断
	UINT nCharLength=lstrlen(pszNumString);
	if(nCharLength==0L) 
	{
		return false;
	}

	//变量定义
	bool bNumber=true;

	//数字判断
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

//bool CWHService::Post(CString& csResponse,//反馈,这个就是你要的
//								   const char *szServer,//服务器
//								   WORD& nPort,//端口
//								   const char* szObject,//URI
//								   const char *szData, //正文内容
//								   DWORD& dwHttpStatus,//状态码
//								   BOOL bAutoRedirect)//是否自动转向
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
//		//计算本地内存空间大小
//		dwFileSize = atol(szSizeBuffer);
//		LPSTR szContents = contents.GetBuffer(dwFileSize);
//		//读取http文件
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

bool CWHService::Post(CString& csResponse,//反馈,这个就是你要的
					   const char *szServer,//服务器
					   INTERNET_PORT& nPort,//端口
					   const char* szObject,//URI
					   const char *szData, //正文内容
					   DWORD& dwHttpStatus,//状态码
					   BOOL bAutoRedirect)//是否自动转向
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
