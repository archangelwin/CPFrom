// InputNum.cpp : 实现文件
//

#include "stdafx.h"
#include "InputNum.h"
#include "AuthenDlg.h"

// CInputNum 对话框

IMPLEMENT_DYNAMIC(CInputNum, CDialog)

CInputNum::CInputNum(CAuthenDlg* pParent /*=NULL*/)
	: CDialog(CInputNum::IDD, pParent), m_pAuthenDlg(pParent)
{

}

CInputNum::~CInputNum()
{
}

void CInputNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NUM1, m_btNum1);
	DDX_Control(pDX, IDC_BTN_NUM2, m_btNum2);
	DDX_Control(pDX, IDC_BTN_NUM3, m_btNum3);
	DDX_Control(pDX, IDC_BTN_NUM4, m_btNum4);
	DDX_Control(pDX, IDC_BTN_NUM5, m_btNum5);
	DDX_Control(pDX, IDC_BTN_NUM6, m_btNum6);
	DDX_Control(pDX, IDC_BTN_NUM7, m_btNum7);
	DDX_Control(pDX, IDC_BTN_NUM8, m_btNum8);
	DDX_Control(pDX, IDC_BTN_NUM9, m_btNum9);
	DDX_Control(pDX, IDC_BTN_NUM10, m_btNum10);
	DDX_Control(pDX, IDC_BTN_NUM11, m_btNum11);
	DDX_Control(pDX, IDC_BTN_DEL, m_btDel);
	DDX_Control(pDX, IDC_BTN_RESET, m_btReset);
}


BEGIN_MESSAGE_MAP(CInputNum, CDialog)
	ON_BN_CLICKED(IDC_BTN_NUM1, &CInputNum::OnBnClickedBtnNum1)
	ON_BN_CLICKED(IDC_BTN_NUM2, &CInputNum::OnBnClickedBtnNum2)
	ON_BN_CLICKED(IDC_BTN_NUM3, &CInputNum::OnBnClickedBtnNum3)
	ON_BN_CLICKED(IDC_BTN_NUM4, &CInputNum::OnBnClickedBtnNum4)
	ON_BN_CLICKED(IDC_BTN_NUM5, &CInputNum::OnBnClickedBtnNum5)
	ON_BN_CLICKED(IDC_BTN_NUM6, &CInputNum::OnBnClickedBtnNum6)
	ON_BN_CLICKED(IDC_BTN_NUM7, &CInputNum::OnBnClickedBtnNum7)
	ON_BN_CLICKED(IDC_BTN_NUM8, &CInputNum::OnBnClickedBtnNum8)
	ON_BN_CLICKED(IDC_BTN_NUM9, &CInputNum::OnBnClickedBtnNum9)
	ON_BN_CLICKED(IDC_BTN_NUM10, &CInputNum::OnBnClickedBtnNum10)
	ON_BN_CLICKED(IDC_BTN_NUM11, &CInputNum::OnBnClickedBtnNum11)
	ON_BN_CLICKED(IDC_BTN_DEL, &CInputNum::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_RESET, &CInputNum::OnBnClickedBtnReset)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM1, &CInputNum::OnBnDoubleclickedBtnNum1)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM2, &CInputNum::OnBnDoubleclickedBtnNum2)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM3, &CInputNum::OnBnDoubleclickedBtnNum3)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM4, &CInputNum::OnBnDoubleclickedBtnNum4)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM5, &CInputNum::OnBnDoubleclickedBtnNum5)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM6, &CInputNum::OnBnDoubleclickedBtnNum6)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM7, &CInputNum::OnBnDoubleclickedBtnNum7)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM8, &CInputNum::OnBnDoubleclickedBtnNum8)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM9, &CInputNum::OnBnDoubleclickedBtnNum9)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM10, &CInputNum::OnBnDoubleclickedBtnNum10)
	ON_BN_DOUBLECLICKED(IDC_BTN_NUM11, &CInputNum::OnBnDoubleclickedBtnNum11)
END_MESSAGE_MAP()


// CInputNum 消息处理程序

void CInputNum::OnBnClickedBtnNum1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM1);
}

void CInputNum::OnBnClickedBtnNum2()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM2);
}

void CInputNum::OnBnClickedBtnNum3()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM3);
}

void CInputNum::OnBnClickedBtnNum4()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM4);
}

void CInputNum::OnBnClickedBtnNum5()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM5);
}

void CInputNum::OnBnClickedBtnNum6()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM6);
}

void CInputNum::OnBnClickedBtnNum7()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM7);
}

void CInputNum::OnBnClickedBtnNum8()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM8);
}

void CInputNum::OnBnClickedBtnNum9()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM9);
}

void CInputNum::OnBnClickedBtnNum10()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM10);
}

void CInputNum::OnBnClickedBtnNum11()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM11);
}

void CInputNum::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pAuthenDlg->DelLastCharInEdit();
}

void CInputNum::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pAuthenDlg->ResetEdit();
}

void CInputNum::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	//获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);

	CPen PenOut(PS_SOLID,0,RGB(36, 26, 120));
	CPen PenIn(PS_SOLID,0,RGB(166, 178, 226));
	CBrush BrushOut(RGB(141, 141, 195));
	CBrush BrushIn(RGB(198,202,230));


	CBrush * pOldBrush=dc.SelectObject(&BrushOut);
	CPen* pOldPen = dc.SelectObject(&PenOut);
	dc.Rectangle(ClientRect);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	CRect InBordRect(ClientRect);
	InBordRect.DeflateRect(1,1,1,1);

	pOldBrush=dc.SelectObject(&BrushOut);
	pOldPen = dc.SelectObject(&PenIn);
	dc.Rectangle(InBordRect);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	CRect InRect(ClientRect);
	InRect.DeflateRect(7,7,7,7);
	pOldPen = dc.SelectObject(&PenOut);
	pOldBrush=dc.SelectObject(&BrushIn);
	dc.Rectangle(InRect);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

void CInputNum::AddNumToEidt(int nID)
{
	TCHAR szBtnCaption[32];
	GetDlgItemText(nID,szBtnCaption,CountArray(szBtnCaption));
	CString strCaption(szBtnCaption);
	m_pAuthenDlg->AddCharToEdit(strCaption);
}


void CInputNum::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if(bShow)
	{
		time_t   t; 
		srand((unsigned)time(&t)); 
		int number;
		std::map<int, CString> NumMap;
		int i=0;
		for(i=0; i<11; i++)
		{
			CString strCaption;
			if(i==10)
			{
				strCaption="x";
			}
			else
			{
				strCaption.Format("%d", i);
			}
			number=IDC_BTN_NUM1+(int)(11.0*rand()/RAND_MAX);
			if(NumMap.find(number) == NumMap.end())
			{
				NumMap.insert(make_pair(number,strCaption));
			}
			else
			{
				i--;
			}
		}

		std::map<int, CString>::iterator itBegin = NumMap.begin();
		for(itBegin; itBegin!= NumMap.end(); itBegin++)
		{
			int n = itBegin->first;
			CString strTemp = itBegin->second;
			SetDlgItemText(itBegin->first, itBegin->second);
		}

	}

}

BOOL CInputNum::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialog::OnEraseBkgnd(pDC);
}

void CInputNum::OnBnDoubleclickedBtnNum1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM1);
}

void CInputNum::OnBnDoubleclickedBtnNum2()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM2);
}

void CInputNum::OnBnDoubleclickedBtnNum3()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM3);
}

void CInputNum::OnBnDoubleclickedBtnNum4()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM4);
}

void CInputNum::OnBnDoubleclickedBtnNum5()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM5);
}

void CInputNum::OnBnDoubleclickedBtnNum6()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM6);
}

void CInputNum::OnBnDoubleclickedBtnNum7()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM7);
}

void CInputNum::OnBnDoubleclickedBtnNum8()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM8);
}

void CInputNum::OnBnDoubleclickedBtnNum9()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM9);
}

void CInputNum::OnBnDoubleclickedBtnNum10()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM10);
}

void CInputNum::OnBnDoubleclickedBtnNum11()
{
	// TODO: 在此添加控件通知处理程序代码
	AddNumToEidt(IDC_BTN_NUM11);
}
