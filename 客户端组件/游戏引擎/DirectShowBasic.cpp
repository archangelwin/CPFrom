// CDXGraph.cpp
//



#include "stdafx.h"
//#include <streams.h>
#include "DirectShowBasic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////CSupported////////////////////////
// {38be3000-dbf4-11d0-860e-00a024cfef6d}    
DEFINE_GUID(CLSID_MicrosoftMp3Decoder,    
			0x38be3000, 0xdbf4, 0x11d0, 0x86, 0x0e, 0x00, 0xa0, 0x24, 0xcf, 0xef, 0x6d);   

// {d51bd5a1-7548-11cf-a520-0080c77ef58a}    
DEFINE_GUID(CLSID_MicrosoftWaveParser,    
			0xd51bd5a1, 0x7548, 0x11cf, 0xa5, 0x20, 0x00, 0x80, 0xc7, 0x7e, 0xf5, 0x8a);   

// {280a3020-86cf-11d1-abe6-00a0c905f375}    
DEFINE_GUID(CLSID_MicrosoftAC3Parser,    
			0x280a3020, 0x86cf, 0x11d1, 0xab, 0xe6, 0x00, 0xa0, 0xc9, 0x05, 0xf3, 0x75);   

// {94297043-bd82-4dfd-b0de-8177739c6d20}    
DEFINE_GUID(CLSID_MicrosoftDMOWrapper,    
			0x94297043, 0xbd82, 0x4dfd, 0xb0, 0xde, 0x81, 0x77, 0x73, 0x9c, 0x6d, 0x20);   

GUID CSupported::sSupportedGUIDs[];   
long CSupported::sGUIDCount = 0;   
/////////////////////////////////////////////////////////////////    
CSupported::CSupported()   
{   
	long i = 0;   
	// Video Renderer and Audio Renderer    
	sSupportedGUIDs[i++] = CLSID_VideoRenderer;   
	sSupportedGUIDs[i++] = CLSID_DSoundRender;   
	// Microsoft AVI codec and miscellaneous utilities    
	sSupportedGUIDs[i++] = CLSID_AviSplitter;   
	sSupportedGUIDs[i++] = CLSID_AVIDec;   
	sSupportedGUIDs[i++] = CLSID_MicrosoftWaveParser;   
	sSupportedGUIDs[i++] = CLSID_MicrosoftAC3Parser;   
	// DV filters    
	sSupportedGUIDs[i++] = CLSID_DVSplitter;   
	sSupportedGUIDs[i++] = CLSID_DVVideoCodec;      
	// Microsoft Mpeg1 codec    
	sSupportedGUIDs[i++] = CLSID_MPEG1Splitter;   
	sSupportedGUIDs[i++] = CLSID_CMpegAudioCodec;   
	sSupportedGUIDs[i++] = CLSID_CMpegVideoCodec;   
	sSupportedGUIDs[i++] = CLSID_MicrosoftMp3Decoder;   
	// Microsoft Mpeg2 codec
	//linjs delete
	//sSupportedGUIDs[i++] = CLSID_MMSPLITTER;   
	//sSupportedGUIDs[i++] = CLSID_MPEG2Demultiplexer;   

	// This way, we support all DMO codecs. Maybe too arbitrary!    
	sSupportedGUIDs[i++] = CLSID_MicrosoftDMOWrapper;   

	sGUIDCount = i; // total count of CSupported GUIDs    
}   

CSupported::~CSupported()   
{   
}   

BOOL CSupported::IsGUIDSupported(GUID inGUID)   
{   
	for (long i = 0; i < sGUIDCount; i++)   
	{   
		if (sSupportedGUIDs[i] == inGUID)   
		{   
			return TRUE;   
		}   
	}   
	return FALSE;   
}  
////////////////////////////////////////////////////CSupported////////////////////////// 

////////////////////////////////////////////////////CGraphBuilderCB/////////////////////
CGraphBuilderCB::CGraphBuilderCB() :   
CUnknown(NAME("Callbacker"), NULL)   
{   
	mSupported = new CSupported();   
}   

CGraphBuilderCB::~CGraphBuilderCB()   
{   
	if (mSupported)   
	{   
		delete mSupported;   
		mSupported = NULL;   
	}   
}   

STDMETHODIMP CGraphBuilderCB::NonDelegatingQueryInterface(REFIID riid, void** ppv)   
{   
	if (riid == __uuidof(IAMGraphBuilderCallback))    
	{   
		return GetInterface((IAMGraphBuilderCallback*)this, ppv);   
	}   
	return CUnknown::NonDelegatingQueryInterface(riid,ppv);   
}   

//////////////////////////////////////////////////////////////////////////////    
//    
// IAMGraphBuilderCallback-overriden functions    
//////////////////////////////////////////////////////////////////////////////    
//----------------------------------------------------------------------------    
// SelectedFilter    
//    
//----------------------------------------------------------------------------    
STDMETHODIMP CGraphBuilderCB::SelectedFilter(IMoniker *pMon)   
{   
	if (!pMon)   
	{   
		return E_POINTER;   
	}   

	IBindCtx * pBCtx = NULL;   
	HRESULT hr = CreateBindCtx(0, (LPBC*)&pBCtx );   
	if (!pBCtx || FAILED(hr))   
	{   
		return E_UNEXPECTED;   
	}   

	IBaseFilter * pBf = NULL;   
	hr = pMon->BindToObject(pBCtx, NULL, __uuidof(IBaseFilter), (void**)&pBf);   
	pBCtx->Release();   
	if (FAILED(hr) || !pBf)   
	{   
		return E_UNEXPECTED;   
	}   

	// Get filter's CLSID    
	IPersist * pPersist = NULL;   
	hr = pBf->QueryInterface( __uuidof(IPersist), (void**)&pPersist);   
	pBf->Release();   
	if (SUCCEEDED(hr))   
	{   
		CLSID  clsid = GUID_NULL;   
		pPersist->GetClassID(&clsid);   
		pPersist->Release();   
		if (CSupported::IsGUIDSupported(clsid))   
		{   
			return S_OK;   
		}   
	}   
	return E_FAIL;   
}   

//----------------------------------------------------------------------------    
// CreatedFilter    
//    
//----------------------------------------------------------------------------    
STDMETHODIMP CGraphBuilderCB::CreatedFilter(IBaseFilter *pBf)   
{   
	return S_OK;   
}  
////////////////////////////////////////////////////CGraphBuilderCB/////////////////////

////////////////////////////////////////////////////////////////////////////////////////
CDXGraph::CDXGraph()
{
	mGraph        = NULL;
	mMediaControl = NULL;
	mEvent        = NULL;
	mBasicVideo   = NULL;
	mBasicAudio   = NULL;
	mVideoWindow  = NULL;
	mSeeking      = NULL;

	mObjectTableEntry = 0;
}

CDXGraph::~CDXGraph()
{
	Release();
}

bool CDXGraph::Create(void)
{
	if (!mGraph)
	{
		if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&mGraph)))
		{
			AddToObjectTable();

			return QueryInterfaces();
		}
		mGraph = 0;
	}
	return false;
}

bool CDXGraph::QueryInterfaces(void)
{
	if (mGraph)
	{
		HRESULT hr = NOERROR;
		hr |= mGraph->QueryInterface(IID_IMediaControl, (void **)&mMediaControl);
		hr |= mGraph->QueryInterface(IID_IMediaEventEx, (void **)&mEvent);
		hr |= mGraph->QueryInterface(IID_IBasicVideo, (void **)&mBasicVideo);
		hr |= mGraph->QueryInterface(IID_IBasicAudio, (void **)&mBasicAudio);
		hr |= mGraph->QueryInterface(IID_IVideoWindow, (void **)&mVideoWindow);
		hr |= mGraph->QueryInterface(IID_IMediaSeeking, (void **)&mSeeking);
		if (mSeeking)
		{
			mSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
		}
		return SUCCEEDED(hr);
	}
	return false;
}

void CDXGraph::Release(void)
{
	if (mSeeking)
	{
		mSeeking->Release();
		mSeeking = NULL;
	}
	if (mMediaControl)
	{
		mMediaControl->Release();
		mMediaControl = NULL;
	}
	if (mEvent)
	{
		mEvent->Release();
		mEvent = NULL;
	}
	if (mBasicVideo)
	{
		mBasicVideo->Release();
		mBasicVideo = NULL;
	}
	if (mBasicAudio)
	{
		mBasicAudio->Release();
		mBasicAudio = NULL;
	}
	if (mVideoWindow)
	{
		mVideoWindow->put_Visible(OAFALSE);
		mVideoWindow->put_MessageDrain((OAHWND)NULL);
		mVideoWindow->put_Owner(OAHWND(0));
		mVideoWindow->Release();
		mVideoWindow = NULL;
	}
	RemoveFromObjectTable();
	if (mGraph)
	{
		mGraph->Release();
		mGraph = NULL;
	}
}

bool CDXGraph::Attach(IGraphBuilder * inGraphBuilder)
{
	Release();

	if (inGraphBuilder)
	{
		inGraphBuilder->AddRef();
		mGraph = inGraphBuilder;

		AddToObjectTable();
		return QueryInterfaces();
	}
	return true;
}

IGraphBuilder * CDXGraph::GetGraph(void)
{
	return mGraph;
}

IMediaEventEx * CDXGraph::GetEventHandle(void)
{
	return mEvent;
}

// Connect filter from the upstream output pin to the downstream input pin
bool CDXGraph::ConnectFilters(IPin * inOutputPin, IPin * inInputPin,
							  const AM_MEDIA_TYPE * inMediaType)
{
	if (mGraph && inOutputPin && inInputPin)
	{
		HRESULT hr = mGraph->ConnectDirect(inOutputPin, inInputPin, inMediaType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

void CDXGraph::DisconnectFilters(IPin * inOutputPin)
{
	if (mGraph && inOutputPin)
	{
		HRESULT hr = mGraph->Disconnect(inOutputPin);
	}
}

bool CDXGraph::SetDisplayWindow(HWND inWindow)
{ 
	if (mVideoWindow)
	{
		// long lVisible;
		// mVideoWindow->get_Visible(&lVisible);
		// Hide the video window first
		mVideoWindow->put_Visible(OAFALSE);
		mVideoWindow->put_Owner((OAHWND)inWindow);

		RECT windowRect;
		::GetClientRect(inWindow, &windowRect);
		mVideoWindow->put_Left(0);
		mVideoWindow->put_Top(0);
		mVideoWindow->put_Width(windowRect.right - windowRect.left);
		mVideoWindow->put_Height(windowRect.bottom - windowRect.top);
		mVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

		mVideoWindow->put_MessageDrain((OAHWND) inWindow);
		// Restore the video window
		if (inWindow != NULL)
		{
			// mVideoWindow->put_Visible(lVisible);
			mVideoWindow->put_Visible(OATRUE);
		}
		else
		{
			mVideoWindow->put_Visible(OAFALSE);
		}
		return true;
	}
	return false;
}

bool CDXGraph::ResizeVideoWindow(long inLeft, long inTop, long inWidth, long inHeight)
{
	if (mVideoWindow)
	{
		long lVisible = OATRUE;
		mVideoWindow->get_Visible(&lVisible);
		// Hide the video window first
		mVideoWindow->put_Visible(OAFALSE);

		mVideoWindow->put_Left(inLeft);
		mVideoWindow->put_Top(inTop);
		mVideoWindow->put_Width(inWidth);
		mVideoWindow->put_Height(inHeight);

		// Restore the video window
		mVideoWindow->put_Visible(lVisible);
		return true;
	}
	return false;
}

bool CDXGraph::SetNotifyWindow(HWND inWindow)
{
	if (mEvent)
	{
		mEvent->SetNotifyWindow((OAHWND)inWindow, WM_GRAPHNOTIFY, 0);
		return true;
	}
	return false;
}

void CDXGraph::HandleEvent(WPARAM inWParam, LPARAM inLParam)
{
	if (mEvent)
	{
		LONG eventCode = 0, eventParam1 = 0, eventParam2 = 0;
		while (SUCCEEDED(mEvent->GetEvent(&eventCode, &eventParam1, &eventParam2, 0)))
		{
			mEvent->FreeEventParams(eventCode, eventParam1, eventParam2);
			switch (eventCode)
			{
			case EC_COMPLETE:
				break;

			case EC_USERABORT:
			case EC_ERRORABORT:
				break;

			default:
				break;
			}
		}
	}
}

bool CDXGraph::Run(void)
{
	if (mGraph && mMediaControl)
	{
		if (!IsRunning())
		{
			if (SUCCEEDED(mMediaControl->Run()))
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool CDXGraph::Stop(void)
{
	if (mGraph && mMediaControl)
	{
		if (!IsStopped())
		{ 
			if (SUCCEEDED(mMediaControl->Stop()))
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool CDXGraph::Pause(void)
{
	if (mGraph && mMediaControl)
	{
		if (!IsPaused())
		{ 
			if (SUCCEEDED(mMediaControl->Pause()))
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool CDXGraph::IsRunning(void)
{
	if (mGraph && mMediaControl)
	{
		OAFilterState state = State_Stopped;
		if (SUCCEEDED(mMediaControl->GetState(10, &state)))
		{
			return state == State_Running;
		}
	}
	return false;
}

bool CDXGraph::IsStopped(void)
{
	if (mGraph && mMediaControl)
	{
		OAFilterState state = State_Stopped;
		if (SUCCEEDED(mMediaControl->GetState(10, &state)))
		{
			return state == State_Stopped;
		}
	}
	return false;
}

bool CDXGraph::IsPaused(void)
{
	if (mGraph && mMediaControl)
	{
		OAFilterState state = State_Stopped;
		if (SUCCEEDED(mMediaControl->GetState(10, &state)))
		{
			return state == State_Paused;
		}
	}
	return false;
}

bool CDXGraph::SetFullScreen(BOOL inEnabled)
{
	if (mVideoWindow)
	{
		HRESULT hr = mVideoWindow->put_FullScreenMode(inEnabled ? OATRUE : OAFALSE);
		return SUCCEEDED(hr);
	}
	return false;
}

bool CDXGraph::GetFullScreen(void)
{
	if (mVideoWindow)
	{
		long  fullScreenMode = OAFALSE;
		mVideoWindow->get_FullScreenMode(&fullScreenMode);
		return (fullScreenMode == OATRUE);
	}
	return false;
}

// IMediaSeeking features
bool CDXGraph::GetCurrentPosition(double * outPosition)
{
	if (mSeeking)
	{
		__int64 position = 0;
		if (SUCCEEDED(mSeeking->GetCurrentPosition(&position)))
		{
			*outPosition = ((double)position) / 10000000.;
			return true;
		}
	}
	return false;
}

bool CDXGraph::GetStopPosition(double * outPosition)
{
	if (mSeeking)
	{
		__int64 position = 0;
		if (SUCCEEDED(mSeeking->GetStopPosition(&position)))
		{
			*outPosition = ((double)position) / 10000000.;
			return true;
		}
	}
	return false;
}

bool CDXGraph::SetCurrentPosition(double inPosition)
{
	if (mSeeking)
	{
		__int64 one = 10000000;
		__int64 position = (__int64)(one * inPosition);
		HRESULT hr = mSeeking->SetPositions(&position, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame,
			0, AM_SEEKING_NoPositioning);
		return SUCCEEDED(hr);
	}
	return false;
}

bool CDXGraph::SetStartStopPosition(double inStart, double inStop)
{
	if (mSeeking)
	{
		__int64 one = 10000000;
		__int64 startPos = (__int64)(one * inStart);
		__int64 stopPos  = (__int64)(one * inStop);
		HRESULT hr = mSeeking->SetPositions(&startPos, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame,
			&stopPos, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame);
		return SUCCEEDED(hr);
	}
	return false;
}

bool CDXGraph::GetDuration(double * outDuration)
{
	if (mSeeking)
	{
		__int64 length = 0;
		if (SUCCEEDED(mSeeking->GetDuration(&length)))
		{
			*outDuration = ((double)length) / 10000000.;
			return true;
		}
	}
	return false;
}

bool CDXGraph::SetPlaybackRate(double inRate)
{
	if (mSeeking)
	{
		if (SUCCEEDED(mSeeking->SetRate(inRate)))
		{
			return true;
		}
	}
	return false;
}

// Attention: range from -10000 to 0, and 0 is FULL_VOLUME.
bool CDXGraph::SetAudioVolume(long inVolume)
{
	if (mBasicAudio)
	{
		HRESULT hr = mBasicAudio->put_Volume(inVolume);
		return SUCCEEDED(hr);
	}
	return false;
}

long CDXGraph::GetAudioVolume(void)
{
	long volume = 0;
	if (mBasicAudio)
	{
		mBasicAudio->get_Volume(&volume);
	}
	return volume;
}

// Attention: range from -10000(left) to 10000(right), and 0 is both.
bool CDXGraph::SetAudioBalance(long inBalance)
{
	if (mBasicAudio)
	{
		HRESULT hr = mBasicAudio->put_Balance(inBalance);
		return SUCCEEDED(hr);
	}
	return false;
}

long CDXGraph::GetAudioBalance(void)
{
	long balance = 0;
	if (mBasicAudio)
	{
		mBasicAudio->get_Balance(&balance);
	}
	return balance;
}

bool CDXGraph::RenderFile(const char * inFile)
{
	if (mGraph)
	{
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFile, -1, szFilePath, MAX_PATH);
		if (SUCCEEDED(mGraph->RenderFile(szFilePath, NULL)))
		{
			return true;
		}
	}
	return false;
}

bool CDXGraph::SnapshotBitmap(const char * outFile)
{
	if (mBasicVideo)
	{
		long bitmapSize = 0;
		if (SUCCEEDED(mBasicVideo->GetCurrentImage(&bitmapSize, 0)))
		{
			bool pass = false;
			unsigned char * buffer = new unsigned char[bitmapSize];
			if (SUCCEEDED(mBasicVideo->GetCurrentImage(&bitmapSize, (long *)buffer)))
			{
				BITMAPFILEHEADER hdr;
				LPBITMAPINFOHEADER lpbi;

				lpbi = (LPBITMAPINFOHEADER)buffer;

				int nColors = 1 << lpbi->biBitCount;
				if (nColors > 256)
					nColors = 0;

				hdr.bfType  = ((WORD) ('M' << 8) | 'B'); //always is "BM"
				hdr.bfSize  = bitmapSize + sizeof( hdr );
				hdr.bfReserved1  = 0;
				hdr.bfReserved2  = 0;
				hdr.bfOffBits  = (DWORD) (sizeof(BITMAPFILEHEADER) + lpbi->biSize +
					nColors * sizeof(RGBQUAD));

				CFile bitmapFile(outFile, CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary);
				bitmapFile.Write(&hdr, sizeof(BITMAPFILEHEADER));
				bitmapFile.Write(buffer, bitmapSize);
				bitmapFile.Close();
				pass = true;
			}
			delete [] buffer;
			return pass;
		}
	}
	return false;
}



//////////////////////// For GraphEdit Dubug purpose /////////////////////////////
void CDXGraph::AddToObjectTable(void)
{
	IMoniker * pMoniker = 0;
	IRunningObjectTable * objectTable = 0;
	if (SUCCEEDED(GetRunningObjectTable(0, &objectTable)))
	{
		WCHAR wsz[256];
		swprintf(wsz, L"FilterGraph %08p pid %08x", (DWORD_PTR)mGraph, GetCurrentProcessId());
		HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
		if (SUCCEEDED(hr))
		{
			hr = objectTable->Register(0, mGraph, pMoniker, &mObjectTableEntry);
			pMoniker->Release();
		}
		objectTable->Release();
	}
}

void CDXGraph::RemoveFromObjectTable(void)
{
	IRunningObjectTable * objectTable = 0;
	if (SUCCEEDED(GetRunningObjectTable(0, &objectTable)))
	{
		objectTable->Revoke(mObjectTableEntry);
		objectTable->Release();
		mObjectTableEntry = 0;
	}
}

