// InsureSuccess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InsureSuccess.h"


// CInsureSuccess �Ի���

IMPLEMENT_DYNAMIC(CInsureSuccess, CDialog)

CInsureSuccess::CInsureSuccess(CWnd* pParent /*=NULL*/)
	: CDialog(CInsureSuccess::IDD, pParent)
{
}

CInsureSuccess::~CInsureSuccess()
{
}

void CInsureSuccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_CLOSE, m_btCloseButton);
}


BEGIN_MESSAGE_MAP(CInsureSuccess, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CLOSE, &CInsureSuccess::OnBnClickedClose)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CInsureSuccess ��Ϣ�������

BOOL CInsureSuccess::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Image.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INSURE_SUCCESS"));
	m_Font.CreateFont(-12, 0, 0, 0, 400, FALSE, FALSE, FALSE, GB2312_CHARSET,  
		OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,  
		DEFAULT_PITCH, TEXT("����"));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	int nImageX = m_Image.GetWidth();
	int nImageY = m_Image.GetHeight();

	INT nXScreen=GetSystemMetrics(SM_CXSCREEN);
	INT nYScreen=GetSystemMetrics(SM_CYSCREEN);
	MoveWindow((nXScreen-nImageX)/2, (nYScreen-nImageY)/2,nImageX+1,nImageY+1);

	m_nBeginTop = 60;
	m_nTopSpace = 20;

	m_btCloseButton.MoveWindow(161,202,68,24);
//	m_btCloseButton.SetButtonColor(RGB(120,185, 43));
	m_btCloseButton.SetWindowText("�� ��");

	CRect rt;
	GetClientRect(rt);
	//��������
	CRgn Rgn;
	Rgn.CreateRoundRectRgn(0,0,rt.Width(),rt.Height(),4,4);
	//��������
	SetWindowRgn(Rgn,TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CInsureSuccess::SetInfo(DWORD dwGameID, char *szNickName, DWORD dwTargetGameID, char *szTargetNickName,  char *szDate, DWORD dwRecordID, SCORE lScore, char *szScore)
{
	m_dwGameID = dwGameID;
	strncpy(m_szNickName, szNickName, 32) ;
	m_dwTargetGameID = dwTargetGameID;
	strncpy(m_szTargetNickName, szTargetNickName, 32);
	m_dwRecordID = dwRecordID;
	m_lScore = lScore;
	strncpy(m_szDate, szDate, 32);
	strncpy(m_szScore, szScore, 128);
}
void CInsureSuccess::OnPaint()
{
	CPaintDC cdc(this); // device context for painting
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	CDC dc;
	dc.CreateCompatibleDC(&cdc);
	CBitmap* pOldBmp = NULL;
	if (m_BitBuffer.m_hObject == NULL)
	{
		m_BitBuffer.CreateCompatibleBitmap(&cdc,rcClient.Width(),rcClient.Height());
		pOldBmp = (CBitmap* )dc.SelectObject(&m_BitBuffer);
		CFont *pFont = (CFont *)dc.SelectObject(&m_Font);
		dc.SetTextColor(RGB(102,102,102));   
		dc.SetBkMode(TRANSPARENT);
		m_Image.DrawImage(&dc, 0, 0,rcClient.Width(),rcClient.Height(),0,0);
		CString strTemp;
		strTemp.Format("�������ǳƣ�%s", m_szNickName);
		dc.TextOut(88,m_nBeginTop, strTemp);
		strTemp.Format("������ID��%d", m_dwGameID);
		dc.TextOut(100,m_nBeginTop+m_nTopSpace, strTemp);
		strTemp.Format("�������ǳƣ�%s", m_szTargetNickName);
		dc.TextOut(88,m_nBeginTop+m_nTopSpace*2, strTemp);
		strTemp.Format("������ID��%d", m_dwTargetGameID);
		dc.TextOut(100,m_nBeginTop+m_nTopSpace*3, strTemp);
		strTemp.Format("���ͽ�ң�%I64d", m_lScore);
		dc.TextOut(100,m_nBeginTop+m_nTopSpace*4, strTemp);
		strTemp.Format("��д��%s", m_szScore);
		dc.TextOut(125,m_nBeginTop+m_nTopSpace*5, strTemp);
		strTemp.Format("�������ڣ�%s", m_szDate);
		dc.TextOut(100,m_nBeginTop+m_nTopSpace*6, strTemp);
		dc.TextOut(22,m_nBeginTop+m_nTopSpace*7, "��ʾ���رպ��Զ�����");
		dc.TextOut(22,m_nBeginTop+m_nTopSpace*8, "����ƾ֤");
		strTemp.Format("��ţ�%d",m_dwRecordID);
		dc.TextOut(288,43, strTemp);
		cdc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&dc,0,0,SRCCOPY);
		dc.SelectObject(pFont);
		dc.SelectObject(pOldBmp);
		dc.DeleteDC();
	}
	else
	{
		pOldBmp = (CBitmap* )dc.SelectObject(&m_BitBuffer);
		cdc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&dc,0,0,SRCCOPY);
		dc.SelectObject(pOldBmp);
		dc.DeleteDC();
	}
}

void CInsureSuccess::OnBnClickedClose()
{
	if(OpenClipboard())
	{

		EmptyClipboard();
		SetClipboardData(CF_BITMAP,m_BitBuffer.m_hObject);
		CloseClipboard();
	}
	m_Font.DeleteObject();
	m_BitBuffer.DeleteObject();
	OnCancel();
}

LRESULT CInsureSuccess::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CDialog::OnNcHitTest(point);
	//�Ի�����϶�
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}
