#ifndef WH_SERVICE_HEAD_FILE
#define WH_SERVICE_HEAD_FILE

#pragma once

#include "ServiceCoreHead.h"

//////////////////////////////////////////////////////////////////////////////////

//ϵͳ����
class SERVICE_CORE_CLASS CWHService
{
	//��������
private:
	//���캯��
	CWHService();

	//ϵͳ����
public:
	//�����ַ�
	static bool SetClipboardString(LPCTSTR pszString);

	//������ʶ
public:
	//������ʶ
	static bool GetMachineID(TCHAR szMachineID[LEN_MACHINE_ID]);
	//������ʶ
	static bool GetMachineIDEx(TCHAR szMachineID[LEN_MACHINE_ID]);
	//������ַ
	static bool GetMACAddress(TCHAR szMACAddress[LEN_NETWORK_ID]);

	//ϵͳ�ȼ�
public:
	//ע���ȼ�
	static bool UnRegisterHotKey(HWND hWnd, UINT uKeyID);
	//ע���ȼ�
	static bool RegisterHotKey(HWND hWnd, UINT uKeyID, WORD wHotKey);

	//ϵͳ�ļ�
public:
	//����Ŀ¼
	static bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount);
	//��ԴĿ¼
	static VOID GetGameResDirectory(tagGameKind &GameKind,TCHAR szResDirectory[], WORD wBufferCount);
	//�ļ��汾
	static bool GetModuleVersion(LPCTSTR pszModuleName, DWORD & dwVersionInfo);

	//ѹ������
public:
	//ѹ������
	static ULONG CompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize);
	//��ѹ����
	static ULONG UnCompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize);
public:
	static HINSTANCE GotoURL(LPCTSTR url, int showcmd);
	static LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
public:
	static bool BAllNumber(LPCTSTR pszNumString);
	static VOID HtmlFilter(CString &sContent);
	static bool Post(CString& csResponse,//����,���������Ҫ��
		const char *szServer,//������
		WORD& nPort,//�˿�
		const char* szObject,//URI
		const char *szData, //��������
		DWORD& dwHttpStatus,//״̬��
		BOOL bAutoRedirect);//�Ƿ��Զ�ת��
};

//////////////////////////////////////////////////////////////////////////////////

#endif