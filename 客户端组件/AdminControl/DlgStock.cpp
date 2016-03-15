// DlgStock.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgStock.h"


// CDlgStock 对话框

IMPLEMENT_DYNAMIC(CDlgStock, CDialog)

CDlgStock::CDlgStock(CWnd* pParent /*=NULL*/)
: CDialog(CDlgStock::IDD, pParent)
{
	m_pGameServerItem = NULL;
	m_bClickOnCheck = FALSE;
	m_bSelAll = TRUE;
}

CDlgStock::~CDlgStock()
{
	if (m_pGameServerItem!=NULL)
	{
		SafeDelete(m_pGameServerItem);
	}
}

void CDlgStock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STOCK_LIST, m_StockList);
	DDX_Control(pDX, IDC_SET_STROAG, m_SetStroag);
	DDX_Control(pDX, IDC_STTODAYSCORE, m_stTodatScoreTotal);
	DDX_Control(pDX, IDC_INFO, m_stInfo);
	DDX_Control(pDX, IDC_STOCK_USER_LIST, m_StockUserList);
	DDX_Control(pDX, IDC_STWARINNING, m_StWarning);
}


BEGIN_MESSAGE_MAP(CDlgStock, CDialog)
	ON_BN_CLICKED(IDC_SET_STROAG, &CDlgStock::OnBnClickedSetStroag)
	ON_BN_CLICKED(IDC_GET_STROAGE, &CDlgStock::OnBnClickedGetStroage)
	ON_NOTIFY(NM_CLICK, IDC_STOCK_LIST, OnClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STOCK_LIST, OnItemchangedList1)
	ON_BN_CLICKED(IDC_CK, OnCk)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CDlgStock::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rcRect;
	GetClientRect(&rcRect);

	m_StockList.SetWindowPos(NULL,rcRect.left,rcRect.top,rcRect.right-50,rcRect.bottom-70,SWP_NOZORDER);

	m_StockUserList.SetWindowPos(NULL,rcRect.right+10-50,rcRect.top,250,rcRect.bottom-70,SWP_NOZORDER);

	m_stInfo.SetWindowText("当天累计：负数系统赢，正数玩家赢！");
	m_StockList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_StWarning.SetWindowText("警告：不要频繁点击列表获取信息！");
	m_StWarning.SetWindowPos(NULL,rcRect.right+10-50,rcRect.bottom-70,250,200,SWP_NOZORDER);
	m_StockList.InitStockInfoList();
	m_StockUserList.InitStockInfoList();

	return TRUE;
}

// CDlgStock 消息处理程序

void CDlgStock::OnInsertStockInfo(tagUMSysGameSet* ptagUMSysGameSet)
{
	// 	int iLine = m_StockList.GetItemCount();
	// 	CString szText;
	// 	szText.Format(_T("%d"),iLine);
	// 	m_StockList.InsertItem(iLine,szText);
	// 
	// 	int col = 1;
	// 	switch(col)
	// 	{
	// 	case 1:
	// 		{
	// 			CServerListData* pCServerListData = CServerListData::GetInstance();
	// 			m_pGameServerItem = pCServerListData->SearchGameServer(ptagUMSysGameSet->dwServerID); 
	// 
	// 			LPCTSTR GameName = m_GameServerItem->m_GameServer.szServerName;
	// 
	// 			szText.Format(_T("%s"),GameName);
	// 			m_StockList.SetItemText(iLine,++col,szText);
	// 		}
	// 	case 2:
	// 		{
	// 			szText.Format(_T("%d"),ptagUMSysGameSet->dwStoragStart);
	// 			m_StockList.SetItemText(iLine,++col,szText);
	// 		}
	// 	case 3:
	// 		{
	// 			szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
	// 			m_StockList.SetItemText(iLine,++col,szText);
	// 		}
	// 	case 4:
	// 		{
	// 			if (ptagUMSysGameSet->bValid==0)
	// 			{
	// 				szText.Format("未启用");
	// 			}else
	// 				szText.Format("启用");
	// 			
	// 			m_StockList.SetItemText(iLine,++col,szText);
	// 		}
	// 	}

	m_StockList.OnInsertStockDataInfo(ptagUMSysGameSet);

	m_cbTotalScore = m_StockList.OnGetAllTodatScore();
	m_cbYesterdayScore = m_StockList.OnGetAllYesterdayScore();
	m_cbdayafterScore = m_StockList.OnGetAllYesafterdayScore();
	CString strTotalScore;
	TCHAR szControl[128]=TEXT("");
	TCHAR szControl1[128]=TEXT("");
	TCHAR szControl2[128]=TEXT("");

	SwitchScoreFormat(m_cbTotalScore,4L,szControl,CountArray(szControl));
	SwitchScoreFormat(m_cbYesterdayScore,4L,szControl1,CountArray(szControl1));
	SwitchScoreFormat(m_cbdayafterScore,4L,szControl2,CountArray(szControl2));

	CString szInfo;
	szInfo.Format(_T("前天总累计：%s,昨天总累计：%s,当天总累计：%s"),szControl2,szControl1,szControl);
	m_stTodatScoreTotal.SetWindowText(szInfo);

	return;
}

void CDlgStock::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect m_Rect;
	GetClientRect(&m_Rect);

	// 	if (m_StockList)
	// 	{
	// 
	// 	}

}

WORD CDlgStock::OnSetStock(BYTE cbBuffer[], WORD wBufferSize)
{
	tabStoragStartArray* ptabStoragStartArry = (tabStoragStartArray*)cbBuffer;


	ptabStoragStartArry->dwCount = m_StockList.m_tabStoragStartArray.dwCount;
	for (int i = 0;i < ptabStoragStartArry->dwCount;i++)
	{
		ptabStoragStartArry->StoragStart[i] = m_StockList.m_tabStoragStartArray.StoragStart[i];
	}

	return sizeof(tabStoragStartArray);

}

void CDlgStock::OnBnClickedSetStroag()
{
	//return;
	// TODO: 在此添加控件通知处理程序代码
	m_StockList.OnSetStockDataInfo();

	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->OnSetStroag();
	}

}

void CDlgStock::OnBnClickedGetStroage()
{
	// TODO: 在此添加控件通知处理程序代码
	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->OnGetStroag();
	}
}


void CDlgStock::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	DWORD dwPos = GetMessagePos(); 
	CPoint point(LOWORD(dwPos), HIWORD(dwPos) ); 

	m_StockList.ScreenToClient(&point); 

	LVHITTESTINFO lvinfo; 
	lvinfo.pt = point; 
	lvinfo.flags = LVHT_ABOVE; 

	UINT nFlag; 
	int nItem = m_StockList.HitTest(point, &nFlag); 
	//判断是否点在checkbox上 
	if (nFlag == LVHT_ONITEMSTATEICON) 
	{ 
		m_bClickOnCheck = TRUE; 
	} 
	*pResult = 0;
}

void CDlgStock::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (m_bClickOnCheck)
	{//只响应因点击在CheckBox上而引起的状态改变
		//因点击在全选按钮上引起的状态改变被忽略
		int nItemCount = m_StockList.GetItemCount();
		m_bSelAll = TRUE;
		this->UpdateData(TRUE);
		for(int i = 0; i < nItemCount ;i++)
		{
			if(!m_StockList.GetCheck(i))
			{
				m_bSelAll = FALSE;
				break;
			}
		}
		((CButton*)GetDlgItem(IDC_CK))->SetCheck(m_bSelAll);
		this->UpdateData(FALSE);
		m_bClickOnCheck = FALSE;
	}
	*pResult = 0;
}

void CDlgStock::OnCk() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	m_bSelAll = !m_bSelAll;
	int iTaskCount = m_StockList.GetItemCount();
	for (int i = 0; i < iTaskCount; i++)
		m_StockList.SetCheck(i, m_bSelAll);
	this->UpdateData(FALSE);
}

BOOL CDlgStock::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

VOID CDlgStock::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
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