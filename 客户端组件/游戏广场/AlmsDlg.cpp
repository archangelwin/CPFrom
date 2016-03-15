// AlmsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "AlmsDlg.h"

#define IDC_BROWSER_ALMS					100									//浏览控件

// CAlmsDlg 对话框
CAlmsDlg::CAlmsDlg() : CSkinDialog(IDD_DIALOG_ALMS)
{
	//任务组件
	m_MissionManager.InsertMissionItem(this);

	return;
}

CAlmsDlg::~CAlmsDlg()
{

}

void CAlmsDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ALMS, m_btGetAlms);
}

BEGIN_MESSAGE_MAP(CAlmsDlg, CSkinDialog)
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ALMS, &CAlmsDlg::OnBnClickedButtonAlms)
END_MESSAGE_MAP()

//创建函数
BOOL CAlmsDlg::OnInitDialog()
{
	__super::OnInitDialog();
    MoveWindow(0,0,450,390);
	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);
	CenterWindow();
	//设置标题
	SetWindowText(TEXT("领取救济金"));	
	
	//创建控件
	m_WebPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcClient,this,IDC_BROWSER_ALMS);

	//构造地址
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	TCHAR szBrowseUrl[256]=TEXT("");
	_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/Ads/Alms.aspx"),pGlobalServer->GetPlatformServer(3));
	//连接地址
	m_WebPublicize.Navigate(szBrowseUrl,NULL,NULL,NULL,NULL); 

	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btGetAlms.SetButtonImage(IDB_BT_ALMS,/*TEXT("BT_GET_ALMS"),*/hInstance,false,false);

    m_WebPublicize.MoveWindow(1,36,448,182);
	m_btGetAlms.MoveWindow(130,243,190,55);

	TCHAR szAlms[MAX_PATH];
	pGlobalServer->ReadPlatFileString("PlatInfo","Alms",szAlms,MAX_PATH);
	GetDlgItem(IDC_STATIC_ALMS)->SetWindowText(szAlms);

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

	return TRUE;
}

//消息解释
BOOL CAlmsDlg::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}


// CAlmsDlg 消息处理程序
void CAlmsDlg::OnBnClickedButtonAlms()
{
	//是否可领取
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	//if (pGlobalUserData->lUserInsure + pGlobalUserData->lUserScore >=1000)
	//{
	//	//显示提示
	//	CInformation Information(this);
	//	Information.ShowMessageBox(TEXT("您当前的金币数大于1000，暂时无法领取！"),MB_ICONERROR);
	//	return;
	//}
	//变量定义
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//发起连接
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//错误提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("服务器连接失败，请检查网络配置以及网络连接状况！"),MB_ICONERROR);

		return;
	}
}


//连接事件
bool CAlmsDlg::OnEventMissionLink(INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0L)
	{
		//设置控件
		m_btGetAlms.EnableWindow(TRUE);

		//显示提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("尝试了所有的服务器都无法成功连接服务器，请留意网站维护公告！"),MB_ICONERROR);
	}
	else
	{
		//发送数据
		ASSERT(GetMissionManager()!=NULL);
		CMD_GP_GetAlms GetAlms;
		ZeroMemory(&GetAlms,sizeof(GetAlms));
		//变量定义
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		tagIndividualUserData * pIndividualUserData=pGlobalUserInfo->GetIndividualUserData();

		GetAlms.dwUserID = pGlobalUserData->dwUserID;
		//机器标识
		CWHService::GetMachineIDEx(GetAlms.szMachineID);
		lstrcpyn(GetAlms.szPassword,pGlobalUserInfo->GetGlobalUserData()->szPassword,CountArray(GetAlms.szPassword));

		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_GET_ALMS,&GetAlms,sizeof(GetAlms));
	}

	return true;
}

//关闭事件
bool CAlmsDlg::OnEventMissionShut(BYTE cbShutReason)
{
	//关闭处理
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//重试任务
		//CMissionManager * pMissionManager=GetMissionManager();
		//if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//设置控件
		m_btGetAlms.EnableWindow(TRUE);

		//显示提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("由于当前服务器处理繁忙，领取救济金失败，请稍后再重试！"),MB_ICONERROR);
	}

	return true;
}

//读取事件
bool CAlmsDlg::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//命令处理
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_OPERATE_FAILURE:	//操作失败
			{
				//效验参数
				CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

				//关闭连接
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//显示消息
				if (pOperateFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//操作成功
			{
				//变量定义
				CMD_GP_GetAlmsSuccess * pOperateSuccess=(CMD_GP_GetAlmsSuccess *)pData;
				//效验数据
				ASSERT(wDataSize>=(sizeof(CMD_GP_GetAlmsSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_GetAlmsSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//关闭连接
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//更新保险柜
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
				pGlobalUserData->lUserInsure = pOperateSuccess->lUserInsure;

				//显示消息
				if (pOperateSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				//关闭窗口
				//		__super::OnCancel();

				return true;
			}
		}
	}

	//错误断言
	ASSERT(FALSE);

	return true;
}

//重画消息
//VOID CAlmsDlg::OnPaint()
//{
//	CPaintDC dc(this);
//
//	//获取位置
//	CRect rcClient;
//	GetClientRect(&rcClient);
//	//CDC *pDC = GetDC();
//	//CPen penColor;
//	//penColor.CreatePen(PS_SOLID,1,RGB(145,168,183));//边框颜色
//	//pDC->SelectObject(penColor);
//	//pDC->MoveTo(20,205);
//	//pDC->LineTo(rcClient.Width()-20,205);
//
//	//penColor.DeleteObject();
//	//ReleaseDC(pDC);
//
//	return;
//}