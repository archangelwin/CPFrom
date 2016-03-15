#include "Stdafx.h"
#include "D3DSound.h"

CD3DSound *	CD3DSound::m_pD3DSound=NULL;
CD3DSound::CD3DSound()
{
	
}
CD3DSound::~CD3DSound()
{
	m_D3DSoundThread.ConcludeThread(INFINITE);
	CWHDataLocker DataLocker(m_CriticalSection);
	for (INT_PTR i=m_D3DSoundBufferBuffer.GetCount();i>0; i--)
	{
		CD3DSoundBuffer * pD3DSoundBuffer = m_D3DSoundBufferBuffer[i-1];
		pD3DSoundBuffer->Stop();
		m_pD3DSound->m_D3DSoundBufferBuffer.RemoveAt(i-1);
		delete pD3DSoundBuffer;
	}
	if( m_pIDirectSound != NULL )
	{
		m_pIDirectSound->Release();
	}
}

bool CD3DSound::CreateD3DSound(HWND hWnd)
{
	if( DirectSoundCreate(NULL,&m_pIDirectSound,NULL)!=DS_OK )
	{
		m_pIDirectSound = NULL;
		return FALSE;
	}
	if( m_pIDirectSound->SetCooperativeLevel(hWnd,DSSCL_NORMAL)!=DS_OK)
	{
		return FALSE;
	}
	m_D3DSoundThread.SetD3DSound(this);
	m_D3DSoundThread.StartThread();
	return true;
}
//停止声音
bool CD3DSound::StopSound()
{
	if(m_pIDirectSound == NULL)
		return false;
	CWHDataLocker DataLocker(m_CriticalSection);
	for (INT_PTR i=m_D3DSoundBufferBuffer.GetCount();i>0; i--)
	{
		CD3DSoundBuffer * pD3DSoundBuffer = m_D3DSoundBufferBuffer[i-1];
		pD3DSoundBuffer->Stop();
	}
	return true;
}
bool CD3DSound::Pause()
{
	if(m_pIDirectSound == NULL)
		return false;
	CWHDataLocker DataLocker(m_CriticalSection);
	for (INT_PTR i=0;i<m_D3DSoundBufferBuffer.GetCount();i++)
	{
		CD3DSoundBuffer * pD3DSoundBuffer = m_D3DSoundBufferBuffer[i];
		pD3DSoundBuffer->Pause();
	}
	return true;
}
//继续
bool CD3DSound::Run()
{
	if(m_pIDirectSound == NULL)
		return false;
	CWHDataLocker DataLocker(m_CriticalSection);
	for (INT_PTR i=0;i<m_D3DSoundBufferBuffer.GetCount();i++)
	{
		CD3DSoundBuffer * pD3DSoundBuffer = m_D3DSoundBufferBuffer[i];
		pD3DSoundBuffer->Run();
	}
	return true;
}
//播放声音
bool CD3DSound::PlaySound(LPCTSTR pszFileName, bool bRepetition)
{
	if(m_pIDirectSound == NULL)
		return false;
	CD3DSoundBuffer * pD3DSoundBuffer = new CD3DSoundBuffer;
	if(pD3DSoundBuffer != NULL)
	{
		if(pD3DSoundBuffer->LoadSoundResource(pszFileName))
		{
			pD3DSoundBuffer->PlaySound(0, bRepetition);
		}
		else
		{
			delete pD3DSoundBuffer;
			return false;
		}
	}
	DWORD bwBegin = GetTickCount();
	CWHDataLocker DataLocker(m_CriticalSection);
	CString str;
	str.Format("...................%d\r\n",GetTickCount() - bwBegin);
	OutputDebugString(str);
	m_D3DSoundBufferBuffer.Add(pD3DSoundBuffer);
	return true;
}
//播放声音
bool CD3DSound::PlaySound(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, bool bRepetition)
{
	if(m_pIDirectSound == NULL)
		return false;
	CD3DSoundBuffer * pD3DSoundBuffer = new CD3DSoundBuffer;
	if(pD3DSoundBuffer != NULL)
	{
		if(pD3DSoundBuffer->LoadSoundResource(hInstance, pszResource, pszTypeName))
		{
			pD3DSoundBuffer->PlaySound(0, bRepetition);
		}
		else
		{
			delete pD3DSoundBuffer;
			return false;
		}
	}
	DWORD bwBegin = GetTickCount();
	CWHDataLocker DataLocker(m_CriticalSection);
	CString str;
	str.Format("...................%d\r\n",GetTickCount() - bwBegin);
	OutputDebugString(str);
	m_D3DSoundBufferBuffer.Add(pD3DSoundBuffer);
	return true;
}
//获取对象
bool CD3DSound::CreateSoundBuffer(CD3DSoundBuffer * & pD3DSoundBuffer)
{
	//pD3DSoundBuffer = new CD3DSoundBuffer;
	return false;
}
//删除对象
bool CD3DSound::DeleteSoundBuffer(CD3DSoundBuffer * & pD3DSoundBuffer)
{
	return true;
}