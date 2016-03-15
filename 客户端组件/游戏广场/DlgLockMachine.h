#ifndef DLG_LOCK_MACHINE_HEAD_FILE
#define DLG_LOCK_MACHINE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
class CDlgLockMachine : public CSkinDialog, public CMissionItem
{
	//��������
protected:
	BYTE							m_cbMachine;						//�󶨱�־
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];	//֤������
	TCHAR							m_szCompellation[LEN_COMPELLATION];	//��ʵ����
	TCHAR							m_szPassword2[LEN_PASSWORD];			//�û�����
    int                             m_nType;                            //0�󶨻�����1�����֤
	bool                            m_bShowPassportID;                  //�Ƿ���ʾ���֤

	//�ؼ�����
protected:
	CSkinButton						m_btOk;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

	CSkinButton						m_btPassID;							//�����֤
	CSkinButton                     m_btPasswordProtect;                //�������뱣��
	CPasswordControl				m_PasswordControl;					//�û�����

	CSkinHyperLink                  m_cTitlePC;
	CSkinHyperLink                  m_cPWD;
	CSkinHyperLink                  m_cTitlePassID;
	CSkinHyperLink                  m_cPassName;
	CSkinHyperLink                  m_cPassID;
	CSkinHyperLink                  m_cTitleValidate;
	CSkinHyperLink                  m_cPWD2;
	CSkinHyperLink                  m_cPidRemark;
	CSkinHyperLink                  m_cInsurePwdQQ;
	CSkinHyperLink                  m_cApplyProtectRemark;              //���뱣������
	CPasswordControl				m_PasswordControl2;					//�û�����

	CSkinEdit						m_edName;						     //����
	CSkinEdit						m_edPassID;						     //���֤��
	CWebPublicize					m_WebPublicize;						//�������	

	CPngImageSB                       m_ImageMachine;                       //��ͼƬ
	CPngImageSB                       m_ImagePassID;                       //���֤ͼƬ

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������

	//��������
public:
	//���캯��
	CDlgLockMachine();
	//��������
	virtual ~CDlgLockMachine();

	//���غ���
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	afx_msg void OnBnClickedButtonPassID();
	afx_msg void OnBnClickedButtonPasswordProtect();
	//���غ���
public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif