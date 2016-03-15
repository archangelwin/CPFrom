#ifndef GLOBAL_SERVER_HEAD_FILE
#define GLOBAL_SERVER_HEAD_FILE

#pragma once

#include "PlatformDataHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��ַ��Ϣ
struct tagServerItem
{
	WORD							wServerPort;						//����˿�
	DWORD							dwServerAddr;						//�����ַ
	TCHAR							szServerHost[LEN_SERVER];			//������Ϣ
};

//////////////////////////////////////////////////////////////////////////////////

//ȫ�ַ�����
class PLATFORM_DATA_CLASS CGlobalServer
{
protected:
	CString m_strAppPath;                                        //����·��
	CString m_strProduct;			   //��Ʒ���֣���������ʾ�ģ�
	CString m_strProductClass;			           //�㳡����
	CString m_strProductKey;	       //��Ʒ����

	//��ַ����
	CString m_strQQUrl;		                    //QQ����
	CString m_strLogonServer;		            //��¼��ַ
	CString m_strCookieServer;	                //��¼��ַ
	CString m_strPlatformLink;	                //ƽ̨��վ
	CString m_strWebPostServer;		            //webPost��ַ
	CString m_strZipPostServer;		            //webPost��ַ
	CString m_sDownLowdServer;                  //���ص�ַ
	CString m_sPayServer;                       //��ֵ��ַ
	int m_nWebPostPort;                         //post�˿�
	bool m_bHaveQQLogon;
	bool m_bGameLevel;                          //��ʾ�ȼ�
	//��������
public:
	//���캯��
	CGlobalServer();
	//��������
	virtual ~CGlobalServer();

protected:
	static CGlobalServer *		m_pGlobalServer;						//ƽ̨��Ϣ

	//ȫ����Ϣ
public:
	//������Ŀ
	WORD GetItemCount();

	//�ϴε�¼
public:
	//�ϴε�¼
	VOID SetLastServerName(LPCTSTR pszLastServer);
	//�ϴε�¼
	VOID GetLastServerName(TCHAR szLastServer[LEN_SERVER]);
	//��ȡƽ̨��Ϣ
    UINT GetPlatInfo(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault);
	//������Ϣ
public:
	//��������
	VOID GetServerItemName(WORD wIndex, TCHAR szResult[LEN_SERVER]);
	//������Ϣ
	bool GetServerItemInfo(LPCTSTR pszServerName, tagServerItem & ServerItem);

	//д�뺯��
protected:
	//��ȡ��ֵ
	VOID WriteFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nValue);
	//д������
	VOID WriteFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, LPCTSTR pszString);

	//��ȡ����
public:
	//��ȡ��ֵ
	UINT ReadFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault);
	//��ȡ����
	CString ReadFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, TCHAR szResult[], WORD wMaxCount,bool bCrevasse = TRUE);
	CString ReadPlatFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, TCHAR szResult[], WORD wMaxCount,bool bCrevasse = TRUE);
public:
	void InitPlatInfo();
	CString GetAppPath(){return m_strAppPath;};
	CString GetPlatformProduct(int nType);
	CString GetPlatformServer(int nType);
	int GetPostPort(){return m_nWebPostPort;};
	bool BHaveQQLogon(){return m_bHaveQQLogon;};
	CString GetQQLogonUrl(){return m_strQQUrl;};
	bool BShowGameLevel(){return m_bGameLevel;};

	//��̬����
public:
	//��ȡ����
	static CGlobalServer * GetInstance() { return m_pGlobalServer; }

};

//////////////////////////////////////////////////////////////////////////////////

#endif