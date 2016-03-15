#pragma once

#include "Stdafx.h"
// CVerifyInsurePass �Ի���

class CVerifyInsurePass : public CSkinDialog, public CMissionItem
{

public:
	CVerifyInsurePass();   // ��׼���캯��
	virtual ~CVerifyInsurePass();

protected:	
	TCHAR							m_szInsurePassword[LEN_PASSWORD];			//���չ�����
	int                             m_nSavePwdType;
	int                             m_nSaveMinute;

protected:
	CSkinButton						m_btVerifyInsurePass;               //��֤����
	CPasswordControl				m_PasswordControl;					//�û�����
	CSkinComboBox					m_ComMinutes;					    //������

	CSkinHyperLink					m_VerifyPassTitle;					//̧ͷ
	CSkinHyperLink					m_PassText;					//̧ͷ
	CSkinHyperLink					m_GetInsurePwd;						    //�һ�����
	CSkinHyperLink					m_VerifyMinute;					//������
	CSkinHyperLink					m_VerifyQQtip;					//qq��¼

	CMissionManager					m_MissionManager;					//�������
	//�ػ���Ϣ
	//VOID OnPaint();
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnBnClickedButtonVerifyPass();
	afx_msg void OnBnClickedForgetInsure();

public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()
};
