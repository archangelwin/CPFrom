#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgEnquire.h"
#include "DlgSearchUser.h"
#include "PlatformFrame.h"
#include ".\platformframe.h"
#include "MessagePop.h"
#include "DlgMobileBind.h"
#include "DlgLockMachine.h"
#include "DlgService.h"
#include "VerifyInsurePass.h"

//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С�ֻ��ε�
#define ROUND_CX					4									//Բ�ǿ��
#define ROUND_CY					4									//Բ�Ǹ߶�

//��Ļλ��
#define BORAD_SIZE					5									//�߿��С
#define CAPTION_SIZE				79									//�����С

//��Ļ����
//#define LESS_LIST_CX				267/*285*/									//�б���
#define LIST_HALL_SPACE             6
#define LESS_LIST_CX				266+4									//�б���
#define SPLITTER_WIDTH				0									//��ֿ��

//��Ļ����
#define LESS_SCREEN_CY				740									//��С�߶�
#define LESS_SCREEN_CX				1024								//��С���

//////////////////////////////////////////////////////////////////////////////////

//���ư�ť
#define IDC_MIN						100									//��С��ť
#define IDC_MAX						101									//���ť
#define IDC_SKIN					102									//Ƥ����ť
#define IDC_CLOSE					103									//�رհ�ť
#define IDC_CERTIFICATE		    	104									//֤��

//���ư�ť
#define IDC_CONTROL					110									//���ư�ť
#define IDC_LOCK_LIST				111									//������ť

//�ؼ���ʶ
#define IDC_SERVER_LIST				300									//��Ϸ�б�
#define IDC_WEB_PUBLICIZE			301									//����ؼ�
#define IDC_SKIN_SPLITTER			302									//��ֿؼ�
#define IDC_SYSTEM_TRAY_ICON		303									//����ͼ��
#define IDC_BUTTON_GAMELIST			304								    //��Ϸ
#define IDC_BUTTON_GAMEMATCH		305									//����

//�ؼ���ʶ
#define IDC_VIEW_ITEM_CTRL			310									//������
#define IDC_USER_INFO_CTRL			311									//�û���Ϣ
#define IDC_MATCH_LIST              299                                 //��Ϸ�б�

//��Χ��ť
#define IDC_PLATFORM				400									//ƽ̨��ť
#define IDC_NAVIGATION				500									//������ť

//////////////////////////////////////////////////////////////////////////////////

//������Ŀ
#define MAX_SERVER_COUNT			5									//������Ŀ

//ʱ���ʶ
#define IDI_FLASH_TRAY_ICON			10									//����ͼ��
#define IDI_MESSAGE_POP				11									//��������
#define IDI_CLOSE_PAZZA				12									//�رտͻ���
#define IDI_REM_INSUREPASS			13									//���汣�չ�����

//ʱ���ʶ
#define IDI_TIMER_WEB               17
#define IDI_UPDATA_ONLINE			16									//��������
#define TIME_UPDATA_ONLINE			10000								//��������

//////////////////////////////////////////////////////////////////////////////////

#define IDM_RESTORE                 106                                 //��ԭ��ʾ
#define IDM_MINIMIZE                107                                 //��С����ʾ
#define IDM_MAXIMIZE                108                                 //�����ʾ

//////////////////////////////////////////////////////////////////////////////////

#define WM_INSUREPLAZA_UPDATA      (WM_USER+1680)                       //���и�����Ϣ
#define WM_INSTALL_CANCEL_EVENT     8888                                //��װ�¼�

struct tagInsurePlazaUpdata
{
	SCORE  lUserScore;
	SCORE  lUserInsure;
};

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CPlatformFrame * CPlatformFrame::m_pPlatformFrame=NULL;					//���ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)

	//ϵͳ��Ϣ
//	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_GETMINMAXINFO()
	ON_WM_SETTINGCHANGE()

	//��ť��Ϣ
	ON_BN_CLICKED((IDC_PLATFORM+0), OnBnClickedPlatform1)
//	ON_BN_CLICKED((IDC_PLATFORM+1), OnBnClickedPlatform2)
	ON_BN_CLICKED((IDC_PLATFORM+2), OnBnClickedPlatform3)

	//�Զ���Ϣ
	ON_MESSAGE(WM_HOTKEY, OnMessageHotKey)
	ON_MESSAGE(WM_TRAY_ICON, OnMessageTrayIcon)
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)
	ON_MESSAGE(WM_INSTALL_CANCEL_EVENT, OnMessageInstallCancelEvent)

	//�Զ���Ϣ
	ON_MESSAGE(WM_INSUREPLAZA_UPDATA, OnMessageInsurePlazaEvent)
	ON_MESSAGE(WM_SAFA_BIND,OnSafeBind)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CListEncircle::CListEncircle()
{
}

//��������
CListEncircle::~CListEncircle()
{
}

//�滭����
bool CListEncircle::PreDrawEncircleImage(tagEncircleBMP & EncircleImage)
{
	return true;
	//��������
	CDC * pDCL=CDC::FromHandle(EncircleImage.ImageTL.GetDC());
	CDC * pDCM=CDC::FromHandle(EncircleImage.ImageTM.GetDC());
	CDC * pDCR=CDC::FromHandle(EncircleImage.ImageTR.GetDC());
		
// 	CPngImageSB StationQQ;
// 	StationQQ.LoadImage(AfxGetInstanceHandle(),TEXT("QQ_INFO"));
// 	StationQQ.DrawImage(pDCR,30,0);
	//������Դ
	CPngImageSB ListTitleL;
	CPngImageSB ListTitleM;
	CPngImageSB ListTitleR;
	ListTitleL.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_L"));
	ListTitleM.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_M"));
	ListTitleR.LoadImage(AfxGetInstanceHandle(),TEXT("LIST_TITLE_R"));

	//������Դ
	//ListTitleL.DrawImage(pDCL,0,0);
	//ListTitleM.DrawImage(pDCM,0,0);
	//ListTitleR.DrawImage(pDCR,0,0);
	

	//�ͷ���Դ
	EncircleImage.ImageTL.ReleaseDC();
	EncircleImage.ImageTM.ReleaseDC();
	EncircleImage.ImageTR.ReleaseDC();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CFrameEncircle::CFrameEncircle()
{
}

//��������
CFrameEncircle::~CFrameEncircle()
{
}

//�滭����
bool CFrameEncircle::PreDrawEncircleImage(tagEncircleBMP & EncircleImage)
{
	//��������
	CDC * pDC=CDC::FromHandle(EncircleImage.ImageTL.GetDC());
	CDC * pDCR = CDC::FromHandle(EncircleImage.ImageTR.GetDC());

// 	CRect rcClient;
// 	GetClientRect(,&rcClient);
	//������Դ
	CPngImageSB StationLogo;
	CPngImageSB StationSmallLogo;
	CPngImageSB StationQQ;
	StationSmallLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_SMALL_LOGO"));
	StationLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_LOGO"));
	StationQQ.LoadImage(AfxGetInstanceHandle(),TEXT("QQ_INFO"));

	pDC->SetTextColor(RGB(255,255,255));
	//pDC->TextOut(28,7,TEXT("���������ơ�ҵ��������֤��ȫ���й�������"));
	//�����־
	StationSmallLogo.DrawImage(pDC,2,2);
	StationLogo.DrawImage(pDC,10,16);
	StationQQ.DrawImage(pDCR,320,40);
	EncircleImage.ImageTL.ReleaseDC();
	EncircleImage.ImageTR.ReleaseDC();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPlatformFrame::CPlatformFrame()
{
	//�������
	m_bMaxShow=false;
	m_bRectify=false;
	m_rcNormalSize.SetRect(0,0,0,0);
	m_dwAllOnLineCount=0;

	//״̬����
	m_bWhisperIcon=false;
	m_bHideGameList=false;
	m_bLockGameList=false;
	m_bAutoMenuEnable=FALSE;

	//�������
	m_pServerViewItem=NULL;

	//�������
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);

	//ƽ̨����
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

	//���ýӿ�
	CCustomFaceManager * pCustomFaceManager=CCustomFaceManager::GetInstance();
	pCustomFaceManager->SetCustomFaceEvent(QUERY_OBJECT_PTR_INTERFACE(this,IUnknownEx));

	//������Դ
	tagEncircleResource	EncircleItem;
	EncircleItem.pszImageTL=MAKEINTRESOURCE(IDB_ITEM_FRAME_TL);
	EncircleItem.pszImageTM=MAKEINTRESOURCE(IDB_ITEM_FRAME_TM);
	EncircleItem.pszImageTR=MAKEINTRESOURCE(IDB_ITEM_FRAME_TR);
	EncircleItem.pszImageML=MAKEINTRESOURCE(IDB_ITEM_FRAME_ML);
	EncircleItem.pszImageMR=MAKEINTRESOURCE(IDB_ITEM_FRAME_MR);
	EncircleItem.pszImageBL=MAKEINTRESOURCE(IDB_ITEM_FRAME_BL);
	EncircleItem.pszImageBM=MAKEINTRESOURCE(IDB_ITEM_FRAME_BM);
	EncircleItem.pszImageBR=MAKEINTRESOURCE(IDB_ITEM_FRAME_BR);
	m_ItemEncircle.InitEncircleResource(EncircleItem,AfxGetInstanceHandle());

	//�б���Դ
	tagEncircleResource	EncircleList;
	EncircleList.pszImageTL=MAKEINTRESOURCE(IDB_SERVER_LIST_TL);
	EncircleList.pszImageTM=MAKEINTRESOURCE(IDB_SERVER_LIST_TM);
	EncircleList.pszImageTR=MAKEINTRESOURCE(IDB_SERVER_LIST_TR);
	EncircleList.pszImageML=MAKEINTRESOURCE(IDB_SERVER_LIST_ML);
	EncircleList.pszImageMR=MAKEINTRESOURCE(IDB_SERVER_LIST_MR);
	EncircleList.pszImageBL=MAKEINTRESOURCE(IDB_SERVER_LIST_BL);
	EncircleList.pszImageBM=MAKEINTRESOURCE(IDB_SERVER_LIST_BM);
	EncircleList.pszImageBR=MAKEINTRESOURCE(IDB_SERVER_LIST_BR);
	m_ListEncircle.InitEncircleResource(EncircleList,AfxGetInstanceHandle());

	//��ܻ���
	tagEncircleResource	EncircleFrame;
	EncircleFrame.pszImageTL=MAKEINTRESOURCE(IDB_FRAME_TL);
	EncircleFrame.pszImageTM=MAKEINTRESOURCE(IDB_FRAME_TM);
	EncircleFrame.pszImageTR=MAKEINTRESOURCE(IDB_FRAME_TR);
	EncircleFrame.pszImageML=MAKEINTRESOURCE(IDB_FRAME_ML);
	EncircleFrame.pszImageMR=MAKEINTRESOURCE(IDB_FRAME_MR);
	EncircleFrame.pszImageBL=MAKEINTRESOURCE(IDB_FRAME_BL);
	EncircleFrame.pszImageBM=MAKEINTRESOURCE(IDB_FRAME_BM);
	EncircleFrame.pszImageBR=MAKEINTRESOURCE(IDB_FRAME_BR);
	m_FrameEncircle.InitEncircleResource(EncircleFrame,AfxGetInstanceHandle());

	m_wAVServerPort=0;
	m_dwAVServerAddr=0;
	m_pInsurePlaza = NULL;
	m_bShowVerify = true;

	return;
}

//��������
CPlatformFrame::~CPlatformFrame()
{
	//ƽ̨����
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) 
		m_pPlatformFrame=NULL;

	if (m_pInsurePlaza!=NULL)
	{
		SafeDelete(m_pInsurePlaza);
		m_pInsurePlaza = NULL;
	}
	return;
}

//�ӿڲ�ѯ
VOID * CPlatformFrame::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ICustomFaceEvent,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ICustomFaceEvent,Guid,dwQueryVer);
	return NULL;
}

//�����¼�
VOID CPlatformFrame::OnViewItemEvent(WORD wItemIndex, CWnd * pItemView)
{
	//�������
	bool bShowList=true;
	bool bPlazaView=(m_PlazaViewItem.m_hWnd==pItemView->GetSafeHwnd());

	//�����ж�
	if (bPlazaView==false) bShowList=m_bLockGameList;

	//�б����
	ControlServerList((bShowList==true)?ServerListControl_Show:ServerListControl_Hide,false);

	return;
}

//����¼�
VOID CPlatformFrame::OnSplitterEvent(UINT uControlID, INT nXPos, INT nYPos)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��ʾ�ؼ�
	if (m_bHideGameList==true)
	{
		//���ñ���
		m_bRectify=true;
		m_bHideGameList=false;
	
		//���ð�ť
		HINSTANCE hInstance=AfxGetInstanceHandle();
		//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,(m_bHideGameList==true)?TEXT("BT_GAME_LIST_SHOW"):TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);
	}

	//�����ؼ�
	RectifyControl(rcClient.Width(),rcClient.Height());

	return;
}

//����ʧ��
VOID CPlatformFrame::OnEventSystemFace(DWORD dwUserID, WORD wFaceID)
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//���ñ���
		pGlobalUserData->wFaceID=wFaceID;

		//��������
		pGlobalUserData->dwCustomID=0L;
		ZeroMemory(&pGlobalUserData->CustomFaceInfo,sizeof(pGlobalUserData->CustomFaceInfo));

		//�����¼�
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	return;
}

//ͷ������
VOID CPlatformFrame::OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo)
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//���ñ���
		pGlobalUserData->dwCustomID=dwCustomID;
		CopyMemory(&pGlobalUserData->CustomFaceInfo,&CustomFaceInfo,sizeof(CustomFaceInfo));

		//�����¼�
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	//��ǰ����
	if (m_pServerViewItem!=NULL)
	{
		m_pServerViewItem->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	//���·���
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		m_ServerViewItemArray[i]->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	return;
}

//��Ϣ����
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//�����
BOOL CPlatformFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//���ܰ�ť
	switch (nCommandID)
	{
	case IDC_BUTTON_GAMEMATCH:
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			m_btGameList.SetButtonImage(IDB_BT_GAMELIST1,hInstance,true,false);
			m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH,hInstance,true,false);
			m_ServerListView.ShowWindow(SW_HIDE);
			m_ServerMatchList.ShowWindow(SW_SHOW);
			return TRUE;
		}
	case  IDC_BUTTON_GAMELIST:
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			m_btGameList.SetButtonImage(IDB_BT_GAMELIST,hInstance,true,false);
			m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH1,hInstance,true,false);
			m_ServerMatchList.ShowWindow(SW_HIDE);
			m_ServerListView.ShowWindow(SW_SHOW);
			return TRUE;
		}
	case IDC_MIN:				//��С��ť
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_MAX:				//���ť
		{
			//���ڿ���
			if (m_bMaxShow==true)
			{
				RestoreWindow();
			}
			else
			{
				MaxSizeWindow();
			}

			//���½���
			RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_UPDATENOW);

			return TRUE;
		}
	case IDC_CLOSE:				//�رհ�ť
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_SKIN:				//�������
		{
			//��������
			if (m_DlgSkinControl.m_hWnd==NULL)
			{
				m_DlgSkinControl.Create(IDD_SKIN_CONTROL,this);
			}

			//��ȡλ��
			CRect rcButton;
			CRect rcControl;
			m_btSkin.GetWindowRect(&rcButton);
			m_DlgSkinControl.GetWindowRect(&rcControl);

			//��ʾ����
			UINT uFlags=SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;
			m_DlgSkinControl.SetWindowPos(NULL,rcButton.right-rcControl.Width(),rcButton.bottom,0,0,uFlags);

			return TRUE;
		}
	case IDC_CONTROL:			//���ư�ť
		{
			//�����б�
			ControlServerList(ServerListControl_Turn,true);

			return TRUE;
		}
	case IDC_LOCK_LIST:			//�����б�
		{
			//���ñ���
			//m_bLockGameList=!m_bLockGameList;

			////���ð�ť
			//HINSTANCE hInstance=AfxGetInstanceHandle();
			//m_btLockList.SetButtonImage(IDB_BK_LIST,(m_bLockGameList==true)?TEXT("BT_UNLOCK_LIST"):TEXT("BT_LOCK_LIST"),hInstance,true,false);

			return TRUE;
		}
	case IDC_NAVIGATION+2:
		{
			if(m_ServerViewItemArray.GetCount()<1)
			{
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				UINT wServerID = pGlobalServer->GetPlatInfo("PlatInfo","GSerVerID",0);
				if (wServerID>0)
				{
					CServerListData * pServerListData=CServerListData::GetInstance();
					if (pServerListData!=NULL) 
					{
						CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
						if (pGameServerItem!=NULL) 
						{
							EntranceServerItem(pGameServerItem,true);
							return true;
						}
					}
				}
			}
			OpenInSureDlg();
			return TRUE;
		}
	case IDC_NAVIGATION+0:
		{
			PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

			return TRUE;
		}
	case IDC_NAVIGATION+1:
		{
			//��������
 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
 			//�����ַ
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			TCHAR szPayServer[MAX_PATH]=TEXT("");
			CString sPayUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"PayServer",szPayServer,MAX_PATH);
	
 			//���ӵ�ַ
 			WebBrowse(sPayUrl,true);
 
 			return TRUE;
		}
	case IDC_NAVIGATION+3:       //�̳ǰ�ť
		{
			//��������
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//�����ַ
// 			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Navigation%ld.aspx"),pGlobalServer->GetPlatformServer(3),(nCommandID-IDC_NAVIGATION)+1);
// 
// 			//���ӵ�ַ
// 			WebBrowse(szNavigation,true);

			//��������
// 			CDlgService DlgService;
// 			DlgService.DoModal();
			//CInformation Information(this);
			//Information.ShowMessageBox(TEXT("�̳�ϵͳά���У������ڴ���"),MB_ICONINFORMATION,10);

			//��ҳ��
			//�����ַ
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			TCHAR szBrowseUrl[256]=TEXT("");
			_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/Shop/MallClient.aspx?type=0"),pGlobalServer->GetPlatformServer(3));

			CMessagePop DlgMobileBind ;
			DlgMobileBind.SetWindowSize(695,540,695,/*210-107+100*/540);
			DlgMobileBind.InitWebDlg(szBrowseUrl,"��Ϸ�̳�",true,false,0);
			//CDlgMobileBind DlgMobileBind;
			DlgMobileBind.DoModal();

			//�����ַ
			//CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			//TCHAR szNavigation[256]=TEXT("");
			//_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Shop/OnLineMall.aspx"),pGlobalServer->GetPlatformServer(3));
			//CMessagePop DlgMobileBind ;
			//DlgMobileBind.SetWindowSize(700,490,700,/*210-107+100*/450);
			//DlgMobileBind.InitWebDlg(szNavigation,"��Ϸ�̳�",true,false,0);
			//DlgMobileBind.DoModal();

			return TRUE;
		}
	case IDC_NAVIGATION+4:		//��ϵ�ͷ�
		{

			ASSERT(CParameterGlobal::GetInstance()!=NULL);
			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

			//��ϵ�ͷ�
			TCHAR szService[MAX_PATH]=TEXT("");
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			CString sServiceUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"QQService",szService,MAX_PATH,false);
			//ShellExecute(NULL,TEXT("OPEN"),sServiceUrl,NULL,NULL,SW_NORMAL);
			ShellExecute(NULL,TEXT("open"), TEXT("iexplore.exe"),sServiceUrl, NULL, SW_NORMAL); 

			//�����ַ
			TCHAR szNavigation[256]=TEXT("");
			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),pGlobalServer->GetPlatformServer(3));
			//���ӵ�ַ
			WebBrowse(szNavigation,true);

			return TRUE;

		}
	case IDC_NAVIGATION+5://
		{
			//��������
// 			ASSERT(CParameterGlobal::GetInstance()!=NULL);
// 			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
// 
// 			//�����ַ
// 			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 			TCHAR szNavigation[256]=TEXT("");
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/AskService.aspx"),pGlobalServer->GetPlatformServer(3));
// 			//��ҳ��
// 			ShellExecute(NULL,TEXT("OPEN"),szNavigation,NULL,NULL,SW_NORMAL);
// 
// 			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s/Service/IssueList.aspx"),pGlobalServer->GetPlatformServer(3));
// 			//���ӵ�ַ
// 			WebBrowse(szNavigation,true);
			return TRUE;
		}
	}

	//�˵�����
	switch (nCommandID)
	{
	case IDM_USER_LOGON:		//�û���¼
		{
			m_MissionLogon.ShowLogon();

			return TRUE;
		}
	case IDM_SWITCH_ACCOUNTS:	//�л��ʺ�
		{
			//�л�ѯ��
			if ((m_ServerViewItemArray.GetCount()>0L)||(m_pServerViewItem!=NULL))
			{
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("���е���Ϸ���伴���رգ�ȷʵҪ���л��ʺš��� "),MB_YESNO)!=IDYES) return TRUE;
			}

			//��������
			KillTimer(IDI_MESSAGE_POP);
			m_MissionLogon.SetLoginSocketType(2);
			//if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
			//{
				//����ʧ�ܣ��رմ���
				ClosePazza(2);
			//}
			return TRUE;
		}
	case IDM_RESTORE:   //��ԭ
		{
			if(IsIconic())
			{
				ShowWindow(SW_RESTORE);
			}
			return TRUE;
		}
	case IDM_MINIMIZE:  //��С��
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDM_MAXIMIZE:  //���
		{
			if(IsIconic())
			{
				ShowWindow(SW_RESTORE);
			}
			MaxSizeWindow();
			return TRUE;
		}
	//case SC_RESTORE :
	//	{
	//		if(IsIconic())
	//		{
	//			ShowWindow(SW_RESTORE);
	//		}
	//		return TRUE;
	//	}
	}

	return __super::OnCommand(wParam,lParam);
}

VOID CPlatformFrame::OpenInSureDlg()
{
	//��������
	bool bGoldServer=false;
	CServerViewItem * pServerViewGold=NULL;

	//���ҷ���
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_ServerViewItemArray[i]!=NULL);
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];

		//��������
		WORD wServerType=pServerViewItem->GetServerType();
		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();

		//���鷿
		if(CServerRule::IsTrainRoom(pServerViewItem->GetServerRule()))
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			if (Information.ShowMessageBox(TEXT("�����ڵ���Ϸ�����ݲ�֧�ֱ��չ���"),MB_OK|MB_ICONWARNING,10)!=IDYES)
			{
				return;
			}		
			return;
		}
		//�����ж�
		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
		{
			//���ñ���
			bGoldServer=true;
			pServerViewGold=pServerViewItem;

			break;
		}
	}
			//m_sRemInsurePwd = "1234567";
	if (m_sRemInsurePwd == "") //û�б��汣�չ�����
	{
		CVerifyInsurePass dlgVefifyPass;
		int nRet;
		if((nRet=dlgVefifyPass.DoModal()) == 1)
		{
			int aa = 2;
		}
		else
		{
			return;
		}
	}



	//������Դ
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

	//��������
	if (bGoldServer==false)
	{
		//�㳡����
		/*			CDlgInsurePlaza DlgInsurePlaza;
		_sntprintf(DlgInsurePlaza.m_szSaveInsurePass,CountArray(DlgInsurePlaza.m_szSaveInsurePass),m_sRemInsurePwd);
		INT_PTR nResult=DlgInsurePlaza.DoModal();*/
		if (m_pInsurePlaza!=NULL)
		{
			m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
			m_pInsurePlaza->SwitchInsureModeView(1);
			m_pInsurePlaza->QueryUserInsureInfo();
			m_pInsurePlaza->CenterWindow();
			m_pInsurePlaza->ShowWindow(SW_SHOW);
		}
		else
		{
			m_pInsurePlaza = new CDlgInsurePlaza;
			//_sntprintf(m_pInsurePlaza->m_szSaveInsurePass,CountArray(m_pInsurePlaza->m_szSaveInsurePass),m_sRemInsurePwd);
			m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
			m_pInsurePlaza->Create(424,this);
			m_pInsurePlaza->CenterWindow();
			m_pInsurePlaza->SetForegroundWindow();
			m_pInsurePlaza->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		if (m_pInsurePlaza!=NULL)
		{
			m_pInsurePlaza->DestroyWindow();
			m_pInsurePlaza= NULL;
		}
		//��������
		ASSERT(pServerViewGold!=NULL);
		pServerViewGold->ShowInsureView(m_sRemInsurePwd);
	}
	AfxSetResourceHandle(hInstResourceClient);
}

//�����ؼ�
VOID CPlatformFrame::RectifyControl(INT nWidth, INT nHeight)
{
	//״̬�ж�
	if ((nWidth==0)||(nHeight==0)) return;

	//���λ��
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//������Ϣ
	tagEncircleInfo EncircleInfoList;
	tagEncircleInfo EncircleInfoItem;
	tagEncircleInfo EncircleInfoFrame;
	m_ListEncircle.GetEncircleInfo(EncircleInfoList);
	m_ItemEncircle.GetEncircleInfo(EncircleInfoItem);
	m_FrameEncircle.GetEncircleInfo(EncircleInfoFrame);

	//��ȡλ��
	ScreenToClient(&rcSplitter);

	//��ֿؼ�
	if (m_bHideGameList==false)
	{
		//��ַ�Χ
		INT nLessPos=nWidth*28/100,nMaxPos=nWidth/2;
		if (nLessPos>=LESS_LIST_CX) 
			nLessPos=LESS_LIST_CX;

		//�������
		if (m_bRectify==false)
		{
			m_bRectify=true;
			rcSplitter.left=nLessPos;
			rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
		}

		//��ַ�Χ
		m_SkinSplitter.SetSplitterRange(nLessPos,nMaxPos);

		//����λ��
		if ((nWidth!=0)&&(nHeight!=0))
		{
			if (rcSplitter.left<nLessPos)
			{
				rcSplitter.left=nLessPos;
				rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
			}
			if (rcSplitter.right>nMaxPos)
			{
				rcSplitter.right=nMaxPos;
				rcSplitter.left=rcSplitter.right-SPLITTER_WIDTH;
			}
		}
	}
	else 
	{
		//���λ��
		rcSplitter.left=EncircleInfoFrame.nLBorder;
		rcSplitter.right=rcSplitter.left+SPLITTER_WIDTH;
	}

	//λ�õ���
	rcSplitter.top=EncircleInfoFrame.nTBorder;
	rcSplitter.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//�ؼ�λ��
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//���ư�ť
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-37,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-72,1,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-98,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSkin,NULL,nWidth-130,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btCertificate,NULL,nWidth-162,3,0,0,uFlags|SWP_NOSIZE);

	//������ť
	CRect rcNavigation;
	m_btNavigation[0].GetWindowRect(&rcNavigation);

	//������ť
	INT nNavigationArea=rcNavigation.Width()*CountArray(m_btNavigation);
	INT nSpace=__min(__max((nWidth-nNavigationArea-890)/(CountArray(m_btNavigation)+1),0),30);


	//������ť
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		INT nIndex=CountArray(m_btNavigation)-i;
		if (nSpace == 30)
		{	
			int nSp = nSpace - 10;
			//m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,AfxGetInstanceHandle(),true,false);	
			//m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION3,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,AfxGetInstanceHandle(),true,false);
			
			INT nXExcursion=nWidth-(rcNavigation.Width()+nSp)*nIndex-nSp-215-55+120;
			DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,32,0,0,uFlags|SWP_NOSIZE);
		}else
		{
			//m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,AfxGetInstanceHandle(),true,false);	
			//m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION3,AfxGetInstanceHandle(),true,false);
			//m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,AfxGetInstanceHandle(),true,false);
			
			INT nXExcursion=nWidth-(rcNavigation.Width()+nSpace+17)*nIndex-nSpace-210;
			DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,32,0,0,uFlags|SWP_NOSIZE);
		}
	}

	//ƽ̨��ť
	CRect rcPlatform;
//	m_btPlatform[0].GetWindowRect(&rcPlatform);

	//ƽ̨��ť
//	INT nYPlatform=EncircleInfoFrame.nTBorder+2L;
//	DeferWindowPos(hDwp,m_btPlatform[0],NULL,nWidth-(rcPlatform.Width()+7)*3-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[0],NULL,nWidth-(rcPlatform.Width()+7)*2-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[1],NULL,nWidth-(rcPlatform.Width()+7)*2-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);
//	DeferWindowPos(hDwp,m_btPlatform[2],NULL,nWidth-(rcPlatform.Width()+7)*1-EncircleInfoFrame.nRBorder-10,nYPlatform,0,0,uFlags|SWP_NOSIZE);

	//������ť
	//CRect rcLockList;
	//m_btLockList.GetWindowRect(&rcLockList);
	//DeferWindowPos(hDwp,m_btLockList,NULL,rcSplitter.left-rcLockList.Width()-13,EncircleInfoFrame.nTBorder+rcUserInfoCtrl.Height()+4,
	//	rcLockList.Width(),rcLockList.Height(),uFlags); 

	//ҳ��λ��
	//m_WndViewItemCtrl.SetViewItemPostion(rcSplitter.right+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder,
	//	nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItem.nRBorder-EncircleInfoItem.nLBorder-rcSplitter.right,
	//	nHeight-EncircleInfoFrame.nTBorder-EncircleInfoFrame.nBBorder-EncircleInfoItem.nTBorder-EncircleInfoItem.nBBorder);

	//������ 
	//CSize SizeItemFrame; 
	//m_WndViewItemCtrl.GetViewItemSize(SizeItemFrame);
	//DeferWindowPos(hDwp,m_WndViewItemCtrl,NULL,rcSplitter.right+10,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder-SizeItemFrame.cy,
	//	SizeItemFrame.cx,SizeItemFrame.cy,uFlags);

	//ҳ��λ��
	m_WndViewItemCtrl.SetViewItemPostion(rcSplitter.right+LIST_HALL_SPACE+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder/*-SizeItemFrame.cy*/,
		nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItem.nRBorder-EncircleInfoItem.nLBorder-rcSplitter.right-LIST_HALL_SPACE,
		nHeight-EncircleInfoFrame.nTBorder-EncircleInfoFrame.nBBorder-EncircleInfoItem.nTBorder-EncircleInfoItem.nBBorder);

	//������ 
	CSize SizeItemFrame; 
	m_WndViewItemCtrl.GetViewItemSize(SizeItemFrame);
	DeferWindowPos(hDwp,m_WndViewItemCtrl,NULL,rcSplitter.right+LIST_HALL_SPACE+EncircleInfoItem.nLBorder,EncircleInfoFrame.nTBorder+EncircleInfoItem.nTBorder-SizeItemFrame.cy,
		SizeItemFrame.cx,SizeItemFrame.cy,uFlags);


	//�����ؼ�
	DeferWindowPos(hDwp,m_SkinSplitter,NULL,rcSplitter.left,rcSplitter.top,rcSplitter.Width(),rcSplitter.Height(),uFlags);
	DeferWindowPos(hDwp,m_WndUserInfoCtrl,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder,rcSplitter.left-EncircleInfoFrame.nLBorder,rcUserInfoCtrl.Height(),uFlags);
	DeferWindowPos(hDwp,m_PlatformPublicize,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+rcUserInfoCtrl.Height(),rcSplitter.left-EncircleInfoFrame.nLBorder,27,uFlags);

	DeferWindowPos(hDwp,m_btGameList,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+rcUserInfoCtrl.Height(),(rcSplitter.left - EncircleInfoFrame.nLBorder)/2,32,uFlags);
	DeferWindowPos(hDwp,m_btGameMatch,NULL,EncircleInfoFrame.nLBorder+ (rcSplitter.left - EncircleInfoFrame.nLBorder)/2,EncircleInfoFrame.nTBorder+27+rcUserInfoCtrl.Height(),(rcSplitter.left - EncircleInfoFrame.nLBorder)/2,32,uFlags);
	
	DeferWindowPos(hDwp,m_ServerListView,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+32+rcUserInfoCtrl.Height(),
		rcSplitter.left-EncircleInfoFrame.nLBorder,nHeight-/*EncircleInfoFrame.nTBorder-*/rcUserInfoCtrl.bottom-27-32-EncircleInfoFrame.nBBorder-1,uFlags);

	DeferWindowPos(hDwp,m_ServerMatchList,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+27+32+rcUserInfoCtrl.Height(),
		rcSplitter.left-EncircleInfoFrame.nLBorder,nHeight-/*EncircleInfoFrame.nTBorder-*/rcUserInfoCtrl.bottom-27-32-EncircleInfoFrame.nBBorder-1,uFlags);
	//m_WndUserInfoCtrl.ShowWindow(SW_HIDE);
	CRect rcList;
    m_ServerListView.GetWindowRect(&rcList);
	//m_ServerListView.ShowWindow(SW_HIDE);
	//m_btGameMatch.ShowWindow(SW_HIDE);
	//m_btGameList.ShowWindow(SW_HIDE);

	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	//���ư�ť
	CRect rcControl;
	//m_btControl.GetClientRect(&rcControl);
	//m_btControl.SetWindowPos(NULL,(rcSplitter.Width()-rcControl.Width())/2,(rcSplitter.Height()-rcControl.Height())/2,0,0,uFlags|SWP_NOSIZE);

	//���½���
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return;
}

//���ҳ��
bool CPlatformFrame::WebBrowse(LPCTSTR pszURL, bool bAutoFullView)
{
	//���ҳ��
	CPlazaViewItem::GetInstance()->WebBrowse(pszURL);

	//�������
	m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

	//�������
	if (bAutoFullView==true)
	{
		CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
		if (pParameterGlobal->m_bFullScreenBrowse==true) ControlServerList(ServerListControl_Hide,false);
	}

	return true;
}

//�б����
bool CPlatformFrame::ControlServerList(enServerListControl ServerListControl, bool bFocusControl)
{
	//λ�ÿ���
	bool bHideGameList=false;
	switch (ServerListControl)
	{
	case ServerListControl_Hide: { bHideGameList=true; break; }
	case ServerListControl_Show: { bHideGameList=false; break; }
	case ServerListControl_Turn: { bHideGameList=!m_bHideGameList; break; }
	}

	//���ƹ���
	if ((bHideGameList==true)&&(bFocusControl==false)&&(m_bLockGameList==true))
	{
		return true;
	}

	//�����ж�
	if (bHideGameList!=m_bHideGameList)
	{
		//���ñ���
		m_bRectify=false;
		m_bHideGameList=bHideGameList;

		//���ð�ť
		HINSTANCE hInstance=AfxGetInstanceHandle();
		//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,(m_bHideGameList==true)?TEXT("BT_GAME_LIST_SHOW"):TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);

		//��������
		CRect rcClient;
		GetClientRect(&rcClient);
		RectifyControl(rcClient.Width(),rcClient.Height());
	}

	return true;
}

//��ȡ˽��
bool CPlatformFrame::ShowWhisperItem()
{
	//��ȡ��Ϣ
	if (m_DlgWhisperItemArray.GetCount()>0L)
	{
		//��ȡ����
		CDlgWhisper * pDlgWhisper=m_DlgWhisperItemArray[0];

		//��ʾ����
		pDlgWhisper->ShowWindow(SW_RESTORE);

		//�ö�����
		pDlgWhisper->SetActiveWindow();
		pDlgWhisper->BringWindowToTop();
		pDlgWhisper->SetForegroundWindow();

		//ɾ������
		m_DlgWhisperItemArray.RemoveAt(0L);

		//ɾ��ͼ��
		if (m_DlgWhisperItemArray.GetCount()==0L)
		{
			//���ñ���
			m_bWhisperIcon=false;

			//ɾ��ʱ��
			KillTimer(IDI_FLASH_TRAY_ICON);

			//����ͼ��
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
		}

		return true;
	}

	return false;
}

//����˽��
bool CPlatformFrame::InsertWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//����Ч��
	ASSERT((pDlgWhisper!=NULL)&&(pDlgWhisper->m_hWnd!=NULL));
	if ((pDlgWhisper==NULL)||(pDlgWhisper->m_hWnd==NULL)) return false;

	//״̬�ж�
	if (pDlgWhisper->IsWindowVisible()) return false;

	//��������
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper) return false;
	}

	//����˽��
	m_DlgWhisperItemArray.Add(pDlgWhisper);

	//����ͼ��
	if (m_DlgWhisperItemArray.GetCount()==1L)
	{
		//���ñ���
		m_bWhisperIcon=true;

		//����ʱ��
		SetTimer(IDI_FLASH_TRAY_ICON,500,NULL);

		//����ͼ��
		m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_WHISPER)));
	}

	return true;
}

//ɾ��˽��
bool CPlatformFrame::RemoveWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//��������
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper)
		{
			//ɾ������
			m_DlgWhisperItemArray.RemoveAt(i);

			//ɾ��ͼ��
			if (m_DlgWhisperItemArray.GetCount()==0L)
			{
				//���ñ���
				m_bWhisperIcon=false;

				//ɾ��ʱ��
				KillTimer(IDI_FLASH_TRAY_ICON);

				//����ͼ��
				m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
			}

			return true;
		}
	}

	return false;
}

//�����
bool CPlatformFrame::ActiveServerViewItem(CServerViewItem * pServerViewItem)
{
	//�����ж�
	if (m_pServerViewItem==pServerViewItem)
	{
		//���ñ���
		m_pServerViewItem=NULL;

		//���뷿��
		m_ServerViewItemArray.Add(pServerViewItem);

		//�����ǩ
		LPCTSTR pszKindName(pServerViewItem->GetKindName());
		m_WndViewItemCtrl.InsertViewItem(pServerViewItem,pszKindName);
	}

	//�����
	m_WndViewItemCtrl.ActiveViewItem(pServerViewItem);

	return true;
}

//ɾ������
bool CPlatformFrame::DeleteServerViewItem(CServerViewItem * pServerViewItem)
{
	//��ǰ����
	if ((m_pServerViewItem!=NULL)&&(m_pServerViewItem==pServerViewItem))
	{
		//״̬�ж�
		if(pServerViewItem->IsPlayingMySelf() && pServerViewItem->GetServiceStatus() !=ServiceStatus_NetworkDown)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			if (Information.ShowMessageBox(TEXT("��������Ϸ�У�ǿ���˳������۷֣�ȷʵҪǿ����"),MB_ICONQUESTION|MB_YESNO,0)!=IDYES)
			{
				return false;
			}
			pServerViewItem->OnGameProcessClose(0);
		}

		//���ñ���
		m_pServerViewItem=NULL;

		//���ٷ���
		pServerViewItem->DestroyWindow();

		return true;
	}

	//��������
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		if (m_ServerViewItemArray[i]==pServerViewItem)
		{ 
			//״̬�ж�
			if(pServerViewItem->IsPlayingMySelf() && pServerViewItem->GetServiceStatus() !=ServiceStatus_NetworkDown)
			{
				//��ʾ��Ϣ
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("��������Ϸ�У�ǿ���˳������۷֣�ȷʵҪǿ����"),MB_ICONQUESTION|MB_YESNO,0)!=IDYES)
				{
					return false;
				}
				pServerViewItem->OnGameProcessClose(0);
			}

			//���ٷ���
			pServerViewItem->DestroyWindow();
			m_ServerViewItemArray.RemoveAt(i);

			//ɾ������
			m_WndViewItemCtrl.RemoveViewItem(pServerViewItem);
			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//����֪ͨ
			CDlgSearchUser * pDlgSearchUser=CDlgSearchUser::GetInstance();
			if (pDlgSearchUser!=NULL) pDlgSearchUser->OnViewItemDelete(pServerViewItem);

			return true;
		}
	}

	return false;
}

//ö�ٷ���
CServerViewItem * CPlatformFrame::EmunServerViewItem(WORD wIndex)
{
	//�����ж�
	if (wIndex<m_ServerViewItemArray.GetCount())
	{
		return m_ServerViewItemArray[wIndex];
	}

	return NULL;
}

//���ҷ���
CServerViewItem * CPlatformFrame::SearchServerViewItem(WORD wServerID)
{
	//���ҷ���
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem->GetServerID()==wServerID) return pServerViewItem;
	}

	return NULL;
}

//���뷿��
CServerViewItem * CPlatformFrame::EntranceServerItem(CGameKindItem * pGameKindItem)
{
	return NULL;
}

//���뷿��
CServerViewItem * CPlatformFrame::EntranceServerItem(CGameServerItem * pGameServerItem,bool bOpenInsureDlg)
{
	//Ч�����
	ASSERT(pGameServerItem!=NULL);
	if (pGameServerItem==NULL) return NULL;

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	//��¼�ж�
	if (pGlobalUserData->dwUserID==0L) return NULL;

	//��������
	tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
	tagGameKind * pGameKind=&pGameServerItem->m_pGameKindItem->m_GameKind;

	//���ҷ���
	WORD wServerID=pGameServer->wServerID;
	CServerViewItem * pServerViewItem=SearchServerViewItem(wServerID);

	//�����
	if (pServerViewItem!=NULL)
	{
		ActiveServerViewItem(pServerViewItem);
		return pServerViewItem;
	}

	//��ǰ�ж�
	if (m_pServerViewItem!=NULL)
	{
		if(m_pServerViewItem->GetServiceStatus() == ServiceStatus_NetworkDown)
		{
			DeleteServerViewItem(m_pServerViewItem);
		}
		else
		{
			//��ͬ�ж�
			if (wServerID==m_pServerViewItem->GetServerID()) 
				return pServerViewItem;

			//��ʾ��Ϣ
			TCHAR szBuffer[256]=TEXT("");
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("���ڽ��� [ %s ] ��Ϸ�����У����Ժ�ȴ�Ƭ��..."),m_pServerViewItem->GetServerName());

			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(szBuffer,MB_OK|MB_ICONWARNING,30);

			return m_pServerViewItem;

		}
	}

	//��Ա����
	if (m_ServerViewItemArray.GetCount()>=MAX_SERVER_COUNT)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������Ϸ����̫���ˣ���رղ��ֺ��ٴγ��ԣ�"),MB_ICONQUESTION,60);

		return NULL;
	}

	//��װ�ж�
	if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
	{
		//��ȡ�汾
		CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;
		CWHService::GetModuleVersion(pGameKind->szProcessName,pGameKindItem->m_dwProcessVersion);

		//������Ϸ
		if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
		{
			CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
			pCGlobalUnits->DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,wServerID,pGameKind->szProcessName);

			return NULL;
		}

		//�����б�
		m_ServerListView.OnGameItemUpdate(pGameKindItem);
	}

	//�󶨲���
	SCORE myTotalScore = pGlobalUserData->lUserScore + pGlobalUserData->lUserInsure;
	if (m_bShowVerify && myTotalScore > 1000000 && (!pGlobalUserData->cbMoorMachine || !pIndividualUserData->cbMoorPassPortID || !pIndividualUserData->cbMoorPhone))
	{
		//������ʾ
		CString sCoinStr;
		sCoinStr = "����ǰ����ܶ���࣬Ϊ�����Ľ�Ұ�ȫ����󶨱��������֤���ֻ��ٽ�����Ϸ�������ȷ�������а󶨡�";
		//�˳��ж�
		m_bShowVerify = false;
		CInformation Information(CPlatformFrame::GetInstance());
		if(Information.ShowMessageBox(sCoinStr,MB_ICONINFORMATION|MB_OKCANCEL,0,false) == IDOK)
		{			//��ʾ����
			CDlgLockMachine DlgLockMachine;
			DlgLockMachine.DoModal();
			return NULL;
		}
	}

	//��������
	try
	{
		//��������
		m_pServerViewItem=new CServerViewItem;
		m_pServerViewItem->Create(IDD_GAME_SERVER,this);

		//���÷���
		m_pServerViewItem->InitServerViewItem(pGameServerItem,m_wAVServerPort,m_dwAVServerAddr,false,bOpenInsureDlg);
	}
	catch (LPCTSTR pszString)
	{
		//���ٷ���
		if (m_pServerViewItem!=NULL)
		{
			if (m_pServerViewItem->m_hWnd!=NULL)
			{
				m_pServerViewItem->DestroyWindow();
			}
			//else
			//{
				SafeDelete(m_pServerViewItem);
			//}
		}

		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(pGameServer->szServerName,pszString,MB_ICONERROR);

		return NULL;
	}

	return m_pServerViewItem;
}

//��ԭ����
bool CPlatformFrame::RestoreWindow()
{
	//״̬�ж�
	if (m_bMaxShow==true)
	{
		//���ñ���
		m_bMaxShow=false;
		m_bRectify=false;

		//���ð�ť
		m_btMax.SetButtonImage(IDB_BT_MAX,AfxGetInstanceHandle(),true,false);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//��󴰿�
bool CPlatformFrame::MaxSizeWindow()
{
	//״̬�ж�
	if (m_bMaxShow==false)
	{
		//���ñ���
		m_bMaxShow=true;
		m_bRectify=false;

		//Ĭ��λ��
		GetWindowRect(&m_rcNormalSize);

		//���ð�ť
		m_btMax.SetButtonImage(IDB_BT_RESORE,AfxGetInstanceHandle(),true,false);

		//��ȡλ��
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//�ر���Ϣ
VOID CPlatformFrame::OnClose()
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//�ر���ʾ
	if ((pGlobalUserData->dwUserID!=0L)&&(m_MissionLogon.GetActiveStatus()==false))
	{
		//��ʾ����
		CDlgEnquire DlgEnquire;
		INT_PTR nResult=DlgEnquire.DoModal();

		//�����
		switch (nResult)
		{
		case IDCANCEL:				//ȡ������
			{
				return;
			}
		case IDC_CLOSE_SERVER:		//�˳�����
			{
				//�رշ���
				ASSERT(m_WndViewItemCtrl.GetActiveItem()>0);
				WORD wActiveItem=m_WndViewItemCtrl.GetActiveItem();
				
				//�رշ���
				if (wActiveItem>=1)
				{
					ASSERT((wActiveItem-1)<m_ServerViewItemArray.GetCount());
					DeleteServerViewItem(m_ServerViewItemArray[wActiveItem-1]);
				}

				return;
			}
		case IDC_SWITCH_ACCOUNTS:	//�л��ʺ�
			{
				//Ͷ����Ϣ
				PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

				return;
			}
		//case IDC_CLOSE_PLAZA:	//�رմ���
		//	{
		//		//ȫ������
		//		KillTimer(IDI_MESSAGE_POP);
		//		//��������
		//		m_MissionLogon.SetLoginInOrOut(true);
		//		if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
		//		{
		//			//����ʧ�ܣ��رմ���
		//			ClosePazza();
		//		}
		//		return;
		//	}
		}
	}

	KillTimer(IDI_MESSAGE_POP);
	//////////////////////////////////////////////////////////////////////////
	CGlobalUnits::GetInstance()->DeleteUserCookie();
	CGlobalUserInfo::GetInstance()->ResetUserInfoData();
	UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

	__super::OnClose();
	return;
	//////////////////////////////////////////////////////////////////////////
	if (m_MissionLogon.BHaveLogonIn()) //�Ѿ���¼
	{
		//��������
		m_MissionLogon.SetLoginSocketType(1);
		if (!m_MissionLogon.GetMissionManager()->AvtiveMissionItem(&m_MissionLogon,false))
		{
			//����ʧ�ܣ��رմ���
			ClosePazza(1);
		}
		return;
	}
	ClosePazza(1);
	//ע���ȼ�
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

	//__super::OnClose();
}

//�滭����
BOOL CPlatformFrame::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,RGB(10,111,167));

	//���λ��5
	tagEncircleInfo ItemEncircleInfo;
	tagEncircleInfo FrameEncircleInfo;
	m_ItemEncircle.GetEncircleInfo(ItemEncircleInfo);
	m_FrameEncircle.GetEncircleInfo(FrameEncircleInfo);

	//���λ��
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//���λ��
	CRect rcWebPublicize;
	//m_PlatformPublicize.GetWindowRect(&rcWebPublicize);

	//λ��ת��
	ScreenToClient(&rcSplitter);
	ScreenToClient(&rcWebPublicize);

	//�ؼ�λ��
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);
/*
	//��Ϸ�б�
	if (false)
	//if (m_bHideGameList==false)
	{
		//�б�λ��
		CRect rcList;
		rcList.right=rcSplitter.left;
		rcList.left=FrameEncircleInfo.nLBorder;
		rcList.top=FrameEncircleInfo.nTBorder+rcUserInfoCtrl.Height();
		rcList.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;
		//m_ServerListView.GetWindowRect(&rcList);

		ScreenToClient(&rcList);
		//��������
		CImage ImageBuffer;
		ImageBuffer.Create(rcList.Width(),rcList.Height(),32);

		//���� DC
		CDC BufferDC;
		BufferDC.CreateCompatibleDC(pDC);
		BufferDC.SelectObject(ImageBuffer);

		//���û���
		BufferDC.SetBkMode(TRANSPARENT);
		BufferDC.SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

		//�滭�б�
		CRect rcBuffer(0,0,rcList.Width(),rcList.Height());
		//m_ListEncircle.DrawEncircleFrame(&BufferDC,rcBuffer);


		//BufferDC.FillSolidRect(&rcList,RGB(236,243,249));
		BufferDC.FillSolidRect(&rcList,RGB(0,255,0));
		//�����ַ�
		//TCHAR szOnLineInfo[32]=TEXT("");
		//_sntprintf(szOnLineInfo,CountArray(szOnLineInfo),TEXT("������ף����Ϸ���"),m_dwAllOnLineCount);

		//�滭��Ϣ
		//BufferDC.SetTextColor(RGB(0,0,0));
		//BufferDC.TextOut(10,7,szOnLineInfo,lstrlen(szOnLineInfo));

		//�滭����
		pDC->BitBlt(rcList.left,rcList.top,rcList.Width(),rcList.Height(),&BufferDC,0,0,SRCCOPY);

		//������Դ
		BufferDC.DeleteDC();
		ImageBuffer.Destroy();
	}
*/
	//������
	CRect rcItem;
	rcItem.left=rcSplitter.right+LIST_HALL_SPACE;
	rcItem.top=FrameEncircleInfo.nTBorder;
	rcItem.right=rcClient.Width()-FrameEncircleInfo.nRBorder;
	rcItem.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;

	//�滭���
	m_ItemEncircle.DrawEncircleFrame(pDC,rcItem);
	m_FrameEncircle.DrawEncircleFrame(pDC,rcClient);
	//////////////////////////////////////////////////////////////////////////
	//CRect rcList;
	//rcList.right=rcSplitter.left;
	//rcList.left=FrameEncircleInfo.nLBorder;
	//rcList.top=FrameEncircleInfo.nTBorder+rcUserInfoCtrl.Height()+27+32;
	//rcList.bottom=rcClient.Height()-FrameEncircleInfo.nBBorder;

	//CDC dcMem;
	//CBitmap bmp; //�ڴ��г�����ʱͼ���λͼ

	//dcMem.CreateCompatibleDC(pDC); //��������DC���������ڴ�DC
	////��������λͼ(������pDC���������򻭳���ͼ�α�ɺ�ɫ)
	//bmp.CreateCompatibleBitmap(pDC,rcList.Width(),rcList.Height());
	//CBitmap *pOldBit=dcMem.SelectObject(&bmp);
	////��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
	//dcMem.FillSolidRect(rcList,RGB(255,255,255));
	////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////
	//pDC->BitBlt(rcList.left,rcList.top,rcList.Width(),rcList.Height(),&dcMem,0,0,SRCCOPY);
	////���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	////��ͼ��ɺ������
	//dcMem.DeleteDC();     //ɾ��DC
	//bmp.DeleteObject(); //ɾ��λͼ
	//////////////////////////////////////////////////////////////////////////

	return TRUE;
}

//��������
LRESULT CPlatformFrame::OnNcHitTest(CPoint Point)
{
	//��ť����
	if (m_bMaxShow==false)
	{
		//��ȡλ��
		CRect rcClient;
		GetClientRect(&rcClient);

		//ת��λ��
		CPoint ClientPoint=Point;
		ScreenToClient(&ClientPoint);

		//����λ��
		if (ClientPoint.x<=BORAD_SIZE)
		{
			if (ClientPoint.y<=CAPTION_SIZE) return HTTOPLEFT;
			if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOMLEFT;
			return HTLEFT;
		}

		//����λ��
		if (ClientPoint.x>=(rcClient.Width()-BORAD_SIZE))
		{
			if (ClientPoint.y<=CAPTION_SIZE) return HTTOPRIGHT;
			if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOMRIGHT;
			return HTRIGHT;
		}

		//����λ��
		if (ClientPoint.y<=BORAD_SIZE) return HTTOP;
		if (ClientPoint.y>=(rcClient.Height()-BORAD_SIZE)) return HTBOTTOM;
	}
	else
		return HTBORDER; 

	return __super::OnNcHitTest(Point);
}

//ʱ����Ϣ
VOID CPlatformFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_FLASH_TRAY_ICON:	//����ͼ��
		{
			//���ñ���
			m_bWhisperIcon=!m_bWhisperIcon;

			//����ͼ��
			UINT uIconID=(m_bWhisperIcon==true)?IDI_WHISPER:IDR_MAINFRAME;
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(uIconID)));

			return;
		}
	case IDI_UPDATA_ONLINE:
		{
			UpDataAllOnLineCount();
			return;
		}	
	case IDI_TIMER_WEB:
		 {
			 KillTimer(IDI_TIMER_WEB);
			 //����ҳ
			 CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			 ASSERT(CPlatformFrame::GetInstance()!=NULL);
/*			 CString sMainUrl;
			 sMainUrl.Format("%s/index.aspx",pGlobalServer->GetPlatformServer(3))*/;
			 CPlatformFrame::GetInstance()->WebBrowse(m_sMainUrl,false);
		 }

	case IDI_MESSAGE_POP:
		{
			KillTimer(IDI_MESSAGE_POP);
			PopSysMessage();
			return;
		}
	case IDI_CLOSE_PAZZA:
		{
			KillTimer(IDI_CLOSE_PAZZA);

			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
			UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
			UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);

			__super::OnClose();
			return;
		}
	case IDI_REM_INSUREPASS:
		{
			KillTimer(IDI_REM_INSUREPASS);
			m_sRemInsurePwd = "";
		}

	}

	__super::OnTimer(nIDEvent);
}

//λ����Ϣ
VOID CPlatformFrame::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	//��������
	CRgn WindowRgn;
	WindowRgn.CreateRoundRectRgn(0,0,cx+1,cy+1,ROUND_CX,ROUND_CY);

	//��������
	SetWindowRgn(WindowRgn,TRUE);

	return;
}

//λ����Ϣ
VOID CPlatformFrame::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);

	//����λ��
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//����λ��
	lpMMI->ptMinTrackSize.x=__min(LESS_SCREEN_CX,rcArce.Width());
	lpMMI->ptMinTrackSize.y=__min(LESS_SCREEN_CY,rcArce.Height());

	return;
}

//������Ϣ
INT CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ô���
	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);
	//ע��dll
	RegisterDll();

	//�����ַ
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();

	TCHAR szMainUrl[MAX_PATH]=TEXT("");
	m_sMainUrl = pGlobalServer->ReadPlatFileString(TEXT("ServerInfo"),"MainUrl",szMainUrl,MAX_PATH,false);
	if (m_sMainUrl == "")
	{
		m_sMainUrl = "http://www.999qp.com/index.aspx";
	}
	//�����㳡
	CRect rcCreate(0,0,0,0);
	m_PlazaViewItem.SetMainUrl(m_sMainUrl);
	m_PlazaViewItem.Create(IDD_GAME_PLAZA,this);

	//�����ؼ�
	m_ServerListView.Create(WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SERVER_LIST);
	m_SkinSplitter.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN_SPLITTER);
//m_ServerListView.ShowWindow(SW_HIDE);
	//���ڿؼ�
	m_WndViewItemCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_VIEW_ITEM_CTRL);
	m_WndUserInfoCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_USER_INFO_CTRL);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	//������ť
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MAX);
	m_btSkin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLOSE);
	m_btCertificate.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CERTIFICATE);
	//m_btControl.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CONTROL);
	//m_btLockList.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_LOCK_LIST);
	m_btGameList.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BUTTON_GAMELIST);
	m_btGameMatch.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BUTTON_GAMEMATCH);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btMin.SetButtonImage(IDB_BT_MIN,hInstance,true,false);
	m_btMax.SetButtonImage(IDB_BT_MAX,hInstance,true,false);
	m_btSkin.SetButtonImage(IDB_BT_SKIN,hInstance,true,false);
	m_btClose.SetButtonImage(IDB_BT_CLOSE,hInstance,true,false);
	m_btCertificate.SetButtonImage(IDB_BT_CERTIFICATE,hInstance,true,false);

	//m_btLockList.SetButtonImage(IDB_BK_LIST,TEXT("BT_LOCK_LIST"),hInstance,true,false);
	//m_btLockList.ShowWindow(SW_HIDE);

	//���ư�ť
	//m_btControl.SetParent(&m_SkinSplitter);
	//m_btControl.SetButtonImage(IDB_BK_GAME_LIST,TEXT("BT_GAME_LIST_HIDE"),hInstance,true,false);

	//ƽ̨��ť
// 	for (INT i=0;i<CountArray(m_btPlatform);i++)
// 	{
// 		//������ԭ���չ�ť
// 		if (i == 1)
// 		{
// 			continue;
// 		}
// 
// 		m_btPlatform[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_PLATFORM+i);
// 	}

	//������ť
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		m_btNavigation[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_NAVIGATION+i);
	}

	//ƽ̨��ť
	//m_btPlatform[0].SetButtonImage(IDB_BK_PLATFORM_1,TEXT("BT_PLATFORM_1"),hInstance,true,false);
	//m_btPlatform[1].SetButtonImage(IDB_BK_PLATFORM_2,TEXT("BT_PLATFORM_2"),hInstance,true,false);
	//m_btPlatform[2].SetButtonImage(IDB_BK_PLATFORM_3,TEXT("BT_PLATFORM_3"),hInstance,true,false);

	//������ť
	m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,hInstance,true,false);
	m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,hInstance,true,false);
	m_btNavigation[2].SetButtonImage(IDB_BK_NAVIGATION3,hInstance,true,false);
	m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION4,hInstance,true,false);
	m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,hInstance,true,false);

	//�������
	m_SkinSplitter.SetSplitterEvent(this);
	m_SkinSplitter.SetSplitterColor(0.67,0.95);
	m_SkinSplitter.SetSplitterType(SplitterType_Vor);

	///////////////////�����б�///////////////////////////////////////////////////////
	m_ServerMatchList.Create(/*WS_CHILD|*/LVS_REPORT|LVS_OWNERDRAWFIXED|LVS_NOSCROLL|LVS_NOCOLUMNHEADER,rcCreate, this, IDC_MATCH_LIST);
    m_ServerMatchList.SetBkColor(RGB(236,237,255));
	m_ServerMatchList.SetItemHeight(64);
	m_ServerMatchList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_ServerMatchList.ModifyStyle(0,LVS_EX_TRACKSELECT);
	m_ServerMatchList.InsertColumn(0,TEXT("���"),LVCFMT_LEFT,0,0);
	m_ServerMatchList.InsertColumn(1,TEXT("�Է��û���"),LVCFMT_LEFT,266,1);
	//m_ServerMatchList.SetListColor(RGB(255,0,0),RGB(0,255,0),RGB(255,255,255),RGB(101,101,255));
	//int nPos = 0;

	//for(int nIndex = 3;nIndex<40;nIndex++)
	//{
	//	CString strTemp;
	//	strTemp.Format("Index %d",nIndex);
	//	m_ServerMatchList.InsertItem(nPos,(LPCTSTR)strTemp);

	//	m_ServerMatchList.SetItemText(nPos,1,(LPCTSTR)"aaa");

	//	m_ServerMatchList.SetItemData(nPos,nIndex);
	//}
//////////////////////////////////////////////////////////////////////////

	//��Ϸ�б�
	m_ServerListView.InitServerTreeView();
	CServerListData::GetInstance()->SetServerListDataSink(&m_ServerListView,&m_ServerMatchList);

	//��ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.SetMaxTipWidth(320);
	m_ToolTipCtrl.SetDelayTime(100);
	m_ToolTipCtrl.AddTool(&m_btMin,TEXT("��С��"));
	m_ToolTipCtrl.AddTool(&m_btMax,TEXT("���"));
	m_ToolTipCtrl.AddTool(&m_btSkin,TEXT("���滻��"));
	m_ToolTipCtrl.AddTool(&m_btClose,TEXT("�ر���Ϸ"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[0],TEXT("�û���¼"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[1],TEXT("�ʺų�ֵ"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[2],TEXT("���չ�"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[3],TEXT("��Ϸ�̳�"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[4],TEXT("��Ϸ�ͷ�"));
	//m_ToolTipCtrl.AddTool(&m_btControl,TEXT("���أ���ʾ����Ϸ�б�"));
	CString sTip = "�����α���[2014]C-CBG022��\r\n������[2013]1114-104��\r\n��ICP��2235390��\r\n������ֵ�0697404��\r\nICP֤����B2-20140068";
	//sTip.Replace("#","\r\n");
	m_ToolTipCtrl.AddTool(&m_btCertificate,sTip);

	//ϵͳ����
	m_WndViewItemCtrl.SetViewItemEvent(this);
	m_WndViewItemCtrl.InsertViewItem(&m_PlazaViewItem,TEXT("��Ϸ�㳡"));

	//ע���¼�
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//����λ��
	CSize SizeRestrict;
	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);

	//����λ��
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//��ȡλ��
	CWHRegKey InfoKeyItem;
	if (InfoKeyItem.OpenRegKey(REG_INTERFACE_INFO,false)==true)
	{
		SizeRestrict.cx=InfoKeyItem.GetValue(TEXT("ScreenWidth"),rcArce.Width()/2);
		SizeRestrict.cy=InfoKeyItem.GetValue(TEXT("ScreenHeight"),rcArce.Height()/2);
	}

	//λ�õ���
	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);

	//�ƶ�����
	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
	m_rcNormalSize.right=m_rcNormalSize.left+SizeRestrict.cx;
	m_rcNormalSize.bottom=m_rcNormalSize.top+SizeRestrict.cy;
	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Games/CustomerNew.aspx"),pGlobalServer->GetPlatformServer(3));

	//���ӹ��
	//m_PlatformPublicize.Navigate("http://61.174.50.46:8090/Games/CustomerNew.aspx");
	m_PlatformPublicize.Navigate(szBillUrl);
	m_PlatformPublicize.SetBoradColor(RGB(215,235,255));

	//if(theApp.m_bsSpreader)
	//{
	//	m_btGameList.SetButtonImage(IDB_BT_GAMELIST1,hInstance,true,false);
	//	m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH,hInstance,true,false);
	//	m_ServerListView.ShowWindow(SW_HIDE);
	//	m_ServerMatchList.ShowWindow(SW_SHOW);
	//}
	//else
	//{
		m_btGameList.SetButtonImage(IDB_BT_GAMELIST,hInstance,true,false);
		m_btGameMatch.SetButtonImage(IDB_BT_GAMEMATCH1,hInstance,true,false);
		m_ServerListView.ShowWindow(SW_SHOW);
		m_ServerMatchList.ShowWindow(SW_HIDE);
	//}

	InitData();	

	//��ʾ����
	MaxSizeWindow();

	//��¼ϵͳ
	PostMessage(WM_COMMAND,IDM_USER_LOGON,0);

	//ע���ȼ�
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
	//CWHService::RegisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS,pParameterGlobal->m_wBossHotKey);
	//CWHService::RegisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER,pParameterGlobal->m_wWhisperHotKey);

	//��������
	m_SystemTrayIcon.InitTrayIcon(m_hWnd,IDC_SYSTEM_TRAY_ICON);
	m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)),pGlobalServer->GetPlatformProduct(1));

	//��������
	SetTimer(IDI_UPDATA_ONLINE, TIME_UPDATA_ONLINE, NULL);
//	SetTimer(IDI_TIMER_WEB, 5*1000, NULL);
	//��������
	CSkinDialog::SetWndFont(this,NULL);

	return 0;
}

//�����Ϣ
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//�����Ϣ
VOID CPlatformFrame::OnLButtonDblClk(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDblClk(nFlags,Point);

	//״̬�ж�
	if (Point.y>CAPTION_SIZE) return;

	//���ڿ���
	if (m_bMaxShow==true)
	{
		RestoreWindow();
	}
	else
	{
		MaxSizeWindow();
	}
	
	return;
}

//���øı�
VOID CPlatformFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags,lpszSection);

	//���ڿ���
	if (m_bMaxShow==true)
	{
		m_bMaxShow=false;
		MaxSizeWindow();
	}
	else
	{
		m_bMaxShow=true;
		RestoreWindow();
	}

	return;
}

//ƽ̨��ť
VOID CPlatformFrame::OnBnClickedPlatform1()
{
	//�����û�
	CDlgSearchUser DlgSearchUser;
	DlgSearchUser.DoModal();

	return;
}

//ƽ̨��ť
VOID CPlatformFrame::OnBnClickedPlatform2()
{
	//��������
// 	bool bGoldServer=false;
// 	CServerViewItem * pServerViewGold=NULL;
// 
// 	//���ҷ���
// 	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
// 	{
// 		//��ȡ����
// 		ASSERT(m_ServerViewItemArray[i]!=NULL);
// 		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
// 
// 		//��������
// 		WORD wServerType=pServerViewItem->GetServerType();
// 		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();
// 
// 		//�����ж�
// 		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
// 		{
// 			//���ñ���
// 			bGoldServer=true;
// 			pServerViewGold=pServerViewItem;
// 
// 			break;
// 		}
// 	}
// 
// 	//������Դ
// 	AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));
// 
// 	//��������
// 	if (bGoldServer==false)
// 	{
// 		//�㳡����
// 		CDlgInsurePlaza DlgInsurePlaza;
// 		INT_PTR nResult=DlgInsurePlaza.DoModal();
// 	}
// 	else
// 	{
// 		//��������
// 		ASSERT(pServerViewGold!=NULL);
// 		pServerViewGold->ShowInsureView();
// 	}

	return;
}

//ƽ̨��ť
VOID CPlatformFrame::OnBnClickedPlatform3()
{
	//��������
	CParameterGame * pParameterGame=NULL;
	CParameterServer * pParameterServer=NULL;

	//�������
	WORD wActiveItem=m_WndViewItemCtrl.GetActiveItem();
	tagViewItemInfo * pViewItemInfo=m_WndViewItemCtrl.GetViewItemInfo(wActiveItem);

	//��������
	if ((wActiveItem>=1)&&(pViewItemInfo!=NULL))
	{
		//��ȡ����
		CWnd * pItemView=pViewItemInfo->pItemView;
		CServerViewItem * pServerViewItem=(CServerViewItem *)pItemView;

		//���ñ���
		if (pServerViewItem!=NULL)
		{
			pParameterGame=pServerViewItem->GetParameterGame();
			pParameterServer=pServerViewItem->GetParameterServer();
		}

	}

	//�������
	CDlgCollocate DlgCollocate;
	DlgCollocate.InitCollocate(pParameterGame,pParameterServer);

	//��ʾ����
	if (DlgCollocate.DoModal()==IDOK)
	{
		//���͹���
		for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
		{
			//��ȡ����
			CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
			if (pServerViewItem->GetServiceStatus()==ServiceStatus_ServiceIng) pServerViewItem->SendUserRulePacket();
		}
	}

	return;
}

//�ȼ���Ϣ
LRESULT CPlatformFrame::OnMessageHotKey(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//�ϰ��ȼ�
		{
			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

			//��¼�ж�
			if (pGlobalUserData->dwUserID!=0L)
			{
				//��������
				bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

				//���ش���
				if (bBossCome==false)
				{
					//��ԭ����
					ShowWindow(SW_RESTORE);
					ShowWindow(SW_SHOW);

					//�ö�����
					SetActiveWindow();
					BringWindowToTop();
					SetForegroundWindow();

					//��ʾͼ��
					m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
				}
				else
				{
					//���ش���
					ShowWindow(SW_MINIMIZE);
					ShowWindow(SW_HIDE);

					//����ͼ��
					m_SystemTrayIcon.HideTrayIcon();
				}

				//������Ϣ
				for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
				{
					ASSERT(m_ServerViewItemArray[i]!=NULL);
					m_ServerViewItemArray[i]->NotifyBossCome(bBossCome);
				}
			}

			return 0;
		}
	case IDI_HOT_KEY_WHISPER:	//˽���ȼ�
		{
			//��ȡ��Ϣ
			if (m_DlgWhisperItemArray.GetCount()>0L)
			{
				ShowWhisperItem();
				return 1;
			}

			return 0;
		}
	}

	return 0;
}

//ͼ����Ϣ
LRESULT CPlatformFrame::OnMessageTrayIcon(WPARAM wParam, LPARAM lParam)
{
	//�¼�����
	switch (lParam)
	{
	case WM_LBUTTONDOWN:		//��굥��
	case WM_LBUTTONDBLCLK:		//���˫��
		{
			//��ȡ��Ϣ
			if (m_DlgWhisperItemArray.GetCount()>0L)
			{
				ShowWhisperItem();
				return 1;
			}

			return 1;
		}
	case WM_RBUTTONDOWN:		//��굥��
	case WM_RBUTTONDBLCLK:		//���˫��
		{
			//�����˵�
			CSkinMenu Menu;
			Menu.CreateMenu();

			//����˵�
			Menu.AppendMenu(IDM_RESTORE,TEXT("��ԭ"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
			Menu.AppendMenu(IDM_MINIMIZE,TEXT("��С��"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
			Menu.AppendMenu(IDM_MAXIMIZE,TEXT("���"));
			Menu.AppendSeparator();
			Menu.AppendMenu(IDC_CLOSE,TEXT("�˳��㳡"));
			//Menu.AppendSeparator();
			//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("����..."));

			//��ʾ�˵�
			CPoint MousePoint;
			GetCursorPos(&MousePoint);
			Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

			return 1;
		}
	}

	return 0;
}

//�¼���Ϣ
LRESULT CPlatformFrame::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//�¼�����
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//��¼���
		{
			//��ʾ����
			ShowWindow(SW_SHOW);
			SetForegroundWindow();

			//��Ϸ�б�
			ControlServerList(ServerListControl_Show,false);

			SetTimer(IDI_TIMER_WEB, 1*1000, NULL);

			//�û����
			ASSERT(CGlobalUnits::GetInstance()!=NULL);
			if (CGlobalUnits::GetInstance()->DeleteUserCookie())
			{
				CGlobalUnits::GetInstance()->WriteUserCookie();
			}
	
			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();
			if(pGlobalUserInfo->GetUserAccountType()>0 && (!pIndividualUserData->cbMoorPhone || !pIndividualUserData->cbMoorPassPortID)) //�������û�����û�а�
			{
				CInformation Information(CPlatformFrame::GetInstance());
				if(Information.ShowMessageBox(TEXT("�װ���QQ�˺��û�,Ϊ�������˻���ȫ,�����������֤���ֻ����㡮ȷ�������а� "),MB_ICONINFORMATION|MB_OKCANCEL,0) == IDOK)
				{			//��ʾ����
					CDlgLockMachine DlgLockMachine;
					DlgLockMachine.DoModal();
				}
				PopSysMessage();
			}
			else if (!pIndividualUserData->cbMoorPhone) //���ֻ�
			{
// 				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
// 				TCHAR szBillUrl[256]=TEXT("");
// 				_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/MachineBind/UserBindMachine2.aspx"),pGlobalServer->GetPlatformServer(3));
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/MachineBind/UserBindMachine.aspx?userId=%d"),pGlobalServer->GetPlatformServer(3),pGlobalUserData->dwUserID);

				CMessagePop DlgMobileBind ;
				DlgMobileBind.SetWindowSize(490,210,490,/*210-107*/210);
				DlgMobileBind.InitWebDlg(szBrowseUrl,"�ֻ���",true,false,0);
				//CDlgMobileBind DlgMobileBind;
				DlgMobileBind.DoModal();
				PopSysMessage();
			}
			else
			{
				SetTimer(IDI_MESSAGE_POP,1000*3,NULL);
			}
	
			return 0L;
		}
	case EVENT_USER_LOGOUT:			//ע���ɹ�
		{
			//����㳡
			m_WndViewItemCtrl.ActiveViewItem(&m_PlazaViewItem);

			//�رշ���
			if (m_pServerViewItem!=NULL)
			{
				if(!DeleteServerViewItem(m_pServerViewItem))return 0L;
			}

			//�رշ���
			while (m_ServerViewItemArray.GetCount()>0)
			{
				if(!DeleteServerViewItem(m_ServerViewItemArray[0]))
					return 0L;
			}
			//�رձ��չ�
			if (m_pInsurePlaza!=NULL)
			{
				SafeDelete(m_pInsurePlaza);
				m_pInsurePlaza = NULL;
			}
			m_ServerMatchList.ResetData();
			m_ServerListView.ResetData();
			m_ServerListData.ResetDate();


			//���ش���
			ShowWindow(SW_HIDE);

			//���³�ʼ����¼��Ϣ
			m_sRemInsurePwd = "";
			m_bShowVerify = true;
			//////////////////////////////////////////////////////////////////////////
			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();
			m_MissionLogon.SetHaveLogonIn(false);
			m_MissionLogon.SetLoginSocketType(0);
			//��ʾ��¼
			m_MissionLogon.ShowLogon();

			return 0L;
		}
	case EVENT_DOWN_LOAD_FINISH:	//�������
		{
			//��ȡ����
			WORD wKindID=LOWORD(lParam);
			WORD wServerID=HIWORD(lParam);

			//�����б�
			CServerListData * pServerListData=CServerListData::GetInstance();
			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);

			//���뷿��
			if ((wKindID!=0)&&(wServerID!=0))
			{
				CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
				if (pGameServerItem!=NULL) EntranceServerItem(pGameServerItem);
			}

			return 0L;
		}
	}

	return 0L;
}

//�¼���Ϣ
LRESULT CPlatformFrame::OnMessageInstallCancelEvent(WPARAM wParam, LPARAM lParam)
{
	//��ʾ��¼
	m_MissionLogon.ShowLogon();
	return 0L;
}

void CPlatformFrame::SetVideoOption(WORD wAVServerPort, DWORD dwAVServerAddr)
{
	m_wAVServerPort=wAVServerPort;
	m_dwAVServerAddr=dwAVServerAddr;
}

//�¼���Ϣ
LRESULT CPlatformFrame::OnMessageInsurePlazaEvent(WPARAM wParam, LPARAM lParam)
{
	tagInsurePlazaUpdata *pUpdata = (tagInsurePlazaUpdata*)wParam;
	if(pUpdata)
	{
		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//����
		pGlobalUserData->lUserScore = pUpdata->lUserScore;
		pGlobalUserData->lUserInsure = pUpdata->lUserInsure;

		m_WndUserInfoCtrl.InvalidateRect(NULL);
	}

	return 0;
}

//��������������
void CPlatformFrame::UpDataAllOnLineCount()
{
	DWORD dwAllOnLineCount = GetAllOnLineCount();
	if(m_dwAllOnLineCount != dwAllOnLineCount)
	{
		m_dwAllOnLineCount = dwAllOnLineCount;
		RedrawWindow();
	}
}

//��ȡ����������
DWORD CPlatformFrame::GetAllOnLineCount()
{
	return m_ServerListData.GetAllOnLineCount();
}

//��������Ϸ
void CPlatformFrame::AddLastPlayGame(WORD wServerID)
{
	//return; // lhm 20149119 add
	//���ҷ���
	CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);

	//�����¼
	m_ServerListView.AddLastPlayGame(wServerID, pGameServerItem);

	return;
}

//����ʧЧ
bool CPlatformFrame::ListGameServerInvalidation(WORD wKindID, WORD wServerID)
{
	//ɾ������
	m_ServerListData.DeleteGameServer(wServerID);

	//��ȡ����
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//��������
	if(pGameKindItem!=NULL && m_ServerListView.IsEmptySubitem(wKindID))
	{
		m_ServerListView.OnGameItemDelete(pGameKindItem);
		m_ServerListView.OnGameItemInsert(pGameKindItem);
		m_ServerListView.OnGameKindFinish(wKindID);
	}

	return true;
}

//��Ϣ����
LRESULT CPlatformFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(message==0x0313)
	{
		//�����˵�
		CSkinMenu Menu;
		Menu.CreateMenu();

		//����˵�
		Menu.AppendMenu(IDM_RESTORE,TEXT("��ԭ"), (IsIconic()||IsWindowVisible()==FALSE)?MF_ENABLED:MF_GRAYED);
		Menu.AppendMenu(IDM_MINIMIZE,TEXT("��С��"),(IsIconic()==FALSE||IsWindowVisible())?MF_ENABLED:MF_GRAYED);
		Menu.AppendMenu(IDM_MAXIMIZE,TEXT("���"));
		Menu.AppendSeparator();
		Menu.AppendMenu(IDC_CLOSE,TEXT("�˳��㳡"));
		//Menu.AppendSeparator();
		//Menu.AppendMenu(IDM_NULL_COMMAND,TEXT("����..."));

		//��ʾ�˵�
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		Menu.TrackPopupMenu(MousePoint.x,MousePoint.y,this);

		return 0;
	}

	return __super::WindowProc(message, wParam, lParam);
}

//void CPlatformFrame::OnSysCommand(UINT nID,LPARAM lParam)
//{
//	switch(nID)
//	{
//	case SC_MAXIMIZE :
//		ShowWindow(SW_SHOWMAXIMIZED);
//		return;
//		break;
//	case SC_MINIMIZE :
//		ShowWindow(SW_MINIMIZE);
//		return;
//		break;
//	case SC_RESTORE :
//		//	 AfxMessageBox("Restore");
//		ShowWindow(SW_RESTORE);
//		return;
//		break;
//	}
//	CPlatformFrame::OnSysCommand(nID,lParam );
//}

bool CPlatformFrame::RegisterDll()
{
	int dllnum = 1;
	CString dllpath[1]={"ImageOle.dll"};
	BOOL bsResult = false ;
	//����Ƿ�֧��ע��
	int i=0;
	for(i=0;i<dllnum;i++)
	{
		CString strOcxPath;
		if(dllpath[i] == "")
		{
			continue;
		}
		CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
		strOcxPath  =pCGlobalUnits->m_sAppPath +dllpath[i];
		if(true)
		//if (SupportsSelfRegister(strOcxPath))
		{
			HMODULE hModule = ::LoadLibrary(strOcxPath) ;
			if (LOADLIBRARY_FAILED(hModule)) return FALSE ;

			//���ע�ắ����ַ
			CTLREGPROC DLLRegisterServer =
				(CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer") ;
			if (DLLRegisterServer != NULL)
			{
				HRESULT regResult = DLLRegisterServer() ;
				bsResult = (regResult == NOERROR) ;
			}
			::FreeLibrary(hModule) ;
		}
	}
	return true;
}

bool CPlatformFrame::GetPlayingGameServer(int &nGameServerID)
{
	bool bPlaying = false;
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//��ȡ����
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL)
		{
			bPlaying = pServerViewItem->IsPlayingMySelf();
			nGameServerID = pServerViewItem->GetGameServer().wServerID;
			break;
		}
	}
	return bPlaying;
}

void CPlatformFrame::ExitGameServer(int nGameServerID)
{
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//��ȡ����
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL && pServerViewItem->GetGameServer().wServerID == nGameServerID)
		{
			DeleteServerViewItem(pServerViewItem);
			break;
		}
	}
}

void CPlatformFrame::ActiveGameServe(int nGameServerID)
{
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//��ȡ����
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];
		if (pServerViewItem!=NULL && pServerViewItem->GetGameServer().wServerID == nGameServerID)
		{
			ActiveServerViewItem(pServerViewItem);
			break;
		}
	}
}

void CPlatformFrame::PopSysMessage()
{
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	CString sContent;
	sContent.Format("ID=%d",pGlobalUserInfo->GetGlobalUserData()->dwGameID);
	CString csResponse;
	unsigned short nPort = pGlobalServer->GetPostPort();
	DWORD dwRes = 0;
	CWHService::Post(csResponse,pGlobalServer->GetPlatformServer(4),nPort,"GetPopMsg.aspx",sContent,dwRes,TRUE);
	CString sPopMsgUrl = csResponse;
	if (sPopMsgUrl.Find("http://")!=-1)
	{
		CMessagePop *m_pPopDlg = new CMessagePop;
		m_pPopDlg->SetWindowSize(480,380,480,380-72-55);
		m_pPopDlg->InitWebDlg(sPopMsgUrl,"ϵͳ����",false,true,10);

		m_pPopDlg->Create(IDD_DIALOG_MSGPOP,this);
		m_pPopDlg->SetForegroundWindow();
		m_pPopDlg->ShowWindow(SW_SHOW);
	}
}

void CPlatformFrame::ClosePazza(int nType)//1,�رտͻ���;2,�л��˺�
{
	if (nType == 1)
	{
		SetTimer(IDI_CLOSE_PAZZA,500,NULL);;
	}
	else if (nType==2)
	{
		//�����¼�
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);
	}
	//CGlobalUnits::GetInstance()->DeleteUserCookie();
	//CGlobalUserInfo::GetInstance()->ResetUserInfoData();
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
	//UnregisterHotKey(m_hWnd,IDI_HOT_KEY_WHISPER);
	//__super::OnClose();
}

LRESULT CPlatformFrame::OnSafeBind(WPARAM wParam, LPARAM lParam)
{
	//������ʾ
	CString sCoinStr;
	sCoinStr = "����ǰ����ܶ���࣬Ϊ�����Ľ�Ұ�ȫ����󶨱��������֤���ֻ��ٽ�����Ϸ�������ȷ�ϡ����а󶨡�";
	//�˳��ж�
	CInformation Information(CPlatformFrame::GetInstance());
	if(Information.ShowMessageBox(sCoinStr,MB_ICONINFORMATION|MB_OKCANCEL,0) == IDOK)
	{			//��ʾ����
		CDlgLockMachine DlgLockMachine;
		DlgLockMachine.DoModal();
	}
	return true;
}

void CPlatformFrame::SetRemInsurePwd(CString sNewInsurePwd)
{
	if (m_sRemInsurePwd == "") //������
		return;
	m_sRemInsurePwd = sNewInsurePwd;
	if (m_pInsurePlaza!=NULL && m_pInsurePlaza->m_hWnd!=NULL)
	{
		m_pInsurePlaza->SetInsurePass(m_sRemInsurePwd);
	}
	CServerViewItem * pServerViewGold=NULL;
	//���ҷ���
	for (INT_PTR i=0;i<m_ServerViewItemArray.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_ServerViewItemArray[i]!=NULL);
		CServerViewItem * pServerViewItem=m_ServerViewItemArray[i];

		//��������
		WORD wServerType=pServerViewItem->GetServerType();
		enServiceStatus ServiceStatus=pServerViewItem->GetServiceStatus();

		//�����ж�
		if (((wServerType&GAME_GENRE_GOLD)/*||(wServerType&GAME_GENRE_MATCH)*/)&&(ServiceStatus==ServiceStatus_ServiceIng))
		{
			//���ñ���
			pServerViewGold=pServerViewItem;
			//��������
			ASSERT(pServerViewGold!=NULL);
			if (pServerViewGold->m_pDlgInsureServer!=NULL && pServerViewGold->m_pDlgInsureServer->m_hWnd!=NULL)
			{
				pServerViewGold->m_pDlgInsureServer->SetInsurePass(m_sRemInsurePwd);
			}

			break;
		}
	}
}

void CPlatformFrame::SaveInsurePwd(int nType,int nMinute,LPCTSTR pszInsurePwd)
{
	if (nType == 2) //�Զ�ע��
	{
		m_sRemInsurePwd = pszInsurePwd;
		SetTimer(IDI_REM_INSUREPASS,nMinute*1000*60,NULL);
	}
	else if(nType == 3) //���浽���ε�¼
	{
		m_sRemInsurePwd = pszInsurePwd;
	}
	else //����ע��
	{
		m_sRemInsurePwd = pszInsurePwd;
		SetTimer(IDI_REM_INSUREPASS,1000*3,NULL);
	}
}

void CPlatformFrame::InitData()
{
	CString sGameKindInfoPath;
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	sGameKindInfoPath = pGlobalServer->GetAppPath()+"\\GameKind\\"+"GameKindInfo.xml";
	CCressXML xml;
	if(!xml.LoadFile(sGameKindInfoPath))
	{
		return;
	}
	xml.SelectNodeToList("//items/item");
	while(xml.QueryNode() != NULL)
	{
		CGameKindInfo *pGameKindInfo = new CGameKindInfo;
		pGameKindInfo->nKindID = atoi(xml.GetValueByName("ID"));
		pGameKindInfo->sKindTypePath = xml.GetValueByName("HP");
		pGameKindInfo->sStarLevelPath = xml.GetValueByName("LP");
		m_ServerListData.InsertGameKinfInfo(pGameKindInfo);
	}
}
//////////////////////////////////////////////////////////////////////////////////

