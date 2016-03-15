
// UserHangUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserHangUp.h"
#include "UserHangUpDlg.h"
#include "ServerListData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinThread* pConnectThread = NULL;

UINT _ConnectThread(LPVOID param)
{
	CUserHangUpDlg* pConnectDlg = (CUserHangUpDlg*)param;

// 	while(1)
// 	{
// 		pConnectDlg->OnPlazzConnection();
// 
// 		Sleep(10000);
// 
// 		pConnectDlg->m_SocketClient->m_TCPSocketModule->CloseSocket();
// 	}

	return 0;
}

CUserHangUpDlg::CUserHangUpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserHangUpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bIsConnected = FALSE;

	//m_IsThreadStart = false;
	m_ArrayIndex = 0;
	m_SocketClient = new CSocketClient;
}

CUserHangUpDlg::~CUserHangUpDlg()
{
	if (m_SocketArray.GetCount()!=0)
	{
		for (int i=0;i<m_SocketArray.GetCount();i++)
		{
			SafeDelete(m_SocketArray[i]);
		}
		
		m_SocketArray.RemoveAll();
	}
	
	if (m_SocketClient!=NULL)
	{
		SafeDelete(m_SocketClient);
	}

	int nUninstRes = crUninstall();
}

void CUserHangUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	//	DDX_Control(pDX, IDC_IPADDRESS1, m_AddressCtrl);
	//	DDX_Control(pDX, IDC_EDIT2, m_Port);
	DDX_Control(pDX, IDC_IPCONTROL, m_IP);
	DDX_Control(pDX, IDC_BKIP, m_BkIP);
	DDX_Control(pDX, IDC_CONNECT, m_BtConnect);
	DDX_Control(pDX, IDC_CHANGE_CONNECT, m_BtChangeConnect);
	DDX_Control(pDX, IDC_OPEN_FILE, m_BtOpenFile);
	DDX_Control(pDX, IDC_GAMECOMB, m_CombGame);
	DDX_Control(pDX, IDC_ACCOUNT, m_EDUserID);
	DDX_Control(pDX, IDC_PASSWORD, m_EDPassword);
	DDX_Control(pDX, IDC_GAME_NAME, m_EDGameName);
	DDX_Control(pDX, IDC_GAME_KINDID, m_EDGameID);
	DDX_Control(pDX, IDC_GAME_PORT, m_EDPort);
	DDX_Control(pDX, IDC_GAME_VERSION, m_EDVersion);
	DDX_Control(pDX, IDC_COMBO2, m_CombGameInfoList);
	DDX_Control(pDX, IDC_COMBO_ACCOUNT, m_ComboAccount);
}

BEGIN_MESSAGE_MAP(CUserHangUpDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN_FILE, &CUserHangUpDlg::OnBnClickedOpenFile)
	ON_BN_CLICKED(IDC_CONNECT, &CUserHangUpDlg::OnBnClickedConnect)
//	ON_BN_CLICKED(IDC_BUTTON1, &CUserHangUpDlg::OnBnClickedButton1)

	ON_MESSAGE(WM_LOGON_SUCCESS, OnLogonSuccess)
	ON_MESSAGE(WM_LOGON_FAILURE, OnLogonFailure)
	ON_MESSAGE(WM_LOGON_BREAK, OnSocketLogonBreak)
	ON_MESSAGE(WM_THREAD_QUIT, OnAllThreadQuit)
	ON_MESSAGE(WM_GAMEINFO_UPDATE,OnGameInfoUpdate)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SET, &CUserHangUpDlg::OnBnClickedConnectSet)
	ON_BN_CLICKED(IDC_CHANGE_CONNECT, &CUserHangUpDlg::OnBnClickedChangeConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserHangUpDlg::OnBnClickedAddUser)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserHangUpDlg::OnBnClickedDELUser)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserHangUpDlg::OnBnClickedAddGame)
	ON_BN_CLICKED(IDC_BUTTON7, &CUserHangUpDlg::OnBnClickedDelGame)
	ON_CBN_EDITUPDATE(IDC_COMBO2, &CUserHangUpDlg::OnCbnEditupdateCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CUserHangUpDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON8, &CUserHangUpDlg::OnBnClickedUpdateGameInfo)
	ON_BN_CLICKED(IDC_BUTTON9, &CUserHangUpDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON5, &CUserHangUpDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON10, &CUserHangUpDlg::OnBnClickedChangeUserInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCOUNT, &CUserHangUpDlg::OnCbnSelchangeComboAccount)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON11, &CUserHangUpDlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CUserHangUpDlg 消息处理程序

BOOL CUserHangUpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |   LVS_EDITLABELS|   LVS_EX_SUBITEMIMAGES ); 
	m_List.InsertColumn(0,"账号");
	m_List.InsertColumn(1,"密码");
	m_List.InsertColumn(2,"端口");
	m_List.InsertColumn(3,"KindID");
	m_List.InsertColumn(4,"游戏");
	m_List.InsertColumn(5,"游戏版本号");
	m_List.InsertColumn(6,"状态");
	m_List.SetColumnWidth(0,50);
	m_List.SetColumnWidth(1,70);
	m_List.SetColumnWidth(2,50);
	m_List.SetColumnWidth(3,50);
	m_List.SetColumnWidth(4,120);
	m_List.SetColumnWidth(5,80);
	m_List.SetColumnWidth(6,500);



//	m_IP.SetWindowText("60.191.137.104");
	OnOpenAddressFile();

	m_GameInfo.CreateUserInfoTable();
	m_GameInfo.CreateGameInfoTable();

	m_GameInfo.SelectUserInfo();
	m_GameInfo.SelectGameInfo();
	OnGetDataBase();
	OnGetGameList();
	OnInsertList();

//	OnPlazzConnection();

// 	m_SocketClient.m_IsPlazaLogon = true;
// 	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));
// 
// 	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);
// 
// 	pConnectThread = ::AfxBeginThread(_ConnectThread,this);
// 
// 	if (m_SocketClient.OnSocketConnect(m_dwIPAddress,8100) == true)
// 	{
// 		//获取对象
// // 		ASSERT(CServerListData::GetInstance()!=NULL);
// // 		CServerListData * pServerListData=CServerListData::GetInstance();
// 	}

//	SetTimer(PLAZALOHON,60000,NULL);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUserHangUpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUserHangUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUserHangUpDlg::OnOpenAddressFile()
{
	CStdioFile file;
	CString filePathName;

	filePathName = GetModuleDir();
	CString filename = "/IPCollocation.txt";
	filePathName += filename;

	if(filePathName == "")  return;
	if(!file.Open(filePathName,CFile::modeRead))
	{
//		MessageBox("can not open file!");
		return;
	}

	CString strLen;
	CString strIP,strBKIP;

	while(file.ReadString(strLen))
	{
		int iLen = strLen.GetLength();
		int iSpaceIndex = strLen.Find(",");
		strIP = strLen.Left(iSpaceIndex);
		strBKIP = strLen.Right(iLen - iSpaceIndex - 1);
	}

	m_IP.SetWindowText(strIP);
	m_BkIP.SetWindowText(strBKIP);

}

void CUserHangUpDlg::OnPlazzConnection()
{
//  	m_SocketClient->m_IsPlazaLogon = true;
// 	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));
// 
// 	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);
// 
//	pConnectThread = ::AfxBeginThread(_ConnectThread,this);
// 
// 	if (m_SocketClient->OnSocketConnect(m_dwIPAddress,8100) == true)
// 	{
// 		//获取对象
// // 		ASSERT(CServerListData::GetInstance()!=NULL);
// // 		CServerListData * pServerListData=CServerListData::GetInstance();
// 	}
}

void CUserHangUpDlg::OnGetGameList()
{
	int nGameCount = m_GameInfo.m_GameInfo.GetCount();
	int nCount = m_CombGame.GetCount();
	for (int i = 0;i<nGameCount;i++)
	{
		if (nCount == 0)
		{
			m_CombGame.AddString(m_GameInfo.m_GameInfo[i]->GameName);
			m_CombGameInfoList.AddString(m_GameInfo.m_GameInfo[i]->GameName);
		}else
		{
			for (int j=0;j<nCount;j++)
			{
				int nCount = m_CombGame.FindStringExact(j,m_GameInfo.m_GameInfo[i]->GameName);
				if (nCount == CB_ERR)
				{
					m_CombGame.AddString(m_GameInfo.m_GameInfo[i]->GameName);
					m_CombGameInfoList.AddString(m_GameInfo.m_GameInfo[i]->GameName);
				}
			}
		}
	}
}

VOID CUserHangUpDlg::OnGetDataBase()
{
	int nUserCount = m_GameInfo.m_UserInfo.GetCount();
	int nGameCount = m_GameInfo.m_GameInfo.GetCount();
	
// 	for (int k=0;k<nUserCount;k++)
// 	{
// 		for (int p=0;p<m_AllUserInfo.GetCount();p++)
// 		{
// 			if (m_GameInfo.m_UserInfo[k]->UserID == m_AllUserInfo[p]->UserID)
// 			{
// 				return;
// 			}
// 		}
// 	}
	m_AllUserInfo.RemoveAll();

// 	for (int k=0;k<nUserCount;k++)
// 	{
// 		
// 	}

	for (int i=0;i<nUserCount;i++)
	{
		for (int j=0;j<nGameCount;j++)
		{
			if (m_GameInfo.m_UserInfo[i]->Port == m_GameInfo.m_GameInfo[j]->Port && m_GameInfo.m_UserInfo[i]->GameID == m_GameInfo.m_GameInfo[j]->GameID)
			{
				stgUserInfo* pUserInfo = new stgUserInfo;
				pUserInfo->UserID = m_GameInfo.m_UserInfo[i]->UserID;
				pUserInfo->PassWord = m_GameInfo.m_UserInfo[i]->PassWord;
				pUserInfo->GameID = m_GameInfo.m_GameInfo[j]->GameID;
				pUserInfo->Port = m_GameInfo.m_GameInfo[j]->Port;
				pUserInfo->Version = m_GameInfo.m_GameInfo[j]->Version;
				pUserInfo->GameName = m_GameInfo.m_GameInfo[j]->GameName;
				m_AllUserInfo.Add(pUserInfo);
				m_ComboAccount.AddString(pUserInfo->UserID);
			}
		}
	}

// 	int nCount = m_AllUserInfo.GetCount();
// 	for (int i=0;i<nCount;i++)
// 	{
// 		m_List.InsertItem(i,m_AllUserInfo[i]->UserID);
// 		m_List.SetItemText(i,0,m_AllUserInfo[i]->UserID);
// 		m_List.SetItemText(i,1,m_AllUserInfo[i]->PassWord);
// 		m_List.SetItemText(i,2,m_AllUserInfo[i]->Port);
// 		m_List.SetItemText(i,3,m_AllUserInfo[i]->GameName);
// 		m_List.SetItemText(i,4,m_AllUserInfo[i]->Version);
// 
// 	}
}

void CUserHangUpDlg::OnInsertList()
{
// 	DWORD userID;
 	int nCount = m_AllUserInfo.GetCount();
// 	for (int j=0;j<m_List.GetItemCount();j++)
// 	{
// 		userID = _ttoi(m_List.GetItemText(j,0));
// 		for (int k=0;k<nCount;k++)
// 		{
// 			if (userID == _ttoi(m_AllUserInfo[k]->UserID))
// 			{
// 				return;
// 			}
// 		}
// 	}

	for (int i=0;i<nCount;i++)
	{
		m_List.InsertItem(i,m_AllUserInfo[i]->UserID);
		m_List.SetItemText(i,0,m_AllUserInfo[i]->UserID);
		m_List.SetItemText(i,1,m_AllUserInfo[i]->PassWord);
		m_List.SetItemText(i,2,m_AllUserInfo[i]->Port);
		m_List.SetItemText(i,3,m_AllUserInfo[i]->GameID);
		m_List.SetItemText(i,4,m_AllUserInfo[i]->GameName);
		m_List.SetItemText(i,5,m_AllUserInfo[i]->Version);
	}

	return;
}

void CUserHangUpDlg::OnBnClickedOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
//	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

	CStdioFile file;
	CString filePathName;
	int row;
	CString result;

// 	//生成一个对话框
// 	lpszOpenFile = new CFileDialog
// 		(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.txt)|*.txt|所有文件(*.*)|*.*|");
// 
// 	if(lpszOpenFile->DoModal() == IDOK )//假如点击对话框确定按钮
// 	{
// 		filePathName = lpszOpenFile->GetPathName();//得到打开文件的路径
// 		SetWindowText(filePathName);//在窗口标题上显示路径
// 	}
	filePathName = GetModuleDir();
	CString filename = "/AccountsInfo.txt";
	filePathName += filename;

	if(filePathName == "")  return;
	if(!file.Open(filePathName,CFile::modeRead))
	{
		MessageBox("can not open file!");
		return;
	}
	if (m_List.GetItemCount()!=0)
	{
		OnBnClickedButton1();
		m_List.DeleteAllItems();
	}

	CString strLine,strTemp,sMid;
	row = 0;
	
	while(file.ReadString(strLine))
	{
		int iLen = strLine.GetLength();
		int iSpaceIndex = strLine.Find(",");
		sName = strLine.Left(iSpaceIndex);
		strTemp = strLine.Right(iLen - iSpaceIndex - 1);

		iLen = strTemp.GetLength();
		iSpaceIndex = strTemp.Find(",");
		sPwd = strTemp.Left(iSpaceIndex);
		sMid = strTemp.Right(iLen - iSpaceIndex - 1);

		iLen = sMid.GetLength();
		iSpaceIndex = sMid.Find(",");
		sKindID = sMid.Left(iSpaceIndex);
		strTemp = sMid.Right(iLen - iSpaceIndex - 1);

		iLen = strTemp.GetLength();
		iSpaceIndex = strTemp.Find(",");
		sPort = strTemp.Left(iSpaceIndex);
		sMid = strTemp.Right(iLen - iSpaceIndex - 1);

		iLen = sMid.GetLength();
		iSpaceIndex = sMid.Find(",");
		sProcessVersion = sMid.Left(iSpaceIndex);
		sGameName = sMid.Right(iLen - iSpaceIndex - 1);


		m_GameInfo.InsertUserInfo(_ttoi(sName),sPwd,_ttoi(sKindID),_ttoi(sPort));
//		m_GameInfo.InsertGameInfo(_ttoi(sKindID),_ttoi(sPort),_ttoi(sProcessVersion),sGameName);
// 		m_List.InsertItem(row,sName);
// 		m_List.SetItemText(row,0,sName);
// 		m_List.SetItemText(row,1,sPwd);
// 		m_List.SetItemText(row,2,sKindID);
// 		m_List.SetItemText(row,3,sPort);
// 		m_List.SetItemText(row,4,sProcessVersion);
/*		m_List.SetItemText(row,5,"等待连接!");*/

		row++;
	}

	if (m_ArrayIndex == m_SocketArray.GetCount())
	{
		m_BtConnect.SetWindowText("连接");
		m_BtConnect.EnableWindow(TRUE);
		m_BtChangeConnect.EnableWindow(TRUE);
		m_BtOpenFile.EnableWindow(TRUE);
		m_ArrayIndex = 0;
	}

	m_GameInfo.SelectUserInfo();
	OnGetDataBase();
	OnInsertList();

}

void CUserHangUpDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szName,szPwd;
	if (OnConnectServer()==false)
	{
		return;
	}

// 	//变量定义
// 	WORD wPacketSize,wSubCmdID;
// 	BYTE cbBuffer[SOCKET_TCP_PACKET];
// 	ZeroMemory(&cbBuffer,sizeof(cbBuffer));
// 
// 	int nItem = m_List.GetItemCount();
// 	if (nItem == 0)
// 	{
// 		AfxMessageBox("列表数据没有空！");
// 		return;
// 	}
// 
// 	CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts*)cbBuffer;
// 	//系统信息
// 	pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;
// 
// 	for (int i = 0;i<nItem;i++)
// 	{
// 		szName = m_List.GetItemText(i,1);
// 		szPwd = m_List.GetItemText(i,2);
// 
// // 		pLogonAccounts->szAccounts = szName;
// // 		pLogonAccounts->szPassword = szPwd;
// 
// 		lstrcpyn(pLogonAccounts->szAccounts,szName.GetBuffer(szName.GetLength()),CountArray(pLogonAccounts->szAccounts));
// 		lstrcpyn(pLogonAccounts->szPassword,szPwd.GetBuffer(szPwd.GetLength()),CountArray(pLogonAccounts->szPassword));
// 
// 		m_TCPSocketModule->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonAccounts));
// 	}
}
CString CUserHangUpDlg::GetModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 

	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath.Left( nPos ); 
}

bool CUserHangUpDlg::OnConnectServer()
{
	CString lPort;
	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));
	GetDlgItemText(IDC_BKIP,m_szBkCustomServer,CountArray(m_szBkCustomServer));

	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);
	m_dwBackAddress = inet_addr((LPSTR)(LPCTSTR)m_szBkCustomServer);

	int nItem = m_List.GetItemCount();
	int nPort = 0;

	OnReSetArray();


	if (nItem == 0)
	{
		return false;
	}
	for (int i=0;i<nItem;i++)
	{
		nPort = _ttoi(m_List.GetItemText(i,2));
// 		if (nPort != m_wCurrentPort)
// 		{	
			m_wCurrentPort = nPort;
			CSocketClient* pSocketClient = new CSocketClient;
			pSocketClient->m_IsPlazaLogon = false;
			pSocketClient->m_wCurrentPort = m_wCurrentPort;
			pSocketClient->m_dwIPAddress = m_dwIPAddress;
			pSocketClient->m_wProcessVersion = _ttoi(m_List.GetItemText(i,5));
			pSocketClient->m_UserID = _ttoi(m_List.GetItemText(i,0));
			pSocketClient->m_wKindID = _ttoi(m_List.GetItemText(i,3));
			pSocketClient->m_wPassWord = m_List.GetItemText(i,1);

			pSocketClient->m_dwBackAddress = m_dwBackAddress;
			pSocketClient->m_dwBackPort = m_wCurrentPort;

			if (pSocketClient->OnSocketConnect(m_dwIPAddress,m_wCurrentPort) == true)
			{
				m_List.SetItemText(i,6,"正在连接...");
				
				m_SocketArray.Add(pSocketClient);
			}else
			{
				m_List.SetItemText(i,6,"连接失败,请检查网络!");
				//m_SocketArray.Add(pSocketClient);
				SafeDelete(pSocketClient);

				return false;
			}
//		}
	}

	return true;
}

void CUserHangUpDlg::OnReSetArray()
{
	if (m_SocketArray.GetCount()!=0)
	{
		for (int i=0;i<m_SocketArray.GetCount();i++)
		{
			SafeDelete(m_SocketArray[i]);
		}

		m_SocketArray.RemoveAll();
	}
}

LRESULT CUserHangUpDlg::OnLogonSuccess(WPARAM wParam, LPARAM lParam)
{
	if (m_ArrayIndex == m_SocketArray.GetCount())
	{
		m_BtConnect.SetWindowText("连接");
		m_BtConnect.EnableWindow(TRUE);
		m_BtChangeConnect.EnableWindow(TRUE);
		m_BtOpenFile.EnableWindow(TRUE);
		m_ArrayIndex = 0;
	}

	
	DWORD lUserID = (DWORD)wParam;

	for (int i=0;i<m_List.GetItemCount();i++)
	{
		DWORD nUserID = _ttoi(m_List.GetItemText(i,0));
		
		if (lUserID == nUserID)
		{
			m_List.SetItemText(i,6,"连接成功!");
		}

	}
	
	return true;
}

LRESULT CUserHangUpDlg::OnLogonFailure(WPARAM wParam, LPARAM lParam)
{
	if (m_ArrayIndex == m_SocketArray.GetCount())
	{
		m_BtConnect.SetWindowText("连接");
		m_BtConnect.EnableWindow(TRUE);
		m_BtChangeConnect.EnableWindow(TRUE);
		m_BtOpenFile.EnableWindow(TRUE);
		m_ArrayIndex = 0;
	}

	DWORD lUserID = (DWORD)wParam;

	CMD_GR_LogonFailure* pLogonFailure = (CMD_GR_LogonFailure*)lParam;

	for (int i=0;i<m_List.GetItemCount();i++)
	{
		DWORD nUserID = _ttoi(m_List.GetItemText(i,0));

		if (lUserID == nUserID)
		{
			m_List.SetItemText(i,6,pLogonFailure->szDescribeString);
		}

	}


	return true;
}

WORD CUserHangUpDlg::OnLogonPacket(BYTE cbBuffer[], WORD wBufferSize)
{
	//变量定义
	CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts *)cbBuffer;

	//系统信息
	pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;

	//机器标识
//	CWHService::GetMachineIDEx(pLogonAccounts->szMachineID);
	int  nItem = m_List.GetItemCount();
	if (nItem == 0)
	{
		
	}


	return sizeof(CMD_GP_LogonAccounts);
}

bool CUserHangUpDlg::OnSocketLogonFinish(VOID * pData, WORD wDataSize)
{
	//变量定义
	CMD_GR_LogonUserID LogonUserID;
	ZeroMemory(&LogonUserID,sizeof(LogonUserID));

	LogonUserID.dwPlazaVersion = VERSION_PLAZA;
	LogonUserID.dwFrameVersion = VERSION_FRAME;
	

	return true;
}

LRESULT CUserHangUpDlg::OnSocketLogonBreak(WPARAM wParam, LPARAM lParam)
{
	DWORD lUserID = (DWORD)wParam;

//	CMD_GR_LogonFailure* pLogonFailure = (CMD_GR_LogonFailure*)lParam;

	for (int i=0;i<m_List.GetItemCount();i++)
	{
		DWORD nUserID = _ttoi(m_List.GetItemText(i,0));

		if (lUserID == nUserID)
		{
			m_List.SetItemText(i,6,"连接断开,尝试重新连接...");
		}

	}

	if (m_ArrayIndex == m_SocketArray.GetCount() || m_SocketArray.GetCount() == 0)
	{
		m_BtConnect.SetWindowText("连接");
		m_BtConnect.EnableWindow(TRUE);
		m_BtChangeConnect.EnableWindow(TRUE);
		m_BtOpenFile.EnableWindow(TRUE);
		m_ArrayIndex = 0;
	}


	return true;
}


LRESULT CUserHangUpDlg::OnAllThreadQuit(WPARAM wParam, LPARAM lParam)
{
	m_BtConnect.SetWindowText("正在重接...");
	m_BtConnect.EnableWindow(FALSE);
	m_BtChangeConnect.EnableWindow(FALSE);
	m_BtOpenFile.EnableWindow(FALSE);

	DWORD lUserID = (DWORD)wParam;

	for (int i=0;i<m_List.GetItemCount();i++)
	{
		DWORD nUserID = _ttoi(m_List.GetItemText(i,0));

// 		if (lUserID == nUserID)
// 		{
			m_List.SetItemText(i,6,"正在断开连接...");
//		}

	}

 	m_ArrayIndex++;

	return TRUE;
}

bool CUserHangUpDlg::OnSocketLogonSuccess(VOID * pData, WORD wDataSize)
{	

	return true;
}
void CUserHangUpDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_SocketArray.GetCount();
	if (nCount == 0)
	{
		return;
	}
	for (int i=0;i<nCount;i++)
	{
		if (m_SocketArray[i] != NULL)
		{
			SafeDelete(m_SocketArray[i]);
		}
//		m_SocketArray[i]->m_TCPSocketModule->CloseSocket();
		m_List.SetItemText(i,6,"断开连接!");
	}


//	DWORD ExitCode;

// 	TerminateThread(_SendThread,0);
// 
// 	if (GetExitCodeThread(_SendThread,&ExitCode))
// 	{
// 		if (ExitCode==STILL_ACTIVE)
// 		{
// 			AfxMessageBox("a");
// 		}
// 	}

//	CloseHandle(SendThread);

//	OnReSetArray();
}


bool CUserHangUpDlg::OnReConnect(DWORD UserID)
{
	DWORD lUserID;

	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));

	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);

	for (int i=0;i<m_SocketArray.GetCount();i++)
	{
		if (m_SocketArray[i]->m_UserID == UserID)
		{
			SafeDelete(m_SocketArray[i]);
			m_SocketArray.RemoveAt(i);
		}
	}
	for (int n=0;n<m_List.GetItemCount();n++)
	{
		lUserID = _ttoi(m_List.GetItemText(n,0));
		if (lUserID == UserID)
		{
			CSocketClient* pSocketClient = new CSocketClient;
			pSocketClient->m_IsPlazaLogon = false;
			pSocketClient->m_wCurrentPort = _ttoi(m_List.GetItemText(n,2));
//			pSocketClient->m_dwIPAddress = m_dwIPAddress;
			pSocketClient->m_wProcessVersion = _ttoi(m_List.GetItemText(n,5));
			pSocketClient->m_UserID = lUserID;
			pSocketClient->m_wKindID = _ttoi(m_List.GetItemText(n,3));
			pSocketClient->m_wPassWord = m_List.GetItemText(n,1);

			if (pSocketClient->OnSocketConnect(m_dwIPAddress,m_wCurrentPort) == true)
			{
				m_List.SetItemText(n,6,"正在连接...");
				m_SocketArray.Add(pSocketClient);
			}else
			{
				m_List.SetItemText(n,6,"连接失败!");
				SafeDelete(pSocketClient);
			}

		}
		
	}

	return true;
}

//时间消息
VOID CUserHangUpDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == PLAZALOHON)
	{
		
// 		m_SocketClient->m_IsPlazaLogon = true;
// 		GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));
// 
// 		m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);
// 
// 		if (m_SocketClient->OnSocketConnect(m_dwIPAddress,8100) == true)
// 		{
// 			//获取对象
// // 			ASSERT(CServerListData::GetInstance()!=NULL);
// // 			CServerListData * pServerListData=CServerListData::GetInstance();
// //			Sleep(20000);
// 
// //			m_SocketClient->m_TCPSocketModule->CloseSocket();
// 		}

	}

	__super::OnTimer(nIDEvent);

	return;
}
void CUserHangUpDlg::OnBnClickedConnectSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  strIp, strBKIP, strAIP;

	GetDlgItemText(IDC_IPCONTROL,strIp);
	GetDlgItemText(IDC_BKIP,strBKIP);
	strAIP.Format("%s,%s",strIp,strBKIP);

	CStdioFile file;
	CString filePathName;

	filePathName = GetModuleDir();
	CString filename = "/IPCollocation.txt";
	filePathName += filename;

	if(filePathName == "")  return;
	if(!file.Open(filePathName,CFile::modeCreate|CFile::typeText|CFile::modeReadWrite))
	{
		MessageBox("can not open file!");
		return;
	}else
	{
		file.WriteString(strAIP);
// 		file.WriteString("\r\n");
// 		file.WriteString(strBKIP);
// 		file.WriteString("\r\n");
		file.Close();
	}


}

void CUserHangUpDlg::OnBnClickedChangeConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString lPort;
	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));
	GetDlgItemText(IDC_BKIP,m_szBkCustomServer,CountArray(m_szBkCustomServer));

	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);
	m_dwBackAddress = inet_addr((LPSTR)(LPCTSTR)m_szBkCustomServer);

	int nItem = m_List.GetItemCount();
	WORD nPort = 0;

	OnReSetArray();

	if (nItem == 0)
	{
		return;
	}
	for (int i=0;i<nItem;i++)
	{
		nPort = _ttoi(m_List.GetItemText(i,2));

		m_wCurrentPort = nPort;

		CSocketClient* pSocketClient = new CSocketClient;
		pSocketClient->m_IsPlazaLogon = false;
		pSocketClient->m_IsBkConnect = true;
		pSocketClient->m_wCurrentPort = m_wCurrentPort;
		pSocketClient->m_dwIPAddress = m_dwIPAddress;
		pSocketClient->m_wProcessVersion = _ttoi(m_List.GetItemText(i,5));
		pSocketClient->m_UserID = _ttoi(m_List.GetItemText(i,0));
		pSocketClient->m_wKindID = _ttoi(m_List.GetItemText(i,3));
		pSocketClient->m_wPassWord = m_List.GetItemText(i,1);

		pSocketClient->m_dwBackAddress = m_dwBackAddress;
		pSocketClient->m_dwBackPort = m_wCurrentPort;

		if (pSocketClient->OnSocketConnect(m_dwBackAddress,m_wCurrentPort) == true)
		{
			m_List.SetItemText(i,6,"正在连接...");

			m_SocketArray.Add(pSocketClient);
		}else
		{
			m_List.SetItemText(i,6,"连接失败,请检查网络!");
			//m_SocketArray.Add(pSocketClient);
			SafeDelete(pSocketClient);

			return;
		}

	}

}

void CUserHangUpDlg::OnBnClickedAddUser()
{
	// TODO: 在此添加控件通知处理程序代码
//	int nCombIndex = m_CombGame.GetCurSel();
	CString strCBText,strUserID,strPassWord;
// 	m_CombGame.GetLBText(nCombIndex,strCBText);

	m_ComboAccount.GetWindowText(strUserID);
	m_EDPassword.GetWindowText(strPassWord);

	if (strUserID == "" || strPassWord == "")
	{
		AfxMessageBox("UserID或者密码不能为空！");

		return;
	}

	m_CombGame.GetWindowText(strCBText);

	if (strCBText == "")
	{
		AfxMessageBox("没有选择游戏!");
		return;
	}

	for (int p=0;p<m_AllUserInfo.GetCount();p++)
	{
		if (strUserID == m_AllUserInfo[p]->UserID)
		{
			AfxMessageBox("用户已存在!");
			return;
		}
	}

	int nGameCount = m_GameInfo.m_GameInfo.GetCount();
	stgUserInfo* pAllUserInfo = new stgUserInfo;
	for (int i=0;i<nGameCount;i++)
	{
		if (strCBText == m_GameInfo.m_GameInfo[i]->GameName)
		{
			/*stgUserInfo* pAllUserInfo = new stgUserInfo;*/
			pAllUserInfo->UserID = strUserID;
			pAllUserInfo->PassWord = strPassWord;
			pAllUserInfo->GameID = m_GameInfo.m_GameInfo[i]->GameID;
			pAllUserInfo->Port = m_GameInfo.m_GameInfo[i]->Port;
			pAllUserInfo->Version = m_GameInfo.m_GameInfo[i]->Version;
			pAllUserInfo->GameName = m_GameInfo.m_GameInfo[i]->GameName;
			m_GameInfo.InsertUserInfo(_ttoi(strUserID),strPassWord,_ttoi(m_GameInfo.m_GameInfo[i]->GameID),_ttoi(m_GameInfo.m_GameInfo[i]->Port));
			m_AllUserInfo.Add(pAllUserInfo);
		}
	}
	
/*	OnInsertList();*/
	for (int k=0;k<m_List.GetItemCount();k++)
	{
		DWORD userID = _ttoi(m_List.GetItemText(k,0));
		if (userID == _ttoi(pAllUserInfo->UserID))
		{
			return;
		}
	}

	int nCount = m_List.GetItemCount();
	m_List.InsertItem(nCount,pAllUserInfo->UserID);
	m_List.SetItemText(nCount,0,pAllUserInfo->UserID);
	m_List.SetItemText(nCount,1,pAllUserInfo->PassWord);
	m_List.SetItemText(nCount,2,pAllUserInfo->Port);
	m_List.SetItemText(nCount,3,pAllUserInfo->GameID);
	m_List.SetItemText(nCount,4,pAllUserInfo->GameName);
	m_List.SetItemText(nCount,5,pAllUserInfo->Version);

	m_GameInfo.SelectUserInfo();

	return;
}

void CUserHangUpDlg::OnBnClickedDELUser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUserID;
	bool isUserDel = false;
	m_ComboAccount.GetWindowText(strUserID);

	if (strUserID == "")
	{
		AfxMessageBox("UserID不能为空!");
		return;
	}

	for (int p=0;p<m_AllUserInfo.GetCount();p++)
	{
		if (strUserID == m_AllUserInfo[p]->UserID)
		{
			m_AllUserInfo.RemoveAt(p);
			isUserDel = true;
		}
	}
	if (isUserDel == false)
	{
		AfxMessageBox("用户不存在或已删除!");
		return;
	}

	m_GameInfo.DeleteUserInfo(_ttoi(strUserID));

	for (int i=0;i<m_List.GetItemCount();i++)
	{
		if (strUserID == m_List.GetItemText(i,0))
		{
			m_List.DeleteItem(i);
		}
	}

	int n = m_ComboAccount.GetCurSel();
	m_ComboAccount.DeleteString(n);

	m_GameInfo.SelectUserInfo();

	return;
}

void CUserHangUpDlg::OnBnClickedAddGame()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGameName,strGameID,strPort,strVersion;
	m_EDGameName.GetWindowText(strGameName);
	m_EDGameID.GetWindowText(strGameID);
	m_EDPort.GetWindowText(strPort);
	m_EDVersion.GetWindowText(strVersion);

	if (strGameName == "" || strGameID == "" || strPort == "" || strVersion == "")
	{
		AfxMessageBox("信息不完全,检查后添加!");
		return;
	}

	for (int i=0;i<m_GameInfo.m_GameInfo.GetCount();i++)
	{
		if (strPort == m_GameInfo.m_GameInfo[i]->Port)
		{
			AfxMessageBox("游戏已存在或游戏端口重复,确认信息重新添加!");

			return;
		}
	}

	m_GameInfo.InsertGameInfo(_ttoi(strGameID),_ttoi(strPort),_ttoi(strVersion),strGameName);

	m_CombGame.AddString(strGameName);
	m_CombGameInfoList.AddString(strGameName);

	m_GameInfo.SelectGameInfo();
}

void CUserHangUpDlg::OnBnClickedDelGame()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort,strGameName;
	bool   isPortDel = false;
//	m_EDPort.GetWindowText(strPort);
// 	int nCombIndex = m_CombGameInfoList.GetCurSel();
// 	m_CombGameInfoList.GetLBText(nCombIndex,strGameName);
	m_CombGameInfoList.GetWindowText(strGameName);

	if (strGameName == "" /*&& strPort == ""*/)
	{
		AfxMessageBox("没有选择游戏，确认信息后删除!");
		return;
	}

	int j;
	for (j=0;j<m_GameInfo.m_GameInfo.GetCount();j++)
	{
		if (strGameName == m_GameInfo.m_GameInfo[j]->GameName)
		{
			strPort = m_GameInfo.m_GameInfo[j]->Port;
			m_GameInfo.m_GameInfo.RemoveAt(j);
			/*m_GameInfo.DeleteGameInfo(_ttoi(m_GameInfo.m_GameInfo[j]->Port));*/
			isPortDel = true;
		}
	}

	if (isPortDel == false)
	{
		AfxMessageBox("游戏已删除,检查信息后删除!");
		return;
	}

	m_GameInfo.DeleteGameInfo(_ttoi(strPort));

	int nCBCount = m_CombGame.GetCount();

	for (int i=0;i<nCBCount;i++)
	{
		int nCBIndex = m_CombGame.FindStringExact(i,strGameName);
		int nCBindex1 = m_CombGameInfoList.FindStringExact(i,strGameName);
		if (nCBIndex != CB_ERR)
		{
			m_CombGame.DeleteString(nCBIndex);
		}
		if (nCBindex1 != CB_ERR)
		{
			m_CombGameInfoList.DeleteString(nCBIndex);
		}
	}

	/*m_GameInfo.DeleteGameInfo(_ttoi(strPort));*/

	m_GameInfo.SelectGameInfo();
	
}

void CUserHangUpDlg::OnCbnEditupdateCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGameName;
	int nCombIndex = m_CombGameInfoList.GetCurSel();
	m_CombGameInfoList.GetLBText(nCombIndex,strGameName);

	if (strGameName == "" /*&& strPort == ""*/)
	{
		AfxMessageBox("没有选择游戏，确认信息后删除!");
		return;
	}

	for (int i=0;i<m_GameInfo.m_GameInfo.GetCount();i++)
	{
		if (strGameName == m_GameInfo.m_GameInfo[i]->GameName)
		{
			m_EDGameName.SetWindowText(m_GameInfo.m_GameInfo[i]->GameName);
			m_EDGameID.SetWindowText(m_GameInfo.m_GameInfo[i]->GameID);
			m_EDPort.SetWindowText(m_GameInfo.m_GameInfo[i]->Port);
			m_EDVersion.SetWindowText(m_GameInfo.m_GameInfo[i]->Version);
		}
	}
}

void CUserHangUpDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGameName;
	int nCombIndex = m_CombGameInfoList.GetCurSel();
	m_CombGameInfoList.GetLBText(nCombIndex,strGameName);

	if (strGameName == "" /*&& strPort == ""*/)
	{
		AfxMessageBox("没有选择游戏，确认信息后删除!");
		return;
	}

	for (int i=0;i<m_GameInfo.m_GameInfo.GetCount();i++)
	{
		if (strGameName == m_GameInfo.m_GameInfo[i]->GameName)
		{
			m_EDGameName.SetWindowText(m_GameInfo.m_GameInfo[i]->GameName);
			m_EDGameID.SetWindowText(m_GameInfo.m_GameInfo[i]->GameID);
			m_EDPort.SetWindowText(m_GameInfo.m_GameInfo[i]->Port);
			m_EDVersion.SetWindowText(m_GameInfo.m_GameInfo[i]->Version);
		}
	}
}

void CUserHangUpDlg::OnBnClickedUpdateGameInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGameName,strGameID,strPort,strVersion;
	m_EDGameName.GetWindowText(strGameName);
	m_EDGameID.GetWindowText(strGameID);
	m_EDPort.GetWindowText(strPort);
	m_EDVersion.GetWindowText(strVersion);
// 	int nCombIndex = m_CombGameInfoList.GetCurSel();
// 	m_CombGameInfoList.GetLBText(nCombIndex,strGameName);
	m_CombGameInfoList.GetWindowText(strGameName);

	if (strGameName == "" /*&& strPort == ""*/)
	{
		AfxMessageBox("没有选择游戏，确认信息后删除!");
		return;
	}

	for (int i=0;i<m_GameInfo.m_GameInfo.GetCount();i++)
	{
		if (strGameName == m_GameInfo.m_GameInfo[i]->GameName)
		{
			if (m_GameInfo.UpdateGameInfo(_ttoi(strGameID),_ttoi(strPort),_ttoi(strVersion),strGameName)==true)
			{
				AfxMessageBox("更行成功!");
			}else
				AfxMessageBox("更新失败!");
			
		}
	}

	m_GameInfo.SelectGameInfo();
}

void CUserHangUpDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	OnGetDataBase();
//	OnGetGameList();
//	m_List.DeleteAllItems();
//	OnInsertList();

	int nCount = m_List.GetItemCount();
	CString strUserID;

	for(int i=0;i<nCount;i++)
	{
		strUserID = m_List.GetItemText(i,0);
		for(int j=0;j<m_AllUserInfo.GetCount();j++)
		{
			if (strUserID == m_AllUserInfo[j]->UserID)
			{
				m_List.SetItemText(i,0,m_AllUserInfo[j]->UserID);
				m_List.SetItemText(i,1,m_AllUserInfo[j]->PassWord);
				m_List.SetItemText(i,2,m_AllUserInfo[j]->Port);
				m_List.SetItemText(i,3,m_AllUserInfo[j]->GameID);
				m_List.SetItemText(i,4,m_AllUserInfo[j]->GameName);
				m_List.SetItemText(i,5,m_AllUserInfo[j]->Version);
			}
		}
	}
}

void CUserHangUpDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameInfo.DropUserInfoTalbe();
	m_List.DeleteAllItems();
	m_AllUserInfo.RemoveAll();
	m_GameInfo.m_UserInfo.RemoveAll();
}

void CUserHangUpDlg::OnBnClickedChangeUserInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString UserID,PassWord;

	m_ComboAccount.GetWindowText(UserID);
	m_EDPassword.GetWindowText(PassWord);

	CString strGameName;
// 	int nCombIndex = m_CombGame.GetCurSel();
// 	m_CombGame.GetLBText(nCombIndex,strGameName);
	m_CombGame.GetWindowText(strGameName);

// 	if (strGameName == "")
// 	{
// 		AfxMessageBox("没有选择游戏!");
// 		return;
// 	}

	if (UserID == "")
	{
		AfxMessageBox("UserID不能为空!");
		return;
	}

	int nGameCount = m_GameInfo.m_GameInfo.GetCount();
	int nAllUserCount = m_AllUserInfo.GetCount();
	/*stgUserInfo* pAllUserInfo = new stgUserInfo;*/
	for (int k=0;k<nAllUserCount;k++)
	{
		if (UserID == m_AllUserInfo[k]->UserID)
		{
			for (int i=0;i<nGameCount;i++)
			{
				if (strGameName == m_GameInfo.m_GameInfo[i]->GameName)
				{
					/*stgUserInfo* pAllUserInfo = new stgUserInfo;*/
					m_AllUserInfo[k]->UserID = UserID;
					m_AllUserInfo[k]->PassWord = PassWord;
					m_AllUserInfo[k]->GameID = m_GameInfo.m_GameInfo[i]->GameID;
					m_AllUserInfo[k]->Port = m_GameInfo.m_GameInfo[i]->Port;
					m_AllUserInfo[k]->Version = m_GameInfo.m_GameInfo[i]->Version;
					m_AllUserInfo[k]->GameName = m_GameInfo.m_GameInfo[i]->GameName;
					m_GameInfo.UpdataUserInfo(_ttoi(m_AllUserInfo[k]->UserID),m_AllUserInfo[k]->PassWord,_ttoi(m_AllUserInfo[k]->GameID),_ttoi(m_AllUserInfo[k]->Port));
					/*m_AllUserInfo.Add(pAllUserInfo);*/
				}
			}
		}
	}

	int nCount = m_List.GetItemCount();
	CString strUserID;

	for(int i=0;i<nCount;i++)
	{
		strUserID = m_List.GetItemText(i,0);
		for(int j=0;j<m_AllUserInfo.GetCount();j++)
		{
			if (strUserID == m_AllUserInfo[j]->UserID)
			{
				m_List.SetItemText(i,0,m_AllUserInfo[j]->UserID);
				m_List.SetItemText(i,1,m_AllUserInfo[j]->PassWord);
				m_List.SetItemText(i,2,m_AllUserInfo[j]->Port);
				m_List.SetItemText(i,3,m_AllUserInfo[j]->GameID);
				m_List.SetItemText(i,4,m_AllUserInfo[j]->GameName);
				m_List.SetItemText(i,5,m_AllUserInfo[j]->Version);
			}
		}
	}

	m_GameInfo.SelectUserInfo();
}

void CUserHangUpDlg::OnCbnSelchangeComboAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	CString userID;
	int nCombIndex = m_ComboAccount.GetCurSel();
	m_ComboAccount.GetLBText(nCombIndex,userID);
	
	int nAllUserCount = m_AllUserInfo.GetCount();
	for (int i=0;i<nAllUserCount;i++)
	{
		if (userID == m_AllUserInfo[i]->UserID)
		{
			m_EDPassword.SetWindowText(m_AllUserInfo[i]->PassWord);
			for (int k = 0;k<m_CombGame.GetCount();k++)
			{
				int n = m_CombGame.FindStringExact(k,m_AllUserInfo[i]->GameName);
				if (n != CB_ERR)
				{
					m_CombGame.SetCurSel(n);
				}
			}
		}
	}

	return;
}


LRESULT CUserHangUpDlg::OnGameInfoUpdate(WPARAM wParam, LPARAM lParam)
{
	m_GameInfo.SelectGameInfo();
	OnGetGameList();

	m_SocketClient->m_TCPSocketModule->CloseSocket();
	return true;
}
void CUserHangUpDlg::OnBnClickedButton11()
{
// 	CSocketClient* p = NULL;
// 	p->m_dwBackPort = 90;
	// TODO: 在此添加控件通知处理程序代码
	m_SocketClient->m_IsPlazaLogon = true;
	GetDlgItemText(IDC_IPCONTROL,m_szCustomServer,CountArray(m_szCustomServer));

	m_dwIPAddress = inet_addr((LPSTR)(LPCTSTR)m_szCustomServer);

	if (m_SocketClient->OnSocketConnect(m_dwIPAddress,8100) == true)
	{
		//获取对象
		// 			ASSERT(CServerListData::GetInstance()!=NULL);
		// 			CServerListData * pServerListData=CServerListData::GetInstance();
		//			Sleep(20000);

		//			m_SocketClient->m_TCPSocketModule->CloseSocket();
	}
}
