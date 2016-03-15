#include "StdAfx.h"
#include "Resource.h"
#include ".\dlgmatchawards.h"


BEGIN_MESSAGE_MAP(CDlgMatchAwards, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


CDlgMatchAwards::CDlgMatchAwards(void):CDialog(IDD_DLG_MATCH_AWARDS)
{
	m_pMatchResult=NULL;

}

CDlgMatchAwards::~CDlgMatchAwards(void)
{

}


void CDlgMatchAwards::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//////��������
	////CPngImageSB ImageBack;

	//////����ͼƬ
	////ImageBack.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));

	////ImageBack.DrawImage(&dc, 0,0);

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(17,0,0,0,700,0,0,0,134,3,2,1,2,TEXT("����"));
	CFont * pOldFont=pBufferDC->SelectObject(&DrawFont);
	pBufferDC->SetTextColor(RGB(0,0,0));

	//��������
	CPngImageSB ImageAwards;

	//����ͼƬ
	ImageAwards.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));

	//����λ��
	INT nXPos=(rcClient.Width()-ImageAwards.GetWidth())/2;
	INT nYPos=(rcClient.Height()-ImageAwards.GetHeight())/2;

	//�滭����
	if(m_pMatchResult!=NULL)
	{
		//��������
// 		CFont DrawFont;
// 		DrawFont.CreateFont(16,0,0,0,700,0,0,0,134,3,2,1,2,TEXT("����"));
// 		CFont * pOldFont=pBufferDC->SelectObject(&DrawFont);
// 		pBufferDC->SetTextColor(RGB(0,0,0));

		CString strText;
		ImageAwards.DrawImage(pBufferDC,nXPos,nYPos);

//		pBufferDC->DrawText(strText, &CRect(nXPos+60+60,nYPos+205-30-95,nXPos+360+60,nYPos+230-30-95),DT_TOP|DT_LEFT|DT_SINGLELINE);
		pBufferDC->DrawText(m_pMatchResult->szDescribe, &CRect(nXPos+45,nYPos+115-20,nXPos+372,nYPos+195-20),DT_TOP|DT_WORDBREAK);

		pBufferDC->SelectObject(pOldFont);
		pBufferDC->SetTextColor(RGB(0,0,0));

		int nIndex=0;

		strText.Format(TEXT("%d"),m_pMatchResult->dwRank);
		//��������
		CFont DrawFont;
		DrawFont.CreateFont(25,0,0,0,700,0,0,0,134,3,2,1,2,TEXT("����"));
		CFont * pOldFont=pBufferDC->SelectObject(&DrawFont);
		pBufferDC->SetTextColor(RGB(255,0,0));
		pBufferDC->DrawText(strText, &CRect(nXPos+60+260,nYPos+205-30-55-3,nXPos+360+260,nYPos+230-30-55-3),DT_TOP|DT_LEFT|DT_SINGLELINE);

		pBufferDC->SelectObject(pOldFont);
		pBufferDC->SetTextColor(RGB(0,0,0));
		//��Ϸ�ҽ���
		if(m_pMatchResult->dwGold>0)
		{
 			CFont DrawFont;
 			DrawFont.CreateFont(14,0,0,0,700,0,0,0,134,3,2,1,2,TEXT("����"));
 			CFont * pOldFont=pBufferDC->SelectObject(&DrawFont);
			pBufferDC->SetTextColor(RGB(255,0,0));

			strText.Format(TEXT("%d��Ϸ��"), m_pMatchResult->dwGold);
			pBufferDC->DrawText(strText, &CRect(nXPos+160+20,nYPos+205-30+25,nXPos+460+20,nYPos+230-30+25),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}
		pBufferDC->SelectObject(pOldFont);
		pBufferDC->SetTextColor(RGB(0,0,0));

		//���ƽ���
		if(m_pMatchResult->dwMedal>0)
		{
			strText.Format(TEXT("%d����"), m_pMatchResult->dwMedal);
			pBufferDC->DrawText(strText, &CRect(nXPos+60,nYPos+205+nIndex*30-30,nXPos+360,nYPos+230+nIndex*30-30),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}

		//���齱��
		if(m_pMatchResult->dwExperience>0)
		{
			strText.Format(TEXT("�� %d����"), m_pMatchResult->dwExperience);
			pBufferDC->DrawText(strText, &CRect(nXPos+60,nYPos+205+nIndex*30-30,nXPos+360,nYPos+230+nIndex*30-30),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}

		CTime tmSCan = CTime::GetCurrentTime();
		CString szTime = tmSCan.Format("%Y��%m��%d�� %Hʱ%M��");
		pBufferDC->DrawText(szTime, &CRect(nXPos+220+40,nYPos+205+nIndex*30-30+60-15,nXPos+520+40,nYPos+230+nIndex*30-30+60-15),DT_TOP|DT_LEFT|DT_SINGLELINE);

		//������Դ
		//�ͷ���Դ
		pBufferDC->SelectObject(pOldFont);
		DrawFont.DeleteObject();
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);
}

void CDlgMatchAwards::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDOK, m_btCloseAwards);

	CWnd::DoDataExchange(pDX);
}

BOOL CDlgMatchAwards::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��������
	CPngImageSB ImageBack;

	//����ͼƬ
	ImageBack.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));
	m_btCloseAwards.SetButtonImage(IDB_BT_CLOSE_AWARDS,GetModuleHandle(GAME_FRAME_DLL_NAME),false,false);
	m_btCloseAwards.SetWindowPos(NULL,ImageBack.GetWidth()-55,30,27,22,SWP_NOZORDER);

    SetWindowPos(NULL, 0,0,ImageBack.GetWidth(),ImageBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	//CenterWindow();

	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//����λ��
	CRect rcUnLayered;
	rcUnLayered.top=20;
	rcUnLayered.left=20;
	rcUnLayered.right=rcWindow.Width()-20;
	rcUnLayered.bottom=rcWindow.Height()-20;

	//���ô�С
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());

	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,7,7);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	//�ֲ㴰��
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(7,7),false);

	return TRUE; 
}

void CDlgMatchAwards::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

void CDlgMatchAwards::OnWindowPosChanged(WINDOWPOS* lpWndPos)
{
	CDialog::OnWindowPosChanged(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}
}

LRESULT CDlgMatchAwards::OnNcHitTest(CPoint pt)
{
	//�Ի�����϶�
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(pt) ? HTCAPTION : CDialog::OnNcHitTest(pt);
}

//ȷ������
VOID CDlgMatchAwards::OnOK()
{
	/*ShowWindow(SW_HIDE);*/
	//Ͷ�ݹر�
	if(AfxGetMainWnd()!=NULL)
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

