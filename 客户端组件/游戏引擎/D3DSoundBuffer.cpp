#include "Stdafx.h"
#include "D3DSoundBuffer.h"
#include "D3DSound.h"

#define WAV_HDR_SIZE  44

CD3DSoundBuffer::CD3DSoundBuffer()
{
	m_pIDirectSoundBuffer = NULL;
}
CD3DSoundBuffer::~CD3DSoundBuffer()
{
	if (m_pIDirectSoundBuffer != NULL)
	{
		m_pIDirectSoundBuffer->Release();
	}
}

//ֹͣ����
bool CD3DSoundBuffer::Stop()
{
	if (m_pIDirectSoundBuffer != NULL)
	{
		m_pIDirectSoundBuffer->Stop();
	}
	return true;
}
//��ͣ
bool CD3DSoundBuffer::Pause()
{
	m_pIDirectSoundBuffer->SetVolume(DSBVOLUME_MIN);
	return true;
}
//����
bool CD3DSoundBuffer::Run()
{
	m_pIDirectSoundBuffer->SetVolume(DSBVOLUME_MAX);
	return true;
}
//��������
bool CD3DSoundBuffer::PlaySound(DWORD dwStartPosition, bool bRepetition)
{
	if (m_pIDirectSoundBuffer != NULL)
	{
		//loop=DSBPLAY_LOOPING;	
		m_pIDirectSoundBuffer->Play(0,0,bRepetition);
	}
	return true;
}

//��������
bool CD3DSoundBuffer::ResetResource()
{
	return true;
}
//��������
bool CD3DSoundBuffer::LoadSoundResource(LPCTSTR pszFileName)
{
	bool bRet = true;
	WAVEFORMATEX swfmt;                            						 // ���������ṹ
	MMCKINFO ckRiff;                               						 // RIFF�������Ϣ
	MMCKINFO ckInfo;                               						 // ���������Ϣ
	HMMIO hmmio;                                   						 // �򿪵Ķ�ý���ļ�
	DWORD dwSize;                                    					 // ʵ�����ݴ�С

	hmmio = mmioOpen((LPSTR)pszFileName,NULL,MMIO_ALLOCBUF|MMIO_READ);

	ckRiff.fccType = mmioFOURCC('W','A','V','E');						 // �趨�ļ�����
	mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);						 // ��������

	ckInfo.ckid = mmioFOURCC( 'f', 'm' , 't' , ' ');					 // �趨��������
	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // ��������

	mmioRead(hmmio,(HPSTR)&swfmt,sizeof(swfmt));

	mmioAscend(hmmio,&ckInfo,0);										 // ����������
	ckInfo.ckid = mmioFOURCC('d','a','t','a');							 // �趨��������

	MMRESULT hr =  mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // ��������

	dwSize = ckInfo.cksize;
                        
	DSBUFFERDESC desc;                          						 // ���������ṹ
	memset(&desc,0,sizeof(desc));										 // ��սṹ����
	desc.dwSize = sizeof(desc);                 						 // ���ýṹ��С
	desc.dwBufferBytes = dwSize;                  						 // �趨��������С
	desc.lpwfxFormat = &swfmt;                  						 // �趨��������ʽ
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | 
		DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;

	if(CD3DSound::GetInstance()->m_pIDirectSound->CreateSoundBuffer(&desc,&m_pIDirectSoundBuffer,NULL) != DS_OK)
	{
		bRet = false;
		goto next_;
	}

	LPVOID pAudio;
	DWORD bytesAudio;
	if(m_pIDirectSoundBuffer->Lock(0,dwSize, &pAudio ,&bytesAudio,NULL,NULL,NULL) != DS_OK)
	{
		bRet = false;
		goto next_;
	}

	mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);							 // ��ȡ���ļ�����

	if(m_pIDirectSoundBuffer->Unlock(pAudio,bytesAudio,NULL,NULL))
	{
		bRet = false;
		goto next_;
	}
next_:
	mmioClose(hmmio,0);
	return bRet;
}
//��������
bool CD3DSoundBuffer::LoadSoundResource(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName)
{
	bool bRet = true;
	//������Դ
	HRSRC hResource=FindResource(hInstance,pszResource,pszTypeName);
	if (hResource==NULL) return false;

	//������Դ
	HGLOBAL hGlobal=LoadResource(hInstance,hResource);
	if (hGlobal==NULL) return false;

	DWORD dwImageSize=SizeofResource(hInstance,hResource);

	WAVEFORMATEX swfmt;                            						 // ���������ṹ
	MMCKINFO ckRiff;                               						 // RIFF�������Ϣ
	MMCKINFO ckInfo;                               						 // ���������Ϣ
	MMIOINFO Info;
	HMMIO hmmio;                                   						 // �򿪵Ķ�ý���ļ�
	DWORD dwSize;                                    					 // ʵ�����ݴ�С

	ZeroMemory(&Info, sizeof(MMIOINFO));
	Info.fccIOProc = FOURCC_MEM;
	Info.pchBuffer = (HPSTR)hGlobal;
	Info.cchBuffer = dwImageSize;
	hmmio = mmioOpen(NULL, &Info,MMIO_ALLOCBUF|MMIO_READ);

	ckRiff.fccType = mmioFOURCC('W','A','V','E');						 // �趨�ļ�����
	MMRESULT hr = mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);						 // ��������

	ckInfo.ckid = mmioFOURCC( 'f', 'm' , 't' , ' ');					 // �趨��������
	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // ��������

	mmioRead(hmmio,(HPSTR)&swfmt,sizeof(swfmt));

	mmioAscend(hmmio,&ckInfo,0);										 // ����������
	ckInfo.ckid = mmioFOURCC('d','a','t','a');							 // �趨��������

	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // ��������

	dwSize = ckInfo.cksize;//1153708;

	DSBUFFERDESC desc;                          						 // ���������ṹ
	memset(&desc,0,sizeof(desc));										 // ��սṹ����
	desc.dwSize = sizeof(desc);                 						 // ���ýṹ��С
	desc.dwBufferBytes = dwSize;                  						 // �趨��������С
	desc.lpwfxFormat = &swfmt;                  						 // �趨��������ʽ
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | 
		DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;

	HRESULT hr1;
	if((hr1 = CD3DSound::GetInstance()->m_pIDirectSound->CreateSoundBuffer(&desc,&m_pIDirectSoundBuffer,NULL)) != DS_OK)
	{
		bRet = false;
		goto next_;
	}

	LPVOID pAudio;
	DWORD bytesAudio;
	if(m_pIDirectSoundBuffer->Lock(0,dwSize, &pAudio ,&bytesAudio,NULL,NULL,NULL) != DS_OK)
	{
		bRet = false;
		goto next_;
	}

	mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);							 // ��ȡ���ļ�����

	if(m_pIDirectSoundBuffer->Unlock(pAudio,bytesAudio,NULL,NULL))
	{
		bRet = false;
		goto next_;
	}
next_:
	mmioClose(hmmio,0);
	//������Դ
	UnlockResource(hGlobal);
	FreeResource(hGlobal);
	return bRet;
}

//��仺��
bool CD3DSoundBuffer::FillSoundBuffer(VOID * pSoundData, DWORD dwSoundSize)
{
	return true;
}
//��������
bool CD3DSoundBuffer::GetWaveDataInfo(LPVOID pDataBuffer, tagWaveDataInfo & WaveDataInfo)
{
	return true;
}

//��������
bool CD3DSoundBuffer::CreateSoundBuffer(tagWaveDataInfo & WaveDataInfo, DWORD dwFlags)
{
	return true;
}
//��������
bool CD3DSoundBuffer::CreateSoundBuffer(INT nChannels, INT nSecs, DWORD nSamplesPerSec, WORD wBitsPerSample, DWORD dwFlags)
{
	return true;
}