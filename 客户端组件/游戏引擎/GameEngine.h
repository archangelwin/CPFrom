// GameEngine.h : GameEngine DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGameEngineApp
// �йش���ʵ�ֵ���Ϣ������� GameEngine.cpp
//

class CGameEngineApp : public CWinApp
{
public:
	CGameEngineApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
