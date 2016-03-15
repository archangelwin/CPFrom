#include "Stdafx.h"
#include "DlgLogon.h"
#include "GamePlaza.h"
#include "MissionLogon.h"
#include "DlgProxyConfig.h"
#include ".\dlglogon.h"
#include "MessagePop.h"
  
//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					7									//圆角宽度
#define ROUND_CY					7									//圆角高度

//屏幕位置
#define LAYERED_SIZE				5									//分层大小
#define CAPTION_SIZE				35									//标题大小

//控件标识
#define IDC_WEB_PUBLICIZE			300									//浏览控件
//时间标识
#define IDI_DRAW_REGISTER_TIP		10									//

//////////////////////////////////////////////////////////////////////////////////
  
BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)

	//系统消息
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//按钮消息
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
	ON_BN_CLICKED(IDC_PROXY_CONFIG, OnBnClickedProxyConfig)
	ON_BN_CLICKED(IDC_BUTTON_LOGON_QQ, OnBnClickedQQ)

	//连接消息
	ON_STN_CLICKED(IDC_DELETE_RECORD, OnBnClickedDeleteRecord)
	ON_STN_CLICKED(IDC_LOGON_UNBUNDLING, OnBnClickedUnbundling)
	ON_STN_CLICKED(IDC_LOGON_GETPWD, OnBnClickedGetPwd)
	ON_STN_CLICKED(IDC_LOGON_REMPWD, OnBnClickedRemPwd)
	ON_BN_CLICKED(IDC_BT_LOGON_LINK_4, OnBnClickedLogonLink4)

	//控件消息
	ON_CBN_SELCHANGE(IDC_GAME_ID, OnSelchangeGameID)
	ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_CBN_EDITCHANGE(IDC_ACCOUNTS, OnCbnEditchangeAccounts)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeLogonMode)
	//自定消息
	ON_MESSAGE(WM_UPDATE_RESOUCE, OnUpdateResouce)
	ON_MESSAGE(WM_LOGIN_QQ,OnQQLogin)

	ON_WM_MOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLogon::CDlgLogon() : CDialog(IDD_DLG_LOGON)
{
	//登录信息
	m_dwGameID=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLogonServer[0]=0;

	m_pQQRegDialog = NULL;
	//配置变量
	m_cbRemPassword=FALSE;
	m_cbLogonMode=LOGON_BY_ACCOUNTS;
	m_cbAccountType = LOGON_ACCOUNT_NORMAL;
    m_bCanOpenMobileBind = true;
	m_bCanOpenGetPwd = true;
	m_bShowRegTip = true;
	//创建画刷
	m_brBrush.CreateSolidBrush(RGB(215,223,228));

	return;
}

//析构函数
CDlgLogon::~CDlgLogon()
{
	//销毁资源
	if (m_brBrush.GetSafeHandle()!=NULL)
	{
		m_brBrush.DeleteObject();
	}

	//删除对象
	for (INT_PTR i=0;i<m_AccountsInfoArray.GetCount();i++)
	{
		SafeDelete(m_AccountsInfoArray[i]);
	}

	if( NULL != m_pQQRegDialog )
	{
		delete m_pQQRegDialog;
		m_pQQRegDialog = NULL;
	}
	return;
}

//控件绑定
VOID CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//绑定控件
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDC_REGISTER, m_btRegister);
	DDX_Control(pDX, IDC_BUTTON_LOGON_QQ, m_btQQ);

	//绑定控件
	DDX_Control(pDX, IDCANCEL, m_btQuit);
	DDX_Control(pDX, IDC_PROXY_CONFIG, m_btOption);
	DDX_Control(pDX, IDC_DELETE_RECORD, m_btDeleteRecord);

	//其他控件
	DDX_Control(pDX, IDC_GAME_ID, m_GameIDControl);
	DDX_Control(pDX, IDC_ACCOUNTS, m_AccountsControl);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);

	//辅助控件
	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	DDX_Control(pDX, IDC_LOGON_SERVER, m_ServerControl);

	//连接控件
	DDX_Control(pDX, IDC_LOGON_UNBUNDLING, m_Unbundling);
	DDX_Control(pDX, IDC_LOGON_GETPWD, m_GetPwd);
	DDX_Control(pDX, IDC_LOGON_REMPWD, m_RemPwd);
	DDX_Control(pDX, IDC_BT_LOGON_LINK_4, m_btLogonLink4);
	DDX_Control(pDX, IDC_REM_PASSWORD, m_cbRemPwd);
}

//创建函数
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//设置窗口
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//设置标题
	SetWindowText(TEXT("龙马游"));

	//设置字体
	CSkinDialog::SetWndFont(this,NULL);
	
	//加载资源
	CPngImageSB ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));

	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//边框设置
	m_ServerControl.SetDrawBorad(false);
	m_GameIDControl.SetDrawBorad(false);
	m_AccountsControl.SetDrawBorad(false);
	m_PasswordControl.SetDrawBorad(false);
	

	//渲染设置
//	m_ServerControl.SetReadOnly(true);
	m_ServerControl.SetRenderImage(false);	
	m_GameIDControl.SetRenderImage(false);
	m_AccountsControl.SetRenderImage(false);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btQuit.SetButtonImage(IDB_BT_LOGON_QUIT,TEXT("BT_LOGON_QUIT"),hInstance,false,false);
	m_btEnter.SetButtonImage(IDB_BT_LOGON,TEXT("BT_LOGON_ENTER"),hInstance,false,false);
	m_btRegister.SetButtonImage(IDB_BT_LOGON,TEXT("BT_LOGON_REGISTER"),hInstance,false,false);
	m_btQQ.SetButtonImage(IDB_BT_LOGON,TEXT("BT_LOGON_QQ"),hInstance,false,false);
	m_btOption.SetButtonImage(IDB_BT_LOGON_ITEM,TEXT("BT_LOGON_ITEM"),hInstance,false,false);
	//m_btDeleteRecord.SetButtonImage(IDB_BT_LOGON_ITEM,TEXT("BT_LOGON_ITEM"),hInstance,false,false);
	//m_btLogonLink1.SetButtonImage(IDB_BT_LOGON_LINK,TEXT("BT_LOGON_LINK_1"),hInstance,false,false);
	m_btLogonLink3.SetButtonImage(IDB_BT_LOGON_LINK,TEXT("BT_LOGON_LINK_3"),hInstance,false,false);
	m_btLogonLink4.SetButtonImage(IDB_BT_LOGON_LINK,TEXT("BT_LOGON_LINK_4"),hInstance,false,false);
	m_btLogonLink3.ShowWindow(SW_HIDE);
	m_btLogonLink4.ShowWindow(SW_HIDE);
	m_TabControl.ShowWindow(SW_HIDE);

	m_Unbundling.SetBackGroundColor(RGB(93,163,238));
	m_btDeleteRecord.SetBackGroundColor(RGB(88,156,237));
	m_GetPwd.SetBackGroundColor(RGB(88,156,237));
	m_RemPwd.SetBackGroundColor(RGB(88,156,237));
	m_Unbundling.SetHyperLinkTextColor(RGB(25,108,162),RGB(255,0,0),RGB(25,108,162));
	m_btDeleteRecord.SetHyperLinkTextColor(RGB(70,125,160),RGB(255,255,255),RGB(25,108,162));
	m_GetPwd.SetHyperLinkTextColor(RGB(70,125,160),RGB(25,108,162),RGB(25,108,162));
	m_RemPwd.SetHyperLinkTextColor(RGB(70,125,160),RGB(255,255,255),RGB(25,108,162));
	m_Unbundling.SetCustomFont(true,true,true,false/*,-16*/);
	m_btDeleteRecord.SetCustomFont(true,true,true,false);
	m_GetPwd.SetCustomFont(true,true,true,false);
	m_cbRemPwd.SetTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	m_GetPwd.ShowWindow(SW_HIDE);

	//广告控件
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);
	m_PlatformPublicize.ShowWindow(SW_HIDE);

	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/LogonLogo.aspx"),pGlobalServer->GetPlatformServer(3));

	//设置广告
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetWindowPos(NULL,9,45,SizeWindow.cx-9*2,103,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	//加入标签
	m_TabControl.SetItemSize(CSize(100,25));
	m_TabControl.InsertItem(LOGON_BY_ACCOUNTS,TEXT(" 帐号登录 "));
	m_TabControl.InsertItem(LOGON_BY_GAME_ID,TEXT(" I D 登录 "));

	//设置控件
	m_TabControl.SetRenderImage(false);
	m_TabControl.SetTabCtrlColor(RGB(215,223,228),RGB(145,168,183));

	//配置信息
	LoadServerResouce();
	LoadAccountsInfo();
	LoadLogonServerInfo();

	//设置焦点
	if (m_AccountsControl.GetCurSel()!=LB_ERR)
	{
		//消息处理
		OnSelchangeAccounts();
		//设置焦点
		m_PasswordControl.SetFocus();
	}
	else
	{
		//设置焦点
		m_AccountsControl.SetFocus();
	}
	//居中窗口
	CenterWindow(this);

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//分层窗口
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);
	m_btOption.ShowWindow(SW_HIDE);

	INT nTip = pGlobalServer->GetPlatInfo("PlatInfo","bRegTip",0);
	m_bShowRegTip = (nTip==1?true:false);

	TCHAR szRegTips[MAX_PATH];
	pGlobalServer->ReadPlatFileString("PlatInfo","RegTip",szRegTips,MAX_PATH);

	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	if (m_bShowRegTip)
	{
		m_ToolTipCtrl.AddTool(&m_btRegister,szRegTips);
	}
	m_ToolTipCtrl.AddTool(&m_Unbundling,"用手机解除主机绑定");
  
	//TOOLINFO popup = {0};
	//popup.hwnd = m_btRegister.m_hWnd;
	//::GetClientRect(m_btRegister.m_hWnd,&popup.rect);
	//::SendMessage(m_ToolTipCtrl.m_hWnd,TTM_ADDTOOL,0,(LPARAM)&popup);
	//::SendMessage(m_ToolTipCtrl.m_hWnd,TTM_NEWTOOLRECT,0,(LPARAM)&popup);

	return TRUE;
}

//消息解释
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		CRect rcReg;
		m_btRegister.GetWindowRect(&rcReg);

		CRect rcUnBind;
		m_Unbundling.GetWindowRect(&rcUnBind);

		if(rcReg.PtInRect(pMsg->pt))
		{
			m_ToolTipCtrl.MoveWindow(rcReg.left+20,rcReg.top-25,140,20);
		}
		else if(rcUnBind.PtInRect(pMsg->pt))
		{
			m_ToolTipCtrl.MoveWindow(rcUnBind.left-30,rcUnBind.top+20,120,20);
		}
		m_ToolTipCtrl.RelayEvent(pMsg);
	}
	//if (m_ToolTipCtrl.m_hWnd!=NULL)
	//{
	//	m_ToolTipCtrl.RelayEvent(pMsg);
	//}
	//按键过虑
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//确定函数
VOID CDlgLogon::OnOK()
{
	m_cbAccountType = LOGON_ACCOUNT_NORMAL;
	m_sLogonAccount = "";
	if( NULL != m_pQQRegDialog->GetSafeHwnd() )
	{
		delete m_pQQRegDialog;
		m_pQQRegDialog = NULL;
	}
	//获取信息
	if (GetInformation()==false) return;

	//隐藏窗口
	ShowWindow(SW_HIDE);

	//执行登录
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);

	return;
}

//取消消息
VOID CDlgLogon::OnCancel()
{
	//关闭窗口
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

	return;
}

//构造数据
WORD CDlgLogon::ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags,int nValidateType,CString sCode,int LogonMode)
{
	//变量定义
	TCHAR szPassword[LEN_MD5];
	CWHEncrypt::MD5Encrypt(m_szPassword,szPassword);

	if (LogonMode == -1)//没有传递登录模式的话，用默认登录模式组包
		LogonMode = m_cbLogonMode;

	//发送数据
	switch (LogonMode)
	{
	case LOGON_BY_GAME_ID:			//I D 登录
		{
			//变量定义
			CMD_GP_LogonGameID * pLogonGameID=(CMD_GP_LogonGameID *)cbBuffer;

			//系统信息
			pLogonGameID->dwPlazaVersion=VERSION_PLAZA;

			//机器标识
			CWHService::GetMachineIDEx(pLogonGameID->szMachineID);

			//登录信息
			pLogonGameID->dwGameID=m_dwGameID;
			lstrcpyn(pLogonGameID->szPassword,szPassword,CountArray(pLogonGameID->szPassword));
			pLogonGameID->cbValidateFlags=cbValidateFlags;

			if (nValidateType == 8) //手机
			{
				lstrcpyn(pLogonGameID->szPhoneVerifyID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonGameID->szPhoneVerifyID));
			}
			else if (nValidateType == 9) //身份证
			{
				lstrcpyn(pLogonGameID->szPassPortID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonGameID->szPassPortID));
			}


			//保存密码
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			lstrcpyn(pGlobalUserData->szPassword,pLogonGameID->szPassword,CountArray(pGlobalUserData->szPassword));

			return sizeof(CMD_GP_LogonGameID);
		}
	case LOGON_BY_ACCOUNTS:			//帐号登录
		{
			//变量定义
			CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts *)cbBuffer;
			//系统信息
			pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;
			//机器标识
			CWHService::GetMachineIDEx(pLogonAccounts->szMachineID);

			//登录信息
			lstrcpyn(pLogonAccounts->szPassword,szPassword,CountArray(pLogonAccounts->szPassword));
			lstrcpyn(pLogonAccounts->szAccounts,m_szAccounts,CountArray(pLogonAccounts->szAccounts));
			pLogonAccounts->cbValidateFlags=cbValidateFlags;

			if (nValidateType == 8) //手机
			{
				lstrcpyn(pLogonAccounts->szPhoneVerifyID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonAccounts->szPhoneVerifyID));
			}
			else if (nValidateType == 9) //身份证
			{
				lstrcpyn(pLogonAccounts->szPassPortID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonAccounts->szPassPortID));
			}

			//保存密码
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			lstrcpyn(pGlobalUserData->szPassword,pLogonAccounts->szPassword,CountArray(pGlobalUserData->szPassword));

			return sizeof(CMD_GP_LogonAccounts);
		}
	}

	return 0;
}

//下载资源
VOID CDlgLogon::LoadServerResouce()
{
	CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
	int nResoucer = pCGlobalUnits->GetResouceVersion();

	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();

	CString sContent;
	CString csResponse;
	unsigned short nPort = pGlobalServer->GetPostPort();
	DWORD dwRes = 0;
	CWHService::Post(csResponse,pGlobalServer->GetPlatformServer(7),nPort,"GetResouce.aspx",sContent,dwRes,TRUE);
	int nNver = atoi(csResponse);
	if (nResoucer <nNver) //等待下载资源
	{
		m_btEnter.EnableWindow(FALSE);
		m_btRegister.EnableWindow(FALSE);
		m_btQQ.EnableWindow(FALSE);

		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szSkinRes[256]=TEXT("");
		_sntprintf(szSkinRes,CountArray(szSkinRes),TEXT("%s/Download/Resouce.zip"),pGlobalServer->GetPlatformServer(5));
		CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
		CString sFile = pCGlobalUnits->m_sAppPath+"Resouce.zip";
		cfilter.AddZipCommand(szSkinRes, sFile, true);
		cfilter.StartTread(this);
	}
	pCGlobalUnits->SetResouceVersion(nNver);
}

//加载账号
VOID CDlgLogon::LoadAccountsInfo()
{
	//读取信息
	CWHRegKey RegUserInfo;
	if (RegUserInfo.OpenRegKey(REG_USER_INFO,false)==false) return;

	//变量定义
	DWORD dwRegIndex=0L;
	DWORD dwLastUserID=RegUserInfo.GetValue(TEXT("LastUserID"),0L);

	//读取信息
	do
	{
		//变量定义
		tagAccountsInfo AccountsInfo;
		ZeroMemory(&AccountsInfo,sizeof(AccountsInfo));

		//读取键项
		TCHAR szKeyItemName[16]=TEXT("");
		if (RegUserInfo.EnumItemString(dwRegIndex++,szKeyItemName,CountArray(szKeyItemName))==false) break;

		//打开子键
		CWHRegKey RegUserItem;
		if (RegUserItem.Attach(RegUserInfo.OpenItemKey(szKeyItemName))==NULL) continue;

		//帐户信息
		AccountsInfo.dwUserID=_tstol(szKeyItemName);
		RegUserItem.GetString(TEXT("GameID"),AccountsInfo.szGameID,CountArray(AccountsInfo.szGameID));
		RegUserItem.GetString(TEXT("UserAccount"),AccountsInfo.szAccounts,CountArray(AccountsInfo.szAccounts));

		TCHAR szAccountType[16]=TEXT("");
		RegUserItem.GetString(TEXT("AccountType"),szAccountType,CountArray(szAccountType));
        AccountsInfo.cbAccountType = _tstol(szAccountType);
		//读取密码
		TCHAR szPassword[MAX_ENCRYPT_LEN]=TEXT("");
		RegUserItem.GetString(TEXT("UserPassword"),szPassword,CountArray(szPassword));

		//解开密码
		if (szPassword[0]!=0)
		{
			CWHEncrypt::XorCrevasse(szPassword,AccountsInfo.szPassword,CountArray(AccountsInfo.szPassword));
		}

		//构造数据
		tagAccountsInfo * pAccountsInfo=new tagAccountsInfo;
		CopyMemory(pAccountsInfo,&AccountsInfo,sizeof(AccountsInfo));

		//插入数据
		if (AccountsInfo.cbAccountType == 0) //普通账号插入
		{
			m_AccountsInfoArray.InsertAt(m_AccountsInfoArray.GetCount(),pAccountsInfo);
		}

	} while (true);

	//插入信息
	for (INT_PTR i=0;i<m_AccountsInfoArray.GetCount();i++)
	{
		//插入信息
		INT nGameIDItem=CB_ERR;
		INT nAccountsItem=CB_ERR;
		tagAccountsInfo * pAccountsInfo=m_AccountsInfoArray[i];
		
		//插入信息
		if (pAccountsInfo->szGameID[0]!=0) 
			nGameIDItem=m_GameIDControl.AddString(pAccountsInfo->szGameID);
		if (pAccountsInfo->szAccounts[0]!=0) 
			nAccountsItem=m_AccountsControl.AddString(pAccountsInfo->szAccounts);

		//设置数据
		if (nGameIDItem!=CB_ERR) 
			m_GameIDControl.SetItemDataPtr(nGameIDItem,pAccountsInfo);
		if (nAccountsItem!=CB_ERR) 
			m_AccountsControl.SetItemDataPtr(nAccountsItem,pAccountsInfo);

		//设置选择
		if ((dwLastUserID!=0L)&&(pAccountsInfo->dwUserID==dwLastUserID))
		{
			if (nGameIDItem!=CB_ERR) m_GameIDControl.SetCurSel(nGameIDItem);
			if (nAccountsItem!=CB_ERR) m_AccountsControl.SetCurSel(nAccountsItem);
		}
	}

	//设置选择
	if ((m_GameIDControl.GetCount()>0)&&(m_GameIDControl.GetCurSel()==LB_ERR)) 
		m_GameIDControl.SetCurSel(0);
	if ((m_AccountsControl.GetCount()>0)&&(m_AccountsControl.GetCurSel()==LB_ERR)) 
		m_AccountsControl.SetCurSel(0);

	return;
}

//地址信息
VOID CDlgLogon::LoadLogonServerInfo()
{
	//读取数目
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	WORD wItemCount=pGlobalServer->GetItemCount();

	//上次登录
	TCHAR szLastServer[LEN_SERVER]=TEXT("");
	pGlobalServer->GetLastServerName(szLastServer);

	//读取信息
	for (WORD i=0;i<wItemCount;i++)
	{
		//读取信息
		TCHAR szServerItem[LEN_SERVER]=TEXT("");
		pGlobalServer->GetServerItemName(i,szServerItem);

		//插入信息
		if (szServerItem[0]!=0)
		{
			//插入信息
			INT nItem=m_ServerControl.AddString(szServerItem);

			//最近登录
			if ((szLastServer[0]!=0)&&(lstrcmp(szLastServer,szServerItem)==0))
			{
				szLastServer[0]=0;
				m_ServerControl.SetCurSel(nItem);
			}
		}
	}

	//最近登录
	if (szLastServer[0]!=0)
	{
		m_ServerControl.SetCurSel(m_ServerControl.AddString(szLastServer));
	}

	//设置选择
	if (m_ServerControl.GetCurSel()==LB_ERR)
	{
		if (m_ServerControl.GetCount()==0L)
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			m_ServerControl.SetCurSel(m_ServerControl.AddString(pGlobalServer->GetPlatformServer(1)));
		}
		else
		{
			m_ServerControl.SetCurSel(0);
		}
	}

	return;
}

//获取信息
bool CDlgLogon::GetInformation()
{
	//获取信息
	//m_dwGameID=GetDlgItemInt(IDC_GAME_ID,NULL,FALSE);
	if (m_cbAccountType == LOGON_ACCOUNT_NORMAL)
	{
		GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
		//获取信息
		m_PasswordControl.GetUserPassword(m_szPassword);
		//配置信息
		m_cbRemPassword=(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);
	}
	else
	{
		m_cbRemPassword = 0;
	}
	//判断用户输入
	TCHAR szDescribe[128]=TEXT("");
	if (CWHService::BAllNumber(m_szAccounts))
	{
		m_dwGameID=GetDlgItemInt(IDC_ACCOUNTS,NULL,FALSE);
		m_cbLogonMode = LOGON_BY_GAME_ID;
	}
	else
	{
		m_cbLogonMode = LOGON_BY_ACCOUNTS;
	}

	GetDlgItemText(IDC_LOGON_SERVER,m_szLogonServer,CountArray(m_szLogonServer));

	//地址判断
	if (m_szLogonServer[0]==0L)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请选择“登录服务器”后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_ServerControl.SetFocus();

		return false;
	}

	//I D 判断
	if ((m_cbLogonMode==LOGON_BY_GAME_ID)&&(m_dwGameID==0L))
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请您输入 ID 后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_GameIDControl.SetFocus();

		return false;
	}

	//帐号判断
	if ((m_cbLogonMode==LOGON_BY_ACCOUNTS)&&(m_szAccounts[0]==0L))
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请您输入帐号后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_AccountsControl.SetFocus();

		return false;
	}

	//密码判断
	if (m_szPassword[0]==0)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请您输入密码后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_PasswordControl.SetFocus();

		return false;
	}
	return true;
}

//选择改变
VOID CDlgLogon::OnSelchangeGameID()
{
	//获取选择
	INT nCurrentSel=m_GameIDControl.GetCurSel();
	tagAccountsInfo * pAccountsInfo=(tagAccountsInfo *)m_GameIDControl.GetItemDataPtr(nCurrentSel);

	//设置控件
	if ((nCurrentSel!=LB_ERR)&&(pAccountsInfo!=NULL))
	{
		//用户帐号
		m_GameIDControl.SetCurSel(nCurrentSel);

		//同步帐号
		for (INT i=0;i<m_AccountsControl.GetCount();i++)
		{
			if (m_AccountsControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				m_AccountsControl.SetCurSel(i);
				break;
			}
		}

		//设置密码
		m_PasswordControl.SetUserPassword(pAccountsInfo->szPassword);

		//记住密码
		bool bRemPassword=(pAccountsInfo->szPassword[0]!=0);
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck((bRemPassword==true)?BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		//设置密码
		m_PasswordControl.SetUserPassword(TEXT(""));

		//记住密码
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);
	}

	return;
}

//选择改变
VOID CDlgLogon::OnSelchangeAccounts()
{
	//获取选择
	INT nCurrentSel=m_AccountsControl.GetCurSel();
	tagAccountsInfo * pAccountsInfo=(tagAccountsInfo *)m_AccountsControl.GetItemDataPtr(nCurrentSel);

	//设置控件
	if ((nCurrentSel!=LB_ERR)&&(pAccountsInfo!=NULL))
	{
		//用户帐号
		m_AccountsControl.SetCurSel(nCurrentSel);

		//同步标识
		for (INT i=0;i<m_GameIDControl.GetCount();i++)
		{
			if (m_GameIDControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				m_GameIDControl.SetCurSel(i);
				break;
			}
		}

		//设置密码
		m_PasswordControl.SetUserPassword(pAccountsInfo->szPassword);

		//记住密码
		bool bRemPassword=(pAccountsInfo->szPassword[0]!=0);
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck((bRemPassword==true)?BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		//设置密码
		m_PasswordControl.SetUserPassword(TEXT(""));

		//记住密码
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);
	}

	return;
}

//网络设置
VOID CDlgLogon::OnBnClickedProxyConfig()
{
	//隐藏窗口
	ShowWindow(SW_HIDE);

	//代理设置
	CDlgProxyConfig DlgProxyConfig;
	DlgProxyConfig.DoModal();

	//显示窗口
	ShowWindow(SW_SHOW);

	return;
}

//编辑改变
VOID CDlgLogon::OnCbnEditchangeAccounts()
{
	//安全设置
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);

	//密码重置
	if (m_PasswordControl.IsFalsityPassword()==true) m_PasswordControl.SetUserPassword("");

	return;
}

//删除记录
VOID CDlgLogon::OnBnClickedDeleteRecord()
{
	//变量定义
	CAccountsCtrl * pAccountsCtrl=NULL;
	tagAccountsInfo * pAccountsInfo=NULL;

	//获取窗口
	switch (m_TabControl.GetCurSel())
	{
	case LOGON_BY_GAME_ID: { pAccountsCtrl=&m_GameIDControl; break; }
	case LOGON_BY_ACCOUNTS: { pAccountsCtrl=&m_AccountsControl; break;	}
	default: ASSERT(FALSE);
	}

	//获取信息
	INT nCurrentSel=pAccountsCtrl->GetCurSel();

	//删除处理
	if (nCurrentSel!=LB_ERR)
	{
		//获取变量
		ASSERT(pAccountsCtrl->GetItemDataPtr(nCurrentSel)!=NULL);
		pAccountsInfo=(tagAccountsInfo *)pAccountsCtrl->GetItemDataPtr(nCurrentSel);

		//构造标识
		CString strUserID;
		strUserID.Format(TEXT("%ld"),pAccountsInfo->dwUserID);

		//用户表项
		CWHRegKey RegUserInfo;
		RegUserInfo.OpenRegKey(REG_USER_INFO,false);

		//删除表项
		RegUserInfo.RecurseDeleteKey(strUserID);

		//删除列表
		for (INT i=0;i<m_GameIDControl.GetCount();i++)
		{
			if (m_GameIDControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				//删除字符
				m_GameIDControl.DeleteString(i);
				m_GameIDControl.SetWindowText(TEXT(""));

				//设置选择
				if ((m_GameIDControl.GetCurSel()==LB_ERR)&&(m_GameIDControl.GetCount()>0))
				{
					m_GameIDControl.SetCurSel(0);
				}

				break;
			}
		}

		//删除列表
		for (INT i=0;i<m_AccountsControl.GetCount();i++)
		{
			if (m_AccountsControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				//删除字符
				m_AccountsControl.DeleteString(i);
				m_AccountsControl.SetWindowText(TEXT(""));

				//更新选择
				if ((m_AccountsControl.GetCurSel()==LB_ERR)&&(m_AccountsControl.GetCount()>0))
				{
					m_AccountsControl.SetCurSel(0);
				}

				break;
			}
		}
	}

	//设置焦点
	pAccountsCtrl->SetFocus();

	//获取变量
	nCurrentSel=pAccountsCtrl->GetCurSel();
	pAccountsInfo=(nCurrentSel!=LB_ERR)?(tagAccountsInfo *)pAccountsCtrl->GetItemDataPtr(nCurrentSel):NULL;

	//设置密码
	m_PasswordControl.SetUserPassword((pAccountsInfo!=NULL)?pAccountsInfo->szPassword:TEXT(""));

	//记住密码
	bool bRemPassword=(pAccountsInfo!=NULL)?(pAccountsInfo->szPassword[0]!=0):false;
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck((bRemPassword==true)?BST_CHECKED:BST_UNCHECKED);

	return;
}

VOID CDlgLogon::OnBnClickedQQ()
{

	if( NULL == m_pQQRegDialog->GetSafeHwnd() )
	{
		m_pQQRegDialog = new CDlgQQLogon;
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		m_pQQRegDialog->SetUrl(pGlobalServer->GetQQLogonUrl());
		m_pQQRegDialog->Create(IDD_DIALOG_QQLOGON,this);
		//m_pQQRegDialog->MoveWindow( rect.left-nLeft, rect.top+127, 520, 355 );
		m_pQQRegDialog->ShowWindow( SW_SHOW );	
	}
	else
		m_pQQRegDialog->ShowWindow( SW_SHOW );
}

//类型改变
VOID CDlgLogon::OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabControl.GetCurSel())
	{
	case LOGON_BY_GAME_ID:		//I D 登录
		{
			//设置变量
			m_cbLogonMode=LOGON_BY_GAME_ID;

			//设置控件
			GetDlgItem(IDC_GAME_ID)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_MODE_NAME,TEXT("游戏 I D："));

			//设置选择
			m_TabControl.SetCurSel(LOGON_BY_GAME_ID);

			break;
		}
	case LOGON_BY_ACCOUNTS:		//帐号登录
		{
			//设置变量
			m_cbLogonMode=LOGON_BY_ACCOUNTS;

			//设置控件
			GetDlgItem(IDC_GAME_ID)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_MODE_NAME,TEXT("游戏帐号："));

			//设置选择
			m_TabControl.SetCurSel(LOGON_BY_ACCOUNTS);

			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//手机解绑
VOID CDlgLogon::OnBnClickedUnbundling()
{
	//构造地址
	if (m_bCanOpenMobileBind)
	{
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szBillUrl[256]=TEXT("");
		_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/UserUnBindMachine.aspx?uid=%s"),pGlobalServer->GetPlatformServer(3),m_sLogonAccount);
		CMessagePop DlgMobileBind ;
		DlgMobileBind.SetWindowSize(420,360+72+55,400,360);
		DlgMobileBind.InitWebDlg(szBillUrl,"手机自助解绑",true,false,0);

		m_bCanOpenMobileBind = false;
		DlgMobileBind.DoModal();
		m_bCanOpenMobileBind = true;
	}
	return;
}

//找回密码
VOID CDlgLogon::OnBnClickedGetPwd()
{
	//构造地址	
	if (m_bCanOpenGetPwd)
	{
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szBillUrl[256]=TEXT("");
		_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/ReBackPwd.aspx"),pGlobalServer->GetPlatformServer(3));

		CMessagePop DlgMobileBind ;
		DlgMobileBind.SetWindowSize(480+13,360+72+55-160,400+13,360-160);//413 200
		DlgMobileBind.InitWebDlg(szBillUrl,"找回密码",true,false,0);
		m_bCanOpenGetPwd = false;
		DlgMobileBind.DoModal();
		m_bCanOpenGetPwd = true;
	}
	//打开页面
	//ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//记住密码
VOID CDlgLogon::OnBnClickedRemPwd()
{
	bool bCheck = ((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck();
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(!bCheck);
	return;
}

//连接按钮
VOID CDlgLogon::OnBnClickedLogonLink4()
{
	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),pGlobalServer->GetPlatformServer(3));

	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//注册帐号
VOID CDlgLogon::OnBnClickedRegister()
{
	//隐藏窗口
	ShowWindow(SW_HIDE);

	//获取地址
	CString strLogonServer;
	GetDlgItemText(IDC_LOGON_SERVER,strLogonServer);

	//构造地址
	strLogonServer.TrimLeft();
	strLogonServer.TrimRight();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	lstrcpyn(m_szLogonServer,(strLogonServer.IsEmpty()==true)?pGlobalServer->GetPlatformServer(1):strLogonServer,CountArray(m_szLogonServer));

	//显示注册
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowRegister();

	return;
}

//绘画背景
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//设置缓冲
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//加载资源
	CPngImageSB ImageBack;
	CPngImageSB ImageTitle;
	CPngImageSB ImageTiP;
	//CPngImageSB ImageUnBin;
	ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("LOGON_TITILE"));
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	CString sImagePath;
	sImagePath.Format("%s/SkinRes/REGISTER_TIP.png",pGlobalServer->GetAppPath());
	//ImageTiP.LoadImage(AfxGetInstanceHandle(),TEXT("REGISTER_TIP"));
	ImageTiP.LoadImage(sImagePath);
	//ImageUnBin.LoadImage(AfxGetInstanceHandle(),TEXT("BT_UNBUNDING"));
	//加载图标
	//CPngImageSB ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	//ImageLogo.DrawImage(pBufferDC,11,6);
	ImageTitle.DrawImage(pBufferDC,40,6);
	//ImageUnBin.DrawImage(pBufferDC,400,180);
	if (m_bShowRegTip && this->IsWindowVisible())
	{
		if(pGlobalServer->BHaveQQLogon())
		{
			ImageTiP.DrawImage(pBufferDC,57+14,298-25);
		}
		else
		{
			ImageTiP.DrawImage(pBufferDC,105+14,298-25);
		}
		SetTimer(IDI_DRAW_REGISTER_TIP,3000,NULL);
	}
	else
	{
		ImageTiP.DestroyCImage();
	}
	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}


void CDlgLogon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case IDI_DRAW_REGISTER_TIP:	
		{
			m_bShowRegTip = false;
			KillTimer(IDI_DRAW_REGISTER_TIP);
			Invalidate(TRUE);
		}
		CDialog::OnTimer(nIDEvent);
	}
}

//显示消息
VOID CDlgLogon::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//鼠标消息
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟标题
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//位置改变
VOID CDlgLogon::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//控件颜色
HBRUSH CDlgLogon::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(10,10,10));
			return m_brBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//尺寸变化
VOID CDlgLogon::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//调整控件
	if(cx > 0 && cy > 0 && m_btQuit.m_hWnd)
	{
		CRect rcButton;
	//	m_btHelp.MoveWindow(cx-32-rcButton.Width(),0,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		m_btOption.GetWindowRect(&rcButton);
		m_btOption.MoveWindow(334,165,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

		m_btQuit.GetWindowRect(&rcButton);
		m_btQuit.MoveWindow(cx-3-18,3,14,16,SWP_NOZORDER|SWP_NOMOVE);

		m_Unbundling.GetWindowRect(&rcButton);
		m_Unbundling.MoveWindow(334,193,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		m_btDeleteRecord.GetWindowRect(&rcButton);
		m_btDeleteRecord.MoveWindow(334,226,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		m_GetPwd.GetWindowRect(&rcButton);
		m_GetPwd.MoveWindow(334,243,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		m_cbRemPwd.MoveWindow(334,243,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

		m_btEnter.GetWindowRect(&rcButton);
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		if(pGlobalServer->BHaveQQLogon())
		{
			m_btRegister.MoveWindow(57,294,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
			m_btEnter.MoveWindow(57+110+16,294,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
			m_btQQ.MoveWindow(57+(110+16)*2,294,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		}
		else
		{
			m_btQQ.ShowWindow(SW_HIDE);
			m_btRegister.MoveWindow(105,294,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
			m_btEnter.MoveWindow(270,294,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

		}
		GetDlgItem(IDC_REM_PASSWORD)->GetWindowRect(&rcButton);
		GetDlgItem(IDC_REM_PASSWORD)->MoveWindow(334,266,/*rcButton.Width()*/12,12,SWP_NOZORDER|SWP_NOMOVE);
		m_RemPwd.MoveWindow(334+14+3,266,60,12,SWP_NOZORDER|SWP_NOMOVE);

		m_btLogonLink3.GetWindowRect(&rcButton);
		m_btLogonLink3.MoveWindow(13+109+109,316,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
		m_btLogonLink4.GetWindowRect(&rcButton);
		m_btLogonLink4.MoveWindow(13+109+109+109,316,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

		//if(m_TabControl.m_hWnd)m_TabControl.MoveWindow(26,126,328,27,SWP_NOZORDER|SWP_NOMOVE);
		if(m_ServerControl.m_hWnd)
			m_ServerControl.MoveWindow(165,195,155,12,SWP_NOZORDER|SWP_NOMOVE);
		if(m_GameIDControl.m_hWnd)
			m_GameIDControl.MoveWindow(165,195,155,12,SWP_NOZORDER|SWP_NOMOVE);
		if(m_AccountsControl.m_hWnd)
			m_AccountsControl.MoveWindow(165,230,155,12,SWP_NOZORDER|SWP_NOMOVE);
		if(m_PasswordControl.m_hWnd)
			m_PasswordControl.MoveWindow(165,260,155,20,SWP_NOZORDER|SWP_NOMOVE);

		//CWnd *pDlgItem = GetDlgItem(IDC_STATIC_SERVER);
		//if(pDlgItem && pDlgItem->m_hWnd)
		//	pDlgItem->MoveWindow(37,170,80,16,SWP_NOZORDER|SWP_NOMOVE);
		//pDlgItem = GetDlgItem(IDC_MODE_NAME);
		//if(pDlgItem && pDlgItem->m_hWnd)
		//	pDlgItem->MoveWindow(49,207,66,16,SWP_NOZORDER|SWP_NOMOVE);
		//pDlgItem = GetDlgItem(IDC_STATIC_PASS);
		//if(pDlgItem && pDlgItem->m_hWnd)
		//	pDlgItem->MoveWindow(49,245,66,16,SWP_NOZORDER|SWP_NOMOVE);
	}
}

LRESULT CDlgLogon::OnUpdateResouce(WPARAM wParam, LPARAM lPara)
{
	CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
	pCGlobalUnits->InitGlobalUnits();
	m_btEnter.EnableWindow(TRUE);
	m_btRegister.EnableWindow(TRUE);
	m_btQQ.EnableWindow(TRUE);

	return true;
}

LRESULT CDlgLogon::OnQQLogin(WPARAM wParam, LPARAM lParam)
{
	TCHAR *cID = (TCHAR *)wParam;
	TCHAR *cpwd = (TCHAR *)lParam;

	CString userid(cID);
	CString passwo(cpwd);
	lstrcpyn(m_szAccounts,cID,LEN_ACCOUNTS);
	lstrcpyn(m_szPassword,cpwd,LEN_PASSWORD);
	m_sLogonAccount = userid;

	delete[] cID;
	delete[] cpwd;

	if(userid =="" || passwo =="")
		return -1;
    // m_AccountsControl.SetWindowText(userid);
	//m_PasswordControl.SetUserPassword(passwo);

	UpdateData(false);
	m_cbAccountType = LOGON_ACCOUNT_QQ;

	if( NULL != m_pQQRegDialog->GetSafeHwnd() )
	{
		delete m_pQQRegDialog;
		m_pQQRegDialog = NULL;
	}
	//获取信息
	if (GetInformation()==false) 
		return 0;

	//隐藏窗口
	ShowWindow(SW_HIDE);

	//执行登录
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);


	return 0;
}

void CDlgLogon::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != m_pQQRegDialog )
		::SetWindowPos( m_pQQRegDialog->GetSafeHwnd(),NULL,  x - ((800-416)/2) +90,y + 127,0,0,SWP_NOSIZE);
}
//////////////////////////////////////////////////////////////////////////////////


