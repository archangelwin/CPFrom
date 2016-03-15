// UserOfflineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserOfflineDlg.h"


// CUserOfflineDlg 对话框

IMPLEMENT_DYNAMIC(CUserOfflineDlg, CDialog)

CUserOfflineDlg::CUserOfflineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserOfflineDlg::IDD, pParent)
{
		m_GetOffLine = false;
}

CUserOfflineDlg::~CUserOfflineDlg()
{
}

void CUserOfflineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_OffLineList);
	DDX_Control(pDX, IDC_BUTTON_GET_OFFLINE, m_BtGetOffLine);
}


BEGIN_MESSAGE_MAP(CUserOfflineDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_OFFLINE, &CUserOfflineDlg::OnBnClickedButtonGetOffline)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUserOfflineDlg 消息处理程序
//创建函数
BOOL CUserOfflineDlg::OnInitDialog()
{
	__super::OnInitDialog();

	m_OffLineList.InitUserInfoList();
	m_OffLineList.SetCellMargin(1.5);

	return TRUE;
}

void CUserOfflineDlg::OnBnClickedButtonGetOffline()
{
	// TODO: 在此添加控件通知处理程序代码
	m_OffLineList.DeleteAllItems();
// 	CUserInfoMap::iterator it = m_UserOffLineMap.begin();
// 	for (it;it!=m_UserOffLineMap.end();it++)
// 	{
// 		CUserInfoItem* pInfo = it->second;
// 		if (pInfo != NULL)
// 		{
// 			delete pInfo;
// 		}
// 		m_UserOffLineMap.erase(it->first);
// 	}
	m_UserOffLineMap.clear();
//	m_GetOffLine = true;


//	CUserServerInfo* pCUserInfo = CUserServerInfo::GetInstance();
	CMissionUserInfo* pUserInfo = CMissionUserInfo::GetInstance();
	pUserInfo->OnGetOffLineUser();
	
}

void CUserOfflineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect m_Rect;
	GetClientRect(&m_Rect);
	// TODO: 在此处添加消息处理程序代码
	if (m_OffLineList)
	{
		m_OffLineList.MoveWindow(m_Rect.left,m_Rect.top,m_Rect.Width()-10,m_Rect.Height()-50);
		m_BtGetOffLine.MoveWindow(m_Rect.left,m_Rect.top+m_Rect.Height()-50+5,80,40);
	}
}


bool CUserOfflineDlg::OnInsertOFFLineUserInfo(tagUMUserScoreSet* pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	CUserInfoItem* pCUserInfoItem = NULL;
	CUserInfoMap::iterator it = m_UserOffLineMap.find(pUserInfo->dwUserID);

	if (it == m_UserOffLineMap.end())
	{
		pCUserInfoItem = new CUserInfoItem;
		if (pCUserInfoItem==NULL) return false;
		m_UserOffLineMap.insert(std::make_pair(pUserInfo->dwUserID,pCUserInfoItem));
	}else
	 	pCUserInfoItem = it->second;

	CopyMemory(&pCUserInfoItem->m_tagUMUserScoreSet,pUserInfo,sizeof(tagUMUserScoreSet));

	m_OffLineList.OnGameUserInfoInsert(pCUserInfoItem);

	return true;
}

BOOL CUserOfflineDlg::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
