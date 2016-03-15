// UserRemarksInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserRemarksInfo.h"
#include "UserRemarks.h"
#include "UserServerInfo.h"

CUserRemarksInfo * CUserRemarksInfo::m_pUserRemarksInfo=NULL;						//对象指针
// CUserRemarksInfo 对话框

IMPLEMENT_DYNAMIC(CUserRemarksInfo, CDialog)

CUserRemarksInfo::CUserRemarksInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CUserRemarksInfo::IDD, pParent)
{

}

CUserRemarksInfo::~CUserRemarksInfo()
{
}

void CUserRemarksInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDREMARKS, m_EDRemarks);
	DDX_Control(pDX, IDC_STUSERINFO, m_STUserInfo);
}


BEGIN_MESSAGE_MAP(CUserRemarksInfo, CDialog)
	ON_BN_CLICKED(IDC_BTADD, &CUserRemarksInfo::OnBnClickedBtadd)
END_MESSAGE_MAP()


// CUserRemarksInfo 消息处理程序
BOOL CUserRemarksInfo::OnInitDialog()
{
	__super::OnInitDialog();

	OnSetUserInfo();

	return TRUE;
}


void CUserRemarksInfo::OnSetUserInfo()
{
	CString strUserInfo,strChannel;

	m_UserRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(m_UMUserInfo.dwUserID);

	m_EDRemarks.SetWindowText(m_UserRemarks);

// 	if (m_UMUserInfo.dwWinOrLostRate1 == 0)
// 	{
// 		strChannel = "正常";
// 	}else
// 		strChannel = "试玩站";
	strChannel.Format("%d",m_UMUserInfo.dwWinOrLostRate1);

	strUserInfo.Format("UserID：%ld      昵称：%s\r\n\r\n金币：%I64d     银行：%I64d      累计输赢金币：%I64d     当日输赢金币：%lld\r\n\r\n转出：%I64d     转入：%I64d     充值金额：%I64d     渠道：%s\r\n\r\n赢局：%d     输局：%d",
						m_UMUserInfo.dwUserID,m_UMUserInfo.szNickName,m_UMUserInfo.lScore,m_UMUserInfo.lInsure,m_UMUserInfo.lWinScore,
						m_UMUserInfo.lMaxWin1,m_UMUserInfo.lOutScore,m_UMUserInfo.lInScore,m_UMUserInfo.lMaxLose1,strChannel,m_UMUserInfo.dwWinCount,
						m_UMUserInfo.dwLoseCount);

	m_STUserInfo.SetWindowText(strUserInfo);
}

void CUserRemarksInfo::OnBnClickedBtadd()
{
	// TODO: 在此添加控件通知处理程序代码
//	CString strRrmarks;
	m_EDRemarks.GetWindowText(m_UserRemarks);

	DWORD userID = CUserRemarks::GetInstance()->SelectUser(m_UMUserInfo.dwUserID);
	if (userID == m_UMUserInfo.dwUserID)
	{
		if (CUserRemarks::GetInstance()->UpdateUserInfo(m_UMUserInfo.dwUserID,m_UserRemarks) == true)
		{
			CUserServerInfo::GetInstance()->OnUpdateUserRemarks(m_UMUserInfo.dwUserID,m_UserRemarks);
			//AfxMessageBox("更改成功!");
			//return;
		}
		
	}
	else if(CUserRemarks::GetInstance()->InsertUserRemarksInfo(m_UMUserInfo.dwUserID,m_UserRemarks) == true)
	{
		CUserServerInfo::GetInstance()->OnUpdateUserRemarks(m_UMUserInfo.dwUserID,m_UserRemarks);
		//AfxMessageBox("添加成功!");
		//return;
	}


	CDialog::OnOK();
}
