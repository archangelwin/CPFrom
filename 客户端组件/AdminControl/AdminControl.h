
// AdminControl.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
// #include "MissionManager.h"
#include "MissionLogon.h"
#include "PlatformEvent.h"
#include "AdminControlDlg.h"
#include "MissionUserInfo.h"
#include "Stdafx.h"
// CAdminControlApp:
// 有关此类的实现，请参阅 AdminControl.cpp
//
class CMyFrameWnd;


class CAdminControlApp : public CWinAppEx
{
public:
	CAdminControlApp();
	~CAdminControlApp();

// 重写
public:
	CMyFrameWnd* m_pMyFrameWnd;

//	CMissionList					m_MissionList;						//列表任务
//	CMissionLogon					m_MissionLogon;						//登录任务
//	CMissionManager					m_MissionManager;					//任务管理
	CPlatformEvent					m_PlatformEvent;

	CParameterGlobal				m_ParameterGlobal;					//全局配置
	CGlobalUserInfo					m_GlobalUserInfo;					//用户信息
	//资源组件
public:
	CSkinRenderManager				m_SkinRenderManager;				//渲染管理
	CSkinResourceManager			m_SkinResourceManager;

	virtual BOOL InitInstance();


// 实现

	DECLARE_MESSAGE_MAP()
};

extern CAdminControlApp theApp;


//窗口类继承  
class CMyFrameWnd : public CFrameWnd  
{  
public:  
	CMyFrameWnd();  
	~CMyFrameWnd();  
	//任务组件
protected:
	CMissionList                    m_MissionList;						//游戏列表
	CMissionLogon					m_MissionLogon;						//登录任务
	CMissionUserInfo                m_MissionUserInfo;                  //用户信息
	CMissionManager					m_MissionManager;					//任务管理
public:
	//控制按钮
public:
	CButton						m_btMin;							//最小按钮
	CButton						m_btMax;							//最大按钮
	CButton						m_btClose;							//关闭按钮
	//界面变量
protected:
	bool							m_bMaxShow;							//最大标志
	bool							m_bRectify;							//调整标志
	CRect							m_rcNormalSize;						//正常位置
	DWORD                           m_dwAllOnLineCount;                 //总在线人数

	//控件变量
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件
protected:
	CAdminControlDlg                m_PlazaViewItem;
//	CGameUserListDlg*               m_pGameUserListDlg;
	//静态变量
protected:
	static CMyFrameWnd *			m_pPlatformFrame;					//框架指针

	//功能函数
public:
	//更新总在线人数
	void UpDataAllOnLineCount();
	//获取总在线人数
	DWORD GetAllOnLineCount();
	//界面函数
protected:
	//还原窗口
	bool RestoreWindow();
	//最大窗口
	bool MaxSizeWindow();
private:
private:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);
protected:
	afx_msg	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);
	//功能函数
public:
	//获取实例
	static CMyFrameWnd * GetInstance() { return m_pPlatformFrame; }
protected:
	//消息过虑
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
protected:
protected:
	//关闭消息
	VOID OnClose();
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//位置消息
	VOID OnGetMinMaxInfo(MINMAXINFO * lpMMI);
	//创建消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDblClk(UINT nFlags, CPoint Point);
	//消息函数
protected:
	//消息函数
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:  
	DECLARE_MESSAGE_MAP();  
};  