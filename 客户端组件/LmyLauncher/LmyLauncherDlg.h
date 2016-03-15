
// LmyLauncherDlg.h : 头文件
//
#pragma once

#pragma comment(lib,"version.lib")

#include "Stdafx.h"
#include "Resource.h"

#include "GradientProgressCtrl.h"
#include "SkinHyperLink.h"
#include "Log.h"
#include "PngImage.h"


// CLmyLauncherDlg 对话框
class CLmyLauncherDlg : public CDialog
{
// 构造
public:
	CLmyLauncherDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CLmyLauncherDlg();

// 对话框数据
	enum { IDD = IDD_LMYLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CLog                            m_DownLogFile;
	CString                         m_sDownLogTxt;
	STDownFile                      m_STCurrentDownFile;             // 当前下载文件
	Image *							m_pImage;							//图片对象
	CFont                           m_DefaultFont;
	CSize							m_SizeScaleImage;					//进度大小
	int                             m_nPointNum;

protected:
	bool                            m_bCreate;
	//CGradientProgressCtrl	        m_ProgressFile;
	//CGradientProgressCtrl	        m_ProgressSpeed;

	CSkinHyperLink					m_Percentage;					 			    
	CSkinHyperLink                  m_NowDownLoadFile;                        
	CSkinHyperLink                  m_DownLoadSpeed; 

	std::vector<STDownFile>        Vector_DownFile;					// 下载文件列表
	int                            m_nTotalFieNum;                  // 文件总数
	int                            m_nDownFileNum;                  // 剩余文件总数
	UINT                           m_nXmlVer;


	CString                        m_sCurrentDownFile;              //当前下载文件
	DWORD                          m_dwTotalFileSize;               //文件大小
	DWORD						   m_dwDownLoadSize;				//已经下载大小

	DWORD                          m_dwDownSpeed;                   //下载速度  
	DWORD						   m_dwLastCalcSize;				//上次大小
	DWORD						   m_dwLastCalcTime;				//上次时间

	bool                           m_bFileListFinish;               //下载文件列表是否完成
	bool                           m_bError;                        //是否下载出错

protected:
	CString                        m_sUpdateXmlUrl;                 //下载地址
	CString                        m_sUpdateXmlBackUrl;             //备用下载地址

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


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();	
	virtual VOID OnCancel();
	virtual void PostNcDestroy();
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpwndpos);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
