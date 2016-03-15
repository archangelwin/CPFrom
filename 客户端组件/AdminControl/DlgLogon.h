#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerControl.h"
#include "AccountsCtrl.h"
/*#include "PlatformPublicize.h"*/
/*#include "GetFilter.h"*/
//////////////////////////////////////////////////////////////////////////////////

//��¼��ʽ
#define LOGON_BY_GAME_ID			1									//I D ��¼
#define LOGON_BY_ACCOUNTS			0									//�ʺŵ�¼

//////////////////////////////////////////////////////////////////////////////////


//�˺���Ϣ
struct tagAccountsInfo
{
	DWORD							dwUserID;							//�û���ʶ
	TCHAR							szGameID[16];						//��Ϸ��ʶ
	TCHAR							szAccounts[LEN_ACCOUNTS];			//��¼�˺�
	TCHAR							szPassword[LEN_PASSWORD];			//��¼����
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

	//��¼��Ϣ
public:
	DWORD							m_dwGameID;							//��Ϸ I D
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//��Ϸ�ʺ�
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	TCHAR							m_szLogonServer[LEN_SERVER];		//��¼��ַ

	//�ؼ�����
public:
	CButton						m_btQuit;							//�˳���ť
	CButton						m_btEnter;							//��¼��ť
	CButton						m_btOption;							//���ð�ť
	CButton						m_btRegister;						//ע�ᰴť
	CButton						m_btDeleteRecord;					//ɾ����ť

	CStatic                     m_STConnect;
	//�ʺſؼ�
protected:
	CAccountsCtrl					m_GameIDControl;					//��¼ I D
	CAccountsCtrl					m_AccountsControl;					//��¼�ʺ�

protected:
	//	CGetFilter  cfilter;
	//��ť�ؼ�
protected:
	CButton						m_btLogonLink1;						//���Ӱ�ť
	CButton						m_btLogonLink2;						//���Ӱ�ť
	CButton						m_btLogonLink3;						//���Ӱ�ť
	CButton						m_btLogonLink4;						//���Ӱ�ť

	//����ؼ�
protected:
	CTabCtrl					m_TabControl1;						//��¼ģʽ
	CServerControl					m_ServerControl;					//��¼��ַ
	CEdit						m_PasswordControl;					//�û�����

	//����ؼ�
protected:
	CBrush							m_brBrush;							//������ˢ
	CSkintDPI                       m_SkinDPI;                          //����DPI
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	//	CPlatformPublicize				m_PlatformPublicize;				//����ؼ�

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
	WORD ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags,int nValidateType = 0,CString sCode = "");

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
	//���Ӱ�ť
	VOID OnBnClickedLogonLink1();
	//���Ӱ�ť
	VOID OnBnClickedLogonLink2();
	//���Ӱ�ť
	VOID OnBnClickedLogonLink3();
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

	//�ؼ�����
protected:
	//��������
	VOID SetUserPassword(LPCTSTR pszPassword);
	//��ȡ����
	LPCTSTR GetUserPassword(TCHAR szPassword[LEN_PASSWORD]);
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
//	BOOL OnEraseBkgnd(CDC * pDC);
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
	LRESULT OnUpdateResouce(WPARAM wParam, LPARAM lPara);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif