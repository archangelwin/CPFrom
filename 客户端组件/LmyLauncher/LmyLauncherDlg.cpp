
// LmyLauncherDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "LmyLauncher.h"
#include "LmyLauncherDlg.h"
#include <afxinet.h>
#include "CressXML.h"
#include "UnzipFile.h"
#include "BitImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  IDI_DOWNLOAD_FILE    300
#define  IDI_DOWNLOAD_PROCESS 301

DWORD WINAPI _DownLoadFile(PVOID pParam);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLmyLauncherDlg 对话框




CLmyLauncherDlg::CLmyLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLmyLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bCreate = false;
	m_bFileListFinish = false;
	m_bError = false;
	m_nTotalFieNum = 0;
	m_nDownFileNum = 0;
	m_nXmlVer = 0;

	//文件信息
	m_dwDownLoadSize=0L;
	m_dwTotalFileSize=0L;

	//下载速度
	m_dwDownSpeed=0L;
	m_dwLastCalcSize=0L;
	m_dwLastCalcTime=0L;
	m_nPointNum = 1;


	CTime tTime = CTime::GetCurrentTime();
	CString sTime ;
	sTime.Format( "_%04d%02d%02d.log",tTime.GetYear(),tTime.GetMonth(),tTime.GetDay() );

	CString m_sDownLogTxt;
	m_sDownLogTxt.Format("%s/DownLoad/AutoUpdate%s",theApp.m_sLocalPathStart,sTime);
	m_DownLogFile.Init(m_sDownLogTxt);
	m_DefaultFont.CreateFont(-12,0,0,0,1,0,0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("宋体"));

	CPngImageSB ImageDownLoadScale;
	ImageDownLoadScale.LoadCImage(AfxGetInstanceHandle(),TEXT("DOWN_LOAD_SCALE"));
	m_SizeScaleImage.SetSize(ImageDownLoadScale.GetCWidth(),ImageDownLoadScale.GetCHeight()/2);

}

CLmyLauncherDlg::~CLmyLauncherDlg()
{
	if (m_DownLogFile.m_bOpen)
	{		
		m_DownLogFile.CloseFile(m_sDownLogTxt);
		// 	    DeleteFile(m_sMsgFile);
	}
	//KillTimer(IDI_DOWNLOAD_FILE);
}

void CLmyLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Percentage);
	DDX_Control(pDX, IDC_STATIC4, m_NowDownLoadFile);
	DDX_Control(pDX, IDC_STATIC5, m_DownLoadSpeed);

	//DDX_Control(pDX, IDC_PROGRESS1, m_ProgressFile);
	//DDX_Control(pDX, IDC_PROGRESS2, m_ProgressSpeed);
}

BEGIN_MESSAGE_MAP(CLmyLauncherDlg, CDialog)
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	//ON_WM_SIZE()
END_MESSAGE_MAP()


// CLmyLauncherDlg 消息处理程序

BOOL CLmyLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
//	SetLayeredWindowAttributes(0,200,LWA_ALPHA);

	CPngImageSB ImageDownLoadBK;
	ImageDownLoadBK.LoadCImage(AfxGetInstanceHandle(),TEXT("DOWN_LOAD_BK"));

	//设置大小
	CSize SizeWindow(ImageDownLoadBK.GetCWidth(),ImageDownLoadBK.GetCHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//居中窗口
	CenterWindow();
	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Percentage.SetBackGroundColor(RGB(240,240,240));
	m_Percentage.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_Percentage.SetCustomFont(true,false,false,false);
	m_Percentage.SetWindowText("");
	m_Percentage.MoveWindow(rcClient.left+33,rcClient.top+130,130,14);

	m_NowDownLoadFile.SetBackGroundColor(RGB(240,240,240));
	m_NowDownLoadFile.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_NowDownLoadFile.SetCustomFont(true,false,false,false);
	m_NowDownLoadFile.SetWindowText("");
	m_NowDownLoadFile.MoveWindow(rcClient.left+178,rcClient.top+130,230,14);


	m_DownLoadSpeed.SetBackGroundColor(RGB(240,240,240));
	m_DownLoadSpeed.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_DownLoadSpeed.SetCustomFont(true,false,false,false);
	m_DownLoadSpeed.SetWindowText("");
	m_DownLoadSpeed.MoveWindow(rcClient.left+425,rcClient.top+130,160,14);

	// 设置初始进度显示
	//m_ProgressFile.SetRange32(0, 100);
	//m_ProgressFile.SetBkColor(RGB(160,180,220));
	//m_ProgressFile.ShowPercent(true);	
	//m_ProgressFile.MoveWindow(rcClient.left+85,rcClient.top+147,323,18);

	//m_ProgressSpeed.SetRange32(0, 100);
	//m_ProgressSpeed.SetBkColor(RGB(160,180,220));
	//m_ProgressSpeed.ShowPercent(true);	
	//m_ProgressSpeed.MoveWindow(rcClient.left+85,rcClient.top+175,323,18);

	m_bCreate = true;
	//m_ProgressFile.ShowWindow(SW_HIDE);
	//m_ProgressSpeed.ShowWindow(SW_HIDE);


	//m_Percentage.ShowWindow(SW_HIDE);
	//m_NowDownLoadFile.ShowWindow(SW_HIDE);
	//m_DownLoadSpeed.ShowWindow(SW_HIDE);
	
	SetTimer(IDI_DOWNLOAD_FILE,1000,NULL);
	SetTimer(IDI_DOWNLOAD_PROCESS,1000,NULL);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

VOID CLmyLauncherDlg::OnCancel()
{
	DestroyWindow();
	//PostMessage(WM_CLOSE,0,0);
}

//绘画背景
BOOL CLmyLauncherDlg::OnEraseBkgnd(CDC * pDC)
{
	//return false;
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建设备
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//设置环境
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(m_DefaultFont);

	//pBufferDC->FillSolidRect(&rcClient,RGB(240,240,240));
	//pBufferDC->FillSolidRect(&rcClient,RGB(255,255,255));
	//pBufferDC->FillSolidRect(&rcClient,RGB(0,0,0));

//绘画背景
	CPngImageSB ImageDownLoadBK;
	ImageDownLoadBK.LoadCImage(AfxGetInstanceHandle(),TEXT("DOWN_LOAD_BK"));
	//ImageDownLoadBK.DrawCImage(pBufferDC,(rcClient.Width()-ImageDownLoadBK.GetCWidth())/2,0,ImageDownLoadBK.GetCWidth(),ImageDownLoadBK.GetCHeight(),0,0);
	ImageDownLoadBK.DrawCImage(pBufferDC,0,0,ImageDownLoadBK.GetCWidth(),ImageDownLoadBK.GetCHeight(),0,0);

	//加载资源
	CPngImageSB ImageDownLoadScale;
	ImageDownLoadScale.LoadCImage(AfxGetInstanceHandle(),TEXT("DOWN_LOAD_SCALE"));

	//绘画进度
	DWORD dwDownScaleFile=0L;
	DWORD dwDownScaleSpeed=0L;
	if (m_dwTotalFileSize>0L)
	{
		dwDownScaleSpeed=m_dwDownLoadSize*100L/m_dwTotalFileSize;
	}
	if (m_nTotalFieNum>0)
	{
		dwDownScaleFile=(m_nTotalFieNum-m_nDownFileNum)*100L/m_nTotalFieNum;
	}
	int nXScreenPosFile = (ImageDownLoadBK.GetCWidth()-ImageDownLoadScale.GetCWidth())/2;
	int nYScreenPosFile = (ImageDownLoadBK.GetCHeight()/2/* -ImageDownLoadScale.GetCHeight()/2-30*/);
	nYScreenPosFile = 44;

	INT nXDrawAreaFile=m_SizeScaleImage.cx*dwDownScaleFile/100L;
	if (nXDrawAreaFile<=0)
	{
		return false;
	}
	ImageDownLoadScale.DrawCImage(pBufferDC,nXScreenPosFile,nYScreenPosFile,m_SizeScaleImage.cx,m_SizeScaleImage.cy,0,0);
	ImageDownLoadScale.DrawCImage(pBufferDC,nXScreenPosFile,nYScreenPosFile,nXDrawAreaFile,m_SizeScaleImage.cy,0,m_SizeScaleImage.cy);


	INT nXDrawAreaSpeed=m_SizeScaleImage.cx*dwDownScaleSpeed/100L;
	if (nXDrawAreaSpeed<=0)
	{
		return false;
	}
	ImageDownLoadScale.DrawCImage(pBufferDC,nXScreenPosFile,nYScreenPosFile+18,m_SizeScaleImage.cx,m_SizeScaleImage.cy,0,0);
	ImageDownLoadScale.DrawCImage(pBufferDC,nXScreenPosFile,nYScreenPosFile+18,nXDrawAreaSpeed,m_SizeScaleImage.cy,0,m_SizeScaleImage.cy);

	//文字位置
	CRect rcDescribe;
	rcDescribe.SetRect(nXScreenPosFile,80,320,92);

	//绘画文字
	pBufferDC->SetTextColor(RGB(0,0,0));

	//CString sSpeed;
	//sSpeed.Format("%dkb/秒",m_dwDownSpeed);
	//pBufferDC->DrawText(sSpeed,rcDescribe,DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
	if (0 == m_nDownFileNum && m_dwTotalFileSize == m_dwDownLoadSize)
	{
		pBufferDC->DrawText("下载完成",rcDescribe,DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
	}
	else
	{
		//CString sTmp = "正在下载 ";
		//for (int i=0;i<m_nPointNum;i++)
		//{
		//	sTmp +="…";
		//}
		//if(m_nPointNum++>=2)
		//	m_nPointNum = 1;

		//pBufferDC->DrawText(sTmp,rcDescribe,DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
		pBufferDC->DrawText("正在下载 ",rcDescribe,DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
		rcDescribe.left+=51;
		rcDescribe.right+=51;
		rcDescribe.top+=5;
		CString sTmp = "";
		for (int i=0;i<m_nPointNum;i++)
		{
			sTmp +="…";
		}
		if(m_nPointNum++>=2)
			m_nPointNum = 1;

		pBufferDC->DrawText(sTmp,rcDescribe,DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
		
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	//使用UpdateLayerWindow进行窗口透明处理 
	//HMODULE hFuncInst=LoadLibrary("User32.DLL"); 
	//typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);           
	//MYFUNC UpdateLayeredWindow; 
	//UpdateLayeredWindow=(MYFUNC)GetProcAddress(hFuncInst,"UpdateLayeredWindow"); 
	//SIZE sizeWindow={267,154}; 
	//POINT ptSrc={0,0}; 
	//POINT ptWinPos={rcClient.left,rcClient.top}; 
	//BLENDFUNCTION m_Blend; 
	//UpdateLayeredWindow( m_hWnd,pDC->GetSafeHdc(),&ptWinPos,&sizeWindow,pBufferDC->GetSafeHdc(),&ptSrc,0,&m_Blend,2); 


	return TRUE;
}

//位置改变
VOID CLmyLauncherDlg::OnWindowPosChanged(WINDOWPOS * lpwndpos)
{
	__super::OnWindowPosChanged(lpwndpos);

	//移动按钮
	if (m_bCreate==true)
	{
		//获取位置
		CRect rcClient;
		GetClientRect(&rcClient);
	}

	return;
}

void CLmyLauncherDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}

bool CLmyLauncherDlg::DownLoadFile(STDownFile downFile)
{
	ASSERT(downFile.sUrl != "");
	ASSERT(downFile.sFileName != "");
	CInternetSession session;
	CHttpConnection *pHttpConnection = NULL;
	CHttpFile *pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;
	DWORD dwHttpRequestFlags = INTERNET_FLAG_RELOAD;
	
	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数
	char* pszBuffer = NULL;  
	
	//Invalidate(true);
	//下载速度
	m_dwDownSpeed=0L;
	m_dwLastCalcSize=0L;
	m_dwLastCalcTime=GetTickCount();
	try
	{
		AfxParseURL(downFile.sUrl, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort);
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject, NULL, 1, NULL, NULL, dwHttpRequestFlags);
		if(pHttpFile->SendRequest() == FALSE)
		{
			m_bError = true;
			return false;
		}
		
		DWORD dwStateCode;
		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if(dwStateCode == HTTP_STATUS_OK)//检测服务器文件是否存在
		{
			CString sTmpFile = downFile.sFileName/*+".tmp"*/;
			sTmpFile = theApp.m_sLocalPathStart +sTmpFile;
			TRACE(sTmpFile+"\n");
			HANDLE hFile = CreateFile(sTmpFile, GENERIC_WRITE,
				FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  //创建本地文件
			if(hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				m_bError = true;
				return false;
			} 
			char szInfoBuffer[1000];  //返回消息
			DWORD dwFileSize = 0;   //文件长度
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				(void*)szInfoBuffer,&dwInfoBufferSize,NULL);
			
			dwFileSize = atoi(szInfoBuffer);
			//////////////////////////////////////////////////////////////////////////
			m_dwTotalFileSize = dwFileSize;  //seaplums
			m_dwDownLoadSize = 0;  // seaplums
			//////////////////////////////////////////////////////////////////////////

			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //读取文件的缓冲
			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //读取服务器上数据

			m_DownLogFile.Write("正在下载 "+ downFile.sFileName);
			
			while(nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //写到本地文件
				dwTotalWrite += dwWrite;
				m_dwDownLoadSize += dwWrite;  // seaplums
				nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);

				int nFileSizeRate = dwTotalWrite*100/dwFileSize;
				CString sFileRate;
				sFileRate.Format("%d",nFileSizeRate);

				CString sNumsRate;
				sNumsRate.Format("(%d/%d)",m_nTotalFieNum-m_nDownFileNum,m_nTotalFieNum);
				if (0 == m_nDownFileNum)
				{
					int aa = 2;
				}
				m_Percentage.SetWindowText(sFileRate+" %"+sNumsRate);
				int nPos = dwTotalWrite*100/dwFileSize;
				//m_ProgressSpeed.SetPos(nPos);

				//Invalidate(true);

				//计算速度
				if (GetTickCount()>=(m_dwLastCalcTime+500L))
				{
					//计算速度
					m_dwDownSpeed=(m_dwDownLoadSize-m_dwLastCalcSize)/(GetTickCount()-m_dwLastCalcTime);
					if(m_dwDownSpeed<0)
					{
						m_dwDownSpeed = -1*m_dwDownSpeed;
					}

					//设置变量
					m_dwLastCalcTime=GetTickCount();
					m_dwLastCalcSize=m_dwDownLoadSize;
					//CString sSpeed;
					//sSpeed.Format("%d kb/秒",m_dwDownSpeed);
					//m_DownLoadSpeed.SetWindowText(sSpeed);
				}
			}
			DWORD sFileSize;
			sFileSize = GetCompressedFileSize(sTmpFile,NULL);
			if(dwFileSize != sFileSize)//判断下载是否完整
			{
				DeleteFile(sTmpFile);
				m_bError = true;
				return false; //返回下载失败
			}
			
			delete[]pszBuffer;
			pszBuffer = NULL;
			CloseHandle(hFile);

			//对Zip文件进行再次的检测
			CString strExName = downFile.sFileName.Right(downFile.sFileName.GetLength()-downFile.sFileName.Find(".",0) - 1); 
			if( strExName == "zip" )
			{
				bool bUnzipRet = UnZipFile(sTmpFile);
				if (!bUnzipRet) //解压失败
				{
					m_bError = true;
				}
				::DeleteFile(sTmpFile);
			}
			//return true;
		}
		else
		{
			delete[]pszBuffer;
			pszBuffer = NULL;
			if(pHttpFile != NULL)
			{
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if(pHttpConnection != NULL)
			{
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			m_bError = true;
			return false;
		}
	}
	catch(...)
	{
		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if(pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		m_bError = true;
		return false;
	}
	if(pHttpFile != NULL)
		pHttpFile->Close();
	if(pHttpConnection != NULL)
		pHttpConnection->Close();
	session.Close();
	return true;

}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLmyLauncherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case IDI_DOWNLOAD_FILE:	
		{
			KillTimer(IDI_DOWNLOAD_FILE);
			if(Vector_DownFile.size() > 0)
			{
				StartDownTread();
			}
			else
			{
				CString strExeFile = theApp.m_sLocalPathStart+"LMYLobby.exe";
				int nRet = WinExec(strExeFile, SW_SHOW);
				int nLastError = GetLastError();
				PostMessage(WM_CLOSE,0,0);
				//EndDialog(-1);
			}
			//AfxBeginThread((AFX_THREADPROC)_DownLoadFile,this);
		}
	case IDI_DOWNLOAD_PROCESS:
		{
			Invalidate(true);
		}
		CDialog::OnTimer(nIDEvent);
	}
}

void CLmyLauncherDlg::StartDownTread()
{
	if(Vector_DownFile.size() > 0)
	{
		m_STCurrentDownFile = Vector_DownFile.back();
		Vector_DownFile.pop_back();
		m_sCurrentDownFile = m_STCurrentDownFile.sFileName;
		m_nDownFileNum--;
		m_NowDownLoadFile.SetWindowText(m_STCurrentDownFile.sFileName);
		CString sNumsRate;
		sNumsRate.Format("(%d/%d)",m_nTotalFieNum-m_nDownFileNum,m_nTotalFieNum);
		int nPos = (m_nTotalFieNum-m_nDownFileNum)*100/m_nTotalFieNum;
		//m_ProgressFile.SetPos(nPos);
		if (/*true */CheckNeedDownLoad(m_STCurrentDownFile)) //需要下载
		{
			AfxBeginThread((AFX_THREADPROC)_DownLoadFile,this);
		}
		else
		{
			m_DownLogFile.Write(m_STCurrentDownFile.sFileName + " 当前已是最新");
			StartDownTread();
			return;
		}
	}
	else
	{
		KillTimer(IDI_DOWNLOAD_FILE);
		CString sTmp;
		sTmp.Format("版本%d  更新完成",m_nXmlVer);
		m_DownLogFile.Write(sTmp);
		if (!m_bError)
		{
			//构造路径
			TCHAR szServerInfoPath[MAX_PATH]=TEXT("");
			_sntprintf(szServerInfoPath,CountArray(szServerInfoPath),TEXT("%s%s"),theApp.m_sLocalPathStart,UPDATE_INFO_FILE);
			//写入数据
			CString sNver;
			sNver.Format("%d",m_nXmlVer);
			WritePrivateProfileString(TEXT("VerInfo"),TEXT("PVer"),sNver,szServerInfoPath);

			CString strExeFile = theApp.m_sLocalPathStart+"LMYLobby.exe";
			int nRet = WinExec(strExeFile, SW_SHOW);
			int nLastError = GetLastError();
			//////////////////////////////////////////////////////////////////////////
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		else
		{
			CString sError;
			sError.Format("更新失败 %d",GetLastError());
			m_DownLogFile.Write(sError);
			int nRet = MessageBox("更新失败，请从官网下载更新","龙马游更新程序!",MB_OKCANCEL);
			if(nRet == IDOK)
			{
				ShellExecute(NULL,TEXT("OPEN"),"http://www.999qp.com",NULL,NULL,SW_NORMAL);
			}
			PostMessage(WM_CLOSE,0,0);
			return;

		}
	}
}

HRESULT  CLmyLauncherDlg::GetFileDate (TCHAR *szFileName, FILETIME *pft) {
	// we are interested only in the create time
	// this is the equiv of "modified time" in the 
	// Windows Explorer properties dialog
	FILETIME ct,lat;
	HANDLE hFile = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (hFile == INVALID_HANDLE_VALUE) 
		return LastError();
	BOOL bret = ::GetFileTime(hFile,&ct,&lat,pft);
	if (bret == 0) {
		::CloseHandle(hFile);
		return LastError();
	}

	::CloseHandle(hFile);
	return S_OK;
}

HRESULT  CLmyLauncherDlg::GetFileVersion (TCHAR *szFileName, VS_FIXEDFILEINFO *pvsf,CString &sFileVer) 
{
	DWORD dwHandle;
	DWORD cchver = GetFileVersionInfoSize(szFileName,&dwHandle);
	if (cchver == 0) 
		return LastError();
	TCHAR* pver = new TCHAR[cchver];
	BOOL bret = GetFileVersionInfo(szFileName,dwHandle,cchver,pver);
	if (!bret) 
		return LastError();
	UINT uLen;
	void *pbuf;
	bret = VerQueryValue(pver,_T("\\"),&pbuf,&uLen);
	if (!bret) 
		return LastError();
	memcpy(pvsf,pbuf,sizeof(VS_FIXEDFILEINFO));
	delete[] pver;

	sFileVer.Format(_T("%u.%u.%u.%u"), 
		HIWORD(pvsf->dwFileVersionMS), 
		LOWORD(pvsf->dwFileVersionMS), 
		HIWORD(pvsf->dwFileVersionLS), 
		LOWORD(pvsf->dwFileVersionLS)
		);

	//m_sProductVersion.Format(_T("%u.%u.%u.%u"), 
	//	HIWORD(m_vfixedFileInfo.dwProductVersionMS), 
	//	LOWORD(m_vfixedFileInfo.dwProductVersionMS), 
	//	HIWORD(m_vfixedFileInfo.dwProductVersionLS), 
	//	LOWORD(m_vfixedFileInfo.dwProductVersionLS)
	//	);

	return S_OK;
}

HRESULT  CLmyLauncherDlg::LastError () {
	HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
	if (SUCCEEDED(hr)) 
		return E_FAIL;
	return hr;
}

bool CLmyLauncherDlg::CheckNeedDownLoad(STDownFile downFile)
{
	CString strExName = downFile.sFileName.Right(downFile.sFileName.GetLength()-downFile.sFileName.Find(".",0) - 1); 
	if( strExName == "zip" ) //zip文件都要下载
	{
		return true;
	}
	CString sFilePath = theApp.m_sLocalPathStart + downFile.sFileName;

	// CURRENTDIR
	CFile f;
	if (f.Open(sFilePath, CFile::modeRead | CFile::shareDenyNone)) 
	{
		VS_FIXEDFILEINFO m_vfixedFileInfo;
		CString sFileVer;
		if ( SUCCEEDED( GetFileVersion((TCHAR*)(LPCTSTR)sFilePath, &m_vfixedFileInfo,sFileVer)) )  //有文件版本号
		{
			// 没有版本比较大小
			if (sFileVer.IsEmpty()) 
			{
				ULONGLONG m_ullSize = f.GetLength();
				if (m_ullSize!=downFile.nLength) //大小不一样
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else 
			{
				if (downFile.sFileVersion.CompareNoCase(sFileVer) > 0)
					return true;
				else
					return false;
			}
		
		}
		else
		{
			return true;
		}

		//FILETIME m_fileTime;
	
		//if (SUCCEEDED(GetFileDate((TCHAR*)(LPCTSTR)sFilePath, &m_fileTime)))
		//{
		//	int nEval = CompareFileTime(&m_fileTime, &downFile.m_fileTime);
		//	if( -1 == nEval) //时间是新的
		//		return true;
		//	else
		//		return false;
		//}
		return true;
	}
	return true;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLmyLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CLmyLauncherDlg::GetDownFileList(CString sUpdateXmlUrl)
{
	ASSERT(sUpdateXmlUrl != "");
	CString sXmlContent;
	if(!DownLoadXmlFile(sUpdateXmlUrl,sXmlContent)) //下载xml文件失败
		return false;

	CCressXML xml;
	if(!xml.LoadXML(sXmlContent))
		return false;
	xml.SelectNodeToList("Product");
	if (xml.QueryNode() != NULL)
	{
		CString sProcName = xml.GetAttrValueByName("productname");
		int nFileNum =  atoi(xml.GetAttrValueByName("filenum"));
		m_nXmlVer = atoi(xml.GetAttrValueByName("Ver"));
	}
	else
	{
		return false;
	}

	xml.SelectNodeToList("Product//File");
	while(xml.QueryNode()!=NULL)
	{
		STDownFile downFile;
		downFile.sFileName=xml.GetValueByName("FileName");
		if (downFile.sFileName == "")
		{
			continue;
		}
		downFile.sFileVersion = xml.GetValueByName("FileVersion");
		downFile.nLength = atoi(xml.GetValueByName("Length"));
		downFile.sInstallDir = xml.GetValueByName("LocalPath");
		downFile.sUrl = xml.GetValueByName("URL");
		downFile.m_fileTime.dwHighDateTime = atoi(xml.GetValueByName("FileDateHigh"));
		downFile.m_fileTime.dwLowDateTime = atoi(xml.GetValueByName("FileDateLow"));
		downFile.bRegister = (xml.GetValueByName("Register") == "NO"?false:true);
		downFile.bZipFile = (xml.GetValueByName("ZipFile")== "NO"?false:true);
		downFile.bForceOverWrite = (xml.GetValueByName("ForceOverwrite")== "NO"?false:true);
		downFile.bExecute = (xml.GetValueByName("Execute")== "NO"?false:true);

		Vector_DownFile.push_back(downFile);
	}
	m_bFileListFinish = true;

	m_nDownFileNum = m_nTotalFieNum = Vector_DownFile.size();
	return true;
}


bool CLmyLauncherDlg::DownLoadXmlFile(CString sFileURL,CString &sXmlContent)
{
	sXmlContent.Empty();

	CInternetSession is;
	CHttpFile *pHF = NULL;
	try {
		/* 
		　　网络连接请求时间超时值在数毫秒级。如果连接请求时间超过这个超时值，请求将被取消。 
		　　缺省的超时值是无限的。 
		*/ 
		is.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,000); 
		is.SetOption(INTERNET_OPTION_SEND_TIMEOUT,1000); 
		is.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT,2000); 
		/* 在网络连接请求时的重试次数。如果一个连接企图在指定的重试次数后仍失败，则请求被取消。 缺省值为5。*/ 
		is.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 2);   //重试次数

		// 打开配置文件中的URL
		pHF = (CHttpFile *)is.OpenURL(sFileURL,1, INTERNET_FLAG_RELOAD | INTERNET_FLAG_TRANSFER_ASCII);
		if (NULL == pHF) 
		{
			m_bError = true;
			return false;
			//throw _T("打开URL失败"); 
		}

		CString strData;
		while (pHF->ReadString(strData)) {
			sXmlContent += strData;
		}
	} catch (CInternetException *e) {
		if (pHF != NULL) {
			pHF->Close();
			delete pHF;
			pHF = NULL;
		}
		is.Close();
		m_bError = true;
		int nError = GetLastError();

		TCHAR szError[200];
		e->GetErrorMessage(szError,200);
		CString sErrorMsg;
		sErrorMsg.Format("%d  %s",nError,szError);
		m_DownLogFile.Write(sErrorMsg);

		return false;
		//throw;
	}

	if (pHF != NULL) {
		pHF->Close();
		delete pHF;
		pHF = NULL;
	}
	is.Close();
	return true;
	//////////////////////////////////////////////////////////////////////////
	//CInternetSession	session;
	//CHttpFile *pHttpFile = NULL;
	//CHttpConnection *pHttpConnection = NULL;
	//CString strServer, strObject;
	//INTERNET_PORT wPort;
	//DWORD dwHttpRequestFlags = INTERNET_FLAG_RELOAD;

	//DWORD dwType;
	//const int nTimeOut = 2000;
	//session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
	//session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数

	//INTERNET_OPTION_MAX_CONNS_PER_SERVER |INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER

	//try
	//{
	//	AfxParseURL(sFileURL, dwType, strServer, strObject, wPort);
	//	pHttpConnection = session.GetHttpConnection(strServer, wPort);
	//	pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject, NULL, 1, NULL, NULL, dwHttpRequestFlags);
	//	if(pHttpFile->SendRequest() == FALSE)
	//	{
	//		if (pHttpFile != NULL)
	//			delete pHttpFile;
	//		if(pHttpConnection != NULL)
	//		{
	//			pHttpConnection->Close();
	//			delete pHttpConnection;
	//			pHttpConnection = NULL;
	//		}
	//		session.Close();
	//		m_bError = true;
	//		return false;
	//	}

	//	DWORD dwStateCode;
	//	pHttpFile->QueryInfoStatusCode(dwStateCode);
	//	if(dwStateCode != HTTP_STATUS_OK)//检测服务器文件是否存在)
	//	{
	//		if (pHttpFile != NULL)
	//			delete pHttpFile;
	//		if(pHttpConnection != NULL)
	//		{
	//			pHttpConnection->Close();
	//			delete pHttpConnection;
	//			pHttpConnection = NULL;
	//		}
	//		session.Close();
	//		m_bError = true;
	//		return false;
	//	}
	//	pHttpFile = (CHttpFile *)session.OpenURL(sFileURL, 1, INTERNET_FLAG_RELOAD | INTERNET_FLAG_TRANSFER_ASCII);
	//	CString sTmp;
	//	while(pHttpFile->ReadString(sTmp))
	//	{
	//		sXmlContent+=sTmp;
	//	}
	//}
	//catch(...)
	//{
	//	if (pHttpFile != NULL)
	//		delete pHttpFile;
	//	if(pHttpConnection != NULL)
	//	{
	//		pHttpConnection->Close();
	//		delete pHttpConnection;
	//		pHttpConnection = NULL;
	//	}
	//	session.Close();
	//	m_bError = true;
	//	int nError = GetLastError();
	//	return false;
	//}
	//if (pHttpFile != NULL)
	//{
	//	pHttpFile->Close();
	//	delete pHttpFile;
	//}
	//if(pHttpConnection != NULL)
	//{
	//	pHttpConnection->Close();
	//	delete pHttpConnection;
	//	pHttpConnection = NULL;
	//}
	//session.Close();
	//return true;
}

bool CLmyLauncherDlg::UnZipFile(CString szFileName)
{
	try
	{
		const int BUF_SIZE = 128;
		CUnzipFile uf(szFileName);
		uf.GoToFirstFile();
		unz_file_info ui;
		TCHAR szDir[_MAX_DIR];
		TCHAR szDrive[_MAX_DRIVE];
		_tsplitpath(szFileName, szDrive, szDir,NULL, NULL);
		CString szPath = CString(szDrive) + szDir;
		do
		{
			uf.GetCurrentFileInfo(&ui);
			int iNameSize = ui.size_filename + 1;
			char* pName = new char [iNameSize];

			uf.GetCurrentFileInfo(NULL, pName, iNameSize);


			CString sName = pName;
			delete[]pName;

			/// sea add
			CString sFileName = szPath+sName;			
			char szFileName[MAX_PATH + 1];
			memset(szFileName,0,MAX_PATH + 1);
			memcpy(szFileName,sFileName,sFileName.GetLength());
			int nLen = lstrlen(szFileName);		
			while (nLen--)
			{
				if (szFileName[nLen] == '/')
					szFileName[nLen] = '\\';
			}
			BOOL bFolder = (szFileName[lstrlen(szFileName) - 1] == '\\');
			if(bFolder) // 文件夹
				continue;			
			if (!CreateFilePath(szFileName))   // 创建文件的完整目录
				return false;
			/// sea end 

			CFile f( szPath + sName, CFile::modeWrite | CFile::modeCreate);

			uf.OpenCurrentFile();
			char buf[BUF_SIZE];

			int size_read;
			do
			{
				size_read = uf.ReadCurrentFile(buf, BUF_SIZE);
				if (size_read > 0)
					f.Write(buf, size_read);
			}
			while (size_read == BUF_SIZE);

			uf.UpdateFileStatus(f, ui);

		}
		while(uf.GoToNextFile());

		uf.Close();
	}
	catch (CException*)
	{
		return false;
	}
	return true;
}

BOOL CLmyLauncherDlg::CreateFolder(LPCTSTR szFolder)
{
	if (!szFolder || !lstrlen(szFolder))
		return FALSE;

	DWORD dwAttrib = GetFileAttributes(szFolder);

	// already exists ?
	if (dwAttrib != 0xffffffff)
		return ((dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

	// recursively create from the top down
	char* szPath = _strdup(szFolder);
	char* p = strrchr(szPath, '\\');
	if (p) 
	{
		// The parent is a dir, not a drive
		*p = '\0';

		// if can't create parent
		if (!CreateFolder(szPath))
		{
			free(szPath);
			return FALSE;
		}
		free(szPath);

		if (!::CreateDirectory(szFolder, NULL)) 
			return FALSE;
	}

	return TRUE;
}

BOOL CLmyLauncherDlg::CreateFilePath(LPCTSTR szFilePath)
{
	char* szPath = _strdup(szFilePath);    
	char* p = strrchr(szPath,'\\');       	
	BOOL bRes = FALSE;	
	if (p)
	{
		*p = '\0'; 		
		bRes = CreateFolder(szPath);
	}	
	free(szPath);	
	return bRes;
}

void CLmyLauncherDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CLmyLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	UINT nCommand = nID & 0xFFF0;
	BOOL bShift = GetAsyncKeyState( VK_SHIFT ) & 0x8000;

	if ( nCommand == SC_MINIMIZE || ( nCommand == SC_MINIMIZE && bShift ) )
	{
		return;
	}

	CDialog::OnSysCommand(nID, lParam);
}


DWORD WINAPI _DownLoadFile( void *pParam )
{
	CLmyLauncherDlg *pThis = static_cast<CLmyLauncherDlg *>(pParam);

	bool bDownrSuess = pThis->DownLoadFile(pThis->m_STCurrentDownFile);
	if (bDownrSuess)
	{
		pThis->m_DownLogFile.Write(pThis->m_STCurrentDownFile.sFileName + "  下载成功");
		pThis->StartDownTread();
	}
	else
	{
		CString sError;
		sError.Format("%s 更新失败 %d",pThis->m_STCurrentDownFile.sFileName,GetLastError());
		pThis->m_DownLogFile.Write(sError);

		int nRet = MessageBox(NULL,"文件更新失败，请从官网下载更新!","龙马游更新程序",MB_OKCANCEL);
		if(nRet == IDOK)
		{
			ShellExecute(NULL,TEXT("OPEN"),"http://www.999qp.com",NULL,NULL,SW_NORMAL);
		}
		pThis->PostMessage(WM_CLOSE,0,0);
		return 0;
	}
	return 0;
}