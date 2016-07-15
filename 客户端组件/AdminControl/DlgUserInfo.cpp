// DlgUserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgUserInfo.h"
#include "UserServerInfo.h"

// CDlgUserInfo 对话框

IMPLEMENT_DYNAMIC(CDlgUserInfo, CDialog)

CDlgUserInfo::CDlgUserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserInfo::IDD, pParent)
	, m_RaUserWin(0)
	, m_RaUserlose(0)
	, m_RaUserDefault(0)
{
		m_AllowSet = 0;
		m_RaState = 0;
}

CDlgUserInfo::~CDlgUserInfo()
{
}

void CDlgUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_ST_USERINFO, m_StUserInfo);
	// 	DDX_Control(pDX, IDC_EDWIN_MAX, m_EdWinMax);
	// 	DDX_Control(pDX, IDC_EDLOSE_MAX, m_EdLoseMax);
	// 	DDX_Control(pDX, IDC_EDNOTIFY_win, m_EdNotifyWin);
	// 	DDX_Control(pDX, IDC_EDNOTIFY_LOSE, m_EdNotifyLose);
	// 	DDX_Control(pDX, IDC_ED_RATE, m_EdRate);
	// 	DDX_Control(pDX, IDC_ED_WINLOSE, m_EdWinLoseScore);
	//	DDX_Control(pDX, IDC_COMBO1, m_CombState);
	DDX_Control(pDX, IDC_COMBO2, m_ComWinMax);
	DDX_Control(pDX, IDC_COMBO3, m_ComLoseMax);
	DDX_Control(pDX, IDC_COMBO4, m_ComNotifyWin);
	DDX_Control(pDX, IDC_COMBO5, m_ComNotifyLose);
	DDX_Control(pDX, IDC_COMBO6, m_ComRate);
	DDX_Control(pDX, IDC_COMBO7, m_ComSetWinLose);
	DDX_Control(pDX, IDC_EDIT1, m_EdUserInfo);
	DDX_Control(pDX, IDCANCEL, m_BtRaUserWin);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_total, m_total);
}


BEGIN_MESSAGE_MAP(CDlgUserInfo, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgUserInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgUserInfo::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgUserInfo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgUserInfo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgUserInfo::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CDlgUserInfo 消息处理程序

//创建函数
BOOL CDlgUserInfo::OnInitDialog()
{
	__super::OnInitDialog();

	m_ComWinMax.AddString("500");
	m_ComWinMax.AddString("1000");
	m_ComWinMax.AddString("2000");
	m_ComWinMax.AddString("5000");
	m_ComWinMax.AddString("8000");
	m_ComWinMax.AddString("10000");
	m_ComWinMax.AddString("20000");
	m_ComWinMax.AddString("50000");

	m_ComLoseMax.AddString("-500");
	m_ComLoseMax.AddString("-1000");
	m_ComLoseMax.AddString("-2000");
	m_ComLoseMax.AddString("-5000");
	m_ComLoseMax.AddString("-8000");
	m_ComLoseMax.AddString("-10000");
	m_ComLoseMax.AddString("-20000");
	m_ComLoseMax.AddString("-50000");

	m_ComNotifyWin.AddString("500");
	m_ComNotifyWin.AddString("1000");
	m_ComNotifyWin.AddString("2000");
	m_ComNotifyWin.AddString("5000");
	m_ComNotifyWin.AddString("8000");
	m_ComNotifyWin.AddString("10000");
	m_ComNotifyWin.AddString("20000");
	m_ComNotifyWin.AddString("50000");
	
// 	m_ComNotifyLose.AddString("-50000");
// 	m_ComNotifyLose.AddString("-20000");
// 	m_ComNotifyLose.AddString("-10000");
// 	m_ComNotifyLose.AddString("-8000");
// 	m_ComNotifyLose.AddString("-5000");
// 	m_ComNotifyLose.AddString("-2000");
// 	m_ComNotifyLose.AddString("-1000");
// 	m_ComNotifyLose.AddString("-500");

	m_ComNotifyLose.AddString("-500");
	m_ComNotifyLose.AddString("-1000");
	m_ComNotifyLose.AddString("-2000");
	m_ComNotifyLose.AddString("-5000");
	m_ComNotifyLose.AddString("-8000");
	m_ComNotifyLose.AddString("-10000");
	m_ComNotifyLose.AddString("-20000");
	m_ComNotifyLose.AddString("-50000");
	
	m_ComSetWinLose.AddString("500");
	m_ComSetWinLose.AddString("1000");
	m_ComSetWinLose.AddString("2000");
	m_ComSetWinLose.AddString("5000");
	m_ComSetWinLose.AddString("8000");
	m_ComSetWinLose.AddString("10000");
	m_ComSetWinLose.AddString("20000");
	m_ComSetWinLose.AddString("50000");
	m_ComSetWinLose.AddString("-500");
	m_ComSetWinLose.AddString("-1000");
	m_ComSetWinLose.AddString("-2000");
	m_ComSetWinLose.AddString("-5000");
	m_ComSetWinLose.AddString("-8000");
	m_ComSetWinLose.AddString("-10000");
	m_ComSetWinLose.AddString("-20000");
	m_ComSetWinLose.AddString("-50000");
	
	m_ComRate.AddString("5");
	m_ComRate.AddString("10");
	m_ComRate.AddString("20");
	m_ComRate.AddString("30");
	m_ComRate.AddString("40");
	m_ComRate.AddString("50");
	m_ComRate.AddString("60");
	m_ComRate.AddString("70");
	m_ComRate.AddString("80");
	m_ComRate.AddString("90");
	m_ComRate.AddString("100");
	
	OnSetUserInfo();

	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |   LVS_EDITLABELS|   LVS_EX_SUBITEMIMAGES ); 
	m_ListCtrl.InsertColumn(0,"UserID");
	m_ListCtrl.InsertColumn(1,"GameID");
	m_ListCtrl.InsertColumn(2,"昵称");
	m_ListCtrl.InsertColumn(3,"累计输赢");
	m_ListCtrl.InsertColumn(4,"总转出");
	m_ListCtrl.InsertColumn(5,"总转入");
	m_ListCtrl.InsertColumn(6,"差值");
	m_ListCtrl.InsertColumn(7,"金币");
	m_ListCtrl.InsertColumn(8,"银行");
	m_ListCtrl.InsertColumn(9,"转出");
	m_ListCtrl.InsertColumn(10,"转入");
	m_ListCtrl.InsertColumn(11,"是否在线");
	m_ListCtrl.InsertColumn(12,"充值");
	m_ListCtrl.SetColumnWidth(0,2);
	m_ListCtrl.SetColumnWidth(1,50);
	m_ListCtrl.SetColumnWidth(2,90);
	m_ListCtrl.SetColumnWidth(3,75);
	m_ListCtrl.SetColumnWidth(4,75);
	m_ListCtrl.SetColumnWidth(5,75);
	m_ListCtrl.SetColumnWidth(6,75);
	m_ListCtrl.SetColumnWidth(7,75);
	m_ListCtrl.SetColumnWidth(8,75);
	m_ListCtrl.SetColumnWidth(9,75);
	m_ListCtrl.SetColumnWidth(10,75);
	m_ListCtrl.SetColumnWidth(11,50);
	m_ListCtrl.SetColumnWidth(12,50);
	m_totalWL=0;
	for (int i=0;i<m_tagSameMachine.dwCount;i++)
	{
		OnInsertSameMachine(m_tagSameMachine.SameMachineItem[i],i);

		m_totalWL += m_tagSameMachine.SameMachineItem[i].lWinScore;
	}
	CString strtotal;
	strtotal.Format("总账号：%d 个, 总输赢：%I64d",m_tagSameMachine.dwCount,m_totalWL);
	m_total.SetWindowText(strtotal);

	return TRUE;
}

VOID CDlgUserInfo::OnInsertSameMachine(tagUMSameMachineItem tagsameitem,DWORD samecount)
{
	CString strinfo;
	DWORD tiemcount = samecount;
// 	for (int i=0;i<samecounts;i++)
// 	{	
		strinfo.Format("%d",tagsameitem.dwUserID);
 		m_ListCtrl.InsertItem(tiemcount,strinfo);
 		m_ListCtrl.SetItemText(tiemcount,0,strinfo);
		strinfo.Format("%d",tagsameitem.dwGameID);
 		m_ListCtrl.SetItemText(tiemcount,1,strinfo);

		strinfo.Format("%s",tagsameitem.szNickName);
 		m_ListCtrl.SetItemText(tiemcount,2,strinfo);

		strinfo.Format("%I64d",tagsameitem.lWinScore);
 		m_ListCtrl.SetItemText(tiemcount,3,strinfo);

		strinfo.Format("%I64d",tagsameitem.lAllOutScore);
		m_ListCtrl.SetItemText(tiemcount,4,strinfo);

		strinfo.Format("%I64d",tagsameitem.lAllInScore);
		m_ListCtrl.SetItemText(tiemcount,5,strinfo);

		strinfo.Format("%I64d",tagsameitem.lDifference);
		m_ListCtrl.SetItemText(tiemcount,6,strinfo);

		strinfo.Format("%I64d",tagsameitem.lScore);
 		m_ListCtrl.SetItemText(tiemcount,7,strinfo);

		strinfo.Format("%I64d",tagsameitem.lInsure);
 		m_ListCtrl.SetItemText(tiemcount,8,strinfo);

		strinfo.Format("%I64d",tagsameitem.lOutScore);
		m_ListCtrl.SetItemText(tiemcount,9,strinfo);

		strinfo.Format("%I64d",tagsameitem.lInScore);
		m_ListCtrl.SetItemText(tiemcount,10,strinfo);

		strinfo.Format("%d",tagsameitem.wOnline);
		m_ListCtrl.SetItemText(tiemcount,11,strinfo);

		strinfo.Format("%I64d",tagsameitem.lMoney);
		m_ListCtrl.SetItemText(tiemcount,12,strinfo);
//	}
}

VOID CDlgUserInfo::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//转换数值
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//变量定义
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//转换字符
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//拷贝字符
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//插入逗号
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//结束字符
	pszBuffer[wTargetIndex++]=0;

	return;
}

void CDlgUserInfo::OnSetUserInfo()
{
	CString strUserInfo,strChannel;
	CString szState;
	CString szServerName;

	TCHAR szlScore[128]=TEXT("");
	TCHAR szlInsure[128]=TEXT("");
	TCHAR szlWinScore[128]=TEXT("");
	TCHAR szlMaxWin1[128]=TEXT("");
	TCHAR szlOutScore[128]=TEXT("");
	TCHAR szlInScore[128]=TEXT("");
	TCHAR szlMaxLose1[128]=TEXT("");
	TCHAR szlAllOutScore[128]=TEXT("");
	TCHAR szlAllInScore[128]=TEXT("");
	TCHAR szlDifference[128]=TEXT("");
//	m_UserRemarks = CUserRemarks::GetInstance()->SelectUserRemarks(m_UMUserInfo.dwUserID);

//	m_EDRemarks.SetWindowText(m_UserRemarks);

	if (((m_tagUserInfo.dwIsSet)&LC_TANKING)>0 || m_tagUserInfo.wOnline == 0)
	{
		m_AllowSet = 1;
		m_ComRate.EnableWindow(TRUE);
		m_ComSetWinLose.EnableWindow(TRUE);
		//m_CombState.EnableWindow(TRUE);
		/*m_RaUserWin.EnableWindow(TRUE);*/
		((CButton *)GetDlgItem(IDC_RADIO1))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO2))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO3))->EnableWindow(TRUE);
	}else
	{
		m_AllowSet = 1;
// 		m_ComRate.EnableWindow(FALSE);
// 		m_ComSetWinLose.EnableWindow(FALSE);
// 		//m_CombState.EnableWindow(FALSE);
// 		((CButton *)GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
// 		((CButton *)GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);
// 		((CButton *)GetDlgItem(IDC_RADIO3))->EnableWindow(FALSE);
		MessageBox("当前玩家在百人游戏中，设置只有在玩家离开百人游戏后生效！","系统提示",MB_OK);
	}

	if (m_tagUserInfo.dwWinOrLostRate1 == 0)
	{
		strChannel = "正常";
	}else
		strChannel = "试玩站";

	switch (m_tagUserInfo.dwType)
	{
	case MAXWIN:
		{
			((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
			m_RaState = 1;
		}
		break;
	case MAXLOSE:
		{
			((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
			m_RaState = 2;
		}
		break;
	case MAXDEFAULT:
		{
			((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
			m_RaState = 3;
		}
		break;
	default:
		{
			((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
		}
	}

	SwitchScoreFormat(m_tagUserInfo.lScore,3L,szlScore,CountArray(szlScore));
	SwitchScoreFormat(m_tagUserInfo.lInsure,3L,szlInsure,CountArray(szlInsure));
	SwitchScoreFormat(m_tagUserInfo.lWinScore,3L,szlWinScore,CountArray(szlWinScore));
	SwitchScoreFormat(m_tagUserInfo.lMaxWin1,3L,szlMaxWin1,CountArray(szlMaxWin1));
	SwitchScoreFormat(m_tagUserInfo.lOutScore,3L,szlOutScore,CountArray(szlOutScore));
	SwitchScoreFormat(m_tagUserInfo.lInScore,3L,szlInScore,CountArray(szlInScore));
	SwitchScoreFormat(m_tagUserInfo.lMaxLose1,3L,szlMaxLose1,CountArray(szlMaxLose1));
	SwitchScoreFormat(m_tagUserInfo.lAllOutScore,3L,szlAllOutScore,CountArray(szlAllOutScore));
	SwitchScoreFormat(m_tagUserInfo.lAllInScore,3L,szlAllInScore,CountArray(szlAllInScore));
	SwitchScoreFormat(m_tagUserInfo.lDifference,3L,szlDifference,CountArray(szlDifference));

	CServerListData* pCServerListData = CServerListData::GetInstance();
	CGameServerItem * pGameServerItem = NULL;
	if (m_tagUserInfo.dwServerID != 0)
	{
		pGameServerItem = pCServerListData->SearchGameServer(m_tagUserInfo.dwServerID);

		if (pGameServerItem == NULL)
		{
			szServerName = "玩家没有登录游戏";
		}else
			szServerName.Format("%s",pGameServerItem->m_GameServer.szServerName);
	}else
		szServerName = "玩家没有登录游戏";


	TCHAR szClientAddr[16]=TEXT("");
	BYTE * pClientAddr=(BYTE *)&m_tagUserInfo.dwClientAddr;
	_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

	CTime tm(m_tagUserInfo.dwBeginTime);
	CString strTime = tm.Format(_T("%m-%d"));

	strUserInfo.Format("Game：%ld      昵称：%s       当前所在游戏：%s\r\n\r\n金币：%s     银行：%s      累计输赢金币：%s     当日输赢金币：%s\r\n\r\n转出：%s     转入：%s   (%s---今天)\r\n\r\n总转出：%s     总转入：%s     差值：%s\r\n\r\n最后一次转出：%s     最后一次转入：%s\r\n\r\n充值金额：%s     渠道：%s     赢局：%d     输局：%d\r\n\r\nIP：%s    机器码：%s",
		m_tagUserInfo.dwGameID,m_tagUserInfo.szNickName,szServerName,szlScore,szlInsure,szlWinScore,
		szlMaxWin1,szlOutScore,szlInScore,strTime,szlAllOutScore,szlAllInScore,szlDifference,m_tagUserInfo.szLastOut,m_tagUserInfo.szLastIn,szlMaxLose1,strChannel,m_tagUserInfo.dwWinCount,
		m_tagUserInfo.dwLoseCount,szClientAddr,m_tagUserInfo.szMachineID);

	m_EdUserInfo.SetWindowText(strUserInfo);

	CString WinMax,LoseMax,NotifyWin,NotifyLose,lRate,WinLoseScore;
	WinMax.Format("%lld",m_tagUserInfo.lMaxWin/10000);
	LoseMax.Format("%lld",m_tagUserInfo.lMaxLose/10000);
	NotifyWin.Format("%lld",m_tagUserInfo.lNotifyMaxWin/10000);
	NotifyLose.Format("%lld",m_tagUserInfo.lNotifyMaxLost/10000);
	lRate.Format("%ld",m_tagUserInfo.dwWinOrLostRate);
	WinLoseScore.Format("%lld",m_tagUserInfo.lSetWinOrLose/10000);

	m_ComWinMax.SetWindowText(WinMax);
	m_ComLoseMax.SetWindowText(LoseMax);
	m_ComNotifyWin.SetWindowText(NotifyWin);
	m_ComNotifyLose.SetWindowText(NotifyLose);
	m_ComRate.SetWindowText(lRate);
	m_ComSetWinLose.SetWindowText(WinLoseScore);
}

void CDlgUserInfo::OnBnClickedOk()
{
	//return;
	// TODO: 在此添加控件通知处理程序代码
	CString lWinMax,lLoseMax,lNotifyWin,lNotifyLose,lWinLoseScore;
	m_ComWinMax.GetWindowText(lWinMax);
	m_ComLoseMax.GetWindowText(lLoseMax);
	m_ComNotifyWin.GetWindowText(lNotifyWin);
	m_ComNotifyLose.GetWindowText(lNotifyLose);
	m_ComRate.GetWindowText(lRate);
	m_ComSetWinLose.GetWindowText(lWinLoseScore);

	WinMax.Format("%I64d",_ttoi64(lWinMax)*10000);
	LoseMax.Format("%I64d",_ttoi64(lLoseMax)*10000);
	NotifyWin.Format("%I64d",_ttoi64(lNotifyWin)*10000);
	NotifyLose.Format("%I64d",_ttoi64(lNotifyLose)*10000);
	WinLoseScore.Format("%I64d",_ttoi64(lWinLoseScore)*10000);

	CString szWarningInfo;

	if (m_AllowSet == 1)
	{
		if (_ttoi64(WinLoseScore)>_ttoi64(WinMax) || _ttoi64(WinLoseScore)<_ttoi64(LoseMax))
		{
			MessageBox("设置输赢分数不能高于赢最高,或者低于输最高！","系统提示",MB_OK);
			return;
		}
	}

	switch (m_RaState)
	{
	case 1:
		{
 			ntype = MAXWIN;
 			if (_ttoi64(WinLoseScore)<0)
 			{
 				MessageBox("设置输赢分数必须为正数！","系统提示",MB_OK);
 				return;
 			}
 			if (_ttoi64(lRate)==0 || _ttoi64(lRate) > 100)
 			{
 				MessageBox("换牌概率不能为0并且小于等于100！","系统提示",MB_OK);
 				return;
 			}
 			if (_ttoi64(WinLoseScore)==0)
 			{
 				MessageBox("设置输赢分数不能为0！","系统提示",MB_OK);
 				return;
 			}
			if (_ttoi64(lRate)>=40)
			{
				szWarningInfo.Format("是否确定设置【玩家赢】概率为百分之%s",lRate);
				if (MessageBox(szWarningInfo,"系统提示",MB_YESNO) == IDNO)
				{
					return;
				}	
			}
		}
		break;
	case 2:
		{
 			ntype = MAXLOSE;
 			if (_ttoi64(WinLoseScore)>0)
 			{
 				MessageBox("设置输赢分数必须为负数！","系统提示",MB_OK);
 				return;
 			}
			if (_ttoi64(lRate)==0 || _ttoi64(lRate) > 100)
			{
				MessageBox("换牌概率不能为0并且小于等于100！","系统提示",MB_OK);
				return;
			}
 			if (_ttoi64(WinLoseScore)==0)
 			{
 				MessageBox("设置输赢分数不能为0！","系统提示",MB_OK);
 				return;
 			}
			if (_ttoi64(lRate)>=40)
			{
				szWarningInfo.Format("是否确定设置【玩家输】概率为百分之%s",lRate);
				if (MessageBox(szWarningInfo,"系统提示",MB_YESNO) == IDNO)
				{
					return;
				}
			}
		}
		break;
	case 3:
		{
 			ntype = MAXDEFAULT;
 			WinLoseScore.Format("0");
 			lRate.Format("0");
		}
		break;
	}

	OnOK();
}

void CDlgUserInfo::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgUserInfo::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RaState = 1;
}

void CDlgUserInfo::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RaState = 2;
}

void CDlgUserInfo::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RaState = 3;
}
