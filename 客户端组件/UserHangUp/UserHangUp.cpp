
// UserHangUp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "UserHangUp.h"
#include "UserHangUpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUserHangUpApp

BEGIN_MESSAGE_MAP(CUserHangUpApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUserHangUpApp ����

CUserHangUpApp::CUserHangUpApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUserHangUpApp ����

CUserHangUpApp theApp;


// CUserHangUpApp ��ʼ��

BOOL CUserHangUpApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
// 	CR_INSTALL_INFO info = {0};  
// 	info.cb = sizeof(CR_INSTALL_INFO); 
// 	info.pszAppName = TEXT("UserHangUp"); 
// 	info.pszAppVersion = TEXT("2.0.1");     
// 	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;  
// 	info.dwFlags |= CR_INST_DONT_SEND_REPORT;  
// 	info.dwFlags |= CR_INST_NO_GUI;
// 	info.pszErrorReportSaveDir = TEXT("./HUPErrReport");  
// 
// 	// Install crash handlers
// 	int nInstResult = crInstall(&info);            
// 	//assert(nInstResult==0);
// 	if(nInstResult!=0)
// 	{
// 		TCHAR buff[256];
// 		crGetLastErrorMsg(buff, 256); // Get last error
// 		_tprintf(_T("%s\n"), buff); // and output it to the screen
// 		return 1;
// 	}

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

	CUserHangUpDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
