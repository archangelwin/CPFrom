#include "StdAfx.h"
#include "GlobalUnits.h"
#include "PlatformFrame.h"
#include "PlatformEvent.h"
#include "ServerListView.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
#define ITEM_SIZE			 		18									//����߶�
#define ITEM_HEIGHT					1									//����߶�

#define ITEM_TYPE_HEIGHT			29									//����߶�
#define ITEM_KIND_HEIGHT			27									//����߶�
#define ITEM_ROOM_HEIGHT			21									//����߶�
#define ITEM_LAST_HEIGHT			80									//����߶�

//////////////////////////////////////////////////////////////////////////////////

//ʱ�䶨��
#define IDI_UPDATE_ONLINE			100									//��������
#define TIME_UPDATE_ONLINE			30000								//��������

//////////////////////////////////////////////////////////////////////////////////

//ͼ������
#define IND_ROOT					0									//�б���
#define IND_TYPE					1									//��Ϸ����
#define IND_NODE					2									//��Ϸ�ڵ�
#define IND_KIND_NODOWN				3									//��û����
#define IND_KIND_UNKNOW				4									//δ֪����
#define IND_SERVER_UPDATE			5									//�ղط���
#define IND_SERVER_ATTACH			6									//�ղط���
#define IND_SERVER_NORMAL			7									//��������
#define IND_SERVER_ENTRANCE			8									//��ǰʹ��
#define IND_SERVER_EVERENTRANCE		9									//��������
#define IND_BROWSE					10									//�������
#define IND_FUNCTION				11									//��������

//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CServerListView, CTreeCtrl)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CLICK, OnNMLClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnTvnItemexpanding)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CServerListView::CServerListView()
{
	//���ñ���
	m_nXScroll=0;
	m_nYScroll=0;
	m_bInsertLastRoom= false;
	for(int i=0;i<SHOW_LAST_COUNT;i++)
	{
		m_pLastGameServerItem[i] = NULL;
	}

	//�б���
	m_TreeListRoot=NULL;
	m_TreeAssistant=NULL;

	//��������
	m_hItemMouseHover=NULL;
	m_hTreeClickExpand=NULL;

	//�ں˱���
	m_GameImageMap.InitHashTable(PRIME_KIND);

	//������Դ
	m_ImageArrow.LoadImage(AfxGetInstanceHandle(),TEXT("SERVER_LIST_ARROW"));
	m_ImageArrowType.LoadImage(AfxGetInstanceHandle(),TEXT("SERVER_TYPE_ARROW"));

	//��������
	m_FontBold.CreateFont(-12,0,0,0,600,0,0,0,134,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));
	m_FontGameKind.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));
	m_FontGameServer.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));

	//���ñ���
	m_LastServerItem.m_GameType.wTypeID=0;
	m_LastServerItem.m_GameType.wTypeID=0;
	m_LastServerItem.m_GameType.wSortID=0;
	m_LastServerItem.m_GameType.wJoinID=0;
	_sntprintf(m_LastServerItem.m_GameType.szTypeName, CountArray(m_LastServerItem.m_GameType.szTypeName), TEXT("�����Ϸ"));
	//nBB = 0;

	return;
}

//��������
CServerListView::~CServerListView()
{
	m_FontBold.DeleteObject();
	m_FontGameKind.DeleteObject();
	m_FontGameServer.DeleteObject();
	//�����¼
	SaveLastPlayGame();
}

//�����
BOOL CServerListView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	/*UINT nCommandID=LOWORD(wParam);

	//�˵�����
	switch (nCommandID)
	{
	case IDM_ENTER_SERVER:		//���뷿��
		{
			//��ȡ����
			HTREEITEM hTreeItem=GetSelectedItem();

			//ѡ���ж�
			if (hTreeItem==NULL) return TRUE;

			//��ȡ����
			CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);

			//�����
			if (pGameListItem!=NULL)
			{
				switch (pGameListItem->GetItemGenre())
				{
				case ItemGenre_Kind:	//��Ϸ����
					{
						//���뷿��
						CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
						pPlatformFrame->EntranceServerItem((CGameKindItem *)pGameListItem);

						break;
					}
				case ItemGenre_Server:	//��Ϸ����
					{
						//���뷿��
						CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
						pPlatformFrame->EntranceServerItem((CGameServerItem *)pGameListItem);

						break;
					}
				}
			}

			return TRUE;
		}
	case IDM_SHRINK_LIST:		//�����б�
		{
			//�����б�
			HTREEITEM hCurrentItem=GetSelectedItem();
			if (hCurrentItem!=NULL)	Expand(hCurrentItem,TVE_COLLAPSE);

			return TRUE;
		}
	case IDM_EXPAND_LIST:		//չ���б�
		{
			//չ���б�
			HTREEITEM hCurrentItem=GetSelectedItem();
			if (hCurrentItem!=NULL)	Expand(hCurrentItem,TVE_EXPAND);

			return TRUE;
		}
	}*/

	return __super::OnCommand(wParam,lParam);
}

//���ں���
LRESULT CServerListView::DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	//˫����Ϣ
	switch (uMessage)
	{
	//case WM_MOUSEWHEEL:
	//	{
	//		CPoint MousePoint;
	//		MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));
	//		if (m_rcLastRoom[0].PtInRect(MousePoint) || m_rcLastRoom[1].PtInRect(MousePoint) || m_rcLastRoom[2].PtInRect(MousePoint))
	//		{
	//			return true;
	//		}

	//	}
	//case WM_MOUSEMOVE:
	//	{
	//		CPoint MousePoint;
	//		MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));
	//		if (m_rcLastRoom[0].PtInRect(MousePoint) || m_rcLastRoom[1].PtInRect(MousePoint) || m_rcLastRoom[2].PtInRect(MousePoint))
	//		{
	//			return true;
	//		}
	//	}

	case WM_LBUTTONDOWN:		//�����Ϣ
		{
			//�������
			CPoint MousePoint;
			MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));

			//���ñ���
			m_hTreeClickExpand=NULL;

			//�������
			HTREEITEM hTreeItem=HitTest(MousePoint);
			///////////////////////////�����Ϸ����///////////////////////////////////////////////
			HTREEITEM hItemRoot = GetRootItem( );
			if (hTreeItem!=NULL)
			{
				if (hTreeItem == hItemRoot)
					return 0;
				if (GetParentItem(hTreeItem) == hItemRoot)
				{
					if (m_rcLastRoom[0].PtInRect(MousePoint))
					{
						if (m_pLastGameServerItem[0]!=NULL)
						{
							//���뷿��
							CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
							pPlatformFrame->EntranceServerItem(m_pLastGameServerItem[0]);
							return 0;
						}
					}
					else if (m_rcLastRoom[1].PtInRect(MousePoint))
					{
						if (m_pLastGameServerItem[1]!=NULL)
						{
							//���뷿��
							CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
							pPlatformFrame->EntranceServerItem(m_pLastGameServerItem[1]);
							return 0;
						}
					}
					else  if (m_rcLastRoom[2].PtInRect(MousePoint))
					{
						if (m_pLastGameServerItem[2]!=NULL)
						{
							//���뷿��
							CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
							pPlatformFrame->EntranceServerItem(m_pLastGameServerItem[2]);
							return 0;
						}
					}
					return 0;
				}
			}
			//////////////////////////////////////////////////////////////////////////


			//��Ϣ����
			if ((hTreeItem!=NULL)&&(GetChildItem(hTreeItem)!=NULL))
			{
				//��ȡ����
				CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);
				CGameListItem * pGameListItemChild=(CGameListItem *)GetItemData(GetChildItem(hTreeItem));
				if (pGameListItemChild == NULL)
				{
					return 0;
				}

				//ѡ������
				SetFocus();
				Select(hTreeItem,TVGN_CARET);

				//��ȡλ��
				CRect rcTreeItem;
				GetItemRect(hTreeItem,&rcTreeItem,TRUE);

				CRect rcClient;
				GetClientRect(&rcClient);

				rcTreeItem.left = rcClient.left+2;
				rcTreeItem.right = rcClient.right-2;

				//��Ϣ����
				if (rcTreeItem.PtInRect(MousePoint)==TRUE)
				{
					m_hTreeClickExpand=hTreeItem;
					//չ���б�
					if (ExpandVerdict(hTreeItem)==false)
					{
						ExpandTreeItem(m_hTreeClickExpand);
						//Expand(m_hTreeClickExpand,TVE_EXPAND);
					}
					else
					{	
						Expand(m_hTreeClickExpand,TVE_COLLAPSE);
					}
					//////////////////////////////////////////////////////////////////////////
					//return __super::DefWindowProc(uMessage,wParam,lParam);
					//////////////////////////////////////////////////////////////////////////

					return 0;
				}
			}

			break;
		}
	case WM_LBUTTONDBLCLK:		//�����Ϣ
		{
			//�������
			CPoint MousePoint;
			MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));

			//�������
			HTREEITEM hTreeItem=HitTest(MousePoint);	
			HTREEITEM hItemRoot = GetRootItem( );

			//�����ж�
			if (hTreeItem!=NULL)
			{
				if (hTreeItem == hItemRoot)
					return 0;
				//��ȡ����
				CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);
				if ((pGameListItem!=NULL)&&(pGameListItem->GetItemGenre()==ItemGenre_Kind))
				{
					//��������
					CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;

					//�����ж�
					if (pGameKindItem->m_dwProcessVersion==0L)
					{
						//��ȡ�汾
						tagGameKind * pGameKind=&pGameKindItem->m_GameKind;
						CWHService::GetModuleVersion(pGameKind->szProcessName,pGameKindItem->m_dwProcessVersion);

						//�����ж�
						if (pGameKindItem->m_dwProcessVersion==0L)
						{
							CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
							pGlobalUnits->DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,0,pGameKind->szProcessName);
						}
						else
						{
							OnGameItemUpdate(pGameKindItem);
						}
					}
				}
			}

			//��Ϣ����
			if ((hTreeItem!=NULL)&&(GetChildItem(hTreeItem)!=NULL))
			{
				//��ȡ����
				CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);
				CGameListItem * pGameListItemChild=(CGameListItem *)GetItemData(GetChildItem(hTreeItem));
				if (pGameListItemChild == NULL)
				{
					return 0;
				}
				//ѡ������
				SetFocus();
				Select(hTreeItem,TVGN_CARET);

				//λ���ж�
				CRect rcTreeItem;
				GetItemRect(hTreeItem,&rcTreeItem,TRUE);
				if (rcTreeItem.PtInRect(MousePoint)==FALSE) break;

				//չ���ж�
				if ((m_hTreeClickExpand!=hTreeItem)&&(ExpandVerdict(hTreeItem)==true))
				{
					//���ñ���
					m_hTreeClickExpand=NULL;

					//չ���б�
					Expand(hTreeItem,TVE_COLLAPSE);
				}

				return 0;
			}

			break;
		}
	}

	return __super::DefWindowProc(uMessage,wParam,lParam);
}

//����ͨ��
VOID CServerListView::InitAssistantItem()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szAssistantPath[MAX_PATH]=TEXT("");
	_sntprintf(szAssistantPath,CountArray(szAssistantPath),TEXT("%s\\Collocate\\Collocate.INI"),szDirectory);

	//��ȡ����
	TCHAR szAssistant[512]=TEXT("");
	GetPrivateProfileString(TEXT("Assistant"),TEXT("AssistantName"),TEXT(""),szAssistant,CountArray(szAssistant),szAssistantPath);

	//��������
	if (szAssistant[0]!=0)
	{
		//��������
		DWORD dwInsideID=1;

		//��������
		UINT nMask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM|TVIF_STATE;
		m_TreeAssistant=InsertItem(nMask,szAssistant,IND_FUNCTION,IND_FUNCTION,TVIS_BOLD,TVIS_BOLD,NULL,NULL,TVI_LAST);

		//��������
		do
		{
			//�������
			TCHAR szItemName[16]=TEXT("");
			_sntprintf(szItemName,CountArray(szItemName),TEXT("Assistant%ld"),dwInsideID);

			//��ȡ����
			TCHAR szAssistantName[128]=TEXT("");
			GetPrivateProfileString(szItemName,TEXT("AssistantName"),TEXT(""),szAssistantName,CountArray(szAssistantName),szAssistantPath);

			//����ж�
			if (szAssistantName[0]==0) break;

			//��������
			InsertInsideItem(szAssistantName,IND_BROWSE,dwInsideID++,m_TreeAssistant);

		} while (true);

		//չ���б�
		ExpandListItem(m_TreeAssistant);
	}

	return;
}

//���ú���
VOID CServerListView::InitServerTreeView()
{
	//��������
	SetItemHeight(ITEM_HEIGHT);
	ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_SHOWSELALWAYS|TVS_TRACKSELECT|TVS_NOSCROLL|TVS_NOHSCROLL|TVS_NONEVENHEIGHT);
	//::ShowScrollBar(this->m_hWnd,SB_BOTH,FALSE);

	//���ر�־
	CBitmap ServerImage,ServersStateImage;
	//ServerImage.LoadBitmap(IDB_SERVER_LIST_IMAGE);
	ServersStateImage.LoadBitmap(IDB_SERVER_STATE_IMAGE);
	//m_ImageList.Create(ITEM_SIZE,ITEM_SIZE,ILC_COLOR16|ILC_MASK,0,0);
	m_ImageList.Create(7,9,ILC_COLOR16|ILC_MASK,0,0);
	//������Դ
	SetImageList(&m_ImageList,LVSIL_NORMAL);
	//m_ImageList.Add(&ServerImage,RGB(255,0,255));
	m_ImageList.Add(&ServersStateImage,RGB(255,0,255));
	//��������
	//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//m_TreeListRoot=InsertInsideItem(pGlobalServer->GetPlatformProduct(1),IND_ROOT,0,TVI_ROOT);
	ResetData();
	//�����¼
	LoadLastPlayGame();

	//����ͨ��
	//InitAssistantItem();

	//���ù���
	m_SkinScrollBar.InitScroolBar(this);
    //ModifyStyle(WS_VSCROLL,0);
	//��������
	SetFont(&CSkinResourceManager::GetInstance()->GetDefaultFont());

	return;
}

void CServerListView::ResetData()
{
	KillTimer(IDI_UPDATE_ONLINE);
	DeleteAllItems();
	//�������
	m_bInsertLastRoom = false;
	HTREEITEM hTreeItemNormal=m_TreeListRoot;
	LPCTSTR pszTypeName=m_LastServerItem.m_GameType.szTypeName;
	m_LastServerItem.m_hTreeItemNormal=InsertGameListItem(pszTypeName,-1,&m_LastServerItem,hTreeItemNormal,ITEM_TYPE_HEIGHT,true);

	//LPCTSTR pszTypeName=m_LastServerItem.m_GameType.szTypeName;
	//m_LastServerItem.m_hTreeItemNormal=InsertGameListItem(pszTypeName,IND_TYPE,&m_LastServerItem,TVI_ROOT);
}

//��ȡѡ��
HTREEITEM CServerListView::GetCurrentSelectItem(bool bOnlyText)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//����ж�
	HTREEITEM hTreeItem=HitTest(MousePoint);

	if (bOnlyText==true)
	{
		//��ȡλ��
		CRect rcTreeItem;
		GetItemRect(hTreeItem,&rcTreeItem,TRUE);

		//ѡ���ж�
		if (rcTreeItem.PtInRect(MousePoint)==FALSE) return NULL;
	}

	return hTreeItem;
}


void CServerListView::InsertLastPlayGame()
{
	return;
	//ɾ������
	HTREEITEM hItemRoot = GetRootItem();
	for(int i=0;i<SHOW_LAST_COUNT;i++)
	{
		HTREEITEM hItemLast = GetChildItem(hItemRoot);
		if (hItemLast!=NULL)
		{
			DeleteItem(hItemLast);
		}
	}
	//���²���
	POSITION Position=m_LastPlayGameList.GetHeadPosition();
	while(Position != NULL)
	{
		POSITION temppos=Position;
		WORD wServerID = m_LastPlayGameList.GetNext(Position);
		CServerListData * pServerListData=CServerListData::GetInstance();
		CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(wServerID);
		//�����ж�
		if(pGameServerItem!=NULL)
		{
			InsertGameListItem(pGameServerItem->m_GameServer.szServerName,-1,pGameServerItem,m_LastServerItem.m_hTreeItemNormal,ITEM_LAST_HEIGHT);	
			break;
		}
	}
}


//��������Ϸ
void CServerListView::AddLastPlayGame(WORD wServerID, CGameServerItem *pGameServerItem)
{
	return;
	//����У��
	if(pGameServerItem==NULL) return;

	//���Ҽ�¼
	POSITION Position=m_LastPlayGameList.GetHeadPosition();
	while(Position != NULL)
	{
		POSITION temppos=Position;
		if(m_LastPlayGameList.GetNext(Position) == wServerID)
		{
			m_LastPlayGameList.RemoveAt(temppos);
			break;
		}
	}

	//��¼��Ϸ
	m_LastPlayGameList.AddHead(wServerID);
	//ɾ������
	if(m_LastPlayGameList.GetCount() > SHOW_LAST_COUNT)
	{
		m_LastPlayGameList.RemoveTail();
	}
	InsertLastPlayGame();
	
/*
	//ɾ������
	HTREEITEM hItemRoot = GetRootItem( );
	for (int)
	{
	}
	{
		HTREEITEM hItemLast = GetChildItem(hItemRoot);
		if (hItemLast!=NULL)
		{
			DeleteItem(hItemLast);
		}
	}

	//���²���


	//ɾ������
	if(m_LastPlayGameList.GetCount() > SHOW_LAST_COUNT)
	{
		//ɾ����¼
		WORD wDeleServerID=m_LastPlayGameList.GetTail();
		m_LastPlayGameList.RemoveTail();

		//ɾ������
		HTREEITEM hDeleParentItem=EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal,wDeleServerID);
		if(hDeleParentItem)
		{
			DeleteItem(hDeleParentItem);
		}
	}

	//���뷿��
	if(EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal,wServerID)==NULL)
	{
		//���봦��
		TCHAR szTitle[64]=TEXT("");
		UINT uImageIndex=GetGameImageIndex(pGameServerItem);
		GetGameItemTitle(pGameServerItem,szTitle,CountArray(szTitle));

		//�������
		InsertGameListItem(szTitle,-1,pGameServerItem,m_LastServerItem.m_hTreeItemNormal,ITEM_LAST_HEIGHT);
		m_bInsertLastRoom = true;

		//չ���б�
		ExpandListItem(&m_LastServerItem);
	}
*/
}

//�ж������Ϸ
bool CServerListView::IsLastPlayGame(WORD wServerID)
{
	//������Ϸ����
	POSITION Position=m_LastPlayGameList.GetHeadPosition();
	while(Position != NULL)
	{
		if(m_LastPlayGameList.GetNext(Position) == wServerID) return true;
	}

	return false;
}

//ö�ټ�¼
HTREEITEM CServerListView::EmunGameServerItem(HTREEITEM hParentItem, WORD wServerID)
{
	ASSERT(hParentItem != NULL);

	HTREEITEM hTreeItem = GetChildItem(hParentItem);

	//ѡ���ж�
	while(hTreeItem)
	{
		//��ȡ����
		CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);

		//�жϼ�¼
		if ((pGameListItem!=NULL)&&(pGameListItem->GetItemGenre()==ItemGenre_Server))
		{
			//
			if(((CGameServerItem *)pGameListItem)->m_GameServer.wServerID == wServerID)
			{
				return hTreeItem;
			}
		}

		//��һ��¼
		hTreeItem = GetNextSiblingItem(hTreeItem);
	}

	return NULL;
}

//����Ϊ��
bool CServerListView::IsEmptySubitem(WORD wKindID)
{
	//��ȡ����
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//�����ж�
	if(pGameKindItem!=NULL)
	{
		if(pGameKindItem->m_hTreeItemNormal!=NULL)
		{
			return (GetChildItem(pGameKindItem->m_hTreeItemNormal)==NULL);
		}
	}

	return false;
}

//չ��״̬
bool CServerListView::ExpandVerdict(HTREEITEM hTreeItem)
{
	if (hTreeItem!=NULL)
	{
		UINT uState=GetItemState(hTreeItem,TVIS_EXPANDED);
		return ((uState&TVIS_EXPANDED)!=0);
	}

	return false;
}

VOID CServerListView::ExpandTreeItem(HTREEITEM hTreeItem)
{
	HTREEITEM hItemFirstType = GetNextItem(GetRootItem(),TVGN_NEXT);
	//չ���б�
	HTREEITEM hCurrentItem=hTreeItem;
	HTREEITEM hParentItem = GetParentItem(hCurrentItem);
	do
	{
		if (hParentItem == NULL) //�����ֵܽڵ�
		{
			HTREEITEM hBrotherItem = GetNextItem(GetRootItem(),TVGN_NEXT);
			do 
			{
				if (hBrotherItem == hCurrentItem)
				{
					//Expand(hBrotherItem,TVE_EXPAND);
				}
				else
				{
					Expand(hBrotherItem,TVE_COLLAPSE);
				}
				hBrotherItem = GetNextItem(hBrotherItem,TVGN_NEXT);
			} while (hBrotherItem!=NULL);
		}
		else//�и��ڵ㣬�����ֵܽڵ�
		{
			HTREEITEM hBrotherItem = GetChildItem(hParentItem);
			do
			{
				if (hBrotherItem == hCurrentItem)
				{
					//Expand(hBrotherItem,TVE_EXPAND);
				}
				else
				{
					Expand(hBrotherItem,TVE_COLLAPSE);
				}
				hBrotherItem = GetNextItem(hBrotherItem,TVGN_NEXT);
			}while(hBrotherItem!=NULL);
		}
		hCurrentItem = hParentItem;
		hParentItem = GetParentItem(hCurrentItem);
	} while (hCurrentItem!=NULL);

	Expand(hTreeItem,TVE_EXPAND);
}

//չ���б�
bool CServerListView::ExpandListItem(HTREEITEM hTreeItem)
{
	//Ч�����
	ASSERT(hTreeItem!=NULL);
	if (hTreeItem==NULL)
		return false;

	//չ���б�
	HTREEITEM hCurrentItem=hTreeItem;
	do
	{
		Expand(hCurrentItem,TVE_EXPAND);
		hCurrentItem=GetParentItem(hCurrentItem);
	} while (hCurrentItem!=NULL);

	return true;
}

//չ���б�
bool CServerListView::ExpandListItem(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return false;

	//չ������
	if (pGameListItem->m_hTreeItemAttach!=NULL) 
		ExpandListItem(pGameListItem->m_hTreeItemAttach);
	if (pGameListItem->m_hTreeItemNormal!=NULL) 
		ExpandListItem(pGameListItem->m_hTreeItemNormal);
	
	return true;
}

//�滭����
VOID CServerListView::DrawTreeItem(CDC * pDC, CRect & rcClient, CRect & rcClipBox)
{
	//�����ж�
	HTREEITEM hItemCurrent=GetFirstVisibleItem();
	HTREEITEM hItemRoot = GetRootItem( );

	if (hItemCurrent==NULL) return;

	//��ȡ����
	UINT uTreeStyte=GetWindowLong(m_hWnd,GWL_STYLE);

	//��ȡ����
	ASSERT(CSkinRenderManager::GetInstance()!=NULL);
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();
    int nLastRoomPos = 0; //�����Ϸ����
	int nLastRoomTop = 0;
	int nInter = (rcClient.Width()-12*2)/3;
	//CString sMsg;
	//sMsg.Format("%s,%d  ,%d",pszTitle,nIntegral,nAA);
	//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//CLog ListLog;
	//ListLog.Init(pGlobalServer->GetAppPath() +"\\List1.txt");
	//ListLog.WriteMsg(sMsg+"</br>");
	//int kk = 0;
	//int nAA = 0;
	//�滭����
	do
	{
		//nAA++;
		//��������
		CRect rcItem;
		CRect rcRect;

		//��ȡ״̬
		HTREEITEM hParent=GetParentItem(hItemCurrent);
		UINT uItemState=GetItemState(hItemCurrent,TVIF_STATE);

		//��ȡ����
		bool bDrawChildren=(ItemHasChildren(hItemCurrent)==TRUE);
		bool bDrawSelected=(uItemState&TVIS_SELECTED)&&((this==GetFocus())||(uTreeStyte&TVS_SHOWSELALWAYS));
	
		//��ȡ����
		if (GetItemRect(hItemCurrent,rcItem,TRUE))
		{
			//�滭����
			if (rcItem.top>=rcClient.bottom) break;
			if (rcItem.top>=rcClipBox.bottom) continue;

			//��ȡ����
			CGameListItem * pGameListTemp=(CGameListItem *)GetItemData(hItemCurrent);
			CString str = GetItemText(hItemCurrent);

			//kk +=1;
			//CString sMsg;
			//sMsg.Format("%d             %s   ,%d  ,%d",nAA,str,rcItem.Height(),kk);
			//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			//CLog ListLog;
			//ListLog.Init(pGlobalServer->GetAppPath() +"\\List.txt");
			//ListLog.WriteMsg(sMsg);

			if ((pGameListTemp!=NULL)&&(pGameListTemp->GetItemGenre()==ItemGenre_Server)) //��Ϸ����
			{
				CGameServerItem *pCurrentServerItem = (CGameServerItem *)pGameListTemp;
				if (pCurrentServerItem == NULL)
				{
					continue;
				}
				if(hParent == hItemRoot)
				{
					//if(nLastRoomPos >= SHOW_LAST_COUNT)
					//	return;		
					POSITION Position=m_LastPlayGameList.GetHeadPosition();
					while(Position != NULL)
					{
						POSITION temppos=Position;
						WORD wServerID = m_LastPlayGameList.GetNext(Position);
						CServerListData * pServerListData=CServerListData::GetInstance();
						CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(wServerID);
						//�����ж�
						if(pGameServerItem!=NULL)
						{
							CPngImageSB m_ImageRoomItem;
							CGlobalServer * pGlobalServer=CGlobalServer::GetInstance(); 
							CString sPngPath;
							sPngPath.Format("%s%s%d.png",pGlobalServer->GetAppPath(),"\\GameKind\\",pGameServerItem->m_GameServer.wKindID);
							m_ImageRoomItem.LoadImage(sPngPath);

							if (m_ImageRoomItem.IsNull())
							{
								sPngPath.Format("%s%s0.png",pGlobalServer->GetAppPath(),"\\GameKind\\");
								m_ImageRoomItem.LoadImage(sPngPath);
							}	
							nLastRoomTop = rcItem.top + 4;
							m_rcLastRoom[nLastRoomPos].left = 12+nLastRoomPos*nInter;
							m_rcLastRoom[nLastRoomPos].right = m_rcLastRoom[nLastRoomPos].left + m_ImageRoomItem.GetWidth();
							m_rcLastRoom[nLastRoomPos].top = nLastRoomTop;
							m_rcLastRoom[nLastRoomPos].bottom = nLastRoomTop+m_ImageRoomItem.GetHeight();
							m_ImageRoomItem.DrawImage(pDC,12+m_rcLastRoom[nLastRoomPos].left,m_rcLastRoom[nLastRoomPos].top);

							//��������
							pDC->SelectObject(m_FontGameServer);
							CRect rcText(m_rcLastRoom[nLastRoomPos].left,m_rcLastRoom[nLastRoomPos].bottom+1,m_rcLastRoom[nLastRoomPos].right,m_rcLastRoom[nLastRoomPos].bottom+13);		
							
							pDC->DrawText(pGameServerItem->m_GameServer.szGameLevel,&rcText,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);	
							m_pLastGameServerItem[nLastRoomPos] =  pGameServerItem;
							nLastRoomPos++;

						}
					}
			
					//if (nLastRoomPos == 0)
					//{
					//}			
					//continue;
				}
				else
				{
					rcRect.left=0;
					rcRect.top=rcItem.top+1;
					rcRect.bottom=rcItem.bottom;
					rcRect.right=rcClient.Width();
					//�滭����
					if (/*(bDrawSelected==false)&&*/(m_hItemMouseHover==hItemCurrent))
					{
						//pDC->FillSolidRect(&rcRect,pSkinRenderManager->RenderColor(0.36,1.00));
						pDC->FillSolidRect(&rcRect,RGB(204,224,237));
					}
					else
					{
						pDC->FillSolidRect(&rcRect,RGB(236,243,249));
					}
					if (str == "")
					{
						continue;
					}

					//��ȡ����
					INT nImage,nSelectedImage;
					GetItemImage(hItemCurrent,nImage,nSelectedImage);
					//��ȡ��Ϣ
					IMAGEINFO ImageInfo;
					m_ImageList.GetImageInfo(nImage,&ImageInfo);

					//�滭ͼ��
					INT nImageWidth=ImageInfo.rcImage.right-ImageInfo.rcImage.left;
					INT nImageHeight=ImageInfo.rcImage.bottom-ImageInfo.rcImage.top;
					m_ImageList.Draw(pDC,nImage,CPoint(rcRect.left+15,rcRect.top+5),ILD_TRANSPARENT);

					//CPngImageSB ImageUnBin;
					//ImageUnBin.LoadImage(AfxGetInstanceHandle(),TEXT("BT_UNBUNDING"));
					//ImageUnBin.DrawImage(pDC,rcRect.left+65,rcRect.top+5);

					//��������
					pDC->SelectObject(m_FontGameServer);
					//���û���
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(RGB(21,81,115));
					CRect rcTmp(rcRect.TopLeft(),rcRect.BottomRight());
					rcTmp.left +=27;
					rcTmp.right = rcTmp.left+55;
					//�����ı�
					pDC->DrawText(pCurrentServerItem->m_GameServer.szGameLevel,rcTmp,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

					rcTmp.right = rcRect.right-15;
					rcTmp.left = rcTmp.right-85;
					pDC->DrawText(pCurrentServerItem->m_GameServer.szDescription,rcTmp,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

					rcTmp.left =rcRect.left + 105;
					rcTmp.right = rcTmp.left + 30;
					TCHAR szLoadInfo[32] = {0};
					GetLoadInfoOfServer(&pCurrentServerItem->m_GameServer,szLoadInfo,CountArray(szLoadInfo));

					if(_tcscmp(szLoadInfo,_T("��")) == 0)
						pDC->SetTextColor(RGB(117,199,0));
					else if(_tcscmp(szLoadInfo,_T("��")) == 0)
						pDC->SetTextColor(RGB(16,185,240));
					else if(_tcscmp(szLoadInfo,_T("æ")) == 0)
						pDC->SetTextColor(RGB(243,140,1));
					else if(_tcscmp(szLoadInfo,_T("��")) == 0)
						pDC->SetTextColor(RGB(167,30,224));
					else if(_tcscmp(szLoadInfo,_T("��")) == 0)
						pDC->SetTextColor(RGB(255,47,47));

					pDC->DrawText(szLoadInfo,rcTmp,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
					//DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);
				}
			}
			else if ((pGameListTemp!=NULL)&&(pGameListTemp->GetItemGenre()==ItemGenre_Kind)) //��Ϸ����
			{
				CGameKindItem *pCurrentKindItem = (CGameKindItem *)pGameListTemp;
				CPngImageSB m_ImgTypeBG,m_ImageKindItem;
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance(); 
				CString sPngPath = pGlobalServer->GetAppPath() + "\\GameKind\\GAMEKIND.png";
				m_ImgTypeBG.LoadImage(sPngPath);
				INT nIndex=(uItemState&TVIS_EXPANDED)?0L:1L;
				INT nSelect=(bDrawSelected==true)?1:0;
				nSelect=(m_hItemMouseHover==hItemCurrent)?3:0;
				nSelect = 0;// seaplums

				INT nXPos=rcItem.left-m_ImageArrow.GetWidth()/2-28;
				INT nYPos=rcItem.top+(rcItem.Height()-m_ImageArrow.GetHeight())/2;

			    sPngPath.Format("%s%ss_%d.png",pGlobalServer->GetAppPath(),"\\GameKind\\",pCurrentKindItem->m_GameKind.wKindID);
				m_ImageKindItem.LoadImage(sPngPath);
				if (m_ImageKindItem.IsNull())
				{
					sPngPath.Format("%s%ss_0.png",pGlobalServer->GetAppPath(),"\\GameKind\\");
					m_ImageKindItem.LoadImage(sPngPath);
				}
				
				m_ImgTypeBG.DrawImage(pDC,2,rcItem.top+1,m_ImgTypeBG.GetWidth()/2,m_ImgTypeBG.GetHeight(),nSelect*m_ImgTypeBG.GetWidth()/2,0);	
				m_ImageArrow.DrawImage(pDC,4,nYPos,m_ImageArrow.GetWidth()/2,m_ImageArrow.GetHeight(),nIndex*m_ImageArrow.GetWidth()/2,0);				
				m_ImageKindItem.DrawImage(pDC,2+m_ImageArrow.GetWidth()/2+5,rcItem.top+1);

				CServerListData * pServerListData=CServerListData::GetInstance();
				CGameKindInfo *pGameKindInfo = pServerListData->SearchGameKindInfo(pCurrentKindItem->m_GameKind.wKindID);
				if (pGameKindInfo!=NULL)
				{
					if (pGameKindInfo->sKindTypePath!="")
					{
						CPngImageSB m_ImgHot;
						sPngPath = pGlobalServer->GetAppPath() + "\\GameKind\\" +pGameKindInfo->sKindTypePath ;
						m_ImgHot.LoadImage(sPngPath);
						m_ImgHot.DrawImage(pDC,rcItem.right+25,rcItem.top);

					}
					if (pGameKindInfo->sStarLevelPath!="")
					{
						CPngImageSB m_ImageStar;
						sPngPath = pGlobalServer->GetAppPath() + "\\GameKind\\" +pGameKindInfo->sStarLevelPath ;
						m_ImageStar.LoadImage(sPngPath);
						int nPngWidth = m_ImageStar.GetWidth();
						m_ImageStar.DrawImage(pDC,rcClient.Width()-nPngWidth-10,rcItem.top+7);
						//m_ImageStar.DrawImage(pDC,rcItem.right+25+80,rcItem.top+7);
					}
				}
				//�����ı�
				DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);

			}
			else if ((pGameListTemp!=NULL)&&(pGameListTemp->GetItemGenre()==ItemGenre_Type)) //��Ϸ������š��ȣ�
			{
				CGameTypeItem *pCurrentTypeItem = (CGameTypeItem *)pGameListTemp;

				CPngImageSB m_ImgGameType,m_ImgType;
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance(); 
				CString sPngPath = pGlobalServer->GetAppPath() + "\\GameKind\\TYPE.png";
				m_ImgGameType.LoadImage(sPngPath);

				sPngPath.Format("%s\\GameKind\\TYPE%d.png",pGlobalServer->GetAppPath(),pCurrentTypeItem->m_GameType.wTypeID);
				m_ImgType.LoadImage(sPngPath);
				INT nIndex=(uItemState&TVIS_EXPANDED)?0L:1L;
				INT nSelect=(bDrawSelected==true)?1:0;
                nSelect=(m_hItemMouseHover==hItemCurrent)?3:0;
				if(hItemCurrent == hItemRoot)
				{
					//INT nXPos=rcItem.left-m_ImageArrowType.GetWidth()/2-5;
					//INT nYPos=rcItem.top+1+(rcItem.Height()-m_ImageArrowType.GetHeight())/2;

					//m_ImgGameType.DrawImage(pDC,2,rcItem.top+1,m_ImgGameType.GetWidth()/4,m_ImgGameType.GetHeight(),nSelect*m_ImgGameType.GetWidth()/4-0,0);
					////�滭ͼ��
					//m_ImageArrowType.DrawImage(pDC,4,nYPos,m_ImageArrowType.GetWidth()/2,m_ImageArrowType.GetHeight(),nIndex*m_ImageArrowType.GetWidth()/2,0);

					////�����ı�
					//DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);
				}
				else if (str == "")
				{
					continue;
				}
				else
				{
					INT nXPos=rcItem.left-m_ImageArrowType.GetWidth()/2-5;
					INT nYPos=rcItem.top+1+(rcItem.Height()-m_ImageArrowType.GetHeight())/2;
					//�滭ͼ��
					m_ImgGameType.DrawImage(pDC,1,rcItem.top,m_ImgGameType.GetWidth()/4,m_ImgGameType.GetHeight(),nSelect*m_ImgGameType.GetWidth()/4,0);	
					m_ImageArrowType.DrawImage(pDC,4,nYPos,m_ImageArrowType.GetWidth()/2,m_ImageArrowType.GetHeight(),nIndex*m_ImageArrowType.GetWidth()/2,0);
					if(!m_ImgType.IsNull())
						m_ImgType.DrawImage(pDC,20,rcItem.top+4/*,m_ImgType.GetWidth(),m_ImageArrowType.GetHeight(),nIndex*m_ImageArrowType.GetWidth()/2,0*/);
					//�����ı�
					DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);		
				}
			}
			//����λ��
			//rcRect.left=0;
			//rcRect.top=rcItem.top+1;
			//rcRect.bottom=rcItem.bottom;
			//rcRect.right=rcClient.Width();

			////�滭ѡ��
			//if (bDrawSelected==true)
			//{
			//	pDC->FillSolidRect(&rcRect,RGB(253,231,161));
			//}

			////�滭����
			//if ((bDrawSelected==false)&&(m_hItemMouseHover==hItemCurrent))
			//{
			//	pDC->FillSolidRect(&rcRect,pSkinRenderManager->RenderColor(0.36,1.00));
			//}

			//if(hParent==NULL)
			//{
			//	//����λ��
			//	INT nXPos=rcItem.left-m_ImageArrowType.GetWidth()/2-25;
			//	INT nYPos=rcItem.top+1+(rcItem.Height()-m_ImageArrowType.GetHeight())/2;

			//	if (hItemCurrent != hItemRoot)
			//	{
			//		nXPos = 6;
			//	}
			//	//�滭ͼ��
			//	INT nIndex=(uItemState&TVIS_EXPANDED)?1L:0L;
			//	m_ImageArrowType.DrawImage(pDC,nXPos,nYPos,m_ImageArrowType.GetWidth()/2,m_ImageArrowType.GetHeight(),nIndex*m_ImageArrowType.GetWidth()/2,0);
			//}
			////���Ƽ�ͷ
			//else if (bDrawChildren==true)
			//{
			//	//����λ��
			//	INT nXPos=rcItem.left-m_ImageArrow.GetWidth()/2-25;
			//	INT nYPos=rcItem.top+1+(rcItem.Height()-m_ImageArrow.GetHeight())/2;

			//	if (hItemCurrent != hItemRoot)
			//	{
			//		nXPos = 6;
			//	}
			//	//�滭ͼ��
			//	INT nIndex=(uItemState&TVIS_EXPANDED)?1L:0L;
			//	m_ImageArrow.DrawImage(pDC,nXPos,nYPos,m_ImageArrow.GetWidth()/2,m_ImageArrow.GetHeight(),nIndex*m_ImageArrow.GetWidth()/2,0);
			//}

			//�����б�
			//		DrawListImage(pDC,rcItem,hItemCurrent);	
		}
	} while ((hItemCurrent=GetNextVisibleItem(hItemCurrent))!= NULL);

	return;
}

//�滭����
VOID CServerListView::DrawTreeBack(CDC * pDC, CRect & rcClient, CRect & rcClipBox)
{
	//�滭����
	pDC->FillSolidRect(&rcClient,RGB(236,243,249));
	//pDC->FillSolidRect(&rcClient,RGB(255,255,255));

	return;
	//���ƺ���
	for (INT nYPos=m_nYScroll/ITEM_HEIGHT*ITEM_HEIGHT;nYPos<rcClient.Height();nYPos+=ITEM_HEIGHT)
	{
		pDC->FillSolidRect(0,nYPos,rcClient.Width(),1,RGB(223,223,223));
	}

	return;
}

//�滭ͼ��
VOID CServerListView::DrawListImage(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem)
{
	//��ȡ����
	INT nImage,nSelectedImage;
	GetItemImage(hTreeItem,nImage,nSelectedImage);

	//��ȡ��Ϣ
	IMAGEINFO ImageInfo;
	m_ImageList.GetImageInfo(nImage,&ImageInfo);

	//�滭ͼ��
	INT nImageWidth=ImageInfo.rcImage.right-ImageInfo.rcImage.left;
	INT nImageHeight=ImageInfo.rcImage.bottom-ImageInfo.rcImage.top;
	m_ImageList.Draw(pDC,nImage,CPoint(rcRect.left-nImageWidth-3,rcRect.top+(rcRect.Height()-nImageHeight)/2+1),ILD_TRANSPARENT);

	return;
}

//�����ı�
VOID CServerListView::DrawItemString(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected)
{
	//��������
	COLORREF crString=RGB(150,150,150);
	CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);

	//��ɫ����
	if (pGameListItem!=NULL)
	{
		//ѡ������
		switch (pGameListItem->GetItemGenre())
		{
		case ItemGenre_Type:		//��Ϸ����
			{
				//������ɫ
				crString=RGB(21,81,115);
				rcRect.left = rcRect.left + 15+20;
				rcRect.right = rcRect.right + 20+20;

				//��������
				pDC->SelectObject(m_FontBold);

				break;
			}
		case ItemGenre_Inside:		//�ڲ�����
			{
				//������ɫ
				crString=RGB(21,81,115);

				//��������
				CGameInsideItem * pGameInsideItem=(CGameInsideItem *)pGameListItem;
				pDC->SelectObject((pGameInsideItem->m_dwInsideID==0)?m_FontBold:CSkinResourceManager::GetInstance()->GetDefaultFont());

				break;
			}
		case ItemGenre_Kind:  //��Ϸ���
			{
				//������ɫ
				crString=RGB(21,81,115);
				rcRect.left = rcRect.left + 22;
				rcRect.right = rcRect.right + 40;
				//��������
				pDC->SelectObject(m_FontGameServer);
				break;
			}
		case ItemGenre_Server: //��Ϸ����
			{
				//������ɫ
				crString=RGB(21,81,115);
				rcRect.left = rcRect.left -20;
				//��������
				pDC->SelectObject(m_FontGameServer);
				break;
			}
		default:					//��������
			{
				//������ɫ
				crString=RGB(21,81,115);
				//��������
				pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());
			}
		}
	}
	else
	{
		//������ɫ
		crString=RGB(21,81,115);

		//��������
		pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());
	}

	//���û���
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(crString);

	//�滭����
	rcRect.right += 5;
	CString strString=GetItemText(hTreeItem);
	pDC->DrawText(strString,rcRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	return;
}

//��ȡ֪ͨ
VOID CServerListView::OnGameItemFinish()
{
	if (!m_bInsertLastRoom)
	{
		//�����Ϸ
		InsertLastPlayGame();

		//CGameTypeItem                   ItemType;                   
		//ItemType.m_GameType.wTypeID=0;
		//ItemType.m_GameType.wSortID=100;
		//ItemType.m_GameType.wJoinID=0;

		//InsertGameListItem("",-1,&ItemType,m_TreeListRoot,90,false);
	}
	m_bInsertLastRoom = true;
	//��������
	POSITION Position=NULL;
	CServerListData * pServerListData=CServerListData::GetInstance();

	//չ���б�
	//for (DWORD i=0;i<pServerListData->GetGameTypeCount();i++)
	//{
	//	CGameTypeItem * pGameTypeItem=pServerListData->EmunGameTypeItem(Position);
	//	if (pGameTypeItem!=NULL) 
	//		ExpandListItem(pGameTypeItem);
	//}
	HTREEITEM hItemFirstType = GetNextItem(GetRootItem(),TVGN_NEXT);
	if (hItemFirstType!=NULL)
	{
		ExpandListItem(hItemFirstType);
		//HTREEITEM hItemFirstKind = GetChildItem(hItemFirstType);
		//if (hItemFirstKind!=NULL)
		//{
		//	ExpandListItem(hItemFirstKind);
		//}
	}

	//չ���б�
	ExpandListItem(&m_LastServerItem);

	//չ���б�
	//if (m_TreeListRoot!=NULL) 
	//	ExpandListItem(m_TreeListRoot);

	//��֤����
	EnsureVisible(m_TreeListRoot);

	//��������
	ASSERT(CMissionList::GetInstance()!=NULL);
	CMissionList::GetInstance()->UpdateOnLineInfo();
	//SetTimer(IDI_UPDATE_ONLINE,TIME_UPDATE_ONLINE,NULL);

	return;
}

//��ȡ֪ͨ
VOID CServerListView::OnGameKindFinish(WORD wKindID)
{
	//��ȡ����
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//���ʹ���
	if (pGameKindItem!=NULL)
	{
		//��������
		LPCTSTR pszTitle=TEXT("û�п�����Ϸ����");
		HTREEITEM hItemAttachUpdate=pGameKindItem->m_hItemAttachUpdate;
		HTREEITEM hItemNormalUpdate=pGameKindItem->m_hItemNormalUpdate;

		//���±���
		if (hItemAttachUpdate!=NULL) SetItemText(hItemAttachUpdate,pszTitle);
		if (hItemNormalUpdate!=NULL) SetItemText(hItemNormalUpdate,pszTitle);
	}

	return;
}

//����֪ͨ
VOID CServerListView::OnGameItemUpdateFinish()
{
	//��������
	CPlatformFrame::GetInstance()->UpDataAllOnLineCount();

	return;
}

//����֪ͨ
VOID CServerListView::OnGameItemInsert(CGameListItem * pGameListItem)
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
			CGameTypeItem * pGameTypeItem=(CGameTypeItem *)pGameListItem;
			CGameListItem * pParentListItem=pGameListItem->GetParentListItem();

			//���Զ���
			LPCTSTR pszTypeName=pGameTypeItem->m_GameType.szTypeName;

			//��������
			if (pParentListItem!=NULL)
			{
				//�������
				HTREEITEM hTreeItemNormal=pParentListItem->m_hTreeItemNormal;
				if (hTreeItemNormal!=NULL) 
					pGameTypeItem->m_hTreeItemNormal=InsertGameListItem(pszTypeName,-1,pGameTypeItem,hTreeItemNormal,ITEM_TYPE_HEIGHT);

				//ϲ������
				HTREEITEM hTreeItemAttach=pParentListItem->m_hTreeItemAttach;
				if (hTreeItemAttach!=NULL) 
					pGameTypeItem->m_hTreeItemAttach=InsertGameListItem(pszTypeName,-1,pGameTypeItem,hTreeItemAttach,ITEM_TYPE_HEIGHT);
			}
			else
			{
				//�������
				HTREEITEM hTreeItemNormal=m_TreeListRoot;
				pGameTypeItem->m_hTreeItemNormal=InsertGameListItem(pszTypeName,-1,pGameTypeItem,hTreeItemNormal,ITEM_TYPE_HEIGHT);
			}

			//����״̬
			if (pGameTypeItem->m_hTreeItemNormal!=NULL) SetItemState(pGameTypeItem->m_hTreeItemNormal,TVIS_BOLD,TVIS_BOLD);
			if (pGameTypeItem->m_hTreeItemAttach!=NULL) SetItemState(pGameTypeItem->m_hTreeItemAttach,TVIS_BOLD,TVIS_BOLD);

			break;
		}
	case ItemGenre_Kind:	//��Ϸ����
		{
			//��������
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;
			CGameListItem * pParentListItem=pGameListItem->GetParentListItem();

			//��������
			if (pParentListItem!=NULL)
			{
				//��������
				UINT nUpdateImage=IND_SERVER_UPDATE;
				UINT uNormalImage=GetGameKindImageIndex(pGameKindItem);

				//���봦��
				TCHAR szTitle[64]=TEXT("");
				LPCTSTR pszUpdateName=TEXT("�������ط����б�...");
				GetGameKindItemTitle(pGameKindItem,szTitle,CountArray(szTitle));

				//�������
				if (pParentListItem->m_hTreeItemNormal!=NULL)
				{
					HTREEITEM hTreeItemNormal=pParentListItem->m_hTreeItemNormal;
					pGameKindItem->m_hTreeItemNormal=InsertGameListItem(szTitle,uNormalImage,pGameKindItem,hTreeItemNormal,ITEM_KIND_HEIGHT);
					pGameKindItem->m_hItemNormalUpdate=InsertGameListItem(pszUpdateName,nUpdateImage,NULL,pGameKindItem->m_hTreeItemNormal,ITEM_KIND_HEIGHT);
				}

				//ϲ������
				if (pParentListItem->m_hTreeItemAttach!=NULL)
				{
					HTREEITEM hTreeItemAttach=pParentListItem->m_hTreeItemAttach;
					pGameKindItem->m_hTreeItemAttach=InsertGameListItem(szTitle,uNormalImage,pGameKindItem,hTreeItemAttach,ITEM_KIND_HEIGHT);
					pGameKindItem->m_hItemAttachUpdate=InsertGameListItem(pszUpdateName,nUpdateImage,NULL,pGameKindItem->m_hTreeItemAttach,ITEM_KIND_HEIGHT);
				}
			}

			break;
		}
	case ItemGenre_Node:	//��Ϸ�ڵ�
		{
			//��������
			CGameNodeItem * pGameNodeItem=(CGameNodeItem *)pGameListItem;
			CGameListItem * pParentListItem=pGameListItem->GetParentListItem();

			//��������
			if (pParentListItem!=NULL)
			{
				//��������
				LPCTSTR pszNodeName=pGameNodeItem->m_GameNode.szNodeName;

				//ɾ������
				DeleteUpdateItem(pGameNodeItem->GetParentListItem());

				//�������
				HTREEITEM hTreeItemNormal=pParentListItem->m_hTreeItemNormal;
				if (hTreeItemNormal!=NULL) pGameNodeItem->m_hTreeItemNormal=InsertGameListItem(pszNodeName,IND_NODE,pGameNodeItem,hTreeItemNormal,ITEM_KIND_HEIGHT);

				//ϲ������
				HTREEITEM hTreeItemAttach=pParentListItem->m_hTreeItemAttach;
				if (hTreeItemAttach!=NULL) pGameNodeItem->m_hTreeItemAttach=InsertGameListItem(pszNodeName,IND_NODE,pGameNodeItem,hTreeItemAttach,ITEM_KIND_HEIGHT);
			}

			break;
		}
	case ItemGenre_Page:	//��������
		{
			//��������
			CGameListItem * pParentListItem=pGameListItem->GetParentListItem();
			LPCTSTR pszDisplayName=(((CGamePageItem *)pGameListItem)->m_GamePage.szDisplayName);

			//��������
			if (pParentListItem!=NULL)
			{
				//�������
				HTREEITEM hTreeItemNormal=pParentListItem->m_hTreeItemNormal;
				if (hTreeItemNormal!=NULL) pParentListItem->m_hTreeItemNormal=InsertGameListItem(pszDisplayName,IND_BROWSE,pGameListItem,hTreeItemNormal,ITEM_KIND_HEIGHT);

				//ϲ������
				HTREEITEM hTreeItemAttach=pParentListItem->m_hTreeItemAttach;
				if (hTreeItemAttach!=NULL) pParentListItem->m_hTreeItemAttach=InsertGameListItem(pszDisplayName,IND_BROWSE,pGameListItem,hTreeItemAttach,ITEM_KIND_HEIGHT);
			}
			else
			{
				//�������
				HTREEITEM hTreeItemNormal=m_TreeListRoot;
				pGameListItem->m_hTreeItemNormal=InsertGameListItem(pszDisplayName,IND_BROWSE,pGameListItem,hTreeItemNormal,ITEM_KIND_HEIGHT);
			}

			break;
		}
	case ItemGenre_Server:	//��Ϸ����
		{
			//��������
			CGameListItem * pParentListItem=pGameListItem->GetParentListItem();
			CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;

			//��������
			if (pParentListItem!=NULL)
			{
				//���봦��
				TCHAR szTitle[64]=TEXT("");
				UINT uImageIndex=GetGameServerImageIndex(pGameServerItem);
				//GetGameServerItemTitle(pGameServerItem,szTitle,CountArray(szTitle));

				//ɾ������
				DeleteUpdateItem(pGameServerItem->GetParentListItem());

				//�������
				HTREEITEM hTreeItemNormal=pParentListItem->m_hTreeItemNormal;
				if (hTreeItemNormal!=NULL) 
					pGameServerItem->m_hTreeItemNormal=InsertGameListItem(pGameServerItem->m_GameServer.szServerName,uImageIndex,pGameServerItem,hTreeItemNormal,ITEM_ROOM_HEIGHT);

				//ϲ������
				HTREEITEM hTreeItemAttach=pParentListItem->m_hTreeItemAttach;
				if (hTreeItemAttach!=NULL) pGameServerItem->m_hTreeItemAttach=InsertGameListItem(pGameServerItem->m_GameServer.szServerName,uImageIndex,pGameServerItem,hTreeItemAttach,ITEM_ROOM_HEIGHT);

				//�������
				//if(IsLastPlayGame(pGameServerItem->m_GameServer.wServerID)/* && !m_bInsertLastRoom*/)
				//{
				//	InsertGameListItem(pGameServerItem->m_GameServer.szServerName,uImageIndex,pGameServerItem,m_LastServerItem.m_hTreeItemNormal,ITEM_LAST_HEIGHT);
				//	m_bInsertLastRoom = true;
				//}

				if(m_LastPlayGameList.GetCount() < SHOW_LAST_COUNT)
				{
					//AddLastPlayGame(pGameServerItem->m_GameServer.wServerID, pGameServerItem);
					m_LastPlayGameList.AddTail(pGameServerItem->m_GameServer.wServerID);
				}
				
			}

			break;
		}
	}

	return;
}

//����֪ͨ
VOID CServerListView::OnGameItemUpdate(CGameListItem * pGameListItem)
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
			CGameTypeItem * pGameTypeItem=(CGameTypeItem *)pGameListItem;

			//��������
			if (pGameTypeItem->m_hTreeItemAttach!=NULL)
			{
				LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
				ModifyGameListItem(pGameTypeItem->m_hTreeItemAttach,pszTypeName,-1);
			}

			//��������
			if (pGameTypeItem->m_hTreeItemNormal!=NULL)
			{
				LPCTSTR pszTypeName(pGameTypeItem->m_GameType.szTypeName);
				ModifyGameListItem(pGameTypeItem->m_hTreeItemNormal,pszTypeName,-1);
			}

			break;
		}
	case ItemGenre_Kind:	//��Ϸ����
		{
			//��������
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;

			//��������
			TCHAR szTitle[64]=TEXT("");
			UINT uNormalImage=GetGameKindImageIndex(pGameKindItem);
			GetGameKindItemTitle(pGameKindItem,szTitle,CountArray(szTitle));

			//��������
			if (pGameKindItem->m_hTreeItemAttach!=NULL)
			{
				ModifyGameListItem(pGameKindItem->m_hTreeItemAttach,szTitle,-1);
			}

			//��������
			if (pGameKindItem->m_hTreeItemNormal!=NULL)
			{
				ModifyGameListItem(pGameKindItem->m_hTreeItemNormal,szTitle,-1);
			}

			break;
		}
	case ItemGenre_Node:	//��Ϸ�ڵ�
		{
			//��������
			CGameNodeItem * pGameNodeItem=(CGameNodeItem *)pGameListItem;

			//��������
			if (pGameNodeItem->m_hTreeItemAttach!=NULL)
			{
				LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
				ModifyGameListItem(pGameNodeItem->m_hTreeItemAttach,pszNodeName,IND_NODE);
			}

			//��������
			if (pGameNodeItem->m_hTreeItemNormal!=NULL)
			{
				LPCTSTR pszNodeName(pGameNodeItem->m_GameNode.szNodeName);
				ModifyGameListItem(pGameNodeItem->m_hTreeItemNormal,pszNodeName,IND_NODE);
			}

			break;
		}
	case ItemGenre_Page:	//��������
		{
			//��������
			CGamePageItem * pGamePageItem=(CGamePageItem *)pGameListItem;

			//��������
			if (pGamePageItem->m_hTreeItemAttach!=NULL)
			{
				LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
				ModifyGameListItem(pGamePageItem->m_hTreeItemAttach,pszDisplayName,IND_BROWSE);
			}

			//��������
			if (pGamePageItem->m_hTreeItemNormal!=NULL)
			{
				LPCTSTR pszDisplayName(pGamePageItem->m_GamePage.szDisplayName);
				ModifyGameListItem(pGamePageItem->m_hTreeItemNormal,pszDisplayName,IND_BROWSE);
			}

			break;
		}
	case ItemGenre_Server:	//��Ϸ����
		{
			//��������
			CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;

			//��������
			TCHAR szTitle[64]=TEXT("");
			UINT uImageIndex=GetGameServerImageIndex(pGameServerItem);
			//GetGameServerItemTitle(pGameServerItem,szTitle,CountArray(szTitle));

			//��������
			if (pGameServerItem->m_hTreeItemAttach!=NULL)
			{
				ModifyGameListItem(pGameServerItem->m_hTreeItemAttach,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			}

			//��������
			if (pGameServerItem->m_hTreeItemNormal!=NULL)
			{
				ModifyGameListItem(pGameServerItem->m_hTreeItemNormal,pGameServerItem->m_GameServer.szServerName,uImageIndex);
			}

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
VOID CServerListView::OnGameItemDelete(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//ɾ������
	if (pGameListItem->m_hTreeItemAttach!=NULL) DeleteItem(pGameListItem->m_hTreeItemAttach);
	if (pGameListItem->m_hTreeItemNormal!=NULL) DeleteItem(pGameListItem->m_hTreeItemNormal);

	//ɾ������
	if(pGameListItem->GetItemGenre() == ItemGenre_Server)
	{
		HTREEITEM hTreeitem=EmunGameServerItem(m_LastServerItem.m_hTreeItemNormal,((CGameServerItem *)pGameListItem)->m_GameServer.wServerID);
		if(hTreeitem!=NULL) DeleteItem(hTreeitem);
	}

	return;
}

//��ȡͼ��
UINT CServerListView::GetGameKindImageIndex(CGameKindItem * pGameKindItem)
{
	//��װ�ж�
	if (pGameKindItem->m_dwProcessVersion==0L) return IND_KIND_NODOWN;

	//Ѱ���ִ�
	UINT uImageIndxe=0;
	tagGameKind * pGameKind=&pGameKindItem->m_GameKind;
	if (m_GameImageMap.Lookup(pGameKind->wKindID,uImageIndxe)==TRUE) 
		return uImageIndxe;

	//����ͼ��
	if (pGameKindItem->m_dwProcessVersion!=0L)
	{
		//������Դ
		LPCTSTR strProcessName(pGameKind->szProcessName);
		HINSTANCE hInstance=AfxLoadLibrary(strProcessName);

		//����ͼ��
		CBitmap GameLogo;
		AfxSetResourceHandle(hInstance);
		if (GameLogo.LoadBitmap(TEXT("GAME_LOGO"))) 
			uImageIndxe=m_ImageList.Add(&GameLogo,RGB(255,0,255));
		AfxSetResourceHandle(GetModuleHandle(NULL));

		//�ͷ���Դ
		AfxFreeLibrary(hInstance);

		//������Ϣ
		if (uImageIndxe!=0L)
		{
			m_GameImageMap[pGameKind->wKindID]=uImageIndxe;
			return uImageIndxe;
		}
	}
	
	return IND_KIND_NODOWN;
}

//��ȡͼ��
UINT CServerListView::GetGameServerImageIndex(CGameServerItem * pGameServerItem)
{
	TCHAR szLoadInfo[32] = {0};
	GetLoadInfo(pGameServerItem->m_GameServer.dwOnLineCount, pGameServerItem->m_GameServer.dwFullCount, szLoadInfo, CountArray(szLoadInfo));
	if(_tcscmp(szLoadInfo,_T("��")) == 0)
		return 0;
	else if(_tcscmp(szLoadInfo,_T("��")) == 0)
		return 1;
	else if(_tcscmp(szLoadInfo,_T("æ")) == 0)
		return 2;
	else if(_tcscmp(szLoadInfo,_T("��")) == 0)
		return 3;
	else if(_tcscmp(szLoadInfo,_T("��")) == 0)
		return 4;
	return 15;

	//sprintf

	//��ȡͼ��
	if (pGameServerItem->m_ServerStatus==ServerStatus_Normal) 
		return IND_SERVER_NORMAL;
	if (pGameServerItem->m_ServerStatus==ServerStatus_Entrance) 
		return IND_SERVER_ENTRANCE;
	if (pGameServerItem->m_ServerStatus==ServerStatus_EverEntrance) 
		return IND_SERVER_EVERENTRANCE;

	return IND_SERVER_NORMAL;
}

//��ȡ����
LPCTSTR CServerListView::GetGameKindItemTitle(CGameKindItem * pGameKindItem, LPTSTR pszTitle, UINT uMaxCount)
{
	//��������
	LPCTSTR pszKindName(pGameKindItem->m_GameKind.szKindName);
	DWORD dwOnLineCount=pGameKindItem->m_GameKind.dwOnLineCount;
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

	//������Ϣ
	TCHAR szLoadInfo[32] = {0};
	if(pParameterGlobal->m_bShowServerStatus)
		GetLoadInfoOfGameKind(&(pGameKindItem->m_GameKind), szLoadInfo, CountArray(szLoadInfo));
	else
		_sntprintf(szLoadInfo,CountArray(szLoadInfo),TEXT("%ld"),dwOnLineCount);

	//�������
	//if (pGameKindItem->m_dwProcessVersion!=0L)
	//{
		_sntprintf(pszTitle,uMaxCount,TEXT("%s"),(LPCTSTR)pszKindName);
	//}
	//else
	//{
	//	_sntprintf(pszTitle,uMaxCount,TEXT("%s ��˫�����أ�"),pszKindName);
	//}

	return pszTitle; 
}

//��ȡ����
LPCTSTR CServerListView::GetGameServerItemTitle(CGameServerItem * pGameServerItem, LPTSTR pszTitle, UINT uMaxCount)
{
	//��������
	LPCTSTR pszServerName(pGameServerItem->m_GameServer.szServerName);
	DWORD dwOnLineCount=pGameServerItem->m_GameServer.dwOnLineCount;
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

	//������Ϣ
	TCHAR szLoadInfo[32] = {0};
	if(pParameterGlobal->m_bShowServerStatus)
		GetLoadInfoOfServer(&(pGameServerItem->m_GameServer), szLoadInfo, CountArray(szLoadInfo));
	else
		_sntprintf(szLoadInfo,CountArray(szLoadInfo),TEXT("%ld"),dwOnLineCount);

	//�������
	_sntprintf(pszTitle,uMaxCount,TEXT("%s [ %s ]"),pszServerName,szLoadInfo);

	return pszTitle; 
}

//ɾ������
VOID CServerListView::DeleteUpdateItem(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//ɾ������
	while (pGameListItem!=NULL)
	{
		//�����ж�
		if (pGameListItem->GetItemGenre()==ItemGenre_Kind)
		{
			//ɾ������
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;
			if (pGameKindItem->m_hItemAttachUpdate!=NULL) DeleteItem(pGameKindItem->m_hItemAttachUpdate);
			if (pGameKindItem->m_hItemNormalUpdate!=NULL) DeleteItem(pGameKindItem->m_hItemNormalUpdate);

			//���ñ���
			pGameKindItem->m_hItemAttachUpdate=NULL;
			pGameKindItem->m_hItemNormalUpdate=NULL;

			break;
		}

		//��ȡ����
		pGameListItem=pGameListItem->GetParentListItem();
	}

	return;
}

//�޸�����
VOID CServerListView::ModifyGameListItem(HTREEITEM hTreeItem, LPCTSTR pszTitle, UINT uImage)
{
	//return; 
	//��������
	TVITEM TVItem;
	ZeroMemory(&TVItem,sizeof(TVItem));

	//��������
	TVItem.hItem=hTreeItem;
	TVItem.cchTextMax=64;
	TVItem.iImage=uImage;
	TVItem.iSelectedImage=uImage;
	TVItem.pszText=(LPTSTR)pszTitle;
	TVItem.mask=/*TVIF_IMAGE|*/TVIF_SELECTEDIMAGE|TVIF_TEXT/*|TVIF_PARAM|TVIF_INTEGRAL*/;
	//TVItem.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;

	//�޸�����
	SetItem(&TVItem);

	return;
}

//��������
HTREEITEM CServerListView::InsertInsideItem(LPCTSTR pszTitle, UINT uImage, DWORD dwInsideID, HTREEITEM hParentItem)
{
	//��������
	TV_INSERTSTRUCT InsertStruct;
	ZeroMemory(&InsertStruct,sizeof(InsertStruct));

	//��������
	CGameInsideItem * pGameInsideItem=new CGameInsideItem;
	if (pGameInsideItem!=NULL) pGameInsideItem->m_dwInsideID=dwInsideID;

	//���ñ���
	InsertStruct.hParent=hParentItem;
	InsertStruct.hInsertAfter=TVI_LAST;

	//��������
	InsertStruct.item.cchTextMax=64;
	InsertStruct.item.iImage=uImage;
	InsertStruct.item.iSelectedImage=uImage;
	InsertStruct.item.pszText=(LPTSTR)pszTitle;
	InsertStruct.item.lParam=(LPARAM)pGameInsideItem;
	InsertStruct.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;

	return InsertItem(&InsertStruct);
}

//��������
HTREEITEM CServerListView::InsertGameListItem(LPCTSTR pszTitle, UINT uImage, CGameListItem * pGameListItem, HTREEITEM hParentItem,UINT nIntegral,bool bFirst)
{
	if (nIntegral==ITEM_TYPE_HEIGHT)
	{
		int a = 2;
	}
	//��������
	TV_INSERTSTRUCT InsertStruct;
	ZeroMemory(&InsertStruct,sizeof(InsertStruct));

	//���ñ���
	InsertStruct.hParent=hParentItem;
	InsertStruct.hInsertAfter=/*(nIntegral==ITEM_TYPE_HEIGHT)?TVI_LAST:*/TVI_FIRST;
	InsertStruct.item.cchTextMax=64;
	InsertStruct.item.iImage=uImage;
	InsertStruct.item.iSelectedImage=uImage;
	InsertStruct.item.pszText=(LPTSTR)pszTitle;
	InsertStruct.item.lParam=(LPARAM)pGameListItem;	
	InsertStruct.itemex.iIntegral = nIntegral;
	if (ITEM_LAST_HEIGHT == nIntegral)
	{
		InsertStruct.item.mask=TVIF_INTEGRAL|TVIF_PARAM;
		
		HTREEITEM hChildItem =  GetChildItem(GetRootItem());
		/*if (hChildItem!=NULL)
		{
			CGameListItem * pGameListTemp=(CGameListItem *)GetItemData(hChildItem);
			SetFocus();
			SelectItem(hChildItem);
			CRect rcChildItem;
			GetItemRect(hChildItem,&rcChildItem,FALSE);
			int nFirstChildHeight = rcChildItem.Height();
			if (nFirstChildHeight == ITEM_LAST_HEIGHT)
			{
				InsertStruct.itemex.iIntegral = 1;
			}
			else
			{
				InsertStruct.itemex.iIntegral = nIntegral;
			}
		}*/
	}
	else
	{
		InsertStruct.item.mask=/*TVIF_IMAGE|TVIF_SELECTEDIMAGE|*/TVIF_TEXT|TVIF_PARAM|TVIF_INTEGRAL;
		//InsertStruct.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE ;
	}
 //   nBB ++;
	//CString sMsg;
	//sMsg.Format("%s,%d  ,%d",pszTitle,nIntegral,nBB);
	//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//CLog ListLog;
	//ListLog.Init(pGlobalServer->GetAppPath() +"\\List.txt");
	//ListLog.WriteMsg(sMsg+"</br>");


	//Ѱ������
	if (hParentItem == NULL && !bFirst)
	{
		WORD wSortID=pGameListItem->GetSortID();
		HTREEITEM hTreeItem=GetNextItem(m_LastServerItem.m_hTreeItemNormal,TVGN_NEXT);
		if (hTreeItem ==NULL)
		{
			InsertStruct.hInsertAfter=m_LastServerItem.m_hTreeItemNormal;
		}
		else
		{
			while (hTreeItem!=NULL)
			{
				//��ȡ����
				CGameListItem * pGameListTemp=(CGameListItem *)GetItemData(hTreeItem);
				//���ݶԱ�
				if ((pGameListTemp!=NULL)&&(pGameListTemp->GetSortID()>wSortID)) 
				{
					InsertStruct.hInsertAfter=m_LastServerItem.m_hTreeItemNormal;
					break;
				}

				//���ý��
				InsertStruct.hInsertAfter=hTreeItem;

				//�л�����
				hTreeItem=GetNextItem(hTreeItem,TVGN_NEXT);
			}
		}
	}
	else if ((hParentItem!=NULL)&&(pGameListItem!=NULL))
	{
		//��������
		WORD wSortID=pGameListItem->GetSortID();
		HTREEITEM hTreeItem=GetChildItem(hParentItem);

		//ö������
		while (hTreeItem!=NULL)
		{
			//��ȡ����
			CGameListItem * pGameListTemp=(CGameListItem *)GetItemData(hTreeItem);

			//���ݶԱ�
			if ((pGameListTemp!=NULL)&&(pGameListTemp->GetSortID()>wSortID)) break;

			//���ý��
			InsertStruct.hInsertAfter=hTreeItem;

			//�л�����
			hTreeItem=GetNextItem(hTreeItem,TVGN_NEXT);
		} 
	}

	if (hParentItem == m_TreeListRoot && nIntegral == ITEM_TYPE_HEIGHT)
	if (_tcscmp("�����Ϸ", pszTitle) == 0)
	{
		InsertStruct.itemex.iIntegral = 0;
	}
	HTREEITEM insertItem = InsertItem(&InsertStruct);

	//BOOL bRet = (BOOL)SendMessage(TVM_SETITEM, 0, LPARAM(&InsertStruct.itemex));
	//TVITEMEX tvi;
	//tvi.mask = TVIF_INTEGRAL | TVIF_HANDLE;
	//tvi.hItem = insertItem;
	//tvi.iIntegral = nIntegral;
	//SetItem(reinterpret_cast<TVITEM*>(&tvi));
    return insertItem;
	//return InsertItem(&InsertStruct);
}

//�ػ���Ϣ
VOID CServerListView::OnPaint()
{
	CPaintDC dc(this);

	//����λ��
	CRect rcClip;
	dc.GetClipBox(&rcClip);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CDC BufferDC;
	CBitmap BufferImage;
	BufferDC.CreateCompatibleDC(&dc);
	BufferImage.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	//���� DC
	BufferDC.SelectObject(&BufferImage);

	//�滭�ؼ�
	DrawTreeBack(&BufferDC,rcClient,rcClip);
	DrawTreeItem(&BufferDC,rcClient,rcClip);

	//�滭����
	dc.BitBlt(rcClip.left,rcClip.top,rcClip.Width(),rcClip.Height(),&BufferDC,rcClip.left,rcClip.top,SRCCOPY);

	//ɾ����Դ
	BufferDC.DeleteDC();
	BufferImage.DeleteObject();

	return;
}

//ʱ����Ϣ
VOID CServerListView::OnTimer(UINT nIDEvent)
{ 
	//��������
	if (nIDEvent==IDI_UPDATE_ONLINE)
	{
		ASSERT(CMissionList::GetInstance()!=NULL);
		CMissionList::GetInstance()->UpdateOnLineInfo();

		return;
	}

	__super::OnTimer(nIDEvent);
}

//�滭����
BOOL CServerListView::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//λ����Ϣ
VOID CServerListView::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	//��ȡ��Ϣ
	SCROLLINFO ScrollInfoH;
	SCROLLINFO ScrollInfoV;
	ZeroMemory(&ScrollInfoH,sizeof(ScrollInfoH));
	ZeroMemory(&ScrollInfoV,sizeof(ScrollInfoV));

	//��ȡ��Ϣ
	GetScrollInfo(SB_HORZ,&ScrollInfoH,SIF_POS|SIF_RANGE);
	GetScrollInfo(SB_VERT,&ScrollInfoV,SIF_POS|SIF_RANGE);

	//���ñ���
	m_nXScroll=-ScrollInfoH.nPos;
	m_nYScroll=-ScrollInfoV.nPos;

	return;
}

//�����Ϣ
BOOL CServerListView::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//�������
	HTREEITEM hItemMouseHover=HitTest(MousePoint);
	HTREEITEM hItemRoot = GetRootItem( );
	if (hItemMouseHover == hItemRoot)
	{
		return FALSE;
	}
	if (GetParentItem(hItemMouseHover) == hItemRoot)
	{
		return FALSE;
	}

	//�ػ��ж�
	if ((hItemMouseHover!=NULL)&&(hItemMouseHover!=m_hItemMouseHover))
	{
		//���ñ���
		m_hItemMouseHover=hItemMouseHover;

		//�ػ�����
		Invalidate(FALSE);
	}

	//���ù��
	if (hItemMouseHover!=NULL)
	{
		CGameListItem * pGameListTemp=(CGameListItem *)GetItemData(hItemMouseHover);
		if (pGameListTemp!=NULL)
		{
			CString str = GetItemText(hItemMouseHover);
			if(pGameListTemp->GetItemGenre() == ItemGenre_Server && str != "")
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
				return true;
			}
		}
		//return true;
	}
	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//�Ҽ��б�
VOID CServerListView::OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��ȡѡ��
	HTREEITEM hTreeItem=GetCurrentSelectItem(false);

	//ѡ���ж�
	if (hTreeItem==NULL) return;

	//����ѡ��
	Select(hTreeItem,TVGN_CARET);

	//��ȡ����
/*	CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);
	if (pGameListItem!=NULL)
	{
		switch (pGameListItem->GetItemGenre())
		{
		case ItemGenre_Kind:	//��Ϸ����
			{
				//��������
				TCHAR szBuffer[64]=TEXT("");
				CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;

				//����˵�
				CSkinMenu Menu;
				Menu.CreateMenu();

				//�Զ�����
				Menu.AppendMenu(IDM_ENTER_SERVER,TEXT("�Զ�����"));
				Menu.AppendSeparator();

				//������Ϸ
				CW2CT pszKindName(pGameKindItem->m_GameKind.szKindName);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("���ء�%s��"),(LPCTSTR)pszKindName);
				Menu.AppendMenu(IDM_DOWN_LOAD_CLIENT,szBuffer);

				//��ǰ�汾
				if (pGameKindItem->m_dwProcessVersion!=0)
				{
					DWORD dwVersion=pGameKindItem->m_dwProcessVersion;
					_sntprintf(szBuffer,CountArray(szBuffer),TEXT("��װ�汾 %d.%d.%d.%d"),GetProductVer(dwVersion),
						GetMainVer(dwVersion),GetSubVer(dwVersion),GetBuildVer(dwVersion));
					Menu.AppendMenu(IDM_NULL_COMMAND,szBuffer,MF_GRAYED);
				}
				else Menu.AppendMenu(IDM_DOWN_LOAD_CLIENT,TEXT("û�а�װ��������أ�"));

				//���Ʋ˵�
				Menu.AppendSeparator();
				bool bExpand=ExpandVerdict(hTreeItem);
				Menu.AppendMenu(bExpand?IDM_SHRINK_LIST:IDM_EXPAND_LIST,bExpand?TEXT("�����б�"):TEXT("չ���б�"));

				//�����˵�
				Menu.TrackPopupMenu(this);

				return;
			}
		case ItemGenre_Server:	//��Ϸ����
			{
				//��������
				TCHAR szBuffer[64]=TEXT("");
				CGameServerItem * pGameServerItem=(CGameServerItem *)pGameListItem;
				CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;

				//����˵�
				CSkinMenu Menu;
				Menu.CreateMenu();
				Menu.AppendMenu(IDM_ENTER_SERVER,TEXT("������Ϸ����"));
				Menu.AppendSeparator();
				Menu.AppendMenu(IDM_SET_COLLECTION,TEXT("��Ϊ���÷�����"));

				//������Ϸ
				CW2CT pszKindName(pGameKindItem->m_GameKind.szKindName);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("���ء�%s��"),(LPCTSTR)pszKindName);
				Menu.AppendMenu(IDM_DOWN_LOAD_CLIENT,szBuffer);
				Menu.AppendSeparator();

				//��ǰ�汾
				if (pGameKindItem->m_dwProcessVersion!=0)
				{
					DWORD dwVersion=pGameKindItem->m_dwProcessVersion;
					_sntprintf(szBuffer,CountArray(szBuffer),TEXT("��װ�汾 %d.%d.%d.%d"),GetProductVer(dwVersion),
						GetMainVer(dwVersion),GetSubVer(dwVersion),GetBuildVer(dwVersion));
					Menu.AppendMenu(IDM_NULL_COMMAND,szBuffer,MF_GRAYED);
				}
				else Menu.AppendMenu(IDM_DOWN_LOAD_CLIENT,TEXT("û�а�װ��������أ�"));

				//�˵�����
				bool Collection=false;//pGameServerItem->IsCollection();
				if (Collection==true) Menu.CheckMenuItem(IDM_SET_COLLECTION,MF_BYCOMMAND|MF_CHECKED);

				//�����˵�
				Menu.TrackPopupMenu(this);

				return;
			}
		}
	}*/

	return;
}

//����б�
VOID CServerListView::OnNMLClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��ȡѡ��
	HTREEITEM hTreeItem=GetCurrentSelectItem(false);
	//ѡ���ж�
	if (hTreeItem==NULL) return;

	HTREEITEM hItemRoot = GetRootItem( );
	if (hTreeItem == hItemRoot)
	{
		*pResult = TRUE;
		return;
	}
	if (GetParentItem(hTreeItem) == hItemRoot)
	{
		*pResult = TRUE;
		return;
	}
	//����ѡ��
	Select(hTreeItem,TVGN_CARET);

	//��ȡ����
	CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);

	//���뷿��
	if ((pGameListItem!=NULL)&&(pGameListItem->GetItemGenre()==ItemGenre_Server))
	{
		//���뷿��
		CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
		pPlatformFrame->EntranceServerItem((CGameServerItem *)pGameListItem);

		return;
	}

	//�ڲ�����
	if ((pGameListItem!=NULL)&&(pGameListItem->GetItemGenre()==ItemGenre_Inside))
	{
		//��������
		CGameInsideItem * pGameInsideItem=(CGameInsideItem *)pGameListItem;

		//����Ŀ¼
		TCHAR szDirectory[MAX_PATH]=TEXT("");
		CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

		//����·��
		TCHAR szAssistantPath[MAX_PATH]=TEXT("");
		_sntprintf(szAssistantPath,CountArray(szAssistantPath),TEXT("%s\\Collocate\\Collocate.INI"),szDirectory);

		//��ȡ��ַ
		TCHAR szItemName[128]=TEXT(""),szAssistantLink[128]=TEXT("");
		_sntprintf(szItemName,CountArray(szItemName),TEXT("Assistant%ld"),pGameInsideItem->m_dwInsideID);
		GetPrivateProfileString(szItemName,TEXT("AssistantLink"),TEXT(""),szAssistantLink,CountArray(szAssistantLink),szAssistantPath);

		//���ӵ�ַ
		if (szAssistantLink[0]!=0)
		{
			CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
			if (pPlatformFrame!=NULL) pPlatformFrame->WebBrowse(szAssistantLink,false);
		}

		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//int nTotalHeight = 3800;//CalclateTotalHeight();
	//int nCount = 5;//CalculateVisableItemCount();
	//CRect m_rect;
	//GetClientRect(&m_rect);

	//SCROLLINFO scrlinfo;
	//scrlinfo.cbSize = sizeof(scrlinfo);

	//scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
	//scrlinfo.nMax = nTotalHeight;
	//scrlinfo.nMin = 0;
	//scrlinfo.nPage = m_rect.Height();
	//scrlinfo.nPos = 0;
	//SetScrollInfo(SB_VERT,&scrlinfo);

	Invalidate();
	*pResult = TRUE;
	//////////////////////////////////////////////////////////////////////////

	return;
}

//�б�ı�
VOID CServerListView::OnTvnSelchanged(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��ȡѡ��
	HTREEITEM hTreeItem=GetSelectedItem();

	//ѡ���ж�
	if (hTreeItem==NULL) 
		return;
	HTREEITEM hItemRoot = GetRootItem( );
	if (hTreeItem == hItemRoot)
		return;

	//��ȡ����
	CGameListItem * pGameListItem=(CGameListItem *)GetItemData(hTreeItem);

	//���ݴ���
	if (pGameListItem!=NULL)
	{
		switch (pGameListItem->GetItemGenre())
		{
		case ItemGenre_Kind:	//��Ϸ����
			{
				//��������
				WORD wGameID=((CGameKindItem *)pGameListItem)->m_GameKind.wGameID;

				//�����ַ
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				TCHAR szRuleLink[MAX_PATH]=TEXT("");
				_sntprintf(szRuleLink,CountArray(szRuleLink),TEXT("%s/GameRule.aspx?GameID=%ld"),pGlobalServer->GetPlatformServer(3),wGameID);

				//��ҳ��
				CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
				if (pPlatformFrame!=NULL) pPlatformFrame->WebBrowse(szRuleLink,false);

				return;
			}
		case ItemGenre_Page:	//��������
			{
				//��������
				WORD wPageID=((CGamePageItem *)pGameListItem)->m_GamePage.wPageID;

				//�����ַ
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				TCHAR szPageLink[MAX_PATH]=TEXT("");
				_sntprintf(szPageLink,CountArray(szPageLink),TEXT("%s/GamePage.aspx?PageID=%ld"),pGlobalServer->GetPlatformServer(3),wPageID);

				//��ҳ��
				CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
				if (pPlatformFrame!=NULL) pPlatformFrame->WebBrowse(szPageLink,false);

				return;
			}
		}
	}

	return;
}

//�б�չ��
VOID CServerListView::OnTvnItemexpanding(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��������
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	CGameListItem * pGameListItem=(CGameListItem *)GetItemData(pNMTreeView->itemNew.hItem);
	HTREEITEM hCurrentTree=GetSelectedItem();
	HTREEITEM hItemRoot = GetRootItem( );
	if (hCurrentTree == hItemRoot)
	{
		*pResult = TRUE;
		return;
	}

	//��������
	if (pNMTreeView->action==TVE_EXPAND)
	{
		//��ȡ����
		CGameListItem * pGameListItem=(CGameListItem *)GetItemData(pNMTreeView->itemNew.hItem);

		//�����
		if ((pGameListItem!=NULL)&&(pGameListItem->GetItemGenre()==ItemGenre_Kind))
		{
			//��������
			DWORD dwNowTime=(DWORD)time(NULL);
			CGameKindItem * pGameKindItem=(CGameKindItem *)pGameListItem;
			bool bTimeOut=(dwNowTime>=(pGameKindItem->m_dwUpdateTime+30L));

			//�����ж�
			if ((pGameKindItem->m_bUpdateItem==false)||(bTimeOut==true))
			{
				//�����б�
				pGameKindItem->m_bUpdateItem=true;
				pGameKindItem->m_dwUpdateTime=(DWORD)time(NULL);

				//��������
				CMissionList * pMissionList=CMissionList::GetInstance();
				//if (pMissionList!=NULL) 
				//	pMissionList->UpdateServerInfo(pGameKindItem->m_GameKind.wKindID);
			}

			return;
		}
	}

	return;
}

//��÷��为����Ϣ
LPCTSTR CServerListView::GetLoadInfo(DWORD dwOnLineCount, DWORD dwMaxCount, LPTSTR pszBuffer, WORD wBufferSize)
{
	if(pszBuffer == NULL) return NULL;
	if(dwMaxCount == 0)dwMaxCount = 2;

	DWORD dwPer = (dwOnLineCount*100)/dwMaxCount;
	if(dwPer > 80)
	{
		_sntprintf(pszBuffer, wBufferSize, TEXT("��"));
	}
	else if(dwPer > 60)
	{
		_sntprintf(pszBuffer, wBufferSize, TEXT("��"));
	}
	else if(dwPer > 40)
	{
		_sntprintf(pszBuffer, wBufferSize, TEXT("æ"));
	}
	else if(dwPer > 20)
	{
		_sntprintf(pszBuffer, wBufferSize, TEXT("��"));
	}
	else
	{
		_sntprintf(pszBuffer, wBufferSize, TEXT("��"));
	}

	return pszBuffer;
}

//��÷��为����Ϣ
LPCTSTR CServerListView::GetLoadInfoOfServer(tagGameServer * pGameServer, LPTSTR pszBuffer, WORD wBufferSize)
{
	if(pGameServer == NULL || pszBuffer == NULL) return NULL;

	return GetLoadInfo(pGameServer->dwOnLineCount, pGameServer->dwFullCount, pszBuffer, wBufferSize);
}

//��÷��为����Ϣ
LPCTSTR CServerListView::GetLoadInfoOfGameKind(tagGameKind * pGameKind, LPTSTR pszBuffer, WORD wBufferSize)
{
	if(pGameKind == NULL || pszBuffer == NULL) return NULL;

	return GetLoadInfo(pGameKind->dwOnLineCount, pGameKind->dwFullCount, pszBuffer, wBufferSize);
}

//���ؼ�¼
void CServerListView::LoadLastPlayGame()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szFileName[MAX_PATH]={0};
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\ConstantlyPlayGame.wh"),szDirectory);

	//��ȡ�ļ�
	CFile file;
	if(file.Open(szFileName, CFile::modeRead))
	{
		//��ȡ����
		char buffer[128]={0};
		UINT uReadCount=file.Read(buffer, CountArray(buffer));
		uReadCount /= 2;

		//�����¼
		WORD *pServerIDArry = (WORD *)buffer;
		for(BYTE i=0; i<uReadCount; i++)
		{
			if(pServerIDArry[i]>0) 
				m_LastPlayGameList.AddHead(pServerIDArry[i]);
		}

		//�ر��ļ�
		file.Close();
	}

	return;
}

//�����¼
void CServerListView::SaveLastPlayGame()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szFileName[MAX_PATH]={0};
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\ConstantlyPlayGame.wh"),szDirectory);

	//д���ļ�
	CFile file;
	if(file.Open(szFileName, CFile::modeCreate|CFile::modeWrite))
	{
		//��������
		POSITION Position=m_LastPlayGameList.GetHeadPosition();
		WORD wServerIDArry[SHOW_LAST_COUNT]={0};
		for(BYTE i=0; i<SHOW_LAST_COUNT; i++)
		{
			if(Position == NULL) break;

			wServerIDArry[i]=m_LastPlayGameList.GetNext(Position);
		}

		//д������
		file.Write(wServerIDArry, sizeof(wServerIDArry));

		//�ر��ļ�
		file.Close();
	}

	return;
}

void CServerListView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//this->Invalidate();
	//CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	//return;
	//// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nScrollPos = GetScrollPos(SB_VERT);
	int nLimit = GetScrollLimit(SB_VERT);

	int nScroll = nLimit;

	int SCROLL_AMT_Y = 50;

	switch(nSBCode) {
		case SB_LINEUP:      // Scroll up.  
			{
				int aa = 2;
			}
		case SB_PAGEUP:
			if(nScrollPos <= 0)
			{
				return;
			}
			nScroll = min(nScrollPos,SCROLL_AMT_Y);
			SetScrollPos(SB_VERT,nScrollPos - nScroll);
			break;   
		case SB_LINEDOWN:   // Scroll down.
			{
				int bb = 2;
			}
		case SB_PAGEDOWN:
			if(nScrollPos >= nLimit)
			{
				return;
			}
			nScroll = min(nScroll-nScrollPos,SCROLL_AMT_Y);
			SetScrollPos(SB_VERT,nScrollPos + nScroll);
			//ScrollWindow(5,0);
			break;
		case SB_THUMBPOSITION:
			{
				HWND hWndScroll;
				if ( pScrollBar == NULL )
					hWndScroll = m_hWnd;
				else
					hWndScroll = pScrollBar->m_hWnd;

				SCROLLINFO info;
				info.cbSize = sizeof(SCROLLINFO);
				info.fMask = SIF_ALL;
				::GetScrollInfo(hWndScroll, SB_VERT, &info);

				nPos = info.nTrackPos;

				int nScr = nScrollPos - nPos;

				SetScrollPos(SB_VERT,nPos);
			}
			break;
		case SB_THUMBTRACK:
			{
				HWND hWndScroll;
				if ( pScrollBar == NULL )
					hWndScroll = m_hWnd;
				else
					hWndScroll = pScrollBar->m_hWnd;

				SCROLLINFO info;
				info.cbSize = sizeof(SCROLLINFO);
				info.fMask = SIF_ALL;
				::GetScrollInfo(hWndScroll, SB_VERT, &info);

				nPos = info.nTrackPos;
               //nPos+=10;
				int nScr = nScrollPos - nPos;

				SetScrollPos(SB_VERT,nPos,TRUE);
			}
			break;
	}	
	Invalidate();
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
//////////////////////////////////////////////////////////////////////////////////
