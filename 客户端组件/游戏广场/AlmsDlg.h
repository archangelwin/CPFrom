#pragma once

#include "Stdafx.h"
// CAlmsDlg 对话框

class CAlmsDlg : public CSkinDialog, public CMissionItem
{
public:
	CAlmsDlg();   // 标准构造函数
	virtual ~CAlmsDlg();

protected:
	CSkinButton						m_btGetAlms;
	CWebPublicize					m_WebPublicize;						//浏览窗口 	
	CMissionManager					m_MissionManager;					//任务管理
	//重画消息
	//VOID OnPaint();
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnBnClickedButtonAlms();

public:
	//连接事件
	virtual bool OnEventMissionLink(INT nErrorCode);
	//关闭事件
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//读取事件
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};
