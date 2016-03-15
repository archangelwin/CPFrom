#include "StdAfx.h"
#include "MissionUserInfo.h"
#include "UserServerInfo.h"
#include "ServerListData.h"

//静态变量

CMissionUserInfo * CMissionUserInfo::m_pMissionUserInfo=NULL;						//对象指针

BEGIN_MESSAGE_MAP(CMissionUserInfo, CDialog)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


CMissionUserInfo::CMissionUserInfo(void)
{

	m_SysScoreSet = false;
	m_OUserSet = false;
	m_SysScoreGameSet = false;
	m_SetUserVip = false;
	m_SetDLUserVip = false;
//	m_GameServerItem = NULL;
	m_IsAccurateSreach = false;

	ASSERT(m_pMissionUserInfo==NULL);
	if (m_pMissionUserInfo == NULL)
	{
		m_pMissionUserInfo = this;
	}

	return;
}

CMissionUserInfo::~CMissionUserInfo(void)
{

	
	if (m_StockDlg!=NULL)
	{
		SafeDelete(m_StockDlg);
	}
	if (m_pLogDlg!=NULL)
	{
		SafeDelete(m_pLogDlg);
	}
	if (m_GameUserListDlg!=NULL)
	{
		SafeDelete(m_GameUserListDlg);
	}

	//释放对象
	ASSERT(m_pMissionUserInfo==this);
	if (m_pMissionUserInfo==this) m_pMissionUserInfo=NULL;
	return;
}


bool CMissionUserInfo::OnEventMissionLink(INT nErrorCode)
{
	if (nErrorCode!=0L)
	{
		if (m_hWnd == NULL)
		{
			CRect rcCreate(0,0,0,0);
		}
	}

	if (m_SysScoreSet == true)
	{
		m_SysScoreSet = false;

		WORD wPacketSize;
		BYTE cbBuffer[SOCKET_TCP_PACKET];
		ZeroMemory(&cbBuffer,sizeof(cbBuffer));

		wPacketSize = m_GameUserListDlg->SetSysUserDataInfo(cbBuffer,sizeof(cbBuffer));

		if (wPacketSize == 0)
		{
			return false;
		}

		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_GAME_SET,cbBuffer,wPacketSize);
	}

// 	if (m_OUserSet == true)
// 	{
// 		m_OUserSet = false;
// 
// 		WORD wPacketSize;
// 		BYTE cbBuffer[SOCKET_TCP_PACKET];
// 		ZeroMemory(&cbBuffer,sizeof(cbBuffer));
// 
// 		wPacketSize = m_GameUserListDlg->SetUserDataInfo(cbBuffer,sizeof(cbBuffer));
// 
// 		ASSERT(GetMissionManager()!=NULL);
// 		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_SCORE,cbBuffer,wPacketSize);
// 
// 	}

	if (m_SysScoreGameSet == true)
	{
		m_SysScoreGameSet = false;


		WORD wPacketSize;
		BYTE cbBuffer[SOCKET_TCP_PACKET];
		ZeroMemory(&cbBuffer,sizeof(cbBuffer));

		wPacketSize = m_GameUserListDlg->SetSysGameDataInfo(cbBuffer,sizeof(cbBuffer));

		if (wPacketSize == 0)
		{
			return false;
		}
		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_SYS_SET,cbBuffer,wPacketSize);
	}

	if (m_SetUserVip == true)
	{
		m_SetUserVip = false;


		WORD wPacketSize;
		BYTE cbBuffer[SOCKET_TCP_PACKET];
		ZeroMemory(&cbBuffer,sizeof(cbBuffer));

		wPacketSize = m_GameUserListDlg->SetUserVip(cbBuffer,sizeof(cbBuffer));

// 		ASSERT(GetMissionManager()!=NULL);
// 		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_VIP,cbBuffer,wPacketSize);
	}
	if (m_SetDLUserVip == true)
	{
		m_SetDLUserVip = false;

		WORD wPacketSize;
		BYTE cbBuffer[SOCKET_TCP_PACKET];
		ZeroMemory(&cbBuffer,sizeof(cbBuffer));

		wPacketSize = m_GameUserListDlg->SetDLUserVip(cbBuffer,sizeof(cbBuffer));

		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_DELETE_USER_VIP,cbBuffer,wPacketSize);
	}

	return true;
}

bool CMissionUserInfo::OnEventMissionShut(BYTE cbShutReason)
{



	return true;
}

bool CMissionUserInfo::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	if (Command.wMainCmdID == MDM_UM_USER)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_UM_USER_INFO:
			{
				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;
	
				//变量定义
				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);

				if (ptagUMUserScoreSet->nVipType == 3)
				{
					m_pSilverDlg->OnInsertSilver(ptagUMUserScoreSet);

					break;
				}
	
				//获取对象
				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();
	
				CUserServerInfo* pCUserServerInfo = CUserServerInfo::GetInstance();

// 				if (pCUserServerInfo->m_IsSearch==true || ptagUMUserScoreSet->wOnline == 0)
// 				{
// 					//pServerUserInfoData->OnSreachOffLineUserInfo(ptagUMUserScoreSet);
// 					m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);
// 				}
				pServerUserInfoData->OnInsertUserInfo(ptagUMUserScoreSet);

				/*m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);*/
	
				break;
			}
		case SUB_UM_USER_ENTER:           //用户进入房间
			{
			
				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;

				//变量定义
				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);

				if (ptagUMUserScoreSet->nVipType == 3)
				{
					m_pSilverDlg->OnInsertSilver(ptagUMUserScoreSet);

					break;
				}

				//获取对象
				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

				pServerUserInfoData->OnInsertUserInfo(ptagUMUserScoreSet);

				//m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);

				m_hWnd = ::FindWindow(NULL,"AdminControl");
				if (m_hWnd == false)
				{
					break;
				}

				//::SendMessage(m_hWnd,WM_USER_ONLINE_PROMPT,0L,0L);

				break;
			}
		case SUB_UM_USER_LEAVE:           //用户退出房间
			{
				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;

				//变量定义
				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);

				if (ptagUMUserScoreSet->nVipType == 3)
				{
					m_pSilverDlg->OnDeleteSilver(ptagUMUserScoreSet);

					//获取对象
					ASSERT(CUserServerInfo::GetInstance()!=NULL);
					CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

					pServerUserInfoData->OnDeleteUserInfo(ptagUMUserScoreSet);

					break;
				}

				//获取对象
				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

				pServerUserInfoData->OnDeleteUserInfo(ptagUMUserScoreSet);
				
				break;
			}
		case SUB_UM_USER_SCORE:           //用户得分
			{
				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;

				//变量定义
				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);

				if (ptagUMUserScoreSet->nVipType == 3)
				{
					m_pSilverDlg->OnInsertSilver(ptagUMUserScoreSet);

					//获取对象
					ASSERT(CUserServerInfo::GetInstance()!=NULL);
					CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

					pServerUserInfoData->OnDeleteUserInfo(ptagUMUserScoreSet);

					break;
				}

				//获取对象
				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

				if (/*pCUserServerInfo->m_IsSearch==true ||*/ ptagUMUserScoreSet->wOnline == 0)
				{
					//pServerUserInfoData->OnSreachOffLineUserInfo(ptagUMUserScoreSet);
					m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);
				}

				pServerUserInfoData->OnInsertUserInfo(ptagUMUserScoreSet);

				break;
			}
		case SUB_UM_GET_USER_GAME_SET:
			{
				ASSERT(wDataSize%sizeof(tagUMUserGameSet)==0);
				if (wDataSize%sizeof(tagUMUserGameSet)!=0) return false;

				tagUMUserGameSet* ptagUMUserGameSet = (tagUMUserGameSet*)(pData);

				if (m_GameUserListDlg->GetSysUserDataInfo(ptagUMUserGameSet) == true) break;
				

				break;
			}
		case SUB_UM_GET_SYS_SET:
			{
				ASSERT(wDataSize%sizeof(tagUMSysGameSet)==0);
				if (wDataSize%sizeof(tagUMSysGameSet)!=0) return false;

				tagUMSysGameSet* ptagUMSysGameSet = (tagUMSysGameSet*)(pData);

				if (m_StockDlg != NULL)
				{
					m_StockDlg->OnInsertStockInfo(ptagUMSysGameSet);
				}
				
				if (m_GameUserListDlg != NULL)
				{
					m_GameUserListDlg->GetSysGameDataInfo(ptagUMSysGameSet);
					m_GameUserListDlg->GetTankingDataInfo(ptagUMSysGameSet);
				}				

				break;
			}
		case SUB_UM_GET_ALL_STORAGE:
			{
				ASSERT(wDataSize%sizeof(tabStoragStart)==0);
				if(wDataSize%sizeof(tabStoragStart)!=0) return false;

				tabStoragStart* ptabStoragStart = (tabStoragStart*)(pData);

//				m_StockDlg->OnInsertStockInfo(ptabStoragStart);

				break;
			}
		case SUB_UM_ADMIN:
			{
				ASSERT(wDataSize%sizeof(tagAdmin)==0);
				if (wDataSize%sizeof(tagAdmin)!=0) return false;

				tagAdmin* ptagAdmin = (tagAdmin*)(pData);

				m_pLogDlg->OnInsertOnLineUser(ptagAdmin);
				
				break;
			}
		case SUB_UM_LOG:
			{
				ASSERT(wDataSize%sizeof(tagLog)==0);
				if(wDataSize%sizeof(tagLog)!=0) return false;
					
				tagLog* ptagLog = (tagLog*)(pData);

				switch(ptagLog->dwType)
				{
				case 1:
					{
						m_pLogDlg->OnInsertLog(ptagLog);
					}
					break;
				case 2:
					{
						m_GameUserListDlg->OnInsetWarnningDataBase(ptagLog);
					}
					break;
				}


				break;
			}
		case SUB_UM_GET_OFFLINE://获取离线用户
			{
				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;

				//变量定义
				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);

				CUserServerInfo* pCUserServerInfo = CUserServerInfo::GetInstance();

				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

// 				if (pCUserServerInfo->m_IsSearch==true && ptagUMUserScoreSet->wOnline == 0)
// 				{
// 					pServerUserInfoData->OnSreachOffLineUserInfo(ptagUMUserScoreSet);
// 					//m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);
// 				}else
					m_pOffLineUserDlg->OnInsertOFFLineUserInfo(ptagUMUserScoreSet);

					break;
			}
		case SUB_UM_TRANSFERSCORE:
			{	
// 				if (m_IsAccurateSreach == true)
// 				{
// 					ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
// 					if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;
// 
// 					//变量定义
// 					tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);
// 
// 					m_GameUserListDlg->m_GameUserList.ShowUserInfo(ptagUMUserScoreSet);
// 					m_IsAccurateSreach = false;
// 				}else{
					ASSERT(wDataSize%sizeof(tagTransferScore)==0);
					if (wDataSize%sizeof(tagTransferScore)!=0) return false;
	
					tagTransferScore* pTransferScore = (tagTransferScore*)pData;

					m_GameUserListDlg->OnInsertTransferScoreInfo(pTransferScore);

					//
					CString szuserid,sztargetuserid,sznickname,sztargetnickname,transferscore;
					CString szgameid,sztargetgameid;
					sznickname.Format("%s(%ld)",pTransferScore->szNikeName,pTransferScore->dwGameID);
					sztargetnickname.Format("%s(%ld)",pTransferScore->szTargetNikeName,pTransferScore->dwTargetGameID);
					transferscore.Format("%I64d",pTransferScore->lScore);

// 					CStdioFile file;
// 					CString filePathName;
// 					CString result;
// 
// 					filePathName = GetModuleDir();
// 					CString filename = "/LogInfo.txt";
// 					filePathName += filename;
// 
// 					if(filePathName == "")  return true;
// 					if (PathFileExists(filePathName))
// 					{
// 						//存在
// 						if(!file.Open(filePathName,/*CFile::modeCreate|*/CFile::modeReadWrite))
// 						{
// 							MessageBox("can not open file!");
// 							return true;
// 						}
// 					}else{
// 						if(!file.Open(filePathName,CFile::modeCreate|CFile::modeReadWrite))
// 						{
// 							MessageBox("can not open file!");
// 							return true;
// 						}
// 					}
// 
// 
// 					file.SeekToEnd();
// 
// 					CString  szText,sztexts;
// 					CTime tmSCan = CTime::GetCurrentTime();
// 					CString szTime = tmSCan.Format("'%Y-%m-%d %H:%M:%S':");
// 					szText += szTime;
// 					szText += sznickname;
// 					sztexts.Format("转给");
// 					szText += sztexts;
// 					szText += sztargetnickname;
// 					szText += transferscore;
// 					sztexts.Format("\n");
// 					szText += sztexts;
// 
// 					file.WriteString(szText);
// 
// 					file.Close();
//				}

				break;
			}
		case SUB_UM_ANDROIDCOUNT:
			{
				ASSERT(wDataSize%sizeof(tagAndroidCount)==0);
				if (wDataSize%sizeof(tagAndroidCount)!=0) return false;

				tagAndroidCount* ptagAndroidCount = (tagAndroidCount*)pData;

				m_GameUserListDlg->OnSetAndroidCount(ptagAndroidCount);

				break;
			}
		case SUB_UM_GAMESCORE:  //20141112用户输赢排名
			{
				if(wDataSize < sizeof(tagQueryGameScore))
					return false;
				
				tagQueryGameScore *pUserScore = (tagQueryGameScore *)pData;
				int nIndex = wDataSize/sizeof(tagQueryGameScore);
				
				m_StockDlg->m_StockUserList.DeleteAllItems();

				for(int n=0; n < nIndex; ++n)
				{

					m_StockDlg->m_StockUserList.OnInsertStockDataInfo(pUserScore[n]);

				}

				break;
			}
// 		case SUB_UM_GET_USER://搜索离线用户
// 			{
// 				ASSERT(wDataSize%sizeof(tagUMUserScoreSet)==0);
// 				if (wDataSize%sizeof(tagUMUserScoreSet)!=0) return false;
// 
// 				//变量定义
// 				tagUMUserScoreSet * ptagUMUserScoreSet=(tagUMUserScoreSet *)(pData);
// 
// 				//获取对象
// 				ASSERT(CUserServerInfo::GetInstance()!=NULL);
// 				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();
// 
// 				pServerUserInfoData->OnSreachOffLineUserInfo(ptagUMUserScoreSet);
// 			}
// 		case SUB_UM_LTANKING:
// 			{
// 				ASSERT(wDataSize%sizeof(tagUMSysGameSet)==0);
// 				if (wDataSize%sizeof(tagUMSysGameSet)!=0) return false;
// 
// 				tagUMSysGameSet* ptagGameSet = (tagUMSysGameSet*)(pData);
// 
// 				m_GameUserListDlg->GetTankingDataInfo(ptagGameSet);
// 			}
		}
	}

	return true;
}

CString CMissionUserInfo::GetModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 

	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath.Left( nPos ); 
}

void CMissionUserInfo::SetUserInfo()
{
	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

	wPacketSize = m_GameUserListDlg->SetUserDataInfo(cbBuffer,sizeof(cbBuffer));

	if (wPacketSize == 0)
	{
		return;
	}

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_SCORE,cbBuffer,wPacketSize);
}

void CMissionUserInfo::SetOffLineUser(tagUMUserScoreSet offlineuserInfo)
{
//	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

// 	wPacketSize = m_GameUserListDlg->SetUserDataInfo(cbBuffer,sizeof(cbBuffer));
// 
// 	if (wPacketSize == 0)
// 	{
// 		return;
// 	}


	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_SCORE,&offlineuserInfo,sizeof(tagUMUserScoreSet));
}

void CMissionUserInfo::SetSysInfo()
{
	ASSERT(m_SysScoreSet==false);
	if (m_SysScoreSet == true) return;

	m_SysScoreSet = true;

	//激活连接
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//设置地址
	LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
	if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) 
		pMissionManager->SetCustomServer(pszCurrentServer);

	//激活任务
	pMissionManager->AvtiveMissionItem(this,false);

}

void CMissionUserInfo::SetSysGameInfo()
{
	ASSERT(m_SysScoreGameSet==false);
	if (m_SysScoreGameSet == true) return;

	m_SysScoreGameSet = true;

	//激活连接
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//设置地址
	LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
	if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) 
		pMissionManager->SetCustomServer(pszCurrentServer);

	//激活任务
	pMissionManager->AvtiveMissionItem(this,false);

}


void CMissionUserInfo::SetUserVip(tabUserVip ptabUserVip)
{
// 	ASSERT(m_SetUserVip==false);
// 	if(m_SetUserVip == true) return;
// 
// 	m_SetUserVip = true;
// 
// 	//激活连接
// 	ASSERT(GetMissionManager()!=NULL);
// 	CMissionManager * pMissionManager=GetMissionManager();
// 
// 	//设置地址
// 	LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
// 	if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) 
// 		pMissionManager->SetCustomServer(pszCurrentServer);
// 
// 	//激活任务
// 	pMissionManager->AvtiveMissionItem(this,false);
	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_VIP,&ptabUserVip,sizeof(tabUserVip));
}

void CMissionUserInfo::SetDLUserVip(tabUserVip ptabUserVip)
{
// 	ASSERT(m_SetDLUserVip==false);
// 	if(m_SetDLUserVip == true) return;
// 
// 	m_SetDLUserVip = true;

// 	WORD wPacketSize;
// 	BYTE cbBuffer[SOCKET_TCP_PACKET];
// 	ZeroMemory(&cbBuffer,sizeof(cbBuffer));
// 
// 	wPacketSize = m_GameUserListDlg->SetUserVip(cbBuffer,sizeof(cbBuffer));

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_VIP,&ptabUserVip,sizeof(tabUserVip));


	//激活连接
// 	ASSERT(GetMissionManager()!=NULL);
// 	CMissionManager * pMissionManager=GetMissionManager();
// 
// 	//设置地址
// 	LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
// 	if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) 
// 		pMissionManager->SetCustomServer(pszCurrentServer);
// 
// 	//激活任务
// 	pMissionManager->AvtiveMissionItem(this,false);
}

void CMissionUserInfo::OnReRefreshStroage()
{

	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

	wPacketSize = m_GameUserListDlg->OnReFreshStaroge(cbBuffer,sizeof(cbBuffer));
	if (wPacketSize == 0)
	{
		AfxMessageBox("没有选择游戏！");
		return;
	}

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GET_STORAGE,cbBuffer,wPacketSize);

}

void CMissionUserInfo::OnSetDeFault()
{

	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

	wPacketSize = m_GameUserListDlg->SetDefault(cbBuffer,sizeof(cbBuffer));

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_DEFAULT,cbBuffer,wPacketSize);
}

void CMissionUserInfo::OnGetStroag()
{

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GET_ALL_STORAGE);

}

void CMissionUserInfo::OnSetStroag()
{
	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

//	wPacketSize = m_StockDlg->m_StockList.OnSetStockDataInfo(cbBuffer,sizeof(cbBuffer));
	
	wPacketSize = m_StockDlg->OnSetStock(cbBuffer,sizeof(cbBuffer));

	if (wPacketSize == 0)
	{
		return;
	}

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_ALL_STORAGE,cbBuffer,wPacketSize);

}

void CMissionUserInfo::OnSetTanking()
{
	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

	wPacketSize = m_GameUserListDlg->SetTanking(cbBuffer,sizeof(cbBuffer));
	if (wPacketSize == 0)
	{
		return;
	}

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_LTANKING,cbBuffer,wPacketSize);
}

void CMissionUserInfo::OnSetRemarks(DWORD UserID,CString Remarks)
{
//	WORD wPacketSize;
	BYTE cbBuffer[SOCKET_TCP_PACKET];
	ZeroMemory(&cbBuffer,sizeof(cbBuffer));

	//获取对象
	ASSERT(CUserServerInfo::GetInstance()!=NULL);
	CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

	CUserInfoMap::iterator it = pServerUserInfoData->m_UserInfoMap.find(UserID);

	if (it != pServerUserInfoData->m_UserInfoMap.end())
	{
		CUserInfoItem* pCUserInfoItem;
		pCUserInfoItem = it->second;
		tagUMUserScoreSet* ptagScoreSet = new tagUMUserScoreSet;

		CopyMemory(ptagScoreSet,&pCUserInfoItem->m_tagUMUserScoreSet,sizeof(tagUMUserScoreSet));

		sprintf(ptagScoreSet->szRemarks, Remarks);
		
		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_SET_USER_SCORE,ptagScoreSet,sizeof(tagUMUserScoreSet));
	}

}

void CMissionUserInfo::OnGetOffLineUser()
{
	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GET_OFFLINE);
}

void CMissionUserInfo::SreachOffLineUser(CString szSreachInfo)
{
	tagFindUser* pFindUser = new tagFindUser;

	sprintf(pFindUser->szText, szSreachInfo);

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GET_USER,pFindUser,sizeof(tagFindUser));
}

void CMissionUserInfo::OnSreachOffLineUser(CString szUserID)
{
	tabUserID* pUserId = new tabUserID;

	pUserId->dwUserID = _ttoi(szUserID);

	m_IsAccurateSreach = true;

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GET_USER_EX,pUserId,sizeof(tabUserID));
}

void CMissionUserInfo::OnGetStockUser(tagQueryGame* QueryGame)
{
	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_GAMESCORE,QueryGame,sizeof(tagQueryGame));
}

void CMissionUserInfo::OnFrezon(tagUserID* UserId)
{
	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_FORZENUSER,UserId,sizeof(tagUserID));
}

void CMissionUserInfo::OnSetAndroidCount(INT AndroidCount,WORD ServerID)
{
	tagAndroidCount* pAndroidCount = new tagAndroidCount;

	pAndroidCount->dwServerID = ServerID;
	pAndroidCount->nAndroidCount = AndroidCount;
	pAndroidCount->dwBeginTime = 0;
	pAndroidCount->dwEndTime = 0;

	ASSERT(GetMissionManager()!=NULL);
	GetMissionManager()->SendData(MDM_UM_USER,SUB_UM_ANDROIDCOUNT,pAndroidCount,sizeof(tagAndroidCount));

}