#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerControl.h"
#include "AccountsControl.h"
#include "PlatformPublicize.h"
#include "GetFilter.h"
#include "DlgQQLogon.h"
//////////////////////////////////////////////////////////////////////////////////

//登录方式
#define LOGON_BY_GAME_ID			1									//I D 登录
#define LOGON_BY_ACCOUNTS			0									//帐号登录

#define LOGON_ACCOUNT_NORMAL        0                                   //普通账号
#define LOGON_ACCOUNT_QQ            1                                   //普通账号


//////////////////////////////////////////////////////////////////////////////////

//账号信息
struct tagAccountsInfo
{
	DWORD							dwUserID;							//用户标识
	TCHAR							szGameID[16];						//游戏标识
	TCHAR							szAccounts[LEN_ACCOUNTS];			//登录账号
	TCHAR							szPassword[LEN_PASSWORD];			//登录密码
	BYTE                            cbAccountType;                      //账号类型 0普通，1qq
};

//数组定义
typedef CWHArray<tagAccountsInfo *>	CAccountsInfoArray;					//账号数组

//////////////////////////////////////////////////////////////////////////////////

//登录窗口
class CDlgLogon : public CDialog
{
	friend class CGetFilter;
	//配置变量
public:
	BYTE							m_cbLogonMode;						//登录模式
	BYTE							m_cbRemPassword;					//记住密码
	BYTE                            m_cbAccountType;                    //账号类型 0 普通，1qq
	bool                            m_bCanOpenMobileBind;               //是否可以打开自助解绑
	bool                            m_bCanOpenGetPwd;                  //是否可以打开找回密码
	bool                            m_bShowRegTip;                     //注册tip
	//登录信息
public:
	DWORD							m_dwGameID;							//游戏 I D
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//游戏帐号【登陆成功】
	TCHAR							m_szPassword[LEN_PASSWORD];			//用户密码
	TCHAR							m_szLogonServer[LEN_SERVER];		//登录地址

	CString                         m_sLogonAccount;                    //游戏账号【未登陆】

	//控件变量
protected:
//	CSkinButton						m_btHelp;						    //帮助按钮
	CSkinButton						m_btQuit;							//退出按钮
	CSkinButton						m_btEnter;							//登录按钮
	CSkinButton						m_btOption;							//设置按钮
	CSkinButton						m_btRegister;						//注册按钮
	CSkinButton						m_btQQ;					            //qq登录
	CSkinCheckBox                   m_cbRemPwd;
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件
	//帐号控件
protected:
	CAccountsCtrl					m_GameIDControl;					//登录 I D
	CAccountsCtrl					m_AccountsControl;					//登录帐号

protected:
	CGetFilter  cfilter;
	//按钮控件
protected:
	CSkinHyperLink					m_Unbundling;						//解除绑定
	CSkinHyperLink					m_btDeleteRecord;					//删除记录
	CSkinHyperLink					m_GetPwd;						    //找回密码
    CSkinHyperLink                  m_RemPwd;                           //记住密码 
	CSkinButton						m_btLogonLink3;						//连接按钮
	CSkinButton						m_btLogonLink4;						//连接按钮

	//特殊控件
protected:
	CSkinTabCtrl					m_TabControl;						//登录模式
	CServerControl					m_ServerControl;					//登录地址
	CPasswordControl				m_PasswordControl;					//用户密码

	//界面控件
protected:
	CBrush							m_brBrush;							//背景画刷
	CSkintDPI                       m_SkinDPI;                          //设置DPI
	CSkinLayered					m_SkinLayered;						//分层窗口
	CPlatformPublicize				m_PlatformPublicize;				//浏览控件

	CDlgQQLogon                    *m_pQQRegDialog;//QQ登录框 

	//变量定义
protected:
	CAccountsInfoArray				m_AccountsInfoArray;				//账号信息

	//函数定义
public:
	//构造函数
	CDlgLogon();
	//析构函数
	virtual ~CDlgLogon();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
	//取消消息
	virtual VOID OnCancel();

	//功能函数
public:
	//构造数据
	WORD ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags,int nValidateType = 0,CString sCode = "",int LogonMode = -1);

	//辅助函数
private:
	//获取信息
	bool GetInformation();
	VOID LoadServerResouce();
	//加载账号
	VOID LoadAccountsInfo();
	//地址信息
	VOID LoadLogonServerInfo();

	//连接按钮
protected:
	//手机解绑
	VOID OnBnClickedUnbundling();
	//找回密码
	VOID OnBnClickedGetPwd();
	//记住密码
	VOID OnBnClickedRemPwd();
	//连接按钮
	VOID OnBnClickedLogonLink4();

	//按钮消息
protected:
	//注册帐号
	VOID OnBnClickedRegister();
	//网络设置
	VOID OnBnClickedProxyConfig();
	//删除记录
	VOID OnBnClickedDeleteRecord();
	//qq登录
	VOID OnBnClickedQQ();

	//控件函数
protected:
	//选择改变
	VOID OnSelchangeGameID();
	//选择改变
	VOID OnSelchangeAccounts();
	//编辑改变
	VOID OnCbnEditchangeAccounts();
	//类型改变
	VOID OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult);

	//系统消息
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//控件颜色
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	//尺寸变化
	VOID OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUpdateResouce(WPARAM wParam, LPARAM lPara);
	afx_msg LRESULT OnQQLogin(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif