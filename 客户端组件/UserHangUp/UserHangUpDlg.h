
// UserHangUpDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SocketClient.h"
#include "GameSQLite.h"
#include "GameInfo.h"


#define  PLAZALOHON       100
//检测结构信息
// struct CMD_KN_DetectSocket
// {
// 	DWORD								dwSendTickCount;					//发送时间
// 	DWORD								dwRecvTickCount;					//接收时间
// };

struct stgUserInfo
{
	CString UserID;
	CString PassWord;
	CString GameID;
	CString Port;
	CString Version;
	CString GameName;
};

//数组说明
typedef CMap<WORD,WORD,WORD,WORD>	CKindIDMap;							//类型标识
typedef CWHArray<CSocketClient * >   CSocketClientArry;

typedef CWHArray<stgUserInfo*>  CAllUserInfo;

// CUserHangUpDlg 对话框
class CUserHangUpDlg : public CDialog /*, public ITCPSocketSink*/
{
// 构造
public:
	CUserHangUpDlg(CWnd* pParent = NULL);	// 标准构造函数

	//析构函数
	virtual ~CUserHangUpDlg();
// 对话框数据
	enum { IDD = IDD_USERHANGUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 	virtual VOID Release(){delete this;};
// 
// 	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//变量定义
protected:
//	bool							m_bUpdateOnLine;					//更新人数
//	CKindIDMap						m_KindIDMission;					//游戏标识
//	CKindIDMap						m_KindIDPending;					//待决标识

	GameInfo                        m_GameInfo;
	CAllUserInfo                    m_AllUserInfo;


// 	//网络接口
// protected:
// 	//连接事件
// 	virtual bool OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
// 	//关闭事件
// 	virtual bool OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
// 	//读取事件
// 	virtual bool OnEventTCPSocketRead(WORD wSocketID, TCP_Command Command, VOID * pData, WORD wDataSize);
public:
	bool OnConnectServer();

	void OnReSetArray();

	bool OnReConnect(DWORD UserID);

	CString GetModuleDir();

	void OnOpenAddressFile();

	VOID OnGetDataBase();

	void OnGetGameList();

	void OnInsertList();

	void OnPlazzConnection();


	WORD OnLogonPacket(BYTE cbBuffer[], WORD wBufferSize);

	bool OnSocketLogonFinish(VOID * pData, WORD wDataSize);

	bool OnSocketLogonSuccess(VOID * pData, WORD wDataSize);

	

protected:

	LRESULT OnLogonSuccess(WPARAM wParam, LPARAM lParam);

	LRESULT OnLogonFailure(WPARAM wParam, LPARAM lParam);
	
	LRESULT OnSocketLogonBreak(WPARAM wParam, LPARAM lParam);

	LRESULT OnAllThreadQuit(WPARAM wParam, LPARAM lParam);

	LRESULT OnGameInfoUpdate(WPARAM wParam, LPARAM lParam);
// 实现
protected:
	HICON m_hIcon;
	CString sName,sPwd,sKindID,sProcessVersion,sPort,sGameName;

public:
	DWORD                           m_dwIPAddress;
	CString                         m_IPAddress;
	TCHAR							m_szCustomServer[LEN_SERVER];		//指定地址
	TCHAR							m_szBkCustomServer[LEN_SERVER];		//指定地址
	WORD							m_wCurrentPort;						//当前端口
	CSocketClientArry               m_SocketArray;

	DWORD                           m_dwBackAddress;
	WORD                            m_dwBackPort;

	int                             m_ArrayIndex;

public:
	BOOL bIsConnected;
	CTCPSocketHelper				m_TCPSocketModule;					//网络连接
	WORD                            m_nSocketID;
	CSocketClient*                   m_SocketClient;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenFile();
	CListCtrl m_List;
	CIPAddressCtrl m_AddressCtrl;
	CEdit m_Port;
	afx_msg void OnBnClickedConnect();
	CEdit m_IP;
	afx_msg void OnBnClickedButton1();

	//时间消息
	VOID OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedConnectSet();
	CEdit m_BkIP;
	afx_msg void OnBnClickedChangeConnect();
	CButton m_BtConnect;
	CButton m_BtChangeConnect;
	CButton m_BtOpenFile;
	CComboBox m_CombGame;
	afx_msg void OnBnClickedAddUser();
	CEdit m_EDUserID;
	CEdit m_EDPassword;
	afx_msg void OnBnClickedDELUser();
	afx_msg void OnBnClickedAddGame();
	CEdit m_EDGameName;
	CEdit m_EDGameID;
	CEdit m_EDPort;
	CEdit m_EDVersion;
	afx_msg void OnBnClickedDelGame();
	CComboBox m_CombGameInfoList;
	afx_msg void OnCbnEditupdateCombo2();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedUpdateGameInfo();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedChangeUserInfo();
	CComboBox m_ComboAccount;
	afx_msg void OnCbnSelchangeComboAccount();
	afx_msg void OnBnClickedButton11();
};
