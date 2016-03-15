#include "StdAfx.h"
#include "MissionManager.h"

//////////////////////////////////////////////////////////////////////////////////

//�ر�����
#define IDI_CLOSE_LINK					100								//��������
#define IDI_RETRY_LINK                  101                             //��������

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMissionManager, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CMissionSocket::CMissionSocket()
{
	//״̬����
	m_bSwitchDns=false;
	m_bTryDefault=false;
	m_wSwitchIndex=INVALID_WORD;

	//��ǰ����
	m_wCurrentPort=PORT_LOGON;
	m_dwCurrentServer=INADDR_NONE;

	//��ַ��Ϣ
	m_szCustomServer[0]=0;
	m_szCurrentServer[0]=0;

	//�ӿڱ���
	m_pIMissionSocketSink=NULL;

	return;
}

//��������
CMissionSocket::~CMissionSocket()
{
}

//�ӿڲ�ѯ
VOID * CMissionSocket::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//�����¼�
bool CMissionSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{		
	//�ر�����
	if (nErrorCode!=0)
	{
		if ((nErrorCode==WSAETIMEDOUT)||(nErrorCode==WSAECONNREFUSED)||(nErrorCode==WSAEADDRNOTAVAIL))
		{
			PerformClose(SHUT_REASON_TIME_OUT);
		}
		else
		{
			PerformClose(SHUT_REASON_NORMAL);
		}
	}

	//����֪ͨ
	ASSERT(m_pIMissionSocketSink!=NULL);
	if (m_pIMissionSocketSink!=NULL) 
		m_pIMissionSocketSink->OnEventMissionLink(nErrorCode);

	return true;
}

//�ر��¼�
bool CMissionSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//�ر�֪ͨ
	ASSERT(m_pIMissionSocketSink!=NULL);
	if (m_pIMissionSocketSink!=NULL) 
		m_pIMissionSocketSink->OnEventMissionShut(cbShutReason);

	return true;
}

//��ȡ�¼�
bool CMissionSocket::OnEventTCPSocketRead(WORD wSocketID, TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//��ȡ֪ͨ
	ASSERT(m_pIMissionSocketSink!=NULL);
	if (m_pIMissionSocketSink!=NULL) 
		m_pIMissionSocketSink->OnEventMissionRead(Command,pData,wDataSize);

	return true;
}

//����״̬
BYTE CMissionSocket::GetSocketStatus()
{
	//��������
	BYTE cbSocketStatus=SOCKET_STATUS_IDLE;

	//��ȡ״̬
	if (m_TCPSocketModule.GetInterface()!=NULL)
	{
		cbSocketStatus=m_TCPSocketModule->GetSocketStatus();
	}

	return cbSocketStatus;
}

//���õ�ַ
VOID CMissionSocket::SetCustomServer(LPCTSTR pszCustomServer)
{
	//���ñ���
	ASSERT((pszCustomServer!=NULL)&&(pszCustomServer[0]!=0));
	lstrcpyn(m_szCustomServer,pszCustomServer,CountArray(m_szCustomServer)); 

	return;
}

//�ж�����
bool CMissionSocket::PerformClose(BYTE cbShutReason)
{
	//�ر�����
	ASSERT(m_TCPSocketModule.GetInterface()!=NULL);
	if (m_TCPSocketModule.GetInterface()!=NULL) 
		m_TCPSocketModule->CloseSocket(cbShutReason);

	return true;
}

//��������
bool CMissionSocket::PerformConnect(bool bContinue)
{
	//״̬Ч��
	ASSERT(GetSocketStatus()==SOCKET_STATUS_IDLE);
	if (GetSocketStatus()!=SOCKET_STATUS_IDLE) return false;

	//�������
	if (m_TCPSocketModule.GetInterface()==NULL)
	{
		if (m_TCPSocketModule.CreateInstance()==false) return false;
		if (m_TCPSocketModule->SetTCPSocketSink(QUERY_ME_INTERFACE(IUnknownEx))==false) return false;
	}

	//���û���
	if (bContinue==false)
	{
		//���ñ���
		m_bSwitchDns=false;
		m_bTryDefault=false;
		m_wSwitchIndex=INVALID_WORD;

		//���ô���
		CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
		if (m_TCPSocketModule->SetProxyServerInfo(pParameterGlobal->m_cbProxyType,pParameterGlobal->m_ProxyServer)==false)
		{
			ASSERT(FALSE);
			return false;
		}

		//��ȡ��ַ
		if (m_szCustomServer[0]==0)
		{
			CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
			pGlobalServer->GetLastServerName(m_szCustomServer);
		}

		//���ñ���
		m_wCurrentPort=PORT_LOGON;
		lstrcpyn(m_szCurrentServer,m_szCustomServer,CountArray(m_szCurrentServer));

		//Ĭ�ϵ�ַ
		if ((GetServerInfo()==false)&&(SwitchServerItem()==false))
		{
			ASSERT(FALSE);
			return false;
		}
	}
	else
	{
		//�л�����
		if (SwitchServerItem()==false)
		{
			return false;
		}
	}
	//CString sIp = inet_ntoa(ina1.sin_addr);;
 //   CString sMsg;
	//sMsg.Format("ccc, %d",m_dwCurrentServer);
	//AfxMessageBox(sMsg);	
	//��������
	if (m_TCPSocketModule->Connect(m_dwCurrentServer,m_wCurrentPort)!=CONNECT_SUCCESS) 
		return false;

	return true;
}

//���ͺ���
bool CMissionSocket::PerformSendData(WORD wMainCmdID, WORD wSubCmdID)
{
	//״̬Ч��
	ASSERT(GetSocketStatus()==SOCKET_STATUS_CONNECT);
	if (GetSocketStatus()!=SOCKET_STATUS_CONNECT) return false;

	//��������
	ASSERT(m_TCPSocketModule.GetInterface()!=NULL);
	if (m_TCPSocketModule.GetInterface()!=NULL) m_TCPSocketModule->SendData(wMainCmdID,wSubCmdID);

	return true;
}

//���ͺ���
bool CMissionSocket::PerformSendData(WORD wMainCmdID, WORD wSubCmdID, VOID * const pData, WORD wDataSize)
{
	//״̬Ч��
	ASSERT(GetSocketStatus()==SOCKET_STATUS_CONNECT);
	if (GetSocketStatus()!=SOCKET_STATUS_CONNECT) return false;

	//��������
	ASSERT(m_TCPSocketModule.GetInterface()!=NULL);
	if (m_TCPSocketModule.GetInterface()!=NULL) m_TCPSocketModule->SendData(wMainCmdID,wSubCmdID,pData,wDataSize);

	return true;
}

//��ַ��Ϣ
bool CMissionSocket::GetServerInfo()
{
	//Ч�����
	ASSERT(m_szCurrentServer[0]!=0);
	if (m_szCurrentServer[0]==0) 
		return false;

	//��������
	tagServerItem ServerItem;
	ZeroMemory(&ServerItem,sizeof(ServerItem));

	//���ñ���
	m_wCurrentPort=PORT_LOGON;
	m_dwCurrentServer=INADDR_NONE;

	//��ȡ��Ϣ
	CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
	CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
	bool bSuccess=pGlobalServer->GetServerItemInfo(m_szCurrentServer,ServerItem);

	//ת����ַ
	if (bSuccess==true)
	{
		if(ServerItem.dwServerAddr==INADDR_NONE) //û������ip,ʹ������
		{
			LPHOSTENT lpHost=gethostbyname(CT2CA(ServerItem.szServerHost));
			if (lpHost!=NULL) 
			{
				ServerItem.dwServerAddr=((LPIN_ADDR)lpHost->h_addr)->s_addr;
				//CString sMsa;
				//sMsa.Format("kkk,%s,%d",ServerItem.szServerHost,ServerItem.dwServerAddr);
				//AfxMessageBox(sMsa);
			}
		}

	}

	//���ַ���
	if (ServerItem.dwServerAddr==INADDR_NONE)
	{
		//�����ַת��
		CT2CA CurrentServer(m_szCurrentServer);
		ServerItem.dwServerAddr=inet_addr(CurrentServer);

		//��������
		if (ServerItem.dwServerAddr==INADDR_NONE)
		{
			LPHOSTENT lpHost=gethostbyname(CurrentServer);
			if (lpHost!=NULL) 
				ServerItem.dwServerAddr=((LPIN_ADDR)lpHost->h_addr)->s_addr;
		}
	}

	//�������
	if (ServerItem.dwServerAddr!=INADDR_NONE)
	{
		//���ñ���
		m_wCurrentPort=ServerItem.wServerPort;
		m_dwCurrentServer=ServerItem.dwServerAddr;
		//CString sms;
		//sms.Format("bbb,%d",m_dwCurrentServer);
		//AfxMessageBox(sms);
		return true;
	}
	return false;
}

//�л�����
bool CMissionSocket::SwitchServerItem()
{
	do
	{
		//��ȡ��Ϣ
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		if (m_wSwitchIndex >= pGlobalServer->GetItemCount() && m_wSwitchIndex!=INVALID_WORD)
		{
			break;
		}
		pGlobalServer->GetServerItemName(++m_wSwitchIndex,m_szCurrentServer);
		//״̬�л�
		if (m_szCurrentServer[0]==0) //û�ҵ�
		{
			//m_wSwitchIndex=INVALID_WORD;
			continue;
		}
		//��ͬ�ж�
		if (lstrcmp(m_szCurrentServer,m_szCustomServer)==0) 
			continue;

		//��ȡ��Ϣ
		if (GetServerInfo()==true) 
			return true;

	} while (true);

	//����Ĭ��
	if (m_bTryDefault==false)
	{
		//���ñ���
		m_bTryDefault=true;
		CGlobalServer * pGlobalServer=CGlobalServer::GetInstance();
		lstrcpyn(m_szCurrentServer,pGlobalServer->GetPlatformServer(1),CountArray(m_szCurrentServer));

		//��ȡ��Ϣ
		if (GetServerInfo()==true) 
			return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CMissionItem::CMissionItem()
{
	//���ñ���
	m_bActiveStatus=false;
	m_pMissionManager=NULL;

	return;
}

//��������
CMissionItem::~CMissionItem()
{
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CMissionManager::CMissionManager()
{
	//�������
	m_MissionSocket.SetMissionSocketSink(this);

	return;
}

//��������
CMissionManager::~CMissionManager()
{
	int aa = 2;
}

//�����¼�
bool CMissionManager::OnEventMissionLink(INT nErrorCode)
{
	//����֪ͨ
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		//��ȡ����
		CMissionItem * pMissionItem=m_MissionItemArray[i];

		//�¼�����
		if (pMissionItem->m_bActiveStatus==true)
		{
			//����״̬
			if (nErrorCode!=0L)
			{
				if ((nErrorCode==WSAETIMEDOUT)||(nErrorCode==WSAECONNREFUSED)||(nErrorCode==WSAEADDRNOTAVAIL))
				{
					//��������
					AvtiveMissionItem(pMissionItem,true);
					return true;
				}
				else
				{
					pMissionItem->m_bActiveStatus=false;
				}
			}
			else
			{
				//��������
				KillTimer(IDI_RETRY_LINK);
			}

			//�¼�֪ͨ
			pMissionItem->OnEventMissionLink(nErrorCode);
		}
		//else
		//{
		//	if (nErrorCode==0L)
		//	{
		//		//�¼�֪ͨ
		//		pMissionItem->OnEventMissionLink(nErrorCode);
		//	}
		//}
	}

	return true;
}
//�����¼�
//void CMissionManager::OnEventMissionReConnect(INT nErrorCode)
//{
//	//����֪ͨ
//	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
//	{
//		//��ȡ����
//		CMissionItem * pMissionItem=m_MissionItemArray[i];
//		//�¼�����
//		if (pMissionItem->m_bActiveStatus==false)
//		{
//			if ((nErrorCode==WSAETIMEDOUT)||(nErrorCode==WSAECONNREFUSED)||(nErrorCode==WSAEADDRNOTAVAIL))
//			{
//				pMissionItem->m_bActiveStatus=true;
//
//			}
//		}OnEventTCPSocketLink
//	}
//}

//�ر��¼�
bool CMissionManager::OnEventMissionShut(BYTE cbShutReason)
{
	//�ر�֪ͨ
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		try
		{
			//��ȡ����
			CMissionItem * pMissionItem=m_MissionItemArray[i];

			//�¼�����
			if (pMissionItem->m_bActiveStatus==true)
			{
				pMissionItem->m_bActiveStatus=false;
			}
			pMissionItem->OnEventMissionShut(cbShutReason);
		}
		catch (CMemoryException* e)
		{
			return false;			
		}
		catch (CFileException* e)
		{
			return false;
		}
		catch (CException* e)
		{
			return false;
		}
	}

	return true;
}

//��ȡ�¼�
bool CMissionManager::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//����֪ͨ
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		CMissionItem * pMissionItem=m_MissionItemArray[i];
		pMissionItem->OnEventMissionRead(Command,pData,wDataSize);
	}

	return true;
}

//���õ�ַ
VOID CMissionManager::SetCustomServer(LPCTSTR pszCustomServer)
{
	//���õ�ַ
	m_MissionSocket.SetCustomServer(pszCustomServer);

	return;
}

//��������
bool CMissionManager::InsertMissionItem(CMissionItem * pMissionItem)
{
	//��������
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		if (m_MissionItemArray[i]==pMissionItem)
		{
			ASSERT(FALSE);
			return true;
		}
	}

	//��������
	pMissionItem->m_bActiveStatus=false;
	pMissionItem->m_pMissionManager=this;

	//��������
	m_MissionItemArray.Add(pMissionItem);

	return true;
}

//ɾ������
bool CMissionManager::DeleteMissionItem(CMissionItem * pMissionItem)
{
	//��ֹ����
	if (pMissionItem->m_bActiveStatus==true)
	{
		ConcludeMissionItem(pMissionItem,true);
	}

	//ɾ������
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		if (m_MissionItemArray[i]==pMissionItem)
		{
			//ɾ������
			m_MissionItemArray.RemoveAt(i);

			//��������
			pMissionItem->m_bActiveStatus=false;
			pMissionItem->m_pMissionManager=NULL;

			return true;
		}
	}

	//�������
	ASSERT(FALSE);

	return false;
}

//��������
bool CMissionManager::AvtiveMissionItem(CMissionItem * pMissionItem, bool bContinue)
{
	//Ч��״̬
	ASSERT(pMissionItem->m_pMissionManager==this);
	if (pMissionItem->m_pMissionManager!=this) return false;

	//�رմ���
	if (m_hWnd!=NULL) 
		DestroyWindow();

	//��������
	pMissionItem->m_bActiveStatus=true;

	//���Ӵ���
	switch (m_MissionSocket.GetSocketStatus())
	{
	case SOCKET_STATUS_IDLE:	//����״̬
		{
			//��������
			if (m_MissionSocket.PerformConnect(bContinue)==false)
			{
				//��������
				pMissionItem->m_bActiveStatus=false;

				return false;
			}
			else
			{
				if (m_hWnd==NULL)
					Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),GetDesktopWindow(),NULL,NULL);
				SetTimer(IDI_RETRY_LINK,2000,NULL);
			}

			break;
		}
	case SOCKET_STATUS_CONNECT:	//����״̬
		{
			//�¼�֪ͨ
			pMissionItem->OnEventMissionLink(0L);

			break;
		}
	}

	return true;
}

//��ֹ����
bool CMissionManager::ConcludeMissionItem(CMissionItem * pMissionItem, bool bDeferIntermit)
{
	//Ч��״̬
	ASSERT(pMissionItem->m_bActiveStatus==true);
	if (pMissionItem->m_bActiveStatus==false) 
		return false;

	//��������
	pMissionItem->m_bActiveStatus=false;

	//��������
	UINT uActiveCount=0;
	BYTE cbSocketStatus=m_MissionSocket.GetSocketStatus();

	//��������
	for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
	{
		try
		{
			CMissionItem * pMissionItem=m_MissionItemArray[i];
			if (pMissionItem->m_bActiveStatus==true) 
				uActiveCount++;
		}
		catch (CMemoryException* e)
		{
			return false;			
		}
		catch (CFileException* e)
		{
			return false;
		}
		catch (CException* e)
		{
			return false;
		}
	}

	//��ֹ����
	if ((uActiveCount==0)&&(cbSocketStatus!=SOCKET_STATUS_IDLE))
	{
		//��������
		CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

		//�ر��ж�
		if ((bDeferIntermit==true)&&(pParameterGlobal->m_wIntermitTime>0))
		{
			//��������
			if (m_hWnd==NULL)
			{
				CRect rcCreate(0,0,0,0);
				Create(NULL,NULL,WS_CHILD,rcCreate,GetDesktopWindow(),100);
			}

			//����ʱ��
			SetTimer(IDI_CLOSE_LINK,pParameterGlobal->m_wIntermitTime*1000L,NULL);
		}
		else
		{
			//�ر�����
			m_MissionSocket.PerformClose();
		}
	}

	return false;
}

//���ͺ���
bool CMissionManager::SendData(WORD wMainCmdID, WORD wSubCmdID)
{
	//��������
	m_MissionSocket.PerformSendData(wMainCmdID,wSubCmdID);

	return true;
}

//���ͺ���
bool CMissionManager::SendData(WORD wMainCmdID, WORD wSubCmdID, VOID * const pData, WORD wDataSize)
{
	//��������
	m_MissionSocket.PerformSendData(wMainCmdID,wSubCmdID,pData,wDataSize);

	return true;
}

//ʱ����Ϣ
VOID CMissionManager::OnTimer(UINT nIDEvent)
{
	//�ر�����
	if (nIDEvent==IDI_CLOSE_LINK)
	{
		//�رմ���
		DestroyWindow();

		//��ֹ����
		m_MissionSocket.PerformClose();

		return;
	}
	if (nIDEvent == IDI_RETRY_LINK)
	{
		switch( m_MissionSocket.GetSocketStatus())
		{
		case SOCKET_STATUS_IDLE:
			{
				for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
				{
					//��ȡ����
					CMissionItem * pMissionItem=m_MissionItemArray[i];

					//�¼�����
					if (pMissionItem->m_bActiveStatus==true)
					{
						ConcludeMissionItem(pMissionItem,true);
						//��������
						KillTimer(IDI_RETRY_LINK);
						AvtiveMissionItem(pMissionItem,true);

					}
				}
				break;
			}
		case SOCKET_STATUS_WAIT:
			{
				for (INT_PTR i=0;i<m_MissionItemArray.GetCount();i++)
				{
					//��ȡ����
					CMissionItem * pMissionItem=m_MissionItemArray[i];

					//�¼�����
					if (pMissionItem->m_bActiveStatus==true)
					{
						ConcludeMissionItem(pMissionItem,true);
						//��������
						KillTimer(IDI_RETRY_LINK);
						//��������
						AvtiveMissionItem(pMissionItem,true);

					}
				}
				int aa = 2;
				break;
			}
		case SOCKET_STATUS_CONNECT:
			{
				int aa = 2;
				break;
			}
		default:
			{
				int aa = 2;
				break;
			}
		}
	}

	__super::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////////////