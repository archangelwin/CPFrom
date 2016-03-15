#include "Stdafx.h"
#include "DlgLogon.h"
#include "GamePlaza.h"
#include "MissionLogon.h"
#include "DlgProxyConfig.h"
#include ".\dlglogon.h"
#include "MessagePop.h"
  
//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С
#define ROUND_CX					7									//Բ�ǿ��
#define ROUND_CY					7									//Բ�Ǹ߶�

//��Ļλ��
#define LAYERED_SIZE				5									//�ֲ��С
#define CAPTION_SIZE				35									//�����С

//�ؼ���ʶ
#define IDC_WEB_PUBLICIZE			300									//����ؼ�
//ʱ���ʶ
#define IDI_DRAW_REGISTER_TIP		10									//

//////////////////////////////////////////////////////////////////////////////////
  
BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
	ON_BN_CLICKED(IDC_PROXY_CONFIG, OnBnClickedProxyConfig)
	ON_BN_CLICKED(IDC_BUTTON_LOGON_QQ, OnBnClickedQQ)

	//������Ϣ
	ON_STN_CLICKED(IDC_DELETE_RECORD, OnBnClickedDeleteRecord)
	ON_STN_CLICKED(IDC_LOGON_UNBUNDLING, OnBnClickedUnbundling)
	ON_STN_CLICKED(IDC_LOGON_GETPWD, OnBnClickedGetPwd)
	ON_STN_CLICKED(IDC_LOGON_REMPWD, OnBnClickedRemPwd)
	ON_BN_CLICKED(IDC_BT_LOGON_LINK_4, OnBnClickedLogonLink4)

	//�ؼ���Ϣ
	ON_CBN_SELCHANGE(IDC_GAME_ID, OnSelchangeGameID)
	ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_CBN_EDITCHANGE(IDC_ACCOUNTS, OnCbnEditchangeAccounts)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeLogonMode)
	//�Զ���Ϣ
	ON_MESSAGE(WM_UPDATE_RESOUCE, OnUpdateResouce)
	ON_MESSAGE(WM_LOGIN_QQ,OnQQLogin)

	ON_WM_MOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLogon::CDlgLogon() : CDialog(IDD_DLG_LOGON)
{
	//��¼��Ϣ
	m_dwGameID=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLogonServer[0]=0;

	m_pQQRegDialog = NULL;
	//���ñ���
	m_cbRemPassword=FALSE;
	m_cbLogonMode=LOGON_BY_ACCOUNTS;
	m_cbAccountType = LOGON_ACCOUNT_NORMAL;
    m_bCanOpenMobileBind = true;
	m_bCanOpenGetPwd = true;
	m_bShowRegTip = true;
	//������ˢ
	m_brBrush.CreateSolidBrush(RGB(215,223,228));

	return;
}

//��������
CDlgLogon::~CDlgLogon()
{
	//������Դ
	if (m_brBrush.GetSafeHandle()!=NULL)
	{
		m_brBrush.DeleteObject();
	}

	//ɾ������
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

//�ؼ���
VOID CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDC_REGISTER, m_btRegister);
	DDX_Control(pDX, IDC_BUTTON_LOGON_QQ, m_btQQ);

	//�󶨿ؼ�
	DDX_Control(pDX, IDCANCEL, m_btQuit);
	DDX_Control(pDX, IDC_PROXY_CONFIG, m_btOption);
	DDX_Control(pDX, IDC_DELETE_RECORD, m_btDeleteRecord);

	//�����ؼ�
	DDX_Control(pDX, IDC_GAME_ID, m_GameIDControl);
	DDX_Control(pDX, IDC_ACCOUNTS, m_AccountsControl);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);

	//�����ؼ�
	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	DDX_Control(pDX, IDC_LOGON_SERVER, m_ServerControl);

	//���ӿؼ�
	DDX_Control(pDX, IDC_LOGON_UNBUNDLING, m_Unbundling);
	DDX_Control(pDX, IDC_LOGON_GETPWD, m_GetPwd);
	DDX_Control(pDX, IDC_LOGON_REMPWD, m_RemPwd);
	DDX_Control(pDX, IDC_BT_LOGON_LINK_4, m_btLogonLink4);
	DDX_Control(pDX, IDC_REM_PASSWORD, m_cbRemPwd);
}

//��������
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//���ñ���
	SetWindowText(TEXT("������"));

	//��������
	CSkinDialog::SetWndFont(this,NULL);
	
	//������Դ
	CPngImageSB ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));

	//���ô�С
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//�߿�����
	m_ServerControl.SetDrawBorad(false);
	m_GameIDControl.SetDrawBorad(false);
	m_AccountsControl.SetDrawBorad(false);
	m_PasswordControl.SetDrawBorad(false);
	

	//��Ⱦ����
//	m_ServerControl.SetReadOnly(true);
	m_ServerControl.SetRenderImage(false);	
	m_GameIDControl.SetRenderImage(false);
	m_AccountsControl.SetRenderImage(false);

	//���ð�ť
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

	//���ؼ�
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);
	m_PlatformPublicize.ShowWindow(SW_HIDE);

	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/LogonLogo.aspx"),pGlobalServer->GetPlatformServer(3));

	//���ù��
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetWindowPos(NULL,9,45,SizeWindow.cx-9*2,103,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	//�����ǩ
	m_TabControl.SetItemSize(CSize(100,25));
	m_TabControl.InsertItem(LOGON_BY_ACCOUNTS,TEXT(" �ʺŵ�¼ "));
	m_TabControl.InsertItem(LOGON_BY_GAME_ID,TEXT(" I D ��¼ "));

	//���ÿؼ�
	m_TabControl.SetRenderImage(false);
	m_TabControl.SetTabCtrlColor(RGB(215,223,228),RGB(145,168,183));

	//������Ϣ
	LoadServerResouce();
	LoadAccountsInfo();
	LoadLogonServerInfo();

	//���ý���
	if (m_AccountsControl.GetCurSel()!=LB_ERR)
	{
		//��Ϣ����
		OnSelchangeAccounts();
		//���ý���
		m_PasswordControl.SetFocus();
	}
	else
	{
		//���ý���
		m_AccountsControl.SetFocus();
	}
	//���д���
	CenterWindow(this);

	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//����λ��
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;

	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	//�ֲ㴰��
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
	m_ToolTipCtrl.AddTool(&m_Unbundling,"���ֻ����������");
  
	//TOOLINFO popup = {0};
	//popup.hwnd = m_btRegister.m_hWnd;
	//::GetClientRect(m_btRegister.m_hWnd,&popup.rect);
	//::SendMessage(m_ToolTipCtrl.m_hWnd,TTM_ADDTOOL,0,(LPARAM)&popup);
	//::SendMessage(m_ToolTipCtrl.m_hWnd,TTM_NEWTOOLRECT,0,(LPARAM)&popup);

	return TRUE;
}

//��Ϣ����
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
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
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//ȷ������
VOID CDlgLogon::OnOK()
{
	m_cbAccountType = LOGON_ACCOUNT_NORMAL;
	m_sLogonAccount = "";
	if( NULL != m_pQQRegDialog->GetSafeHwnd() )
	{
		delete m_pQQRegDialog;
		m_pQQRegDialog = NULL;
	}
	//��ȡ��Ϣ
	if (GetInformation()==false) return;

	//���ش���
	ShowWindow(SW_HIDE);

	//ִ�е�¼
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);

	return;
}

//ȡ����Ϣ
VOID CDlgLogon::OnCancel()
{
	//�رմ���
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

	return;
}

//��������
WORD CDlgLogon::ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags,int nValidateType,CString sCode,int LogonMode)
{
	//��������
	TCHAR szPassword[LEN_MD5];
	CWHEncrypt::MD5Encrypt(m_szPassword,szPassword);

	if (LogonMode == -1)//û�д��ݵ�¼ģʽ�Ļ�����Ĭ�ϵ�¼ģʽ���
		LogonMode = m_cbLogonMode;

	//��������
	switch (LogonMode)
	{
	case LOGON_BY_GAME_ID:			//I D ��¼
		{
			//��������
			CMD_GP_LogonGameID * pLogonGameID=(CMD_GP_LogonGameID *)cbBuffer;

			//ϵͳ��Ϣ
			pLogonGameID->dwPlazaVersion=VERSION_PLAZA;

			//������ʶ
			CWHService::GetMachineIDEx(pLogonGameID->szMachineID);

			//��¼��Ϣ
			pLogonGameID->dwGameID=m_dwGameID;
			lstrcpyn(pLogonGameID->szPassword,szPassword,CountArray(pLogonGameID->szPassword));
			pLogonGameID->cbValidateFlags=cbValidateFlags;

			if (nValidateType == 8) //�ֻ�
			{
				lstrcpyn(pLogonGameID->szPhoneVerifyID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonGameID->szPhoneVerifyID));
			}
			else if (nValidateType == 9) //���֤
			{
				lstrcpyn(pLogonGameID->szPassPortID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonGameID->szPassPortID));
			}


			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			lstrcpyn(pGlobalUserData->szPassword,pLogonGameID->szPassword,CountArray(pGlobalUserData->szPassword));

			return sizeof(CMD_GP_LogonGameID);
		}
	case LOGON_BY_ACCOUNTS:			//�ʺŵ�¼
		{
			//��������
			CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts *)cbBuffer;
			//ϵͳ��Ϣ
			pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;
			//������ʶ
			CWHService::GetMachineIDEx(pLogonAccounts->szMachineID);

			//��¼��Ϣ
			lstrcpyn(pLogonAccounts->szPassword,szPassword,CountArray(pLogonAccounts->szPassword));
			lstrcpyn(pLogonAccounts->szAccounts,m_szAccounts,CountArray(pLogonAccounts->szAccounts));
			pLogonAccounts->cbValidateFlags=cbValidateFlags;

			if (nValidateType == 8) //�ֻ�
			{
				lstrcpyn(pLogonAccounts->szPhoneVerifyID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonAccounts->szPhoneVerifyID));
			}
			else if (nValidateType == 9) //���֤
			{
				lstrcpyn(pLogonAccounts->szPassPortID,sCode.GetBuffer(sCode.GetLength()),CountArray(pLogonAccounts->szPassPortID));
			}

			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			lstrcpyn(pGlobalUserData->szPassword,pLogonAccounts->szPassword,CountArray(pGlobalUserData->szPassword));

			return sizeof(CMD_GP_LogonAccounts);
		}
	}

	return 0;
}

//������Դ
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
	if (nResoucer <nNver) //�ȴ�������Դ
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

//�����˺�
VOID CDlgLogon::LoadAccountsInfo()
{
	//��ȡ��Ϣ
	CWHRegKey RegUserInfo;
	if (RegUserInfo.OpenRegKey(REG_USER_INFO,false)==false) return;

	//��������
	DWORD dwRegIndex=0L;
	DWORD dwLastUserID=RegUserInfo.GetValue(TEXT("LastUserID"),0L);

	//��ȡ��Ϣ
	do
	{
		//��������
		tagAccountsInfo AccountsInfo;
		ZeroMemory(&AccountsInfo,sizeof(AccountsInfo));

		//��ȡ����
		TCHAR szKeyItemName[16]=TEXT("");
		if (RegUserInfo.EnumItemString(dwRegIndex++,szKeyItemName,CountArray(szKeyItemName))==false) break;

		//���Ӽ�
		CWHRegKey RegUserItem;
		if (RegUserItem.Attach(RegUserInfo.OpenItemKey(szKeyItemName))==NULL) continue;

		//�ʻ���Ϣ
		AccountsInfo.dwUserID=_tstol(szKeyItemName);
		RegUserItem.GetString(TEXT("GameID"),AccountsInfo.szGameID,CountArray(AccountsInfo.szGameID));
		RegUserItem.GetString(TEXT("UserAccount"),AccountsInfo.szAccounts,CountArray(AccountsInfo.szAccounts));

		TCHAR szAccountType[16]=TEXT("");
		RegUserItem.GetString(TEXT("AccountType"),szAccountType,CountArray(szAccountType));
        AccountsInfo.cbAccountType = _tstol(szAccountType);
		//��ȡ����
		TCHAR szPassword[MAX_ENCRYPT_LEN]=TEXT("");
		RegUserItem.GetString(TEXT("UserPassword"),szPassword,CountArray(szPassword));

		//�⿪����
		if (szPassword[0]!=0)
		{
			CWHEncrypt::XorCrevasse(szPassword,AccountsInfo.szPassword,CountArray(AccountsInfo.szPassword));
		}

		//��������
		tagAccountsInfo * pAccountsInfo=new tagAccountsInfo;
		CopyMemory(pAccountsInfo,&AccountsInfo,sizeof(AccountsInfo));

		//��������
		if (AccountsInfo.cbAccountType == 0) //��ͨ�˺Ų���
		{
			m_AccountsInfoArray.InsertAt(m_AccountsInfoArray.GetCount(),pAccountsInfo);
		}

	} while (true);

	//������Ϣ
	for (INT_PTR i=0;i<m_AccountsInfoArray.GetCount();i++)
	{
		//������Ϣ
		INT nGameIDItem=CB_ERR;
		INT nAccountsItem=CB_ERR;
		tagAccountsInfo * pAccountsInfo=m_AccountsInfoArray[i];
		
		//������Ϣ
		if (pAccountsInfo->szGameID[0]!=0) 
			nGameIDItem=m_GameIDControl.AddString(pAccountsInfo->szGameID);
		if (pAccountsInfo->szAccounts[0]!=0) 
			nAccountsItem=m_AccountsControl.AddString(pAccountsInfo->szAccounts);

		//��������
		if (nGameIDItem!=CB_ERR) 
			m_GameIDControl.SetItemDataPtr(nGameIDItem,pAccountsInfo);
		if (nAccountsItem!=CB_ERR) 
			m_AccountsControl.SetItemDataPtr(nAccountsItem,pAccountsInfo);

		//����ѡ��
		if ((dwLastUserID!=0L)&&(pAccountsInfo->dwUserID==dwLastUserID))
		{
			if (nGameIDItem!=CB_ERR) m_GameIDControl.SetCurSel(nGameIDItem);
			if (nAccountsItem!=CB_ERR) m_AccountsControl.SetCurSel(nAccountsItem);
		}
	}

	//����ѡ��
	if ((m_GameIDControl.GetCount()>0)&&(m_GameIDControl.GetCurSel()==LB_ERR)) 
		m_GameIDControl.SetCurSel(0);
	if ((m_AccountsControl.GetCount()>0)&&(m_AccountsControl.GetCurSel()==LB_ERR)) 
		m_AccountsControl.SetCurSel(0);

	return;
}

//��ַ��Ϣ
VOID CDlgLogon::LoadLogonServerInfo()
{
	//��ȡ��Ŀ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	WORD wItemCount=pGlobalServer->GetItemCount();

	//�ϴε�¼
	TCHAR szLastServer[LEN_SERVER]=TEXT("");
	pGlobalServer->GetLastServerName(szLastServer);

	//��ȡ��Ϣ
	for (WORD i=0;i<wItemCount;i++)
	{
		//��ȡ��Ϣ
		TCHAR szServerItem[LEN_SERVER]=TEXT("");
		pGlobalServer->GetServerItemName(i,szServerItem);

		//������Ϣ
		if (szServerItem[0]!=0)
		{
			//������Ϣ
			INT nItem=m_ServerControl.AddString(szServerItem);

			//�����¼
			if ((szLastServer[0]!=0)&&(lstrcmp(szLastServer,szServerItem)==0))
			{
				szLastServer[0]=0;
				m_ServerControl.SetCurSel(nItem);
			}
		}
	}

	//�����¼
	if (szLastServer[0]!=0)
	{
		m_ServerControl.SetCurSel(m_ServerControl.AddString(szLastServer));
	}

	//����ѡ��
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

//��ȡ��Ϣ
bool CDlgLogon::GetInformation()
{
	//��ȡ��Ϣ
	//m_dwGameID=GetDlgItemInt(IDC_GAME_ID,NULL,FALSE);
	if (m_cbAccountType == LOGON_ACCOUNT_NORMAL)
	{
		GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
		//��ȡ��Ϣ
		m_PasswordControl.GetUserPassword(m_szPassword);
		//������Ϣ
		m_cbRemPassword=(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);
	}
	else
	{
		m_cbRemPassword = 0;
	}
	//�ж��û�����
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

	//��ַ�ж�
	if (m_szLogonServer[0]==0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��ѡ�񡰵�¼�����������ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_ServerControl.SetFocus();

		return false;
	}

	//I D �ж�
	if ((m_cbLogonMode==LOGON_BY_GAME_ID)&&(m_dwGameID==0L))
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������� ID ���ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_GameIDControl.SetFocus();

		return false;
	}

	//�ʺ��ж�
	if ((m_cbLogonMode==LOGON_BY_ACCOUNTS)&&(m_szAccounts[0]==0L))
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������ʺź��ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_AccountsControl.SetFocus();

		return false;
	}

	//�����ж�
	if (m_szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��������������ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_PasswordControl.SetFocus();

		return false;
	}
	return true;
}

//ѡ��ı�
VOID CDlgLogon::OnSelchangeGameID()
{
	//��ȡѡ��
	INT nCurrentSel=m_GameIDControl.GetCurSel();
	tagAccountsInfo * pAccountsInfo=(tagAccountsInfo *)m_GameIDControl.GetItemDataPtr(nCurrentSel);

	//���ÿؼ�
	if ((nCurrentSel!=LB_ERR)&&(pAccountsInfo!=NULL))
	{
		//�û��ʺ�
		m_GameIDControl.SetCurSel(nCurrentSel);

		//ͬ���ʺ�
		for (INT i=0;i<m_AccountsControl.GetCount();i++)
		{
			if (m_AccountsControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				m_AccountsControl.SetCurSel(i);
				break;
			}
		}

		//��������
		m_PasswordControl.SetUserPassword(pAccountsInfo->szPassword);

		//��ס����
		bool bRemPassword=(pAccountsInfo->szPassword[0]!=0);
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck((bRemPassword==true)?BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		//��������
		m_PasswordControl.SetUserPassword(TEXT(""));

		//��ס����
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);
	}

	return;
}

//ѡ��ı�
VOID CDlgLogon::OnSelchangeAccounts()
{
	//��ȡѡ��
	INT nCurrentSel=m_AccountsControl.GetCurSel();
	tagAccountsInfo * pAccountsInfo=(tagAccountsInfo *)m_AccountsControl.GetItemDataPtr(nCurrentSel);

	//���ÿؼ�
	if ((nCurrentSel!=LB_ERR)&&(pAccountsInfo!=NULL))
	{
		//�û��ʺ�
		m_AccountsControl.SetCurSel(nCurrentSel);

		//ͬ����ʶ
		for (INT i=0;i<m_GameIDControl.GetCount();i++)
		{
			if (m_GameIDControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				m_GameIDControl.SetCurSel(i);
				break;
			}
		}

		//��������
		m_PasswordControl.SetUserPassword(pAccountsInfo->szPassword);

		//��ס����
		bool bRemPassword=(pAccountsInfo->szPassword[0]!=0);
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck((bRemPassword==true)?BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		//��������
		m_PasswordControl.SetUserPassword(TEXT(""));

		//��ס����
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);
	}

	return;
}

//��������
VOID CDlgLogon::OnBnClickedProxyConfig()
{
	//���ش���
	ShowWindow(SW_HIDE);

	//��������
	CDlgProxyConfig DlgProxyConfig;
	DlgProxyConfig.DoModal();

	//��ʾ����
	ShowWindow(SW_SHOW);

	return;
}

//�༭�ı�
VOID CDlgLogon::OnCbnEditchangeAccounts()
{
	//��ȫ����
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);

	//��������
	if (m_PasswordControl.IsFalsityPassword()==true) m_PasswordControl.SetUserPassword("");

	return;
}

//ɾ����¼
VOID CDlgLogon::OnBnClickedDeleteRecord()
{
	//��������
	CAccountsCtrl * pAccountsCtrl=NULL;
	tagAccountsInfo * pAccountsInfo=NULL;

	//��ȡ����
	switch (m_TabControl.GetCurSel())
	{
	case LOGON_BY_GAME_ID: { pAccountsCtrl=&m_GameIDControl; break; }
	case LOGON_BY_ACCOUNTS: { pAccountsCtrl=&m_AccountsControl; break;	}
	default: ASSERT(FALSE);
	}

	//��ȡ��Ϣ
	INT nCurrentSel=pAccountsCtrl->GetCurSel();

	//ɾ������
	if (nCurrentSel!=LB_ERR)
	{
		//��ȡ����
		ASSERT(pAccountsCtrl->GetItemDataPtr(nCurrentSel)!=NULL);
		pAccountsInfo=(tagAccountsInfo *)pAccountsCtrl->GetItemDataPtr(nCurrentSel);

		//�����ʶ
		CString strUserID;
		strUserID.Format(TEXT("%ld"),pAccountsInfo->dwUserID);

		//�û�����
		CWHRegKey RegUserInfo;
		RegUserInfo.OpenRegKey(REG_USER_INFO,false);

		//ɾ������
		RegUserInfo.RecurseDeleteKey(strUserID);

		//ɾ���б�
		for (INT i=0;i<m_GameIDControl.GetCount();i++)
		{
			if (m_GameIDControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				//ɾ���ַ�
				m_GameIDControl.DeleteString(i);
				m_GameIDControl.SetWindowText(TEXT(""));

				//����ѡ��
				if ((m_GameIDControl.GetCurSel()==LB_ERR)&&(m_GameIDControl.GetCount()>0))
				{
					m_GameIDControl.SetCurSel(0);
				}

				break;
			}
		}

		//ɾ���б�
		for (INT i=0;i<m_AccountsControl.GetCount();i++)
		{
			if (m_AccountsControl.GetItemDataPtr(i)==pAccountsInfo)
			{
				//ɾ���ַ�
				m_AccountsControl.DeleteString(i);
				m_AccountsControl.SetWindowText(TEXT(""));

				//����ѡ��
				if ((m_AccountsControl.GetCurSel()==LB_ERR)&&(m_AccountsControl.GetCount()>0))
				{
					m_AccountsControl.SetCurSel(0);
				}

				break;
			}
		}
	}

	//���ý���
	pAccountsCtrl->SetFocus();

	//��ȡ����
	nCurrentSel=pAccountsCtrl->GetCurSel();
	pAccountsInfo=(nCurrentSel!=LB_ERR)?(tagAccountsInfo *)pAccountsCtrl->GetItemDataPtr(nCurrentSel):NULL;

	//��������
	m_PasswordControl.SetUserPassword((pAccountsInfo!=NULL)?pAccountsInfo->szPassword:TEXT(""));

	//��ס����
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

//���͸ı�
VOID CDlgLogon::OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabControl.GetCurSel())
	{
	case LOGON_BY_GAME_ID:		//I D ��¼
		{
			//���ñ���
			m_cbLogonMode=LOGON_BY_GAME_ID;

			//���ÿؼ�
			GetDlgItem(IDC_GAME_ID)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_MODE_NAME,TEXT("��Ϸ I D��"));

			//����ѡ��
			m_TabControl.SetCurSel(LOGON_BY_GAME_ID);

			break;
		}
	case LOGON_BY_ACCOUNTS:		//�ʺŵ�¼
		{
			//���ñ���
			m_cbLogonMode=LOGON_BY_ACCOUNTS;

			//���ÿؼ�
			GetDlgItem(IDC_GAME_ID)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_MODE_NAME,TEXT("��Ϸ�ʺţ�"));

			//����ѡ��
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

//�ֻ����
VOID CDlgLogon::OnBnClickedUnbundling()
{
	//�����ַ
	if (m_bCanOpenMobileBind)
	{
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szBillUrl[256]=TEXT("");
		_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/UserUnBindMachine.aspx?uid=%s"),pGlobalServer->GetPlatformServer(3),m_sLogonAccount);
		CMessagePop DlgMobileBind ;
		DlgMobileBind.SetWindowSize(420,360+72+55,400,360);
		DlgMobileBind.InitWebDlg(szBillUrl,"�ֻ��������",true,false,0);

		m_bCanOpenMobileBind = false;
		DlgMobileBind.DoModal();
		m_bCanOpenMobileBind = true;
	}
	return;
}

//�һ�����
VOID CDlgLogon::OnBnClickedGetPwd()
{
	//�����ַ	
	if (m_bCanOpenGetPwd)
	{
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szBillUrl[256]=TEXT("");
		_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/ReBackPwd.aspx"),pGlobalServer->GetPlatformServer(3));

		CMessagePop DlgMobileBind ;
		DlgMobileBind.SetWindowSize(480+13,360+72+55-160,400+13,360-160);//413 200
		DlgMobileBind.InitWebDlg(szBillUrl,"�һ�����",true,false,0);
		m_bCanOpenGetPwd = false;
		DlgMobileBind.DoModal();
		m_bCanOpenGetPwd = true;
	}
	//��ҳ��
	//ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//��ס����
VOID CDlgLogon::OnBnClickedRemPwd()
{
	bool bCheck = ((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck();
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(!bCheck);
	return;
}

//���Ӱ�ť
VOID CDlgLogon::OnBnClickedLogonLink4()
{
	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),pGlobalServer->GetPlatformServer(3));

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//ע���ʺ�
VOID CDlgLogon::OnBnClickedRegister()
{
	//���ش���
	ShowWindow(SW_HIDE);

	//��ȡ��ַ
	CString strLogonServer;
	GetDlgItemText(IDC_LOGON_SERVER,strLogonServer);

	//�����ַ
	strLogonServer.TrimLeft();
	strLogonServer.TrimRight();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	lstrcpyn(m_szLogonServer,(strLogonServer.IsEmpty()==true)?pGlobalServer->GetPlatformServer(1):strLogonServer,CountArray(m_szLogonServer));

	//��ʾע��
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowRegister();

	return;
}

//�滭����
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//������Դ
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
	//����ͼ��
	//CPngImageSB ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//�滭����
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
	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}


void CDlgLogon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

//��ʾ��Ϣ
VOID CDlgLogon::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//�����Ϣ
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�����
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//λ�øı�
VOID CDlgLogon::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//�ؼ���ɫ
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

//�ߴ�仯
VOID CDlgLogon::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//�����ؼ�
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
	//��ȡ��Ϣ
	if (GetInformation()==false) 
		return 0;

	//���ش���
	ShowWindow(SW_HIDE);

	//ִ�е�¼
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);


	return 0;
}

void CDlgLogon::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	if( NULL != m_pQQRegDialog )
		::SetWindowPos( m_pQQRegDialog->GetSafeHwnd(),NULL,  x - ((800-416)/2) +90,y + 127,0,0,SWP_NOSIZE);
}
//////////////////////////////////////////////////////////////////////////////////


