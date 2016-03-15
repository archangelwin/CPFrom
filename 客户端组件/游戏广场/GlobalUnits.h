#ifndef GLOBAL_UNITES_HEAD_FILE
#define GLOBAL_UNITES_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgDownLoad.h"

//////////////////////////////////////////////////////////////////////////////////

//全局单元
class CGlobalUnits
{
	//系统变量
public:
	//	DWORD								m_dwPlazaVersion;				//大厅版本
	//	TCHAR								m_szDirSkin[MAX_PATH];			//皮肤目录
	TCHAR								m_szDirWork[MAX_PATH];			//工作目录
	CString                             m_sAppPath;         
	//版本信息
protected:
	DWORD							m_dwPlazaVersion;					//大厅版本
	DWORD							m_dwFrameVersion;					//框架版本
	DWORD                           m_dwResouceVersion;                 //资源版本
	DWORD                           m_dwLockCoin;                       //多少币需要绑定本机
//关键字过滤
public:
	CCriticalSection m_CriticalFilter; //关键字锁
	CStringArray m_arrayFitler;	
	CStringArray m_arrayFliterUrl;//判断网址的关键词
	CStringArray m_arrayQQ;//判断QQ 的关键词
	bool ReplaceFitler(CString& sFilterString,int ntype);
	CString OnReplaceQuanBan(CString sResult);
	CString ReplaceFitlerByReturn(CString sFilterString);
	bool InitArrayFitler();
	//组件指针
protected:
	CDlgDownLoad *					m_pDlgDownLoad;						//下载组件

	//静态变量
protected:
	static CGlobalUnits *			m_pGlobalUnits;						//对象指针

	//函数定义
public:
	//构造函数
	CGlobalUnits();
	//析构函数
	virtual ~CGlobalUnits();

	//版本信息
public:
	bool InitGlobalUnits();
	//工作目录
	LPCTSTR GetWorkDirectory() { return m_szDirWork; }
	//大厅版本
	virtual DWORD GetPlazaVersion() { return m_dwPlazaVersion; }
	//框架版本
	virtual DWORD GetFrameVersion() { return m_dwFrameVersion; }
	//资源版本
	virtual DWORD GetResouceVersion() { return m_dwResouceVersion; }
	//资源版本
	virtual void SetResouceVersion(int nNewVer) { m_dwResouceVersion = nNewVer; }
	//资源版本
	virtual DWORD GetLockCoin() { return m_dwLockCoin; }
	//甜饼信息
public:
	//记录甜饼
	bool WriteUserCookie();
	//删除甜饼
	bool DeleteUserCookie();

	//声音函数
public:
	//播放声音
	bool PlayGameSound(LPCTSTR pszSoundName);
	//播放声音
	bool PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName);

	//功能函数
public:
	//下载游戏
	bool DownLoadClient(LPCTSTR pszClientName, WORD wKindID, WORD wServerID,LPCTSTR szProcessName="");

	//静态函数
public:
	//获取对象
	static CGlobalUnits * GetInstance() { return m_pGlobalUnits; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif