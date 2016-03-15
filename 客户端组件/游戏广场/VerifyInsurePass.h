#pragma once

#include "Stdafx.h"
// CVerifyInsurePass 对话框

class CVerifyInsurePass : public CSkinDialog, public CMissionItem
{

public:
	CVerifyInsurePass();   // 标准构造函数
	virtual ~CVerifyInsurePass();

protected:	
	TCHAR							m_szInsurePassword[LEN_PASSWORD];			//保险柜密码
	int                             m_nSavePwdType;
	int                             m_nSaveMinute;

protected:
	CSkinButton						m_btVerifyInsurePass;               //验证密码
	CPasswordControl				m_PasswordControl;					//用户密码
	CSkinComboBox					m_ComMinutes;					    //分钟数

	CSkinHyperLink					m_VerifyPassTitle;					//抬头
	CSkinHyperLink					m_PassText;					//抬头
	CSkinHyperLink					m_GetInsurePwd;						    //找回密码
	CSkinHyperLink					m_VerifyMinute;					//分钟数
	CSkinHyperLink					m_VerifyQQtip;					//qq登录

	CMissionManager					m_MissionManager;					//任务管理
	//重画消息
	//VOID OnPaint();
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnBnClickedButtonVerifyPass();
	afx_msg void OnBnClickedForgetInsure();

public:
	//连接事件
	virtual bool OnEventMissionLink(INT nErrorCode);
	//关闭事件
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//读取事件
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()
};
