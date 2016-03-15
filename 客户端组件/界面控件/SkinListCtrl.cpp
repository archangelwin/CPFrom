#include "Stdafx.h"
#include "Resource.h"
#include "SkinListCtrl.h"
#include "SkinResourceManager.h"

//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct tagSortInfo
{
	bool							bAscendSort;						//�����־
	WORD							wColumnIndex;						//�б�����
	CSkinListCtrl *					pSkinListCtrl;						//�б�ؼ�
};

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM_REFLECT()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//��̬����
CSkinListCtrlAttribute				CSkinListCtrl::m_SkinAttribute;		//�б�����

//Ĭ������
#define LIST_STYTE					LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinListCtrlAttribute::CSkinListCtrlAttribute()
{
	//��ɫ����
	m_crHeadTitle = RGB(0,0,0);
	m_crTitle=RGB(0,0,0);
	m_crListTX=RGB(0,0,0);
	m_crListBK=RGB(0,0,0);

	return;
}

//��������
CSkinListCtrlAttribute::~CSkinListCtrlAttribute()
{
}

//������Դ
bool CSkinListCtrlAttribute::Initialization(CSkinRenderManager * pSkinRenderManager)
{
	//��������
	m_crHeadTitle=RGB(10,10,10);
	m_crTitle=RGB(10,10,10);
	m_crListTX=RGB(10,10,10);
	m_crListBK=RGB(177,216,255);
	m_crListSelBK = RGB(101,101,255);

	//ɾ��ͼƬ
	m_SkinImageL.Destroy();
	m_SkinImageM.Destroy();
	m_SkinImageR.Destroy();

	//������Ϣ
	HINSTANCE hResInstance=GetModuleHandle(SKIN_CONTROL_DLL_NAME);
	m_SkinImageL.LoadFromResource(hResInstance,IDB_SKIN_HEADER_L);
	m_SkinImageM.LoadFromResource(hResInstance,IDB_SKIN_HEADER_M);
	m_SkinImageR.LoadFromResource(hResInstance,IDB_SKIN_HEADER_R);

	//��Ⱦ��Դ
	pSkinRenderManager->RenderImage(m_SkinImageL);
	pSkinRenderManager->RenderImage(m_SkinImageM);
	pSkinRenderManager->RenderImage(m_SkinImageR);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	//���ñ���
	m_uLockCount=0L;
	m_uItemHeight=130;

	return;
}

//��������
CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}

//�ؼ���
VOID CSkinHeaderCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//��������
	CFont Font;
	Font.CreatePointFont(m_uItemHeight,TEXT("����"));

	//��������
	SetFont(&Font);

	return;
}

//�ؼ���Ϣ
BOOL CSkinHeaderCtrl::OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT * pLResult)
{
	//��������
	NMHEADER * pNMHearder=(NMHEADER*)lParam;

	//�϶���Ϣ
	if ((pNMHearder->hdr.code==HDN_BEGINTRACKA)||(pNMHearder->hdr.code==HDN_BEGINTRACKW))
	{
		//��ֹ�϶�
		if (pNMHearder->iItem<(INT)m_uLockCount)
		{
			*pLResult=TRUE;
			return TRUE;
		}
	}

	return __super::OnChildNotify(uMessage,wParam,lParam,pLResult);
}

//��������
VOID CSkinHeaderCtrl::SetLockCount(UINT uLockCount)
{
	//���ñ���
	m_uLockCount=uLockCount;

	return;
}

//�����и�
VOID CSkinHeaderCtrl::SetItemHeight(UINT uItemHeight)
{
	//���ñ���
	m_uItemHeight=uItemHeight;

	//���ÿؼ�
	if (m_hWnd!=NULL)
	{
		//��������
		CFont Font;
		Font.CreatePointFont(m_uItemHeight,TEXT("����"));

		//��������
		SetFont(&Font);
	}

	return;
}

//�ػ�����
VOID CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcRect;
	GetClientRect(&rcRect);

	//��������
	CDC BufferDC;
	CBitmap BufferBmp;
	BufferDC.CreateCompatibleDC(&dc);
	BufferBmp.CreateCompatibleBitmap(&dc,rcRect.Width(),rcRect.Height());

	//���� DC
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(&BufferBmp);
	BufferDC.SetTextColor(CSkinListCtrl::m_SkinAttribute.m_crHeadTitle);
	BufferDC.SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	CSkinListCtrlAttribute * pSkinAttribute=&CSkinListCtrl::m_SkinAttribute;
	pSkinAttribute->m_SkinImageM.StretchBlt(BufferDC,0,0,rcRect.Width(),rcRect.Height());

	//�滭����
	CRect rcItem;
	HDITEM HDItem;
	TCHAR szBuffer[64];
	for (INT i=0;i<GetItemCount();i++)
	{
		//�������
		HDItem.mask=HDI_TEXT;
		HDItem.pszText=szBuffer;
		HDItem.cchTextMax=CountArray(szBuffer);

		//��ȡ��Ϣ
		GetItem(i,&HDItem);
		GetItemRect(i,&rcItem);

		//�滭����
		INT nLeftWidth=pSkinAttribute->m_SkinImageL.GetWidth();
		INT nRightWidth=pSkinAttribute->m_SkinImageR.GetWidth();
		pSkinAttribute->m_SkinImageL.StretchBlt(BufferDC,rcItem.left,rcItem.top,nLeftWidth,rcItem.Height());
		pSkinAttribute->m_SkinImageM.StretchBlt(BufferDC,rcItem.left+nLeftWidth,rcItem.top,rcItem.Width()-nLeftWidth-nRightWidth,rcItem.Height());
		pSkinAttribute->m_SkinImageR.StretchBlt(BufferDC,rcItem.right-nRightWidth,rcItem.top,nRightWidth,rcItem.Height());

		//�滭����
		rcItem.DeflateRect(3,1,3,1);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcItem,DT_END_ELLIPSIS|DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	//�滭����
	dc.BitBlt(0,0,rcRect.Width(),rcRect.Height(),&BufferDC,0,0,SRCCOPY);

	//������Դ
	BufferDC.DeleteDC();
	BufferBmp.DeleteObject();
	
	return;
}

//��������
BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC * pDC) 
{
	//ˢ�½���
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinListCtrl::CSkinListCtrl()
{
	//���ñ���
	m_bAscendSort=false;
	m_crTitle = CLR_INVALID;							//������ɫ
	m_crListTX = CLR_INVALID;							//�б�����
	m_crListBK = CLR_INVALID;					    	//�б��ɫ
	m_crListSelBK = CLR_INVALID;
	m_nCustomColumn = -1;
	return;
}

//��������
CSkinListCtrl::~CSkinListCtrl()
{
}

//�ؼ���
VOID CSkinListCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//���ù���
	m_SkinScrollBar.InitScroolBar(this);

	//������ɫ
	SetBkColor(m_SkinAttribute.m_crListBK);
	SetTextColor(m_SkinAttribute.m_crListTX);
	SetTextBkColor(m_SkinAttribute.m_crListBK);

	//��������
	SetExtendedStyle(LIST_STYTE);
	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return;
}

//�滭����
VOID CSkinListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//��������
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	//��ȡ����
	INT nItemID=lpDrawItemStruct->itemID;
	INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//������ɫ
	COLORREF rcTextColor=RGB(10,10,10);
	COLORREF rcBackColor=RGB(229,249,255);
	GetItemColor(lpDrawItemStruct,rcTextColor,rcBackColor);

	//�滭����
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	//���û���
	pDC->SetBkColor(rcBackColor);
	pDC->SetTextColor(rcTextColor);

	//�滭����
	for (INT i=0;i<nColumnCount;i++)
	{
		//��ȡλ��
		CRect rcSubItem;
		GetSubItemRect(nItemID,i,LVIR_BOUNDS,rcSubItem);

		//�滭�ж�
		if (rcSubItem.left>rcClipBox.right) break;
		if (rcSubItem.right<rcClipBox.left) continue;

		if (m_nCustomColumn>0 && i==m_nCustomColumn)
		{

			pDC->SetTextColor(RGB(69,137,176));
		}


		//�滭����
		pDC->FillSolidRect(&rcSubItem,rcBackColor);

		//if (nColumnCount ==4)
		//{
		//	CFont nFont ,* nOldFont; 
		//	nFont.CreateFont(100,200,0,0,600,TRUE,TRUE,0,0,0,0,0,0,_TEXT("����"));//�������� 
		//	nOldFont = pDC->SelectObject(&nFont);
		//}

		//�滭����
		DrawCustomItem(pDC,lpDrawItemStruct,rcSubItem,i);
	}

	//�滭����
	if (lpDrawItemStruct->itemState&ODS_FOCUS)
	{
		pDC->DrawFocusRect(&rcItem);
	}

	return;
}
//
//void CSkinListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	TCHAR lpBuffer[256];
//	LV_ITEM lvi;
//	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
//	lvi.iItem = lpDrawItemStruct->itemID ; 
//	lvi.iSubItem = 0;
//	lvi.pszText = lpBuffer ;
//	lvi.cchTextMax = sizeof(lpBuffer);
//	VERIFY(GetItem(&lvi));
//	LV_COLUMN lvc, lvcprev ;
//	::ZeroMemory(&lvc, sizeof(lvc));
//	::ZeroMemory(&lvcprev, sizeof(lvcprev));
//	lvc.mask = LVCF_WIDTH | LVCF_FMT;
//	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;
//	CDC* pDC;
//	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
//	CRect rtClient;
//	GetClientRect(&rtClient);
//	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
//	{
//		if ( nCol > 0 ) 
//		{
//			GetColumn(nCol-1, &lvcprev) ;
//			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
//			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left; 
//		}
//		CRect rcItem;   
//		if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem))   
//			continue;   
//		::ZeroMemory(&lvi, sizeof(lvi));
//		lvi.iItem = lpDrawItemStruct->itemID;
//		lvi.mask = LVIF_TEXT | LVIF_PARAM;
//		lvi.iSubItem = nCol;
//		lvi.pszText = lpBuffer;
//		lvi.cchTextMax = sizeof(lpBuffer);
//		VERIFY(GetItem(&lvi));
//		CRect rcTemp;
//		rcTemp = rcItem;
//		if (nCol==0)
//		{
//			rcTemp.left -=2;
//		}
//		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
//		{
//			pDC->FillSolidRect(&rcTemp, GetSysColor(COLOR_HIGHLIGHT)) ;
//			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
//		}
//		else
//		{
//			COLORREF color;
//			color = GetBkColor();
//			pDC->FillSolidRect(rcTemp,color);
//			if (FindColColor(nCol,color))
//			{
//				pDC->FillSolidRect(rcTemp,color);
//			}
//			if (FindItemColor(nCol,lpDrawItemStruct->itemID,color))
//			{
//				pDC->FillSolidRect(rcTemp,color);
//			}
//			//pDC->SetTextColor(m_color);
//		}
//		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
//		UINT   uFormat    = DT_CENTER ;
//		if (m_Header.m_Format[nCol]=='0')
//		{
//			uFormat = DT_LEFT;
//		}
//		else if (m_Header.m_Format[nCol]=='1')
//		{
//			uFormat = DT_CENTER;
//		}
//		else if (m_Header.m_Format[nCol]=='2')
//		{
//			uFormat = DT_RIGHT;
//		}
//		TEXTMETRIC metric;
//		pDC->GetTextMetrics(&metric);
//		int ofst;
//		ofst = rcItem.Height() - metric.tmHeight;
//		rcItem.OffsetRect(0,ofst/2);
//		pDC->SetTextColor(m_color);
//		COLORREF color;
//		if (FindColTextColor(nCol,color))
//		{
//			pDC->SetTextColor(color);
//		}
//		if (FindItemTextColor(nCol,lpDrawItemStruct->itemID,color))
//		{
//			pDC->SetTextColor(color);
//		}
//		CFont nFont ,* nOldFont; 
//		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//�������� 
//		nOldFont = pDC->SelectObject(&nFont);
//		DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
//			&rcItem, uFormat) ;
//		pDC->SelectStockObject(SYSTEM_FONT) ;
//	}
//}



//������Ϣ
INT CSkinListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ù���
	m_SkinScrollBar.InitScroolBar(this);

	//������ɫ
	SetBkColor(m_SkinAttribute.m_crListBK);
	SetTextColor(m_SkinAttribute.m_crListTX);
	SetTextBkColor(m_SkinAttribute.m_crListBK);

	//��������
	SetExtendedStyle(LIST_STYTE|LVS_OWNERDRAWFIXED );
	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return 0;
}

//��ȡλ��
INT CSkinListCtrl::GetInsertIndex(VOID * pItemData)
{
	return GetItemCount();
}

//��������
INT CSkinListCtrl::SortItemData(LPARAM lParam1, LPARAM lParam2, WORD wColumnIndex, bool bAscendSort)
{
	//��ȡ����
	TCHAR szBuffer1[256]=TEXT("");
	TCHAR szBuffer2[256]=TEXT("");
	GetItemText((INT)lParam1,wColumnIndex,szBuffer1,CountArray(szBuffer1));
	GetItemText((INT)lParam2,wColumnIndex,szBuffer2,CountArray(szBuffer2));

	//�Ա�����
	INT nResult=lstrcmp(szBuffer1,szBuffer2);
	return (bAscendSort==true)?nResult:-nResult;
}

//�����ַ�
VOID CSkinListCtrl::ConstructString(VOID * pItemData, WORD wColumnIndex, LPTSTR pszString, WORD wMaxCount)
{
	//����Ч��
	ASSERT(pszString!=NULL);
	if (pszString==NULL) return;

	//���ñ���
	pszString[0]=0;

	return;
}

//��ȡ��ɫ
VOID CSkinListCtrl::GetItemColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF & crColorText, COLORREF & crColorBack)
{
	//������ɫ
	if (lpDrawItemStruct->itemState&ODS_SELECTED)
	{
		//ѡ����ɫ
		crColorText=RGB(10,10,10);
		crColorText = ((m_crTitle==CLR_INVALID)?m_SkinAttribute.m_crTitle:m_crTitle);
		crColorBack=RGB(101,101,255);
		crColorBack = ((m_crListBK==CLR_INVALID)?m_SkinAttribute.m_crListSelBK:m_crListSelBK);
	}
	else
	{
		//���ñ���
		crColorText=RGB(10,10,10);
		crColorText = ((m_crTitle==CLR_INVALID)?m_SkinAttribute.m_crTitle:m_crTitle);
		crColorBack=RGB(101,101,255);
		crColorBack = ((m_crListBK==CLR_INVALID)?m_SkinAttribute.m_crTitle:m_crListBK);
	}

	return;
}

//�滭����
VOID CSkinListCtrl::DrawCustomItem(CDC * pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect & rcSubItem, INT nColumnIndex)
{
	//��ȡ����
	TCHAR szString[256]=TEXT("");
	GetItemText(lpDrawItemStruct->itemID,nColumnIndex,szString,CountArray(szString));

	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	if (m_nItemHeight >0 && nColumnIndex == m_nCustomColumn)
	{	
		CFont boldfont;
		LOGFONT lf;          //����һ������ṹ���ʵ������logFont
		CSkinResourceManager::GetInstance()->GetDefaultFont().GetLogFont(&lf);
		lf.lfUnderline =TRUE;
		boldfont.CreateFontIndirect(&lf);
		/*pOldFont =*/ pDC->SelectObject(&boldfont);
	}


	//�滭����
	rcSubItem.left+=5;
	pDC->DrawText(szString,lstrlen(szString),&rcSubItem,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_CENTER);


	return;
}

//��������
VOID CSkinListCtrl::InsertDataItem(VOID * pItemData)
{
	//Ч��״̬
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	//��������
	INT nItemInsert=0;
	INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//��������
	for (INT i=0;i<nColumnCount;i++)
	{
		//��ȡ����
		TCHAR szString[256]=TEXT("");
		ConstructString(pItemData,i,szString,CountArray(szString));

		//�����б�
		if (i==0)
		{
			nItemInsert=InsertItem(LVIF_TEXT|LVIF_PARAM,GetInsertIndex(pItemData),szString,0,0,0,(LPARAM)pItemData);
		}
		else
		{
			SetItem(nItemInsert,i,LVIF_TEXT,szString,0,0,0,0);
		}
	}

	return;
}

//��������
VOID CSkinListCtrl::UpdateDataItem(VOID * pItemData)
{
	//Ч��״̬
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	//��������
	LVFINDINFO FindInfo;
	ZeroMemory(&FindInfo,sizeof(FindInfo));

	//���ñ���
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=(LPARAM)pItemData;

	//��������
	INT nItem=FindItem(&FindInfo);
	INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//��������
	if (nItem!=-1L)
	{
		//��������
		for (INT i=0;i<nColumnCount;i++)
		{
			//��ȡ����
			TCHAR szString[256]=TEXT("");
			ConstructString(pItemData,i,szString,CountArray(szString));

			//�����б�
			SetItem(nItem,i,LVIF_TEXT,szString,0,0,0,0);
		}

		//��������
		RedrawItems(nItem,nItem);
	}

	return;
}

//ɾ������
VOID CSkinListCtrl::DeleteDataItem(VOID * pItemData)
{
	//Ч��״̬
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	//��������
	LVFINDINFO FindInfo;
	ZeroMemory(&FindInfo,sizeof(FindInfo));

	//�������
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=(LPARAM)pItemData;

	//ɾ������
	INT nItem=FindItem(&FindInfo);
	if (nItem!=-1L) DeleteItem(nItem);

	return;
}

//�滭����
BOOL CSkinListCtrl::OnEraseBkgnd(CDC * pDC)
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

//���к���
INT CALLBACK CSkinListCtrl::SortFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamList)
{
	//��������
    tagSortInfo * pSortInfo=(tagSortInfo *)lParamList;
	CSkinListCtrl * pSkinListCtrl=pSortInfo->pSkinListCtrl;

	//��������
	return pSkinListCtrl->SortItemData(lParam1,lParam2,pSortInfo->wColumnIndex,pSortInfo->bAscendSort);
}

//�����Ϣ
VOID CSkinListCtrl::OnColumnclick(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��������
	NM_LISTVIEW * pNMListView=(NM_LISTVIEW *)pNMHDR;

	//��������
	tagSortInfo SortInfo;
	ZeroMemory(&SortInfo,sizeof(SortInfo));

	//���ñ���
	SortInfo.pSkinListCtrl=this;
	SortInfo.bAscendSort=m_bAscendSort;
	SortInfo.wColumnIndex=pNMListView->iSubItem;

	//���ñ���
	m_bAscendSort=!m_bAscendSort;

	//�����б�
	SortItems(SortFunction,(LPARAM)&SortInfo);

	return;
}


///////////////////////////////////////////////////////////////////////////////
// OnCustomDraw
void CSkinListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.

		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
		int nSubItem = pLVCD->iSubItem;

		//XLISTCTRLDATA *pXLCD = (XLISTCTRLDATA *) pLVCD->nmcd.lItemlParam;
		//ASSERT(pXLCD);

		//COLORREF crText  = m_crWindowText;
		//COLORREF crBkgnd = m_crWindow;

		//if (pXLCD)
		//{
		//	crText  = pXLCD[nSubItem].crText;
		//	crBkgnd = pXLCD[nSubItem].crBackground;

		//	if (!pXLCD[0].bEnabled)
		//		crText = m_crGrayText;
		//}

		// store the colors back in the NMLVCUSTOMDRAW struct
		//pLVCD->clrText = crText;
		//pLVCD->clrTextBk = crBkgnd;

		//CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
		//CRect rect;
		//GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);

		//if (pXLCD && (pXLCD[nSubItem].bShowProgress))
		//{
		//	DrawProgress(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);

		//	*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
		//}
		//else if (pXLCD && (pXLCD[nSubItem].nCheckedState != -1))
		//{
		//	DrawCheckbox(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);

		//	*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
		//}
		//else
		//{
		//	rect.left += DrawImage(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);

		//	DrawText(nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD);

		//	*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
		//}
	}

	UINT nFormat = DT_VCENTER | DT_SINGLELINE ;
								//+++
		nFormat |= DT_END_ELLIPSIS;

		nFormat |= DT_CENTER;


	CFont *pOldFont = NULL;
	CFont boldfont;

	// check if bold specified for subitem

	CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);

	CFont *font = pDC->GetCurrentFont();
	if (font)
	{
		LOGFONT lf;
		font->GetLogFont(&lf);
		lf.lfWeight = FW_BOLD;
		lf.lfUnderline =TRUE;
		boldfont.CreateFontIndirect(&lf);
		pOldFont = pDC->SelectObject(&boldfont);
	}
	pDC->SetBkMode(TRANSPARENT);
}

void CSkinListCtrl::SetItemHeight(UINT nHeight)
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

VOID CSkinListCtrl::SetCustomColumn(int nColumn)
{
	m_nCustomColumn = nColumn;
}


VOID CSkinListCtrl::SetListColor(COLORREF crTitle, COLORREF crListTX, COLORREF crListBK,COLORREF crListSelBK)
{
	m_crTitle = crTitle;							//������ɫ
	m_crListTX = crListTX;							//�б�����
	m_crListBK = crListBK;							//�б��ɫ
	m_crListSelBK = crListSelBK;
}

VOID CSkinListCtrl::SetHeadColor(COLORREF crHeadTitle)
{
	m_SkinAttribute.m_crHeadTitle = crHeadTitle;

}

LRESULT CSkinListCtrl::OnSetFont(WPARAM wParam, LPARAM)
{
	LRESULT res =  Default();

	CRect rc;
	GetWindowRect( &rc );

	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rc.Width();
	wp.cy = rc.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage( WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp );

	return res;
}

//void CSkinListCtrl::MeasureItem ( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
//{
//	LOGFONT lf;
//	GetFont()->GetLogFont( &lf );
//
//	if( lf.lfHeight < 0 )
//		lpMeasureItemStruct->itemHeight = -lf.lfHeight; 
//	else
//		lpMeasureItemStruct->itemHeight = lf.lfHeight; 
//}


void CSkinListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if( m_nItemHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
}

//////////////////////////////////////////////////////////////////////////////////
