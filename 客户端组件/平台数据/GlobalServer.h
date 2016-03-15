#ifndef GLOBAL_SERVER_HEAD_FILE
#define GLOBAL_SERVER_HEAD_FILE

#pragma once

#include "PlatformDataHead.h"

//////////////////////////////////////////////////////////////////////////////////

//地址信息
struct tagServerItem
{
	WORD							wServerPort;						//服务端口
	DWORD							dwServerAddr;						//服务地址
	TCHAR							szServerHost[LEN_SERVER];			//域名信息
};

//////////////////////////////////////////////////////////////////////////////////

//全局服务器
class PLATFORM_DATA_CLASS CGlobalServer
{
protected:
	CString m_strAppPath;                                        //启动路径
	CString m_strProduct;			   //产品名字（任务栏显示的）
	CString m_strProductClass;			           //广场类名
	CString m_strProductKey;	       //产品主键

	//地址定义
	CString m_strQQUrl;		                    //QQ链接
	CString m_strLogonServer;		            //登录地址
	CString m_strCookieServer;	                //记录地址
	CString m_strPlatformLink;	                //平台网站
	CString m_strWebPostServer;		            //webPost地址
	CString m_strZipPostServer;		            //webPost地址
	CString m_sDownLowdServer;                  //下载地址
	CString m_sPayServer;                       //充值地址
	int m_nWebPostPort;                         //post端口
	bool m_bHaveQQLogon;
	bool m_bGameLevel;                          //显示等级
	//函数定义
public:
	//构造函数
	CGlobalServer();
	//析构函数
	virtual ~CGlobalServer();

protected:
	static CGlobalServer *		m_pGlobalServer;						//平台信息

	//全局信息
public:
	//子项数目
	WORD GetItemCount();

	//上次登录
public:
	//上次登录
	VOID SetLastServerName(LPCTSTR pszLastServer);
	//上次登录
	VOID GetLastServerName(TCHAR szLastServer[LEN_SERVER]);
	//获取平台信息
    UINT GetPlatInfo(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault);
	//子项信息
public:
	//子项名字
	VOID GetServerItemName(WORD wIndex, TCHAR szResult[LEN_SERVER]);
	//子项信息
	bool GetServerItemInfo(LPCTSTR pszServerName, tagServerItem & ServerItem);

	//写入函数
protected:
	//读取数值
	VOID WriteFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nValue);
	//写入数据
	VOID WriteFileString(LPCTSTR pszKeyName, LPCTSTR pszItemName, LPCTSTR pszString);

	//读取函数
public:
	//读取数值
	UINT ReadFileValue(LPCTSTR pszKeyName, LPCTSTR pszItemName, UINT nDefault);
	//读取数据
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

	//静态函数
public:
	//获取对象
	static CGlobalServer * GetInstance() { return m_pGlobalServer; }

};

//////////////////////////////////////////////////////////////////////////////////

#endif