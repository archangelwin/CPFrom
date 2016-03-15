#ifndef SKIN_CONTROL_HEAD_FILE
#define SKIN_CONTROL_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//包含文件

//平台文件
#include "..\..\全局定义\Platform.h"

//组件文件
#include "..\图像控件\WHImageHead.h"
#include "..\..\公共组件\服务核心\ServiceCoreHead.h"

//////////////////////////////////////////////////////////////////////////////////
//公共定义
//加载位图结构
struct tagImageLoadInfo
{
	//变量定义
	UINT								uResourceID;						//资源 ID
	CString								strFileName;						//文件名字
	HINSTANCE							hResourceDLL;						//资源句柄
	//LPCTSTR								pszResource;						//资源标识
	CString								strResType;							//资源类型

	//函数定义
	tagImageLoadInfo()
	{
		uResourceID=0;
		hResourceDLL=NULL;
	}
};

//编辑资源
struct tagSkinEditResource
{
	COLORREF						crFocusTX;							//字体颜色
	COLORREF						crFocusBK;							//背景颜色
	COLORREF						crNoFocusTX;						//字体颜色
	COLORREF						crNoFocusBK;						//背景颜色
	COLORREF						crDisFocusTX;						//字体颜色
	COLORREF						crDisFocusBK;						//背景颜色
	//COLORREF						crBoradNormal;						//边框颜色
	tagImageLoadInfo				m_ImageBottom;						//向下图片
	tagImageLoadInfo				m_ImageBottom1;						//向下图片
};

//按钮资源
struct tagSkinButtonResource
{
	COLORREF						crButtonText;						//字体颜色
	tagImageLoadInfo				LoadInfoButton;						//加载信息
};

//窗口资源
struct tagSkinDialogResource
{
	//配色信息
	COLORREF						crTitleText;						//标题颜色
	COLORREF						crBackGround;						//背景颜色
	COLORREF						crControlText;						//控制颜色
	COLORREF						crInsideBorder;						//边框颜色
	COLORREF						crBackFrame;						//背框颜色

	//加载信息
	tagImageLoadInfo				LoadInfoImageTL;					//加载信息
	tagImageLoadInfo				LoadInfoImageTM;					//加载信息
	tagImageLoadInfo				LoadInfoImageTR;					//加载信息

	//加载信息
	tagImageLoadInfo				LoadInfoButtonMin;					//加载信息
	tagImageLoadInfo				LoadInfoButtonMax;					//加载信息
	tagImageLoadInfo				LoadInfoButtonRes;					//加载信息
	tagImageLoadInfo				LoadInfoButtonClose;				//加载信息

	tagImageLoadInfo                Left;                                  
	tagImageLoadInfo                Right;
	tagImageLoadInfo                Bottom;
	tagImageLoadInfo                LeftL;
	tagImageLoadInfo                RightR;
};

//列表资源
struct tagSkinListCtrlResource
{
	//颜色信息
	COLORREF						crListTX;							//列表文字

	//资源信息
	tagImageLoadInfo				LoadInfoImageBack;					//加载信息
};

//拆分资源
struct tagSkinSplitterResource
{
	tagImageLoadInfo				LoadInfoVor;						//加载信息
	tagImageLoadInfo				LoadInfoHor;						//加载信息
};

//热点资源
struct tagSkinHyperLinkResource
{
	COLORREF						crBackColor;						//背景颜色
	COLORREF						crHoverText;						//字体颜色
	COLORREF						crNormalText;						//字体颜色
	COLORREF						crVisitedText;						//字体颜色
};

//进度条资源
struct tagProgressCtrlResource
{
	COLORREF						crText;								//字体颜色
	tagImageLoadInfo				LoadInfoBkg;						//加载信息
	tagImageLoadInfo				LoadInfoAct;						//加载信息
};

//界面资源
interface ISkinResource : public IUnknownEx
{
	//资源接口
public:
	//创建字体
	virtual bool __cdecl CreateDefaultFont(CFont & Font)=NULL;

	//资源接口
public:
	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinEditResource & SkinEditResource)=NULL;
	// 	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinDialogResource & SkinDialogResource)=NULL;
	// 	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinButtonResource & SkinButtonResource)=NULL;
	// 	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinSplitterResource & SkinSplitterResource)=NULL;
	// 	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinListCtrlResource & SkinListCtrlResource)=NULL;
	// 	//获取信息
	// 	virtual bool __cdecl GetResourceInfo(tagSkinHyperLinkResource & SkinHyperLinkResource)=NULL;
	// 	//获取信息
	virtual bool __cdecl GetResourceInfo(tagProgressCtrlResource & ProgressCtrlResource)=NULL;
};

//导出定义
#ifndef SKIN_CONTROL_CLASS
	#ifdef  SKIN_CONTROL_DLL
		#define SKIN_CONTROL_CLASS _declspec(dllexport)
	#else
		#define SKIN_CONTROL_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifndef _DEBUG
	#define SKIN_CONTROL_DLL_NAME	TEXT("SkinControl.dll")			//组件名字
#else
	#define SKIN_CONTROL_DLL_NAME	TEXT("SkinControlD.dll")		//组件名字
#endif

//////////////////////////////////////////////////////////////////////////////////
//导出文件

#ifndef SKIN_CONTROL_DLL
	#include "SkinEdit.h"
	#include "SkinMenu.h"
	#include "SkinDpi.h"
	#include "SkinDialog.h"
	#include "SkinButton.h"
	#include "SkinTabCtrl.h"
	#include "SkinSplitter.h"
	#include "SkinComboBox.h"
	#include "SkinEncircle.h"
	#include "SkinListCtrl.h"
	#include "SkinRichEdit.h"
	#include "SkinScrollBar.h"
    #include "SkinHyperLink.h"
    #include "SkinCheckBox.h"
	#include "SkinRenderManager.h"
    #include "SkinResourceManager.h"
    #include "GifButton.h"
    #include "GroupBox.h "
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif