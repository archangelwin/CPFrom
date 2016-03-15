#ifndef DLG_LOCK_MACHINE_HEAD_FILE
#define DLG_LOCK_MACHINE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//锁机设置
class CDlgLockMachine : public CSkinDialog, public CMissionItem
{
	//变量定义
protected:
	BYTE							m_cbMachine;						//绑定标志
	TCHAR							m_szPassword[LEN_PASSWORD];			//用户密码
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];	//证件号码
	TCHAR							m_szCompellation[LEN_COMPELLATION];	//真实名字
	TCHAR							m_szPassword2[LEN_PASSWORD];			//用户密码
    int                             m_nType;                            //0绑定机器，1绑定身份证
	bool                            m_bShowPassportID;                  //是否显示身份证

	//控件变量
protected:
	CSkinButton						m_btOk;								//确定按钮
	CSkinButton						m_btCancel;							//取消按钮

	CSkinButton						m_btPassID;							//绑定身份证
	CSkinButton                     m_btPasswordProtect;                //申请密码保护
	CPasswordControl				m_PasswordControl;					//用户密码

	CSkinHyperLink                  m_cTitlePC;
	CSkinHyperLink                  m_cPWD;
	CSkinHyperLink                  m_cTitlePassID;
	CSkinHyperLink                  m_cPassName;
	CSkinHyperLink                  m_cPassID;
	CSkinHyperLink                  m_cTitleValidate;
	CSkinHyperLink                  m_cPWD2;
	CSkinHyperLink                  m_cPidRemark;
	CSkinHyperLink                  m_cInsurePwdQQ;
	CSkinHyperLink                  m_cApplyProtectRemark;              //密码保护提醒
	CPasswordControl				m_PasswordControl2;					//用户密码

	CSkinEdit						m_edName;						     //姓名
	CSkinEdit						m_edPassID;						     //身份证号
	CWebPublicize					m_WebPublicize;						//浏览窗口	

	CPngImageSB                       m_ImageMachine;                       //绑定图片
	CPngImageSB                       m_ImagePassID;                       //身份证图片

	//组件变量
protected:
	CMissionManager					m_MissionManager;					//任务管理

	//函数定义
public:
	//构造函数
	CDlgLockMachine();
	//析够函数
	virtual ~CDlgLockMachine();

	//重载函数
protected:
	//重画消息
	VOID OnPaint();
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
	afx_msg void OnBnClickedButtonPassID();
	afx_msg void OnBnClickedButtonPasswordProtect();
	//重载函数
public:
	//连接事件
	virtual bool OnEventMissionLink(INT nErrorCode);
	//关闭事件
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//读取事件
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif