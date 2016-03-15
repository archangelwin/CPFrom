#include "Stdafx.h"
#include "D3DMusic.h"

CD3DMusic* CD3DMusic::pObject = NULL;
CD3DMusic::CD3DMusic(void)
{
	//m_mapDXGraph = new CMapDXGraph();
	//m_mapKeyName = new CMapKeyName();
	m_idEvent = 0;
	m_iBackID = 0;
	m_iBackMaxID = 100;
}
CD3DMusic::~CD3DMusic(void)
{
	//delete m_mapDXGraph;
}
CString	 CD3DMusic::GetAppPath()
{
	CString strAppPath;
	return strAppPath;
}
BOOL  CD3DMusic::RegisterFilter(LPCTSTR  inFilterAx)
{
	return TRUE;
}
void  CD3DMusic::mapErase(UINT idEvent)
{

}
// 删除声音
void  CD3DMusic::mapErase()
{

}
// 单个播放回调
void  CALLBACK CD3DMusic::TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
}
// 背景播放回调
void  CALLBACK CD3DMusic::ListTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{

}
bool CD3DMusic::Start(LPCTSTR filename)
{
	mapDXGraph::iterator it = m_mapDXGraph.find(filename);
	CDXGraph *pGraph = NULL;
	if (it == m_mapDXGraph.end())
	{
		pGraph = new CDXGraph;
		pGraph->Create();
		pGraph->RenderFile(filename);
		m_mapDXGraph.insert(std::make_pair(filename,pGraph));
	}
	else
	{
		pGraph = it->second;
	}
	if(pGraph->Run())
		return true;

	return false;
}
bool CD3DMusic::Pause(LPCTSTR filename)
{
	mapDXGraph::iterator it = m_mapDXGraph.find(filename);
	if (it != m_mapDXGraph.end())
	{
		if(it->second->Pause())
			return true;
	}
	return false;
}

bool CD3DMusic::Run(LPCTSTR filename/*  = NULL*/)
{
	return true;	
}
bool CD3DMusic::Stop(LPCTSTR filename/*  = NULL*/)
{
	mapDXGraph::iterator it = m_mapDXGraph.find(filename);
	if (it != m_mapDXGraph.end())
	{
		if(it->second->Stop())
		{
			it->second->Release();
			delete it->second;
			m_mapDXGraph.erase(it);
			return true;
		}
	}
	return false;
}
void CD3DMusic::ControlVolume(int ibulk)
{
	mapDXGraph::iterator it = m_mapDXGraph.begin();
	for (it; it != m_mapDXGraph.end(); ++it)
	{
		it->second->SetAudioVolume(ibulk);
	}
}
void CD3DMusic::ListAdd(LPCTSTR filename)
{
	mapDXGraph::iterator it = m_mapGraphList.find(filename);
	CDXGraph *pGraph = NULL;
	if (it == m_mapDXGraph.end())
	{
		pGraph = new CDXGraph;
		pGraph->Create();
		pGraph->RenderFile(filename);
		m_mapDXGraph.insert(std::make_pair(filename,pGraph));
	}
}
void CD3DMusic::ListStart()
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->Run();
	}
}
void CD3DMusic::ListClear()
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->Stop();
		it->second->Release();
		delete it->second;
	}
	m_mapGraphList.clear();
}
void CD3DMusic::ListRun()
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->Run();
	}
}
void CD3DMusic::ListPause()
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->Pause();
	}
}
void CD3DMusic::ListStop()
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->SetAudioVolume(0);
	}
}
void CD3DMusic::ListVolume(int ibulk)
{
	mapDXGraph::iterator it = m_mapGraphList.begin();
	for (it; it != m_mapGraphList.end(); ++it)
	{
		it->second->SetAudioVolume(ibulk);
	}
}