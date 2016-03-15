#include "Stdafx.h"
#include "D3DSoundThread.h"
#include "D3DSound.h"

CD3DSoundThread::CD3DSoundThread()
{

}
CD3DSoundThread::~CD3DSoundThread()
{

}
//运行事件
bool CD3DSoundThread::OnEventThreadRun()
{
	for (INT_PTR i=m_pD3DSound->m_D3DSoundBufferBuffer.GetCount();i>0; i--)
	{
		CD3DSoundBuffer * pD3DSoundBuffer = m_pD3DSound->m_D3DSoundBufferBuffer[i-1];
		DWORD dwStatus=0;
		if((pD3DSoundBuffer->m_pIDirectSoundBuffer->GetStatus(&dwStatus))!=DS_OK ) 
				break;
		if( (dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING  ) 
		{
			pD3DSoundBuffer->Stop();
			CWHDataLocker DataLocker(m_pD3DSound->m_CriticalSection);
			m_pD3DSound->m_D3DSoundBufferBuffer.RemoveAt(i-1);
			delete pD3DSoundBuffer;
		}
		Sleep(2);
	}
	Sleep(1);
	return true;
}