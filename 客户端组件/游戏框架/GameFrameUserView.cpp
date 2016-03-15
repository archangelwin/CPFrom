#include "StdAfx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "GameFrameUserView.h"

//////////////////////////////////////////////////////////////////////////////////

//���ƫ��
#define	BILL_T						5									//����ϸ�
#define	BILL_L						7									//������
#define	BILL_R						7									//����ҿ�
#define	BILL_B						143									//����¸�

//�ؼ���ʾ
#define IDC_WEB_PUBLICIZE			0/*100*/									//����ؼ�
#define IDC_BT_USER_MEDAL			101									//�һ�����
#define IDC_BT_LOVE_LINESS			102									//�һ�����

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameUserView, CWnd)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_BT_USER_MEDAL, OnBnClickedUserMedal)
	ON_BN_CLICKED(IDC_BT_LOVE_LINESS, OnBnClickedLoveLiness)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameUserView::CGameFrameUserView()
{
	//���ñ���
	m_pIClientKernel=NULL;
	m_pICurrentUserItem=NULL;

	return;
}

//��������
CGameFrameUserView::~CGameFrameUserView()
{
}

//���ù��
VOID CGameFrameUserView::SetGameBillInfo(WORD wKindID, WORD wServerID)
{
	//�����ַ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/GameFrame.aspx?KindID=%ld&ServerID=%ld"),pGlobalServer->GetPlatformServer(3),wKindID,wServerID);

	//�򿪵�ַ
	//m_GameFramePublicize.Navigate(szBillUrl);

	return;
}

//�����û�
VOID CGameFrameUserView::SetUserViewInfo(IClientUserItem * pIClientUserItem)
{
	//�����û�
	if (m_pICurrentUserItem!=pIClientUserItem)
	{
		//���ñ���
		m_pICurrentUserItem=pIClientUserItem;

		//���½���
		if (m_hWnd!=NULL)
		{
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
		}
	}

	return;
}

//�����ؼ�
VOID CGameFrameUserView::RectifyControl(INT nWidth, INT nHeight)
{
	//��ȡ��С
	CRect rcButton;
	m_btUserMedal.GetWindowRect(&rcButton);

	//����λ��
	INT nXBorad=12L;
	INT nXButtonPos=(nWidth-rcButton.Width()*2L-nXBorad*2L)/3L;

	//������ť
	m_btUserMedal.SetWindowPos(NULL,nXBorad+nXButtonPos,nHeight-rcButton.Height()-6,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_btLoveLiness.SetWindowPos(NULL,nXBorad+nXButtonPos*2+rcButton.Width(),nHeight-rcButton.Height()-6,0,0,SWP_NOZORDER|SWP_NOSIZE);

	//�������
// 	if (m_GameFramePublicize.m_hWnd!=NULL)
// 	{
// 		m_GameFramePublicize.SetWindowPos(NULL,BILL_L,BILL_T,nWidth-BILL_L-BILL_R,nHeight-BILL_T-BILL_B,SWP_NOZORDER);
// 	}

	return;
}

//���ƶһ�
VOID CGameFrameUserView::OnBnClickedUserMedal()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("Ingot.aspx"));
	//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	//_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/Ingot.aspx"),pGlobalServer->GetPlatformServer(3));

	//��ҳ��
	//ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
	//��ҳ��
	CDlgBrowser DlgBrowser;
	DlgBrowser.CreateBrowserControl(TEXT("Ԫ���һ�"),szLogonLink,CSize(730,450));
	return;
}

//�����һ�
VOID CGameFrameUserView::OnBnClickedLoveLiness()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("LoveLiness.aspx"));

	//��ҳ��
	CDlgBrowser DlgBrowser;
	DlgBrowser.CreateBrowserControl(TEXT("�����һ�"),szLogonLink,CSize(730,450));

	return;
}

//�滭����
BOOL CGameFrameUserView::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SetTextAlign(TA_LEFT|TA_TOP);
	pBufferDC->SetTextColor(RGB(250,250,250));
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CImage ImageUserInfoL;
	CImage ImageUserInfoM;
	CImage ImageUserInfoR;
	ImageUserInfoL.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_L);
	ImageUserInfoM.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_M);
	ImageUserInfoR.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_R);

	//��������
	INT nXStartPos=ImageUserInfoL.GetWidth();
	INT nXConcludePos=rcClient.Width()-ImageUserInfoR.GetWidth();

	//�滭���
	ImageUserInfoL.BitBlt(BufferDC,0,0);
	ImageUserInfoR.BitBlt(BufferDC,rcClient.Width()-ImageUserInfoR.GetWidth(),0);

	//�滭�м�
	for (INT nXPos=nXStartPos;nXPos<nXConcludePos;nXPos+=ImageUserInfoM.GetWidth())
	{
		INT nCXDraw=__min(ImageUserInfoM.GetWidth(),nXConcludePos-nXPos);
		ImageUserInfoM.BitBlt(BufferDC,nXPos,0,nCXDraw,ImageUserInfoM.GetHeight(),0,0);
	}

	//�滭�û�
	if (m_pICurrentUserItem!=NULL)
	{
		//��������
		INT nYExcursion=80L;
		TCHAR szString[128]=TEXT("");

		//��������
		tagUserInfo * pUserInfo=m_pICurrentUserItem->GetUserInfo();
		tagGameAttribute * pGameAttribute=m_pIClientKernel->GetGameAttribute();
		tagCustomFaceInfo * pCustomFaceInfo=m_pICurrentUserItem->GetCustomFaceInfo();

		//��������
		CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
		CFaceItemControl * pFaceItemControl=CFaceItemControl::GetInstance();
		CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

		//�ӿڱ���
		IUserOrderParser * pIUserOrderParser=pGlobalUnits->m_UserOrderParserModule.GetInterface();
		IGameLevelParser * pIGameLevelParser=pGlobalUnits->m_GameLevelParserModule.GetInterface();

		//�滭ͷ��
		if ((pCustomFaceInfo->dwDataSize!=0L)&&(m_pICurrentUserItem->GetCustomID()!=0L))
		{
			pFaceItemControl->DrawFaceNormal(pBufferDC,16+22-15,nYExcursion+14-80,pCustomFaceInfo->dwCustomFace);
		}
		else
		{
			pFaceItemControl->DrawFaceNormal(pBufferDC,16+22-15,nYExcursion+14-80,m_pICurrentUserItem->GetFaceID());
		}

		//λ�ö���
		CRect rcNickName(72+30-17,nYExcursion+14-80,rcClient.Width()-12+30,nYExcursion+26-80);
		CRect rcExperience(72+30-17,nYExcursion+33-80,rcClient.Width()-12+30-20,nYExcursion+45-80);
		CRect rcUserGameID(72+30-17,nYExcursion+52-80,rcClient.Width()-12+30-20,nYExcursion+64-80);

		//λ�ö���
// 		CRect rcGameLevel(15+30-17,nYExcursion+72+10-80,rcClient.Width()-12+30-10,nYExcursion+84+10-80);
// 		CRect rcGameDrawInfo(15+30-17,nYExcursion+91+18-80,rcClient.Width()-12+30-10,nYExcursion+103+18-80);
		CRect rcGameLevel(72+30-17,nYExcursion+72+10-80-49,rcClient.Width()-12+30-10+60,nYExcursion+84+10-80-49);
		CRect rcGameDrawInfo(72+30-17,nYExcursion+91+18-80-57,rcClient.Width()-12+30-10+60,nYExcursion+103+18-80-57);

		//������Ϣ
		DWORD dwExperience=m_pICurrentUserItem->GetUserExperience();
		WORD wExperienceLevel=pUserItemElement->GetExperienceLevel(dwExperience);

		//�û���Ϣ
		LPCTSTR pszMember=pIUserOrderParser->GetMemberDescribe(m_pICurrentUserItem->GetMemberOrder());
		LPCTSTR pszMaster=pIUserOrderParser->GetMasterDescribe(m_pICurrentUserItem->GetMasterOrder());

		//�û���Ϣ
		LPCTSTR pszUserOrder=(pszMaster[0]!=0)?pszMaster:((pszMember[0]!=0)?pszMember:TEXT("��ͨ���"));
		_sntprintf(szString,CountArray(szString),TEXT("�ǳƣ�%s [ %s ]"),m_pICurrentUserItem->GetNickName(),pszUserOrder);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcNickName,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//�û�����
// 		_sntprintf(szString,CountArray(szString),TEXT("���飺%d ��"),wExperienceLevel);
// 		pBufferDC->DrawText(szString,lstrlen(szString),&rcExperience,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//�����־
// 		CSize SizeExperience=pDC->GetTextExtent(szString,lstrlen(szString));
// 		pUserItemElement->DrawExperience(pBufferDC,rcExperience.left+SizeExperience.cx+6,rcExperience.top-4L,dwExperience);

		//��Ϸ��ʶ
// 		_sntprintf(szString,CountArray(szString),TEXT("���룺%ld"),pUserInfo->dwGameID);
// 		pBufferDC->DrawText(szString,lstrlen(szString),&rcUserGameID,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//���ֵȼ�
// 		LPCTSTR pszGameLevel=pIGameLevelParser->GetLevelDescribe(m_pICurrentUserItem);
// 		_sntprintf(szString,CountArray(szString),TEXT("��ң�") SCORE_STRING TEXT(" �ȼ���%s [ %s ]"),pUserInfo->lScore,pszGameLevel,pGameAttribute->szGameName);
// 		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameLevel,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
		LPCTSTR pszGameLevel=pIGameLevelParser->GetLevelDescribe(m_pICurrentUserItem);
		_sntprintf(szString,CountArray(szString),TEXT("��ң�") SCORE_STRING,pUserInfo->lScore);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameLevel,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		CGlobalServer * pGlobalServer = CGlobalServer::GetInstance();
		if (pGlobalServer->BShowGameLevel() == true)
		{
			_sntprintf(szString,CountArray(szString),TEXT("�ȼ���%d�� [ %s ]"),dwExperience,pszGameLevel/*,pGameAttribute->szGameName*/);
		}else
			_sntprintf(szString,CountArray(szString),TEXT("�ȼ���%s [ %s ]"),pszGameLevel,pGameAttribute->szGameName);//		LPCTSTR pszGameLevel=pIGameLevelParser->GetLevelDescribe(m_pICurrentUserItem);
//		_sntprintf(szString,CountArray(szString),TEXT("�ȼ���%d�� [ %s ]"),dwExperience,pszGameLevel/*,pGameAttribute->szGameName*/);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameDrawInfo,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//��Ϸ��Ϣ
		LONG lPlayCount=m_pICurrentUserItem->GetUserPlayCount();
		float fUserWinRate=m_pICurrentUserItem->GetUserWinRate();
		float fUserFleeRate=m_pICurrentUserItem->GetUserFleeRate();
		/*_sntprintf(szString,CountArray(szString),TEXT("������%ld ʤ�ʣ�%.2f%% ���ʣ�%.2f%%"),lPlayCount,fUserWinRate,fUserFleeRate);*/
// 		_sntprintf(szString,CountArray(szString),TEXT("ʤ�ʣ�%.2f%% ���ʣ�%.2f%%"),fUserWinRate,fUserFleeRate);
// 		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameDrawInfo,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//λ����Ϣ
VOID CGameFrameUserView::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//������Ϣ
INT CGameFrameUserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//��ѯ�ӿ�
	ASSERT(CGlobalUnits::GetInstance()->m_ClientKernelModule.GetInterface()!=NULL);
	m_pIClientKernel=CGlobalUnits::GetInstance()->m_ClientKernelModule.GetInterface();

	//�����ؼ�
	CRect rcCreate(0,0,0,0);
	m_btUserMedal.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_USER_MEDAL);
	m_btLoveLiness.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_LOVE_LINESS);
	m_btUserMedal.ShowWindow(SW_HIDE);
	m_btLoveLiness.ShowWindow(SW_HIDE);

	//���ð�ť
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_btUserMedal.SetButtonImage(IDB_BT_USER_INFO,TEXT("BT_USER_DEMAL"),hInstance,false,false);
	m_btLoveLiness.SetButtonImage(IDB_BT_USER_INFO,TEXT("BT_LOVE_LINESS"),hInstance,false,false);

	//�������
	//m_GameFramePublicize.SetBoradColor(RGB(0,0,0));
	//m_GameFramePublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
