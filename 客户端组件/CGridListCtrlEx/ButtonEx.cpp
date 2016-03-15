// ButtonEx.cpp : 实现文件
//

#include "stdafx.h"
/*#include "ListCtrl-Button.h"*/
#include "ButtonEx.h"

// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
{

}

CButtonEx::~CButtonEx()
{
}

CButtonEx::CButtonEx( int nItem, int nSubItem, CRect rect, HWND hParent )    //-
{
	m_inItem = nItem;
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;
}

BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonEx::OnBnClicked)
END_MESSAGE_MAP()



// CButtonEx 消息处理程序



void CButtonEx::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage( m_hParent, WM_BN_CLICK, m_inItem, m_inSubItem );   //-
}
