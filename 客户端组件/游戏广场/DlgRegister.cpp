#include "StdAfx.h"
#include "GamePlaza.h"
#include "DlgRegister.h"
#include "MissionLogon.h"

//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					7									//圆角宽度
#define ROUND_CY					7									//圆角高度

//屏幕位置
#define LAYERED_SIZE				1									//分层大小
#define CAPTION_SIZE				35									//标题大小

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)

	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//按钮消息
	ON_BN_CLICKED(IDC_QUIT, OnBnClickedQuit)
	ON_BN_CLICKED(IDC_SELECT_FACE, OnBnClickedSelectFace)

	ON_EN_SETFOCUS(IDC_ACCOUNTS,OnSetFocusAccount)
	ON_EN_KILLFOCUS(IDC_ACCOUNTS,OnKillFocusAccount)

	ON_EN_SETFOCUS(IDC_NICKNAME,OnSetFocusNickName)
	ON_EN_KILLFOCUS(IDC_NICKNAME,OnKillFocusNickName)

	ON_EN_SETFOCUS(IDC_LOGON_PASS1,OnSetFocusLogonPass)
	ON_EN_KILLFOCUS(IDC_LOGON_PASS1,OnKillFocusLogonPass)
	ON_EN_SETFOCUS(IDC_LOGON_PASS2,OnSetFocusLogonPass2)
	ON_EN_KILLFOCUS(IDC_LOGON_PASS2,OnKillFocusLogonPass2)

	ON_EN_SETFOCUS(IDC_INSURE_PASS1,OnSetFocusInsurePass)
	ON_EN_KILLFOCUS(IDC_INSURE_PASS1,OnKillFocusInsurePass)
	ON_EN_SETFOCUS(IDC_INSURE_PASS2,OnSetFocusInsurePass2)
	ON_EN_KILLFOCUS(IDC_INSURE_PASS2,OnKillFocusInsurePass2)

	ON_EN_SETFOCUS(IDC_PASSPORT_ID,OnSetFocusPassportID)
	ON_EN_KILLFOCUS(IDC_PASSPORT_ID,OnKillFocusPassportID)

	//特殊消息
	ON_EN_CHANGE(IDC_LOGON_PASS1, OnEnChangeLogonPass)
	//ON_EN_CHANGE(IDC_INSURE_PASS1, OnEnChangeInsurePass)
	ON_STN_CLICKED(IDC_CHANGE_VALIDATE, OnBnClickedChangeValidate)
	ON_STN_CLICKED(IDC_STATIC_AGREEMENT, OnBnClickedAgreeMent)

	ON_WM_SIZE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgRegister::CDlgRegister() : CDialog(IDD_DLG_REGISTER)
{
	//设置变量
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szNickName[0]=0;
	m_szSpreader[0]=0;
	m_szLogonPass[0]=0;
	m_szInsurePass[0]=0;
	m_szPassPortID[0]=0;
	m_szCompellation[0]=0;

	//设置变量
	m_cbRemPassword=FALSE;
	m_cbLogonPassLevel=PASSWORD_LEVEL_0;
	m_cbInsurePassLevel=PASSWORD_LEVEL_0;

	//创建画刷
	m_brBrush.CreateSolidBrush(RGB(222,239,246));

	return;
}

//析构函数
CDlgRegister::~CDlgRegister()
{
}

//控件绑定
VOID CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//按钮控件
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDC_QUIT, m_btQuit);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	//DDX_Control(pDX, IDC_SELECT_FACE, m_btSelectFace);

	//编辑控件
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	//DDX_Control(pDX, IDC_SPREADER, m_edSpreader);
	DDX_Control(pDX, IDC_NICKNAME, m_edNickName);
	DDX_Control(pDX, IDC_PASSPORT_ID, m_edPassPortID);
	DDX_Control(pDX, IDC_LOGON_PASS1, m_edLogonPass1);
	DDX_Control(pDX, IDC_LOGON_PASS2, m_edLogonPass2);
	DDX_Control(pDX, IDC_INSURE_PASS1, m_edInsurePass1);
	DDX_Control(pDX, IDC_INSURE_PASS2, m_edInsurePass2);
	//DDX_Control(pDX, IDC_COMPELLATION, m_edCompellation);
	DDX_Control(pDX, IDC_VALIDATE_CODE, m_edValidateCode);

	//其他控件
	//DDX_Control(pDX, IDC_FACE_ITEM, m_FaceItemView);
	DDX_Control(pDX, IDC_CHANGE_VALIDATE, m_ChangeValidate);
	DDX_Control(pDX, IDC_VALIDATE_CODE_WND, m_WndValidateCode);
	DDX_Control(pDX, IDC_STATIC_AGREEMENT, m_Agreement);

	DDX_Control(pDX, IDC_STATIC_REG_ACCOUNTS, m_cRegAccount);
	DDX_Control(pDX, IDC_STATIC_REG_NICKNAME, m_cRegNickName);
	DDX_Control(pDX, IDC_STATIC_REG_LOGINPASS1, m_cRegLoginPass);
	DDX_Control(pDX, IDC_STATIC_REG_LOGINPASS2, m_cRegLoginPass2);
	DDX_Control(pDX, IDC_STATIC_REG_INSUREPASS1, m_cRegInsurePass);
	DDX_Control(pDX, IDC_STATIC_REG_INSUREPASS2, m_cRegInsurePass2);
	DDX_Control(pDX, IDC_STATIC_REG_PASSPORTID, m_cRegPassPortID);
}

//消息解释
BOOL CDlgRegister::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if (pMsg->message==WM_CHAR)
	{
		//密码过滤
		if ((m_edLogonPass1.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edLogonPass2.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edInsurePass1.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edInsurePass2.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//配置函数
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();

	//设置窗口
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//设置标题
	SetWindowText(TEXT("用户注册"));
	//MoveWindow(0,0,500,468);

	//变量定义
	ASSERT(CFaceItemControl::GetInstance()!=NULL);
	IFaceItemControl * pIFaceItemControl=CFaceItemControl::GetInstance();

	//加载资源
	CPngImageSB ImageBack;
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	int nSpreader = pGlobalServer->GetPlatInfo(TEXT("PlatInfo"),TEXT("Spreader"),0);
	if (nSpreader == 0)
	{
		m_bsSpreader = false;
		ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));
	}
	else
	{
		m_bsSpreader = true;
		ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_SPREADER"));
	}

	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//验证控件
	m_WndValidateCode.RandValidateCode();
	m_edValidateCode.LimitText(VALIDATE_COUNT);
	m_ChangeValidate.SetBackGroundColor(RGB(222,239,246));
	m_Agreement.SetBackGroundColor(RGB(222,239,246));


	//限制输入
	m_edAccounts.LimitText(LEN_ACCOUNTS-1);
	m_edNickName.LimitText(LEN_NICKNAME-1);
	m_edSpreader.LimitText(LEN_ACCOUNTS-1);
	m_edLogonPass1.LimitText(LEN_PASSWORD-1);
	m_edLogonPass2.LimitText(LEN_PASSWORD-1);
	m_edInsurePass1.LimitText(LEN_PASSWORD-1);
	m_edInsurePass2.LimitText(LEN_PASSWORD-1);
	m_edPassPortID.LimitText(LEN_PASS_PORT_ID-1);
	m_edCompellation.LimitText(LEN_COMPELLATION-1);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btCancel.SetButtonImage(IDB_BT_REGISTER_CLOSE,hInstance,false,false);
	m_btQuit.SetButtonImage(IDB_BT_REGISTER,TEXT("BT_REGISTER_QUIT"),hInstance,false,false);
	m_btEnter.SetButtonImage(IDB_BT_REGISTER,TEXT("BT_REGISTER_ENTER"),hInstance,false,false);

	//获取头像
//	m_wFaceID=rand()%pIFaceItemControl->GetFaceCount();

	//设置头像
	m_FaceItemView.SetSystemFace(m_wFaceID);

	//设置性别
	((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->SetCheck(BST_CHECKED);
	((CButton *)GetDlgItem(IDC_AGREE_AGREEMENT))->SetCheck(BST_CHECKED);

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

	//获取目录
	TCHAR szPath[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szPath, sizeof(szPath));

	//读取配置
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\Spreader.ini"),szPath);

	//读取推荐人
	TCHAR szSpreader[LEN_ACCOUNTS]=TEXT("");
	GetPrivateProfileString(TEXT("SpreaderInfo"),TEXT("SpreaderName"),TEXT(""),szSpreader,CountArray(szSpreader),szFileName);

	//设置名字
	if (szSpreader[0]!=0)
	{
		SetDlgItemText(IDC_SPREADER,szSpreader);
		((CEdit *)GetDlgItem(IDC_SPREADER))->SetReadOnly();
	}

	m_edAccounts.MoveWindow(133,57,157,22);
	m_edAccounts.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
    m_cRegAccount.MoveWindow(300,57,200,22);

	m_edNickName.MoveWindow(133,89,157,22);
	m_edNickName.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edNickName.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegNickName.MoveWindow(300,89,200,22);

	m_edLogonPass1.MoveWindow(133,152,157,22);
	m_edLogonPass1.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edLogonPass1.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegLoginPass.MoveWindow(300,152,150,22);

	m_edLogonPass2.MoveWindow(133,222,157,22);
	m_edLogonPass2.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edLogonPass2.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegLoginPass2.MoveWindow(300,222,150,22);

	m_edInsurePass1.MoveWindow(133,252,157,22);
	m_edInsurePass1.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edInsurePass1.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegInsurePass.MoveWindow(300,252,150,22);

	m_edInsurePass2.MoveWindow(133,284,157,22);
	m_edInsurePass2.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edInsurePass2.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegInsurePass2.MoveWindow(300,284,150,22);

	m_edPassPortID.MoveWindow(133,315,157,22);
	m_edPassPortID.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edPassPortID.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_cRegPassPortID.MoveWindow(300,315,150,22);

	m_edValidateCode.MoveWindow(133,348,55,22);
	m_edValidateCode.SetDisableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edValidateCode.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
    m_WndValidateCode.MoveWindow(200,348,72,18);
	m_ChangeValidate.MoveWindow(297,348,170,22);


	((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->MoveWindow(142,119,18,24);
	((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->MoveWindow(220,119,18,24);

	((CButton *)GetDlgItem(IDC_AGREE_AGREEMENT))->MoveWindow(127,390,18,18);
	m_Agreement.MoveWindow(148,390,150,18);

	m_btCancel.MoveWindow(472,2,25,25);

	if (m_bsSpreader)
	{
		//GetDlgItem(IDC_STATIC_INSURE1)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_STATIC_INSURE2)->ShowWindow(SW_HIDE);
		m_edInsurePass1.ShowWindow(SW_HIDE);
		m_edInsurePass2.ShowWindow(SW_HIDE);
		m_edPassPortID.ShowWindow(SW_HIDE);
		m_cRegPassPortID.ShowWindow(SW_HIDE);
		((CButton *)GetDlgItem(IDC_AGREE_AGREEMENT))->ShowWindow(SW_HIDE);
		m_Agreement.ShowWindow(SW_HIDE);

		m_btEnter.MoveWindow(138,430-123,94,34);
		m_btQuit.MoveWindow(318,430-123,94,34);
		//m_cRegLoginPass2.MoveWindow(300,222,150,22);
		m_cRegInsurePass.MoveWindow(300,252-123,150,22);
		m_cRegInsurePass2.MoveWindow(300,284-123,150,22);
		m_cRegPassPortID.MoveWindow(300,315-123,150,22);

		m_edValidateCode.MoveWindow(133,256,55,22);
		m_WndValidateCode.MoveWindow(200,256,72,18);
		m_ChangeValidate.MoveWindow(297,256,170,22);
	}
	else
	{
		m_btEnter.MoveWindow(138,430,94,34);
		m_btQuit.MoveWindow(318,430,94,34);
	}

	return FALSE;
}

//确定函数
VOID CDlgRegister::OnOK()
{
	//获取信息
	if (GetInformation()==false) return;

	//隐藏窗口
	ShowWindow(SW_HIDE);

	//执行注册
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);

	return;
}

//取消函数
VOID CDlgRegister::OnCancel()
{
	//隐藏窗口
	ShowWindow(SW_HIDE);

	//显示登录
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowLogon();
	
	return;
}

//发送登录
WORD CDlgRegister::ConstructRegisterPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags)
{
	//变量定义
	TCHAR szLogonPass[LEN_MD5];
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(m_szLogonPass,szLogonPass);
	CWHEncrypt::MD5Encrypt(m_szInsurePass,szInsurePass);

	//变量定义
	CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;

	//系统信息
	pRegisterAccounts->dwPlazaVersion=VERSION_PLAZA;

	//机器标识
	CWHService::GetMachineIDEx(pRegisterAccounts->szMachineID);

	//基本信息
	pRegisterAccounts->wFaceID=m_wFaceID;
	pRegisterAccounts->cbGender=m_cbGender;
	lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));
	lstrcpyn(pRegisterAccounts->szNickName,m_szNickName,CountArray(pRegisterAccounts->szNickName));
	lstrcpyn(pRegisterAccounts->szSpreader,m_szSpreader,CountArray(pRegisterAccounts->szSpreader));
	lstrcpyn(pRegisterAccounts->szLogonPass,szLogonPass,CountArray(pRegisterAccounts->szLogonPass));
	lstrcpyn(pRegisterAccounts->szInsurePass,szInsurePass,CountArray(pRegisterAccounts->szInsurePass));
	lstrcpyn(pRegisterAccounts->szPassPortID,m_szPassPortID,CountArray(pRegisterAccounts->szPassPortID));
	lstrcpyn(pRegisterAccounts->szCompellation,m_szCompellation,CountArray(pRegisterAccounts->szCompellation));
	pRegisterAccounts->cbValidateFlags=cbValidateFlags;

	//保存密码
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	lstrcpyn(pGlobalUserData->szPassword,pRegisterAccounts->szLogonPass,CountArray(pGlobalUserData->szPassword));

	//发送数据
	return sizeof(CMD_GP_RegisterAccounts);
}

//获取信息
bool CDlgRegister::GetInformation()
{
	//验证信息
	TCHAR szValidateCode[VALIDATE_COUNT+1]=TEXT("");
	GetDlgItemText(IDC_VALIDATE_CODE,szValidateCode,CountArray(szValidateCode));

	//密码信息
	TCHAR szLogonPass2[LEN_PASSWORD]=TEXT("");
	TCHAR szInsurePass2[LEN_PASSWORD]=TEXT("");
	GetDlgItemText(IDC_LOGON_PASS2,szLogonPass2,CountArray(szLogonPass2));
	GetDlgItemText(IDC_LOGON_PASS1,m_szLogonPass,CountArray(m_szLogonPass));
	if (m_bsSpreader) //推广包，保险柜密码与登录密码一致
	{
		GetDlgItemText(IDC_LOGON_PASS2,szInsurePass2,CountArray(szInsurePass2));
		GetDlgItemText(IDC_LOGON_PASS1,m_szInsurePass,CountArray(m_szInsurePass));
	}
	else
	{
		GetDlgItemText(IDC_INSURE_PASS2,szInsurePass2,CountArray(szInsurePass2));
		GetDlgItemText(IDC_INSURE_PASS1,m_szInsurePass,CountArray(m_szInsurePass));
	}

	//获取字符
	GetControlString(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	GetControlString(IDC_NICKNAME,m_szNickName,CountArray(m_szNickName));
	GetControlString(IDC_SPREADER,m_szSpreader,CountArray(m_szSpreader));
	GetControlString(IDC_PASSPORT_ID,m_szPassPortID,CountArray(m_szPassPortID));
	//GetControlString(IDC_COMPELLATION,m_szCompellation,CountArray(m_szCompellation));

	//变量定义
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	//帐号判断
	if (pUserItemElement->EfficacyAccounts(m_szAccounts,szDescribe,CountArray(szDescribe))==false)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//设置焦点
		m_edAccounts.SetFocus();

		return false;
	}

	//昵称判断
	if (pUserItemElement->EfficacyNickName(m_szNickName,szDescribe,CountArray(szDescribe))==false)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//设置焦点
		m_edNickName.SetFocus();

		return false;
	}

	//密码判断
	if (pUserItemElement->EfficacyPassword(m_szLogonPass,szDescribe,CountArray(szDescribe))==false)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//设置焦点
		m_edLogonPass1.SetFocus();

		return false;
	}

	//密码判断
	if (lstrcmp(m_szLogonPass,szLogonPass2)!=0)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("您两次输入的帐号密码不一致，请重新输入！"),MB_ICONERROR,0);

		//设置焦点
		m_edLogonPass1.SetFocus();

		return false;
	}

	//密码判断
	if (pUserItemElement->EfficacyPassword(m_szInsurePass,szDescribe,CountArray(szDescribe))==false)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//设置焦点
		m_edInsurePass1.SetFocus();

		return false;
	}

	//密码判断
	if (lstrcmp(m_szInsurePass,szInsurePass2)!=0)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("您两次输入的保险柜密码不一致，请重新输入！"),MB_ICONERROR,0);

		//设置焦点
		m_edInsurePass1.SetFocus();

		return false;
	}

	if (!m_bsSpreader) //非推广包
	{	
		//密码判断
		if (lstrcmp(m_szLogonPass,m_szInsurePass)==0)
		{
			//提示信息
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("保险柜密码不能与登录密码一致，请重新输入！"),MB_ICONERROR,0);

			//设置焦点
			m_edInsurePass1.SetFocus();

			return false;
		}	
		//身份证号
		if (/*m_szPassPortID[0]!=0 && */pUserItemElement->EfficacyPassPortID(m_szPassPortID,szDescribe,CountArray(szDescribe))==false)
		{
			//提示信息
			CInformation Information(this);
			Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

			//设置焦点
			m_edPassPortID.SetFocus();

			return false;
		}

		bool bCheck = ((CButton *)GetDlgItem(IDC_AGREE_AGREEMENT))->GetCheck();
		if (!bCheck)
		{
			//提示信息
			CInformation Information(this);
			Information.ShowMessageBox("请选择接受协议条框",MB_ICONERROR,0);
			return false;
		}
	}
	//效验判断
	if (m_WndValidateCode.CheckValidateCode(szValidateCode)==false)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("效验码效验验证失败，请重新输入！"),MB_ICONERROR,0);

		//设置焦点
		m_edValidateCode.SetFocus();

		return false;
	}

	//真实姓名判断
	//if (/*m_szCompellation[0]!=0 && */pUserItemElement->EfficacyRealName(m_szCompellation,szDescribe,CountArray(szDescribe))==false)
	//{
	//	//提示信息
	//	CInformation Information(this);
	//	Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

	//	//设置焦点
	//	m_edCompellation.SetFocus();

	//	return false;
	//}



	//用户性别
	if (((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->GetCheck()==BST_CHECKED) m_cbGender=GENDER_FEMALE;
	if (((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->GetCheck()==BST_CHECKED) m_cbGender=GENDER_MANKIND;

	//配置信息
	m_cbRemPassword= true; //(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);
	return true;
}

//获取字符
VOID CDlgRegister::GetControlString(UINT uControlID, TCHAR szString[], WORD wMaxCount)
{
	//获取字符
	CString strString;
	GetDlgItemText(uControlID,strString);

	//去掉空格
	strString.TrimLeft();
	strString.TrimRight();

	CString sFilterSrc[4] = {"&","<",">","%"};
	CString sFilterDes[4] = {"&amp;","&lt;","&gt;",""};
	for(int i(0) ; i < 4 ; i ++)
	{	
		strString.Replace(sFilterSrc[i],sFilterDes[i]);
	}

	//拷贝字符
	lstrcpyn(szString,strString,wMaxCount);

	return;
}

//关闭按钮
VOID CDlgRegister::OnBnClickedQuit()
{
	//关闭窗口
	OnCancel();

	return;
}

//密码输入
VOID CDlgRegister::OnEnChangeLogonPass()
{
	//获取密码
	TCHAR szPassword[LEN_PASSWORD]=TEXT("");
	GetDlgItemText(IDC_LOGON_PASS1,szPassword,CountArray(szPassword));

	//等级判断
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	BYTE cbPasswordLevel=pUserItemElement->GetPasswordLevel(szPassword);

	//更新窗口
	if (m_cbLogonPassLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbLogonPassLevel=cbPasswordLevel;

		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	return;
}

//密码输入
VOID CDlgRegister::OnEnChangeInsurePass()
{
	//获取密码
	TCHAR szPassword[LEN_PASSWORD]=TEXT("");
	GetDlgItemText(IDC_INSURE_PASS1,szPassword,CountArray(szPassword));

	//等级判断
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	BYTE cbPasswordLevel=pUserItemElement->GetPasswordLevel(szPassword);

	//更新窗口
	if (m_cbInsurePassLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbInsurePassLevel=cbPasswordLevel;

		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	return;
}

VOID CDlgRegister::OnSetFocusAccount()
{
	m_cRegAccount.SetWindowText("6-31个中英文字母、数字组成");
	m_cRegAccount.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegAccount.ShowWindow(SW_SHOW);
	//(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
}

VOID CDlgRegister::OnKillFocusAccount()
{
	//变量定义
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetControlString(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	if (pUserItemElement->EfficacyAccounts(m_szAccounts,szDescribe,CountArray(szDescribe))==false)
	{
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegAccount.SetWindowText(szDescribe);
		m_cRegAccount.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		m_cRegAccount.SetWindowText("");
	}
}

VOID CDlgRegister::OnSetFocusNickName()
{
	m_cRegNickName.SetWindowText("6-31个中英文字母、数字组成");
	m_cRegNickName.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegNickName.ShowWindow(SW_SHOW);
}

VOID CDlgRegister::OnKillFocusNickName()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetControlString(IDC_NICKNAME,m_szNickName,CountArray(m_szNickName));
	//昵称判断
	if (pUserItemElement->EfficacyNickName(m_szNickName,szDescribe,CountArray(szDescribe))==false)
	{
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegNickName.SetWindowText(szDescribe);
		m_cRegNickName.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		m_cRegNickName.SetWindowText("");
	}
}

VOID CDlgRegister::OnSetFocusLogonPass()
{
	m_cRegLoginPass.SetWindowText("请输入8位及以上密码");
	m_cRegLoginPass.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegLoginPass.ShowWindow(SW_SHOW);
}

VOID CDlgRegister::OnKillFocusLogonPass()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetDlgItemText(IDC_LOGON_PASS1,m_szLogonPass,CountArray(m_szLogonPass));

	//密码判断
	if (pUserItemElement->EfficacyPassword(m_szLogonPass,szDescribe,CountArray(szDescribe))==false)
	{	
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegLoginPass.SetWindowText(szDescribe);
		m_cRegLoginPass.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));		
		//return;
	}
	else
	{
		m_cRegLoginPass.SetWindowText("");
	}
}

VOID CDlgRegister::OnSetFocusLogonPass2()
{
	m_cRegLoginPass2.SetWindowText("请再次确认您的密码");
	m_cRegLoginPass2.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegLoginPass2.ShowWindow(SW_SHOW);
}

VOID CDlgRegister::OnKillFocusLogonPass2()
{
	//密码信息
	TCHAR szLogonPass2[LEN_PASSWORD]=TEXT("");

	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetDlgItemText(IDC_LOGON_PASS2,szLogonPass2,CountArray(szLogonPass2));
	GetDlgItemText(IDC_LOGON_PASS1,m_szLogonPass,CountArray(m_szLogonPass));
	//密码判断
	if (lstrcmp(m_szLogonPass,szLogonPass2)!=0)
	{
		//设置焦点
		m_cRegLoginPass2.SetWindowText("您两次输入的帐号密码不一致!");
		m_cRegLoginPass2.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		m_cRegLoginPass2.SetWindowText("");
	}
}

VOID CDlgRegister::OnSetFocusInsurePass()
{	
	m_cRegInsurePass.SetWindowText("请输入8位及以上密码");
	m_cRegInsurePass.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegInsurePass.ShowWindow(SW_SHOW);

}
VOID CDlgRegister::OnKillFocusInsurePass()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetDlgItemText(IDC_LOGON_PASS1,m_szLogonPass,CountArray(m_szLogonPass));
	GetDlgItemText(IDC_INSURE_PASS1,m_szInsurePass,CountArray(m_szInsurePass));
	//密码判断
	if (pUserItemElement->EfficacyPassword(m_szInsurePass,szDescribe,CountArray(szDescribe))==false)
	{
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegInsurePass.SetWindowText(szDescribe);
		m_cRegInsurePass.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		//m_cRegInsurePass.SetWindowText("");
		//密码判断
		if (lstrcmp(m_szLogonPass,m_szInsurePass)==0)
		{
			m_cRegInsurePass.SetWindowText("保险柜密码不能与登录密码一致");
			m_cRegInsurePass.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
		}
		else
		{
			m_cRegInsurePass.SetWindowText("");
		}
	}

}

VOID CDlgRegister::OnSetFocusInsurePass2()
{
	m_cRegInsurePass2.SetWindowText("请再次确认您的密码");
	m_cRegInsurePass2.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegInsurePass2.ShowWindow(SW_SHOW);
}

VOID CDlgRegister::OnKillFocusInsurePass2()
{
	//密码信息
	TCHAR szInsurePass2[LEN_PASSWORD]=TEXT("");

	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetDlgItemText(IDC_INSURE_PASS2,szInsurePass2,CountArray(szInsurePass2));
	GetDlgItemText(IDC_INSURE_PASS1,m_szInsurePass,CountArray(m_szInsurePass));
	//密码判断
	if (lstrcmp(m_szInsurePass,szInsurePass2)!=0)
	{
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegInsurePass2.SetWindowText("您两次输入的帐号密码不一致!");
		m_cRegInsurePass2.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		m_cRegInsurePass2.SetWindowText("");
	}
}

VOID CDlgRegister::OnSetFocusPassportID()
{
	m_cRegPassPortID.SetWindowText("请输入18位真实有效身份证号码");
	m_cRegPassPortID.SetHyperLinkTextColor(RGB(250,0,0),RGB(0,0,220),RGB(0,0,100));
	m_cRegPassPortID.ShowWindow(SW_SHOW);

}

VOID CDlgRegister::OnKillFocusPassportID()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();
	GetControlString(IDC_PASSPORT_ID,m_szPassPortID,CountArray(m_szPassPortID));
	if (/*m_szPassPortID[0]!=0 && */pUserItemElement->EfficacyPassPortID(m_szPassPortID,szDescribe,CountArray(szDescribe))==false)
	{
		//设置焦点
		//m_edAccounts.SetFocus();
		m_cRegPassPortID.SetWindowText(szDescribe);
		m_cRegPassPortID.SetHyperLinkTextColor(RGB(255,0,0),RGB(255,0,0),RGB(255,0,0));
	}
	else
	{
		m_cRegPassPortID.SetWindowText("");
	}
}

//头像选择
VOID CDlgRegister::OnBnClickedSelectFace()
{
	//创建组件
	if ((m_FaceSelectControl.GetInterface()==NULL)&&(m_FaceSelectControl.CreateInstance()==false))
	{
		CInformation Information(this);
		Information.ShowMessageBox(m_FaceSelectControl.GetErrorDescribe(),MB_ICONERROR);
		return;
	}

	//隐藏界面
	ShowWindow(SW_HIDE);

	//设置控件
	m_FaceSelectControl->SetAllowItemFull();

	//选择头像
	if (m_FaceSelectControl->GetSelectFaceID(m_wFaceID)==true)
	{
		m_FaceItemView.SetSystemFace(m_wFaceID);
	}

	//显示界面
	ShowWindow(SW_SHOW);

	return;
}

//更换验证
VOID CDlgRegister::OnBnClickedChangeValidate()
{
	//更换验证
	m_WndValidateCode.RandValidateCode();

	return;
}

VOID CDlgRegister::OnBnClickedAgreeMent()
{
	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink3.aspx"),pGlobalServer->GetPlatformServer(3));

	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//绘画背景
BOOL CDlgRegister::OnEraseBkgnd(CDC * pDC)
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

	//加载资源
	CPngImageSB ImageBack;
	//CPngImageSB ImageTitle;
	//ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("REGISTER_TITLE"));
	if(m_bsSpreader)
	{
		ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_SPREADER"));
	}
	{
		ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));
	}

	//加载图标
	CPngImageSB ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	//ImageLogo.DrawImage(pBufferDC,11,6);
	//ImageTitle.DrawImage(pBufferDC,40,6);

	//加载资源
	CPngImageSB ImagePassword;
	ImagePassword.LoadImage(AfxGetInstanceHandle(),TEXT("PASSWORD_LEVEL"));

	//获取大小
	CSize SizePassword;
	SizePassword.SetSize(ImagePassword.GetWidth()/3,ImagePassword.GetHeight()/2);

	//绘画等级
	ImagePassword.DrawImage(pBufferDC,128,185,SizePassword.cx*3,SizePassword.cy,0,0);
	//ImagePassword.DrawImage(pBufferDC,249,311,SizePassword.cx*3,SizePassword.cy,0,0);

	//绘画叠加
	if (m_cbLogonPassLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,128+nImagePos,185,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//绘画叠加
	//if (m_cbInsurePassLevel>=PASSWORD_LEVEL_1)
	//{
	//	INT nImagePos=(m_cbInsurePassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
	//	ImagePassword.DrawImage(pBufferDC,249+nImagePos,311,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	//}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//显示消息
VOID CDlgRegister::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	//if (m_SkinLayered.m_hWnd!=NULL)
	//{
	//	m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	//}

	return;
}

//鼠标消息
VOID CDlgRegister::OnLButtonDown(UINT nFlags, CPoint Point)
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
VOID CDlgRegister::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	//if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	//{l
	//	m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	//}

	return;
}

//控件颜色
HBRUSH CDlgRegister::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
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

//////////////////////////////////////////////////////////////////////////////////

void CDlgRegister::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//m_edAccounts.MoveWindow().

	// TODO: 在此处添加消息处理程序代码
}
