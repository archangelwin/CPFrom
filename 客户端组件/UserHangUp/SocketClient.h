#pragma once

#include "GameInfo.h"

#define WM_LOGON_SUCCESS               WM_USER+200
#define WM_LOGON_FAILURE               WM_USER+201
#define WM_LOGON_BREAK                 WM_USER+203
#define WM_LOGON_CONNECTING            WM_USER+202
#define WM_GAMEINFO_UPDATE             WM_USER+205

#define WM_THREAD_QUIT                 WM_USER+204

//检测结构信息
struct CMD_KN_DetectSocket
{
	DWORD								dwSendTickCount;					//发送时间
	DWORD								dwRecvTickCount;					//接收时间
};



class CSocketClient:public ITCPSocketSink , public CWnd
{
public:
	CSocketClient(void);
	~CSocketClient(void);

	virtual VOID Release(){delete this;};

	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	CTCPSocketHelper				m_TCPSocketModule;					//网络连接
	HWND                            m_hWnd;

	DWORD                           m_dwIPAddress;
	TCHAR							m_szCustomServer[LEN_SERVER];		//指定地址
	WORD							m_wCurrentPort;						//当前端口
	WORD                            m_wKindID;
	DWORD                           m_UserID;
	DWORD                           m_wProcessVersion;
	CString                         m_wPassWord;
	bool                            m_IsConnect;
	bool                            m_IsThreadStart;

	bool                            m_IsBkConnect;
	DWORD                           m_dwBackAddress;
	WORD                            m_dwBackPort;

	DWORD                           m_SendTickCount;
	DWORD                           m_RecvTickCount;

	WORD                            m_PlazaPort;

	bool                            m_IsPlazaLogon;

	GameInfo                        m_GameInfoDB;

	//网络接口
protected:
	//连接事件
	virtual bool OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool OnEventTCPSocketRead(WORD wSocketID, TCP_Command Command, VOID * pData, WORD wDataSize);

public:
	bool OnSocketConnect(DWORD sIP,WORD sPort);

	VOID OnCloseThread();

	bool OnChangeConnect();

	void OnPlazzConnect();


	DECLARE_MESSAGE_MAP()
};
