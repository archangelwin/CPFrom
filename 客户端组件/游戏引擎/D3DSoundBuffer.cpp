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

//停止播放
bool CD3DSoundBuffer::Stop()
{
	if (m_pIDirectSoundBuffer != NULL)
	{
		m_pIDirectSoundBuffer->Stop();
	}
	return true;
}
//暂停
bool CD3DSoundBuffer::Pause()
{
	m_pIDirectSoundBuffer->SetVolume(DSBVOLUME_MIN);
	return true;
}
//继续
bool CD3DSoundBuffer::Run()
{
	m_pIDirectSoundBuffer->SetVolume(DSBVOLUME_MAX);
	return true;
}
//播放声音
bool CD3DSoundBuffer::PlaySound(DWORD dwStartPosition, bool bRepetition)
{
	if (m_pIDirectSoundBuffer != NULL)
	{
		//loop=DSBPLAY_LOOPING;	
		m_pIDirectSoundBuffer->Play(0,0,bRepetition);
	}
	return true;
}

//重置声音
bool CD3DSoundBuffer::ResetResource()
{
	return true;
}
//加载声音
bool CD3DSoundBuffer::LoadSoundResource(LPCTSTR pszFileName)
{
	bool bRet = true;
	WAVEFORMATEX swfmt;                            						 // 声明声音结构
	MMCKINFO ckRiff;                               						 // RIFF区块的信息
	MMCKINFO ckInfo;                               						 // 子区块的信息
	HMMIO hmmio;                                   						 // 打开的多媒体文件
	DWORD dwSize;                                    					 // 实际数据大小

	hmmio = mmioOpen((LPSTR)pszFileName,NULL,MMIO_ALLOCBUF|MMIO_READ);

	ckRiff.fccType = mmioFOURCC('W','A','V','E');						 // 设定文件类型
	mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);						 // 查找类型

	ckInfo.ckid = mmioFOURCC( 'f', 'm' , 't' , ' ');					 // 设定区块类型
	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // 查找区块

	mmioRead(hmmio,(HPSTR)&swfmt,sizeof(swfmt));

	mmioAscend(hmmio,&ckInfo,0);										 // 跳出子区块
	ckInfo.ckid = mmioFOURCC('d','a','t','a');							 // 设定区块类型

	MMRESULT hr =  mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // 查找区块

	dwSize = ckInfo.cksize;
                        
	DSBUFFERDESC desc;                          						 // 声明描述结构
	memset(&desc,0,sizeof(desc));										 // 清空结构内容
	desc.dwSize = sizeof(desc);                 						 // 配置结构大小
	desc.dwBufferBytes = dwSize;                  						 // 设定缓冲区大小
	desc.lpwfxFormat = &swfmt;                  						 // 设定缓冲区格式
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

	mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);							 // 读取音文件数据

	if(m_pIDirectSoundBuffer->Unlock(pAudio,bytesAudio,NULL,NULL))
	{
		bRet = false;
		goto next_;
	}
next_:
	mmioClose(hmmio,0);
	return bRet;
}
//加载声音
bool CD3DSoundBuffer::LoadSoundResource(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName)
{
	bool bRet = true;
	//加载资源
	HRSRC hResource=FindResource(hInstance,pszResource,pszTypeName);
	if (hResource==NULL) return false;

	//锁定资源
	HGLOBAL hGlobal=LoadResource(hInstance,hResource);
	if (hGlobal==NULL) return false;

	DWORD dwImageSize=SizeofResource(hInstance,hResource);

	WAVEFORMATEX swfmt;                            						 // 声明声音结构
	MMCKINFO ckRiff;                               						 // RIFF区块的信息
	MMCKINFO ckInfo;                               						 // 子区块的信息
	MMIOINFO Info;
	HMMIO hmmio;                                   						 // 打开的多媒体文件
	DWORD dwSize;                                    					 // 实际数据大小

	ZeroMemory(&Info, sizeof(MMIOINFO));
	Info.fccIOProc = FOURCC_MEM;
	Info.pchBuffer = (HPSTR)hGlobal;
	Info.cchBuffer = dwImageSize;
	hmmio = mmioOpen(NULL, &Info,MMIO_ALLOCBUF|MMIO_READ);

	ckRiff.fccType = mmioFOURCC('W','A','V','E');						 // 设定文件类型
	MMRESULT hr = mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);						 // 查找类型

	ckInfo.ckid = mmioFOURCC( 'f', 'm' , 't' , ' ');					 // 设定区块类型
	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // 查找区块

	mmioRead(hmmio,(HPSTR)&swfmt,sizeof(swfmt));

	mmioAscend(hmmio,&ckInfo,0);										 // 跳出子区块
	ckInfo.ckid = mmioFOURCC('d','a','t','a');							 // 设定区块类型

	mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);					 // 查找区块

	dwSize = ckInfo.cksize;//1153708;

	DSBUFFERDESC desc;                          						 // 声明描述结构
	memset(&desc,0,sizeof(desc));										 // 清空结构内容
	desc.dwSize = sizeof(desc);                 						 // 配置结构大小
	desc.dwBufferBytes = dwSize;                  						 // 设定缓冲区大小
	desc.lpwfxFormat = &swfmt;                  						 // 设定缓冲区格式
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

	mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);							 // 读取音文件数据

	if(m_pIDirectSoundBuffer->Unlock(pAudio,bytesAudio,NULL,NULL))
	{
		bRet = false;
		goto next_;
	}
next_:
	mmioClose(hmmio,0);
	//清理资源
	UnlockResource(hGlobal);
	FreeResource(hGlobal);
	return bRet;
}

//填充缓冲
bool CD3DSoundBuffer::FillSoundBuffer(VOID * pSoundData, DWORD dwSoundSize)
{
	return true;
}
//声音属性
bool CD3DSoundBuffer::GetWaveDataInfo(LPVOID pDataBuffer, tagWaveDataInfo & WaveDataInfo)
{
	return true;
}

//创建缓冲
bool CD3DSoundBuffer::CreateSoundBuffer(tagWaveDataInfo & WaveDataInfo, DWORD dwFlags)
{
	return true;
}
//创建缓冲
bool CD3DSoundBuffer::CreateSoundBuffer(INT nChannels, INT nSecs, DWORD nSamplesPerSec, WORD wBitsPerSample, DWORD dwFlags)
{
	return true;
}