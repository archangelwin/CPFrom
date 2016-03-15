// UserRemarksInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "UserRemarksInfo.h"
#include "UserRemarks.h"
#include "UserServerInfo.h"

CUserRemarksInfo * CUserRemarksInfo::m_pUserRemarksInfo=NULL;						//����ָ��
// CUserRemarksInfo �Ի���

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


// CUserRemarksInfo ��Ϣ�������
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
// 		strChannel = "����";
// 	}else
// 		strChannel = "����վ";
	strChannel.Format("%d",m_UMUserInfo.dwWinOrLostRate1);

	strUserInfo.Format("UserID��%ld      �ǳƣ�%s\r\n\r\n��ң�%I64d     ���У�%I64d      �ۼ���Ӯ��ң�%I64d     ������Ӯ��ң�%lld\r\n\r\nת����%I64d     ת�룺%I64d     ��ֵ��%I64d     ������%s\r\n\r\nӮ�֣�%d     ��֣�%d",
						m_UMUserInfo.dwUserID,m_UMUserInfo.szNickName,m_UMUserInfo.lScore,m_UMUserInfo.lInsure,m_UMUserInfo.lWinScore,
						m_UMUserInfo.lMaxWin1,m_UMUserInfo.lOutScore,m_UMUserInfo.lInScore,m_UMUserInfo.lMaxLose1,strChannel,m_UMUserInfo.dwWinCount,
						m_UMUserInfo.dwLoseCount);

	m_STUserInfo.SetWindowText(strUserInfo);
}

void CUserRemarksInfo::OnBnClickedBtadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strRrmarks;
	m_EDRemarks.GetWindowText(m_UserRemarks);

	DWORD userID = CUserRemarks::GetInstance()->SelectUser(m_UMUserInfo.dwUserID);
	if (userID == m_UMUserInfo.dwUserID)
	{
		if (CUserRemarks::GetInstance()->UpdateUserInfo(m_UMUserInfo.dwUserID,m_UserRemarks) == true)
		{
			CUserServerInfo::GetInstance()->OnUpdateUserRemarks(m_UMUserInfo.dwUserID,m_UserRemarks);
			//AfxMessageBox("���ĳɹ�!");
			//return;
		}
		
	}
	else if(CUserRemarks::GetInstance()->InsertUserRemarksInfo(m_UMUserInfo.dwUserID,m_UserRemarks) == true)
	{
		CUserServerInfo::GetInstance()->OnUpdateUserRemarks(m_UMUserInfo.dwUserID,m_UserRemarks);
		//AfxMessageBox("��ӳɹ�!");
		//return;
	}


	CDialog::OnOK();
}
