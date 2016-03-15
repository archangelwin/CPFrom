// DlgSilver.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgSilver.h"


// CDlgSilver 对话框

IMPLEMENT_DYNAMIC(CDlgSilver, CDialog)

CDlgSilver::CDlgSilver(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSilver::IDD, pParent)
{

}

CDlgSilver::~CDlgSilver()
{
}

void CDlgSilver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_SilverList);
}


BEGIN_MESSAGE_MAP(CDlgSilver, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgSilver 消息处理程序
//创建函数
BOOL CDlgSilver::OnInitDialog()
{
	__super::OnInitDialog();

	m_SilverList.InitUserInfoList();
	m_SilverList.SetCellMargin(1.5);
	m_SilverList.m_IsFirstList = false;

	return TRUE;
}

bool CDlgSilver::OnInsertSilver(tagUMUserScoreSet* pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	CUserInfoItem* pCUserInfoItem = NULL;
	CUserInfoMap::iterator it = m_SilverMap.find(pUserInfo->dwUserID);

	if (it == m_SilverMap.end())
	{
		pCUserInfoItem = new CUserInfoItem;
		if (pCUserInfoItem==NULL) return false;
		m_SilverMap.insert(std::make_pair(pUserInfo->dwUserID,pCUserInfoItem));
	}else
		pCUserInfoItem = it->second;

	CopyMemory(&pCUserInfoItem->m_tagUMUserScoreSet,pUserInfo,sizeof(tagUMUserScoreSet));

	CServerListData* pCServerListData = CServerListData::GetInstance();
	CGameServerItem * pGameServerItem = NULL;
	if (pCServerListData == NULL)
	{
		return false;
	}
	if (pCServerListData->m_GameServerItemMap.Lookup(pUserInfo->dwServerID,pGameServerItem)==TRUE)
	{
		if (pGameServerItem == NULL)
		{
			return false;
		}
		pCUserInfoItem->szServerName = pGameServerItem->m_GameServer.szServerName;

	}

	m_SilverList.OnGameUserInfoInsert(pCUserInfoItem);

	return true;
}

bool CDlgSilver::OnDeleteSilver(tagUMUserScoreSet* pUserInfo)
{
	ASSERT(pUserInfo!=NULL);
	if (pUserInfo==NULL) return false;

	CUserInfoMap::iterator it = m_SilverMap.find(pUserInfo->dwUserID);

	if (it != m_SilverMap.end())
	{
		m_SilverList.OnGameUserInfoDelete(it->second);

		m_SilverMap.erase(it);
	}
	
	return true;
}

void CDlgSilver::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect m_Rect;
	GetClientRect(&m_Rect);
	if (m_SilverList)
	{
		m_SilverList.MoveWindow(m_Rect.left,m_Rect.top,m_Rect.Width()-10,m_Rect.Height()-50);
	}
}

BOOL CDlgSilver::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
