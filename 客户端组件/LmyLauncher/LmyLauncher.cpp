
// LmyLauncher.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "LmyLauncher.h"
#include "LmyLauncherDlg.h"
#include "DlgStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLmyLauncherApp

BEGIN_MESSAGE_MAP(CLmyLauncherApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLmyLauncherApp 构造

CLmyLauncherApp::CLmyLauncherApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_nPlatVer = 0;
	//m_pWnd = NULL;
}


// 唯一的一个 CLmyLauncherApp 对象

CLmyLauncherApp theApp;


// CLmyLauncherApp 初始化

BOOL CLmyLauncherApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//存在判断
	bool bDownExist=false;
	bool bPlazaExist = false;
	CMutex Mutex(FALSE,"LmyDownload",NULL);
	if (Mutex.Lock(0)==FALSE) 
		bDownExist=true;
	//结果处理
	if (bDownExist==true) 
		return FALSE;
	//搜索窗口

	CWnd * pWndGamePlaza=CWnd::FindWindow("LMYGAME",NULL);
	if (pWndGamePlaza!=NULL) 
	{
		//设置变量
		bPlazaExist=true;
		if (MessageBox(NULL,"检测到大厅正在运行，请先关闭大厅!","龙马游更新程序",MB_OKCANCEL) == IDOK) 
		{
			HANDLE hProcessHandle; 
			ULONG nProcessID;		

			::GetWindowThreadProcessId(pWndGamePlaza->GetSafeHwnd(), &nProcessID );
			hProcessHandle = ::OpenProcess(PROCESS_TERMINATE, FALSE, nProcessID );
			::TerminateProcess( hProcessHandle, 4 );
		}
		else
		{
			//还原窗口
			if (pWndGamePlaza->IsIconic()) 
			{
				pWndGamePlaza->ShowWindow(SW_RESTORE);
			}
			//激活窗口
			pWndGamePlaza->SetActiveWindow();
			pWndGamePlaza->BringWindowToTop();
			pWndGamePlaza->SetForegroundWindow();
			//结束自己
			return false;
		}		
	}


	CString tempstr;
	char path[500] = {0};				
	::GetModuleFileName(NULL, path, 499);
	CString sTmpPaths = path;							
	CString sLocalPaths = sTmpPaths.Mid(0, sTmpPaths.ReverseFind('\\') + 1);
	m_sLocalPathStart  =  sLocalPaths;

	//构造路径
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_snprintf_s(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s%s"),theApp.m_sLocalPathStart,UPDATE_INFO_FILE);

	//读取数据
	m_nPlatVer =GetPrivateProfileInt(TEXT("VerInfo"),TEXT("PVer"),0,szServerInfoPath);
	//变量定义
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//注册窗口
	WndClasss.style=CS_DBLCLKS;
	WndClasss.hIcon=LoadIcon(IDR_MAINFRAME);
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName="LmyDownload";
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW));
	if (AfxRegisterClass(&WndClasss)==FALSE) 
		AfxThrowResourceException();

	//CDlgStatus mDlg;
	//m_pMainWnd = &mDlg;
	//INT_PTR nResponse = mDlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}

	//return false;


	//建立窗口
	CString m_sUpdateXmlUrl = "http://download.999qp.com/AutoUpdate/update.xml";  //发布时修改
	CString m_sUpdateXmlBackUrl = "http://download.999xw.com/AutoUpdate/update.xml"; //发布时修改
	CLmyLauncherDlg* pDlg = new CLmyLauncherDlg(); 

	//SYSTEMTIME      stLocal;
	//FILETIME        ftLocal;
	//ULARGE_INTEGER  uli;  

	//CString sFilePath = theApp.m_sLocalPathStart + "DownLoad.dll";
	//pDlg->GetFileDate((TCHAR*)(LPCTSTR)sFilePath, &ftLocal);

	//SystemTimeToFileTime(&stLocal, &ftLocal);  
	//uli.LowPart = ftLocal.dwLowDateTime;  
	//uli.HighPart = ftLocal.dwHighDateTime;  
	//CString sTmp;
	//sTmp.Format("Local File Time: %llu/n", uli.QuadPart);



	bool bGetXml = pDlg->GetDownFileList(m_sUpdateXmlUrl);
	if (!bGetXml) //下载更新文件失败
	{
		//bool bGetXml = pDlg->GetDownFileList(m_sUpdateXmlUrl);
		bGetXml = pDlg->GetDownFileList(m_sUpdateXmlBackUrl);
	}
	if (!bGetXml) //下载更新文件失败
	{
		//int nRet = MessageBox(NULL,"配置更新失败，请从官网下载更新!","龙马游更新程序",MB_OKCANCEL);
		//if(nRet == IDOK)
		//{
		//	ShellExecute(NULL,TEXT("OPEN"),"http://www.999qp.com",NULL,NULL,SW_NORMAL);
		//}
		//return false;
		CString strExeFile = theApp.m_sLocalPathStart+"LMYLobby.exe";
		WinExec(strExeFile, SW_SHOW);
		if (pDlg!=NULL)
		{
			delete pDlg;
			pDlg = NULL;
		}
		return FALSE;
	}
	else //下载更新文件成功
	{
		if ((pDlg->GetNewXmlVer() <= theApp.m_nPlatVer) || (pDlg->GetDownLoadFlieCount()<=0)) //版本号一致
		{	
			CString strExeFile = theApp.m_sLocalPathStart+"LMYLobby.exe";
			WinExec(strExeFile, SW_SHOW);
			if (pDlg!=NULL)
			{
				delete pDlg;
				pDlg = NULL;
			}
			return FALSE;
		}
	}
	//m_pWnd = pDlg;
	pDlg->Create(IDD_LMYLAUNCHER_DIALOG);
	m_pMainWnd = pDlg; 
	pDlg->ShowWindow(SW_SHOW);
	return TRUE;

	//CLmyLauncherDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
}


//退出函数
INT CLmyLauncherApp::ExitInstance()
{
	//if (m_pWnd!=NULL)
	//{
	//	delete m_pWnd;
	//	m_pWnd = NULL;
	//}
	return __super::ExitInstance();
}

INT CLmyLauncherApp::KillProcess(LPCSTR pszClassName, LPCSTR pszWindowTitle)
{
	HANDLE hProcessHandle; 
	ULONG nProcessID;
	HWND TheWindow;
	TheWindow = ::FindWindow(pszClassName,NULL);
	::GetWindowThreadProcessId( TheWindow, &nProcessID );
	hProcessHandle = ::OpenProcess( PROCESS_TERMINATE, FALSE, nProcessID );
	return ::TerminateProcess( hProcessHandle, 4 );
}
