#pragma once

#include "SkinControlHead.h"
#include "SkinRenderManager.h"
// CSkinCheckBox

class SKIN_CONTROL_CLASS CSkinCheckBox : public CButton
{
	DECLARE_DYNAMIC(CSkinCheckBox)

public:
	CSkinCheckBox();
	virtual ~CSkinCheckBox();
	//字体颜色
	VOID SetTextColor(COLORREF crBackColor, COLORREF crFontText, COLORREF crDlgText);


	//颜色定义
protected:
	COLORREF						m_crBackColor;						//背景颜色
	COLORREF						m_crFontText;						//字体颜色
	COLORREF						m_crDlgText;						//字体颜色

protected:
	//控件绑定
	virtual VOID PreSubclassWindow();
	//配置控件
	VOID Initialization();
	//建立消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//重画消息
	//VOID OnNcPaint()
	//绘画控件
	HBRUSH CtlColor(CDC * pDC, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
};


