#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"
// CDlgMobileBind 对话框

class CDlgMobileBind : public CSkinDialog
{
public:
	CDlgMobileBind();   // 标准构造函数
	virtual ~CDlgMobileBind();

protected:
	CPlatformPublicize				m_PlatformPublicize;				//浏览控件


protected:
	//重画消息
	VOID OnPaint();
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
