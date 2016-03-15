
// AdminControl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
// #include "MissionManager.h"
#include "MissionLogon.h"
#include "PlatformEvent.h"
#include "AdminControlDlg.h"
#include "MissionUserInfo.h"
#include "Stdafx.h"
// CAdminControlApp:
// �йش����ʵ�֣������ AdminControl.cpp
//
class CMyFrameWnd;


class CAdminControlApp : public CWinAppEx
{
public:
	CAdminControlApp();
	~CAdminControlApp();

// ��д
public:
	CMyFrameWnd* m_pMyFrameWnd;

//	CMissionList					m_MissionList;						//�б�����
//	CMissionLogon					m_MissionLogon;						//��¼����
//	CMissionManager					m_MissionManager;					//�������
	CPlatformEvent					m_PlatformEvent;

	CParameterGlobal				m_ParameterGlobal;					//ȫ������
	CGlobalUserInfo					m_GlobalUserInfo;					//�û���Ϣ
	//��Դ���
public:
	CSkinRenderManager				m_SkinRenderManager;				//��Ⱦ����
	CSkinResourceManager			m_SkinResourceManager;

	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAdminControlApp theApp;


//������̳�  
class CMyFrameWnd : public CFrameWnd  
{  
public:  
	CMyFrameWnd();  
	~CMyFrameWnd();  
	//�������
protected:
	CMissionList                    m_MissionList;						//��Ϸ�б�
	CMissionLogon					m_MissionLogon;						//��¼����
	CMissionUserInfo                m_MissionUserInfo;                  //�û���Ϣ
	CMissionManager					m_MissionManager;					//�������
public:
	//���ư�ť
public:
	CButton						m_btMin;							//��С��ť
	CButton						m_btMax;							//���ť
	CButton						m_btClose;							//�رհ�ť
	//�������
protected:
	bool							m_bMaxShow;							//����־
	bool							m_bRectify;							//������־
	CRect							m_rcNormalSize;						//����λ��
	DWORD                           m_dwAllOnLineCount;                 //����������

	//�ؼ�����
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�
protected:
	CAdminControlDlg                m_PlazaViewItem;
//	CGameUserListDlg*               m_pGameUserListDlg;
	//��̬����
protected:
	static CMyFrameWnd *			m_pPlatformFrame;					//���ָ��

	//���ܺ���
public:
	//��������������
	void UpDataAllOnLineCount();
	//��ȡ����������
	DWORD GetAllOnLineCount();
	//���溯��
protected:
	//��ԭ����
	bool RestoreWindow();
	//��󴰿�
	bool MaxSizeWindow();
private:
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);
protected:
	afx_msg	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);
	//���ܺ���
public:
	//��ȡʵ��
	static CMyFrameWnd * GetInstance() { return m_pPlatformFrame; }
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
protected:
protected:
	//�ر���Ϣ
	VOID OnClose();
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//λ����Ϣ
	VOID OnGetMinMaxInfo(MINMAXINFO * lpMMI);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDblClk(UINT nFlags, CPoint Point);
	//��Ϣ����
protected:
	//��Ϣ����
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:  
	DECLARE_MESSAGE_MAP();  
};  