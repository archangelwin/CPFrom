#include "StdAfx.h"
#include "MatchList.h"
#include "PlatformFrame.h"

//默认属性
#define LIST_STYTE					LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE

CMatchList::CMatchList(void)
{

}

CMatchList::~CMatchList(void)
{

}

BEGIN_MESSAGE_MAP(CMatchList, CListCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM_REFLECT()
//	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
//ON_WM_LBUTTONDOWN()
    ON_NOTIFY_REFLECT_EX(NM_CLICK, &CMatchList::OnNMClick)
	//ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CMatchList::OnLvnItemchanged)
END_MESSAGE_MAP()

//控件绑定
VOID CMatchList::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//设置滚动
	//m_SkinScrollBar.InitScroolBar(this);

	////设置颜色
	//SetBkColor(m_SkinAttribute.m_crListBK);
	//SetTextColor(m_SkinAttribute.m_crListTX);
	//SetTextBkColor(m_SkinAttribute.m_crListBK);

	//设置属性
	//SetExtendedStyle(LIST_STYTE);
	//m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return;
}

void CMatchList::ResetData()
{
	DeleteAllItems();
}

//绘画函数
VOID CMatchList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//变量定义
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	//获取属性
	INT nItemID=lpDrawItemStruct->itemID;
	//INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//定制颜色
	COLORREF rcTextColor=RGB(10,10,10);
	COLORREF rcBackColor=RGB(229,249,255);
	//GetItemColor(lpDrawItemStruct,rcTextColor,rcBackColor);

	//绘画区域
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	//设置环境
	pDC->SetBkColor(rcBackColor);
	//pDC->SetBkColor(RGB(255,0,0));
	pDC->SetTextColor(rcTextColor);

	//绘画子项
	int nCount = GetItemCount();
	for (INT i=0;i<GetItemCount();i++)
	{
		//获取位置
		CRect rcSubItem;
		GetSubItemRect(nItemID,i,LVIR_BOUNDS,rcSubItem);

		//绘画判断
		if (rcSubItem.left>rcClipBox.right) break;
		if (rcSubItem.right<rcClipBox.left) continue;

		CPngImageSB m_ImageRoomItem;
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance(); 
		CString sPngPath;

		int nServerID = GetItemData(nItemID);
		CServerListData * pServerListData=CServerListData::GetInstance();
		CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
		if (pGameServerItem!=NULL)
		{
			sPngPath.Format("%s%sm_%d.png",pGlobalServer->GetAppPath(),"\\GameKind\\",pGameServerItem->m_GameServer.wKindID);
			m_ImageRoomItem.LoadImage(sPngPath);	
			if (m_ImageRoomItem.IsNull())
			{
				sPngPath.Format("%s%sm_0.png",pGlobalServer->GetAppPath(),"\\GameKind\\");
				m_ImageRoomItem.LoadImage(sPngPath);
			}			
		}
		else
		{
			sPngPath.Format("%s%s0.png",pGlobalServer->GetAppPath(),"\\GameKind\\");
			m_ImageRoomItem.LoadImage(sPngPath);
		}
		m_ImageRoomItem.DrawImage(pDC,rcSubItem.left+4,rcSubItem.top);
		//绘画背景
		//pDC->FillSolidRect(&rcSubItem,RGB(255,0,0));

		//if (nColumnCount ==4)
		//{
		//	CFont nFont ,* nOldFont; 
		//	nFont.CreateFont(100,200,0,0,600,TRUE,TRUE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体 
		//	nOldFont = pDC->SelectObject(&nFont);
		//}

		//绘画数据
		//DrawCustomItem(pDC,lpDrawItemStruct,rcSubItem,i);
	}


	//rcWindowRect.InflateRect(1,1,1,1);
	//绘画焦点
	//if (lpDrawItemStruct->itemState&ODS_FOCUS)
	//{
	//	pDC->DrawFocusRect(&rcItem);
	//}

	return;
}

void CMatchList::ClearSelMask()
{
	POSITION    pos;
	int         n;
	pos = GetFirstSelectedItemPosition ();
	while (pos)
	{
		n = GetNextSelectedItem (pos);
		if (n >= 0)
			SetItemState (n, 0, LVIS_FOCUSED | LVIS_SELECTED);
	}
}

void CMatchList::SetItemHeight(UINT nHeight)
{
	m_nItemHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

//建立消息
INT CMatchList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置滚动
	//m_SkinScrollBar.InitScroolBar(this);

	////设置颜色
	//SetBkColor(m_SkinAttribute.m_crListBK);
	//SetTextColor(m_SkinAttribute.m_crListTX);
	//SetTextBkColor(m_SkinAttribute.m_crListBK);

	//设置属性
	//SetExtendedStyle(LIST_STYTE|LVS_OWNERDRAWFIXED );
	//m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	InitializeFlatSB(this->m_hWnd);                                                 
	FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);   

	return 0;
}

//绘画数据
VOID CMatchList::DrawCustomItem(CDC * pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect & rcSubItem, INT nColumnIndex)
{
	//获取文字
	TCHAR szString[256]=TEXT("");
	GetItemText(lpDrawItemStruct->itemID,nColumnIndex,szString,CountArray(szString));

	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//if (m_nItemHeight >0 && nColumnIndex == m_nCustomColumn)
	//{	
	//	CFont boldfont;
	//	LOGFONT lf;          //定义一个字体结构体的实例对象logFont
	//	CSkinResourceManager::GetInstance()->GetDefaultFont().GetLogFont(&lf);
	//	lf.lfUnderline =TRUE;
	//	boldfont.CreateFontIndirect(&lf);
	//	/*pOldFont =*/ pDC->SelectObject(&boldfont);
	//}


	//绘画文字
	rcSubItem.left+=5;
	pDC->DrawText(szString,lstrlen(szString),&rcSubItem,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_CENTER);


	return;
}

//插入数据
//VOID CMatchList::InsertDataItem(VOID * pItemData)
//{
//	//效验状态
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//变量定义
//	INT nItemInsert=0;
//	INT nColumnCount= 2;//m_SkinHeaderCtrl.GetItemCount();
//
//	//插入数据
//	for (INT i=0;i<nColumnCount;i++)
//	{
//		//获取描述
//		TCHAR szString[256]=TEXT("");
//		//ConstructString(pItemData,i,szString,CountArray(szString));
//
//		//插入列表
//		if (i==0)
//		{
//			//nItemInsert=InsertItem(LVIF_TEXT|LVIF_PARAM,GetInsertIndex(pItemData),szString,0,0,0,(LPARAM)pItemData);
//		}
//		else
//		{
//			SetItem(nItemInsert,i,LVIF_TEXT,szString,0,0,0,0);
//		}
//	}
//
//	return;
//}

//更新数据
//VOID CMatchList::UpdateDataItem(VOID * pItemData)
//{
//	//效验状态
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//变量定义
//	LVFINDINFO FindInfo;
//	ZeroMemory(&FindInfo,sizeof(FindInfo));
//
//	//设置变量
//	FindInfo.flags=LVFI_PARAM;
//	FindInfo.lParam=(LPARAM)pItemData;
//
//	//查找数据
//	INT nItem=FindItem(&FindInfo);
//	INT nColumnCount=2;//m_SkinHeaderCtrl.GetItemCount();
//
//	//更新数据
//	if (nItem!=-1L)
//	{
//		//更新数据
//		for (INT i=0;i<nColumnCount;i++)
//		{
//			//获取描述
//			TCHAR szString[256]=TEXT("");
//			//ConstructString(pItemData,i,szString,CountArray(szString));
//
//			//设置列表
//			SetItem(nItem,i,LVIF_TEXT,szString,0,0,0,0);
//		}
//
//		//更新子项
//		RedrawItems(nItem,nItem);
//	}
//
//	return;
//}
//
////删除数据
//VOID CMatchList::DeleteDataItem(VOID * pItemData)
//{
//	//效验状态
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//变量定义
//	LVFINDINFO FindInfo;
//	ZeroMemory(&FindInfo,sizeof(FindInfo));
//
//	//构造变量
//	FindInfo.flags=LVFI_PARAM;
//	FindInfo.lParam=(LPARAM)pItemData;
//
//	//删除数据
//	INT nItem=FindItem(&FindInfo);
//	if (nItem!=-1L) DeleteItem(nItem);
//
//	return;
//}

//绘画背景
BOOL CMatchList::OnEraseBkgnd(CDC * pDC)
{
	//获取窗口
	CWnd * pHeader=GetHeaderCtrl();
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	LOGFONT logFont;          //定义一个字体结构体的实例对象logFont
	CSkinResourceManager::GetInstance()->GetDefaultFont().GetLogFont(&logFont);

	//窗口判断
	if (pHeader->GetSafeHwnd()!=NULL)
	{
		//获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		//获取位置
		CRect rcHeader;
		pHeader->GetWindowRect(&rcHeader);

		//绘画背景
		rcClient.top=rcHeader.Height();
		pDC->FillSolidRect(&rcClient,GetBkColor());

		return TRUE;
	}

	return __super::OnEraseBkgnd(pDC);
}

void CMatchList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if( m_nItemHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
}


//获取通知
VOID CMatchList::OnGameItemFinish()
{
	//if (!m_bInsertLastRoom)
	//{
	//	//最近游戏
	//	InsertLastPlayGame();

	//	//CGameTypeItem                   ItemType;                   
	//	//ItemType.m_GameType.wTypeID=0;
	//	//ItemType.m_GameType.wSortID=100;
	//	//ItemType.m_GameType.wJoinID=0;

	//	//InsertGameListItem("",-1,&ItemType,m_TreeListRoot,90,false);
	//}
	//m_bInsertLastRoom = true;
	////变量定义
	//POSITION Position=NULL;
	//CServerListData * pServerListData=CServerListData::GetInstance();

	////展开列表
	////for (DWORD i=0;i<pServerListData->GetGameTypeCount();i++)
	////{
	////	CGameTypeItem * pGameTypeItem=pServerListData->EmunGameTypeItem(Position);
	////	if (pGameTypeItem!=NULL) 
	////		ExpandListItem(pGameTypeItem);
	////}
	//HTREEITEM hItemFirstType = GetNextItem(GetRootItem(),TVGN_NEXT);
	//if (hItemFirstType!=NULL)
	//{
	//	ExpandListItem(hItemFirstType);
	//	//HTREEITEM hItemFirstKind = GetChildItem(hItemFirstType);
	//	//if (hItemFirstKind!=NULL)
	//	//{
	//	//	ExpandListItem(hItemFirstKind);
	//	//}
	//}

	////展开列表
	//ExpandListItem(&m_LastServerItem);

	////展开列表
	////if (m_TreeListRoot!=NULL) 
	////	ExpandListItem(m_TreeListRoot);

	////保证可视
	//EnsureVisible(m_TreeListRoot);

	////更新人数
	//ASSERT(CMissionList::GetInstance()!=NULL);
	//CMissionList::GetInstance()->UpdateOnLineInfo();
	//SetTimer(IDI_UPDATE_ONLINE,TIME_UPDATE_ONLINE,NULL);

	return;
}

//获取通知
VOID CMatchList::OnGameKindFinish(WORD wKindID)
{
	//获取类型
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//类型处理
	//if (pGameKindItem!=NULL)
	//{
	//	//变量定义
	//	LPCTSTR pszTitle=TEXT("没有可用游戏房间");
	//	HTREEITEM hItemAttachUpdate=pGameKindItem->m_hItemAttachUpdate;
	//	HTREEITEM hItemNormalUpdate=pGameKindItem->m_hItemNormalUpdate;

	//	//更新标题
	//	if (hItemAttachUpdate!=NULL) SetItemText(hItemAttachUpdate,pszTitle);
	//	if (hItemNormalUpdate!=NULL) SetItemText(hItemNormalUpdate,pszTitle);
	//}

	return;
}

//更新通知
VOID CMatchList::OnGameItemUpdateFinish()
{
	//更新人数
	//CPlatformFrame::GetInstance()->UpDataAllOnLineCount();

	return;
}

//插入通知
VOID CMatchList::OnGameItemInsert(CGameListItem * pGameListItem)
{
	//效验参数
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//插入处理
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//游戏种类
		{
			break;
		}
	case ItemGenre_Kind:	//游戏类型
		{
			break;
		}
	case ItemGenre_Node:	//游戏节点
		{
			break;
		}
	case ItemGenre_Page:	//定制子项
		{
			break;
		}
	case ItemGenre_Server:	//游戏房间
		{
			//if (GetItemCount() <4)
			//{
				//变量定义
				CGameListItem * pParentListItem=pGameListItem->GetParentListItem();
				CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;

				int nCnt(0),nCtrlIndex(1);
				nCnt = GetItemCount();
				CString str;
				str.Format("%s%d",pGameServerItem->m_GameServer.szServerName,pGameServerItem->m_GameServer.wServerID);
				InsertItem(nCnt,pGameServerItem->m_GameServer.szDescription);
				SetItemText(nCnt,1,str);
				SetItemData(nCnt,pGameServerItem->m_GameServer.wServerID);
				break;
			//}
		}
	}

	return;
}

//更新通知
VOID CMatchList::OnGameItemUpdate(CGameListItem * pGameListItem)
{
	//效验参数
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//插入处理
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//游戏种类
		{
			//变量定义
			//CGameTypeItem * pGameTypeItem=(CGameTypeItem *)pGameListItem;

			////设置子项
			//if (pGameTypeItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
			//	ModifyGameListItem(pGameTypeItem->m_hTreeItemAttach,pszTypeName,-1);
			//}

			////设置子项
			//if (pGameTypeItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
			//	ModifyGameListItem(pGameTypeItem->m_hTreeItemNormal,pszTypeName,-1);
			//}

			break;
		}
	case ItemGenre_Kind:	//游戏类型
		{
			//变量定义
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;

			//构造数据
			//TCHAR szTitle[64]=TEXT("");
			//UINT uNormalImage=GetGameKindImageIndex(pGameKindItem);
			//GetGameKindItemTitle(pGameKindItem,szTitle,CountArray(szTitle));

			////设置子项
			//if (pGameKindItem->m_hTreeItemAttach!=NULL)
			//{
			//	ModifyGameListItem(pGameKindItem->m_hTreeItemAttach,szTitle,-1);
			//}

			////设置子项
			//if (pGameKindItem->m_hTreeItemNormal!=NULL)
			//{
			//	ModifyGameListItem(pGameKindItem->m_hTreeItemNormal,szTitle,-1);
			//}

			break;
		}
	case ItemGenre_Node:	//游戏节点
		{
			//变量定义
			CGameNodeItem * pGameNodeItem=(CGameNodeItem *)pGameListItem;

			////设置子项
			//if (pGameNodeItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
			//	ModifyGameListItem(pGameNodeItem->m_hTreeItemAttach,pszNodeName,IND_NODE);
			//}

			////设置子项
			//if (pGameNodeItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
			//	ModifyGameListItem(pGameNodeItem->m_hTreeItemNormal,pszNodeName,IND_NODE);
			//}

			break;
		}
	case ItemGenre_Page:	//定制子项
		{
			//变量定义
			CGamePageItem * pGamePageItem=(CGamePageItem *)pGameListItem;

			//设置子项
			//if (pGamePageItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
			//	ModifyGameListItem(pGamePageItem->m_hTreeItemAttach,pszDisplayName,IND_BROWSE);
			//}

			////设置子项
			//if (pGamePageItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
			//	ModifyGameListItem(pGamePageItem->m_hTreeItemNormal,pszDisplayName,IND_BROWSE);
			//}

			break;
		}
	case ItemGenre_Server:	//游戏房间
		{
			//变量定义
			CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;

			//构造数据
			TCHAR szTitle[64]=TEXT("");
			UINT uImageIndex=-1 ; //GetGameServerImageIndex(pGameServerItem);
			//GetGameServerItemTitle(pGameServerItem,szTitle,CountArray(szTitle));

			//设置子项
			//if (pGameServerItem->m_hTreeItemAttach!=NULL)
			//{
			//	ModifyGameListItem(pGameServerItem->m_hTreeItemAttach,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			//}

			////设置子项
			//if (pGameServerItem->m_hTreeItemNormal!=NULL)
			//{
			//	ModifyGameListItem(pGameServerItem->m_hTreeItemNormal,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			//}

			//最近插入
			/*if(IsLastPlayGame(pGameServerItem->m_GameServer.wServerID))
			{
				HTREEITEM hTreeServerItem = EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal, pGameServerItem->m_GameServer.wServerID);
				if(hTreeServerItem!=NULL)
				{
					ModifyGameListItem(hTreeServerItem,szTitle,uImageIndex);
				}
			}*/

			break;
		}
	}

	return;
}

//删除通知
VOID CMatchList::OnGameItemDelete(CGameListItem * pGameListItem)
{
	//效验参数
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//删除树项
	//if (pGameListItem->m_hTreeItemAttach!=NULL) DeleteItem(pGameListItem->m_hTreeItemAttach);
	//if (pGameListItem->m_hTreeItemNormal!=NULL) DeleteItem(pGameListItem->m_hTreeItemNormal);

	//删除树项
	//if(pGameListItem->GetItemGenre() == ItemGenre_Server)
	//{
	//	HTREEITEM hTreeitem=EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal,((CGameServerItem *)pGameListItem)->m_GameServer.wServerID);
	//	if(hTreeitem!=NULL) DeleteItem(hTreeitem);
	//}

	return;
}

void CMatchList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	POSITION pos = GetFirstSelectedItemPosition();
	if(pos!=NULL)
	{
		while(pos)
		{
			int Item = GetNextSelectedItem(pos);
			int nServerID= GetItemData(Item);
			//
			//获取类型
			CServerListData * pServerListData=CServerListData::GetInstance();
			CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
			if (pGameServerItem!=NULL)
			{
				//进入房间
				CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
				pPlatformFrame->EntranceServerItem(pGameServerItem);
			}
		}

		
	}
	else
	{
		TRACE0("No items were selected!\n");
	}
	__super::OnLButtonDown(nFlags, point);
}


BOOL CMatchList::OnNMClick(NMHDR * pNotifyStruct, LRESULT* result)
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)pNotifyStruct;
	ASSERT(lpnmitem);
	
	/*LVHITTESTINFO info;
	info.pt = lpnmitem->ptAction;
	info.flags = LVHT_ONITEM;
	info.iItem = lpnmitem->iItem;
	info.iSubItem = lpnmitem->iSubItem;
	info.iGroup = 0;
	int iIndex = SubItemHitTest(&info);*/
	int iIndex = lpnmitem->iItem;
	if (-1 != iIndex)
	{
		int nServerID= GetItemData(iIndex);
		//
		//获取类型
		CServerListData * pServerListData=CServerListData::GetInstance();
		CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
		if (pGameServerItem!=NULL)
		{
			//进入房间
			CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
			pPlatformFrame->EntranceServerItem(pGameServerItem);
		}
	}
	else
	{
		AfxDebugBreak();
	}
	*result = 0;
	return FALSE;
}

//void CMatchList::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	CString str;
//	str.Format(_T("OnItemchangedListCtrl.  Item index: %d"), pNMLV->iItem);
//
//	int nServerID= GetItemData(pNMLV->iItem);
//	//获取类型
//	CServerListData * pServerListData=CServerListData::GetInstance();
//	CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
//	if (pGameServerItem!=NULL)
//	{
//		//进入房间
//		CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
//		pPlatformFrame->EntranceServerItem(pGameServerItem);
//		return;
//	}
//	*pResult = 0;
//}
