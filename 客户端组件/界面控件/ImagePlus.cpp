#include "StdAfx.h"
#include "ImagePlus.h"

/////////////////////////////////////////////////////////////////////////////////////////

//构造函数
CImagePlus::CImagePlus(void)
{
	m_nRefCount = 0;
	m_bLoadAlways = false;
	m_crTrans = (COLORREF)(-1);
}

//析构函数
CImagePlus::~CImagePlus(void)
{
	Destroy();
}

//增加引用
int CImagePlus::LockResource()
{
	if (m_nRefCount==0)
	{
		if (m_LoadInfo.hResourceDLL==NULL)
		{
			Load(m_LoadInfo.strFileName);
		}
		else
		{
			m_LoadInfo.strResType.Trim();
			m_LoadInfo.strResType.MakeUpper();
			if (m_LoadInfo.strResType == _T("BMP"))
			{
				LoadFromResource(m_LoadInfo.hResourceDLL,m_LoadInfo.uResourceID);
			}
			else
			{
				LoadImageFromResource(m_LoadInfo.hResourceDLL, m_LoadInfo.uResourceID, m_LoadInfo.strResType);
			}
		}
		if (IsNull()) return 0;
		AlphaChannelHandle();
	}
	return ++m_nRefCount;
}

//减少引用
int CImagePlus::UnLockResource()
{
	try
	{
		if (m_nRefCount>0) m_nRefCount--;
		if (m_nRefCount==0) Destroy();
	}
	catch (...) {}
	return m_nRefCount;
}

//是否设置加载信息
bool CImagePlus::IsSetLoadInfo()
{
	return ((m_LoadInfo.hResourceDLL)||(m_LoadInfo.strFileName.IsEmpty()==false));
}

//清除加载参数
bool CImagePlus::RemoveLoadInfo()
{
	m_LoadInfo.uResourceID = 0;
	m_LoadInfo.hResourceDLL = NULL;
	m_LoadInfo.strFileName.Empty();
	return true;
}

//获取加载参数
bool CImagePlus::GetLoadInfo(tagImageLoadInfo & LoadInfo)
{
	LoadInfo = m_LoadInfo;
	return IsSetLoadInfo();
}

//设置参数
bool CImagePlus::SetLoadInfo(const tagImageLoadInfo & LoadInfo, bool bLoadAlways)
{
	//保存变量
	int nOldRefCount = m_nRefCount;
	bool bOldLoadAlways = m_bLoadAlways;

	//清理资源
	Destroy();
	m_nRefCount = 0;
	m_bLoadAlways = bLoadAlways;

	//设置变量
	m_LoadInfo.uResourceID = LoadInfo.uResourceID;
	m_LoadInfo.hResourceDLL = LoadInfo.hResourceDLL;
	m_LoadInfo.strFileName = LoadInfo.strFileName;
	m_LoadInfo.strResType = LoadInfo.strResType;

	//恢复锁定
	if (bOldLoadAlways) nOldRefCount--;
	if (m_bLoadAlways) nOldRefCount++;
	while (nOldRefCount>0)
	{
		nOldRefCount--;
		LockResource();
	};

	return true;
}

//设置加载参数
bool CImagePlus::SetLoadInfo(LPCTSTR pszFileName, bool bLoadAlways)
{
	//保存变量
	int nOldRefCount = m_nRefCount;
	bool bOldLoadAlways = m_bLoadAlways;

	//清理资源
	Destroy();
	m_nRefCount = 0;
	m_bLoadAlways = bLoadAlways;

	//设置变量
	m_LoadInfo.uResourceID = 0;
	m_LoadInfo.hResourceDLL = NULL;
	m_LoadInfo.strFileName = pszFileName;

	//恢复锁定
	if (bOldLoadAlways) nOldRefCount--;
	if (m_bLoadAlways) nOldRefCount++;
	while (nOldRefCount>0)
	{
		nOldRefCount--;
		LockResource();
	};

	return true;
}

//设置加载参数
bool CImagePlus::SetLoadInfo(UINT uResourceID, HINSTANCE hResourceDLL, bool bLoadAlways, LPCTSTR pszResType)
{
	//保存变量
	int nOldRefCount = m_nRefCount;
	bool bOldLoadAlways = m_bLoadAlways;

	//清理资源
	Destroy();
	m_nRefCount = 0;
	m_bLoadAlways = bLoadAlways;
	m_LoadInfo.strFileName.Empty();

	//设置变量
	m_LoadInfo.uResourceID = uResourceID;
	m_LoadInfo.hResourceDLL = hResourceDLL;
	m_LoadInfo.strResType = pszResType;

	//恢复锁定
	if (bOldLoadAlways) nOldRefCount--;
	if (m_bLoadAlways) nOldRefCount++;
	while (nOldRefCount>0)
	{
		nOldRefCount--;
		LockResource();
	};

	return true;
}

//创建区域
bool CImagePlus::CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor)
{
	//创建区域
	CreateImageRegion(ImageRgn,0,0,GetWidth(),GetHeight(),crTransColor);

	return true;
}

//创建区域
bool CImagePlus::CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor)
{
	//判断状态
	ASSERT(IsNull()==false);
	if (IsNull()==true) return false;

	//参数调整
	INT nImageWidht = GetWidth();
	INT nImageHeight = GetHeight();
	if ((nXSrcPos+nSrcWidth)>nImageWidht) nSrcWidth = nImageWidht-nXSrcPos;
	if ((nYSrcPos+nSrcHeight)>nImageHeight) nSrcHeight = nImageHeight-nYSrcPos;

	//创建对象
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	ImageRgn.CreateRectRgn(0,0,0,0);

	//创建位图
	CImage ImageConsult;
	ImageConsult.Create(nSrcWidth,nSrcHeight,32);

	//调整位图
	BITMAP ImageInfo;
	GetObject(ImageConsult,sizeof(ImageInfo),&ImageInfo);
	while ((ImageInfo.bmWidthBytes%4)!=0) ImageInfo.bmWidthBytes++;

	//绘画位图
	BitBlt(ImageConsult.GetDC(),0,0,nSrcWidth,nSrcHeight,nXSrcPos,nYSrcPos);
	ImageConsult.ReleaseDC();

	//获取属性
	BYTE cbRTranColor = GetRValue(crTransColor);
	BYTE cbGTranColor = GetGValue(crTransColor);
	BYTE cbBTranColor = GetBValue(crTransColor);
	BYTE * pcbImageBitIndex = (BYTE *)ImageInfo.bmBits+(ImageInfo.bmHeight-1)*ImageInfo.bmWidthBytes;

	//创建区域
	for (INT nYPos=0;nYPos<ImageInfo.bmHeight;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageInfo.bmWidth;nXPos++)
		{
			//变量定义
			INT nXStartPos = nXPos;

			//透明判断
			do
			{
				COLORREF crImageColor = *(((LONG *)pcbImageBitIndex)+nXPos);
				if ((cbRTranColor==GetRValue(crImageColor))&&(cbGTranColor==GetGValue(crImageColor))&&(cbBTranColor==GetBValue(crImageColor))) break;
			} while ((++nXPos)<ImageInfo.bmWidth);

			//创建区域
			if ((nXPos-nXStartPos)>0)
			{
				//创建区域
				CRgn RgnUnite;
				RgnUnite.CreateRectRgn(nXStartPos,nYPos,nXPos,nYPos+1);

				//合并区域
				CombineRgn(ImageRgn,RgnUnite,ImageRgn,RGN_OR);
			}
		}

		//设置位置
		pcbImageBitIndex-=ImageInfo.bmWidthBytes;
	}

	return true;
}

//透明绘画
bool CImagePlus::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor)
{
	//绘画图片
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor);

	return true;
}

//透明绘画
bool CImagePlus::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor)
{
	//无效区域
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//绘画判断
	if (IsNull()==true) return false;

	//位置调整
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//颜色保存
	COLORREF crTextColor = pDestDC->SetTextColor(RGB(0,0,0));
	COLORREF crBackColor = pDestDC->SetBkColor(RGB(255,255,255));

	//掩码对象
	CDC MaskDC;
	CBitmap MaskImage;
	MaskDC.CreateCompatibleDC(pDestDC);
	MaskImage.CreateBitmap(ImageRender.cxRender,ImageRender.cyRender,1,1,NULL);

	//位图 DC
	CDC * pDCImage = CDC::FromHandle(GetDC());
	COLORREF crImageBkColor = pDCImage->SetBkColor(crTransColor);

	//构造掩码
	MaskDC.SelectObject(&MaskImage);
	MaskDC.BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//绘画对象
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		&MaskDC,0,0,SRCAND);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//颜色还原
	pDestDC->SetBkColor(crBackColor);
	pDestDC->SetTextColor(crTextColor);

	//释放资源
	ReleaseDC();
	MaskDC.DeleteDC();
	MaskImage.DeleteObject();

	return true;
}

//混合绘画
bool CImagePlus::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//透明绘画
	BlendDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor,cbAlphaDepth);

	return true;
}

//混合绘画
bool CImagePlus::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//无效区域
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//绘画判断
	if (IsNull()==true) return false;

	//位置调整
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//创建位图
	CImage ImageResult;
	CImage ImageSource;
	ImageResult.Create(ImageRender.cxRender,ImageRender.cyRender,32);
	ImageSource.Create(ImageRender.cxRender,ImageRender.cyRender,32);

	//绘画位图
	CDC * pDCImage = CDC::FromHandle(GetDC());
	CDC * pDCResult = CDC::FromHandle(ImageResult.GetDC());
	CDC * pDCSource = CDC::FromHandle(ImageSource.GetDC());
	pDCSource->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCCOPY);
	pDCResult->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDestDC,ImageRender.nXScreen,ImageRender.nYScreen,SRCCOPY);

	//获取属性
	float fAlpha = (float)(cbAlphaDepth/255.0);
	INT nPitchResult = ImageResult.GetPitch();
	INT nPitchSource = ImageSource.GetPitch();

	//获取数据
	LPBYTE cbBitResult = (LPBYTE)ImageResult.GetBits();
	LPBYTE cbBitSource = (LPBYTE)ImageSource.GetBits();

	//创建区域
	for (INT nYPos=0;nYPos<ImageRender.cyRender;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageRender.cxRender;nXPos++)
		{
			//获取颜色
			COLORREF * pcrResult = (COLORREF *)(cbBitResult+nYPos*nPitchResult+nXPos*4);
			COLORREF * pcrSource = (COLORREF *)(cbBitSource+nYPos*nPitchSource+nXPos*4);

			//混合处理
			if (*pcrSource!=crTransColor)
			{
				//结果颜色
				BYTE cbResultR = GetRValue(*pcrResult);
				BYTE cbResultG = GetGValue(*pcrResult);
				BYTE cbResultB = GetBValue(*pcrResult);

				//原图颜色
				BYTE cbSourceR = GetRValue(*pcrSource);
				BYTE cbSourceG = GetGValue(*pcrSource);
				BYTE cbSourceB = GetBValue(*pcrSource);

				//颜色混合
				cbResultR = (BYTE)(cbSourceR*fAlpha+cbResultR*(1.0-fAlpha));
				cbResultG = (BYTE)(cbSourceG*fAlpha+cbResultG*(1.0-fAlpha));
				cbResultB = (BYTE)(cbSourceB*fAlpha+cbResultB*(1.0-fAlpha));

				//颜色混合
				*pcrResult = RGB(cbResultR,cbResultG,cbResultB);
			}
		}
	}

	//绘画界面
	ImageResult.BitBlt(pDestDC->m_hDC,ImageRender.nXScreen,ImageRender.nYScreen);

	//释放对象
	ReleaseDC();
	ImageSource.ReleaseDC();
	ImageResult.ReleaseDC();

	return true;
}

//区域计算
bool CImagePlus::GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender)
{
	//相交矩形
	CRect rcIntersect;
	rcIntersect.top = __max(yDest,rcDirty.top);
	rcIntersect.left = __max(xDest,rcDirty.left);
	rcIntersect.right = __min((xDest+cxDest),rcDirty.right);
	rcIntersect.bottom = __min((yDest+cyDest),rcDirty.bottom);

	//渲染位置
	ImageRender.nYScreen = rcIntersect.top;
	ImageRender.nXScreen = rcIntersect.left;

	//渲染大小
	ImageRender.cxRender = rcIntersect.Width();
	ImageRender.cyRender = rcIntersect.Height();

	//图形索引
	ImageRender.nXImage = xSrc+ImageRender.nXScreen-xDest;
	ImageRender.nYImage = ySrc+ImageRender.nYScreen-yDest;

	return true;
}


//导入图片
BOOL CImagePlus::LoadImageFromResource(HINSTANCE hInstance, UINT uResourceID, LPCTSTR pszResourceType)
{
	return LoadImageFromResource(hInstance, MAKEINTRESOURCE(uResourceID), pszResourceType);
}

//导入图片
BOOL CImagePlus::LoadImageFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszResourceType)
{
	//变量定义
	HRSRC hResource = NULL;
	HGLOBAL hGlobal = NULL;
	IStream * pIStream = NULL;

	//加载位图
	try
	{
		//查找资源
		hResource = FindResource(hInstance, pszResourceName, pszResourceType);
		if (hResource == NULL)
		{
			DWORD m = GetLastError();
			throw 0;
		}

		//加载资源
		hGlobal = LoadResource(hInstance, hResource);
		if (hGlobal == NULL) throw 0;

		//读取资源
		LPVOID pImageBuffer = ::LockResource(hGlobal);
		DWORD dwImageSize = SizeofResource(hInstance, hResource);

		//创建数据
		CreateStreamOnHGlobal(NULL, TRUE, &pIStream);
		if (pIStream == NULL) throw 0;

		//写入数据
		pIStream->Write(pImageBuffer, dwImageSize, NULL);

		//创建位图
		if (Load(pIStream) != S_OK) throw 0;

		//释放资源
		if (pIStream != NULL) pIStream->Release();

		//是否资源
		if (hGlobal != NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		//AlphaChannelHandle();

		return TRUE;
	}
	catch (...)
	{
		//释放资源
		if (pIStream != NULL) pIStream->Release();

		//是否资源
		if (hGlobal != NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		return FALSE;
	}

	return TRUE;
}


//透明处理
BOOL CImagePlus::AlphaChannelHandle()
{
	if(IsNull()) return FALSE;
	if(GetBPP() < 32) return FALSE;

	int nWidth = GetWidth();
	int nHeight = GetHeight();
	for(int i=0; i<nWidth; i++)
	{
		for(int j=0; j<nHeight; j++)
		{
			unsigned char *pdwColor = (unsigned char *)GetPixelAddress(i,j);
			pdwColor[0] = pdwColor[0] * pdwColor[3] / 255;
			pdwColor[1] = pdwColor[1] * pdwColor[3] / 255;
			pdwColor[2] = pdwColor[2] * pdwColor[3] / 255;
		}
	}

	return TRUE;
}

//设置透明色
COLORREF CImagePlus::SetTransColor(COLORREF crTrans)
{
	COLORREF crTransOld;

	crTransOld = m_crTrans;
	m_crTrans = crTrans;

	return crTransOld;
}

//获取透明色
COLORREF CImagePlus::GetTransColor()
{
	return m_crTrans;
}

//绘画函数
BOOL CImagePlus::DrawImage(HDC hDestDC, int xDest, int yDest)
{
	if (IsNull()) return FALSE;

	return DrawImage(hDestDC, xDest, yDest, GetWidth(), GetHeight(), 0, 0, GetWidth(), GetHeight());
}

BOOL CImagePlus::DrawImage(HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc)
{
	if (IsNull()) return FALSE;

	return DrawImage(hDestDC, xDest, yDest, nDestWidth, nDestHeight, xSrc, ySrc, GetWidth(), GetHeight());
}

BOOL CImagePlus::DrawImage(HDC hDestDC, CRect rcDest, CRect rcSrc)
{
	return DrawImage(hDestDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());
}

BOOL CImagePlus::DrawImage( HDC hDestDC, int xDest, int yDest, int nDestWidth,
	int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight )
{
	BOOL bResult;

	if (IsNull()) return FALSE;

	HDC hDC = GetDC();

#if WINVER >= 0x0500
	if( (m_crTrans != (COLORREF)(-1)) && IsTransparencySupported() )
	{
		bResult = ::TransparentBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight,
			hDC, xSrc, ySrc, nSrcWidth, nSrcHeight, GetTransColor() );
	}
	else if( (GetBPP()>=32) && IsTransparencySupported() )
	{
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 0xff;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bResult = ::AlphaBlend( hDestDC, xDest, yDest, nDestWidth, nDestHeight, 
			hDC, xSrc, ySrc, nSrcWidth, nSrcHeight, bf );
	}
	else
#endif  // WINVER >= 0x0500
	{
		SetStretchBltMode(hDC, HALFTONE);
		SetBrushOrgEx(hDC, 0, 0, NULL);
		bResult = ::StretchBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, 
			hDC, xSrc, ySrc, nSrcWidth, nSrcHeight, SRCCOPY );
	}

	ReleaseDC();

	return( bResult );
}

BOOL CImagePlus::AdjustHSL(int nHue,int nSat,int nLum)
{
	if (IsNull()) return FALSE;
	float h,s,l;
	COLORREF color;
	unsigned char* pucColor = NULL;
	int nWidth = this->GetWidth();
	int nHeight = this->GetHeight();
	for(int i = 0; i < nWidth; i++)
	{
		for(int j = 0; j < nHeight; j++)
		{
			pucColor = (unsigned char*)(this->GetPixelAddress(i, j));
			RGBtoHSL(pucColor[2],pucColor[1],pucColor[0],&h,&s,&l);

			h = (float)((360-nHue)%360);
			s = nSat/100.0f;
			if (nLum > 100)
			{
				l += ((1-l)*(nLum-100)/100.0f);
			}
			else
			{
				l += (l*(nLum-100)/100.0f);
			}

			color = HSLtoRGB(h,s,l);
			pucColor[2] = GetRValue(color);
			pucColor[1] = GetBValue(color);
			pucColor[0] = GetGValue(color);

		}
	}
	return TRUE;
}


void CImagePlus::RGBtoHSL(BYTE Red, BYTE Green, BYTE Blue,float* Hue,float* Sat,float* Lum)
{
	BYTE minval = min(Red,min(Green,Blue));
	BYTE maxval = max(Red,max(Green,Blue));
	float mdiff = float(maxval) - float(minval);
	float msum  = float(maxval) + float(minval);

	*Lum = msum / 510.0f;

	if (maxval == minval) 
	{
		*Sat = 0.0f;
		*Hue = 0.0f; 
	}   
	else 
	{ 
		float rnorm = (maxval - Red) / mdiff;      
		float gnorm = (maxval - Green) / mdiff;
		float bnorm = (maxval - Blue) / mdiff;   

		*Sat = (*Lum <= 0.5f) ? (mdiff / msum) : (mdiff / (510.0f - msum));

		if(Red == maxval) 
			*Hue = 60.0f * (6.0f + bnorm - gnorm);
		if(Green == maxval) 
			*Hue = 60.0f * (2.0f + rnorm - bnorm);
		if(Blue == maxval) 
			*Hue = 60.0f * (4.0f + gnorm - rnorm);
		if (*Hue > 360.0f) 
			*Hue -= 360.0f;
	}
}

COLORREF CImagePlus::HSLtoRGB(float Hue,float Sat,float Lum)
{
	BYTE r,g,b;

	Lum = min(1,Lum);
	Sat = min(1,Sat);

	if(Sat == 0.0)
	{
		r = g = b = (BYTE)(255 * Lum);
	} 
	else 
	{
		float rm1, rm2;

		if (Lum <= 0.5f) 
			rm2 = Lum + Lum * Sat;
		else
			rm2 = Lum + Sat - Lum * Sat;
		rm1 = 2.0f * Lum - rm2;   

		r = HueToRGB(rm1, rm2, Hue + 120.0f);
		g = HueToRGB(rm1, rm2, Hue);
		b = HueToRGB(rm1, rm2, Hue - 120.0f);
	}
	return RGB(r,g,b);
}

BYTE CImagePlus::HueToRGB(float rm1,float rm2,float rh)
{
	while(rh > 360.0f)
		rh -= 360.0f;
	while(rh < 0.0f)
		rh += 360.f;

	if(rh < 60.0f)
		rm1 = rm1 + (rm2 - rm1) * rh / 60.0f;
	else if(rh < 180.0f)
		rm1 = rm2;
	else if(rh < 240.0f)
		rm1 = rm1 + (rm2 - rm1) * (240.0f - rh) / 60.0f;

	//float n = rm1*255;
	//int m = min((int)n,255);
	//m = max(0,m);
	return (BYTE)(rm1 * 255);//;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//构造函数
CImagePlusHandle::CImagePlusHandle(CImagePlus * pImageObject)
{
	m_pImage=NULL;
	AttachResource(pImageObject);
	return;
}

//析构函数
CImagePlusHandle::~CImagePlusHandle()
{
	DetchResource();
	return;
}

//绑定资源
bool CImagePlusHandle::AttachResource(IGDIResource * pImageObject)
{
	DetchResource();
	if (pImageObject)
	{
		CImagePlus * pSkinImage=(CImagePlus *)pImageObject;
		if (pImageObject->LockResource()>0)
		{
			m_pImage=pSkinImage;
			return true;
		}
	}
	return false;
}

//解除绑定
bool CImagePlusHandle::DetchResource()
{
	if (m_pImage) 
	{
		m_pImage->UnLockResource();
		m_pImage=NULL;
		return true;
	} 
	return false;
}

//是否绑定
bool CImagePlusHandle::IsAttached()
{
	return (m_pImage!=NULL);
}

//是否有效
bool CImagePlusHandle::IsResourceValid()
{
	return ((m_pImage)&&(m_pImage->IsNull()==false));
}

//获取句柄
HBITMAP CImagePlusHandle::GetBitmapHandle()
{
	if (IsResourceValid()==false) return NULL;
	return (HBITMAP)(*m_pImage);
}

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
