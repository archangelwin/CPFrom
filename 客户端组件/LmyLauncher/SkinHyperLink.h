#ifndef SKIN_HYPER_LINK_HEAD_FILE
#define SKIN_HYPER_LINK_HEAD_FILE

#pragma once

#include "LmyLauncher.h"
//////////////////////////////////////////////////////////////////////////////////
//超连接类
class CSkinHyperLink : public CStatic
{
	//状态变量
protected:
	bool							m_bVisited;                     	//是否访问
   	bool							m_bHovering;						//盘旋标志

	//配置变量
protected:
    bool							m_bUnderLine;						//是否划线
	bool                            m_bBold;                            //粗体    
	bool							m_AutoRectify;						//自动调整
	bool                            m_bCursor;                        //是否加鼠标标志
	bool                            m_bCustomFont;
	int                             m_nCusFontHeight;
	int                             m_nCusFontWidth;
	LPCTSTR                         m_lpszFontName;

	//颜色定义
protected:
	COLORREF						m_crBackColor;						//背景颜色
	COLORREF						m_crHoverText;						//字体颜色
	COLORREF						m_crNormalText;						//字体颜色
	COLORREF						m_crVisitedText;					//字体颜色

	//函数定义
public:
	//构造函数
	CSkinHyperLink();
	//析构函数
	virtual ~CSkinHyperLink();

	//重载函数
protected:
	//控件绑定
	virtual VOID PreSubclassWindow();

	//查询函数
public:
	//获取访问
	bool IsVisiteded() { return m_bVisited; }
	//获取下划线
	bool IsUnderline() { return m_bUnderLine; }
	//获取调整
	bool IsAutoRectify() { return m_AutoRectify; }

	//设置函数
public:
	//设置访问
    VOID SetVisited(bool bVisited);
	//设下划线
    VOID SetUnderLine(bool bUnderLine);
	//粗体
    VOID SetBold(bool bBold);
	//
	VOID SetBCursor(bool bCursor);
	void SetCustomFont(bool bCustomFont,bool bCursor,bool bUnderLine,bool bBold,int nFontHeight=-12,int nFontWidth=0,LPCTSTR lpszFontName="宋体");	
	//设置调整
    VOID SetAutoRectify(bool bAutoRectify);

	//颜色设置
public:
	//背景颜色
	VOID SetBackGroundColor(COLORREF crBackColor);
	//字体颜色
	VOID SetHyperLinkTextColor(COLORREF crHoverText, COLORREF crNormalText, COLORREF crVisitedText);

	//辅助函数
protected:
	//调整位置
	VOID RectifyControl();
	//配置控件
	VOID Initialization();

	//消息函数
protected:
	//绘画消息
	VOID OnPaint();
	//单击控件
	VOID OnStnClicked();
	//建立消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//自定消息
protected:
	//标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);
	//鼠标离开
	LRESULT OnMouseLeaveMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif