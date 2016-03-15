#ifndef DLG_SERVICE_HEAD_FILE
#define DLG_SERVICE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"
#include "DlgServicePassword.h"
#include "DlgServiceIndividual.h"

//////////////////////////////////////////////////////////////////////////////////

//�û�����
#define SERVICE_INDIVIDUAL			1									//�޸�����
#define SERVICE_PASSWORD			2									//�޸�����
#define SERVICE_PAY_RECORD			3									//��ֵ��¼

//////////////////////////////////////////////////////////////////////////////////

//����˵��
typedef CWHArray<CDlgServiceItem *> CDlgServiceItemArray;

//////////////////////////////////////////////////////////////////////////////////

//ѡ�����
class CDlgServiceBar : public CWnd
{
	//���Ϣ
protected:
	bool							m_bHovering;						//������־
	WORD							m_wItemDown;						//��������
	WORD							m_wItemHover;						//��������
	WORD							m_wItemActive;						//��������

	//������Ϣ
protected:
	CSize							m_SizeButton;						//��ť��С
	CRect							m_rcItemCreate;						//����λ��
	CDlgServiceItemArray			m_DlgServiceItemArray;				//��������

	//��������
public:
	//���캯��
	CDlgServiceBar();
	//��������
	virtual ~CDlgServiceBar();

	//���غ���
public:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���ܺ���
public:
	//��������
	bool SetItemCreateRect(CRect rcItemCreate);
	//��������
	bool InsertServiceItem(CDlgServiceItem * pDlgServiceItem);
	//��������
	bool SetActiveServiceItem(CDlgServiceItem * pDlgServiceItem);

	//�ڲ�����
private:
	//�����л�
	WORD SwitchToButtonIndex(CPoint MousePoint);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//����ר��
class CDlgService : public CSkinDialog
{
	//�������
protected:
	BYTE							m_cbServiceID;						//������ʶ

	//�ؼ�����
protected:
	CDlgServiceBar					m_DlgServiceBar;					//���ť

	//�������
public:
	CDlgServiceIndividual			m_DlgServiceIndividual;				//��������
	CDlgServicePassword				m_DlgServicePassword;				//�޸�����

	//��ҳ����
public:
	CDlgServiceBrowser				m_DlgBrowserPayRecord;				//��ֵ��¼

	//��������
public:
	//���캯��
	CDlgService();
	//��������
	virtual ~CDlgService();

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual VOID OnOK();

	//���ܺ���
public:
	//������ʶ
	VOID SetExpectationID(BYTE cbServiceID);
	//��ȡ����
	CDlgServiceItem * GetServiceItem(BYTE cbServiceID);

	//��Ϣӳ��
protected:
	//�б���Ϣ
	VOID OnActionServiceUser(NMHDR * pNMHDR, LRESULT * pResult);
	//�б���Ϣ
	VOID OnActionServiceMember(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif