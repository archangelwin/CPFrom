// AuthenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AuthenDlg.h"
#include "MissionLogon.h"

#define AUTHEN_LEN   18   //身份证位数
#define CODE_LEN     10
// CAuthenDlg 对话框

IMPLEMENT_DYNAMIC(CAuthenDlg, CSkinDialog)

CAuthenDlg::CAuthenDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CAuthenDlg::IDD, pParent),m_InputNumDlg(this)
{

}

CAuthenDlg::~CAuthenDlg()
{
}

void CAuthenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT_NUM, m_edInputNum);
	//	DDX_Control(pDX, IDC_EDIT_CHECKNUM, m_edCheckNum);
	DDX_Control(pDX, IDC_STA_GETPIC, m_staGetPic);
	DDX_Control(pDX, IDC_VALIDATE_CODE_WND, m_WndValidateCode);
}


BEGIN_MESSAGE_MAP(CAuthenDlg, CSkinDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STA_GETPIC, OnStnClickedStaGetpic)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAuthenDlg 消息处理程序
BOOL CAuthenDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("安全提示"));
	((CEdit *)(GetDlgItem(IDC_EDIT_NUM)))->LimitText(AUTHEN_LEN);
	((CEdit *)(GetDlgItem(IDC_EDIT_CHECKNUM)))->LimitText(CODE_LEN);
//	m_staGetPic.SetBackGroundColor(m_SkinAttribute.m_crBackFrame);

	CenterWindow();

	if (m_InputNumDlg.m_hWnd==NULL) 
	{
		m_InputNumDlg.Create(IDD_INPUT_DLG, this);
	}

	m_InputNumDlg.ShowWindow(SW_SHOW);
	m_InputNumDlg.SetForegroundWindow();

	//验证控件
	m_WndValidateCode.RandValidateCode();
	MoveInPutNumDlg();

	return TRUE;
}

void CAuthenDlg::OnStnClickedStaGetpic()
{
	// TODO: 在此添加控件通知处理程序代码
	GetVerifyCode();
}

void CAuthenDlg::GetVerifyCode()
{
// 	CPlazaViewItem * pPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
// 	ASSERT(pPlazaViewItem!=NULL);
//	pPlazaViewItem->GetVerifyCode();
	//验证控件
	m_WndValidateCode.RandValidateCode();
}

void CAuthenDlg::MoveInPutNumDlg()
{
	//获取位置
	if(::IsWindow(m_InputNumDlg.m_hWnd))
	{
		CRect ClientRect;
		GetClientRect(&ClientRect);
		CRect WindowRect;
		GetWindowRect(&WindowRect);
		m_InputNumDlg.SetWindowPos(NULL, WindowRect.right-4, WindowRect.top + ClientRect.Height()/3, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
}

void CAuthenDlg::AddCharToEdit(const CString& strChar)
{
	TCHAR szEditText[32];
	GetDlgItemText(IDC_EDIT_NUM,szEditText,CountArray(szEditText));
	CString strText(szEditText);
	if(strText.GetLength()>= AUTHEN_LEN)
	{
		return;
	}
	strText = strText + strChar;
	SetDlgItemText(IDC_EDIT_NUM, strText);
}

void CAuthenDlg::ResetEdit()
{
	SetDlgItemText(IDC_EDIT_NUM, "");
}

void CAuthenDlg::DelLastCharInEdit()
{
	TCHAR szEditText[32];
	GetDlgItemText(IDC_EDIT_NUM,szEditText,CountArray(szEditText));
	CString strText(szEditText);
	strText = strText.Left(strText.GetLength()-1);
	SetDlgItemText(IDC_EDIT_NUM, strText);
}

void CAuthenDlg::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

//消息解释
BOOL CAuthenDlg::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message == WM_KEYDOWN)
	{
		//if (pMsg->wParam == VK_RETURN)
		//	return TRUE;
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}

//确定函数
void CAuthenDlg::OnOK()
{
	TCHAR szCodeText[32];
	GetDlgItemText(IDC_EDIT_CHECKNUM,szCodeText,CountArray(szCodeText));
	CString strCode(szCodeText);
	//if(strCode.CompareNoCase(m_strCode) != 0)
	if (m_WndValidateCode.CheckValidateCode(szCodeText)==false)
	{
		ShowInformation(TEXT("您输入的验证码不正确，请重新输入！") ,0, MB_ICONINFORMATION);
		return;
	}
	TCHAR szEditText[32];
	GetDlgItemText(IDC_EDIT_NUM,szEditText,CountArray(szEditText));
	CString strText(szEditText);
	if(strText.GetLength()!=18 && strText.GetLength()!=15)
	{
		ShowInformation(TEXT("您输入的身份证号码位数不正确，请重新输入！") ,0, MB_ICONINFORMATION);
		return;
	}
	ShowWindow(SW_HIDE);
	m_sValidateCode = strText;

// 	CString sMsg;
// 	sMsg.Format("输入sfz:%s /r/n",m_sValidateCode);
// 	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 	CLog ListLog;
// 	ListLog.Init(pGlobalServer->GetAppPath() +"\\Auhten.txt");
// 	ListLog.WriteMsg(sMsg);

//	CPlazaViewItem * pPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
//	ASSERT(pPlazaViewItem!=NULL);
	int nCode = atoi(m_strCode);
	//pPlazaViewItem->UserAuthen(strText, nCode);

	CSkinDialog::OnOK();
}

//取消消息
void CAuthenDlg::OnCancel()
{
	ShowWindow(SW_HIDE);
//	CPlazaViewItem * pPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
//	ASSERT(pPlazaViewItem!=NULL);
//	pPlazaViewItem->PostMessage(WM_COMMAND,IDM_CANCEL_CONNECT,0);

	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL)
		pMissionLogon->OnStatusCancel();

	CSkinDialog::OnCancel();
}

void CAuthenDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

}

void CAuthenDlg::OnMove(int x, int y)
{
	CSkinDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
}

void CAuthenDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CSkinDialog::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		SetDlgItemText(IDC_EDIT_NUM, "");
		SetDlgItemText(IDC_EDIT_CHECKNUM, "");
		m_strCode.Empty();

		//释放判断
// 		if ( !m_Image.IsNull() ) 
// 		{
// 			m_Image.Destroy();
// 		}
		m_InputNumDlg.ShowWindow(SW_SHOW);
		GetVerifyCode();
	}
	else
	{
		m_InputNumDlg.ShowWindow(SW_HIDE);
	}

}

void CAuthenDlg::OnDestroy()
{
	CSkinDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
