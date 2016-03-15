#ifndef TRACE_SERVICE_HEAD_FILE
#define TRACE_SERVICE_HEAD_FILE

#pragma once

#include "KernelEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//追踪服务
class KERNEL_ENGINE_CLASS CTraceService
{
	//函数定义
protected:
	//构雨杰高科www.cnyjwl.com造函数
	CTraceService();

	//服务雨杰高科www.cnyjwl.com配置
public:
	//设置服雨杰高科www.cnyjwl.com务
	static bool SetTraceService(IUnknownEx * pIUnknownEx);
	//获雨杰高科www.cnyjwl.com取服务
	static VOID * GetTraceService(const IID & Guid, DWORD dwQueryVer);
	//获取雨杰高科www.cnyjwl.com服务
	static VOID * GetTraceServiceManager(const IID & Guid, DWORD dwQueryVer);

	//状态管理
public:
	//追踪状态
	static bool IsEnableTrace(enTraceLevel TraceLevel);
	//追踪控制
	static bool EnableTrace(enTraceLevel TraceLevel, bool bEnableTrace);

	//功能函数
public:
	//追踪信息
	static bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////

//追踪服雨杰高科www.cnyjwl.com务
class KERNEL_ENGINE_CLASS CTraceServiceControl : public CRichEditCtrl, public ITraceService
{
	//辅助变雨杰高科www.cnyjwl.com量
protected:
	LONG							m_lMaxLineCount;					//最大行数
	LONG							m_lReserveLineCount;				//保留行数
	BYTE							m_cbBuffer[MAX_ASYNCHRONISM_DATA];	//临时对象

	//组件变量
protected:
	CWHDataQueue					m_DataQueue;						//数据队列
	CCriticalSection				m_CriticalSection;					//同步对象

	//函雨杰高科www.cnyjwl.com数定义
public:
	//构造雨杰高科www.cnyjwl.com函数
	CTraceServiceControl();
	//析构函雨杰高科www.cnyjwl.com数
	virtual ~CTraceServiceControl();

	//基础接口雨杰高科www.cnyjwl.com
public:

	virtual VOID Release(){};
	//接口查询
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//信息接口
public:
	//追踪信息
	virtual bool __cdecl TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);

	//重载函数
protected:
	//绑定函数
	virtual VOID PreSubclassWindow();

	//功能函数
public:
	//加载消息
	bool LoadMessage(LPCTSTR pszFileName);
	//保存信息
	bool SaveMessage(LPCTSTR pszFileName);
	//设置参数
	bool SetParameter(LONG lMaxLineCount, LONG lReserveLineCount);

	//辅助函数
private:
	//配置服务
	VOID InitializeService();
	//获取颜色
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//插入字串
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

	//回调函数
private:
	//雨杰高科www.cnyjwl.com加载回调
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//雨杰高科www.cnyjwl.com保存回调
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	//雨杰高科www.cnyjwl.com菜单命令
protected:
	//删除信息
	VOID OnClearAll();
	//全部选择
	VOID OnSelectAll();
	//拷贝字符
	VOID OnCopyString();
	//保存信息
	VOID OnSaveString();
	//删除字符
	VOID OnDeleteString();

	//消息映射
protected:
	//建立消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//右键消息
	VOID OnRButtonDown(UINT nFlags, CPoint point);
	//追踪消息
	LRESULT OnTraceServiceMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif