#pragma once

#include <map>
#include <vector>
#include "DirectShow/streams.h"
#include <initguid.h>
#include "GameEngineHead.h"
using namespace std;

const long GUID_MAX_COUNT = 1000;
#define WM_GRAPHNOTIFY  (WM_USER+20)

class CSupported
{
private:
	static GUID sSupportedGUIDs[GUID_MAX_COUNT];
	static long sGUIDCount;

public:
	CSupported();
	~CSupported();

	static BOOL IsGUIDSupported(GUID inGUID);
};


class CGraphBuilderCB : public CUnknown
	, public IAMGraphBuilderCallback
{
private:
	CSupported * mSupported;

public:
	CGraphBuilderCB();
	~CGraphBuilderCB();

	DECLARE_IUNKNOWN
	STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);

	// IAMGraphBuilderCallback
	STDMETHODIMP SelectedFilter(IMoniker *pMon);
	STDMETHODIMP CreatedFilter(IBaseFilter *pFil);
};

class CDXGraph
{
private:
	IGraphBuilder *     mGraph;
	IMediaControl *  mMediaControl;
	IMediaEventEx *  mEvent;
	IBasicVideo *  mBasicVideo;
	IBasicAudio *  mBasicAudio;
	IVideoWindow  *  mVideoWindow;
	IMediaSeeking *  mSeeking;

	DWORD    mObjectTableEntry;

public:
	CDXGraph();
	virtual ~CDXGraph();

public:
	virtual bool Create(void);
	virtual void Release(void);
	virtual bool Attach(IGraphBuilder * inGraphBuilder);

	IGraphBuilder * GetGraph(void); // Not outstanding reference count
	IMediaEventEx * GetEventHandle(void);

	bool ConnectFilters(IPin * inOutputPin, IPin * inInputPin, const AM_MEDIA_TYPE * inMediaType = 0);
	void DisconnectFilters(IPin * inOutputPin);

	bool SetDisplayWindow(HWND inWindow);
	bool SetNotifyWindow(HWND inWindow);
	bool ResizeVideoWindow(long inLeft, long inTop, long inWidth, long inHeight);
	void HandleEvent(WPARAM inWParam, LPARAM inLParam);

	bool Run(void);        // Control filter graph
	bool Stop(void);
	bool Pause(void);
	bool IsRunning(void);  // Filter graph status
	bool IsStopped(void);
	bool IsPaused(void);

	bool SetFullScreen(BOOL inEnabled);
	bool GetFullScreen(void);

	// IMediaSeeking
	bool GetCurrentPosition(double * outPosition);
	bool GetStopPosition(double * outPosition);
	bool SetCurrentPosition(double inPosition);
	bool SetStartStopPosition(double inStart, double inStop);
	bool GetDuration(double * outDuration);
	bool SetPlaybackRate(double inRate);

	// Attention: range from -10000 to 0, and 0 is FULL_VOLUME.
	bool SetAudioVolume(long inVolume);
	long GetAudioVolume(void);
	// Attention: range from -10000(left) to 10000(right), and 0 is both.
	bool SetAudioBalance(long inBalance);
	long GetAudioBalance(void);

	bool RenderFile(const char * inFile);
	bool SnapshotBitmap(const char * outFile);

private:
	void AddToObjectTable(void) ;
	void RemoveFromObjectTable(void);

	bool QueryInterfaces(void);
};