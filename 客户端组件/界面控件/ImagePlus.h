#ifndef SKIN_IMAGE_PLUS_HEAD_FILE
#define SKIN_IMAGE_PLUS_HEAD_FILE

#pragma once

#include "SkinImage.h"
#include "SkinControlHead.h"

//////////////////////////////////////////////////////////////////////////


//位图对象类
class SKIN_CONTROL_CLASS CImagePlus : public CImage, public IGDIResource
{
	friend class CImagePlusHandle;

	//内部变量
private:
	int									m_nRefCount;						//引用计数
	bool								m_bLoadAlways;						//是否常在
	tagImageLoadInfo					m_LoadInfo;							//加载参数
	COLORREF							m_crTrans;							//透明颜色

	//函数定义
public:
	//构造函数
	CImagePlus(void);
	//析构函数
	virtual ~CImagePlus(void);

	//接口函数
protected:
	//增加引用
	virtual int LockResource();
	//减少引用
	virtual int UnLockResource();
	//获取引用计数
	virtual int GetReferenceCount() { return m_nRefCount; }

	//功能函数
public:
	//是否设置加载信息
	bool IsSetLoadInfo();
	//清除加载参数
	bool RemoveLoadInfo();
	//获取加载参数
	bool GetLoadInfo(tagImageLoadInfo & LoadInfo);
	//设置参数
	bool SetLoadInfo(const tagImageLoadInfo & LoadInfo, bool bLoadAlways=false);
	//设置加载参数
	bool SetLoadInfo(LPCTSTR pszFileName, bool bLoadAlways=false);
	//设置加载参数
	bool SetLoadInfo(UINT uResourceID, HINSTANCE hResourceDLL=NULL, bool bLoadAlways=false, LPCTSTR pszResType=_T("BMP"));
	//加载图片
	BOOL LoadImageFromResource(HINSTANCE hInstance, UINT uResourceID, LPCTSTR pszResourceType);
	BOOL LoadImageFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszResourceType);
	//透明处理
	BOOL AlphaChannelHandle();
	//绘画函数
	BOOL DrawImage( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight,
		int xSrc, int ySrc, int nSrcWidth, int nSrcHeight );
	BOOL DrawImage(HDC hDestDC, int xDest, int yDest);
	BOOL DrawImage(HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc);
	BOOL DrawImage(HDC hDestDC, CRect rcDest, CRect rcSrc);
	//设置透明色
	COLORREF SetTransColor(COLORREF crTrans);
	//获取透明色
	COLORREF GetTransColor();
	//调色函数
	BOOL AdjustHSL(int degHue,int perSaturation,int perLuminosity);
	void RGBtoHSL(BYTE Red, BYTE Green, BYTE Blue, float* Hue, float* Sat, float* Lum);
	COLORREF HSLtoRGB(float Hue,float Sat,float Lum);
	BYTE HueToRGB(float rm1,float rm2,float rh);

	//重载函数
public:
	//位图指针
	operator CBitmap * () { return CBitmap::FromHandle((HBITMAP)(*this)); }

	//区域函数
public:
	//创建区域
	bool CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor);
	//创建区域
	bool CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor);

	//绘图函数
public:
	//透明绘画
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor);
	//透明绘画
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor);

	//混合绘画
public:
	//混合绘画
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth);
	//混合绘画
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth);

	//辅助函数
private:
	//区域计算
	bool GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender);
};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//位图资源句柄
class SKIN_CONTROL_CLASS CImagePlusHandle : public IGDIResourceHandle
{
	//变量定义
protected:
	CImagePlus							* m_pImage;							//位图指针
	
	//函数定义
public:
	//构造函数
	CImagePlusHandle(CImagePlus * pImageObject=NULL);
	//析构函数
	virtual ~CImagePlusHandle();
	
	//接口函数
public:
	//是否绑定
	virtual bool IsAttached();
	//是否有效
	virtual bool IsResourceValid();
	//解除绑定
	virtual bool DetchResource();
	//绑定资源
	virtual bool AttachResource(IGDIResource * pImageObject);

	//操作重载
public:
	//获取句柄
	HBITMAP GetBitmapHandle();
	//获取对象
	CImagePlus * GetImageObject() { return m_pImage; };
	//指针重载
	CImagePlus * operator->() { return GetImageObject(); }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#endif