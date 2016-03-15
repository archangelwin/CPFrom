#pragma once


// CSkinLayered
#include "PngImage.h"

class CSkinLayered : public CWnd
{
	//变量定义
protected:
	CWnd *							m_pWndControl;						//控件窗口

	//函数定义
public:
	//构造函数
	CSkinLayered();
	//析构函数
	virtual ~CSkinLayered();

	//功能函数
public:
	//创建窗口
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//设置区域
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//设置区域
	VOID InitLayeredArea(CPngImageSB & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//消息映射
protected:
	//关闭消息
	VOID OnClose();
	//焦点消息
	VOID OnSetFocus(CWnd * pOldWnd);

	//静态函数
protected:
	//枚举函数
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


