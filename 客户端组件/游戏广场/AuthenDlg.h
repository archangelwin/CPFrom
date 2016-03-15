#pragma once
#include "Resource.h"
#include "WndValidateCode.h"
#include "InputNum.h"

// CAuthenDlg �Ի���

class CAuthenDlg : public CSkinDialog
{
	DECLARE_DYNAMIC(CAuthenDlg)

public:
	CAuthenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuthenDlg();

// �Ի�������
	enum { IDD = IDD_AUTHEN_DLG };

public:
	//����
	void AddCharToEdit(const CString& strChar);
	//����
	void ResetEdit();
	//ɾ��
	void DelLastCharInEdit();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//��ʼ������
	virtual BOOL OnInitDialog();

	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

private:
	//�ƶ�����
	void MoveInPutNumDlg();
	//��֤����֤
	void GetVerifyCode();

public:
	CSkinButton				m_btOK;						//��¼��ť
	CSkinButton				m_btCancel;					//ȡ����ť
	CSkinEdit               m_edInputNum;               //���֤�����
	CSkinEdit               m_edCheckNum;               //��֤��
	CSkinHyperLink			m_staGetPic;				//���»�ȡ��֤��
	CWndValidateCode		m_WndValidateCode;					//��֤�ؼ�


	CString                 m_sValidateCode;                  //����֤��

private:
	CInputNum				m_InputNumDlg;                 //���ּ�
	CString					m_strCode;                     //

public:
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStaGetpic();
	afx_msg void OnDestroy();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
};
