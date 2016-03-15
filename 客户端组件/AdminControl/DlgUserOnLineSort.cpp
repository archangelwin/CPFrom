// DlgUserOnLineSort.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgUserOnLineSort.h"
#include "UserServerInfo.h"

// CDlgUserOnLineSort 对话框

IMPLEMENT_DYNAMIC(CDlgUserOnLineSort, CDialog)

CDlgUserOnLineSort::CDlgUserOnLineSort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserOnLineSort::IDD, pParent)
{

}

CDlgUserOnLineSort::~CDlgUserOnLineSort()
{
}

void CDlgUserOnLineSort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_UserInfoList);
	DDX_Control(pDX, IDC_BUTTON_REFUSH, m_BtRefresh);
	DDX_Control(pDX, IDC_LIST2, m_DecList);
}


BEGIN_MESSAGE_MAP(CDlgUserOnLineSort, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_REFUSH, &CDlgUserOnLineSort::OnBnClickedButtonRefush)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDlgUserOnLineSort::OnNMRClickList1)
END_MESSAGE_MAP()


// CDlgUserOnLineSort 消息处理程序

//创建函数
BOOL CDlgUserOnLineSort::OnInitDialog()
{
	__super::OnInitDialog();

	m_UserInfoList.InitUserInfoList();
	m_UserInfoList.SetCellMargin(1.5);

	m_DecList.InitUserInfoList();
	m_DecList.SetCellMargin(1.5);

	return TRUE;
}


BOOL CDlgUserOnLineSort::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
void CDlgUserOnLineSort::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect m_Rect;
	GetClientRect(&m_Rect);
	// TODO: 在此处添加消息处理程序代码
	if (m_UserInfoList)
	{
		m_UserInfoList.MoveWindow(m_Rect.left,m_Rect.top,m_Rect.Width()/2-10,m_Rect.Height()-50);
		m_DecList.MoveWindow(m_Rect.left+m_Rect.Width()/2,m_Rect.top,m_Rect.Width()/2-10,m_Rect.Height()-50);
		m_BtRefresh.MoveWindow(m_Rect.left,m_Rect.top+m_Rect.Height()-50+5,80,40);
	}
}

void CDlgUserOnLineSort::OnBnClickedButtonRefush()
{
	// TODO: 在此添加控件通知处理程序代码
	int i=0;
	int j=0;

	m_UserInfoList.DeleteAllItems();
	m_DecList.DeleteAllItems();

	CUserServerInfo* pCUserInfo = CUserServerInfo::GetInstance();
	pCUserInfo->OnUserInfoSort();


	vector<pair<DWORD,CUserInfoItem*>>::iterator iter;
	for (iter = pCUserInfo->tUserVector.begin();iter != pCUserInfo->tUserVector.end();iter++)
	{	
		m_UserInfoList.OnGameUserInfoInsert(iter->second);
		i++;
		if (i==10)
		{
			break;
		}
	}

	vector<pair<DWORD,CUserInfoItem*>>::const_reverse_iterator it;
	for (it = pCUserInfo->tUserVector.rbegin();it != pCUserInfo->tUserVector.rend();it++)
	{
		m_DecList.OnGameUserInfoInsert(it->second);
		j++;
		if (j==10)
		{
			break;
		}
	}
}

void CDlgUserOnLineSort::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
