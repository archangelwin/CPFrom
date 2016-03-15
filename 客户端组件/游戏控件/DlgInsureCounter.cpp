#include "StdAfx.h"
#include "Resource.h"
#include "Information.h"
#include "DlgInsureCounter.h"
#include ".\dlginsurecounter.h"
#include "InsureSuccess.h"

//////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDlgInsureTeller, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_EDIT_TELLER, OnEnChangeScore)
	ON_BN_CLICKED(IDC_BUTTON_TELLER, OnBnClickedTakeScore)
	ON_BN_CLICKED(IDC_BT_QUERY_TELLER,OnBnClickedQueryInfo)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_TELLER_NUM1,IDC_TELLER_NUM7,OnInsureTellerClick)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CBankLogDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_BEFORE, OnBnClickedButtonBefore)
	//ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRANSFER_LOG, OnNMDblclkListTransferLog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TRANSFER_LOG, OnNMDblclkListTransferLog)
	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_TRANSFER_LOG, OnNMDblclkListTransferLog)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDlgInsureSave, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_BN_CLICKED(IDC_BT_SAVE_SCORE, OnBnClickedSaveScore)
	ON_BN_CLICKED(IDC_BT_QUERY_SAVE,OnBnClickedQueryInfo)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_INSURE_SAVENUM1,IDC_INSURE_SAVENUM7,OnInsureSaveClick)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDlgInsureTransfer, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_BN_CLICKED(IDC_BT_TRANSFER_SCORE, OnBnClickedTransferScore)
	ON_BN_CLICKED(IDC_BT_QUERY_TRANSFER,OnBnClickedQueryInfo)
	ON_BN_CLICKED(IDC_BY_ID, OnBnClickedById)
	ON_BN_CLICKED(IDC_BY_NAME, OnBnClickedByName)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_INSURE_TRANNUM1,IDC_INSURE_TRANNUM6,OnInsureTransferClick)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgBrowserItem, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgInsureMain, CSkinDialog)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeInsureMode)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SAFA, OnSelchangedTreeSafa)
	ON_NOTIFY(NM_CLICK, IDC_TREE_SAFA, OnClickTreeSafa)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

#define WM_INSUREPLAZA_UPDATA      (WM_USER+1680)             //���и�����Ϣ

struct tagInsurePlazaUpdata
{
	SCORE  lUserScore;
	SCORE  lUserInsure;
};

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureItem::CDlgInsureItem()
{
}

//��������
CDlgInsureItem::~CDlgInsureItem()
{
}

//��ȡ��Ϸ��
SCORE CDlgInsureItem::GetUserControlScore(CWnd * pWndScore)
{
	//��������
	WORD wIndex=0;
	SCORE lScore=0L;

	//��ȡ��ֵ
	TCHAR szBuffer[32]=TEXT("");
	pWndScore->GetWindowText(szBuffer,CountArray(szBuffer));

	//������ֵ
	while (szBuffer[wIndex]!=0)
	{
		//��������
		WORD wCurrentIndex=wIndex++;

		//������ֵ
		if ((szBuffer[wCurrentIndex]>=TEXT('0'))&&(szBuffer[wCurrentIndex]<=TEXT('9')))
		{
			lScore=lScore*10L+(szBuffer[wCurrentIndex]-TEXT('0'));
		}
	}

	return lScore;
}

//�滭����
VOID CDlgInsureItem::DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos)
{
	//ת������
	TCHAR szControl[128]=TEXT("");
	SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

	//��������
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//�滭�ж�
	if (nScoreLength>0L)
	{
		//������Դ
		CPngImageSB ImageNumber;
		ImageNumber.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("SCORE_NUMBER"));

		//��ȡ��С
		CSize SizeNumber;
		SizeNumber.SetSize(ImageNumber.GetWidth()/12L,ImageNumber.GetHeight());

		//�滭����
		for (INT i=0;i<nScoreLength;i++)
		{
			//�滭����
			if (szControl[i]==TEXT(','))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//�滭���
			if (szControl[i]==TEXT('.'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//�滭����
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//����λ��
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize)
{
	//��������
	LPCTSTR pszNumber[]={TEXT("��"),TEXT("Ҽ"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("½"),TEXT("��"),TEXT("��"),TEXT("��")};
	LPCTSTR pszWeiName[]={TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��")};

	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	bool bNeedFill=false;
	bool bNeedZero=false;
	UINT uTargetIndex=0,uSourceIndex=0;

	//�ַ�����
	UINT uItemLength=lstrlen(pszNumber[0]);
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת������
	for (UINT i=0;i<uSwitchLength;i++)
	{
		//��������
		WORD wNumberIndex=szSwitchScore[i]-TEXT('0');

		//�������
		if ((bNeedZero==true)&&(wNumberIndex!=0L))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszNumber[0],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//��������
		if (wNumberIndex!=0L)
		{
			_tcsncat(pszBuffer,pszNumber[wNumberIndex],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//����λ��
		if ((wNumberIndex!=0L)&&((uSwitchLength-i)>=2))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//�����ж�
		if ((bNeedZero==false)&&(wNumberIndex==0))
		{
			bNeedZero=true;
		}

		//��λ�ж�
		if ((bNeedFill==false)&&(wNumberIndex!=0))
		{
			bNeedFill=true;
		}

		//�λ��
		if (((uSwitchLength-i)==5)||((uSwitchLength-i)==9))
		{
			//����λ��
			if ((bNeedFill==true)&&(wNumberIndex==0L))
			{
				_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
			}

			//���ñ���
			bNeedZero=false;
			bNeedFill=false;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureTeller::CDlgInsureTeller() : CDialog(IDD_INSURE_TELLER)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureTeller::~CDlgInsureTeller()
{
}

void CDlgInsureTeller::UpDateView()//���½���
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//ת������
	TCHAR szControl[128]=TEXT("");
	m_DlgInsureItem.SwitchScoreFormat(pGlobalUserData->lUserInsure,3L,szControl,CountArray(szControl));
	//���ÿؼ�
	SetDlgItemText(IDC_EDIT_TELLER2,szControl);
	SetDlgItemText(IDC_EDIT_TELLER,"");
}

//�ؼ���
VOID CDlgInsureTeller::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDC_BUTTON_TELLER, m_btTakeScore);
	DDX_Control(pDX, IDC_BT_QUERY_TELLER, m_btQueryInfo);
	//�ؼ�����
	DDX_Control(pDX, IDC_EDIT_TELLER, m_edScore);
	DDX_Control(pDX, IDC_EDIT_TELLER2, m_edSelfScore);
	DDX_Control(pDX, IDC_TELLER_INSUREPWD, m_PasswordControl);
	DDX_Control(pDX, IDC_TELLER_NUM1, m_InsureTellerNum1);
	DDX_Control(pDX, IDC_TELLER_NUM2, m_InsureTellerNum2);
	DDX_Control(pDX, IDC_TELLER_NUM3, m_InsureTellerNum3);
	DDX_Control(pDX, IDC_TELLER_NUM4, m_InsureTellerNum4);
	DDX_Control(pDX, IDC_TELLER_NUM5, m_InsureTellerNum5);
	DDX_Control(pDX, IDC_TELLER_NUM6, m_InsureTellerNum6);
	DDX_Control(pDX, IDC_TELLER_NUM7, m_InsureTellerNum7);


	DDX_Control(pDX, IDC_TELLER1, m_Teller1);
	DDX_Control(pDX, IDC_TELLER2, m_Teller2);
	DDX_Control(pDX, IDC_TELLER3, m_Teller3);
	//DDX_Control(pDX, IDC_TELLER4, m_Teller4);
	DDX_Control(pDX, IDC_TELLER5, m_Teller5);
	DDX_Control(pDX, IDC_TELLER6, m_Teller6);
}

//��������
BOOL CDlgInsureTeller::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_edScore.LimitText(16L);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);

	CRect rcClient;
	GetClientRect(&rcClient);

	m_Teller1.MoveWindow(rcClient.left+24,rcClient.top+5,92,28);
	m_Teller2.MoveWindow(rcClient.left+24+92,rcClient.top+5,110,28);
	m_Teller3.MoveWindow(rcClient.left+24,rcClient.top+70,85,24);
	//m_Teller4.MoveWindow(rcClient.left+24+85,rcClient.top+76,330,14);
	m_Teller5.MoveWindow(rcClient.left+24,rcClient.top+110,85,24);
	m_Teller6.MoveWindow(rcClient.left+24,rcClient.top+180,85,24);
	GetDlgItem(IDC_SCORE_STRING)->MoveWindow(rcClient.left+85+24,rcClient.top+185,350,14);

	m_InsureTellerNum1.MoveWindow(rcClient.left+90,rcClient.top+142,55,24);
	m_InsureTellerNum2.MoveWindow(rcClient.left+90+55,rcClient.top+142,55,24);
	m_InsureTellerNum3.MoveWindow(rcClient.left+90+55*2,rcClient.top+142,55,24);
	m_InsureTellerNum4.MoveWindow(rcClient.left+90+55*3,rcClient.top+142,55,24);
	m_InsureTellerNum5.MoveWindow(rcClient.left+90+55*4,rcClient.top+142,45,24);
	m_InsureTellerNum6.MoveWindow(rcClient.left+90+55*4+45,rcClient.top+142,45,24);
	m_InsureTellerNum7.MoveWindow(rcClient.left+90+55*4+45*2,rcClient.top+142,60,24);

	m_edScore.MoveWindow(rcClient.left+24+85,rcClient.top+110,240,22,SWP_NOZORDER|SWP_NOMOVE);
	m_edSelfScore.MoveWindow(rcClient.left+24+85,rcClient.top+70,240,22,SWP_NOZORDER|SWP_NOMOVE);
	m_btTakeScore.MoveWindow(rcClient.left+153,rcClient.top+260,68,24);	
	//m_btQueryInfo.MoveWindow(rcClient.left+24+85+240+15,rcClient.top+70,68,24,SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE);
	//m_btQueryInfo.SetWindowText("��  ѯ");
	m_btTakeScore.SetWindowText("ȡ  ��");

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
	DeferWindowPos(hDwp,m_btQueryInfo,NULL,rcClient.left+24+85+240+15,rcClient.top+70-6,0,0,uFlags|SWP_NOSIZE);
	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();


	m_Teller1.SetCustomFont(true,false,false,true,-16);
	m_Teller2.SetCustomFont(true,false,false,true,-16);
	m_Teller3.SetCustomFont(true,false,false,true,-16);
	m_Teller4.SetCustomFont(true,false,false,false,-14);
	m_Teller5.SetCustomFont(true,false,false,true,-16);
	m_Teller6.SetCustomFont(true,false,false,true,-16);
	m_Teller7.SetCustomFont(true,false,false,false,-16);

	m_Teller1.SetBackGroundColor(RGB(125,125,125));
	m_Teller2.SetBackGroundColor(RGB(125,125,125));


	m_Teller1.SetHyperLinkTextColor(RGB(2,59,72),RGB(2,59,72),RGB(2,59,72));
	m_Teller2.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Teller3.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Teller4.SetHyperLinkTextColor(RGB(0,0,255),RGB(0,0,255),RGB(0,0,255));
	m_Teller5.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Teller6.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Teller7.SetHyperLinkTextColor(RGB(0,0,255),RGB(0,0,255),RGB(0,0,255));

	m_InsureTellerNum1.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum2.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum3.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum4.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum5.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum6.SetCustomFont(true,true,true,false,-14);
	m_InsureTellerNum7.SetCustomFont(true,true,true,false,-14);

	m_InsureTellerNum1.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum2.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum3.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum4.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum5.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum6.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTellerNum7.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));

	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
    UpDateView();
	return TRUE;
}

//ȷ����ť
VOID CDlgInsureTeller::OnOK()
{
	return;
}

//ȡ����ť
VOID CDlgInsureTeller::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureTeller::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_EDIT_TELLER);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		//��������
		if(lScore > pGlobalUserData->lUserInsure) 
			lScore = pGlobalUserData->lUserInsure;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_EDIT_TELLER,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_EDIT_TELLER,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}
//��ѯ
VOID CDlgInsureTeller::OnBnClickedQueryInfo()
{
	m_pDlgInsureMain->QueryUserInsureInfo();
}
//ȡ�ť
VOID CDlgInsureTeller::OnBnClickedTakeScore()
{
	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_EDIT_TELLER);
	SCORE lTakeScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//�����ж�
	if (lTakeScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("ȡ������Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	if (lTakeScore>pGlobalUserData->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ���Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//�����ж�
	if (szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
	}

	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTakeScore(lTakeScore,szInsurePass);

	return;
}


void CDlgInsureTeller::OnInsureTellerClick(UINT nID)
{
	if (nID>=IDC_TELLER_NUM1 && nID<=IDC_TELLER_NUM7)  // �ж�checkbox����Դ�ŷ�Χ������checkbox��Դ������
	{
		switch(nID)
		{
		case IDC_TELLER_NUM1:
			{
				m_edScore.SetWindowText("1000000");
				break;
			}
		case IDC_TELLER_NUM2:
			{
				m_edScore.SetWindowText("5000000");
				break;
			}
		case IDC_TELLER_NUM3:
			{
				m_edScore.SetWindowText("10000000");
				break;
			}
		case IDC_TELLER_NUM4:
			{
				m_edScore.SetWindowText("50000000");
				break;
			}
		case IDC_TELLER_NUM5:
			{
				m_edScore.SetWindowText("100000000");
				break;
			}
		case IDC_TELLER_NUM6:
			{
				m_edScore.SetWindowText("500000000");
				break;
			}
		case IDC_TELLER_NUM7:
			{
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				CString sCoin;
				sCoin.Format("%I64d",m_pUserInsureInfo->lUserInsure);
				m_edScore.SetWindowText(sCoin);
				break;
			}
		}	
	}
}

//�滭����
BOOL CDlgInsureTeller::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	CRect rcTop;
	rcTop.left = rcClient.left;
	rcTop.top = rcClient.top;
	rcTop.right = rcClient.right;
	rcTop.bottom = 38;
	pDCBuffer->FillSolidRect(&rcTop,RGB(125,125,125));

	//��ȡλ��
	CRect rcScore;
	m_edScore.GetWindowRect(&rcScore);

	//ת��λ��
	ScreenToClient(&rcScore);

	//�滭����
	//COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureTeller::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}


//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureSave::CDlgInsureSave() : CDialog(IDD_INSURE_SAVE)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureSave::~CDlgInsureSave()
{
}

void CDlgInsureSave::UpDateView()//���½���
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//ת������
	TCHAR szControl[128]=TEXT("");
	m_DlgInsureItem.SwitchScoreFormat(pGlobalUserData->lUserScore,3L,szControl,CountArray(szControl));
	SetDlgItemText(IDC_SCORE_SAVE2,szControl);
	SetDlgItemText(IDC_SCORE,"");
}


//�ؼ���
VOID CDlgInsureSave::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDC_BT_SAVE_SCORE, m_btSaveScore);
	DDX_Control(pDX, IDC_BT_QUERY_SAVE, m_btQueryInfo);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_SCORE_SAVE2, m_edSelfScore);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_INSURE_SAVENUM1, m_InsureSaveNum1);
	DDX_Control(pDX, IDC_INSURE_SAVENUM2, m_InsureSaveNum2);
	DDX_Control(pDX, IDC_INSURE_SAVENUM3, m_InsureSaveNum3);
	DDX_Control(pDX, IDC_INSURE_SAVENUM4, m_InsureSaveNum4);
	DDX_Control(pDX, IDC_INSURE_SAVENUM5, m_InsureSaveNum5);
	DDX_Control(pDX, IDC_INSURE_SAVENUM6, m_InsureSaveNum6);
	DDX_Control(pDX, IDC_INSURE_SAVENUM7, m_InsureSaveNum7);


	DDX_Control(pDX, IDC_SAVE1, m_Save1);
	DDX_Control(pDX, IDC_SAVE2, m_Save2);
	DDX_Control(pDX, IDC_SAVE3, m_Save3);
	DDX_Control(pDX, IDC_SAVE4, m_Save4);
	DDX_Control(pDX, IDC_SAVE5, m_Save5);
}

//��������
BOOL CDlgInsureSave::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_edScore.LimitText(16L);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//����λ��
	m_Save1.MoveWindow(rcClient.left+24,rcClient.top+5,92,28);
	m_Save2.MoveWindow(rcClient.left+24+92,rcClient.top+5,110,28);
	m_Save3.MoveWindow(rcClient.left+24,rcClient.top+70,85,24);
	m_Save4.MoveWindow(rcClient.left+24,rcClient.top+110,85,24);
	m_Save5.MoveWindow(rcClient.left+24,rcClient.top+180,85,24);
	GetDlgItem(IDC_SCORE_STRING)->MoveWindow(rcClient.left+24+85,rcClient.top+185,350,14);

	m_InsureSaveNum1.MoveWindow(rcClient.left+90,rcClient.top+142,55,24);
	m_InsureSaveNum2.MoveWindow(rcClient.left+90+55,rcClient.top+142,55,24);
	m_InsureSaveNum3.MoveWindow(rcClient.left+90+55*2,rcClient.top+142,55,24);
	m_InsureSaveNum4.MoveWindow(rcClient.left+90+55*3,rcClient.top+142,55,24);
	m_InsureSaveNum5.MoveWindow(rcClient.left+90+55*4,rcClient.top+142,45,24);
	m_InsureSaveNum6.MoveWindow(rcClient.left+90+55*4+45,rcClient.top+142,45,24);
	m_InsureSaveNum7.MoveWindow(rcClient.left+90+55*4+45*2,rcClient.top+142,60,24);
	m_edSelfScore.MoveWindow(rcClient.left+24+85,rcClient.top+70,240,22,SWP_NOZORDER|SWP_NOMOVE);
	m_edScore.MoveWindow(rcClient.left+24+85,rcClient.top+110,240,22,SWP_NOZORDER|SWP_NOMOVE);
	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
	DeferWindowPos(hDwp,m_btQueryInfo,NULL,rcClient.left+24+85+240+15,rcClient.top+70-6,0,0,uFlags|SWP_NOSIZE);
	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();


	//m_btQueryInfo.SetWindowText("��  ѯ");
	m_btSaveScore.MoveWindow(rcClient.left+153,rcClient.top+260,68,24);
	m_btSaveScore.SetWindowText("��  ��");

	m_Save1.SetCustomFont(true,false,false,true,-16);
	m_Save2.SetCustomFont(true,false,false,true,-16);
	m_Save3.SetCustomFont(true,false,false,true,-16);
	m_Save4.SetCustomFont(true,false,false,true,-16);
	m_Save5.SetCustomFont(true,false,false,true,-16);


	m_Save1.SetHyperLinkTextColor(RGB(2,59,72),RGB(2,59,72),RGB(2,59,72));
	m_Save2.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Save3.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Save4.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Save5.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));

	m_Save1.SetBackGroundColor(RGB(125,125,125));
	m_Save2.SetBackGroundColor(RGB(125,125,125));

	m_InsureSaveNum1.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum2.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum3.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum4.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum5.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum6.SetCustomFont(true,true,true,false,-14);
	m_InsureSaveNum7.SetCustomFont(true,true,true,false,-14);

	m_InsureSaveNum1.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum2.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum3.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum4.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum5.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum6.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureSaveNum7.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));

	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	UpDateView();

	return TRUE;
}

//ȷ����ť
VOID CDlgInsureSave::OnOK()
{
	return;
}

//ȡ����ť
VOID CDlgInsureSave::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureSave::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		//��������
		if(lScore > pGlobalUserData->lUserScore) 
			lScore = pGlobalUserData->lUserScore;
		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}
//��ѯ
VOID CDlgInsureSave::OnBnClickedQueryInfo()
{
	m_pDlgInsureMain->QueryUserInsureInfo();
}
//��ť
VOID CDlgInsureSave::OnBnClickedSaveScore()
{

	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	//��������
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lSaveScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//�����ж�
	if (lSaveScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	if (lSaveScore>pGlobalUserData->lUserScore)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����Я����Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//ִ�д��
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformSaveScore(lSaveScore);

	return;
}


void CDlgInsureSave::OnInsureSaveClick(UINT nID)
{
	if (nID>=IDC_INSURE_SAVENUM1 && nID<=IDC_INSURE_SAVENUM7)  // �ж�checkbox����Դ�ŷ�Χ������checkbox��Դ������
	{
		switch(nID)
		{
		case IDC_INSURE_SAVENUM1:
			{
				m_edScore.SetWindowText("1000000");
				break;
			}
		case IDC_INSURE_SAVENUM2:
			{
				m_edScore.SetWindowText("5000000");
				break;
			}
		case IDC_INSURE_SAVENUM3:
			{
				m_edScore.SetWindowText("10000000");
				break;
			}
		case IDC_INSURE_SAVENUM4:
			{
				m_edScore.SetWindowText("50000000");
				break;
			}
		case IDC_INSURE_SAVENUM5:
			{
				m_edScore.SetWindowText("100000000");
				break;
			}
		case IDC_INSURE_SAVENUM6:
			{
				m_edScore.SetWindowText("500000000");
				break;
			}
		case IDC_INSURE_SAVENUM7:
			{
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				CString sCoin;
				sCoin.Format("%I64d",m_pUserInsureInfo->lUserScore);
				m_edScore.SetWindowText(sCoin);
				break;
			}
		}	
	}
}

//�滭����
BOOL CDlgInsureSave::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	CRect rcTop;
	rcTop.left = rcClient.left;
	rcTop.top = rcClient.top;
	rcTop.right = rcClient.right;
	rcTop.bottom = 38;
	pDCBuffer->FillSolidRect(&rcTop,RGB(125,125,125));

	//��ȡλ��
	CRect rcScore;
	m_edScore.GetWindowRect(&rcScore);

	//ת��λ��
	ScreenToClient(&rcScore);

	//�滭����
	//COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureSave::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureTransfer::CDlgInsureTransfer() : CDialog(IDD_INSURE_TRANSFER)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureTransfer::~CDlgInsureTransfer()
{
}

void CDlgInsureTransfer::UpDateView()//���½���
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//ת������
	TCHAR szControl[128]=TEXT("");
	m_DlgInsureItem.SwitchScoreFormat(pGlobalUserData->lUserInsure,3L,szControl,CountArray(szControl));
	SetDlgItemText(IDC_EDIT_TRAN1,szControl);
	SetDlgItemText(IDC_SCORE,"");
	SetDlgItemText(IDC_NICKNAME,"");
}

//�ؼ���
VOID CDlgInsureTransfer::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_NICKNAME, m_edNickName);
	DDX_Control(pDX, IDC_EDIT_TRAN1,m_edSelfScore);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);

	DDX_Control(pDX, IDC_TRAN1, m_Tran1);
	DDX_Control(pDX, IDC_TRAN2, m_Tran2);
	DDX_Control(pDX, IDC_TRAN3, m_Tran3);
	DDX_Control(pDX, IDC_TRAN4, m_Tran4);
	DDX_Control(pDX, IDC_TRAN5, m_Tran5);
	DDX_Control(pDX, IDC_TRAN6, m_Tran6);
	//DDX_Control(pDX, IDC_SCORE_STRING, m_Tran7);

	DDX_Control(pDX, IDC_INSURE_TRANNUM1, m_InsureTranNum1);
	DDX_Control(pDX, IDC_INSURE_TRANNUM2, m_InsureTranNum2);
	DDX_Control(pDX, IDC_INSURE_TRANNUM3, m_InsureTranNum3);
	DDX_Control(pDX, IDC_INSURE_TRANNUM4, m_InsureTranNum4);
	DDX_Control(pDX, IDC_INSURE_TRANNUM5, m_InsureTranNum5);
	DDX_Control(pDX, IDC_INSURE_TRANNUM6, m_InsureTranNum6);

	DDX_Control(pDX, IDC_BT_TRANSFER_SCORE, m_btTransferScore);
	DDX_Control(pDX, IDC_BT_QUERY_TRANSFER, m_btQueryInfo);
}

//��������
BOOL CDlgInsureTransfer::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_edScore.LimitText(16L);
	m_edNickName.LimitText(LEN_NICKNAME-1);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);
	((CButton *)GetDlgItem(IDC_BY_ID))->SetCheck(1);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	GetDlgItem(IDC_BY_ID)->MoveWindow(133,48,70,22);
	GetDlgItem(IDC_BY_NAME)->MoveWindow(240,48,70,22);

	m_Tran1.MoveWindow(rcClient.left+24,rcClient.top+5,92,28);
	m_Tran2.MoveWindow(rcClient.left+24+92,rcClient.top+5,110,28);
	m_Tran3.MoveWindow(rcClient.left+24,rcClient.top+70,85,24);
	m_Tran4.MoveWindow(rcClient.left+24,rcClient.top+110,85,24);
	m_Tran5.MoveWindow(rcClient.left+24,rcClient.top+150,85,24);
	m_Tran6.MoveWindow(rcClient.left+24,rcClient.top+220,85,24);
	//m_Tran7.MoveWindow(rcClient.left+85,rcClient.top+220,150,14);
	GetDlgItem(IDC_SCORE_STRING)->MoveWindow(rcClient.left+24+85,rcClient.top+225,350,14);

	m_InsureTranNum1.MoveWindow(rcClient.left+90,rcClient.top+182,55,24);
	m_InsureTranNum2.MoveWindow(rcClient.left+90+55,rcClient.top+182,55,24);
	m_InsureTranNum3.MoveWindow(rcClient.left+90+55*2,rcClient.top+182,55,24);
	m_InsureTranNum4.MoveWindow(rcClient.left+90+55*3,rcClient.top+182,55,24);
	m_InsureTranNum5.MoveWindow(rcClient.left+90+55*4,rcClient.top+182,45,24);
	m_InsureTranNum6.MoveWindow(rcClient.left+90+55*4+45,rcClient.top+182,50,24);


	//����λ��
	m_edSelfScore.MoveWindow(rcClient.left+24+85,rcClient.top+70,240,22,SWP_NOZORDER|SWP_NOMOVE);
	m_edNickName.MoveWindow(rcClient.left+24+85,rcClient.top+110,240,22,SWP_NOZORDER|SWP_NOMOVE);
	m_edScore.MoveWindow(rcClient.left+24+85,rcClient.top+150,240,22,SWP_NOZORDER|SWP_NOMOVE);

	//m_btQueryInfo.MoveWindow(rcClient.left+24+85+240+15,rcClient.top+70,0,0,SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE);
	//m_btQueryInfo.SetWindowText("��  ѯ");

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
	DeferWindowPos(hDwp,m_btQueryInfo,NULL,rcClient.left+24+85+240+15,rcClient.top+70-6,0,0,uFlags|SWP_NOSIZE);
	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	m_btTransferScore.MoveWindow(rcClient.left+153,rcClient.top+260,68,24);
	m_btTransferScore.SetWindowText("ת  ��");

	m_Tran1.SetCustomFont(true,false,false,true,-16);
	m_Tran2.SetCustomFont(true,false,false,true,-16);
	m_Tran3.SetCustomFont(true,false,false,true,-16);
	m_Tran4.SetCustomFont(true,false,false,true,-16);
	m_Tran5.SetCustomFont(true,false,false,true,-16);
	m_Tran6.SetCustomFont(true,false,false,true,-16);

	m_Tran1.SetBackGroundColor(RGB(125,125,125));
	m_Tran2.SetBackGroundColor(RGB(125,125,125));


	m_Tran1.SetHyperLinkTextColor(RGB(2,59,72),RGB(2,59,72),RGB(2,59,72));
	m_Tran2.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Tran3.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Tran4.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Tran5.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));
	m_Tran6.SetHyperLinkTextColor(RGB(10,89,148),RGB(10,89,148),RGB(10,89,148));


	m_InsureTranNum1.SetCustomFont(true,true,true,false,-14);
	m_InsureTranNum2.SetCustomFont(true,true,true,false,-14);
	m_InsureTranNum3.SetCustomFont(true,true,true,false,-14);
	m_InsureTranNum4.SetCustomFont(true,true,true,false,-14);
	m_InsureTranNum5.SetCustomFont(true,true,true,false,-14);
	m_InsureTranNum6.SetCustomFont(true,true,true,false,-14);

	m_InsureTranNum1.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTranNum2.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTranNum3.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTranNum4.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTranNum5.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));
	m_InsureTranNum6.SetHyperLinkTextColor(RGB(121,120,120),RGB(121,120,120),RGB(121,120,120));


	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	UpDateView();

	return TRUE;
}

//ȷ����ť
VOID CDlgInsureTransfer::OnOK()
{
	//ת�˲���
	OnBnClickedTransferScore();

	return;
}

//ȡ����ť
VOID CDlgInsureTransfer::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureTransfer::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

		//��������
		if(lScore > m_pUserInsureInfo->lUserInsure) 
			lScore = m_pUserInsureInfo->lUserInsure;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}
//��ѯ
VOID CDlgInsureTransfer::OnBnClickedQueryInfo()
{
	m_pDlgInsureMain->QueryUserInsureInfo();
}
//ת�˰�ť
VOID CDlgInsureTransfer::OnBnClickedTransferScore()
{
	m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	//�����ж�
	if (m_pUserInsureInfo->lUserInsure < m_pUserInsureInfo->lTransferPrerequisite)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�����չ���Ϸ�ҵ���Ŀ�������ת������ %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		return;
	}
	//�󶨲���
	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	////��¼�ж�
	//if (pGlobalUserData->dwUserID==0L) return;
	//SCORE myTotalScore = pGlobalUserData->lUserScore + pGlobalUserData->lUserInsure;
	//if (myTotalScore > 1000000 && (!pGlobalUserData->cbMoorMachine || !pIndividualUserData->cbMoorPassPortID || !pIndividualUserData->cbMoorPhone))
	//{
	//	AfxGetMainWnd()->SendMessage(WM_SAFA_BIND,0,0);
	//	//������ʾ
	//	return;
	//}


	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lTransferScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//��ȡ�ǳ�
	CString strNickName;
	GetDlgItemText(IDC_NICKNAME,strNickName);

	//��ʽ�ǳ�
	strNickName.TrimLeft();
	strNickName.TrimRight();

	//�ǳ��ж�
	if (strNickName.GetLength()==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		if(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck()==BST_CHECKED)
			Information.ShowMessageBox(TEXT("������Ҫ���͵�����ǳƣ�"),MB_ICONERROR,30);
		else
			Information.ShowMessageBox(TEXT("������Ҫ���͵����ID��"),MB_ICONERROR,30);

		//���ý���
		m_edNickName.SetFocus();

		return;
	}

	//ID���ж�
	if(((CButton *)GetDlgItem(IDC_BY_ID))->GetCheck()==BST_CHECKED)
	{
		int nlen = strNickName.GetLength();
		for(int i=0; i<nlen; i++)
		{
			if(strNickName[i] < '0' || strNickName[i] > '9')
			{
				//��ʾ��Ϣ
				CInformation Information(this);
				Information.ShowMessageBox(TEXT("��������ȷ�����ID��"),MB_ICONERROR,30);

				//���ý���
				m_edNickName.SetFocus();
				return;
			}
		}
	}

	//�����ж�
	if (lTransferScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���͵���Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore>m_pUserInsureInfo->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ���Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore<m_pUserInsureInfo->lTransferPrerequisite /*1*/)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�ӱ��չ�ת�˵���Ϸ����Ŀ�������� %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//�����ж�
	if (szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
	}
	
	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTransferScore(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck(),strNickName,lTransferScore,szInsurePass);

	//���ý���
	//m_PasswordControl.SetFocus();
	//m_PasswordControl.SetUserPassword(TEXT(""));

	return;
}

//�滭����
BOOL CDlgInsureTransfer::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	CRect rcTop;
	rcTop.left = rcClient.left;
	rcTop.top = rcClient.top;
	rcTop.right = rcClient.right;
	rcTop.bottom = 38;
	pDCBuffer->FillSolidRect(&rcTop,RGB(125,125,125));

	//��ȡλ��
	CRect rcScore;
	CRect rcNickName;
	m_edScore.GetWindowRect(&rcScore);
	m_edNickName.GetWindowRect(&rcNickName);

	//ת��λ��
	ScreenToClient(&rcScore);
	ScreenToClient(&rcNickName);

	//�滭����
	COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);
	//pDCBuffer->Draw3dRect(rcNickName.left-6,rcNickName.top-5,rcNickName.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureTransfer::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CDlgInsureTransfer::OnBnClickedById()
{
	// TODO: Add your control notification handler code here
	//GetDlgItem(IDC_TRANSFER_TYPE_TIP)->SetWindowText(TEXT("������� I D��"));
	//m_Tran4.SetWindowText("�û� ID��");
	//m_Tran4.Invalidate(true);
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}

void CDlgInsureTransfer::OnBnClickedByName()
{
	// TODO: Add your control notification handler code here
	//m_Tran4.SetWindowText("�û��ǳƣ�");
	//m_Tran4.Invalidate(true);
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}

void CDlgInsureTransfer::OnInsureTransferClick(UINT nID)
{
	if (nID>=IDC_INSURE_TRANNUM1 && nID<=IDC_INSURE_TRANNUM6)  // �ж�checkbox����Դ�ŷ�Χ������checkbox��Դ������
	{
		switch(nID)
		{
		case IDC_INSURE_TRANNUM1:
			{
				m_edScore.SetWindowText("1000000");
				break;
			}
		case IDC_INSURE_TRANNUM2:
			{
				m_edScore.SetWindowText("5000000");
				break;
			}
		case IDC_INSURE_TRANNUM3:
			{
				m_edScore.SetWindowText("10000000");
				break;
			}
		case IDC_INSURE_TRANNUM4:
			{
				m_edScore.SetWindowText("50000000");
				break;
			}
		case IDC_INSURE_TRANNUM5:
			{
				m_edScore.SetWindowText("100000000");
				break;
			}
		case IDC_INSURE_TRANNUM6:
			{
				m_edScore.SetWindowText("500000000");
				break;
			}
		}	
	}
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//���캯��
CBankLogDlg::CBankLogDlg() : CDialog(IDD_DIALOG_INSURE_LOG)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CBankLogDlg::~CBankLogDlg()
{
}

void CBankLogDlg::UpDateView()//���½���
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//ת������
	//TCHAR szControl[128]=TEXT("");
	//m_DlgInsureItem.SwitchScoreFormat(pGlobalUserData->lUserInsure,3L,szControl,CountArray(szControl));
	//SetDlgItemText(IDC_EDIT_TRAN1,szControl);
	//SetDlgItemText(IDC_SCORE,"");
	//SetDlgItemText(IDC_NICKNAME,"");
}

//�ؼ���
VOID CBankLogDlg::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX,IDC_BUTTON_FIRST,m_bFirstPage);
	DDX_Control(pDX,IDC_BUTTON_BEFORE,m_bBeforePage);
	DDX_Control(pDX,IDC_BUTTON_NEXT,m_bNextPage);
	DDX_Control(pDX,IDC_BUTTON_LAST,m_bLastPage);
	DDX_Control(pDX,IDC_BUTTON_QUERY,m_bQuery);

	DDX_Control(pDX,IDC_GROUP_INSURELOG,m_gbLog);
	DDX_Control(pDX,IDC_LIST_TRANSFER_LOG,m_LogList);
	DDX_Control(pDX,IDC_COMBO_LOGDATA,m_boxLogDate);

	DDX_Control(pDX, IDC_STATIC_LOGTIP, m_BankLogTip);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_BankLogPage);
	DDX_Control(pDX, IDC_STATIC_LOGDATE, m_BankLogDate);
}

//��������
BOOL CBankLogDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);
	m_gbLog.SetBorderColor(RGB(84,141,200));
	m_BankLogTip.ShowWindow(SW_HIDE);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	m_gbLog.MoveWindow(rcClient.left+5,rcClient.top,483,300+15);
	int nHeightSpace = 30;

	m_BankLogDate.MoveWindow(rcClient.left+7,rcClient.top+20,30,20);
	m_bQuery.MoveWindow(rcClient.left+220,rcClient.top+18,62,22);
	m_boxLogDate.MoveWindow(rcClient.left+7+30+3,rcClient.top+20,92,200);

	m_LogList.MoveWindow(rcClient.left+7+5,rcClient.top+22+25,470,220);

	m_bFirstPage.MoveWindow(rcClient.left+10,rcClient.top+22+25+200+30,62,22);
	m_bBeforePage.MoveWindow(rcClient.left+10+62+8,rcClient.top+22+25+200+30,62,22);
	m_bNextPage.MoveWindow(rcClient.left+10+(62+8)*2,rcClient.top+22+25+200+30,62,22);
	m_bLastPage.MoveWindow(rcClient.left+10+(62+8)*3,rcClient.top+22+25+200+30,62,22);
	m_BankLogPage.MoveWindow(rcClient.left+10+(62+8)*4+5,rcClient.top+22+25+200+35,60,22);

	m_BankLogTip.SetCustomFont(true,false,false,false,-12);
	m_BankLogPage.SetCustomFont(true,false,false,false,-12);
	m_BankLogDate.SetCustomFont(true,false,false,false,-12);

	//m_BankOldPwd.SetBackGroundColor(RGB(231,231,247));
	//m_BankNewPwd.SetBackGroundColor(RGB(231,231,247));
	//m_BankConfirmPwd.SetBackGroundColor(RGB(231,231,247));

	m_BankLogTip.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_BankLogPage.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));
	m_BankLogDate.SetHyperLinkTextColor(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0));

	CTime TimeNow = CTime::GetCurrentTime();
	CString sNowTime;
	sNowTime = TimeNow.Format("%Y-%m-%d");
	m_boxLogDate.AddString(sNowTime);
	CTimeSpan sub(-1,0,0,0);
	for (int i = 0;i<6;i++)
	{
		TimeNow += sub;
		CString sTimeTmp = TimeNow.Format("%Y-%m-%d");
		m_boxLogDate.AddString(sTimeTmp);
	}
	m_boxLogDate.SetCurSel(0);

	//SkinSB_Init(m_LogList,CGameFrame::m_bmScroll);
	m_gbLog.SetBorderColor(RGB(84,141,200));
	//m_LogList.SetTextBkColor(RGB(255,0,0));
	m_LogList.SetBkColor(RGB(236,237,255));
	m_LogList.SetItemHeight(22);
	//m_gbLog.SetTextColor(RGB(0,0,255));

	m_LogList.SetExtendedStyle(/*LVS_EX_FLATSB|*/LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES/*|LVS_OWNERDRAWFIXED*/);
	m_LogList.ModifyStyle(0,LVS_NOSCROLL);
	m_LogList.ModifyStyle(0,LVS_EX_TRACKSELECT);
	//m_LogList.SetFont()
	m_LogList.SetCustomColumn(5);

	m_LogList.InsertColumn(0,TEXT("���"),LVCFMT_LEFT,0,0);
	m_LogList.InsertColumn(1,TEXT("�Է��û���"),LVCFMT_LEFT,75,1);
	m_LogList.InsertColumn(2,TEXT("����"),LVCFMT_LEFT,36,2);
	m_LogList.InsertColumn(3,TEXT("��������"),LVCFMT_LEFT,75,3);
	m_LogList.InsertColumn(4,TEXT("��������"),LVCFMT_LEFT,105,4);
	m_LogList.InsertColumn(5,TEXT("����"),LVCFMT_LEFT,74,4);
	//m_LogList.SetItemHeight(40);
	//m_LogList.SetListColor(RGB(240,238,255),RGB(0,255,0),RGB(236,237,255));
	m_LogList.SetListColor(RGB(10,10,10),RGB(0,255,0),RGB(236,237,255),RGB(101,101,255));
	CFont Font;
	//Font.CreateFont(-12,0,0,0,0,0,0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));
	//Font.CreateFont(-16,0,0,0,0,0,0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));
	//Font.CreatePointFont(140,TEXT("����"));
	//m_LogList.SetFont(&Font);
	//m_PasswordControl.SetUserPassword(m_pDlgInsureMain->m_szSaveInsurePass);
	UpDateView();

	return TRUE;
}

//ȷ����ť
VOID CBankLogDlg::OnOK()
{
	//ת�˲���
	OnBnClickedButtonQuery();

	return;
}

//ȡ����ť
VOID CBankLogDlg::OnCancel()
{
	return;
}


//�滭����
BOOL CBankLogDlg::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	pDC->FillSolidRect(&rcClient,RGB(222,240,253));	
	m_gbLog.SetStaticBack(pDC, this);
	m_gbLog.Draw(pDC);

	CRect rcList;
	m_LogList.GetWindowRect(&rcList);
	ScreenToClient(rcList);
	rcList.left-=1;
	rcList.right+=1;
	rcList.top-=1;
	rcList.bottom+=1;
	pDC->Draw3dRect(rcList,RGB(157,167,218),RGB(157,167,218));	


	return TRUE;
}

//�ؼ���ɫ
HBRUSH CBankLogDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CBankLogDlg::OnBnClickedButtonQuery()
{
	//m_bQuery.EnableWindow(FALSE);
	//m_bFirstPage.EnableWindow(FALSE);
	//m_bBeforePage.EnableWindow(FALSE);
	//m_bNextPage.EnableWindow(FALSE);
	//m_bLastPage.EnableWindow(FALSE);

	m_lLogIndex=0;
	m_lRecordCount = 0;
	m_lPageCount = 0;
	m_lCurrentPage = 0;

	m_LogList.DeleteAllItems();
	int nDays = m_boxLogDate.GetCurSel();
	m_pDlgInsureMain->SendBankTransferLog(1,nDays);
}

VOID CBankLogDlg::SetTransPages(int nPageCount,int nCurentPage,int nRecordCount)
{
	m_lPageCount = nPageCount;
	m_lCurrentPage = nCurentPage;
	m_lRecordCount = nRecordCount;

	if (m_lPageCount > m_lCurrentPage)
	{
		m_bNextPage.EnableWindow(TRUE);
		m_bLastPage.EnableWindow(TRUE);
		if (m_lCurrentPage>1)
		{
			m_bFirstPage.EnableWindow(TRUE);
			m_bBeforePage.EnableWindow(TRUE);
		}
		else
		{
			m_bFirstPage.EnableWindow(FALSE);
			m_bBeforePage.EnableWindow(FALSE);
		}
	}
	else
	{
		if (m_lPageCount == m_lCurrentPage && m_lCurrentPage>1)
		{
			m_bFirstPage.EnableWindow(TRUE);
			m_bBeforePage.EnableWindow(TRUE);
			m_bNextPage.EnableWindow(FALSE);
			m_bLastPage.EnableWindow(FALSE);
		}
		else
		{
			m_bFirstPage.EnableWindow(FALSE);
			m_bBeforePage.EnableWindow(FALSE);
			m_bNextPage.EnableWindow(FALSE);
			m_bLastPage.EnableWindow(FALSE);

		}
	}

	CString sPages;
	sPages.Format("��%.2d/%.2dҳ",nCurentPage,nPageCount);
	//	TCHAR szPageInfo[64];
	//	_snprintf(szPageInfo,sizeof(szPageInfo),TEXT("��%.2d/%.2dҳ"),m_lCurrentPage,m_lPageCount);
	SetDlgItemText(IDC_STATIC_PAGE,sPages);
}

void CBankLogDlg::InsertTransferLog( CMD_GP_BankRecordItem * pBankTransferLogResult )
{
	CString strTemp;
	strTemp.Format("%d",pBankTransferLogResult->dwIndex);
	m_LogList.InsertItem(m_lLogIndex,(LPCTSTR)strTemp);

	//m_LogList.SetItemText(m_lLogIndex,0,(LPCTSTR)strTemp);

	m_LogList.SetItemText(m_lLogIndex,1,pBankTransferLogResult->szNickName);
	if (pBankTransferLogResult->bType == 1)
	{
		m_LogList.SetItemText(m_lLogIndex,2,TEXT("����"));
	}
	else if (pBankTransferLogResult->bType == 2)
	{
		m_LogList.SetItemText(m_lLogIndex,2,TEXT("����"));
	}

	strTemp.Format("%I64d",pBankTransferLogResult->lTransferCount);
	m_LogList.SetItemText(m_lLogIndex,3,strTemp);

	CTime tm=pBankTransferLogResult->tTransferDate;
	strTemp = tm.Format("%Y-%m-%d %H:%M");
	//OutputDebugString(TEXT("sTime:") +str);

	m_LogList.SetItemText(m_lLogIndex,4,strTemp);

	m_LogList.SetItemText(m_lLogIndex,5,"����");

	m_LogList.SetItemData(m_lLogIndex,pBankTransferLogResult->dwUserID);

	//strTemp.Format("%d",pBankTransferLogResult->dwTagGameID);

	//m_LogList.SetItemText(m_lLogIndex,5,strTemp);
	//strTemp = tm.Format("%Y-%m-%d %H:%M:%S");
	//m_LogList.SetItemText(m_lLogIndex,6,strTemp);

	m_lLogIndex++;

	return;

}

//VOID CBankLogDlg::TransferLogFinish( CMD_GP_BankTransferLogFinish * pBankTransferLogFinish )
//{
//	m_lRecordCount = pBankTransferLogFinish->lRecordCount;
//	m_lPageCount = pBankTransferLogFinish->lPageCount;
//	m_lCurrentPage = pBankTransferLogFinish->lPage;
//	TCHAR szPageInfo[64];
//	_snprintf(szPageInfo,sizeof(szPageInfo),TEXT("��%.2d/%.2dҳ"),m_lCurrentPage,m_lPageCount);
//	SetDlgItemText(STATIC,szPageInfo);
//
//	m_bQuery.EnableWindow(TRUE);
//	m_bFirstPage.EnableWindow(TRUE);
//	m_bBeforePage.EnableWindow(TRUE);
//	m_bNextPage.EnableWindow(TRUE);
//	m_bLastPage.EnableWindow(TRUE);
//
//	return;
//}

void CBankLogDlg::OnBnClickedButtonFirst()
{
	//m_bQuery.EnableWindow(FALSE);
	//m_bFirstPage.EnableWindow(FALSE);
	//m_bBeforePage.EnableWindow(FALSE);
	//m_bNextPage.EnableWindow(FALSE);
	//m_bLastPage.EnableWindow(FALSE);

	m_lLogIndex=0;
	m_lCurrentPage = 1;
	m_LogList.DeleteAllItems();
	int nDays = m_boxLogDate.GetCurSel();
	m_pDlgInsureMain->SendBankTransferLog(m_lCurrentPage,nDays);
}

void CBankLogDlg::OnBnClickedButtonLast()
{
	m_lLogIndex=0;
	m_lCurrentPage = m_lPageCount;
	m_LogList.DeleteAllItems();
	int nDays = m_boxLogDate.GetCurSel();
	m_pDlgInsureMain->SendBankTransferLog(m_lCurrentPage,nDays);
}

void CBankLogDlg::OnBnClickedButtonNext()
{
	m_lLogIndex=0;
	m_lCurrentPage +=1;
	m_LogList.DeleteAllItems();
	int nDays = m_boxLogDate.GetCurSel();
	m_pDlgInsureMain->SendBankTransferLog(m_lCurrentPage,nDays);
}

void CBankLogDlg::OnBnClickedButtonBefore()
{
	m_lLogIndex=0;
	m_lCurrentPage -=1;
	m_LogList.DeleteAllItems();
	int nDays = m_boxLogDate.GetCurSel();
	m_pDlgInsureMain->SendBankTransferLog(m_lCurrentPage,nDays);
}

void CBankLogDlg::OnNMDblclkListTransferLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;  
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);	
	//��ȡѡ�еĵ�һ��λ��
	POSITION p=m_LogList.GetFirstSelectedItemPosition();
	if (p != NULL )
	{
		if (pNMListView->iSubItem ==5)
		{
			//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
			int index = m_LogList.GetNextSelectedItem(p);
			//���ѡ�е�����
			DWORD dwUserID = m_LogList.GetItemData(index); //�Է�id
			CString strNumber=m_LogList.GetItemText(index,0); //���
			CString strTagAccounts=m_LogList.GetItemText(index,1); //�Է��ǳ�
			//CString strTagGameID=m_LogList.GetItemText(index,5);
			CString strType=m_LogList.GetItemText(index,2);
			CString strTransferCount=m_LogList.GetItemText(index,3);
			CString strTransferTime=m_LogList.GetItemText(index,4);

			CInsureSuccess  SuccessDlg;

			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();


			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(_atoi64(strTransferCount),szString,CountArray(szString));
			if ("����" == strType)
			{	
				SuccessDlg.SetInfo(pGlobalUserData->dwGameID,pGlobalUserData->szNickName,dwUserID,strTagAccounts.GetBuffer(strTagAccounts.GetLength()),strTransferTime.GetBuffer(strTransferTime.GetLength()),atoi(strNumber),
					_atoi64(strTransferCount), szString);
			}
			else if ("����" == strType)
			{		
				SuccessDlg.SetInfo(dwUserID,strTagAccounts.GetBuffer(strTagAccounts.GetLength()),pGlobalUserData->dwGameID,pGlobalUserData->szNickName,strTransferTime.GetBuffer(strTransferTime.GetLength()),atoi(strNumber),
					_atoi64(strTransferCount), szString);
			}

			//������Դ
			HINSTANCE hInstResourceClient = AfxGetResourceHandle();
			AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
			SuccessDlg.DoModal();
			AfxSetResourceHandle(hInstResourceClient);
		}
		

		//if(!::IsWindow(m_DetailedLog.m_hWnd))
		//{
		//	m_DetailedLog.Create(IDD_BANK_DETAILED_LOG);
		//}
		//m_DetailedLog.ShowWindow(TRUE);
		//m_DetailedLog.SetTransferInfo((LPCTSTR)strNumber,(LPCTSTR)strTagAccounts,(LPCTSTR)strTagGameID,(LPCTSTR)strType,(LPCTSTR)strTransferCount,(LPCTSTR)strTransferTime);

	}


	*pResult = 0;
}

BOOL CBankLogDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////////////


//�ؼ���ʶ
#define IDC_BROWSERITEM					100									//����ؼ�

CDlgBrowserItem::CDlgBrowserItem(): CDialog(IDD_DLG_SERVICETRANSFER)
{
	//���ñ���

	return;
}

CDlgBrowserItem::~CDlgBrowserItem()
{
}

VOID CDlgBrowserItem::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����

}

BOOL CDlgBrowserItem::OnInitDialog()
{
	__super::OnInitDialog();
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�����ؼ�
	m_WebPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcClient,this,IDC_BROWSERITEM);

	if (m_szServiceUrl[0]!=0)
	{
		//�����ַ
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		TCHAR szBrowseUrl[256]=TEXT("");
		_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/%s"),pGlobalServer->GetPlatformServer(3),m_szServiceUrl);

		//���ӵ�ַ
		m_WebPublicize.Navigate(szBrowseUrl,NULL,NULL,NULL,NULL);
	}

	return TRUE;
}
//���÷���
VOID CDlgBrowserItem::InitService(LPCTSTR pszItemName, LPCTSTR pszServiceUrl)
{
	//���ñ���
	lstrcpyn(m_szItemName,pszItemName,CountArray(m_szItemName));
	lstrcpyn(m_szServiceUrl,pszServiceUrl,CountArray(m_szServiceUrl));

	return;
}
//λ����Ϣ
VOID CDlgBrowserItem::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�ƶ��ؼ�
	if (m_WebPublicize.m_hWnd!=NULL)
	{
		m_WebPublicize.SetWindowPos(NULL,0,0,rcClient.Width(),rcClient.Height(),SWP_NOZORDER);
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureMain::CDlgInsureMain() : CSkinDialog(IDD_INSURE_MAIN)
{
	//�������
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bQueryTransferLog = false;

	//���ñ���
	m_bInitInfo=false;
	m_cbInsureMode=INSURE_SAVE;
	ZeroMemory(&m_UserInsureInfo,sizeof(m_UserInsureInfo));
	_sntprintf(m_szSaveInsurePass,CountArray(m_szSaveInsurePass),TEXT(""));
	m_nBeginTop = 44;
	m_nHSpace = 40;
	m_nLSpace = 35;
	m_nSelIndex = 0;
	m_bInit = false;
	return;
}

//��������
CDlgInsureMain::~CDlgInsureMain()
{
	m_BankFont.DeleteObject();
	m_BankFontInfo.DeleteObject();

	if (m_DlgInsureTeller.m_hWnd!=NULL)
		m_DlgInsureTeller.DestroyWindow();

	if (m_DlgInsureSave.m_hWnd!=NULL)
		m_DlgInsureSave.DestroyWindow();

	if (m_DlgInsureTransfer.m_hWnd!=NULL)
		m_DlgInsureTransfer.DestroyWindow();

	if (m_DlgBrowserItem.m_hWnd!=NULL)
		m_DlgBrowserItem.DestroyWindow();

	if (m_LogDlg.m_hWnd!=NULL)
		m_LogDlg.DestroyWindow();
}

void CDlgInsureMain::OnSelchangedTreeSafa(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDlgInsureMain::OnClickTreeSafa(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//InitSubDlgs();
	UINT uFlags;
	CString sTmp;
	int nType = 0;
	int nID;
	CPoint pt(::GetMessagePos());
	m_treeDlg.ScreenToClient(&pt);
	HTREEITEM hItem = m_treeDlg.HitTest(pt, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		nID = (int)m_treeDlg.GetItemData(hItem);
	}
	SwitchInsureModeView(nID);
	/*if(nID == 0)
	{
		m_pDialog[0]->ShowWindow(SW_SHOW);
		m_pDialog[1]->ShowWindow(SW_HIDE);
		m_pDialog[2]->ShowWindow(SW_HIDE);
		m_pDialog[3]->ShowWindow(SW_HIDE);
		m_pDialog[4]->ShowWindow(SW_HIDE);
		m_treeDlg.SelectItem(sub_son[0]);
	}
	else if(nID == 1)
	{
		m_pDialog[0]->ShowWindow(SW_HIDE);
		m_pDialog[1]->ShowWindow(SW_SHOW);
		m_pDialog[2]->ShowWindow(SW_HIDE);
		m_pDialog[3]->ShowWindow(SW_HIDE);
		m_pDialog[4]->ShowWindow(SW_HIDE);
		m_treeDlg.SelectItem(sub_son[1]);
	}
	else if(nID == 2)
	{
		m_pDialog[0]->ShowWindow(SW_HIDE);
		m_pDialog[1]->ShowWindow(SW_HIDE);
		m_pDialog[2]->ShowWindow(SW_SHOW);
		m_pDialog[3]->ShowWindow(SW_HIDE);
		m_pDialog[4]->ShowWindow(SW_HIDE);
		m_treeDlg.SelectItem(sub_son[2]);
	}
	else if(nID == 3)
	{
		m_pDialog[0]->ShowWindow(SW_HIDE);
		m_pDialog[1]->ShowWindow(SW_HIDE);
		m_pDialog[2]->ShowWindow(SW_HIDE);
		m_pDialog[3]->ShowWindow(SW_SHOW);
		m_pDialog[4]->ShowWindow(SW_HIDE);
		m_treeDlg.SelectItem(sub_son[3]);
	}
	else if(nID == 4)
	{
		m_pDialog[0]->ShowWindow(SW_HIDE);
		m_pDialog[1]->ShowWindow(SW_HIDE);
		m_pDialog[2]->ShowWindow(SW_HIDE);
		m_pDialog[3]->ShowWindow(SW_HIDE);
		m_pDialog[4]->ShowWindow(SW_SHOW);
		m_treeDlg.SelectItem(sub_son[4]);
	}*/
	*pResult = 0;
}

//�ؼ���
VOID CDlgInsureMain::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	//DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	//DDX_Control(pDX, IDC_BT_QUERY_INFO, m_btQueryInfo);
	DDX_Control(pDX, IDC_TREE_SAFA, m_treeDlg);
	
}

//��Ϣ����
BOOL CDlgInsureMain::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	if (pMsg->message==WM_LBUTTONDOWN)
	{
		ScreenToClient(&pMsg->pt);
		for(int n=0; n < 4; ++n)
		{
			if(m_BankRect[n].PtInRect(pMsg->pt))
			{
				if (m_nSelIndex == n)
				{
					break;
				}
				//ȥ��ԭ����
				CRect rtOld(m_BankRect[m_nSelIndex]);
				rtOld.right += 32;
				InvalidateRect(rtOld,TRUE);
				m_nSelIndex = n;
				CRect rtNew(m_BankRect[n]);
				rtNew.right += 32;
				InvalidateRect(rtNew,TRUE);
				SwitchInsureModeView(n+1);
			}
		}
	}
	return __super::PreTranslateMessage(pMsg);
}

//��������
BOOL CDlgInsureMain::OnInitDialog()
{
	__super::OnInitDialog();

	MoveWindow(0,0,633,403);
	//���ñ���
	SetWindowText(TEXT("��Ϸ����"));

	//������Դ
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	//m_TabControl.SetItemSize(CSize(100,25));
	m_treeDlg.MoveWindow(14,40,115,315);
	m_treeDlg.ShowWindow(SW_HIDE);
	m_treeDlg.SetItemHeight(22);

	//CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	//tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//m_UserInsureInfo.lUserInsure = pGlobalUserData->lUserInsure;
	//m_UserInsureInfo.lUserScore = pGlobalUserData->lUserScore;

	//m_treeDlg.SetItemColor(RGB(166, 194, 231),RGB(255,255,255),RGB(255,255,255),RGB(166, 194, 231),true);
	parent_son[0] = m_treeDlg.InsertItem(" ������Ϣ",0,1,TVI_ROOT,TVI_LAST);
//	parent_son[1] = m_treeDlg.InsertItem(" ���а�ȫ",0,1,TVI_ROOT,TVI_LAST);
//	sub_son[0]=m_treeDlg.InsertItem("    ������ҳ",0,1,parent_son[0],TVI_LAST);
	sub_son[1]=m_treeDlg.InsertItem("    ȡ��",1,1,parent_son[0],TVI_LAST);
	sub_son[2]=m_treeDlg.InsertItem("    ���",2,1,parent_son[0],TVI_LAST);
	sub_son[3]=m_treeDlg.InsertItem("    ����",3,1,parent_son[0],TVI_LAST);
	sub_son[4]=m_treeDlg.InsertItem("  ������ϸ",4,1,parent_son[0],TVI_LAST);

	//m_treeDlg.SetItemData(sub_son[0],0);
	m_treeDlg.SetItemData(sub_son[1],1);
	m_treeDlg.SetItemData(sub_son[2],2);
	m_treeDlg.SetItemData(sub_son[3],3);
	m_treeDlg.SetItemData(sub_son[4],4);
	m_treeDlg.SelectItem(sub_son[1]);

	//��ؼ�
	m_DlgInsureSave.m_pDlgInsureMain=this;
	m_DlgInsureSave.m_pUserInsureInfo=&m_UserInsureInfo;
	//ȡ�ؼ�
	m_DlgInsureTeller.m_pDlgInsureMain=this;
	m_DlgInsureTeller.m_pUserInsureInfo=&m_UserInsureInfo;

	//ת�˿ؼ�
	m_DlgInsureTransfer.m_pDlgInsureMain=this;
	m_DlgInsureTransfer.m_pUserInsureInfo=&m_UserInsureInfo;

	//ת�˼�¼�ؼ�
	m_DlgBrowserItem.m_pDlgInsureMain=this;

	//ת�˼�¼�ؼ�
	m_LogDlg.m_pDlgInsureMain=this;

	//�����ǩ
	//m_TabControl.InsertItem(INSURE_SAVE,TEXT(" �����ȡ�� "));
	//m_TabControl.InsertItem(INSURE_TRANSFER,TEXT(" ������Ϸ�� "));
	//m_TabControl.InsertItem(INSURE_TRANSFERRECORD,TEXT("ת�˼�¼"));

	//���ð�ť
	//HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	//m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);

	//��ѯ��Ϣ
	QueryUserInsureInfo();

	//MoveWindow(0,0,591,374);

	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	////������Դ
	//CPngImageSB ImageInsureInfo;
	//ImageInsureInfo.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INFO_FRAME"));

	////�滭��Ϣ
	//INT nYPosInfo=86L;
	//INT nXPosInfo=(rcClient.Width()-ImageInsureInfo.GetWidth())/2L+350;

	////��ȡλ��
	//CRect rcButton(0,0,0,0);
	//m_TabControl.MoveWindow(26,39,435,27,SWP_NOZORDER|SWP_NOMOVE);
	//m_btQueryInfo.GetWindowRect(&rcButton);
	//m_btQueryInfo.MoveWindow(nXPosInfo,nYPosInfo,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

	//��ȡģʽ
	SwitchInsureModeView(1);


	//�����
	for (int n=0; n < 4; ++n)
	{
		m_BankRect[n] = CRect(m_nLSpace-7,m_nBeginTop + m_nHSpace * (n+1)-3, m_nLSpace+68, m_nBeginTop + m_nHSpace * (n+1)+17);
	}
	m_BankFont.CreateFont(18, 0, 0, 0, 700, FALSE, FALSE, FALSE, GB2312_CHARSET,  
		OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,  
		DEFAULT_PITCH, TEXT("����"));
	m_BankFontInfo.CreateFont(14, 0, 0, 0, 700, FALSE, FALSE, FALSE, GB2312_CHARSET,  
		OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,  
		DEFAULT_PITCH, TEXT("����"));
	m_ImageSelBank.LoadFromResource(GetModuleHandle(SHARE_CONTROL_DLL_NAME),IDB_IMAGE_SELBANK);
	m_bInit = true;
	///////////////////////////////
	return FALSE;
}

VOID CDlgInsureMain::OnCancel()
{
	ShowWindow(SW_HIDE);
}

//ȷ����ť
VOID CDlgInsureMain::OnOK()
{
	return;
	//Ĭ�϶���
	switch (m_cbInsureMode)
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			m_DlgInsureSave.OnOK();
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			m_DlgInsureTransfer.OnOK();
			break;
		}
	}

	return;
}

//�滭��Ϣ
VOID CDlgInsureMain::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//�����
	DrawBankTab(pDC, nWidth, nHeight);

/*	//��ȡλ��
	CRect rcTabControl;
	m_TabControl.GetWindowRect(&rcTabControl);

	//ת��λ��
	ScreenToClient(&rcTabControl);

	//�滭����
	INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	pDC->FillSolidRect(nLBorder,rcTabControl.bottom-1L,nWidth-nLBorder-nRBorder,1,RGB(145,168,183));

	//������Դ
	CPngImageSB ImageInsureInfo;
	ImageInsureInfo.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INFO_FRAME"));

	//�滭��Ϣ
	INT nYPosInfo=75L;
	INT nXPosInfo=(nWidth-ImageInsureInfo.GetWidth())/2L;
	ImageInsureInfo.DrawImage(pDC,nXPosInfo,nYPosInfo,ImageInsureInfo.GetWidth(),ImageInsureInfo.GetHeight(),0,0);

	//��ʾ����ˢ�°�ť
	if (m_cbInsureMode != INSURE_TRANSFERRECORD) m_btQueryInfo.ShowWindow(SW_SHOW);
*/
	//������Ϣ
	if (m_bInitInfo==true)
	{/*
		//������Դ
		CPngImageSB ImageInsureIcon;
		ImageInsureIcon.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INSURE_ICON"));

		//�滭��־
		ImageInsureIcon.DrawImage(pDC,nXPosInfo+10,nYPosInfo+17);

		//�滭����
		m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserScore,nXPosInfo+136,nYPosInfo+18L);
		m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserInsure,nXPosInfo+136,nYPosInfo+53L);

		//�滭��ʾ
		LPCTSTR pszScoreString=TEXT("��Ϸ�ң�");
		LPCTSTR pszInsureString=TEXT("���չ�");
		pDC->TextOut(nXPosInfo+83,nYPosInfo+20L,pszScoreString,lstrlen(pszScoreString));
		pDC->TextOut(nXPosInfo+83,nYPosInfo+55L,pszInsureString,lstrlen(pszInsureString));
*/
		//������ʾ
		TCHAR szString[128]=TEXT("");
		_sntprintf(szString,CountArray(szString),TEXT("��ܰ��ʾ��������Ϸ���������ѣ�ȡ�����۳�%ld��,���ͽ��۳�%.1f����������"),m_UserInsureInfo.wRevenueTake,m_UserInsureInfo.wRevenueTransfer*0.1);

		//��ܰ��ʾ
		pDC->SetTextColor(RGB(50,50,50));
		pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));
	}
	else
	{
	}

	return;
}
void CDlgInsureMain::DrawBankTab(CDC * pDC, INT nWidth, INT nHeight)
{
	if (!m_bInit)
	{
		return;
	}
	CRect rect;
	GetClientRect(rect);

	//�滭����
	INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	pDC->FillSolidRect(nLBorder, 37, 118,rect.bottom-77,RGB(212,227,236));
	pDC->FillSolidRect(nLBorder, 37, 118, 35,RGB(113,156,182));
	pDC->FillSolidRect(118-nLBorder+10, 37, 2, rect.bottom-77,RGB(167,193,208));


	pDC->SetTextColor(RGB(40, 64, 118));
	CFont *oldBankFont = (CFont *)pDC->SelectObject(&m_BankFont);
	pDC->TextOut(31,m_nBeginTop, "������Ϣ");

	if (m_nSelIndex < 4)
	{
		pDC->FillSolidRect(m_BankRect[m_nSelIndex], RGB(166,203,226));
		m_ImageSelBank.Draw(pDC->GetSafeHdc(), m_BankRect[m_nSelIndex].right+6, m_BankRect[m_nSelIndex].top);
	}
	pDC->SelectObject(oldBankFont);
	CFont *oldBankFontInfo = (CFont *)pDC->SelectObject(&m_BankFontInfo);
	pDC->TextOut(m_nLSpace,m_nBeginTop + m_nHSpace,   "ȡ    ��");
	pDC->TextOut(m_nLSpace,m_nBeginTop + m_nHSpace*2, "��    ��");
	pDC->TextOut(m_nLSpace,m_nBeginTop + m_nHSpace*3, "��    ��");
	pDC->TextOut(m_nLSpace,m_nBeginTop + m_nHSpace*4, "������ϸ");
	pDC->SelectObject(oldBankFontInfo);
}
VOID CDlgInsureMain::SetInsurePass(CString sInsurePwd)
{
	lstrcpyn(m_szSaveInsurePass,sInsurePwd,CountArray(m_szSaveInsurePass));
}

VOID CDlgInsureMain::UpdatUserInfo()
{
	if(m_DlgInsureTeller.m_hWnd!=NULL)
		m_DlgInsureTeller.UpDateView();
	if(m_DlgInsureSave.m_hWnd!=NULL)
		m_DlgInsureSave.UpDateView();
	if(m_DlgInsureTransfer.m_hWnd!=NULL)
		m_DlgInsureTransfer.UpDateView();
}


//��ʼ����
VOID CDlgInsureMain::OnMissionStart()
{
	return;
}

//��ֹ����
VOID CDlgInsureMain::OnMissionConclude()
{
	return;
}

//��ѯ����
VOID CDlgInsureMain::QueryUserInsureInfo()
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=true;
	m_bTransferMission=false;

	//�¼�����
	OnMissionStart();

	//ִ�в�ѯ
	PerformQueryInfo();

	return;
}

//����ģʽ
VOID CDlgInsureMain::SwitchInsureModeView(BYTE cbInsureMode)
{

	CRect rcTree;
	m_treeDlg.GetWindowRect(&rcTree);
	ScreenToClient(&rcTree);
	int nTreeSpace = 10;
	//return;
	switch (cbInsureMode)
	{
	case 0:           //������ҳ
		{
			m_cbInsureMode=0;
			ASSERT(FALSE);
			break;
		}
	case 1:			//ȡ�� m_DlgInsureTeller
		{
			//���ñ���
			m_cbInsureMode=1;

			//���ÿؼ�
			if (m_DlgInsureTeller.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);
				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureTeller.Create(IDD_INSURE_TELLER,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				m_DlgInsureTeller.SetWindowPos(NULL,rcTree.right,nTBorder+5,rcClient.Width()-rcTree.right-nRBorder-nLBorder,rcClient.Height()-nBBorder-nTBorder-7,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				m_nSelIndex = 0;
				//��ʾ����
				m_DlgInsureTeller.UpDateView();
				m_DlgInsureTeller.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd!=NULL) 
				m_DlgInsureSave.ShowWindow(SW_HIDE);
			if (m_DlgInsureTransfer.m_hWnd!=NULL) 
				m_DlgInsureTransfer.ShowWindow(SW_HIDE);
			if (m_LogDlg.m_hWnd!=NULL) 
				m_LogDlg.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureTeller.SetFocus();

			//����ѡ��
			//m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	
	case 2:			//���
		{
			//���ñ���
			m_cbInsureMode=2;

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureSave.Create(IDD_INSURE_SAVE,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				m_DlgInsureSave.SetWindowPos(NULL,rcTree.right,nTBorder+5,rcClient.Width()-rcTree.right-nRBorder-nLBorder,rcClient.Height()-nBBorder-nTBorder-7,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				m_nSelIndex = 1;
				//��ʾ����
				m_DlgInsureSave.UpDateView();
				m_DlgInsureSave.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureTeller.m_hWnd!=NULL) 
				m_DlgInsureTeller.ShowWindow(SW_HIDE);
			if (m_DlgInsureTransfer.m_hWnd!=NULL) 
				m_DlgInsureTransfer.ShowWindow(SW_HIDE);
			if (m_LogDlg.m_hWnd!=NULL) 
				m_LogDlg.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureSave.SetFocus();

			//����ѡ��
			//m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case 3:		//ת�˷�ʽ
		{
			//���ñ���
			m_cbInsureMode=3;

			//���ÿؼ�
			if (m_DlgInsureTransfer.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureTransfer.Create(IDD_INSURE_TRANSFER,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				m_DlgInsureTransfer.SetWindowPos(NULL,rcTree.right,nTBorder+5,rcClient.Width()-rcTree.right-nRBorder-nLBorder,rcClient.Height()-nBBorder-nTBorder-7,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				m_nSelIndex = 2;
				//��ʾ����
				m_DlgInsureTransfer.UpDateView();
				m_DlgInsureTransfer.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureTeller.m_hWnd!=NULL) 
				m_DlgInsureTeller.ShowWindow(SW_HIDE);
			if (m_DlgInsureSave.m_hWnd!=NULL) 
				m_DlgInsureSave.ShowWindow(SW_HIDE);
			if (m_LogDlg.m_hWnd!=NULL) 
				m_LogDlg.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureTransfer.SetFocus();

			//����ѡ��
			//m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case 4:           //ת�˼�¼
		{
			//���ñ���
			m_cbInsureMode=4;

			//���ذ�ť
			//m_btQueryInfo.ShowWindow(SW_HIDE);

			//���ÿؼ�
			if (m_LogDlg.m_hWnd == NULL)
			{
				CRect rcClient;
				GetClientRect(&rcClient);
				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_LogDlg.Create(IDD_DIALOG_INSURE_LOG,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				//m_LogDlg.SetWindowPos(NULL,rcTree.right+nTreeSpace,nTBorder+12,rcClient.Width()-rcTree.right-nRBorder-nLBorder/*-nTreeSpace*2*/,rcClient.Height()-nBBorder-nTBorder/*-32*/,SWP_NOZORDER|SWP_SHOWWINDOW);
				m_LogDlg.SetWindowPos(NULL,rcTree.right,nTBorder+5,rcClient.Width()-rcTree.right-nRBorder-nLBorder,rcClient.Height()-nBBorder-nTBorder-7,SWP_NOZORDER|SWP_SHOWWINDOW);


				//������ҳ
				//m_DlgBrowserItem.InitService(TEXT("ת�˼�¼"),TEXT("UserService/USTransferRecord.aspx"));

				////��ȡλ��
				//CRect rcClient;
				//GetClientRect(&rcClient);

				////������Դ
				//AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				////�����ؼ�
				//m_DlgBrowserItem.Create(IDD_DLG_SERVICETRANSFER,this);

				////������Դ
				//AfxSetResourceHandle(GetModuleHandle(NULL));

				////�ƶ�λ��
				//INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				//INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				//INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				//INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				//m_LogDlg.SetWindowPos(NULL,rcTree.right,nTBorder+5,rcClient.Width()-rcTree.right-nRBorder-nLBorder,rcClient.Height()-nBBorder-nTBorder-7,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				m_nSelIndex = 3;
				//��ʾ����
				m_LogDlg.ShowWindow(SW_SHOW);
			}
			//���ÿؼ�
			if (m_DlgInsureTeller.m_hWnd!=NULL) 
				m_DlgInsureTeller.ShowWindow(SW_HIDE);
			if (m_DlgInsureTransfer.m_hWnd!=NULL) 
				m_DlgInsureTransfer.ShowWindow(SW_HIDE);
			if (m_DlgInsureSave.m_hWnd!=NULL) 
				m_DlgInsureSave.ShowWindow(SW_HIDE);

			//����ѡ��
			//m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//���͸ı�
//VOID CDlgInsureMain::OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult)
//{
//	switch (m_TabControl.GetCurSel())
//	{
//	case INSURE_TRANSFERRECORD:       //ת�˼�¼
//		{
//			SwitchInsureModeView(INSURE_TRANSFERRECORD);
//			break;
//		}
//	case INSURE_SAVE:		//��ȡ��ʽ
//		{
//			SwitchInsureModeView(INSURE_SAVE);
//			break;
//		}
//	case INSURE_TRANSFER:	//ת�˷�ʽ
//		{
//			SwitchInsureModeView(INSURE_TRANSFER);
//			break;
//		}
//	default:
//		{
//			ASSERT(FALSE);
//		}
//	}
//
//	return;
//}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsurePlaza::CDlgInsurePlaza()
{
	//��������
	m_MissionManager.InsertMissionItem(this);

	//���ñ���
	m_lScore=0L;
	ZeroMemory(m_szNickName,sizeof(m_szNickName));
	ZeroMemory(m_szInsurePass,sizeof(m_szInsurePass));
	//ZeroMemory(m_szSaveInsurePass,sizeof(m_szSaveInsurePass));

	return;
}

//��������
CDlgInsurePlaza::~CDlgInsurePlaza()
{
	if (GetActiveStatus() == true)
	{
		m_MissionManager.ConcludeMissionItem(this,false);
	}
}

//��ѯ�¼�
VOID CDlgInsurePlaza::PerformQueryInfo()
{
	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//�����¼�
VOID CDlgInsurePlaza::PerformSaveScore(SCORE lSaveScore)
{
	//���ñ���
	m_bSaveMission=true;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;

	//���ñ���
	m_lScore=lSaveScore;

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ȡ���¼�
VOID CDlgInsurePlaza::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bTakeMission=true;
	m_bSaveMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;

	//���ñ���
	m_lScore=lTakeScore;
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ת���¼�
VOID CDlgInsurePlaza::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=true;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

VOID CDlgInsurePlaza::SendBankTransferLog(int nCurrentPage,int nDays)
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;
	//m_bModifyInsurePwd = false;
	m_bQueryTransferLog = true;
	//m_bQueryCharm = false;
	//m_bExchangeCharm = false;

	m_nCurrentPage = nCurrentPage;
	m_nDays = nDays;

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

}

//�����¼�
bool CDlgInsurePlaza::OnEventMissionLink(INT nErrorCode)
{
	//���ӽ��
	if (nErrorCode!=0)
	{
		//��������
		//if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		//{
		//	return true;
		//}

		//�¼�����
		OnMissionConclude();

		//������ʾ
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ�Ҵ���ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ��ȡ��ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����չ����ϻ�ȡʧ�ܣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTransferMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ������ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		return true;
	}

	//��������
	else if (m_bSaveMission==true)
	{
		//��������
		CMD_GP_UserSaveScore UserSaveScore;
		ZeroMemory(&UserSaveScore,sizeof(UserSaveScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserSaveScore.lSaveScore=m_lScore;
		UserSaveScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserSaveScore.szMachineID);

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_SAVE_SCORE,&UserSaveScore,sizeof(UserSaveScore));

		return true;
	}

	//ȡ������
	else if (m_bTakeMission==true)
	{
		//��������
		CMD_GP_UserTakeScore UserTakeScore;
		ZeroMemory(&UserTakeScore,sizeof(UserTakeScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserTakeScore.lTakeScore=m_lScore;
		UserTakeScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserTakeScore.szMachineID);
		lstrcpyn(UserTakeScore.szPassword,m_szInsurePass,CountArray(UserTakeScore.szPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TAKE_SCORE,&UserTakeScore,sizeof(UserTakeScore));

		return true;
	}

	//ת������
	else if (m_bTransferMission==true)
	{
		//��������
		CMD_GP_QueryUserInfoRequest QueryUserInfoRequest;
		ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

		//���ñ���
		QueryUserInfoRequest.cbByNickName=m_cbByNickName;
		lstrcpyn(QueryUserInfoRequest.szNickName,m_szNickName,CountArray(QueryUserInfoRequest.szNickName));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));
                return true;
	}

	//��ѯ����
	else if (m_bQueryMission==true)
	{
		//��������
		CMD_GP_QueryInsureInfo QueryInsureInfo;
		ZeroMemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

		//���ñ���
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		QueryInsureInfo.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;
		lstrcpyn(QueryInsureInfo.szPassword,pGlobalUserInfo->GetGlobalUserData()->szPassword,CountArray(QueryInsureInfo.szPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));
                return true;
	}
	//ת�˼�¼
	else if(m_bQueryTransferLog == true)
	{
		CMD_GP_GetBankRecord GetBankRecord;
		ZeroMemory(&GetBankRecord,sizeof(GetBankRecord));

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		GetBankRecord.dwUserID = pGlobalUserData->dwUserID;
		GetBankRecord.dwPage = m_nCurrentPage;
		GetBankRecord.dwPageSize = 8;
		GetBankRecord.dwLastDay = m_nDays;
		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_INSURE_RECORD,&GetBankRecord,sizeof(GetBankRecord));
		return true;
	}

	return true;
}

//�ر��¼�
bool CDlgInsurePlaza::OnEventMissionShut(BYTE cbShutReason)
{
	//��ʾ��Ϣ
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		//if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		//{
		//	return true;
		//}

		//��������
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ���Ϸ�Ҵ���ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//ȡ������
		else if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ���Ϸ��ȡ��ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//��ѯ����
		else if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����չ����ϻ�ȡʧ�ܣ�"),MB_ICONERROR,30);
		}
		else if (m_bQueryTransferLog == true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ���ѯת�˼�¼ʧ�ܣ�"),MB_ICONERROR,30);
		}
	}

	//�¼�����
	OnMissionConclude();

	return true;
}

//��ȡ�¼�
bool CDlgInsurePlaza::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GP_UserInsureInfo)) return false;

				//��������
				CMD_GP_UserInsureInfo * pUserInsureInfo=(CMD_GP_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pUserInsureInfo->lUserInsure;
				pGlobalUserData->lUserScore = pUserInsureInfo->lUserScore;
				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//���´���
				tagInsurePlazaUpdata Updata;
				Updata.lUserScore=pUserInsureInfo->lUserScore;
				Updata.lUserInsure=pUserInsureInfo->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&Updata,0);
				UpdatUserInfo();

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				return true;
			}
		case SUB_GP_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GP_UserInsureSuccess * pUserInsureSuccess=(CMD_GP_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pUserInsureSuccess->lUserInsure;
				pGlobalUserData->lUserScore = pUserInsureSuccess->lUserScore;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);
				UpdatUserInfo();
				//���´���
				tagInsurePlazaUpdata Updata;
				Updata.lUserScore=pUserInsureSuccess->lUserScore;
				Updata.lUserInsure=pUserInsureSuccess->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&Updata,0);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//��ʾ��Ϣ
				if (pUserInsureSuccess->dwRecordID>0)
				{
					//ת����ֵ
					TCHAR szString[128]=TEXT("");
					m_DlgInsureItem.SwitchScoreString(pUserInsureSuccess->lSwapScore,szString,CountArray(szString));
					CInsureSuccess  SuccessDlg;
					SuccessDlg.SetInfo(pUserInsureSuccess->dwGameID,pUserInsureSuccess->szNickName, pUserInsureSuccess->dwTargetGameID,
						pUserInsureSuccess->szTargetNickName, pUserInsureSuccess->szDate, pUserInsureSuccess->dwRecordID, pUserInsureSuccess->lSwapScore, szString);

					//������Դ
					HINSTANCE hInstResourceClient = AfxGetResourceHandle();
					AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
					SuccessDlg.DoModal();
					AfxSetResourceHandle(hInstResourceClient);
				}else
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GP_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_UserInsureFailure * pUserInsureFailure=(CMD_GP_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);
               /*
				if(m_DlgInsureTeller.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTeller.m_PasswordControl.SetFocus();
					m_DlgInsureTeller.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}
                */
				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GP_QUERY_USER_INFO_RESULT:	//�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GP_UserTransferUserInfo)) return false;

				//��������
				CMD_GP_UserTransferUserInfo * pTransferUserInfo=(CMD_GP_UserTransferUserInfo *)pData;

				//������Ϣ
				TCHAR szMessage[128]={0};
				_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ��Ϸ����?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

				//��ʾ��Ϣ
				CInformation Information(this);
				if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
				{
					//��������
					CMD_GP_UserTransferScore UserTransferScore;
					ZeroMemory(&UserTransferScore,sizeof(UserTransferScore));

					//��������
					CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
					tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

					//���ñ���
					UserTransferScore.cbByNickName=m_cbByNickName;
					UserTransferScore.lTransferScore=m_lScore;
					UserTransferScore.dwUserID=pGlobalUserData->dwUserID;
					CWHService::GetMachineIDEx(UserTransferScore.szMachineID);
					lstrcpyn(UserTransferScore.szNickName,m_szNickName,CountArray(UserTransferScore.szNickName));
					lstrcpyn(UserTransferScore.szPassword,m_szInsurePass,CountArray(UserTransferScore.szPassword));

					//��������
					m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TRANSFER_SCORE,&UserTransferScore,sizeof(UserTransferScore));
				}

				return true;
			}
		case SUB_GP_INSURE_RECORD:
			{
				//CMD_GP_BankRecord  BankRecord;
				//ZeroMemory(&BankRecord,sizeof(BankRecord));

				//��������
				CMD_GP_BankRecord * BankRecord=(CMD_GP_BankRecord *)pData;
				WORD wHeadSize=(sizeof(CMD_GP_BankRecord)-sizeof(BankRecord->RecordItem));

				//Ч������
				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+BankRecord->dwIndex*sizeof(CMD_GP_BankRecordItem))));
				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+BankRecord->dwIndex*sizeof(CMD_GP_BankRecordItem)))) return false;

				//BankRecord->dwIndex = 
				for (WORD i=0;i<BankRecord->dwIndex;i++)
				{
					CMD_GP_BankRecordItem * pBankRecordItem=&BankRecord->RecordItem[i];
					//CMD_GP_BankTransferLogResult *pBankTransferLogResult=(CMD_GP_BankTransferLogResult *)pData;
					m_LogDlg.InsertTransferLog(pBankRecordItem);
				}
				m_LogDlg.SetTransPages(BankRecord->dwPageCount,BankRecord->dwPageIndex,BankRecord->dwIndex);

				return true;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureServer::CDlgInsureServer()
{
	//���ñ���
	m_pITCPSocket=NULL;
	m_pIMySelfUserItem=NULL;

	return;
}

//��������
CDlgInsureServer::~CDlgInsureServer()
{
	
}

//��ѯ�¼�
VOID CDlgInsureServer::PerformQueryInfo()
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	CMD_GR_C_QueryInsureInfoRequest QueryInsureInfo;
	ZeroMemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

	//���ñ���
	QueryInsureInfo.cbActivityGame=FALSE;
	lstrcpyn(QueryInsureInfo.szInsurePass,pGlobalUserData->szPassword,CountArray(QueryInsureInfo.szInsurePass));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));

	return;
}

//�����¼�
VOID CDlgInsureServer::PerformSaveScore(SCORE lSaveScore)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_C_SaveScoreRequest SaveScoreRequest;
	ZeroMemory(&SaveScoreRequest,sizeof(SaveScoreRequest));

	//���ñ���
	SaveScoreRequest.lSaveScore=lSaveScore;

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_SAVE_SCORE_REQUEST,&SaveScoreRequest,sizeof(SaveScoreRequest));

	return;
}

//ȡ���¼�
VOID CDlgInsureServer::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_C_TakeScoreRequest TakeScoreRequest;
	ZeroMemory(&TakeScoreRequest,sizeof(TakeScoreRequest));

	//���ñ���
	TakeScoreRequest.lTakeScore=lTakeScore;
	lstrcpyn(TakeScoreRequest.szInsurePass,pszInsurePass,CountArray(TakeScoreRequest.szInsurePass));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TAKE_SCORE_REQUEST,&TakeScoreRequest,sizeof(TakeScoreRequest));

	return;
}

//ת���¼�
VOID CDlgInsureServer::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	CMD_GR_C_QueryUserInfoRequest QueryUserInfoRequest;
	ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	//���ñ���
	QueryUserInfoRequest.cbByNickName=cbByNickName;
	lstrcpyn(QueryUserInfoRequest.szNickName,pszNickName,CountArray(QueryUserInfoRequest.szNickName));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	return;
}

VOID CDlgInsureServer::SendBankTransferLog(int nCurrentPage,int nDays)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//���ñ���	
	m_nCurrentPage = nCurrentPage;
	m_nDays = nDays;

	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();


	CMD_GP_GetBankRecord GetBankRecord;
	ZeroMemory(&GetBankRecord,sizeof(GetBankRecord));

	GetBankRecord.dwUserID = pGlobalUserData->dwUserID;
	GetBankRecord.dwPage = m_nCurrentPage;
	GetBankRecord.dwPageSize = 8;
	GetBankRecord.dwLastDay = m_nDays;
	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_INSURE_RECORD,&GetBankRecord,sizeof(GetBankRecord));

}

//��������
VOID CDlgInsureServer::Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem)
{
	//���ñ���
	m_pITCPSocket=pITCPSocket;
	m_pIMySelfUserItem=pIMySelfUserItem;

	return;
}

//������Ϣ
bool CDlgInsureServer::OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	//��Ϣ�ж�
	if (wMainCmdID==MDM_GR_INSURE)
	{
		switch (wSubCmdID)
		{
		case SUB_GR_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserInsureInfo)) return false;

				//��������
				CMD_GR_S_UserInsureInfo * pUserInsureInfo=(CMD_GR_S_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pUserInsureInfo->lUserInsure;
				pGlobalUserData->lUserScore = pUserInsureInfo->lUserScore;

				//���½���
				UpdatUserInfo();
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				return true;
			}
		case SUB_GR_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GR_S_UserInsureSuccess * pUserInsureSuccess=(CMD_GR_S_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pUserInsureSuccess->lUserInsure;
				pGlobalUserData->lUserScore = pUserInsureSuccess->lUserScore;
				//���½���
				UpdatUserInfo();
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//��ʾ��Ϣ
				//if (pUserInsureSuccess->szDescribeString[0]!=0)
				if (pUserInsureSuccess->dwRecordID>0)
				{
					//ת����ֵ
					TCHAR szString[128]=TEXT("");
					m_DlgInsureItem.SwitchScoreString(pUserInsureSuccess->lSwapScore,szString,CountArray(szString));
					CInsureSuccess  SuccessDlg;
					SuccessDlg.SetInfo(pUserInsureSuccess->dwGameID,pUserInsureSuccess->szNickName, pUserInsureSuccess->dwTargetGameID,
						pUserInsureSuccess->szTargetNickName, pUserInsureSuccess->szDate, pUserInsureSuccess->dwRecordID, pUserInsureSuccess->lSwapScore, szString);

					//������Դ
					HINSTANCE hInstResourceClient = AfxGetResourceHandle();
					AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
					SuccessDlg.DoModal();
					AfxSetResourceHandle(hInstResourceClient);
				}else
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GR_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GR_S_UserInsureFailure * pUserInsureFailure=(CMD_GR_S_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//����ؼ�
				if (m_bInitInfo==true)
				{/*
					if(m_DlgInsureTeller.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureTeller.m_PasswordControl.SetFocus();
						m_DlgInsureTeller.m_PasswordControl.SetUserPassword(TEXT(""));
					}
					if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureSave.m_PasswordControl.SetFocus();
						m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
					}
					if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureTransfer.m_PasswordControl.SetFocus();
						m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
					}*/
				}

				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GR_USER_TRANSFER_USER_INFO:  //�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserTransferUserInfo)) return false;

				//��������
				CMD_GR_S_UserTransferUserInfo * pTransferUserInfo=(CMD_GR_S_UserTransferUserInfo *)pData;

				//������Ϣ
				TCHAR szMessage[128]={0};
				_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ��Ϸ����?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

				//��ʾ��Ϣ
				CInformation Information(this);
				if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
				{
					//��������
					CMD_GP_C_TransferScoreRequest TransferScoreRequest;
					ZeroMemory(&TransferScoreRequest,sizeof(TransferScoreRequest));

					//���ñ���
					TransferScoreRequest.cbByNickName=m_cbByNickName;
					TransferScoreRequest.lTransferScore=m_lScore;
					lstrcpyn(TransferScoreRequest.szNickName,m_szNickName,CountArray(TransferScoreRequest.szNickName));
					lstrcpyn(TransferScoreRequest.szInsurePass,m_szInsurePass,CountArray(TransferScoreRequest.szInsurePass));

					//��������
					m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TRANSFER_SCORE_REQUEST,&TransferScoreRequest,sizeof(TransferScoreRequest));
				}
				return true;
			}
		case SUB_GR_INSURE_RECORD:
			{
				//��������
				DBR_GR_BankRecord * BankRecord=(DBR_GR_BankRecord *)pData;
				WORD wHeadSize=(sizeof(DBR_GR_BankRecord)-sizeof(BankRecord->RecordItem));

				//Ч������
				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+BankRecord->dwIndex*sizeof(DBR_GR_BankRecordItem))));
				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+BankRecord->dwIndex*sizeof(DBR_GR_BankRecordItem)))) return false;

				//BankRecord->dwIndex = 
				for (WORD i=0;i<BankRecord->dwIndex;i++)
				{
					CMD_GP_BankRecordItem * pBankRecordItem=(CMD_GP_BankRecordItem *)&BankRecord->RecordItem[i];

					//CMD_GP_BankRecordItem * pBankTransferLogResult = NULL;
					//CMD_GP_BankTransferLogResult *pBankTransferLogResult=(CMD_GP_BankTransferLogResult *)pData;
					m_LogDlg.InsertTransferLog(pBankRecordItem);
				}
				m_LogDlg.SetTransPages(BankRecord->dwPageCount,BankRecord->dwPageIndex,BankRecord->dwIndex);
				return true;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

