
// LmyLauncher.cpp : ����Ӧ�ó��������Ϊ��
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


// CLmyLauncherApp ����

CLmyLauncherApp::CLmyLauncherApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_nPlatVer = 0;
	//m_pWnd = NULL;
}


// Ψһ��һ�� CLmyLauncherApp ����

CLmyLauncherApp theApp;


// CLmyLauncherApp ��ʼ��

BOOL CLmyLauncherApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//�����ж�
	bool bDownExist=false;
	bool bPlazaExist = false;
	CMutex Mutex(FALSE,"LmyDownload",NULL);
	if (Mutex.Lock(0)==FALSE) 
		bDownExist=true;
	//�������
	if (bDownExist==true) 
		return FALSE;
	//��������

	CWnd * pWndGamePlaza=CWnd::FindWindow("LMYGAME",NULL);
	if (pWndGamePlaza!=NULL) 
	{
		//���ñ���
		bPlazaExist=true;
		if (MessageBox(NULL,"��⵽�����������У����ȹرմ���!","�����θ��³���",MB_OKCANCEL) == IDOK) 
		{
			HANDLE hProcessHandle; 
			ULONG nProcessID;		

			::GetWindowThreadProcessId(pWndGamePlaza->GetSafeHwnd(), &nProcessID );
			hProcessHandle = ::OpenProcess(PROCESS_TERMINATE, FALSE, nProcessID );
			::TerminateProcess( hProcessHandle, 4 );
		}
		else
		{
			//��ԭ����
			if (pWndGamePlaza->IsIconic()) 
			{
				pWndGamePlaza->ShowWindow(SW_RESTORE);
			}
			//�����
			pWndGamePlaza->SetActiveWindow();
			pWndGamePlaza->BringWindowToTop();
			pWndGamePlaza->SetForegroundWindow();
			//�����Լ�
			return false;
		}		
	}


	CString tempstr;
	char path[500] = {0};				
	::GetModuleFileName(NULL, path, 499);
	CString sTmpPaths = path;							
	CString sLocalPaths = sTmpPaths.Mid(0, sTmpPaths.ReverseFind('\\') + 1);
	m_sLocalPathStart  =  sLocalPaths;

	//����·��
	TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
	_snprintf_s(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s%s"),theApp.m_sLocalPathStart,UPDATE_INFO_FILE);

	//��ȡ����
	m_nPlatVer =GetPrivateProfileInt(TEXT("VerInfo"),TEXT("PVer"),0,szServerInfoPath);
	//��������
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//ע�ᴰ��
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
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}

	//return false;


	//��������
	CString m_sUpdateXmlUrl = "http://download.999qp.com/AutoUpdate/update.xml";  //����ʱ�޸�
	CString m_sUpdateXmlBackUrl = "http://download.999xw.com/AutoUpdate/update.xml"; //����ʱ�޸�
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
	if (!bGetXml) //���ظ����ļ�ʧ��
	{
		//bool bGetXml = pDlg->GetDownFileList(m_sUpdateXmlUrl);
		bGetXml = pDlg->GetDownFileList(m_sUpdateXmlBackUrl);
	}
	if (!bGetXml) //���ظ����ļ�ʧ��
	{
		//int nRet = MessageBox(NULL,"���ø���ʧ�ܣ���ӹ������ظ���!","�����θ��³���",MB_OKCANCEL);
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
	else //���ظ����ļ��ɹ�
	{
		if ((pDlg->GetNewXmlVer() <= theApp.m_nPlatVer) || (pDlg->GetDownLoadFlieCount()<=0)) //�汾��һ��
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
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
}


//�˳�����
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
