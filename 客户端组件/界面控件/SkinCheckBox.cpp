// SkinCheckBox.cpp : ʵ���ļ�
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



// CSkinCheckBox ��Ϣ�������
//������Ϣ
INT CSkinCheckBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1)
		return -1;

	//���ÿؼ�
	Initialization();

	return 0;
}

//�ؼ���
VOID CSkinCheckBox::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//���ÿؼ�
	Initialization();

	return;
}


//���ÿؼ�
VOID CSkinCheckBox::Initialization()
{
	//��������
	//if (m_AutoRectify=true) RectifyControl();
	//��������
	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);

	return;
}

HBRUSH CSkinCheckBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(nCtlColor)  
	{
	case CTLCOLOR_STATIC:
		pDC->SetTextColor(RGB(255,0,0));         //������ɫ
		pDC->SetBkColor(RGB(0, 0, 255)); //���屳��ɫ  

		if (pDC) pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	default:
		break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


//�滭�ؼ�
HBRUSH CSkinCheckBox::CtlColor(CDC * pDC, UINT nCtlColor)
{
	//��ͨ״̬
	pDC->SetTextColor(RGB(255,0,0));         //������ɫ
	pDC->SetBkColor(RGB(0, 0, 255)); //���屳��ɫ  
	return NULL;
}

VOID CSkinCheckBox::SetTextColor(COLORREF crBackColor, COLORREF crFontText, COLORREF crDlgText)
{
	m_crBackColor = crBackColor;
	m_crFontText = crFontText;
	m_crDlgText = crDlgText;
	//�ػ�����
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
}