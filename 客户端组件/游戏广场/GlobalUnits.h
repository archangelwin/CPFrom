#ifndef GLOBAL_UNITES_HEAD_FILE
#define GLOBAL_UNITES_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgDownLoad.h"

//////////////////////////////////////////////////////////////////////////////////

//ȫ�ֵ�Ԫ
class CGlobalUnits
{
	//ϵͳ����
public:
	//	DWORD								m_dwPlazaVersion;				//�����汾
	//	TCHAR								m_szDirSkin[MAX_PATH];			//Ƥ��Ŀ¼
	TCHAR								m_szDirWork[MAX_PATH];			//����Ŀ¼
	CString                             m_sAppPath;         
	//�汾��Ϣ
protected:
	DWORD							m_dwPlazaVersion;					//�����汾
	DWORD							m_dwFrameVersion;					//��ܰ汾
	DWORD                           m_dwResouceVersion;                 //��Դ�汾
	DWORD                           m_dwLockCoin;                       //���ٱ���Ҫ�󶨱���
//�ؼ��ֹ���
public:
	CCriticalSection m_CriticalFilter; //�ؼ�����
	CStringArray m_arrayFitler;	
	CStringArray m_arrayFliterUrl;//�ж���ַ�Ĺؼ���
	CStringArray m_arrayQQ;//�ж�QQ �Ĺؼ���
	bool ReplaceFitler(CString& sFilterString,int ntype);
	CString OnReplaceQuanBan(CString sResult);
	CString ReplaceFitlerByReturn(CString sFilterString);
	bool InitArrayFitler();
	//���ָ��
protected:
	CDlgDownLoad *					m_pDlgDownLoad;						//�������

	//��̬����
protected:
	static CGlobalUnits *			m_pGlobalUnits;						//����ָ��

	//��������
public:
	//���캯��
	CGlobalUnits();
	//��������
	virtual ~CGlobalUnits();

	//�汾��Ϣ
public:
	bool InitGlobalUnits();
	//����Ŀ¼
	LPCTSTR GetWorkDirectory() { return m_szDirWork; }
	//�����汾
	virtual DWORD GetPlazaVersion() { return m_dwPlazaVersion; }
	//��ܰ汾
	virtual DWORD GetFrameVersion() { return m_dwFrameVersion; }
	//��Դ�汾
	virtual DWORD GetResouceVersion() { return m_dwResouceVersion; }
	//��Դ�汾
	virtual void SetResouceVersion(int nNewVer) { m_dwResouceVersion = nNewVer; }
	//��Դ�汾
	virtual DWORD GetLockCoin() { return m_dwLockCoin; }
	//�����Ϣ
public:
	//��¼���
	bool WriteUserCookie();
	//ɾ�����
	bool DeleteUserCookie();

	//��������
public:
	//��������
	bool PlayGameSound(LPCTSTR pszSoundName);
	//��������
	bool PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName);

	//���ܺ���
public:
	//������Ϸ
	bool DownLoadClient(LPCTSTR pszClientName, WORD wKindID, WORD wServerID,LPCTSTR szProcessName="");

	//��̬����
public:
	//��ȡ����
	static CGlobalUnits * GetInstance() { return m_pGlobalUnits; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif