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
	//����Բ�ǿ��
	void SetRoundXY(int nWidth, int nHeight);
	//���ñ߿���ɫ
	void SetBorderColor(COLORREF crBorder);
	//�����ı���ɫ
	void SetTextColor(COLORREF crText);
	//���ñ���
	BOOL SetStaticBack(CDC *pDC, CWnd *pParentWnd);
	//�滭���
	BOOL Draw(CDC *pDC);

protected:
	int m_nRoundWidth;
	int m_nRoundHeight;
	COLORREF m_crBorder;
	COLORREF m_crText;
	CImagePlus m_ImageBack;
};

#endif
