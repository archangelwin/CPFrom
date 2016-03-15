#include "StdAfx.h"
#include "HideUserList.h"

CHideUserList::CHideUserList(void)
{
}

CHideUserList::~CHideUserList(void)
{
}


VOID CHideUserList::InitHideUserInfo()
{
	/*SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);*/
// 	m_ImageList.Create(1, 20, ILC_COLOR16 | ILC_MASK, 1, 0);
// 	SetImageList(&m_ImageList, LVSIL_SMALL);

	int Col;
	for (Col=0;Col<this->GetColCount();++Col)
	{
		const CString& title = GetColTitle(Col);
		CGridColumnTrait* pTrait = NULL;
// 		if (Col == 2 || Col == 3)
// 		{
// 			pTrait = new CGridColumnTraitEdit;
// 		}else
			pTrait = new CGridColumnTraitText;

		InsertColumnTrait(Col, title, LVCFMT_LEFT, 98, Col, pTrait);
	}
	
	SetCellMargin(1);

	m_HideUserInfo.SeleteHideUser();
	
}

VOID CHideUserList::InsertUserInfo()
{
	CString userID,NickName;
	int iLine=GetItemCount();

	int k = m_HideUserInfo.m_HideUser.GetCount();
	for (int i=0;i<m_HideUserInfo.m_HideUser.GetCount();i++)
	{
		userID = m_HideUserInfo.m_HideUser[i]->UserID;
		NickName = m_HideUserInfo.m_HideUser[i]->NickName;
		iLine++;
		InsertItem(iLine,userID);
		
		int col = 0;
		switch (col)
		{
		case 0:
			{
				SetItemText(iLine,++col,userID);
			}
		case 1:
			{
				SetItemText(iLine,++col,NickName);
			}
		}
	}
	
	
}


//右键列表
VOID CHideUserList::OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult)
{

	if( GetFocus() != this )
		SetFocus();	// Force focus to finish editing

	// Find out what subitem was clicked
	CPoint point;
	::GetCursorPos(&point);
	// 	int nRow, nCol;
	// 	CellHitTest(point, nRow, nCol);

	// If not right-clicking on an actual row, then don't update focus cell
	if (nRow!=-1)
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

void CHideUserList::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetFocus() != this )
		SetFocus();	// Force focus to finish editing

	// Find out what subitem was clicked
	CellHitTest(point, nRow, nCol);
	// 
	// 	// If not right-clicking on an actual row, then don't update focus cell
// 	if (nRow!=-1)
// 	{
// 		m_nItem = nRow;
// 		// 		// Update the focused cell before calling CListCtrl::OnRButtonDown()
// 		// 		// as it might cause a row-repaint
// 		CUserInfoItem * pGameUserInfoItem = (CUserInfoItem * )GetItemData(nRow);
// 		m_ServerID = ((CUserInfoItem * )GetItemData(nRow))->m_tagUMUserScoreSet.dwServerID;
// 	}

	CListCtrl::OnRButtonDown(nFlags, point);
}