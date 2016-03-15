// SkinCheckBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinCheckBox.h"


// CSkinCheckBox

IMPLEMENT_DYNAMIC(CSkinCheckBox, CButton)

CSkinCheckBox::CSkinCheckBox()
{

}

CSkinCheckBox::~CSkinCheckBox()
{
}


BEGIN_MESSAGE_MAP(CSkinCheckBox, CButton)
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CSkinCheckBox 消息处理程序
//建立消息
INT CSkinCheckBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1)
		return -1;

	//配置控件
	Initialization();

	return 0;
}

//控件绑定
VOID CSkinCheckBox::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//配置控件
	Initialization();

	return;
}


//配置控件
VOID CSkinCheckBox::Initialization()
{
	//调整窗口
	//if (m_AutoRectify=true) RectifyControl();
	//设置属性
	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);

	return;
}

HBRUSH CSkinCheckBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	switch(nCtlColor)  
	{
	case CTLCOLOR_STATIC:
		pDC->SetTextColor(RGB(255,0,0));         //字体颜色
		pDC->SetBkColor(RGB(0, 0, 255)); //字体背景色  

		if (pDC) pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	default:
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


//绘画控件
HBRUSH CSkinCheckBox::CtlColor(CDC * pDC, UINT nCtlColor)
{
	//普通状态
	pDC->SetTextColor(RGB(255,0,0));         //字体颜色
	pDC->SetBkColor(RGB(0, 0, 255)); //字体背景色  
	return NULL;
}

VOID CSkinCheckBox::SetTextColor(COLORREF crBackColor, COLORREF crFontText, COLORREF crDlgText)
{
	m_crBackColor = crBackColor;
	m_crFontText = crFontText;
	m_crDlgText = crDlgText;
	//重画窗口
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
}