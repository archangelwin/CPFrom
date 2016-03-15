#include "StdAfx.h"
#include "SocketClient.h"
#include "ServerListData.h"

#define IDI_SEND_MESSAGE              100

CWinThread* SendThread = NULL;

bool    m_IsThreadRun = false;

UINT _SendThread(LPVOID param)
{
	CSocketClient* pSocket = (CSocketClient*)param;

	while (m_IsThreadRun)
	{
		if (pSocket->m_TCPSocketModule->SendData(MDM_KN_COMMAND,SUB_KN_DETECT_SOCKET) == FALSE)
		{
			if (pSocket->m_IsBkConnect == false)
			{
				pSocket->m_TCPSocketModule->CloseSocket();
				pSocket->OnSocketConnect(pSocket->m_dwIPAddress,pSocket->m_wCurrentPort);
			}else
			{
				pSocket->m_TCPSocketModule->CloseSocket();
				pSocket->OnSocketConnect(pSocket->m_dwBackAddress,pSocket->m_dwBackPort);
			}
			
		}
		
		Sleep(10000);
 	}


//	pDlg->m_IsThreadStart = false;

	return 0;
}

BEGIN_MESSAGE_MAP(CSocketClient, CWnd)
END_MESSAGE_MAP()

CSocketClient::CSocketClient(void)
{
	//创建组件
	if (m_TCPSocketModule.GetInterface()==NULL)
	{
		if (m_TCPSocketModule.CreateInstance()==false) return;
		if (m_TCPSocketModule->SetTCPSocketSink(QUERY_ME_INTERFACE(IUnknownEx))==false) return;
	}

	m_IsConnect = false;
	m_IsThreadStart = false;
	m_IsBkConnect = false;
	m_IsPlazaLogon = false;
}

CSocketClient::~CSocketClient(void)
{
	OnCloseThread();
	m_TCPSocketModule->CloseSocket();
}

bool CSocketClient::OnSocketConnect(DWORD sIP,WORD sPort)
{
	if(m_TCPSocketModule->Connect(sIP,sPort)!=CONNECT_SUCCESS)
	{
		
		return false;
	}

// 	if (m_TCPSocketModule->GetSocketStatus() == SOCKET_STATUS_WAIT)
// 	{
// 		m_hWnd = ::FindWindow(NULL,"UserHangUp");
// 		if (m_hWnd == false)
// 		{
// 			return false;
// 		}
// 		
// 		::SendMessage(m_hWnd,WM_LOGON_CONNECTING,0L,0L);
// 		
// 	}

	return true;
}

VOID * CSocketClient::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);

	return NULL;
}

bool CSocketClient::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	if (m_IsConnect == true)
	{
		return false;
	}

 	TCHAR szPassword[LEN_MD5];

	if (m_IsPlazaLogon == true)
	{
// 		//变量定义
// 		CMD_GP_LogonGameID  LogonGameID;
// 		ZeroMemory(&LogonGameID,sizeof(LogonGameID));
// 
// 		//系统信息
// 		LogonGameID.dwPlazaVersion=VERSION_PLAZA;
// 		//机器标识
// 		CWHService::GetMachineIDEx(LogonGameID.szMachineID);
// 
// 		LogonGameID.dwGameID = 176285;
// 		CString password = "xiang@wan1111";
// 		CWHEncrypt::MD5Encrypt(password,szPassword);
// 		lstrcpyn(LogonGameID.szPassword,szPassword,CountArray(LogonGameID.szPassword));
// 
// 		m_TCPSocketModule->SendData(MDM_GP_LOGON,SUB_GP_LOGON_GAMEID,&LogonGameID,sizeof(LogonGameID));
		OnPlazzConnect();
	}else
	{
		CMD_GR_LogonUserID lLogonID;
		ZeroMemory(&lLogonID,sizeof(lLogonID));
		//系统信息
		lLogonID.dwPlazaVersion = VERSION_PLAZA;
		lLogonID.dwFrameVersion = VERSION_FRAME;
		lLogonID.dwProcessVersion = m_wProcessVersion;

		lLogonID.dwUserID = m_UserID;
		lLogonID.wKindID = m_wKindID;
		CWHEncrypt::MD5Encrypt(m_wPassWord,szPassword);
		lstrcpyn(lLogonID.szPassword,szPassword,CountArray(lLogonID.szPassword));
		CWHService::GetMachineIDEx(lLogonID.szMachineID);

		m_SendTickCount = GetTickCount()/1000L;

		m_TCPSocketModule->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,&lLogonID,sizeof(lLogonID));
	}

	return true;
}

void CSocketClient::OnPlazzConnect()
{
	TCHAR szPassword[LEN_MD5];
	CString  Account;
	//变量定义
	CMD_GP_LogonAccounts  LogonAccount;
	ZeroMemory(&LogonAccount,sizeof(LogonAccount));

	//系统信息
	LogonAccount.dwPlazaVersion=VERSION_PLAZA;
	//机器标识
	CWHService::GetMachineIDEx(LogonAccount.szMachineID);

	Account = "Cyrillic11";
	sprintf(LogonAccount.szAccounts,Account,CountArray(LogonAccount.szAccounts));
	CString password = "CCY19900327ccy";
	CWHEncrypt::MD5Encrypt(password,szPassword);
	lstrcpyn(LogonAccount.szPassword,szPassword,CountArray(LogonAccount.szPassword));

	m_TCPSocketModule->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,&LogonAccount,sizeof(LogonAccount));

}

bool CSocketClient::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if (cbShutReason == SHUT_REASON_NORMAL)
	{
// 
// 		if (m_IsBkConnect == false)
// 		{
// 			OnSocketConnect(m_dwIPAddress,m_wCurrentPort);
// 		}else
// 			OnSocketConnect(m_dwBackAddress,m_dwBackPort);

		m_IsConnect = false;
		m_hWnd = ::FindWindow(NULL,"UserHangUp");
		if (m_hWnd == false)
		{
			return false;
		}
		::SendMessage(m_hWnd,WM_LOGON_BREAK,m_UserID,0L);

	}


	return true;
}

bool CSocketClient::OnEventTCPSocketRead(WORD wSocketID, TCP_Command Command, VOID * pData, WORD wDataSize)
{
	if (Command.wMainCmdID==MDM_KN_COMMAND)
	{
		switch(Command.wSubCmdID)
		{
		case SUB_KN_DETECT_SOCKET:
			{

				return true;
			}
			return true;
		}
	}

	if (Command.wMainCmdID==MDM_GR_LOGON)
	{
		m_RecvTickCount = GetTickCount()/1000L;

		switch(Command.wSubCmdID)
		{
		case SUB_GR_LOGON_SUCCESS:
			{
				m_IsConnect = true;

// 				m_hWnd = ::FindWindow(NULL,"UserHangUp");
// 				if (m_hWnd == false)
// 				{
// 					return false;
// 				}
// 				::SendMessage(m_hWnd,WM_LOGON_SUCCESS,m_UserID,0L);

				return true;
			}
		case SUB_GR_LOGON_FAILURE:
			{
				m_IsConnect = false;

				CMD_GR_LogonFailure * pLogonFailure=(CMD_GR_LogonFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GR_LogonFailure)-sizeof(pLogonFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GR_LogonFailure)-sizeof(pLogonFailure->szDescribeString))) return false;

				m_hWnd = ::FindWindow(NULL,"UserHangUp");
				if (m_hWnd == false)
				{
					return false;
				}
				m_TCPSocketModule->CloseSocket();
				
				::SendMessage(m_hWnd,WM_LOGON_FAILURE,m_UserID,(LPARAM)pLogonFailure);

				

				return true;
			}
		case SUB_GR_LOGON_FINISH:
			{
				m_IsConnect = true;

				m_hWnd = ::FindWindow(NULL,"UserHangUp");
				if (m_hWnd == false)
				{
					return false;
				}
				::SendMessage(m_hWnd,WM_LOGON_SUCCESS,m_UserID,0L);

//				::SetTimer(this->m_hWnd,IDI_SEND_MESSAGE,1000,NULL);
				if (m_IsThreadStart == false)
				{
					SendThread = ::AfxBeginThread(_SendThread,this);
					m_IsThreadRun = true;
					m_IsThreadStart = true;
					//SendThread->ResumeThread();
				}
				
				
				
				return true;
			}
		case SUB_GR_UPDATE_NOTIFY:
			{
// 
// 				AfxMessageBox("1");
				return true;
			}
		}
	}


	if (Command.wMainCmdID==MDM_GP_LOGON)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_LOGON_SUCCESS:	//登录成功
			{
				//return OnSocketSubLogonSuccess(pData,wDataSize);
			}
		case SUB_GP_LOGON_FAILURE:	//登录失败
			{
				//return OnSocketSubLogonFailure(pData,wDataSize);
			}
		case SUB_GP_LOGON_FINISH:	//登录完成
			{
				//return OnSocketSubLogonFinish(pData,wDataSize);
			}
		case SUB_GP_VALIDATE_MBCARD:	//登录失败
			{
				//return OnSocketSubLogonValidateMBCard(pData,wDataSize);
			}
		case SUB_GP_UPDATE_NOTIFY:	//升级提示
			{
				//return OnSocketSubUpdateNotify(pData,wDataSize);
			}
		}
	}

	if (Command.wMainCmdID==MDM_GP_SERVER_LIST)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_LIST_TYPE:		//种类信息
			{
				//效验参数
 				//ASSERT(wDataSize%sizeof(tagGameType)==0);
 				//if (wDataSize%sizeof(tagGameType)!=0) return false;
 
 				//变量定义
 				//WORD wItemCount=wDataSize/sizeof(tagGameType);
 				//tagGameType * pGameType=(tagGameType *)(pData);

	/*			获取对象
				ASSERT(CServerListData::GetInstance()!=NULL);
				CServerListData * pServerListData=CServerListData::GetInstance();

				更新数据
 				for (WORD i=0;i<wItemCount;i++)
 				{
 					pServerListData->InsertGameType(pGameType++);
 				}*/

				return true;
			}
		case SUB_GP_LIST_KIND:		//类型信息
			{
				//效验参数
// 				ASSERT(wDataSize%sizeof(tagGameKind)==0);
// 				if (wDataSize%sizeof(tagGameKind)!=0) return false;

				//变量定义
				WORD wItemCount=wDataSize/sizeof(tagGameKind);
				tagGameKind * pGameKind=(tagGameKind *)(pData);

				//获取对象
				ASSERT(CServerListData::GetInstance()!=NULL);
				CServerListData * pServerListData=CServerListData::GetInstance();

//				CWHService::GetModuleVersion(pGameKind->szProcessName,m_wProcessVersion);
				// 				ASSERT(CUserServerInfo::GetInstance()!=NULL);
				// 				CUserServerInfo * pServerUserInfoData=CUserServerInfo::GetInstance();

				//更新数据
				for (WORD i=0;i<wItemCount;i++)
				{
					pServerListData->InsertGameKind(pGameKind++);
				}

//				SafeDelete(pGameKind);

				return true;
			}
		case SUB_GP_LIST_NODE:		//节点信息
			{
				//效验参数
// 				ASSERT(wDataSize%sizeof(tagGameNode)==0);
// 				if (wDataSize%sizeof(tagGameNode)!=0) return false;
// 
// 				//变量定义
// 				WORD wItemCount=wDataSize/sizeof(tagGameNode);
// 				tagGameNode * pGameNode=(tagGameNode *)(pData);

				//获取对象
//				ASSERT(CServerListData::GetInstance()!=NULL);
//				CServerListData * pServerListData=CServerListData::GetInstance();

				//更新数据
// 				for (WORD i=0;i<wItemCount;i++)
// 				{
// 					pServerListData->InsertGameNode(pGameNode++);
// 				}

				return true;
			}
		case SUB_GP_LIST_PAGE:		//页面信息
			{
				//效验参数
// 				ASSERT(wDataSize%sizeof(tagGamePage)==0);
// 				if (wDataSize%sizeof(tagGamePage)!=0) return false;
// 
// 				//变量定义
// 				WORD wItemCount=wDataSize/sizeof(tagGamePage);
// 				tagGamePage * pGamePage=(tagGamePage *)(pData);

				//获取对象
//				CServerListData * pServerListData=CServerListData::GetInstance();

				//更新数据
// 				for (WORD i=0;i<wItemCount;i++)
// 				{
// 					pServerListData->InsertGamePage(pGamePage++);
// 				}

				return true;
			}
		case SUB_GP_LIST_SERVER:	//房间信息
			{
				//效验参数
//				ASSERT(wDataSize%sizeof(tagGameServer)==0);
				if (wDataSize%sizeof(tagGameServer)!=0) return false;

				//变量定义
				WORD wItemCount=wDataSize/sizeof(tagGameServer);
				tagGameServer * pGameServer=(tagGameServer *)(pData);

				m_GameInfoDB.SelectGameInfo();
				//获取对象
				CServerListData * pServerListData=CServerListData::GetInstance();

				CGameKindItem * pGameKindItem=new CGameKindItem;
				//更新数据
 				for (WORD i=0;i<wItemCount;i++)
 				{	
					bool bInsert=(pServerListData->m_GameKindItemMap.Lookup(pGameServer[i].wKindID,pGameKindItem)==FALSE);

					//获取版本
// 					if (bInsert==true)
// 					{
						LPCTSTR pszProcessName=pGameKindItem->m_GameKind.szProcessName;
						CWHService::GetModuleVersion(pszProcessName,m_wProcessVersion);
//					}
// 					pServerListData->InsertGameServer(pGameServer++);
					for (int j=0;j<m_GameInfoDB.m_GameInfo.GetCount();j++)
					{
						if (pGameServer[i].wServerPort == _ttoi(m_GameInfoDB.m_GameInfo[j]->Port) && m_wProcessVersion != _ttoi(m_GameInfoDB.m_GameInfo[j]->Version))
						{
							m_GameInfoDB.UpdateGameInfo(pGameServer[i].wKindID,pGameServer[i].wServerPort,m_wProcessVersion,pGameServer[i].szServerName);
							
							m_hWnd = ::FindWindow(NULL,"UserHangUp");
							if (m_hWnd == false)
							{
								return false;
							}
							::SendMessage(m_hWnd,WM_GAMEINFO_UPDATE,0L,0L);
							
							//continue;
						}
						//else
						//	m_GameInfoDB.InsertGameInfo(pGameServer->wKindID,pGameServer->wServerPort,m_wProcessVersion,pGameServer->szServerName);
					}

					m_GameInfoDB.InsertGameInfo(pGameServer[i].wKindID,pGameServer[i].wServerPort,m_wProcessVersion,pGameServer[i].szServerName);
 				}

//				SafeDelete(pGameServer);

				m_hWnd = ::FindWindow(NULL,"UserHangUp");
				if (m_hWnd == false)
				{
					return false;
				}
				::SendMessage(m_hWnd,WM_GAMEINFO_UPDATE,0L,0L);

				return true;
			}
		case SUB_GP_LIST_FINISH:	//列表信息
			{
				//列表完成
// 				ASSERT(CServerListData::GetInstance()!=NULL);
// 				if (CServerListData::GetInstance()!=NULL) CServerListData::GetInstance()->OnEventListFinish();

				return true;
			}
		case SUB_GP_SERVER_FINISH:	//房间完成
			{
				//效验数据
				// 				ASSERT(wDataSize%sizeof(WORD)==0);
				// 				if (wDataSize%sizeof(WORD)!=0) return false;
				// 
				// 				//获取对象
				// 				ASSERT(CServerListData::GetInstance()!=NULL);
				// 				CServerListData * pServerListData=CServerListData::GetInstance();
				// 
				// 				//任务处理
				// 				for (UINT i=0;i<(wDataSize/sizeof(WORD));i++)
				// 				{
				// 					m_KindIDPending.RemoveKey(((WORD *)pData)[i]);
				// 					pServerListData->OnEventKindFinish(((WORD *)pData)[i]);
				// 				}
				// 
				// 				//终止任务
				// 				if ((m_KindIDPending.GetCount()==0L)&&(m_bUpdateOnLine==false))
				// 				{
				// 					CMissionManager * pMissionManager=GetMissionManager();
				// 					if (pMissionManager!=NULL) 
				// 						pMissionManager->ConcludeMissionItem(this,false);
				// 				}

				return true;
			}
		case SUB_GR_KINE_ONLINE:	//类型在线
			{
				//变量定义
// 				CMD_GP_KindOnline * pKindOnline=(CMD_GP_KindOnline *)pData;
// 				WORD wHeadSize=(sizeof(CMD_GP_KindOnline)-sizeof(pKindOnline->OnLineInfoKind));
// 
// 				//效验数据
// 				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+pKindOnline->wKindCount*sizeof(tagOnLineInfoKind))));
// 				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+pKindOnline->wKindCount*sizeof(tagOnLineInfoKind)))) return false;
// 
// 				//获取对象
// 				CServerListData * pServerListData=CServerListData::GetInstance();

				//设置人数
// 				for (WORD i=0;i<pKindOnline->wKindCount;i++)
// 				{
// 					tagOnLineInfoKind * pOnLineInfoKind=&pKindOnline->OnLineInfoKind[i];
// 					pServerListData->SetKindOnLineCount(pOnLineInfoKind->wKindID,pOnLineInfoKind->dwOnLineCount);
// 				}

				return true;
			}
		case SUB_GR_SERVER_ONLINE:	//房间在线
			{
				//变量定义
// 				CMD_GP_ServerOnline * pServerOnline=(CMD_GP_ServerOnline *)pData;
// 				WORD wHeadSize=(sizeof(CMD_GP_ServerOnline)-sizeof(pServerOnline->OnLineInfoServer));
// 
// 				//效验数据
// 				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+pServerOnline->wServerCount*sizeof(tagOnLineInfoServer))));
// 				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+pServerOnline->wServerCount*sizeof(tagOnLineInfoServer)))) return false;
// 
// 				//获取对象
// 				CServerListData * pServerListData=CServerListData::GetInstance();
// 
// 				//设置人数
// // 				for (WORD i=0;i<pServerOnline->wServerCount;i++)
// // 				{
// // 					tagOnLineInfoServer * pOnLineInfoServer=&pServerOnline->OnLineInfoServer[i];
// // 					pServerListData->SetServerOnLineCount(pOnLineInfoServer->wServerID,pOnLineInfoServer->dwOnLineCount);
// // 				}
// 
// 				//完成通知
// 				pServerListData->SetServerOnLineFinish();

				//终止任务
				// 				if ((m_KindIDPending.GetCount()==0L)&&(m_bUpdateOnLine==false))
				// 				{
				// 					CMissionManager * pMissionManager=GetMissionManager();
				// 					if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);
				// 				}

				return true;
			}
		}
	}


	return true;
}

VOID CSocketClient::OnCloseThread()
{
	m_hWnd = ::FindWindow(NULL,"UserHangUp");
	if (m_hWnd == false)
	{
		return;
	}
	::SendMessage(m_hWnd,WM_THREAD_QUIT,m_UserID,0L);

	if (m_IsThreadRun == true)
	{
		m_IsThreadRun = false;
		m_IsThreadStart = false;
		SendThread->ResumeThread();
		//::WaitForSingleObject(SendThread->m_hThread,INFINITE);
		while (TRUE)
		{

			DWORD result ; 
			MSG msg ; 

			result  =  MsgWaitForMultipleObjects( 1 ,  &SendThread->m_hThread, 
				FALSE, INFINITE, QS_ALLINPUT); 

			switch(result)  
			{  
			case WAIT_OBJECT_0:   
				break; //break the loop  
			case WAIT_OBJECT_0 + 1:  
				//get the message from Queue  
				//and dispatch it to specific window  
				PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);  
				DispatchMessage(&msg);   
				continue;  
			default:  
				break; // unexpected failure  
			}  
			break;  
		} 
	}

	/*AfxMessageBox("Thread exit");*/
// 	m_hWnd = ::FindWindow(NULL,"UserHangUp");
// 	if (m_hWnd == false)
// 	{
// 		return;
// 	}
// 	::SendMessage(m_hWnd,WM_THREAD_QUIT,0L,0L);
//	delete SendThread;
//	SendThread = NULL;

}

bool CSocketClient::OnChangeConnect()
{
	if (m_IsBkConnect == false)
	{
		m_IsBkConnect = true;
		OnCloseThread();
		m_TCPSocketModule->CloseSocket();

		if(m_TCPSocketModule->Connect(m_dwBackAddress,m_dwBackPort)!=CONNECT_SUCCESS)
			return false;
	}else
	{
		m_IsBkConnect = false;
		OnCloseThread();
		m_TCPSocketModule->CloseSocket();

		if (OnSocketConnect(m_dwIPAddress,m_wCurrentPort)==false)
			return false;
	}


	return true;
}