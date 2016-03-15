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

//��¼��ʽ
#define LOGON_BY_GAME_ID			1									//I D ��¼
#define LOGON_BY_ACCOUNTS			0									//�ʺŵ�¼

#define LOGON_ACCOUNT_NORMAL        0                                   //��ͨ�˺�
#define LOGON_ACCOUNT_QQ            1                                   //��ͨ�˺�


//////////////////////////////////////////////////////////////////////////////////

//�˺���Ϣ
struct tagAccountsInfo
{
	DWORD							dwUserID;							//�û���ʶ
	TCHAR							szGameID[16];						//��Ϸ��ʶ
	TCHAR							szAccounts[LEN_ACCOUNTS];			//��¼�˺�
	TCHAR							szPassword[LEN_PASSWORD];			//��¼����
	BYTE                            cbAccountType;                      //�˺����� 0��ͨ��1qq
};

//���鶨��
typedef CWHArray<tagAccountsInfo *>	CAccountsInfoArray;					//�˺�����

//////////////////////////////////////////////////////////////////////////////////

//��¼����
class CDlgLogon : public CDialog
{
	friend class CGetFilter;
	//���ñ���
public:
	BYTE							m_cbLogonMode;						//��¼ģʽ
	BYTE							m_cbRemPassword;					//��ס����
	BYTE                            m_cbAccountType;                    //�˺����� 0 ��ͨ��1qq
	bool                            m_bCanOpenMobileBind;               //�Ƿ���Դ��������
	bool                            m_bCanOpenGetPwd;                  //�Ƿ���Դ��һ�����
	bool                            m_bShowRegTip;                     //ע��tip
	//��¼��Ϣ
public:
	DWORD							m_dwGameID;							//��Ϸ I D
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//��Ϸ�ʺš���½�ɹ���
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	TCHAR							m_szLogonServer[LEN_SERVER];		//��¼��ַ

	CString                         m_sLogonAccount;                    //��Ϸ�˺š�δ��½��

	//�ؼ�����
protected:
//	CSkinButton						m_btHelp;						    //������ť
	CSkinButton						m_btQuit;							//�˳���ť
	CSkinButton						m_btEnter;							//��¼��ť
	CSkinButton						m_btOption;							//���ð�ť
	CSkinButton						m_btRegister;						//ע�ᰴť
	CSkinButton						m_btQQ;					            //qq��¼
	CSkinCheckBox                   m_cbRemPwd;
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�
	//�ʺſؼ�
protected:
	CAccountsCtrl					m_GameIDControl;					//��¼ I D
	CAccountsCtrl					m_AccountsControl;					//��¼�ʺ�

protected:
	CGetFilter  cfilter;
	//��ť�ؼ�
protected:
	CSkinHyperLink					m_Unbundling;						//�����
	CSkinHyperLink					m_btDeleteRecord;					//ɾ����¼
	CSkinHyperLink					m_GetPwd;						    //�һ�����
    CSkinHyperLink                  m_RemPwd;                           //��ס���� 
	CSkinButton						m_btLogonLink3;						//���Ӱ�ť
	CSkinButton						m_btLogonLink4;						//���Ӱ�ť

	//����ؼ�
protected:
	CSkinTabCtrl					m_TabControl;						//��¼ģʽ
	CServerControl					m_ServerControl;					//��¼��ַ
	CPasswordControl				m_PasswordControl;					//�û�����

	//����ؼ�
protected:
	CBrush							m_brBrush;							//������ˢ
	CSkintDPI                       m_SkinDPI;                          //����DPI
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	CPlatformPublicize				m_PlatformPublicize;				//����ؼ�

	CDlgQQLogon                    *m_pQQRegDialog;//QQ��¼�� 

	//��������
protected:
	CAccountsInfoArray				m_AccountsInfoArray;				//�˺���Ϣ

	//��������
public:
	//���캯��
	CDlgLogon();
	//��������
	virtual ~CDlgLogon();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	//���ܺ���
public:
	//��������
	WORD ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags,int nValidateType = 0,CString sCode = "",int LogonMode = -1);

	//��������
private:
	//��ȡ��Ϣ
	bool GetInformation();
	VOID LoadServerResouce();
	//�����˺�
	VOID LoadAccountsInfo();
	//��ַ��Ϣ
	VOID LoadLogonServerInfo();

	//���Ӱ�ť
protected:
	//�ֻ����
	VOID OnBnClickedUnbundling();
	//�һ�����
	VOID OnBnClickedGetPwd();
	//��ס����
	VOID OnBnClickedRemPwd();
	//���Ӱ�ť
	VOID OnBnClickedLogonLink4();

	//��ť��Ϣ
protected:
	//ע���ʺ�
	VOID OnBnClickedRegister();
	//��������
	VOID OnBnClickedProxyConfig();
	//ɾ����¼
	VOID OnBnClickedDeleteRecord();
	//qq��¼
	VOID OnBnClickedQQ();

	//�ؼ�����
protected:
	//ѡ��ı�
	VOID OnSelchangeGameID();
	//ѡ��ı�
	VOID OnSelchangeAccounts();
	//�༭�ı�
	VOID OnCbnEditchangeAccounts();
	//���͸ı�
	VOID OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult);

	//ϵͳ��Ϣ
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	//�ߴ�仯
	VOID OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUpdateResouce(WPARAM wParam, LPARAM lPara);
	afx_msg LRESULT OnQQLogin(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif