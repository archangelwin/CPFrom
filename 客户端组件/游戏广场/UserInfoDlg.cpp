// UserInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UserInfoDlg.h"
// #include ".\userinfodlg.h"
// #include "GlobalUnits.h"
#include "GlobalUnits.h"
// CUserInfoDlg �Ի���

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


// CUserInfoDlg ��Ϣ�������

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

//������Ϣ
void CUserInfoDlg::UpdateUI(IClientUserItem * pIClientUserItem,LPCTSTR pszGameLevel)
{
	if(pIClientUserItem)
	{
		//�û��˺�
		GetDlgItem(IDC_STC_ACCOUNT)->SetWindowText(pIClientUserItem->GetNickName());
		CString strTemp;
		//�û�ID
		strTemp.Format(_T("%lu"), pIClientUserItem->GetGameID());
		GetDlgItem(IDC_STC_ID)->SetWindowText(strTemp);

		//���ֶ�����
//		if(pIClientUserItem->GetUserScore())
// 		{
//			strTemp.Format(_T("%I64d"), pIClientUserItem->GetUserScore());
//			GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("�� �ң�"));
// 		}
// 		else
// 		{
// 			strTemp.Format(_T("%I64d"), pUserData->lGameGold);
// 			GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("�� �֣�"));
// 		}
		strTemp.Format(_T("%I64d"), pIClientUserItem->GetUserScore());
		GetDlgItem(IDC_STC_SCORE)->SetWindowText(strTemp);

		//��Ϸ�ȼ�
		GetDlgItem(IDC_STC_RANK)->SetWindowText(pszGameLevel);

// 		//��Ϸʤ��
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserWinCount());
// 		GetDlgItem(IDC_STC_WINNUM)->SetWindowText(strTemp);
// 
// 		//��Ϸ���
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserLostCount());
// 		GetDlgItem(IDC_STC_LOSTNUM)->SetWindowText(strTemp);
// 
// 		//��Ϸ�;�
// 		strTemp.Format(_T("%ld"), pIClientUserItem->GetUserDrawCount());
// 		GetDlgItem(IDC_STC_TIENUM)->SetWindowText(strTemp);


		//��Ϸʤ��
// 		if(nTotle != 0)
// 		{
// 			strTemp.Format(_T("%5.2f%%"), (double)(pUserData->lWinCount*100)/(double)(nTotle));
// 		}
// 		else
// 		{
// 			strTemp = _T("0%");
// 		}
// 		//���ܾ���
// 		strTemp.Format("%d",pIClientUserItem->GetUserFleeCount());
// 		GetDlgItem(IDC_STC_FLEE)->SetWindowText(strTemp);
// 
// 		//����
// 		strTemp.Format(_T("%5.2f%%"), pIClientUserItem->GetUserWinRate());
// 		GetDlgItem(IDC_STC_WINRATE)->SetWindowText(strTemp);


		//����
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

// 		//����ǩ��
// 		GetDlgItem(IDC_STC_SIGNATURE)->SetWindowText(pIClientUserItem->GetUnderWrite());

	}


}

//�ƶ�λ��
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