
// LmyLauncherDlg.h : ͷ�ļ�
//
#pragma once

#pragma comment(lib,"version.lib")

#include "Stdafx.h"
#include "Resource.h"

#include "GradientProgressCtrl.h"
#include "SkinHyperLink.h"
#include "Log.h"
#include "PngImage.h"


// CLmyLauncherDlg �Ի���
class CLmyLauncherDlg : public CDialog
{
// ����
public:
	CLmyLauncherDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CLmyLauncherDlg();

// �Ի�������
	enum { IDD = IDD_LMYLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CLog                            m_DownLogFile;
	CString                         m_sDownLogTxt;
	STDownFile                      m_STCurrentDownFile;             // ��ǰ�����ļ�
	Image *							m_pImage;							//ͼƬ����
	CFont                           m_DefaultFont;
	CSize							m_SizeScaleImage;					//���ȴ�С
	int                             m_nPointNum;

protected:
	bool                            m_bCreate;
	//CGradientProgressCtrl	        m_ProgressFile;
	//CGradientProgressCtrl	        m_ProgressSpeed;

	CSkinHyperLink					m_Percentage;					 			    
	CSkinHyperLink                  m_NowDownLoadFile;                        
	CSkinHyperLink                  m_DownLoadSpeed; 

	std::vector<STDownFile>        Vector_DownFile;					// �����ļ��б�
	int                            m_nTotalFieNum;                  // �ļ�����
	int                            m_nDownFileNum;                  // ʣ���ļ�����
	UINT                           m_nXmlVer;


	CString                        m_sCurrentDownFile;              //��ǰ�����ļ�
	DWORD                          m_dwTotalFileSize;               //�ļ���С
	DWORD						   m_dwDownLoadSize;				//�Ѿ����ش�С

	DWORD                          m_dwDownSpeed;                   //�����ٶ�  
	DWORD						   m_dwLastCalcSize;				//�ϴδ�С
	DWORD						   m_dwLastCalcTime;				//�ϴ�ʱ��

	bool                           m_bFileListFinish;               //�����ļ��б��Ƿ����
	bool                           m_bError;                        //�Ƿ����س���

protected:
	CString                        m_sUpdateXmlUrl;                 //���ص�ַ
	CString                        m_sUpdateXmlBackUrl;             //�������ص�ַ

public:
	bool GetDownFileList(CString sXmlUrl);
	UINT  GetDownLoadFlieCount(){return Vector_DownFile.size();};
	UINT  GetNewXmlVer(){return m_nXmlVer;};

	bool DownLoadXmlFile(CString sFileURL,CString &sReturnXml);
	bool DownLoadFile(STDownFile downFile);
	bool UnZipFile(CString szFileName);
	BOOL CreateFolder(LPCTSTR szFolder);
	BOOL CreateFilePath(LPCTSTR szFilePath);
	void StartDownTread();
	bool CheckNeedDownLoad(STDownFile downFile);
	HRESULT GetFileDate (TCHAR *szFileName, FILETIME *pft);
	HRESULT GetFileVersion (TCHAR *szFileName, VS_FIXEDFILEINFO *pvsf,CString &sFileVer);
	HRESULT LastError ();


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();	
	virtual VOID OnCancel();
	virtual void PostNcDestroy();
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpwndpos);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
