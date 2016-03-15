#include "StdAfx.h"
#include "MatchList.h"
#include "PlatformFrame.h"

//Ĭ������
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

//�ؼ���
VOID CMatchList::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//���ù���
	//m_SkinScrollBar.InitScroolBar(this);

	////������ɫ
	//SetBkColor(m_SkinAttribute.m_crListBK);
	//SetTextColor(m_SkinAttribute.m_crListTX);
	//SetTextBkColor(m_SkinAttribute.m_crListBK);

	//��������
	//SetExtendedStyle(LIST_STYTE);
	//m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return;
}

void CMatchList::ResetData()
{
	DeleteAllItems();
}

//�滭����
VOID CMatchList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//��������
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	//��ȡ����
	INT nItemID=lpDrawItemStruct->itemID;
	//INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//������ɫ
	COLORREF rcTextColor=RGB(10,10,10);
	COLORREF rcBackColor=RGB(229,249,255);
	//GetItemColor(lpDrawItemStruct,rcTextColor,rcBackColor);

	//�滭����
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	//���û���
	pDC->SetBkColor(rcBackColor);
	//pDC->SetBkColor(RGB(255,0,0));
	pDC->SetTextColor(rcTextColor);

	//�滭����
	int nCount = GetItemCount();
	for (INT i=0;i<GetItemCount();i++)
	{
		//��ȡλ��
		CRect rcSubItem;
		GetSubItemRect(nItemID,i,LVIR_BOUNDS,rcSubItem);

		//�滭�ж�
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
		//�滭����
		//pDC->FillSolidRect(&rcSubItem,RGB(255,0,0));

		//if (nColumnCount ==4)
		//{
		//	CFont nFont ,* nOldFont; 
		//	nFont.CreateFont(100,200,0,0,600,TRUE,TRUE,0,0,0,0,0,0,_TEXT("����"));//�������� 
		//	nOldFont = pDC->SelectObject(&nFont);
		//}

		//�滭����
		//DrawCustomItem(pDC,lpDrawItemStruct,rcSubItem,i);
	}


	//rcWindowRect.InflateRect(1,1,1,1);
	//�滭����
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

//������Ϣ
INT CMatchList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ù���
	//m_SkinScrollBar.InitScroolBar(this);

	////������ɫ
	//SetBkColor(m_SkinAttribute.m_crListBK);
	//SetTextColor(m_SkinAttribute.m_crListTX);
	//SetTextBkColor(m_SkinAttribute.m_crListBK);

	//��������
	//SetExtendedStyle(LIST_STYTE|LVS_OWNERDRAWFIXED );
	//m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	InitializeFlatSB(this->m_hWnd);                                                 
	FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);   

	return 0;
}

//�滭����
VOID CMatchList::DrawCustomItem(CDC * pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect & rcSubItem, INT nColumnIndex)
{
	//��ȡ����
	TCHAR szString[256]=TEXT("");
	GetItemText(lpDrawItemStruct->itemID,nColumnIndex,szString,CountArray(szString));

	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//if (m_nItemHeight >0 && nColumnIndex == m_nCustomColumn)
	//{	
	//	CFont boldfont;
	//	LOGFONT lf;          //����һ������ṹ���ʵ������logFont
	//	CSkinResourceManager::GetInstance()->GetDefaultFont().GetLogFont(&lf);
	//	lf.lfUnderline =TRUE;
	//	boldfont.CreateFontIndirect(&lf);
	//	/*pOldFont =*/ pDC->SelectObject(&boldfont);
	//}


	//�滭����
	rcSubItem.left+=5;
	pDC->DrawText(szString,lstrlen(szString),&rcSubItem,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_CENTER);


	return;
}

//��������
//VOID CMatchList::InsertDataItem(VOID * pItemData)
//{
//	//Ч��״̬
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//��������
//	INT nItemInsert=0;
//	INT nColumnCount= 2;//m_SkinHeaderCtrl.GetItemCount();
//
//	//��������
//	for (INT i=0;i<nColumnCount;i++)
//	{
//		//��ȡ����
//		TCHAR szString[256]=TEXT("");
//		//ConstructString(pItemData,i,szString,CountArray(szString));
//
//		//�����б�
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

//��������
//VOID CMatchList::UpdateDataItem(VOID * pItemData)
//{
//	//Ч��״̬
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//��������
//	LVFINDINFO FindInfo;
//	ZeroMemory(&FindInfo,sizeof(FindInfo));
//
//	//���ñ���
//	FindInfo.flags=LVFI_PARAM;
//	FindInfo.lParam=(LPARAM)pItemData;
//
//	//��������
//	INT nItem=FindItem(&FindInfo);
//	INT nColumnCount=2;//m_SkinHeaderCtrl.GetItemCount();
//
//	//��������
//	if (nItem!=-1L)
//	{
//		//��������
//		for (INT i=0;i<nColumnCount;i++)
//		{
//			//��ȡ����
//			TCHAR szString[256]=TEXT("");
//			//ConstructString(pItemData,i,szString,CountArray(szString));
//
//			//�����б�
//			SetItem(nItem,i,LVIF_TEXT,szString,0,0,0,0);
//		}
//
//		//��������
//		RedrawItems(nItem,nItem);
//	}
//
//	return;
//}
//
////ɾ������
//VOID CMatchList::DeleteDataItem(VOID * pItemData)
//{
//	//Ч��״̬
//	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
//	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
//
//	//��������
//	LVFINDINFO FindInfo;
//	ZeroMemory(&FindInfo,sizeof(FindInfo));
//
//	//�������
//	FindInfo.flags=LVFI_PARAM;
//	FindInfo.lParam=(LPARAM)pItemData;
//
//	//ɾ������
//	INT nItem=FindItem(&FindInfo);
//	if (nItem!=-1L) DeleteItem(nItem);
//
//	return;
//}

//�滭����
BOOL CMatchList::OnEraseBkgnd(CDC * pDC)
{
	//��ȡ����
	CWnd * pHeader=GetHeaderCtrl();
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	LOGFONT logFont;          //����һ������ṹ���ʵ������logFont
	CSkinResourceManager::GetInstance()->GetDefaultFont().GetLogFont(&logFont);

	//�����ж�
	if (pHeader->GetSafeHwnd()!=NULL)
	{
		//��ȡλ��
		CRect rcClient;
		GetClientRect(&rcClient);

		//��ȡλ��
		CRect rcHeader;
		pHeader->GetWindowRect(&rcHeader);

		//�滭����
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


//��ȡ֪ͨ
VOID CMatchList::OnGameItemFinish()
{
	//if (!m_bInsertLastRoom)
	//{
	//	//�����Ϸ
	//	InsertLastPlayGame();

	//	//CGameTypeItem                   ItemType;                   
	//	//ItemType.m_GameType.wTypeID=0;
	//	//ItemType.m_GameType.wSortID=100;
	//	//ItemType.m_GameType.wJoinID=0;

	//	//InsertGameListItem("",-1,&ItemType,m_TreeListRoot,90,false);
	//}
	//m_bInsertLastRoom = true;
	////��������
	//POSITION Position=NULL;
	//CServerListData * pServerListData=CServerListData::GetInstance();

	////չ���б�
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

	////չ���б�
	//ExpandListItem(&m_LastServerItem);

	////չ���б�
	////if (m_TreeListRoot!=NULL) 
	////	ExpandListItem(m_TreeListRoot);

	////��֤����
	//EnsureVisible(m_TreeListRoot);

	////��������
	//ASSERT(CMissionList::GetInstance()!=NULL);
	//CMissionList::GetInstance()->UpdateOnLineInfo();
	//SetTimer(IDI_UPDATE_ONLINE,TIME_UPDATE_ONLINE,NULL);

	return;
}

//��ȡ֪ͨ
VOID CMatchList::OnGameKindFinish(WORD wKindID)
{
	//��ȡ����
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//���ʹ���
	//if (pGameKindItem!=NULL)
	//{
	//	//��������
	//	LPCTSTR pszTitle=TEXT("û�п�����Ϸ����");
	//	HTREEITEM hItemAttachUpdate=pGameKindItem->m_hItemAttachUpdate;
	//	HTREEITEM hItemNormalUpdate=pGameKindItem->m_hItemNormalUpdate;

	//	//���±���
	//	if (hItemAttachUpdate!=NULL) SetItemText(hItemAttachUpdate,pszTitle);
	//	if (hItemNormalUpdate!=NULL) SetItemText(hItemNormalUpdate,pszTitle);
	//}

	return;
}

//����֪ͨ
VOID CMatchList::OnGameItemUpdateFinish()
{
	//��������
	//CPlatformFrame::GetInstance()->UpDataAllOnLineCount();

	return;
}

//����֪ͨ
VOID CMatchList::OnGameItemInsert(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//���봦��
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//��Ϸ����
		{
			break;
		}
	case ItemGenre_Kind:	//��Ϸ����
		{
			break;
		}
	case ItemGenre_Node:	//��Ϸ�ڵ�
		{
			break;
		}
	case ItemGenre_Page:	//��������
		{
			break;
		}
	case ItemGenre_Server:	//��Ϸ����
		{
			//if (GetItemCount() <4)
			//{
				//��������
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

//����֪ͨ
VOID CMatchList::OnGameItemUpdate(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//���봦��
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//��Ϸ����
		{
			//��������
			//CGameTypeItem * pGameTypeItem=(CGameTypeItem *)pGameListItem;

			////��������
			//if (pGameTypeItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
			//	ModifyGameListItem(pGameTypeItem->m_hTreeItemAttach,pszTypeName,-1);
			//}

			////��������
			//if (pGameTypeItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
			//	ModifyGameListItem(pGameTypeItem->m_hTreeItemNormal,pszTypeName,-1);
			//}

			break;
		}
	case ItemGenre_Kind:	//��Ϸ����
		{
			//��������
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;

			//��������
			//TCHAR szTitle[64]=TEXT("");
			//UINT uNormalImage=GetGameKindImageIndex(pGameKindItem);
			//GetGameKindItemTitle(pGameKindItem,szTitle,CountArray(szTitle));

			////��������
			//if (pGameKindItem->m_hTreeItemAttach!=NULL)
			//{
			//	ModifyGameListItem(pGameKindItem->m_hTreeItemAttach,szTitle,-1);
			//}

			////��������
			//if (pGameKindItem->m_hTreeItemNormal!=NULL)
			//{
			//	ModifyGameListItem(pGameKindItem->m_hTreeItemNormal,szTitle,-1);
			//}

			break;
		}
	case ItemGenre_Node:	//��Ϸ�ڵ�
		{
			//��������
			CGameNodeItem * pGameNodeItem=(CGameNodeItem *)pGameListItem;

			////��������
			//if (pGameNodeItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
			//	ModifyGameListItem(pGameNodeItem->m_hTreeItemAttach,pszNodeName,IND_NODE);
			//}

			////��������
			//if (pGameNodeItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
			//	ModifyGameListItem(pGameNodeItem->m_hTreeItemNormal,pszNodeName,IND_NODE);
			//}

			break;
		}
	case ItemGenre_Page:	//��������
		{
			//��������
			CGamePageItem * pGamePageItem=(CGamePageItem *)pGameListItem;

			//��������
			//if (pGamePageItem->m_hTreeItemAttach!=NULL)
			//{
			//	LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
			//	ModifyGameListItem(pGamePageItem->m_hTreeItemAttach,pszDisplayName,IND_BROWSE);
			//}

			////��������
			//if (pGamePageItem->m_hTreeItemNormal!=NULL)
			//{
			//	LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
			//	ModifyGameListItem(pGamePageItem->m_hTreeItemNormal,pszDisplayName,IND_BROWSE);
			//}

			break;
		}
	case ItemGenre_Server:	//��Ϸ����
		{
			//��������
			CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;

			//��������
			TCHAR szTitle[64]=TEXT("");
			UINT uImageIndex=-1 ; //GetGameServerImageIndex(pGameServerItem);
			//GetGameServerItemTitle(pGameServerItem,szTitle,CountArray(szTitle));

			//��������
			//if (pGameServerItem->m_hTreeItemAttach!=NULL)
			//{
			//	ModifyGameListItem(pGameServerItem->m_hTreeItemAttach,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			//}

			////��������
			//if (pGameServerItem->m_hTreeItemNormal!=NULL)
			//{
			//	ModifyGameListItem(pGameServerItem->m_hTreeItemNormal,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			//}

			//�������
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

//ɾ��֪ͨ
VOID CMatchList::OnGameItemDelete(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//ɾ������
	//if (pGameListItem->m_hTreeItemAttach!=NULL) DeleteItem(pGameListItem->m_hTreeItemAttach);
	//if (pGameListItem->m_hTreeItemNormal!=NULL) DeleteItem(pGameListItem->m_hTreeItemNormal);

	//ɾ������
	//if(pGameListItem->GetItemGenre() == ItemGenre_Server)
	//{
	//	HTREEITEM hTreeitem=EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal,((CGameServerItem *)pGameListItem)->m_GameServer.wServerID);
	//	if(hTreeitem!=NULL) DeleteItem(hTreeitem);
	//}

	return;
}

void CMatchList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POSITION pos = GetFirstSelectedItemPosition();
	if(pos!=NULL)
	{
		while(pos)
		{
			int Item = GetNextSelectedItem(pos);
			int nServerID= GetItemData(Item);
			//
			//��ȡ����
			CServerListData * pServerListData=CServerListData::GetInstance();
			CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
			if (pGameServerItem!=NULL)
			{
				//���뷿��
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
		//��ȡ����
		CServerListData * pServerListData=CServerListData::GetInstance();
		CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
		if (pGameServerItem!=NULL)
		{
			//���뷿��
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString str;
//	str.Format(_T("OnItemchangedListCtrl.  Item index: %d"), pNMLV->iItem);
//
//	int nServerID= GetItemData(pNMLV->iItem);
//	//��ȡ����
//	CServerListData * pServerListData=CServerListData::GetInstance();
//	CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(nServerID);
//	if (pGameServerItem!=NULL)
//	{
//		//���뷿��
//		CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
//		pPlatformFrame->EntranceServerItem(pGameServerItem);
//		return;
//	}
//	*pResult = 0;
//}
