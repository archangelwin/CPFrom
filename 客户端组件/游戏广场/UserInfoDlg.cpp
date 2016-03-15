// UserInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserInfoDlg.h"
// #include ".\userinfodlg.h"
// #include "GlobalUnits.h"
#include "GlobalUnits.h"
// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialog)
CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{
	if (m_brBack.GetSafeHandle()==NULL)
	{
		m_brBack.CreateSolidBrush(RGB(229,243,255));
	}
}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserInfoDlg 消息处理程序

BOOL CUserInfoDlg::OnInitDialog()
{
	__super::OnInitDialog();
	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	VERIFY((dwExStyle & WS_EX_APPWINDOW) == 0);
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle | 0x80000);

	HMODULE hInst = LoadLibrary(_T("User32.DLL")); 
	typedef BOOL (WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD); 
	MYFUNC SetLayeredWindowAttributes = NULL; 
	SetLayeredWindowAttributes = (MYFUNC)::GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
	SetLayeredWindowAttributes(GetSafeHwnd(), 0, 180, 2); 
	::FreeLibrary(hInst);

// 	CPoint point;
// 	GetCursorPos(&point);
// 
// 	CRect rcClient;
// 	GetWindowRect(&rcClient);
// 
// 	MoveWindow(point.x,point.y,rcClient.Width(),rcClient.Height());

	return TRUE;
}

void CUserInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

}

HBRUSH CUserInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_STATIC:
		{
			if(pWnd->GetDlgCtrlID() == IDC_STATIC || pWnd->GetDlgCtrlID() == IDC_STATIC_SCORE)
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(198,109,225));
				pDC->SetTextColor(RGB(40,40,150));
			}
			else
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(198,109,225));
				pDC->SetTextColor(RGB(0,0,40));
			}
			return m_brBack;
		}
	}
	return hbr;
}

//设置信息
void CUserInfoDlg::UpdateUI(IClientUserItem * pIClientUserItem,LPCTSTR pszGameLevel)
{
	if(pIClientUserItem)
	{
		//用户账号
		GetDlgItem(IDC_STC_ACCOUNT)->SetWindowText(pIClientUserItem->GetNickName());
		CString strTemp;
		//用户ID
		strTemp.Format(_T("%lu"), pIClientUserItem->GetGameID());
		GetDlgItem(IDC_STC_ID)->SetWindowText(strTemp);

		//欢乐豆积分
//		if(pIClientUserItem->GetUserScore())
// 		{
//			strTemp.Format(_T("%I64d"), pIClientUserItem->GetUserScore());
//			GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("金 币："));
// 		}
// 		else
// 		{
// 			strTemp.Format(_T("%I64d"), pUserData->lGameGold);
// 			GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("积 分："));
// 		}
		strTemp.Format(_T("%I64d"), pIClientUserItem->GetUserScore());
		GetDlgItem(IDC_STC_SCORE)->SetWindowText(strTemp);

		//游戏等级
		GetDlgItem(IDC_STC_RANK)->SetWindowText(pszGameLevel);

// 		//游戏胜局
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserWinCount());
// 		GetDlgItem(IDC_STC_WINNUM)->SetWindowText(strTemp);
// 
// 		//游戏输局
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserLostCount());
// 		GetDlgItem(IDC_STC_LOSTNUM)->SetWindowText(strTemp);
// 
// 		//游戏和局
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserDrawCount());
// 		GetDlgItem(IDC_STC_TIENUM)->SetWindowText(strTemp);


		//游戏胜率
// 		if(nTotle != 0)
// 		{
// 			strTemp.Format(_T("%5.2f%%"), (double)(pUserData->lWinCount*100)/(double)(nTotle));
// 		}
// 		else
// 		{
// 			strTemp = _T("0%");
// 		}
// 		//逃跑局数
// 		strTemp.Format("%d",pIClientUserItem->GetUserFleeCount());
// 		GetDlgItem(IDC_STC_FLEE)->SetWindowText(strTemp);
// 
// 		//逃跑
// 		strTemp.Format(_T("%5.2f%%"), pIClientUserItem->GetUserWinRate());
// 		GetDlgItem(IDC_STC_WINRATE)->SetWindowText(strTemp);


		//逃率
// 		if(nTotle != 0)
// 		{
// 			strTemp.Format(_T("%5.2f%%"), (double)(pUserData->lFleeCount*100)/(double)(nTotle));
// 		}
// 		else
// 		{
// 			strTemp = _T("0%");
// 		}

// 		CString szFleeRate;
// 		szFleeRate.Format(_T("%5.2f%%"),pIClientUserItem->GetUserFleeRate());
// 		GetDlgItem(IDC_STC_LOSTRATE)->SetWindowText(szFleeRate);

// 		//个性签名
// 		GetDlgItem(IDC_STC_SIGNATURE)->SetWindowText(pIClientUserItem->GetUnderWrite());

	}


}

//移动位置
VOID CUserInfoDlg::RectifyControl()
{

	CRect rcCleint;
	GetClientRect(&rcCleint);

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	int nX = MousePoint.x + 20;
	int nY = MousePoint.y + 20;
	if(nY + rcCleint.Height() > rcCleint.bottom)
	{
		nY -= rcCleint.Height();
	}
	
	SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOSIZE|SWP_NOZORDER);

	return;
}