// DlgHideUser.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgHideUser.h"


// CDlgHideUser 对话框

IMPLEMENT_DYNAMIC(CDlgHideUser, CDialog)

CDlgHideUser::CDlgHideUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHideUser::IDD, pParent)
{

}

CDlgHideUser::~CDlgHideUser()
{
}

void CDlgHideUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_HideList);
}


BEGIN_MESSAGE_MAP(CDlgHideUser, CDialog)
	ON_WM_RBUTTONDOWN()

	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDlgHideUser::OnNMClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDlgHideUser::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BTREFUSH, &CDlgHideUser::OnBnClickedBtrefush)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgHideUser::OnBnClickedButton2)
	ON_COMMAND(ID_DELETE_HIDE_USER, &CDlgHideUser::OnDeleteHideUser)
END_MESSAGE_MAP()


// CDlgHideUser 消息处理程序
BOOL CDlgHideUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
// 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
// 	ASSERT(IDM_ABOUTBOX < 0xF000);

// 	CMenu* pSysMenu = GetSystemMenu(FALSE);
// 	if (pSysMenu != NULL)
// 	{
// 		CString strAboutMenu;
// 		strAboutMenu.LoadString(IDS_ABOUTBOX);
// 		if (!strAboutMenu.IsEmpty())
// 		{
// 			pSysMenu->AppendMenu(MF_SEPARATOR);
// 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
// 		}
// 	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	// TODO: Add extra initialization here
	m_HideList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_HideList.InsertColumn(0,"UserID");
	m_HideList.InsertColumn(1,"昵称");
	m_HideList.SetColumnWidth(0,100);
	m_HideList.SetColumnWidth(1,100);
//	m_GameInfo.SeleteHideUser();

	OnInsertHideUser();

// 	for (int i=0;i<m_GameInfo.m_HideUser.GetCount();i++)
// 	{
// 		m_HideList.InsertItem(i,m_GameInfo.m_HideUser[i]->UserID);
// 		m_HideList.SetItemText(i,0,m_GameInfo.m_HideUser[i]->UserID);
// 		m_HideList.SetItemText(i,1,m_GameInfo.m_HideUser[i]->NickName);
// 	}
// 	m_HideList.InitHideUserInfo();
// 	m_HideList.InsertUserInfo();

	return TRUE;

}

void CDlgHideUser::OnInsertHideUser()
{
	CString szUserID;
// 	for (int j=0;j<m_HideList.GetItemCount();j++)
// 	{
// 		szUserID = m_HideList.GetItemText(j,0);
// 		for (int k=0;k<m_GameInfo.m_HideUser.GetCount();k++)
// 		{
// 			if (szUserID == m_GameInfo.m_HideUser[k]->UserID)
// 			{
// 				return;
// 			}
// 		}
// 	}

	m_HideList.DeleteAllItems();
	for (int i=0;i<m_GameInfo.m_HideUser.GetCount();i++)
	{

		m_HideList.InsertItem(i,m_GameInfo.m_HideUser[i]->UserID);
		m_HideList.SetItemText(i,0,m_GameInfo.m_HideUser[i]->UserID);
		m_HideList.SetItemText(i,1,m_GameInfo.m_HideUser[i]->NickName);

	}
}

void CDlgHideUser::OnRButtonDown(UINT nFlags, CPoint point)
{
// 	if( GetFocus() != this )
// 		SetFocus();	// Force focus to finish editing
// 
// 	// Find out what subitem was clicked
// 	CellHitTest(point, nRow, nCol);
// 	// 
// 	// 	// If not right-clicking on an actual row, then don't update focus cell
// // 	if (nRow!=-1)
// // 	{
// // 		m_nItem = nRow;
// // 		// 		// Update the focused cell before calling CListCtrl::OnRButtonDown()
// // 		// 		// as it might cause a row-repaint
// // 		CUserInfoItem * pGameUserInfoItem = (CUserInfoItem * )GetItemData(nRow);
// // 		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;
// // 	}
// 
// 	CListCtrl::OnRButtonDown(nFlags, point);
}

void CDlgHideUser::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDlgHideUser::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	POSITION pos = m_HideList.GetFirstSelectedItemPosition() ; 

	int nIndex = m_HideList.GetNextSelectedItem(pos);
	m_nItem = nIndex;
	if (nIndex>=0)
	{
		CMenu menu, *pPopup;  
		menu.LoadMenu(IDR_MENU4);

		pPopup = menu.GetSubMenu(0);

		CPoint myPoint;  
		ClientToScreen(&myPoint);  
		GetCursorPos(&myPoint); //鼠标位置 
		//		pPopup->SetMenuItemBitmaps(ID_MARK1,MF_BYPOSITION,&m_MarkBmp1,&m_MarkBmp1); 
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);
	}

}

void CDlgHideUser::OnBnClickedBtrefush()
{
	// TODO: 在此添加控件通知处理程序代码
	OnInsertHideUser();
	m_GameInfo.SeleteHideUser();
	
}

void CDlgHideUser::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szText;
	szText = m_HideList.GetItemText(m_nItem,0);

	m_GameInfo.DeleteHideUser(_ttoi(szText));
	m_HideList.DeleteItem(m_nItem);
	m_GameInfo.SeleteHideUser();

}

void CDlgHideUser::OnDeleteHideUser()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButton2();
	m_GameInfo.SeleteHideUser();
}
