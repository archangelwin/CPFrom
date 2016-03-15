#include "StdAfx.h"
#include "PngImage.h"
#include "D2DEngine.h"
//////////////////////////////////////////////////////////////////////////////////
//���캯��
CPngImageSB::CPngImageSB()
{
	//���ñ���
	m_pImage=NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );

	return;
}

//��������
CPngImageSB::~CPngImageSB()
{
	//����ͼƬ
	DestroyImage(); 
	DestroyCImage();
	return;
}

//�Ƿ����
bool CPngImageSB::IsNull()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetWidth(NULL, m_strImageName) == 0;

	//�����ж�
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//��ȡ���
INT CPngImageSB::GetWidth()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetWidth(NULL, m_strImageName);

	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ���
	return m_pImage->GetWidth();
}

//��ȡ�߶�
INT CPngImageSB::GetHeight()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetHeight(NULL, m_strImageName);

	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ�߶�
	return m_pImage->GetHeight();
}

//����ͼƬ
bool CPngImageSB::DestroyImage()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DeleteImage(NULL, m_strImageName);
	}

	//ɾ������
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//����ͼƬ
bool CPngImageSB::LoadImage(LPCTSTR pszFileName)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->LaodImage(NULL, pszFileName, m_strImageName);
	}

	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//�����ļ�
	CT2CW strFileName(pszFileName);
	m_pImage=Image::FromFile((LPCWSTR)strFileName);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok)) 
	{
		DestroyImage();
		return false;
	}

	return true;
}

//����ͼƬ
bool CPngImageSB::LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->LaodImage(NULL, hInstance, pszResourceName, TEXT("PNG"), m_strImageName);
	}

	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance,pszResourceName,TEXT("PNG"));
	if (hResource==NULL) 
		return false;

	//��ȡ��Դ
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//��������
	IStream * pIStream=NULL;
	HRESULT hr = 0;
	if ( (hr=CreateStreamOnHGlobal(NULL,TRUE,&pIStream))!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//д������
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//����λͼ
	m_pImage=Image::FromStream(pIStream);
	int nError = GetLastError();

	//�ͷ���Դ
	SafeRelease(pIStream);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		DestroyImage();
		return false;
	}

	return true;
}

//�滭ͼ��
bool CPngImageSB::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXPos, nYPos, 255  );
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//��ȡ����
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CPngImageSB::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, 255  );
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL)
		return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nDestWidth,(REAL)nDestHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CPngImageSB::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, nSrcWidth, nSrcHeight, 255 );
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nSrcWidth,(REAL)nSrcHeight,UnitPixel);

	return true;
}

//��ϻ滭
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//͸���滭
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//��ϻ滭
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cbAlphaDepth  );
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDestDC!=NULL);
	Graphics graphics(pDestDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)xDest;
	rcDrawRect.Y=(REAL)yDest;
	rcDrawRect.Width=(REAL)cxDest;
	rcDrawRect.Height=(REAL)cyDest;

	//͸������
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f, 
		0.0f,1.0f,0.0f,0.0f,0.0f, 
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
		0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//��������
	ImageAttributes Attributes; 
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxDest,(REAL)cyDest,UnitPixel,&Attributes);

	return true;
}

//��ϻ滭
bool CPngImageSB::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetCurrentWnd() && CD2DEngine::GetD2DEngine() )
	{
		return CD2DEngine::GetD2DEngine()->DrawImage(CD2DEngine::GetCurrentWnd(), m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cxSrc, cySrc, cbAlphaDepth  );
	}


	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//�����ж�
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return false;

		//������Ļ
		ASSERT(pDestDC!=NULL);
		Graphics graphics(pDestDC->GetSafeHdc());

		//����λ��
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)xDest;
		rcDrawRect.Y=(REAL)yDest;
		rcDrawRect.Width=(REAL)cxDest;
		rcDrawRect.Height=(REAL)cyDest;

		//͸������
		ColorMatrix Matrix=
		{
			1.0f,0.0f,0.0f,0.0f,0.0f, 
			0.0f,1.0f,0.0f,0.0f,0.0f, 
			0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
			0.0f,0.0f,0.0f,0.0f,1.0f
		};

		//��������
		ImageAttributes Attributes; 
		Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

		//�滭ͼ��
		graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxSrc,(REAL)cySrc,UnitPixel,&Attributes);	
	}
	else
	{
		//��ͨ����
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}
//�Ƿ����
bool CPngImageSB::IsCNull()
{
	return m_CImage.IsNull();
}
//��ȡ���(CImage)
INT CPngImageSB::GetCWidth()
{
	if (m_CImage.IsNull()) return 0;
	return m_CImage.GetWidth();
}
//��ȡ�߶�(CImage)
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

	// ������Դ
	HRSRC hRsrc = ::FindResource(hInstance, pszResourceName, TEXT("PNG"));
	if (hRsrc == NULL) return false;

	// ������Դ
	HGLOBAL hImgData = ::LoadResource(hInstance, hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid    = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize    = ::SizeofResource(hInstance, hRsrc);
	HGLOBAL hNew    = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);

	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht == S_OK )
	{
		// ����ͼƬ
		m_CImage.Load(pStream);
	}
	GlobalFree(hNew);
	// �ͷ���Դ
	::FreeResource(hImgData);

	if (m_CImage.IsNull()) return false;
	return true;
}
//�滭ͼ��
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//�����ж�
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;


	//��ȡ����
	INT nImageWidth=m_CImage.GetWidth();
	INT nImageHeight=m_CImage.GetHeight();

	//�滭ͼ��
	m_CImage.Draw(pDC->m_hDC, nXPos, nYPos, nImageWidth,nImageHeight, 0,0,nImageWidth,nImageHeight);
	return true;
}
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;
/*	if (m_CImage.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ�� 
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
	//����λͼ
	m_CImage.Draw(pDC->m_hDC,nXDest, nYDest,nDestWidth, nDestHeight,nXScr, nYSrc, nDestWidth, nDestHeight); 
	return true;
}
bool CPngImageSB::DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	ASSERT(m_CImage.IsNull() == false);
	if (m_CImage.IsNull()) return false;
/*	if (m_CImage.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ�� 
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
	//����λͼ
	m_CImage.Draw(pDC->m_hDC,nXDest, nYDest,nDestWidth, nDestHeight,nXScr, nYSrc, nSrcWidth, nSrcHeight); 
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
