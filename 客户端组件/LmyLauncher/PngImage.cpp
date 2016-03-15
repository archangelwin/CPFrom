#include "StdAfx.h"
#include "PngImage.h"
#include "D2DEngine.h"
//////////////////////////////////////////////////////////////////////////////////
//构造函数
CPngImageSB::CPngImageSB()
{
	//设置变量
	m_pImage=NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );

	return;
}

//析构函数
CPngImageSB::~CPngImageSB()
{
	//销毁图片
	DestroyImage(); 
	DestroyCImage();
	return;
}

//是否加载
bool CPngImageSB::IsNull()
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetWidth(NULL, m_strImageName) == 0;

	//加载判断
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//获取宽度
INT CPngImageSB::GetWidth()
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetWidth(NULL, m_strImageName);

	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取宽度
	return m_pImage->GetWidth();
}

//获取高度
INT CPngImageSB::GetHeight()
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetHeight(NULL, m_strImageName);

	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取高度
	return m_pImage->GetHeight();
}

//销毁图片
bool CPngImageSB::DestroyImage()
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DeleteImage(NULL, m_strImageName);
	}

	//删除对象
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//加载图片
bool CPngImageSB::LoadImage(LPCTSTR pszFileName)
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->LaodImage(NULL, pszFileName, m_strImageName);
	}

	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//加载文件
	CT2CW strFileName(pszFileName);
	m_pImage=Image::FromFile((LPCWSTR)strFileName);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok)) 
	{
		DestroyImage();
		return false;
	}

	return true;
}

//加载图片
bool CPngImageSB::LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName)
{
	//WIN 7 执行
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->LaodImage(NULL, hInstance, pszResourceName, TEXT("PNG"), m_strImageName);
	}

	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//查找资源
	HRSRC hResource=FindResource(hInstance,pszResourceName,TEXT("PNG"));
	if (hResource==NULL) 
		return false;

	//读取资源
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//创建数据
	IStream * pIStream=NULL;
	HRESULT hr = 0;
	if ( (hr=CreateStreamOnHGlobal(NULL,TRUE,&pIStream))!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//写入数据
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//创建位图
	m_pImage=Image::FromStream(pIStream);
	int nError = GetLastError();

	//释放资源
	SafeRelease(pIStream);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		DestroyImage();
		return false;
	}

	return true;
}

//绘画图像
bool CPngImageSB::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//WIN 7 执行
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXPos, nYPos, 255  );
	}

	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//获取属性
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);

	return true;
}

//绘画图像
bool CPngImageSB::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	//WIN 7 执行
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, 255  );
	}

	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL)
		return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nDestWidth,(REAL)nDestHeight,UnitPixel);

	return true;
}

//绘画图像
bool CPngImageSB::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	//WIN 7 执行
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, nSrcWidth, nSrcHeight, 255 );
	}

	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nSrcWidth,(REAL)nSrcHeight,UnitPixel);

	return true;
}

//混合绘画
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//透明绘画
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//混合绘画
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//WIN 7 执行
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cbAlphaDepth  );
	}

	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDestDC!=NULL);
	Graphics graphics(pDestDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)xDest;
	rcDrawRect.Y=(REAL)yDest;
	rcDrawRect.Width=(REAL)cxDest;
	rcDrawRect.Height=(REAL)cyDest;

	//透明矩阵
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f, 
		0.0f,1.0f,0.0f,0.0f,0.0f, 
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
		0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//设置属性
	ImageAttributes Attributes; 
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxDest,(REAL)cyDest,UnitPixel,&Attributes);

	return true;
}

//混合绘画
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//WIN 7 执行
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cxSrc, cySrc, cbAlphaDepth  );
	}


	//创建缓冲
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//加载判断
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return false;

		//创建屏幕
		ASSERT(pDestDC!=NULL);
		Graphics graphics(pDestDC->GetSafeHdc());

		//构造位置
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)xDest;
		rcDrawRect.Y=(REAL)yDest;
		rcDrawRect.Width=(REAL)cxDest;
		rcDrawRect.Height=(REAL)cyDest;

		//透明矩阵
		ColorMatrix Matrix=
		{
			1.0f,0.0f,0.0f,0.0f,0.0f, 
			0.0f,1.0f,0.0f,0.0f,0.0f, 
			0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
			0.0f,0.0f,0.0f,0.0f,1.0f
		};

		//设置属性
		ImageAttributes Attributes; 
		Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

		//绘画图像
		graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxSrc,(REAL)cySrc,UnitPixel,&Attributes);	
	}
	else
	{
		//普通调用
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}
//是否加载
bool CPngImageSB::IsCNull()
{
	return m_CImage.IsNull();
}
//获取宽度(CImage)
INT CPngImageSB::GetCWidth()
{
	if (m_CImage.IsNull()) return 0;
	return m_CImage.GetWidth();
}
//获取高度(CImage)
INT CPngImageSB::GetCHeight()
{
	if (m_CImage.IsNull()) return 0;
	return m_CImage.GetHeight();
}
bool CPngImageSB::DestroyCImage()
{
	if (!m_CImage.IsNull())
	{
		m_CImage.Destroy();
	}
	return true;
}
bool CPngImageSB::LoadCImage(HINSTANCE hInstance,LPCTSTR pszResourceName)
{
	if ( !m_CImage.IsNull()) return false;

	// 查找资源
	HRSRC hRsrc = ::FindResource(hInstance, pszResourceName, TEXT("PNG"));
	if (hRsrc == NULL) return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(hInstance, hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid    = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize    = ::SizeofResource(hInstance, hRsrc);
	HGLOBAL hNew    = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht == S_OK )
	{
		// 加载图片
		m_CImage.Load(pStream);
	}
	GlobalFree(hNew);
	// 释放资源
	::FreeResource(hImgData);

	if (m_CImage.IsNull()) return false;
	return true;
}
//绘画图像
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//加载判断
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;


	//获取属性
	INT nImageWidth=m_CImage.GetWidth();
	INT nImageHeight=m_CImage.GetHeight();

	//绘画图像
	m_CImage.Draw(pDC->m_hDC, nXPos, nYPos, nImageWidth,nImageHeight, 0,0,nImageWidth,nImageHeight);
	return true;
}
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;
/*	if (m_CImage.GetBPP() == 32) //确认该图像包含Alpha通道 
	{     
		int i;   
		int j;    
		for (i=0; i<nDestWidth; i++)  
		{          
			for (j=0; j<nDestHeight; j++)     
			{             
				byte *pByte = (byte *)m_CImage.GetPixelAddress(i, j); 
				pByte[0] = pByte[0] * pByte[3] / 255;          
				pByte[1] = pByte[1] * pByte[3] / 255;    
				pByte[2] = pByte[2] * pByte[3] / 255; 
			}     
		} 
	}*/
	//加载位图
	m_CImage.Draw(pDC->m_hDC,nXDest, nYDest,nDestWidth, nDestHeight,nXScr, nYSrc, nDestWidth, nDestHeight); 
	return true;
}
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;
/*	if (m_CImage.GetBPP() == 32) //确认该图像包含Alpha通道 
 	{     
 		int i;   
 		int j;    
 		for (i=0; i<nDestWidth; i++)  
 		{          
 			for (j=0; j<nDestHeight; j++)     
 			{             
 				byte *pByte = (byte *)m_CImage.GetPixelAddress(i, j); 
  				pByte[0] = pByte[0] * pByte[3] / 255;          
  				pByte[1] = pByte[1] * pByte[3] / 255;    
  				pByte[2] = pByte[2] * pByte[3] / 255; 
 			}     
 		} 
 	}*/
	//加载位图
	m_CImage.Draw(pDC->m_hDC,nXDest, nYDest,nDestWidth, nDestHeight,nXScr, nYSrc, nSrcWidth, nSrcHeight); 
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
