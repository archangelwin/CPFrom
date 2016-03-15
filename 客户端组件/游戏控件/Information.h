#ifndef INFORMATION_HEAD_FILE
#define INFORMATION_HEAD_FILE

#pragma once

#include "ShareControlHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��Ϣ����
class SHARE_CONTROL_CLASS CInformation : public CSkinDialog
{
	//���Ա���
protected:
	UINT							m_uType;							//��Ϣ����
	CString							m_strString;						//��ʾ��Ϣ
	CString							m_strCaption;						//��Ϣ����
	bool                            m_bShowTip;
	UINT                            m_nCustomType;                      //�Զ������ͣ�Ĭ��0,1��ֵ

	//��������
protected:
	UINT							m_nElapse;							//ʣ��ʱ��
	UINT							m_nBtCount;							//��ť��Ŀ
	CRect							m_rcString;							//�ַ�λ��
	HINSTANCE						m_hResInstance;						//��Դ���

	//�ؼ�����
protected:
	CSkinButton						m_btButton[3];						//��ť�ؼ�
	CSkinCheckBox                   m_cbShowTip;                        //������ʾ

	//��������
public:
	//���캯��
	CInformation(CWnd * pParentWnd=NULL);
	//��������
	virtual ~CInformation();

	//���غ���
protected:
	//��ʼ����Ϣ
	virtual BOOL OnInitDialog();
	//������Ϣ
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//��ʾ��Ϣ
	INT ShowMessageBox(LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0,UINT nCustom=0,bool bShowTip = false);
	//��ʾ��Ϣ
	INT ShowMessageBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0,UINT nCustom=0,bool bShowTip = false);
	bool NotipChecked(){return m_bShowTip;}

	//�ڲ�����
private:
	//������ť
	VOID CreateBoxButton();

	//��Ϣӳ��
protected:
	//�滭��Ϣ
	VOID OnPaint();
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//ȫ�ֺ���
extern "C" SHARE_CONTROL_CLASS INT ShowInformation(LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0,UINT nCustom=0,bool bShowTip = false);
extern "C" SHARE_CONTROL_CLASS INT ShowInformationEx(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0,UINT nCustom=0,bool bShowTip = false);

//////////////////////////////////////////////////////////////////////////////////

#endif