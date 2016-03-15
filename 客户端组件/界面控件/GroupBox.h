#ifndef GROUPBOX_HEADER
#define GROUPBOX_HEADER

#pragma once

#include "ImagePlus.h"
#include "SkinControlHead.h"

// CGroupBox

class SKIN_CONTROL_CLASS CGroupBox : public CStatic
{
	DECLARE_DYNAMIC(CGroupBox)

public:
	CGroupBox();
	virtual ~CGroupBox();

protected:
	virtual void PreSubclassWindow();

protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	//设置圆角宽高
	void SetRoundXY(int nWidth, int nHeight);
	//设置边框颜色
	void SetBorderColor(COLORREF crBorder);
	//设置文本颜色
	void SetTextColor(COLORREF crText);
	//设置背景
	BOOL SetStaticBack(CDC *pDC, CWnd *pParentWnd);
	//绘画组框
	BOOL Draw(CDC *pDC);

protected:
	int m_nRoundWidth;
	int m_nRoundHeight;
	COLORREF m_crBorder;
	COLORREF m_crText;
	CImagePlus m_ImageBack;
};

#endif
