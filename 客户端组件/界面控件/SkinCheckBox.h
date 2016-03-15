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
	//������ɫ
	VOID SetTextColor(COLORREF crBackColor, COLORREF crFontText, COLORREF crDlgText);


	//��ɫ����
protected:
	COLORREF						m_crBackColor;						//������ɫ
	COLORREF						m_crFontText;						//������ɫ
	COLORREF						m_crDlgText;						//������ɫ

protected:
	//�ؼ���
	virtual VOID PreSubclassWindow();
	//���ÿؼ�
	VOID Initialization();
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�ػ���Ϣ
	//VOID OnNcPaint()
	//�滭�ؼ�
	HBRUSH CtlColor(CDC * pDC, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
};


