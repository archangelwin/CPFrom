#ifndef DLG_INSURE_COUNTER_HEAD_FILE
#define DLG_INSURE_COUNTER_HEAD_FILE

#pragma once

#include "MissionManager.h"
#include "PasswordControl.h"
#include "ShareControlHead.h"
#include "DlgBrowser.h"

//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CDlgInsureItem;
class CDlgInsureMain;
class CDlgInsureSave;
class CBankLogDlg;

//////////////////////////////////////////////////////////////////////////////////

//������ʽ
#define INSURE_SAVE					0									//��ȡ��ʽ
#define INSURE_TRANSFER				1									//ת�˷�ʽ
#define INSURE_TRANSFERRECORD       2                                   //ת�˼�¼

//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct tagUserInsureInfo
{
	WORD							wRevenueTake;						//˰�ձ���
	float							wRevenueTransfer;					//˰�ձ���
	WORD							wServerID;							//�����ʶ
	SCORE							lUserScore;							//�û���Ϸ��
	SCORE							lUserInsure;						//������Ϸ��
	SCORE							lTransferPrerequisite;				//ת������
};

//////////////////////////////////////////////////////////////////////////////////

//���нӿ�
interface IInsureCounterAction
{
	//��ѯ�¼�
	virtual VOID PerformQueryInfo()=NULL;
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore)=NULL;
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)=NULL;
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)=NULL;
	//ת����־
	virtual VOID SendBankTransferLog(int nCurrentPage,int nDays)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//ҳ������
class CDlgInsureItem
{
	//��������
public:
	//���캯��
	CDlgInsureItem();
	//��������
	virtual ~CDlgInsureItem();

	//���ܺ���
public:
	//��ȡ��Ϸ��
	SCORE GetUserControlScore(CWnd * pWndScore);

	//���ܺ���
public:
	//�滭����
	VOID DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos);
	//ת���ַ�
	VOID SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize);
	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);
};

//////////////////////////////////////////////////////////////////////////////////
//ȡ��Ϸ��
class CDlgInsureTeller : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edSelfScore;						
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinButton						m_btTakeScore;						//ȡ�ť
	CSkinButton						m_btQueryInfo;						//��ѯ��ť

	//�����ؼ�
public:
	CSkinHyperLink					m_InsureTellerNum1;		
	CSkinHyperLink					m_InsureTellerNum2;						
	CSkinHyperLink					m_InsureTellerNum3;						
	CSkinHyperLink					m_InsureTellerNum4;						
	CSkinHyperLink					m_InsureTellerNum5;						
	CSkinHyperLink					m_InsureTellerNum6;						
	CSkinHyperLink					m_InsureTellerNum7;	

	CSkinHyperLink					m_Teller1;		
	CSkinHyperLink					m_Teller2;						
	CSkinHyperLink					m_Teller3;						
	CSkinHyperLink					m_Teller4;						
	CSkinHyperLink					m_Teller5;						
	CSkinHyperLink					m_Teller6;						
	CSkinHyperLink					m_Teller7;	

	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����	
	//��������
public:
	//���캯��
	CDlgInsureTeller();
	//��������
	virtual ~CDlgInsureTeller();
	void UpDateView(); //���½���

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//ȡ�ť
	VOID OnBnClickedTakeScore();
	VOID OnBnClickedQueryInfo();
	afx_msg void OnInsureTellerClick(UINT uID);
	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////

//����Ϸ��
class CDlgInsureSave : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edSelfScore;						
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinButton						m_btSaveScore;						//��ť
	CSkinButton						m_btQueryInfo;						//��ѯ��ť

	//�����ؼ�
public:
	CSkinHyperLink					m_InsureSaveNum1;		
	CSkinHyperLink					m_InsureSaveNum2;						
	CSkinHyperLink					m_InsureSaveNum3;						
	CSkinHyperLink					m_InsureSaveNum4;						
	CSkinHyperLink					m_InsureSaveNum5;						
	CSkinHyperLink					m_InsureSaveNum6;						
	CSkinHyperLink					m_InsureSaveNum7;	

	CSkinHyperLink					m_Save1;
	CSkinHyperLink					m_Save2;
	CSkinHyperLink					m_Save3;
	CSkinHyperLink					m_Save4;
	CSkinHyperLink					m_Save5;

	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����	

	//��������
public:
	//���캯��
	CDlgInsureSave();
	//��������
	virtual ~CDlgInsureSave();
	void UpDateView(); //���½���

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//��ť
	VOID OnBnClickedSaveScore();
	VOID OnBnClickedQueryInfo();
	afx_msg void OnInsureSaveClick(UINT uID);
	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//ת����Ϸ��
class CDlgInsureTransfer : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx                     m_edSelfScore;
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinEditEx						m_edNickName;						//�û��ǳ�
	CSkinButton						m_btTransferScore;					//ת�˰�ť
    CSkinButton						m_btQueryInfo;						//��ѯ��ť
	//�����ؼ�
public:
	CSkinHyperLink					m_InsureTranNum1;
	CSkinHyperLink					m_InsureTranNum2;	
	CSkinHyperLink					m_InsureTranNum3;
	CSkinHyperLink					m_InsureTranNum4;						
	CSkinHyperLink					m_InsureTranNum5;
	CSkinHyperLink					m_InsureTranNum6;	


	CSkinHyperLink					m_Tran1;		
	CSkinHyperLink					m_Tran2;						
	CSkinHyperLink					m_Tran3;						
	CSkinHyperLink					m_Tran4;						
	CSkinHyperLink					m_Tran5;						
	CSkinHyperLink					m_Tran6;						
	CSkinHyperLink					m_Tran7;	


	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����		

	//��������
public:
	//���캯��
	CDlgInsureTransfer();
	//��������
	virtual ~CDlgInsureTransfer();
	void UpDateView(); //���½���

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//ת�˰�ť
	VOID OnBnClickedTransferScore();
	VOID OnBnClickedQueryInfo();
	afx_msg void OnInsureTransferClick(UINT uID);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedById();
	afx_msg void OnBnClickedByName();
};

//////////////////////////////////////////////////////////////////////////////////
//ת�˼�¼
class CBankLogDlg : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��

	//�ؼ�����
public:
	CSkinButton			m_bQuery;
	CSkinButton			m_bFirstPage;
	CSkinButton			m_bBeforePage;
	CSkinButton			m_bNextPage;
	CSkinButton			m_bLastPage;

	CSkinComboBox	    m_boxLogDate;
	CGroupBox			m_gbLog;		
	CSkinListCtrl       m_LogList;

	//�����ؼ�
public:
	CSkinHyperLink					m_BankLogTip;		
	CSkinHyperLink					m_BankLogPage;		
	CSkinHyperLink					m_BankLogDate;	
	CDlgInsureItem					m_DlgInsureItem;					//��������

public:
	LONG				m_lLogIndex;
	int					m_lRecordCount;
	int					m_lPageCount;
	int					m_lCurrentPage;	

	//��������
public:
	//���캯��
	CBankLogDlg();

	//��������
	virtual ~CBankLogDlg();
	void UpDateView(); //���½���

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonBefore();
	VOID InsertTransferLog(CMD_GP_BankRecordItem  * pBankTransferLogResult);
	VOID SetTransPages(int nPageCount,int nCurentPage,int nRecordCount);
	//VOID TransferLogFinish(CMD_GP_BankTransferLogFinish * pBankTransferLogFinish);
	afx_msg void OnNMDblclkListTransferLog(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
//ת�˼�¼
class  CDlgBrowserItem : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

public:
	//���캯��
	CDlgBrowserItem();
	//��������
	virtual ~CDlgBrowserItem();
protected:
	TCHAR							m_szItemName[32];					//��������
	TCHAR							m_szServiceUrl[34];					//���ӵ�ַ
protected:
	CWebPublicize					m_WebPublicize;						//�������

	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
public:
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//���÷���
	VOID InitService(LPCTSTR pszItemName, LPCTSTR pszServiceUrl);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////////////////

//���չ���
class SHARE_CONTROL_CLASS CDlgInsureMain : public CSkinDialog, public IInsureCounterAction
{
	//��������
protected:
	bool							m_bSaveMission;						//�������
	bool							m_bTakeMission;						//ȡ������
	bool							m_bQueryMission;					//��ѯ����
	bool							m_bTransferMission;					//ת������
	bool                            m_bQueryTransferLog;                //ת����־

	//��ѯ����
protected:
	bool							m_bInitInfo;						//������Ϣ
	BYTE							m_cbInsureMode;						//����ģʽ

	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������
public:
	TCHAR							m_szSaveInsurePass[LEN_PASSWORD];		//��������
	tagUserInsureInfo				m_UserInsureInfo;					//������Ϣ

	//�����ؼ�
protected:
	//CSkinTabCtrl					m_TabControl;						//����ѡ��
	//CSkinButton						m_btQueryInfo;						//��ѯ��ť
	CTreeCtrl	                    m_treeDlg;

	HTREEITEM                       parent_son[2];
	HTREEITEM                       sub_son[7];
	CDialog                        *m_pDialog[7];
private:
	bool							m_bInit;							//�Ƿ��ѳ�ʼ��
	int								m_nBeginTop;						//���濪ʼ
	int								m_nHSpace;							//�������¼��
	int								m_nLSpace;							//��߿�ʼλ��
	CFont							m_BankFont;							//������Ϣ����
	CFont							m_BankFontInfo;						//������������
	CRect							m_BankRect[4];						//������������
	int								m_nSelIndex;						//��ǰѡ����
	CBitImage						m_ImageSelBank;					
	//�����
protected:
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CDlgInsureTeller				m_DlgInsureTeller;					//ȡ��
	CDlgInsureSave					m_DlgInsureSave;					//���
	CDlgInsureTransfer				m_DlgInsureTransfer;				//ת������
	CDlgBrowserItem                 m_DlgBrowserItem;                   //ת�˼�¼
	CBankLogDlg                     m_LogDlg;       

	//��������
public:
	//���캯��
	CDlgInsureMain();
	//��������
	virtual ~CDlgInsureMain();
	VOID SetInsurePass(CString sInsurePwd);
	VOID UpdatUserInfo();
	//��ѯ����
	VOID QueryUserInsureInfo();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeSafa(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeSafa(NMHDR* pNMHDR, LRESULT* pResult);
	//ȷ����ť
	virtual VOID OnOK();
	virtual VOID OnCancel();

	//���ں���
protected:
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
protected:
	void DrawBankTab(CDC * pDC, INT nWidth, INT nHeight);
	//�¼�����
public:
	//��ʼ����
	VOID OnMissionStart();
	//��ֹ����
	VOID OnMissionConclude();

	//���ܺ���
public:
	//����ģʽ
	VOID SwitchInsureModeView(BYTE cbInsureMode);

	//��Ϣ����
protected:
	//���͸ı�
	//VOID OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//�㳡����
class SHARE_CONTROL_CLASS CDlgInsurePlaza : public CDlgInsureMain, public CMissionItem
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	//TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������
	int                             m_nCurrentPage;
	int                             m_nDays;

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������

	//��������
public:
	//���캯��
	CDlgInsurePlaza();
	//��������
	virtual ~CDlgInsurePlaza();

	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);
	//ת����־
	virtual VOID SendBankTransferLog(int nCurrentPage,int nDays);

	//�����¼�
private:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class SHARE_CONTROL_CLASS CDlgInsureServer : public CDlgInsureMain
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	//TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������
	int                             m_nCurrentPage;
	int                             m_nDays;

	//��������OnCancel
protected:
	ITCPSocket *					m_pITCPSocket;						//����ӿ�
	IClientUserItem *				m_pIMySelfUserItem;					//�Լ�ָ��

	//��������
public:
	//���캯��
	CDlgInsureServer();
	//��������
	virtual ~CDlgInsureServer();
	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);
	//ת����־
	virtual VOID SendBankTransferLog(int nCurrentPage,int nDays);

	//���ܺ���
public:
	//��������
	VOID Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem);
	//������Ϣ
	bool OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

#endif