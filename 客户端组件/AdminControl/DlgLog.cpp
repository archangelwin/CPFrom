// DlgLog.cpp : 实现文件
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgLog.h"


// CDlgLog 对话框

IMPLEMENT_DYNAMIC(CDlgLog, CDialog)

CDlgLog::CDlgLog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLog::IDD, pParent)
{

	m_Index = 0;
}

CDlgLog::~CDlgLog()
{
}

void CDlgLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMIN_CTRL, m_AdminList);
	DDX_Control(pDX, IDC_EDIT1, m_LogCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLog, CDialog)
END_MESSAGE_MAP()


// CDlgLog 消息处理程序
BOOL CDlgLog::OnInitDialog()
{
	__super::OnInitDialog();

	DWORD dwStyle = m_AdminList.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	m_AdminList.SetExtendedStyle(dwStyle); //设置扩展风格	
//	m_AdminList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT/*|LVS_EX_CHECKBOXES*/);

	m_AdminList.InsertColumn(0,"序号",LVCFMT_CENTER,40);
	m_AdminList.InsertColumn(1,"GameID",LVCFMT_CENTER,60);
	m_AdminList.InsertColumn(2,"昵称",LVCFMT_CENTER,80);
	m_AdminList.InsertColumn(3,"最后登录时间",LVCFMT_CENTER,158);

//	m_EditLog.SetEditCtrl(&m_LogCtrl);
	m_AdminList.SetColumnWidth(0,0);

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(2000000);
	

	return TRUE;
}

//admin加入退出
bool CDlgLog::OnInsertOnLineUser(tagAdmin* ptagAdmin)
{
	CString lUserInfo;
	CString szText;
	CString sUserID,sGameID,sNickName,sLogTime;
	
	sUserID.Format("%d",ptagAdmin->dwUserID);
	sGameID.Format("%d",ptagAdmin->dwGameID);
	sNickName.Format("%s",ptagAdmin->szNickName);
	CTime tm(ptagAdmin->dwLastLoginTime);
	sLogTime = tm.Format(_T("%y-%m-%d %H:%M:%S"));

//	lUserInfo.Format("GameID:%s,用户昵称:%s,最后登录时间:%s",sGameID,sNickName,sLogTime);

	//admin更新
	if (ptagAdmin->dwType == 0)
	{
		for (int nItem = 0;nItem<m_AdminList.GetItemCount();nItem++)
		{
			DWORD GameID = _ttoi(m_AdminList.GetItemText(nItem,1));
			if (GameID == _ttoi(sGameID))
			{
				int Col = 0;
				switch (Col)
				{
				case 0:
					{
						m_AdminList.SetItemText(nItem,++Col,sGameID);
					}
				case 1:
					{
						m_AdminList.SetItemText(nItem,++Col,sNickName);
					}
				case 2:
					{
						m_AdminList.SetItemText(nItem,++Col,sLogTime);
					}
				}
				return false;
			}
		}

		//admin进入
		int iLine = m_AdminList.GetItemCount();
		szText.Format(_T("%d"),iLine);
		m_AdminList.InsertItem(iLine,szText);

		int Col = 0;
		switch (Col)
		{
		case 0:
			{
				m_AdminList.SetItemText(iLine,++Col,sGameID);
				
			}
		case 1:
			{
				m_AdminList.SetItemText(iLine,++Col,sNickName);
			}
		case 2:
			{
				m_AdminList.SetItemText(iLine,++Col,sLogTime);
			}
		}
		
	}else//admin退出
	{
		for (int nItem = 0;nItem<m_AdminList.GetItemCount();nItem++)
		{
			DWORD GameID = _ttoi(m_AdminList.GetItemText(nItem,1));
			if (GameID == _ttoi(sGameID))
			{
				m_AdminList.DeleteItem(nItem);
			}
		}
	}


	return true;
}

//log记录
bool CDlgLog::OnInsertLog(tagLog* ptagLog)
{

// 	if (m_LogCtrl.GetLineCount() >= 400)
// 	{
// 		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
// 	}
	CString sLog;

	UpdateData(TRUE);

	sLog.Format("%s",ptagLog->szLog);

	int nLens = m_LogCtrl.SendMessage(WM_GETTEXTLENGTH);
	m_LogCtrl.SetSel(nLens, nLens, FALSE);
// 	int nItem = m_Log.GetCount();
// 	if (nItem > 100)
// 	{
// 		m_Log.DeleteString(++m_Index);
// 	}
	//m_LogCtrl.LineScroll(m_LogCtrl.GetLineCount());
//	m_LogCtrl.SetSel(-1,-1);
	m_LogCtrl.ReplaceSel(sLog+"\r\n");

	int nLen = m_LogCtrl.SendMessage(WM_GETTEXTLENGTH);
	m_LogCtrl.SetSel(nLen, nLen, FALSE);
	
	UpdateData(FALSE);

	m_LogCtrl.LineScroll(m_LogCtrl.GetLineCount(),0);

	

	return true;
}


void CDlgLog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect m_Rect;
	GetClientRect(&m_Rect);

	
}

BOOL CDlgLog::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}