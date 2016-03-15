// GroupBox.cpp : 实现文件
//

#include "stdafx.h"
#include "GroupBox.h"
#include ".\groupbox.h"


// CGroupBox

IMPLEMENT_DYNAMIC(CGroupBox, CStatic)
CGroupBox::CGroupBox()
{
	m_nRoundWidth = 0;
	m_nRoundHeight = 0;
	m_crBorder = RGB(0,0,0);
	m_crText = RGB(0,0,0);
}

CGroupBox::~CGroupBox()
{
}


BEGIN_MESSAGE_MAP(CGroupBox, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CGroupBox 消息处理程序


void CGroupBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()

	ShowWindow(SW_HIDE);
}

//设置圆角宽高
void CGroupBox::SetRoundXY(int nWidth, int nHeight)
{
	m_nRoundWidth = nWidth;
	m_nRoundHeight = nHeight;
}

//设置边框颜色
void CGroupBox::SetBorderColor(COLORREF crBorder)
{
	m_crBorder = crBorder;
}

//绘画组框
BOOL CGroupBox::Draw(CDC *pDC)
{
	BOOL bResult = FALSE;
	BOOL bReleaseDC = FALSE;
	CWnd *pParentWnd = NULL;
	
	if (!IsWindow(m_hWnd))
	{
		return bResult;
	}

	pParentWnd = GetParent();
	if (pParentWnd == NULL)
	{
		return bResult;
	}
	if ((pDC == NULL)
		|| (pDC->GetSafeHdc() == NULL))
	{
		pDC = pParentWnd->GetWindowDC();
		if (pDC == NULL)
		{
			return bResult;
		}
		bReleaseDC = TRUE;
	}

	CRect rcClient(0,0,0,0);
	CRect rcTemp(0,0,0,0);
	CString strText(_T(""));
	CSize sizeText(0, 0);

	GetWindowRect(&rcClient);
	pParentWnd->ScreenToClient(&rcClient);
	GetWindowText(strText);

	HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HGDIOBJ hOldBrush = ::SelectObject(pDC->GetSafeHdc(), hbr);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(GetFont());
	CPen pen(PS_SOLID, 1, m_crBorder);
	CPen *pOldPen = pDC->SelectObject(&pen);
	rcTemp = rcClient;
	rcTemp.top += pDC->GetTextExtent(_T("Y"), 1).cy/2;
	pDC->RoundRect(rcTemp.left, rcTemp.top, rcTemp.right, rcTemp.bottom, m_nRoundWidth, m_nRoundHeight);
	pDC->SelectObject(pOldPen);

	int nTextWidth = 0;
	int nTextHeight = pDC->GetTextExtent(_T("Y"), 1).cy;
	sizeText = pDC->GetTextExtent(strText);
	nTextWidth = (sizeText.cx > rcClient.Width()-16 ? rcClient.Width()-16 : sizeText.cx);
	rcTemp.left = rcClient.left + 5;
	if (!m_ImageBack.IsNull())
	{
		m_ImageBack.DrawImage(pDC->GetSafeHdc(), rcTemp.left, rcTemp.top, nTextWidth+6, 1, 5, 0, nTextWidth+6, 1);
	}

	pDC->SetTextColor(m_crText);
	rcTemp.left = rcClient.left + 8;
	rcTemp.top = rcClient.top;
	rcTemp.right = rcTemp.left + nTextWidth;
	rcTemp.bottom = rcTemp.top + nTextHeight;

	pDC->DrawText(strText, rcTemp, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);

	::SelectObject(pDC->GetSafeHdc(), hOldBrush);
	if (bReleaseDC && (pParentWnd != NULL))
	{
		pParentWnd->ReleaseDC(pDC);
	}

	bResult = TRUE;
	return bResult;
}

void CGroupBox::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//创建背景图片
	if (cx <= 0 || cy <= 0) return;

	if (m_ImageBack.IsNull())
	{
		m_ImageBack.Create(cx, 1, 24);
	}
	else
	{
		if (!m_ImageBack.IsNull()
			&& (cx > m_ImageBack.GetWidth() || cy > m_ImageBack.GetHeight()))
		{
			m_ImageBack.Destroy();
			m_ImageBack.Create(cx, 1, 24);
		}
	}
}

void CGroupBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	CStatic::PreSubclassWindow();

	//调整控件位置
	CRect rcWindow(0,0,0,0);
	GetWindowRect(&rcWindow);
	PostMessage(WM_SIZE, 0, MAKELPARAM(rcWindow.Width(), rcWindow.Height()));
}

//设置背景
BOOL CGroupBox::SetStaticBack(CDC *pDC, CWnd *pParentWnd)
{
	if (pDC == NULL
		|| pParentWnd == NULL
		|| !IsWindow(m_hWnd)
		|| !IsWindow(pParentWnd->GetSafeHwnd()))
	{
		return FALSE;
	}

	CRect rcButton;
	CRect rcTemp(0,0,0,0);
	GetWindowRect(&rcButton);
	pParentWnd->ScreenToClient(&rcButton);

	//缓冲DC
	CDC *pBackDC = NULL;
	if (m_ImageBack.IsNull()) return FALSE;
	pBackDC = CDC::FromHandle(m_ImageBack.GetDC());
	rcTemp.SetRect(0, 0, m_ImageBack.GetWidth(), m_ImageBack.GetHeight());
	pBackDC->FillSolidRect(rcTemp, RGB(0,0,0));
	int nTextHeight = pDC->GetTextExtent(_T("Y"), 1).cy;

	pBackDC->BitBlt(0, 0, rcButton.Width(), rcButton.Height(), pDC, rcButton.left, rcButton.top+nTextHeight/2, SRCCOPY);
	m_ImageBack.ReleaseDC();

	return TRUE;
}
