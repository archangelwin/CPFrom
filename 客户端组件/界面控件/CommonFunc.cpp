#include "Stdafx.h"
#include "Resource.h"
#include "CommonFunc.h"
#include "GdiPlus.h"
#include "afxdtctl.h"
#include "afxsock.h"

using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes
    
    ImageCodecInfo* pImageCodecInfo = NULL;
    
    GetImageEncodersSize(&num, &size);
    if(size == 0)
        return -1;  // Failure
    
    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
        return -1;  // Failure
    
    GetImageEncoders(num, size, pImageCodecInfo);
    
    for(UINT j = 0; j < num; ++j)
    {
        if( wcsicmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }    
    }
    
    free(pImageCodecInfo);
    return -1;  // Failure
}

BOOL ConvertFile( TCHAR *cSourceFileName , TCHAR *cDestFileName , PictureType mSaveType )
{
	if ( !cSourceFileName || !cDestFileName )
	{
		return FALSE ;
	}	
	
	switch ( mSaveType )
	{
	case BMP_FILE :
		GetFileNameAuto( cDestFileName , _T("bmp") , NULL ) ;
		break ;
	case JPG_FILE :
		GetFileNameAuto( cDestFileName , _T("jpg") , NULL ) ;
		break ;
	case GIF_FILE:
		GetFileNameAuto( cDestFileName , _T("gif") , NULL ) ;
		break ;
	case TIF_FILE:
		GetFileNameAuto( cDestFileName , _T("tif") , NULL ) ;
		break ;
	case PNG_FILE:
		GetFileNameAuto( cDestFileName , _T("png") , NULL ) ;
		break ;
	default:
		GetFileNameAuto( cDestFileName , _T("bmp") , NULL ) ;
		break ;
	}
	
	WCHAR wszSourceFileName[MAX_PATH] , wszDestFileName[MAX_PATH] ;
#ifdef UNICODE
	wcscpy( wszSourceFileName , cSourceFileName ) ;
	wcscpy( wszDestFileName , cDestFileName ) ;
#else
	_mbstowcsz( wszSourceFileName , cSourceFileName , MAX_PATH ) ;
	_mbstowcsz( wszDestFileName ,cDestFileName ,  MAX_PATH ) ;
#endif
	
	TCHAR cFileExtName[10] ;
	
	GetFileExtName( cFileExtName , cSourceFileName ) ;
	cFileExtName[9] = _T('\0') ;
	
	WCHAR wszFormat[20] ;
	
	switch ( mSaveType )
	{
	case BMP_FILE :
		wcscpy( wszFormat , L"image/bmp" ) ;
		break ;
	case JPG_FILE :
		wcscpy( wszFormat , L"image/jpeg" ) ;
		break ;
	case GIF_FILE:
		wcscpy( wszFormat , L"image/gif" ) ;
		break ;
	case TIF_FILE:
		wcscpy( wszFormat , L"image/tiff" ) ;
		break ;
	case PNG_FILE:
		wcscpy( wszFormat , L"image/png" ) ;
		break ;
	default:
		wcscpy( wszFormat , L"image/bmp" ) ;
		break ;
	}
	
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	CLSID   encoderClsid;
	Status  stat=Ok;
	//Image*   image = new Image(L"C:\\Test.jpg"); //?¥y¦b MFC¤U??
	Image*   image = NULL;

	do
	{
		image = Bitmap::FromFile( wszSourceFileName , TRUE );   
		if ( !image )
		{
			break ;
		}
		// Get the CLSID of the PNG encoder.
		if ( GetEncoderClsid( wszFormat, &encoderClsid ) == -1 )
		{
			break ;
		}
		
		stat = image->Save( wszDestFileName , &encoderClsid , NULL);
	} while ( 0 ) ;

	if ( image )
	{
		delete image;
	}
	
	GdiplusShutdown(gdiplusToken);
	
	return (stat==Ok) ;
}

template <class T>
void Make2DArray(T **&x, int rows, int cols)
{
	x = new T *[rows] ;

	ASSERT( x ) ;

	for ( int i = 0 ; i < rows ; i++ )
	{
		x[i] = new int[cols] ;
		ASSERT( x[i] ) ;
	}
}

template <class T>
void Delete2DArray(T **&x, int rows)
{
	for ( int i = 0 ; i < rows ; i++ )
	{
		delete []x[i] ;
	}

	delete []x ;
	x = NULL ;
}

HBITMAP LoadBitmapFromResource( int ResourceID )	
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE( ResourceID ),RT_GROUP_ICON) ;
	return (HBITMAP)LoadImage(hInst , MAKEINTRESOURCE( ResourceID ),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
}

HBITMAP LoadBitmapFromFile(LPCTSTR lpszFileName)
{
	HDC						hdc = ::GetDC( 0 ) ;
	BOOL					bSucess ;
	DWORD					dwFileSize , dwHighSize , dwBytesRead ;
	HANDLE					hFile ;
	BITMAPFILEHEADER *		pbmfh ;

	hFile = CreateFile( lpszFileName , 
						GENERIC_READ , 
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL , 
						OPEN_EXISTING , 
						FILE_FLAG_SEQUENTIAL_SCAN , 
						NULL) ;

	if(hFile == INVALID_HANDLE_VALUE)
	{
		::ReleaseDC( 0 , hdc ) ;
		return NULL ;
	}

	dwFileSize = GetFileSize(hFile , &dwHighSize) ;

	if(dwHighSize)
	{
		CloseHandle(hFile) ;
		::ReleaseDC( 0 , hdc ) ;
		hFile = NULL ;
		return NULL ;
	}

	pbmfh = (BITMAPFILEHEADER *)malloc(dwFileSize) ;

	if(!pbmfh)
	{
		CloseHandle(hFile) ;
		::ReleaseDC( 0 , hdc ) ;
		return NULL ;
	}

	bSucess = ReadFile(hFile , pbmfh , dwFileSize , &dwBytesRead , NULL) ;
	CloseHandle(hFile) ;

	if( !bSucess || (dwBytesRead != dwFileSize) ||
		(pbmfh->bfType != *(WORD *)"BM") ||
		(pbmfh->bfSize != dwFileSize))
	{
		free(pbmfh) ;
		::ReleaseDC( 0 , hdc ) ;
		return NULL ;
	}

	HBITMAP hBitmap = CreateDIBitmap(hdc , (BITMAPINFOHEADER *)(pbmfh + 1) ,
									CBM_INIT , 
									(BYTE *)pbmfh + pbmfh->bfOffBits ,
									(BITMAPINFO *)(pbmfh + 1) ,
									DIB_RGB_COLORS) ;
	free (pbmfh) ;

	::ReleaseDC( 0 , hdc ) ;

	return hBitmap ;
}

HANDLE DDBtoDIB( HBITMAP bitmap) 
{
	//Define Variable
	BITMAP				bm;
	BITMAPINFOHEADER	bi;
    LPBITMAPINFOHEADER 	lpbi;
	DWORD				dwLen;
	HANDLE				hDib;
	HANDLE				handle;
	HDC 				hdc;
	HPALETTE			hPal;

	hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE );

	// get bitmap information
	GetObject(bitmap,sizeof(bm),(LPSTR)&bm);

	// initialize the bitmapinfoheader
	bi.biSize			= sizeof(BITMAPINFOHEADER);
	bi.biWidth			= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
//	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biBitCount		= 24;
	bi.biCompression	= BI_RGB;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// compute the size of the  infoheader and the color table
	int ncolors = (1 << bi.biBitCount); 
	if( ncolors> 256 ) 
		ncolors = 0;
	dwLen  = bi.biSize + ncolors * sizeof(RGBQUAD);

	// we need a device context to get the dib from
	hdc = ::GetDC(NULL);
	hPal = SelectPalette(hdc,hPal,FALSE);
	RealizePalette(hdc);

	// allocate enough memory to hold bitmapinfoheader and color table
	hDib = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDib){
		SelectPalette(hdc,hPal,FALSE);
		::ReleaseDC(NULL,hdc);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDib;

	*lpbi = bi;

	// call getdibits with a NULL lpbits param, so the device driver 
	// will calculate the bisizeimage field 
	GetDIBits(hdc, bitmap, 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS );

	bi = *lpbi;

	// if the driver did not fill in the bisizeimage field, then compute it
	// each scan line of the image is aligned on a dword (32bit) boundary
	if (bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;
	}

	// realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDib, dwLen, GMEM_MOVEABLE))
		hDib = handle;
	else
	{
		GlobalFree(hDib);

		// reselect the original palette
		SelectPalette(hdc,hPal,FALSE);
		::ReleaseDC(NULL,hdc);
		return NULL;
	}

	// get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDib;

	// finally get the dib
	BOOL bgotbits = GetDIBits( hdc, bitmap,
				0L,								// start scan line
				(DWORD)bi.biHeight,				// # of scan lines
				(LPBYTE)lpbi 					// address for bitmap bits
				+ (bi.biSize + ncolors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,				// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);			// use rgb for color table

	if( !bgotbits )
	{
		GlobalFree(hDib);
		
		SelectPalette(hdc,hPal,FALSE);
		::ReleaseDC(NULL,hdc);
		return NULL;
	}

	SelectPalette(hdc,hPal,FALSE);
	::ReleaseDC(NULL,hdc);

	return hDib;
}

HBITMAP DIBToDDB( HANDLE hDIB )
{
	LPBITMAPINFOHEADER lpbi;
	HBITMAP hbm;
	CPalette pal;
	CPalette* pOldPal;
	CClientDC dc(NULL);
	
	if (hDIB == NULL)
		return NULL;
	
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	
	int nColors = lpbi->biClrUsed ? lpbi->biClrUsed :
	1 << lpbi->biBitCount;
	
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors +
		bmInfo.bmiHeader.biClrUsed) +
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
	
	// Create and select a logical palette if needed
	if( nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		if ( !pLP )
		{
			return NULL ;
		}
		
		pLP->palVersion = 0x300;
		pLP->palNumEntries = (unsigned short)nColors;
		
		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}
		
		pal.CreatePalette( pLP );
		
		delete[] pLP;
		
		// Select and realize the palette
		pOldPal = dc.SelectPalette( &pal, FALSE );
		dc.RealizePalette();
	}
	
	
	hbm = CreateDIBitmap(dc.GetSafeHdc(), // handle to device context
						(LPBITMAPINFOHEADER)lpbi, // pointer to bitmap info header
						(LONG)CBM_INIT, // initialization flag
						lpDIBBits, // pointer to initialization data
						(LPBITMAPINFO)lpbi, // pointer to bitmap info
						DIB_RGB_COLORS ); // color-data usage
	
	if (pal.GetSafeHandle())
		dc.SelectPalette(pOldPal,FALSE);
	
	return hbm;
}

LONGLONG FormatStringToTime(CString mTime)
{
	LONGLONG nSeconds = 0 ;
	LONGLONG tempTime = 0 ;

	TCHAR TimeText[9] ;
	_tcscpy( TimeText , mTime ) ;
	TimeText[8] = _T('\0') ;
	
	TCHAR tempChar[3] , *tempPoint ;
	memcpy( tempChar , TimeText , 2*sizeof(TCHAR) ) ;
	tempChar[2] = _T('\0') ;
	tempTime = (LONGLONG)_ttoi( tempChar ) ;
	nSeconds += tempTime*3600 ;
	
	tempPoint = _tcschr( TimeText , _T(':') ) ;
	if ( !tempPoint )
	{
		return 0 ;
	}

	memcpy( tempChar , tempPoint+1 , 2*sizeof(TCHAR) ) ;
	tempChar[2] = _T('\0') ;
	tempTime = (LONGLONG)_ttoi( tempChar ) ;
	nSeconds += tempTime*60 ;

	tempPoint = _tcsrchr( TimeText , _T(':') ) ;
	if ( !tempPoint )
	{
		return 0 ;
	}

	memcpy( tempChar , tempPoint+1 , 2*sizeof(TCHAR) ) ;
	tempChar[2] = _T('\0') ;
	tempTime = (LONGLONG)_ttoi( tempChar ) ;
	nSeconds += tempTime ;

	if ( nSeconds >= (24*3600 - 1) )
	{
		nSeconds = nSeconds %( 24*3600) ;
	}
	else if ( nSeconds < 0 )
	{
		nSeconds = 0 ;
	}

	return nSeconds ;
}

CString FormatTimeToString(LONGLONG ntime)
{
	if ( ntime >= (24*3600L - 1) )
	{
		ntime = ntime %( 24*3600) ;
	}
	else if ( ntime < 0 )
	{
		ntime = 0 ;
	}

	CString mTime ;

	TCHAR TimeText[10] = _T("00:00:00") ;
	
	TCHAR tempText[2] = _T("0") ;
	int	 tempInt ;
	
	int	 nHour = (int)ntime / 3600 ;
	tempInt = nHour / 10 ;
 	_itot( tempInt , tempText , 10 ) ;
	TimeText[0] = *tempText ;
	tempInt = nHour % 10 ;
	_itot( tempInt , tempText , 10 ) ;
	TimeText[1] = *tempText ;
	
	ntime = ntime % 3600 ;
	int	 nMinute = (int)ntime / 60 ;
	tempInt = nMinute / 10 ;
	_itot( tempInt , tempText , 10 ) ;
	TimeText[3] = *tempText ;
	tempInt = nMinute % 10 ;
	_itot( tempInt , tempText , 10 ) ;
	TimeText[4] = *tempText ;
	
	ntime = ntime % 60 ;
	int	 nSencond = (int)ntime ;
	tempInt = nSencond / 10 ;
	_itot( tempInt , tempText , 10 ) ;
	TimeText[6] = *tempText ;
	tempInt = nSencond % 10 ;
	_itot( tempInt , tempText , 10 ) ;
	TimeText[7] = *tempText ;
	
	mTime = TimeText ;

	return mTime ;
}

CString FormatTime(LONGLONG nTime)
{
	CString mTime ;

	int nSecond = (int)(nTime % 60) ;
	nTime /= 60 ;

	int nMinute = (int)(nTime % 60) ;
	nTime /= 60 ;

	int nHour = (int)(nTime % 24) ;
	nTime /= 24 ;

	int nDay = (int)(nTime % 30) ;
	nTime /= 30 ;

	int nMonth = (int)(nTime % 12) ;
	nTime /= 12 ;

	int nYear = (int)(nTime) ;
	
	TCHAR cText[10] ;

	if ( nYear > 0 )
	{
		_itot( nYear , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("Äê") ;
	}

	if ( nMonth > 0 )
	{
		_itot( nMonth , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("ÔÂ") ;
	}

	if ( nDay > 0 )
	{
		_itot( nDay , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("Ìì") ;
	}

	if ( nHour > 0 )
	{
		_itot( nHour , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("Ê±") ;
	}

	if ( nMinute > 0 )
	{
		_itot( nMinute , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("·Ö") ;
	}

	if ( nSecond > 0 )
	{
		_itot( nSecond , cText , 10 ) ;
		mTime += cText ;
		mTime += _T("Ãë") ;
	}

	if ( mTime == _T("") )
	{
		mTime = _T("0Ãë") ;
	}

	return mTime ;
}

void DrawTriangle( CDC *memDC , TRIANGLE mTriangle , COLORREF color )
{
	CRgn Rgn ;
	POINT a[3] ;
	a[0].x = mTriangle.p1.x , a[0].y = mTriangle.p1.y ;
	a[1].x = mTriangle.p2.x , a[1].y = mTriangle.p2.y ;
	a[2].x = mTriangle.p3.x , a[2].y = mTriangle.p3.y ;

	Rgn.CreatePolygonRgn( a , 3 , ALTERNATE  ) ;
	
	FillBackGround( memDC , &Rgn , color ) ;
}

void FillBackGround( CDC *memDC , CRect rc , COLORREF bkColor )
{
	CBrush wndbkBrush( bkColor ) ;
	CBrush *oldBrush = memDC->SelectObject( &wndbkBrush ) ;
	memDC->FillRect (&rc, &wndbkBrush) ;
	memDC->SelectObject( oldBrush ) ;
}

void FillBackGround( CDC *memDC , CRgn *rgn , COLORREF bkColor )
{
	CBrush wndbkBrush( bkColor ) ;
	CBrush *oldBrush = memDC->SelectObject( &wndbkBrush ) ;
	memDC->FillRgn( rgn, &wndbkBrush) ;
	memDC->SelectObject( oldBrush ) ;
}

void DrawBitmap(CDC *memDC , CRect rc , UINT uBmpID , BOOL bStretch , COLORREF crTransparent )
{
	HBITMAP hBkBmp = LoadBitmapFromResource( uBmpID ) ;
	if ( !hBkBmp )
	{
		return ;
	}

	BITMAP bm ;
	:: GetObject( hBkBmp , sizeof(bm) , &bm ); 
	
	HDC hdcMem , hdc ;
	hdc = memDC->m_hDC ;
	hdcMem = CreateCompatibleDC(hdc) ;
	if(hdcMem == NULL)
	{
		DeleteObject( hBkBmp ) ;
		return ;
	}
	HBITMAP hBmp =  (HBITMAP)SelectObject(hdcMem , hBkBmp) ;
		
	if ( bStretch )
	{
		SetStretchBltMode(hdc , COLORONCOLOR) ;
		StretchBlt(	
					hdc , 
					rc.left ,
					rc.top , 
					rc.Width() , 
					rc.Height() ,
					hdcMem ,
					0 , 
					0, 
					bm.bmWidth , 
					bm.bmHeight ,
					SRCCOPY 
					) ;
	}
	else
	{
		BitBlt(
				hdc , 
				rc.left ,
				rc.top , 
				rc.Width() , 
				rc.Height() ,
				hdcMem ,
				0 , 
				0,
				SRCCOPY
				) ;
	}

	SelectObject( hdcMem , hBmp ) ;
	DeleteDC(hdcMem) ;

	DeleteObject( hBkBmp ) ;
}

void DrawBitmap(CDC *memDC , CRect rc , HBITMAP hBkBmp , BOOL bStretch , COLORREF crTransparent)
{
	if ( !memDC || !hBkBmp )
	{
		return ;
	}
	
	BITMAP bm ;
	:: GetObject( hBkBmp , sizeof(bm) , &bm ); 
	
	HDC hdcMem , hdc ;
	hdc = memDC->m_hDC ;
	hdcMem = CreateCompatibleDC(hdc) ;
	if(hdcMem == NULL)
	{
		return ;
	}
	HBITMAP hBmp =  (HBITMAP)SelectObject(hdcMem , hBkBmp) ;
		
	if ( bStretch )
	{
		SetStretchBltMode(hdc , COLORONCOLOR) ;

		if ( crTransparent != 0xFFFFFFFF )
		{
			TransparentBlt( 
					hdc , 
					rc.left ,
					rc.top , 
					rc.Width() , 
					rc.Height() ,
					hdcMem ,
					0 , 
					0, 
					bm.bmWidth , 
					bm.bmHeight ,
					crTransparent ) ;
		}
		else
		{
			StretchBlt(	
					hdc , 
					rc.left ,
					rc.top , 
					rc.Width() , 
					rc.Height() ,
					hdcMem ,
					0 , 
					0, 
					bm.bmWidth , 
					bm.bmHeight ,
					SRCCOPY 
					) ;
		}
	}
	else
	{
		int x = rc.left+(rc.Width()-bm.bmWidth)/2 ;
		int y = rc.top+(rc.Height()-bm.bmHeight)/2 ;

		if ( crTransparent != 0xFFFFFFFF )
		{
			TransparentBlt( 
					hdc , 
					rc.left ,
					rc.top , 
					rc.Width() , 
					rc.Height() ,
					hdcMem ,
					0 , 
					0, 
					bm.bmWidth , 
					bm.bmHeight ,
					crTransparent ) ;
		}
		else
		{
			int nWidth = rc.Width() < bm.bmWidth ? rc.Width() : bm.bmWidth ;
			int nHeight = rc.Height() < bm.bmHeight ? rc.Height() : bm.bmHeight ;
			BitBlt(
				hdc , 
				x ,
				y , 
				nWidth , 
				nHeight ,
				hdcMem ,
				0 , 
				0,
				SRCCOPY
				) ;
		}
	}

	SelectObject( hdcMem , hBmp ) ;
	DeleteDC(hdcMem) ;
}

void DrawSpecialRect(CDC *memDC , CRect mBoundRect , CRect mDestRect , HBITMAP hBkBmp )
{
	if ( mDestRect.left < mBoundRect.left )
	{
		mDestRect.left = mBoundRect.left ;
	}
	if ( mDestRect.right > mBoundRect.right )
	{
		mDestRect.right = mBoundRect.right ;
	}
	if ( mDestRect.top < mBoundRect.top )
	{
		mDestRect.top = mBoundRect.top ;
	}
	if ( mDestRect.bottom > mBoundRect.bottom )
	{
		mDestRect.bottom = mBoundRect.bottom ;
	}

	BITMAP bm ;
	:: GetObject( hBkBmp , sizeof(bm) , &bm ); 

	double x_dwScale = 1.0 , y_dwScale = 1.0 ;
	x_dwScale = (double)(bm.bmWidth) / (double)(mBoundRect.Width()) ;
	y_dwScale = (double)(bm.bmHeight) / (double)(mBoundRect.Height()) ;

	int x_Start , x_Width , y_Start , y_Height ;

	x_Start = (int)((double)(mDestRect.left - mBoundRect.left)*x_dwScale) ;
	y_Start = (int)((double)(mDestRect.top - mBoundRect.top)*y_dwScale) ;
	x_Width = (int)((double)(mDestRect.Width())*x_dwScale) ;
	y_Height = (int)((double)(mDestRect.Height())*y_dwScale) ;

	HDC hdcMem , hdc ;
	hdc = memDC->m_hDC ;
	hdcMem = CreateCompatibleDC(hdc) ;
	if(hdcMem == NULL)
	{
		return ;
	}
	HBITMAP hBmp =  (HBITMAP)SelectObject(hdcMem , hBkBmp) ;
	
	SetStretchBltMode(hdc , COLORONCOLOR) ;
	StretchBlt(	
				hdc , 
				mDestRect.left ,
				mDestRect.top , 
				mDestRect.Width() , 
				mDestRect.Height() ,
				hdcMem ,
				x_Start , 
				y_Start, 
				x_Width , 
				y_Height ,
				SRCCOPY 
				) ;

	SelectObject( hdcMem , hBmp ) ;
	DeleteDC(hdcMem) ;
}

BOOL RepaintBk( CDC *pDC , UINT nResourceID , CRect rc )
{
	CBitmap bmp;

	if (bmp.LoadBitmap( nResourceID ))
	{
		// Get the size of the bitmap.
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		
		// Create an in-memory device context compatible with the
		// display device context that is used to paint.
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);
		
		// Select the bitmap into the in-memory device context.
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
		
		// Find a center point for the bitmap in the client area.
		int nX = rc.left + (rc.Width() - bmpInfo.bmWidth) / 2;
		int nY = rc.top + (rc.Height() - bmpInfo.bmHeight) / 2;
		
		// Copy the bits from the in-memory device context to the on-
		// screen device context to do the painting. Use the computed center
		// point for the target offset.
		pDC->BitBlt(nX, nY, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
			0, 0, SRCCOPY);
		
		dcMemory.SelectObject(pOldBitmap);

		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

BOOL RepaintBk( CDC *pDC , HBITMAP hBitmap , CRect rc )
{
	CBitmap bmp;

	if (bmp.Attach( hBitmap ))
	{
		// Get the size of the bitmap.
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		
		// Create an in-memory device context compatible with the
		// display device context that is used to paint.
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);
		
		// Select the bitmap into the in-memory device context.
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
		
		// Find a center point for the bitmap in the client area.
		int nX = rc.left + (rc.Width() - bmpInfo.bmWidth) / 2;
		int nY = rc.top + (rc.Height() - bmpInfo.bmHeight) / 2;
		
		// Copy the bits from the in-memory device context to the on-
		// screen device context to do the painting. Use the computed center
		// point for the target offset.
		pDC->BitBlt(nX, nY, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
			0, 0, SRCCOPY);
		
		dcMemory.SelectObject(pOldBitmap);

		bmp.Detach() ;
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

void DrawParentText( CDC *memDC , CRect rc , int m_nFontSize , TCHAR *m_FontName , 
					CString mString , COLORREF m_FontColor , int m_DrawDirect ,
					BYTE bCharset )
{	
	CFont oft ;
	oft.CreateFont( m_nFontSize , 
					0, 0, 0, FW_NORMAL, 0, 0, 0, 
					bCharset,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					PROOF_QUALITY,
					VARIABLE_PITCH | FF_ROMAN,
					m_FontName );
	
	CFont *oldFont = memDC->SelectObject( &oft ) ;
	COLORREF ocr = memDC->SetTextColor( m_FontColor );
	
	int obk = memDC->SetBkMode(TRANSPARENT);
	
	TCHAR OutText[100] ;
	_tcscpy( OutText , mString ) ;
	OutText[99] = _T('\0') ;

	memDC->DrawText(OutText, _tcslen(OutText) , rc,m_DrawDirect);
	memDC->SetTextColor(ocr);
	memDC->SelectObject(oldFont);
	memDC->SetBkMode(obk);
}

void SetTransParentWnd(HWND hWnd , BYTE bValue)
{
	//WS_EX_LAYERED = 0x80000
	LONG lStyle = GetWindowLong(hWnd,GWL_EXSTYLE)^0x80000; 
	SetWindowLong(hWnd,GWL_EXSTYLE, lStyle|0x80000) ;	

	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL; 
		//È¡µÃSetLayeredWindowAttributesº¯ÊýÖ¸Õë 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
		if(fun)
		{
			if ( bValue < 20 )
			{
				bValue = 20 ;
			}
			else if ( bValue > 255 )
			{
				bValue = 255 ;
			}
			fun(hWnd,0,bValue,2); 
		}
		FreeLibrary(hInst); 
	}
}

HBITMAP GetWindowBitMap( HWND hWnd )
{
	HDC hdcmy,hbufferdc;
	HBITMAP  hBit,hOldBitmap;
	RECT rc ;

	int SysWidth , SysHeight ;
	
	if(hWnd == NULL)
	{
		hWnd = ::GetDesktopWindow();
		SysWidth  = GetSystemMetrics(SM_CXSCREEN);
		SysHeight = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		::GetWindowRect(hWnd , &rc) ;
		SysHeight = rc.bottom - rc.top ;
		SysWidth  = rc.right - rc.left ;
	}
	
	hdcmy = ::GetDC(hWnd);	
	hbufferdc = CreateCompatibleDC(hdcmy);

	//Create Hbitmap
	hBit = CreateCompatibleBitmap(hdcmy, SysWidth, SysHeight);

	//Get bit to Buffer
	hOldBitmap = (HBITMAP)SelectObject(hbufferdc, hBit);
	BitBlt( hbufferdc, 0, 0, SysWidth, SysHeight,
			hdcmy, 0, 0, SRCCOPY);

	//Get finally bit
	hBit = (HBITMAP)SelectObject(hbufferdc, hOldBitmap);

	DeleteDC( hbufferdc );
	::ReleaseDC(NULL,hdcmy);	

	return hBit;
}

BOOL IsLNKFileType( TCHAR *cFileName )
{
	if ( !cFileName )
	{
		return FALSE ;
	}

	//Is .lnk File ?
	TCHAR cFileExt[10] ;
	GetFileExtName( cFileExt , cFileName ) ;
	cFileExt[9] = _T('\0') ;
	if ( _tcsicmp( cFileExt , _T("lnk") ) == 0 )
	{
		return TRUE ;
	}

	return FALSE ;
}

FILETIME GetFileLastWriteTimeW( WCHAR *wszFileName )
{
	FILETIME mLastWriteTime ;
	mLastWriteTime.dwHighDateTime = 0 ;
	mLastWriteTime.dwLowDateTime = 0 ;
	if ( !wszFileName )
	{
		return mLastWriteTime ;
	}

	WCHAR wszFullName[MAX_PATH] ;
	GetLongPathNameW( wszFileName , wszFullName , MAX_PATH ) ;
	
	WIN32_FIND_DATAW win32_find_data ;
	HANDLE hFindFileDir = FindFirstFileW(wszFullName , &win32_find_data) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return mLastWriteTime ;
	}

	FindClose( hFindFileDir ) ;

	if ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return mLastWriteTime ;
	}

	mLastWriteTime.dwHighDateTime = win32_find_data.ftLastWriteTime.dwHighDateTime ;
	mLastWriteTime.dwLowDateTime = win32_find_data.ftLastWriteTime.dwLowDateTime ;

	return mLastWriteTime ;
}

FILETIME GetFileLastWriteTimeA( char *cFileName )
{
	FILETIME mLastWriteTime ;
	mLastWriteTime.dwHighDateTime = 0 ;
	mLastWriteTime.dwLowDateTime = 0 ;
	if ( !cFileName )
	{
		return mLastWriteTime ;
	}

	char cFullName[MAX_PATH] ;
	GetLongPathNameA( cFileName , cFullName , MAX_PATH ) ;
	
	WIN32_FIND_DATAA win32_find_data ;
	HANDLE hFindFileDir = FindFirstFileA(cFullName , &win32_find_data) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return mLastWriteTime ;
	}

	FindClose( hFindFileDir ) ;

	if ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return mLastWriteTime ;
	}

	mLastWriteTime.dwHighDateTime = win32_find_data.ftLastWriteTime.dwHighDateTime ;
	mLastWriteTime.dwLowDateTime = win32_find_data.ftLastWriteTime.dwLowDateTime ;

	return mLastWriteTime ;
}

BOOL SetFileLastWriteTime( TCHAR *cFileName , FILETIME mWriteTime )
{
	if ( !cFileName )
	{
		return FALSE ;
	}

	HANDLE hFile = CreateFile(  
								cFileName , 
								GENERIC_WRITE , 
								FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL , 
								OPEN_ALWAYS , 
								FILE_WRITE_ATTRIBUTES , 
								NULL) ;
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE ;
	}

	BOOL bOK = SetFileTime( hFile , (LPFILETIME)NULL , (LPFILETIME)NULL , &mWriteTime ) ;
	
	CloseHandle( hFile ) ;
	
	return bOK ;
}

void ConvertLongToChar(long number, TCHAR *cNumber, int numbers)
{
	int i ;
	long residue , quotient ,devider ;
	
	devider = number ;

	for(i = numbers - 1 ; i >= 0 ; i--)
	{
		residue  = devider / 10 ;
		quotient = devider % 10 ;
		devider  = residue ;

		*(cNumber + i) = (TCHAR)(quotient + 48) ;
	}

	*(cNumber + numbers) = _T('\0') ;
}

LPITEMIDLIST ConvertFolderToPIDL( CString strFolderName )
{
	LPITEMIDLIST  pidl;
	LPSHELLFOLDER pDesktopFolder;
	TCHAR         szPath[MAX_PATH];
	OLECHAR       olePath[MAX_PATH];
	ULONG         chEaten;
	ULONG         dwAttributes;
	HRESULT       hr;
	
	// 
	// Get the path to the file we need to convert.
	// 
	_tcscpy( szPath , strFolderName ) ;
	
	// 
	// Get a pointer to the Desktop's IShellFolder interface.
	// 
	if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
	{
		// 
		// IShellFolder::ParseDisplayName requires the file name be in
		// Unicode.
		//
#ifdef UNICODE
		wcscpy( olePath , szPath ) ;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1,
			olePath, MAX_PATH);
#endif
		
		// 
		// Convert the path to an ITEMIDLIST.
		// 
		hr = pDesktopFolder->ParseDisplayName(
											NULL,
											NULL,
											olePath,
											&chEaten,
											&pidl,
											&dwAttributes
											);
		if (FAILED(hr))
		{
			// Handle error.
		}
		
		// 
		// pidl now contains a pointer to an ITEMIDLIST for .\readme.txt.
		// This ITEMIDLIST needs to be freed using the IMalloc allocator
		// returned from SHGetMalloc().
		// 
		
		//release the desktop folder object
		pDesktopFolder->Release();
	}

	return pidl ;
}

int CALLBACK _SHBrowseForFolderCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if(uMsg == BFFM_INITIALIZED)
        ::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    
    return    0;
}

int GetSaveOpenFolderName(HWND hParent, CString &strFolder)
{
	TCHAR cInitPath[MAX_PATH] ;
	_tcscpy( cInitPath , strFolder ) ;
	if ( !IsFileDirectory( cInitPath ) )
	{
		Sleep(0) ;
	}

	LPMALLOC lpMalloc;
	
    if (::SHGetMalloc(&lpMalloc) != NOERROR) 
		return FALSE;
	
	TCHAR szDisplayName[_MAX_PATH];
    TCHAR szBuffer[_MAX_PATH];
    BROWSEINFO browseInfo;
    browseInfo.hwndOwner = hParent;
    browseInfo.pidlRoot = NULL; // set root at Desktop
    browseInfo.pszDisplayName = szDisplayName;
    browseInfo.lpszTitle = _T("Select a folder") ;
    browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
    browseInfo.lpfn = _SHBrowseForFolderCallbackProc;
    browseInfo.lParam = LPARAM(cInitPath);
	
    LPITEMIDLIST lpItemIDList;
    if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
    {
        // Get the path of the selected folder from the    item ID list.
        if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
        {
            // At this point, szBuffer contains the path the user chose.
            if (szBuffer[0] == _T('\0'))
			{
				return FALSE;
			}
			
            // We have a path in szBuffer! Return it.
            strFolder = szBuffer;
            return TRUE;
        }
        else 
			return TRUE; // strResult is empty
		
        lpMalloc->Free(lpItemIDList);
        lpMalloc->Release();
    }
    
	return TRUE;
}

BOOL GetSaveOpenFileName( IN HWND hWnd , IN TCHAR *cFilter , IN BOOL bSave,
						  IN TCHAR *strTitle , IN TCHAR *cFilePath , 
						  IN TCHAR *cInFileName , OUT TCHAR *cOutFileName )
{
	_tcscpy( cOutFileName , _T("") ) ;

	TCHAR szFile[MAX_PATH] , szPath[MAX_PATH] ;
	if ( cFilePath == NULL )
	{
		GetCurrentDirectory( MAX_PATH , szPath ) ;
	}
	else
	{
		_tcscpy( szPath , cFilePath ) ;
	}

	int nLength = _tcslen(szPath) ;
	if ( nLength > 0 && szPath[nLength-1] == _T('\\') )
	{
		szPath[nLength-1] = _T('\0') ;
	}
	
	if ( cInFileName == NULL )
	{
		ZeroMemory( szFile , MAX_PATH ) ;
	}
	else
	{
		_tcscpy( szFile , cInFileName ) ;
	}	
	
	DWORD dwFilterIndex = 1 ;
	if ( cInFileName && cFilter )
	{
		TCHAR cFileExtName[10] ;
		GetFileExtName( cFileExtName , cInFileName ) ;
		if ( _tcsicmp( cFileExtName , _T("") ) != 0 )
		{
			__try
			{
				TCHAR * cTerminalSignal = cFilter ;
				int nLength = 0 ;
				while ( 1 )
				{
					if ( *cTerminalSignal == _T('\0') && 
						 *(cTerminalSignal+1) == _T('\0') )
					{
						break ;
					}
					else
					{
						nLength++ ;
					}

					cTerminalSignal ++ ;
				}

				cTerminalSignal = cFilter ;
				while ( (cTerminalSignal-cFilter) <= nLength )
				{
					if ( _tcsstr( cTerminalSignal , cFileExtName ) )
					{
						break ;
					}
					
					cTerminalSignal = _tcschr( cTerminalSignal , _T('\0') ) ;
					cTerminalSignal += 1 ;
					cTerminalSignal = _tcschr( cTerminalSignal , _T('\0') ) ;
					cTerminalSignal += 1 ;
					dwFilterIndex++ ;
				}
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
			}
		}
	}	

	OPENFILENAME OpenFileName;
    ZeroMemory(&OpenFileName, sizeof(OPENFILENAME));

   // ¶ñ¤J OPENFILENAME µ²ºc¥H¤ä´©½d¥»¤Î¤ÄÂI¡C
    OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = hWnd ;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrInitialDir   = szPath;
	OpenFileName.lpstrFile		   = szFile ;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrTitle        = strTitle ;
    OpenFileName.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT ;
	if ( cFilter )
	{
		OpenFileName.lpstrFilter   = cFilter ;
		OpenFileName.nFilterIndex  = dwFilterIndex ;	
	}
	else
	{
		OpenFileName.lpstrFilter   = _T("All File (*.*)\0*.*\0\0") ;
	}
	
	if ( bSave )
	{
		if(GetSaveFileName(&OpenFileName) == TRUE)
		{
			_tcscpy( cOutFileName , szFile ) ;
			TCHAR cFileExtName[10] ;
			GetFileExtName( cFileExtName , cOutFileName ) ;
			if ( _tcscmp( cFileExtName , _T("") ) == 0 ) 
			{
				if ( cFilter )
				{
					__try
					{	
						TCHAR *cTerminalSignal = NULL ;
						DWORD i = 0 ;
						
						cTerminalSignal = cFilter ;
						while ( i < (OpenFileName.nFilterIndex-1) )
						{
							cTerminalSignal = _tcschr( cTerminalSignal , _T('\0') ) ;
							cTerminalSignal += 1 ;
							cTerminalSignal = _tcschr( cTerminalSignal , _T('\0') ) ;
							cTerminalSignal += 1 ;
							i++ ;
						}
						
						int nLength = 0 ;
						TCHAR *cDotSignal = NULL ;
						TCHAR *cSperateSignal = NULL , *cSpaceSignal = NULL , *cEndSignal = NULL ;
						
						nLength = _tcslen( cTerminalSignal ) ;
						cDotSignal = _tcschr( cTerminalSignal+nLength+1 , _T('.') ) ;
						cSperateSignal = _tcschr( cTerminalSignal+nLength+1 , _T(';') ) ;
						cSpaceSignal = _tcschr( cTerminalSignal+nLength+1 , _T(' ') ) ;
						cTerminalSignal = _tcschr( cFilter+nLength+1 , _T('\0') ) ;
						
						if ( cSperateSignal && cSpaceSignal )
						{
							cEndSignal = ( cSpaceSignal < cSperateSignal ? cSpaceSignal : cSperateSignal ) ;
						}
						else if ( cSperateSignal )
						{
							cEndSignal = cSperateSignal ;
						}
						else if ( cSpaceSignal )
						{
							cEndSignal = cSpaceSignal ;
						}						 
						
						if ( cDotSignal && cEndSignal && cTerminalSignal )
						{
							if ( cTerminalSignal < cSperateSignal )
							{
								_tcsncpy( cFileExtName , cDotSignal , 
									(cSperateSignal-cDotSignal) ) ;
								cFileExtName[cSperateSignal-cDotSignal] = _T('\0') ;
							}
							else
							{
								_tcscpy( cFileExtName , cDotSignal ) ;
							}
							
							cFileExtName[9] = _T('\0') ;
							_tcscat( cOutFileName , cFileExtName ) ;
						}
						else if ( cDotSignal && cTerminalSignal )
						{
							_tcscpy( cFileExtName , cDotSignal ) ;
							_tcscat( cOutFileName , cFileExtName ) ;
						}
					}
					__except ( EXCEPTION_EXECUTE_HANDLER )
					{
						_tcscpy( cOutFileName , szFile ) ;
					}
				}
			}
			return TRUE ;
		}
		else
		{
			return FALSE ;
		}
	}
	else
	{
		if(GetOpenFileName(&OpenFileName) == TRUE)
		{
			_tcscpy( cOutFileName , szFile ) ;			
			return TRUE ;
		}
		else
		{
			return FALSE ;
		}
	}	
}

void CutRect(CRect SourceRc, CRect CutRc, CRect *DestRc1, CRect *DestRc2)
{
	*DestRc1 = CRect(-1,-1,-1,-1) ;
	*DestRc2 = CRect(-1,-1,-1,-1) ;

	if ( CutRc.right <= SourceRc.left )
	{
		*DestRc1 = SourceRc ;
		return ;
	}

	if ( CutRc.left >= SourceRc.right )
	{
		*DestRc1 = SourceRc ;
		return ;
	}

	if ( CutRc.left >= SourceRc.left && CutRc.right <= SourceRc.right )
	{
		DestRc1->left = SourceRc.left ;
		DestRc1->right = CutRc.left ;
		DestRc1->top = SourceRc.top ;
		DestRc1->bottom = SourceRc.bottom ;

		DestRc2->left = CutRc.right ;
		DestRc2->right = SourceRc.right ;
		DestRc2->top = SourceRc.top ;
		DestRc2->bottom = SourceRc.bottom ;

		return ;
	}

	if ( CutRc.left <= SourceRc.left && CutRc.right <= SourceRc.right )
	{
		DestRc1->left = CutRc.right ;
		DestRc1->right = SourceRc.right ;
		DestRc1->top = SourceRc.top ;
		DestRc1->bottom = SourceRc.bottom ;
		
		return ;
	}

	if ( CutRc.right >= SourceRc.right && CutRc.left >= SourceRc.left )
	{
		DestRc1->left = SourceRc.left ;
		DestRc1->right = CutRc.left ;
		DestRc1->top = SourceRc.top ;
		DestRc1->bottom = SourceRc.bottom ;

		return ;
	}
}

void GetProgramFilePathW( WCHAR *wszFilePath )
{
	if ( !wszFilePath ) 
	{
		return ;
	}

	WCHAR wszProgramName[MAX_PATH] ;
	GetModuleFileNameW( NULL , wszProgramName , MAX_PATH ) ;	
	GetFileParentDirW( wszFilePath , wszProgramName ) ;
}

void GetProgramFilePathA( char *cFilePath )
{
	char cProgramName[MAX_PATH] ;
	GetModuleFileNameA( NULL , cProgramName , MAX_PATH ) ;	
	GetFileParentDirA( cFilePath , cProgramName ) ;
}

BOOL GetFileParentDirW( OUT WCHAR *wszFileParentDir , IN WCHAR *wszSrcFileName )
{
	if ( wszSrcFileName == NULL || wszFileParentDir == NULL )
	{
		return FALSE ;
	}
	
	__try
	{
		WCHAR wszTempFileName[MAX_PATH] ;
		wcscpy( wszTempFileName , wszSrcFileName ) ;
			
		WCHAR wszFileTitle[MAX_PATH] ;
		if ( GetFileShortNameW( wszFileTitle , wszTempFileName ) )
		{
			wcscpy( wszFileParentDir , wszSrcFileName ) ;
			int nLength = wcslen( wszFileParentDir ) ;
			int i = nLength ;
			while ( i >= 0 )
			{
				if ( wcsstr( wszFileParentDir+i , wszFileTitle ) )
				{
					*(wszFileParentDir+i) = L'\0' ;
					break ;
				}
				
				i-- ;
			}
			
			nLength = wcslen( wszFileParentDir ) ;
			if ( nLength > 0 && wszFileParentDir[nLength-1] != L'\\' )
			{
				wszFileParentDir[nLength-1] = L'\\' ;
				wszFileParentDir[nLength] = L'\0' ;
			}
			
			return TRUE ;	
		}
		else
		{
			return FALSE ;
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		wcscpy( wszFileParentDir , L"" ) ;
		return FALSE ;
	}
}

BOOL GetFileParentDirA( OUT char *cFileParentDir , IN char *cSrcFileName )
{
	if ( cSrcFileName == NULL || cFileParentDir == NULL )
	{
		return FALSE ;
	}
	
	__try
	{
		char cTempFileName[MAX_PATH] ;
		strcpy( cTempFileName , cSrcFileName ) ;		
			
		char cFileTitle[MAX_PATH] ;
		if ( GetFileShortNameA( cFileTitle , cTempFileName ) )
		{
			strcpy( cFileParentDir , cSrcFileName ) ;
			
			int nLength = strlen( cFileParentDir ) ;
			int i = nLength ;
			while ( i >= 0 )
			{
				if ( strstr( cFileParentDir+i , cFileTitle ) )
				{
					*(cFileParentDir+i) = '\0' ;
					break ;
				}
				
				i-- ;
			}
			
			nLength = strlen( cFileParentDir ) ;
			if ( nLength > 0 && cFileParentDir[nLength-1] != '\\' )
			{
				cFileParentDir[nLength-1] = '\\' ;
				cFileParentDir[nLength] = '\0' ;
			}
			
			return TRUE ;	
		}
		else
		{
			return FALSE ;
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		strcpy( cFileParentDir , "" ) ;
		return FALSE ;
	}
}

BOOL GetFileShortNameW( OUT WCHAR *wszFileShortName , IN WCHAR *wszSrcFileName )
{
	if ( wszSrcFileName == NULL || wszFileShortName == NULL )
	{
		return FALSE ;
	}

	__try
	{
		WCHAR wszTempFileName[MAX_PATH] ;
		wcscpy( wszTempFileName , wszSrcFileName ) ;
		
		WCHAR wszFileTitle[MAX_PATH] ;
		if ( GetFileTitleW( wszTempFileName , wszFileTitle , MAX_PATH ) != 0 )
		{
			return FALSE ;
		}
		else
		{
			WCHAR *wsztempch = wcsrchr( wszTempFileName , L'\\' ) ;
			if ( wsztempch )
			{
				wcscpy( wszFileShortName , wsztempch+1 ) ;
			}
			else
			{
				wcscpy( wszFileShortName , wszTempFileName ) ;
			}
				
			return TRUE ;		
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE ;
	}
}

BOOL GetFileShortNameA( OUT char *cFileShortName , IN char *cSrcFileName )
{
	if ( cSrcFileName == NULL || cFileShortName == NULL )
	{
		return FALSE ;
	}

	__try
	{
		char cTempFileName[MAX_PATH] ;
		strcpy( cTempFileName , cSrcFileName ) ;
			
		char cFileTitle[MAX_PATH] ;
		if ( GetFileTitleA( cTempFileName , cFileTitle , MAX_PATH ) != 0 )
		{
			return FALSE ;
		}
		else
		{
			char *ctempch = strrchr( cTempFileName , '\\' ) ;
			if ( ctempch )
			{
				strcpy( cFileShortName , ctempch+1 ) ;
			}
			else
			{
				strcpy( cFileShortName , cTempFileName ) ;
			}
				
			return TRUE ;		
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE ;
	}
}

void GetFileExtNameW( OUT WCHAR *wszExtName , IN WCHAR *wszSrcFileName )
{
	if ( wszSrcFileName == NULL || wszExtName == NULL )
	{
		return ;
	}

	__try
	{
		WCHAR wszTempFileName[MAX_PATH] ;
		wcscpy( wszTempFileName , wszSrcFileName ) ;
	
		int nLength = wcslen( wszTempFileName ) ;
		if ( wszTempFileName[nLength-1] == L'\\' )
		{
			wszTempFileName[nLength-1] = L'\0' ;
		}
		
		wcscpy( wszExtName , L"" ) ;

		WCHAR wszFileTitle[MAX_PATH] ;
		if ( GetFileShortNameW( wszFileTitle , wszTempFileName ) )
		{
			WCHAR *wcsTemp = wcsrchr( wszFileTitle , L'.' ) ;
			if ( wcsTemp )
			{
				nLength = wcslen( wcsTemp+1 ) ;
				if ( nLength > 9 )
				{
					wcsncpy( wszExtName , wcsTemp+1 , 9 ) ;
					wszExtName[9] = L'\0' ;
				}
				else
				{
					wcscpy( wszExtName , wcsTemp+1 ) ;
				}
			}
		}	
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		wcscpy( wszExtName , L"" ) ;
		return ;
	}
}

void GetFileExtNameA( OUT char *cExtName , IN char *cSrcFileName )
{
	if ( cSrcFileName == NULL || cExtName == NULL )
	{
		return ;
	}
	
	__try
	{
		char cTempFileName[MAX_PATH] ;
		strcpy( cTempFileName , cSrcFileName ) ;
		
		int nLength = strlen( cTempFileName ) ;
		if ( cTempFileName[nLength-1] == '\\' )
		{
			cTempFileName[nLength-1] = '\0' ;
		}

		strcpy( cExtName , "" ) ;

		char cFileTitle[MAX_PATH] ;
		if ( GetFileShortNameA( cFileTitle , cTempFileName ) )
		{
			char *cTemp = strrchr( cFileTitle , '.' ) ;
			if ( cTemp )
			{
				nLength = strlen( cTemp+1 ) ;
				if ( nLength > 9 )
				{
					strncpy( cExtName , cTemp+1 , 9 ) ;
					cExtName[9] = '\0' ;
				}
				else
				{
					strcpy( cExtName , cTemp+1 ) ;
				}
			}
		}
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		strcpy( cExtName , "" ) ;
		return ;
	}
}

void SetFileExtNameW( WCHAR *wszFileName , WCHAR *wszExtName )
{
	if ( wszFileName == NULL || wszExtName == NULL )
	{
		return ;
	}
	
	__try
	{
		WCHAR wszTempFileName[MAX_PATH] ;
		wcscpy( wszTempFileName , wszFileName ) ;
		int nLength = wcslen( wszTempFileName ) ;
		if ( wszTempFileName[nLength-1] == L'\\' )
		{
			wszTempFileName[nLength-1] = L'\0' ;
		}
		
		if ( *wszExtName == L'.' )
		{
			wszExtName++ ;
		}

		WCHAR *wszTemp = wcsrchr( wszTempFileName , L'.' ) ;
		if ( wszTemp )
		{
			wcscpy( wszTemp+1 , wszExtName ) ;
		}
		else
		{
			wcscat( wszTempFileName , L"." ) ;
			wcscat( wszTempFileName , wszExtName ) ;
		}

		wcscpy( wszFileName , wszTempFileName ) ;
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return ;
	}
}

void SetFileExtNameA( char *cFileName , char *cExtName )
{
	if ( cFileName == NULL || cExtName == NULL )
	{
		return ;
	}

	__try
	{
		char cTempFileName[MAX_PATH] ;
		strcpy( cTempFileName , cFileName ) ;
		int nLength = strlen( cTempFileName ) ;
		if ( cTempFileName[nLength-1] == '\\' )
		{
			cTempFileName[nLength-1] = '\0' ;
		}
		
		if ( *cExtName == '.' )
		{
			cExtName++ ;
		}

		char *cTemp = strrchr( cTempFileName , '.' ) ;
		if ( cTemp )
		{
			strcpy( cTemp+1 , cExtName ) ;
		}
		else
		{
			strcat( cTempFileName , "." ) ;
			strcat( cTempFileName , cExtName ) ;
		}

		strcpy( cFileName , cTempFileName ) ;
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return ;
	}
}

BOOL IsMediaPlayVersionUpperThan90()
{
	HKEY hKEY ;
	LPCTSTR data_Set = _T("SOFTWARE\\Microsoft\\MediaPlayer\\Setup\\Installed Versions") ; 
	long ret0 = ( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE , data_Set , 
					0 , KEY_READ , &hKEY ) ) ; 
	if( ret0 != ERROR_SUCCESS ) 
	{ 
		RegCloseKey( hKEY ) ;
		return FALSE ; 
	}  
	DWORD type ;
	unsigned char Data[MAX_PATH] ;
	DWORD size = MAX_PATH ;
	long ret1 = ::RegQueryValueEx( hKEY , _T("wmplayer.exe") , NULL , &type , 
				Data , &size ) ;
	if ( ret1 != ERROR_SUCCESS )
	{
		RegCloseKey( hKEY ) ;
		return FALSE ;
	}
	
	if ( Data[2] < 0x09 )
	{
		RegCloseKey( hKEY ) ;
		return FALSE ;
	}

	RegCloseKey( hKEY ) ;

	return TRUE ;		
}

BOOL IsDirectShowVersionUpperThan90()
{
	HKEY hKEY ;
	LPCTSTR data_Set = _T("SOFTWARE\\Microsoft\\DirectX") ; 
	long ret0 = ( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE , data_Set , 
					0 , KEY_READ , &hKEY ) ) ; 
	if( ret0 != ERROR_SUCCESS ) 
	{ 
		RegCloseKey( hKEY ) ;
		return FALSE ; 
	}  
	DWORD type ;
	unsigned char Data[MAX_PATH] ;
	DWORD size = MAX_PATH ;
		
	long ret1 = ::RegQueryValueEx( hKEY , _T("InstalledVersion") , NULL , &type , 
				Data , &size ) ;
	if ( ret1 != ERROR_SUCCESS )
	{
		RegCloseKey( hKEY ) ;
		return FALSE ;
	}
	
	if ( Data[3] < 0x09 )
	{
		RegCloseKey( hKEY ) ;
		return FALSE ;
	}

	RegCloseKey( hKEY ) ;

	return TRUE ;	
}

CRect GetTriangleRect( TRIANGLE mTriangle )
{
	CRect rc  ;
	rc.left = Get3Min( mTriangle.p1.x , mTriangle.p2.x , mTriangle.p3.x ) ;
	rc.right = Get3Max( mTriangle.p1.x , mTriangle.p2.x , mTriangle.p3.x ) ;
	rc.top = Get3Min( mTriangle.p1.y , mTriangle.p2.y , mTriangle.p3.y ) ;
	rc.bottom = Get3Max( mTriangle.p1.y , mTriangle.p2.y , mTriangle.p3.y ) ;
	return rc ;
}

void BubbleSortForStrings( TCHAR **SortStrings , 
						   int nSortNumber )
{
	TCHAR tempString[MAX_PATH] ; //if the string to be sorted is longer than MAX_PATH
								 //please change this number

	BOOL bMoved = FALSE ;
	for ( int i = 0 ; i < nSortNumber-1 ; i++)
	{
		bMoved = FALSE ;
		for ( int j = 0 ; j < nSortNumber - i -1 ; j++)
		{
			if ( _tcsicmp( SortStrings[j+1] , _T("..") ) == 0 )
			{
				_tcscpy( tempString , SortStrings[j] ) ;
				_tcscpy( SortStrings[j] , SortStrings[j+1] ) ;
				_tcscpy( SortStrings[j+1] , tempString ) ;

				bMoved = TRUE ;
			}
			else if ( _tcsicmp( SortStrings[j] , SortStrings[j+1] ) > 0 &&
				      _tcsicmp( SortStrings[j] , _T("..") ) != 0 )
			{
				_tcscpy( tempString , SortStrings[j] ) ;
				_tcscpy( SortStrings[j] , SortStrings[j+1] ) ;
				_tcscpy( SortStrings[j+1] , tempString ) ;

				bMoved = TRUE ;
			}
		}

		if ( !bMoved )
		{
			break ;
		}
	}
}

void SortStrings( TCHAR **SortStrings , int nSortNumber )
{
	BubbleSortForStrings( SortStrings , nSortNumber ) ;
}

LONGLONG GetFileSizeLongA( char *cFileName )
{
	if ( cFileName == NULL )
	{
		return 0 ;
	}
	
	TCHAR cTempFileName[MAX_PATH] ;
#ifdef UNICODE
	MB2WC( cTempFileName , cFileName , MAX_PATH ) ;
#else 
	strcpy( cTempFileName , cFileName ) ;
#endif
	
	WIN32_FIND_DATA win32_find_data ;
	HANDLE hFindFileDir = FindFirstFile(cTempFileName , &win32_find_data) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return 0 ;
	}
	
	FindClose( hFindFileDir ) ;

	if ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return 0 ;
	}
	
	DWORD dwLowerSize , dwHigherSize ;
	dwLowerSize = win32_find_data.nFileSizeLow ;
	dwHigherSize = win32_find_data.nFileSizeHigh ;

	if ( dwLowerSize == INVALID_FILE_SIZE )
	{
		dwLowerSize = 0 ;
		dwHigherSize = 0 ;
	}	

	LONGLONG lFileSize = 0 ;
	lFileSize = dwHigherSize ;
	lFileSize = lFileSize * 16*16*16*16*16*16*16*16 ;
	lFileSize += dwLowerSize ;	

	return lFileSize ;
}

LONGLONG GetFileSizeLongW( WCHAR *wszFileName )
{
	if ( wszFileName == NULL )
	{
		return 0 ;
	}

	TCHAR cTempFileName[MAX_PATH] ;
#ifdef UNICODE
	wcscpy( cTempFileName , wszFileName ) ;	
#else 
	WC2MB( cTempFileName , wszFileName , MAX_PATH ) ;
#endif
	
	WIN32_FIND_DATA win32_find_data ;
	HANDLE hFindFileDir = FindFirstFile(cTempFileName , &win32_find_data) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return 0 ;
	}

	FindClose( hFindFileDir ) ;

	if ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return 0 ;
	}
	
	DWORD dwLowerSize , dwHigherSize ;
	dwLowerSize = win32_find_data.nFileSizeLow ;
	dwHigherSize = win32_find_data.nFileSizeHigh ;

	if ( dwLowerSize == INVALID_FILE_SIZE )
	{
		dwLowerSize = 0 ;
		dwHigherSize = 0 ;
	}	

	LONGLONG lFileSize = 0 ;
	lFileSize = dwHigherSize ;
	lFileSize = lFileSize * 16*16*16*16*16*16*16*16 ;
	lFileSize += dwLowerSize ;	

	return lFileSize ;
}

void DumpMessage( BOOL* pEndFlagPtr , DWORD dwDelayTime )
{
	MSG msg;
	
	DWORD dwCurTime = GetTickCount() ;
	
	while ( 1 )
	{
		if ( pEndFlagPtr ) 
		{
			if ( (*pEndFlagPtr) == FALSE )
			{
				break ;
			}
		}
		
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if ( (GetTickCount() - dwCurTime) > dwDelayTime )
		{
			break ;
		}
	}
}

BOOL RegisterFilter(TCHAR *cilterFileName)
{
	typedef int(WINAPI *REGISTER_FUNC) (void) ;
	REGISTER_FUNC	MyFunc = NULL ;
	HMODULE hModule = ::LoadLibrary( cilterFileName ) ;
	if ( hModule )
	{
		MyFunc = (REGISTER_FUNC) GetProcAddress( hModule , "DllRegisterServer" ) ;
		BOOL pass = (MyFunc != NULL) ;
		if ( pass )
		{
			MyFunc() ;
		}
		::FreeLibrary( hModule ) ;

		return pass ;
	}

	return FALSE ;
}

char  *GetLastPosInStringA( char *cDestString , int nDestLength ,
						    char *cSearchString , int nSearchLength )
{
	if ( !cDestString || !cSearchString )
	{
		return NULL ;
	}

	if ( nDestLength < nSearchLength )
	{
		return NULL ;
	}
	
	__try
	{
		int nDestSearchNumber=0 ;
	
		while ( nDestSearchNumber < nDestLength )
		{
			char *ctempSearch = cSearchString ;
			char *ctempDest = cDestString+nDestSearchNumber ;

			int  nSameNumber = 0;
			int  nSearchNumber = 0 ;
			while ( (*ctempSearch == *ctempDest)||
					((*ctempSearch>='A')&&(*ctempSearch<='Z')&&(*ctempDest==*ctempSearch+32)) ||
					((*ctempSearch>='a')&&(*ctempSearch<='z')&&(*ctempDest==*ctempSearch-32)) )
			{
				if ( nSearchNumber >= nSearchLength )
				{
					return ctempDest ;
				}

				ctempSearch ++ ;
				ctempDest ++ ;
				
				nSameNumber ++ ;
				nSearchNumber ++ ;
			}
			if ( nSearchNumber >= nSearchLength )
			{
				return ctempDest ;
			}

			if ( nSameNumber == 0 )
			{
				nDestSearchNumber ++ ;
				nSearchNumber ++ ;
			}
			else
			{
				nDestSearchNumber += nSameNumber ;	
			}
		}

		return NULL ;
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return NULL ;
	}
}

WCHAR *GetLastPosInStringW( WCHAR *cDestString , int nDestLength ,
						    WCHAR *cSearchString , int nSearchLength )
{
	if ( !cDestString || !cSearchString )
	{
		return NULL ;
	}

	if ( nDestLength < nSearchLength )
	{
		return NULL ;
	}
	
	__try
	{
		int nDestSearchNumber=0 ;
	
		while ( nDestSearchNumber < nDestLength )
		{
			WCHAR *ctempSearch = cSearchString ;
			WCHAR *ctempDest = cDestString+nDestSearchNumber ;

			int  nSameNumber = 0;
			int  nSearchNumber = 0 ;
			while ( (*ctempSearch == *ctempDest)||
					((*ctempSearch>=L'A')&&(*ctempSearch<=L'Z')&&(*ctempDest==*ctempSearch+32)) ||
					((*ctempSearch>=L'a')&&(*ctempSearch<=L'z')&&(*ctempDest==*ctempSearch-32)) )
			{
				if ( nSearchNumber >= nSearchLength )
				{
					return ctempDest ;
				}

				ctempSearch ++ ;
				ctempDest ++ ;
				
				nSameNumber ++ ;
				nSearchNumber ++ ;
			}
			if ( nSearchNumber >= nSearchLength )
			{
				return ctempDest ;
			}

			if ( nSameNumber == 0 )
			{
				nDestSearchNumber ++ ;
				nSearchNumber ++ ;
			}
			else
			{
				nDestSearchNumber += nSameNumber ;	
			}
		}

		return NULL ;
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return NULL ;
	}
}

BOOL IsValidFileName( TCHAR *cFileName )
{
	if ( !cFileName )
	{
		return FALSE ;
	}

	TCHAR cSpecialChar[] = _T("\\/:*?\"<>|") ;

	TCHAR *tempch = cSpecialChar ;
	while ( *tempch )
	{
		if ( _tcschr( cFileName , *tempch ) )
		{
			return FALSE ;
		}

		tempch ++ ;
	}
	
	return TRUE ;
}

BOOL IsFileDirectoryW(WCHAR *wszFileName)
{
	if ( !wszFileName )
	{
		return FALSE ;
	}
	
	WCHAR wszTempFileName[MAX_PATH] ;
	wcscpy( wszTempFileName , wszFileName ) ;
	int nLength = wcslen( wszTempFileName ) ;
	if ( nLength > 0 && wszTempFileName[nLength-1] == L'\\' )
	{
		wszTempFileName[nLength-1] = L'\0' ;
	}
	
	if ( IsDriverW( wszTempFileName ) )
	{
		return TRUE ;
	}
	
	WIN32_FIND_DATAW win32_find_dataw ;
	HANDLE hFindFileDir = FindFirstFileW(wszTempFileName , &win32_find_dataw) ;
	
	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		if ( wcsicmp( wszTempFileName , L"" ) != 0 )
		{
			WCHAR wszChildFileName[MAX_PATH] ;
			wcscpy( wszChildFileName , wszTempFileName ) ;		
			wcscat( wszChildFileName , L"\\*.*" ) ;
			hFindFileDir = FindFirstFileW( wszChildFileName , &win32_find_dataw ) ;
			if ( hFindFileDir == INVALID_HANDLE_VALUE )
			{
				return FALSE ;
			}
			else
			{
				FindClose( hFindFileDir ) ;
				return TRUE ;
			}
		}
		return FALSE ;
	}
	else
	{
		FindClose( hFindFileDir ) ;
		
		if ( win32_find_dataw.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			return TRUE ;
		}
		return FALSE ;
	}	
}

BOOL IsFileDirectoryA(char *cFileName)
{
	if ( !cFileName )
	{
		return FALSE ;
	}

	char cTempFileName[MAX_PATH] ;
	strcpy( cTempFileName , cFileName ) ;
	int nLength = strlen( cTempFileName ) ;
	if ( nLength > 0 && cTempFileName[nLength-1] == '\\' )
	{
		cTempFileName[nLength-1] = '\0' ;
	}

	if ( IsDriverA( cTempFileName ) )
	{
		return TRUE ;
	}

	WIN32_FIND_DATAA win32_find_dataa ;
	HANDLE hFindFileDir = FindFirstFileA(cTempFileName , &win32_find_dataa) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		if ( stricmp( cTempFileName , "" ) != 0 )
		{
			char cChildFileName[MAX_PATH] ;
			strcpy( cChildFileName , cTempFileName ) ;		
			strcat( cChildFileName , "\\*.*" ) ;
			hFindFileDir = FindFirstFileA( cChildFileName , &win32_find_dataa ) ;
			if ( hFindFileDir == INVALID_HANDLE_VALUE )
			{
				return FALSE ;
			}
			else
			{
				FindClose( hFindFileDir ) ;
				return TRUE ;
			}
		}
		return FALSE ;
	}
	else
	{
		FindClose( hFindFileDir ) ;

		if ( win32_find_dataa.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			return TRUE ;
		}
		return FALSE ;
	}	
}

BOOL IsFileArchiveW(WCHAR *wszFileName)
{
	if ( !wszFileName )
	{
		return FALSE ;
	}
	
	WCHAR wszTempFileName[MAX_PATH] ;
	wcscpy( wszTempFileName , wszFileName ) ;
	int nLength = wcslen( wszTempFileName ) ;
	if ( nLength > 0 && wszTempFileName[nLength-1] == L'\\' )
	{
		wszTempFileName[nLength-1] = L'\0' ;
	}
	
	WIN32_FIND_DATAW win32_find_dataw ;
	HANDLE hFindFileDir = FindFirstFileW(wszTempFileName , &win32_find_dataw) ;
	
	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return FALSE ;
	}
	
	FindClose( hFindFileDir ) ;
	
	if ( win32_find_dataw.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return FALSE ;
	}
	
	return TRUE ;	
}

BOOL IsFileArchiveA(char *cFileName)
{
	if ( !cFileName )
	{
		return FALSE ;
	}
	
	char cTempFileName[MAX_PATH] ;
	strcpy( cTempFileName , cFileName ) ;
	int nLength = strlen( cTempFileName ) ;
	if ( nLength > 0 && cTempFileName[nLength-1] == '\\' )
	{
		cTempFileName[nLength-1] = '\0' ;
	}

	WIN32_FIND_DATAA win32_find_dataa ;
	HANDLE hFindFileDir = FindFirstFileA(cTempFileName , &win32_find_dataa) ;

	if ( hFindFileDir == INVALID_HANDLE_VALUE )
	{
		return FALSE ;
	}

	FindClose( hFindFileDir ) ;

	if ( win32_find_dataa.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		return FALSE ;
	}

	return TRUE ;	
}

BOOL IsDriverW( WCHAR *wszFileName )
{
	if ( !wszFileName )
	{
		return FALSE ;
	}
	
	WCHAR wszTempFileName[MAX_PATH] ;
	wcscpy( wszTempFileName , wszFileName ) ;
	int nLength = wcslen( wszTempFileName ) ;
	if ( wszTempFileName[nLength-1] == L'\\' )
	{
		wszTempFileName[nLength-1] = L'\0' ;
	}
	
	DWORD drives = GetLogicalDrives();
	if (drives != 0)
	{
		UINT flags = SHGFI_DISPLAYNAME;
		CString driveDesc;
		WCHAR wszdriveName[] = L"A:\\";
		WCHAR wszdriveLetter = L'A';
		long bits = 1;
		int size = sizeof(drives) * 8;
		for (int i=0; i<size; i++)
		{			
			wszdriveName[0] = wszdriveLetter;
			
			if (drives & bits)
			{
				WCHAR wszDriverPath[MAX_PATH] ;
				wcscpy( wszDriverPath , wszdriveName ) ;
				int nLength = wcslen( wszDriverPath ) ;
				if ( nLength > 0 )
				{
					if ( wszDriverPath[nLength-1] == L'\\' )
					{
						wszDriverPath[nLength-1] = L'\0' ;
					}
				}
				
				if ( wcsicmp( wszDriverPath , wszTempFileName ) == 0 )
				{
					return TRUE ;
				}			
			}
			
			bits = bits << 1;
			wszdriveLetter += 1;
		}
	}
	
	return FALSE ;
}

BOOL IsDriverA( char *cFileName )
{
	if ( !cFileName )
	{
		return FALSE ;
	}
	
	char cTempFileName[MAX_PATH] ;
	strcpy( cTempFileName , cFileName ) ;
	int nLength = strlen( cTempFileName ) ;
	if ( cTempFileName[nLength-1] == '\\' )
	{
		cTempFileName[nLength-1] = '\0' ;
	}
	
	DWORD drives = GetLogicalDrives();
	if (drives != 0)
	{
		UINT flags = SHGFI_DISPLAYNAME;
		CString driveDesc;
		char cdriveName[] = "A:\\";
		char cdriveLetter = 'A';
		long bits = 1;
		int size = sizeof(drives) * 8;
		for (int i=0; i<size; i++)
		{			
			cdriveName[0] = cdriveLetter;
			
			if (drives & bits)
			{
				char cDriverPath[MAX_PATH] ;
				strcpy( cDriverPath , cdriveName ) ;
				int nLength = strlen( cDriverPath ) ;
				if ( nLength > 0 )
				{
					if ( cDriverPath[nLength-1] == '\\' )
					{
						cDriverPath[nLength-1] = '\0' ;
					}
				}
				
				if ( stricmp( cDriverPath , cTempFileName ) == 0 )
				{
					return TRUE ;
				}			
			}
			
			bits = bits << 1;
			cdriveLetter += 1;
		}
	}
	
	return FALSE ;
}

void GetDriverList(TCHAR *cDriverList[100] , int &nDriverNumber)
{
	nDriverNumber = 0 ;
	
	if ( !cDriverList )
	{
		return ;
	}
	
	DWORD drives = GetLogicalDrives();
	if (drives != 0)
	{
		CString driveDesc;
		TCHAR driveName[] = _T("A:\\");
		TCHAR driveLetter = _T('A');
		long bits = 1;
		int size = sizeof(drives) * 8;
		for (int i=0; i<size; i++)
		{			
			driveName[0] = driveLetter;
			
			if (drives & bits)
			{
				TCHAR cDriverPath[MAX_PATH] ;
				_tcscpy( cDriverPath , driveName ) ;
				int nLength = _tcslen( cDriverPath ) ;
				if ( nLength > 0 )
				{
					if ( cDriverPath[nLength-1] == _T('\\') )
					{
						cDriverPath[nLength-1] = _T('\0') ;
					}
				}

				cDriverList[nDriverNumber] = new TCHAR[MAX_PATH] ;
				if ( cDriverList[nDriverNumber] )
				{
					_tcscpy( cDriverList[nDriverNumber] , cDriverPath ) ;
					nDriverNumber ++ ;

					if ( nDriverNumber >= 100 )
					{
						break ;
					}
				}
			}
			
			bits = bits << 1;
			driveLetter += 1;
		}
	}
}

void GetLocalFileList(TCHAR *cFolder ,
					  TCHAR *cSortedFolderList[10000] ,
					  TCHAR *cSortedFileList[10000] ,
					  int *nFolderNumber ,
					  int *nFileNumber )
{
	if ( nFolderNumber )
	{
		*nFolderNumber = 0 ;
	}
	if ( nFileNumber )
	{
		*nFileNumber = 0 ;
	}	
	
	int nTempFolderNumber=0 , nTempFileNumber=0 ;

	if ( !cFolder )
	{
		return ;
	}

	TCHAR cTempFolder[MAX_PATH] ;
	_tcscpy( cTempFolder , cFolder ) ;
	int nLength = _tcslen( cTempFolder ) ;
	if ( nLength > 0 && cTempFolder[nLength-1] == _T('\\') )
	{
		cTempFolder[nLength-1] = _T('\0') ;
	}

	TCHAR cFileName[MAX_PATH] ;
	_tcscpy(cFileName , cFolder) ;
	
	_tcscat(cFileName , _T("\\*.*")) ;	

	cSortedFolderList[nTempFolderNumber] = new TCHAR[MAX_PATH] ;
	if ( cSortedFolderList[nTempFolderNumber] )
	{
		_tcscpy( cSortedFolderList[nTempFolderNumber] , _T("..") ) ;
		nTempFolderNumber++ ;
	}
	
	WIN32_FIND_DATA win32_find_data ;
	HANDLE hFindFileDir = FindFirstFile(cFileName , &win32_find_data) ;
	
	if (hFindFileDir != INVALID_HANDLE_VALUE)
	{
		BOOL FindDirOK = TRUE ;
		
		while (FindDirOK)
		{
			int nFileType = -1 ; //0--folder 1--file , other not support

			if ( _tcscmp( win32_find_data.cFileName , _T(".") ) == 0 ||
				_tcscmp( win32_find_data.cFileName , _T("..") ) == 0 ||
				_tcscmp( win32_find_data.cFileName , _T("") ) == 0 )
			{
				FindDirOK = FindNextFile(hFindFileDir , &win32_find_data) ;
				continue ;
			}
			else if ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if ( IsLNKFileType( win32_find_data.cFileName ) )
				{
					TCHAR cFullFilePath[MAX_PATH] ;
					_tcscpy( cFullFilePath , cTempFolder ) ;
					_tcscat( cFullFilePath , _T("\\") ) ;
					_tcscat( cFullFilePath , win32_find_data.cFileName ) ;
					
					TCHAR cLnkFilePath[MAX_PATH] ;
					if ( GetLNKFilePath( cLnkFilePath , cFullFilePath ) )
					{
						_tcscpy( cFullFilePath , cLnkFilePath ) ;
					}

					if ( IsFileDirectory( cFullFilePath ) )
					{
						nFileType = 0 ;
					}
					else
					{
						nFileType = 1 ;
					}
				}
				else
				{
					nFileType = 0 ;
				}
			}
			else
			{
				nFileType = 1 ;			
			}

			if ( nFileType == 0 )
			{
				if ( cSortedFolderList )
				{
					cSortedFolderList[nTempFolderNumber] = new TCHAR[MAX_PATH] ;
					if ( cSortedFolderList[nTempFolderNumber] )
					{
						_tcscpy( cSortedFolderList[nTempFolderNumber] , win32_find_data.cFileName ) ;
					
						nTempFolderNumber ++ ;
						if ( nTempFolderNumber >= 10000 )
						{
							break ;
						}
					}
				}
			}
			else if ( nFileType == 1 )
			{
				if ( cSortedFileList )
				{
					cSortedFileList[nTempFileNumber] = new TCHAR[MAX_PATH] ;
					if ( cSortedFileList[nTempFileNumber] )
					{
						_tcscpy( cSortedFileList[nTempFileNumber] , win32_find_data.cFileName ) ;
					
						nTempFileNumber ++ ;
						if ( nTempFileNumber >= 10000 )
						{
							break ;
						}
					}
				}
			}
			
			FindDirOK = FindNextFile(hFindFileDir , &win32_find_data) ;
		}
		FindClose(hFindFileDir) ;
	}	
	
	if ( cSortedFolderList )
	{
		SortStrings( (TCHAR**)cSortedFolderList , nTempFolderNumber ) ;	
	}
	if ( cSortedFileList )
	{
		SortStrings( (TCHAR**)cSortedFileList , nTempFileNumber ) ;	
	}	

	if ( nFolderNumber )
	{
		*nFolderNumber = nTempFolderNumber ;
	}
	if ( nFileNumber )
	{
		*nFileNumber = nTempFileNumber ;
	}
}

void CreateMultiDirectory( TCHAR *cFolderName )
{
	if ( !cFolderName )
	{
		return ;
	}
	
	TCHAR cFolderPath[MAX_PATH] ;
	
	if ( IsFileArchive( cFolderName ) )
	{
		GetFileParentDir( cFolderPath , cFolderName ) ;
	}
	else
	{
		_tcscpy( cFolderPath , cFolderName ) ;
	}
	
	int nLength = _tcslen( cFolderPath ) ;
	if ( nLength > 0 && cFolderPath[nLength-1] == _T('\\') )
	{
		cFolderPath[nLength-1] = _T('\0') ;
	}

	if ( !IsFileDirectory( cFolderPath ) )
	{
		TCHAR cParentFolder[MAX_PATH] ;
		if ( GetFileParentDir( cParentFolder , cFolderPath ) )
		{
			CreateMultiDirectory( cParentFolder ) ;
			CreateDirectory( cFolderPath , NULL ) ;			
		}
	}
}

void DelFolderTree( TCHAR *cFolderName )
{
	if ( !cFolderName )
	{
		return ;
	}
	
	TCHAR cFolderPath[MAX_PATH] ;
	if ( IsFileArchive( cFolderName ) )
	{
		GetFileParentDir( cFolderPath , cFolderName ) ;
	}
	else
	{
		_tcscpy( cFolderPath , cFolderName ) ;
	}

	int nLength = _tcslen( cFolderPath ) ;
	if ( nLength > 0 && cFolderPath[nLength-1] == _T('\\') )
	{
		cFolderPath[nLength-1] = _T('\0') ;
	}

	TCHAR cFinderFile[MAX_PATH] ;
	_tcscpy( cFinderFile , cFolderPath ) ;
	_tcscat( cFinderFile , _T("\\*.*") ) ;

	WIN32_FIND_DATA win32_find_data_dir ;
	HANDLE hFindFileDir = FindFirstFile(cFinderFile , &win32_find_data_dir) ;

	if (hFindFileDir != INVALID_HANDLE_VALUE)
	{
		BOOL FindDirOK = TRUE ;
			
		while (FindDirOK)
		{
			if ( _tcscmp( win32_find_data_dir.cFileName , _T(".")) == 0 ||
				 _tcscmp( win32_find_data_dir.cFileName , _T("..")) == 0 )
			{
				FindDirOK = FindNextFile(hFindFileDir , &win32_find_data_dir) ;
				continue ;
			}
			else if ( win32_find_data_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				TCHAR cChildFile[MAX_PATH] ;
				_tcscpy( cChildFile , cFolderPath ) ;
				_tcscat( cChildFile , _T("\\") ) ;
				_tcscat( cChildFile , win32_find_data_dir.cFileName ) ;				

				DelFolderTree( cChildFile ) ;
				RemoveDirectory( cChildFile ) ;	
				FindDirOK = FindNextFile(hFindFileDir , &win32_find_data_dir) ;
				continue ;
			}
			else
			{
				TCHAR cChildFile[MAX_PATH] ;
				_tcscpy( cChildFile , cFolderPath ) ;
				_tcscat( cChildFile , _T("\\") ) ;
				_tcscat( cChildFile , win32_find_data_dir.cFileName ) ;		
				
				DeleteFile( cChildFile ) ;
				FindDirOK = FindNextFile(hFindFileDir , &win32_find_data_dir) ;
				continue ;
			}
		}
	}

	FindClose( hFindFileDir ) ;
}

void ClearFileContext( TCHAR *cFileName )
{
	if ( !cFileName )
	{
		return ;
	}

	HANDLE hFile = CreateFile( cFileName , GENERIC_WRITE , FILE_SHARE_READ ,
							   NULL , OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL ) ;
	if ( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile ) ;
	}	
}

HBITMAP GetBmpFromImageList(CImageList *pImagelist,int nFaceNumber,COLORREF bkcolor)
{
	if ( !pImagelist )
	{
		return NULL ;
	}
	
	IMAGEINFO ii;
	if ( pImagelist->GetImageInfo(nFaceNumber, &ii) )
	{
		CBitmap dist;
		CClientDC dc(NULL);

		int nWidth = ii.rcImage.right - ii.rcImage.left;
		int nHeight = ii.rcImage.bottom - ii.rcImage.top;

		dist.CreateCompatibleBitmap(&dc, nWidth, nHeight);
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmap = memDC.SelectObject(&dist);
		
		memDC.FillSolidRect(0, 0, nWidth, nHeight, bkcolor );
		pImagelist->Draw(&memDC, nFaceNumber, CPoint(0, 0), ILD_NORMAL);

		memDC.SelectObject(pOldBitmap);

		return (HBITMAP)dist.Detach();
	}
	else
	{
		return NULL ;
	}
}

HBITMAP CopyHBitmap( HBITMAP hSourceBitmap )
{
	if ( !hSourceBitmap )
	{
		return NULL ;
	}
	BYTE *pDib = (BYTE*)DDBtoDIB( hSourceBitmap ) ;
	if ( !pDib )
	{
		return NULL ;
	}

	HBITMAP hBitmap = DIBToDDB( pDib ) ;
	GlobalFree( pDib ) ;

	return hBitmap ;
}

HBITMAP CreateColorBmp( int nWidth , int nHeight , COLORREF clr )
{
	if ( nHeight <= 0 || nWidth <= 0 )
	{
		return NULL ;
	}

	HDC hdc = ::GetDC( NULL ) ;
	HDC destmemdc;
	destmemdc = ::CreateCompatibleDC( hdc ) ;

	HBITMAP hBitmap = ::CreateCompatibleBitmap( hdc , nWidth , nHeight ) ;
	HBITMAP hOldDestBmp = (HBITMAP) ::SelectObject( destmemdc , hBitmap );
	
	CRect destrc( 0 , 0 , nWidth , nHeight ) ;
	LOGBRUSH lbr ;
	lbr.lbColor = clr ;
	lbr.lbStyle = BS_SOLID ;	
	HBRUSH hbrush = CreateBrushIndirect( &lbr ) ;

	::FillRect( destmemdc , &destrc , hbrush );
	
	HBITMAP hDestBmp = (HBITMAP) SelectObject( destmemdc , hOldDestBmp ) ;
	DeleteDC( destmemdc ) ;

	ReleaseDC( NULL , hdc ) ;
	DeleteObject( hbrush ) ;
	return hDestBmp ;
}

HBITMAP ResizeBitmap( HBITMAP hSourceBitmap , int nWidth , int nHeight , COLORREF clrBack )				   
{
	if ( !hSourceBitmap )
	{
		return NULL ;
	}
	if ( nHeight <= 0 || nWidth <= 0 )
	{
		return NULL ;
	}

	BITMAP bm ;
	::GetObject( hSourceBitmap , sizeof(bm) , (void*)&bm ) ;

	double dx , dy , dCoef ;
	dx = (double)(bm.bmWidth) / (double)nWidth ;
	dy = (double)(bm.bmHeight) / (double)nHeight ;
	dCoef = dx > dy ? dx : dy ;
	
	int nDstWidth , nDstHeight , nDstX , nDstY ;
	nDstWidth = (int)((double)(bm.bmWidth) / dCoef) ;
	nDstHeight = (int)((double)(bm.bmHeight) / dCoef) ;
	nDstX = (nWidth - nDstWidth) / 2 ;
	nDstY = (nHeight - nDstHeight) / 2 ;

	HDC hdc = GetDC( NULL ) ;

	HDC destmemdc,sourcememdc;
	destmemdc = ::CreateCompatibleDC( hdc ) ;
	sourcememdc = ::CreateCompatibleDC( hdc ) ;

	HBITMAP hBitmap = CreateCompatibleBitmap( hdc , nWidth , nHeight ) ;
	HBITMAP hOldDestBmp = (HBITMAP) ::SelectObject( destmemdc , hBitmap );
	HBITMAP hOldSourceBmp = (HBITMAP) ::SelectObject( sourcememdc , hSourceBitmap ) ;
	
	CRect destrc( 0 , 0 , nWidth , nHeight ) ;
	LOGBRUSH lbr ;
	lbr.lbColor = clrBack ;
	lbr.lbStyle = BS_SOLID ;	
	HBRUSH hbrush = CreateBrushIndirect( &lbr ) ;

	::FillRect( destmemdc , &destrc , hbrush );

	if ( bm.bmWidth == nDstWidth &&
		 bm.bmHeight == nDstHeight )
	{
		BitBlt( destmemdc , nDstX , nDstY , nDstWidth , nDstHeight ,
				sourcememdc , 0 , 0 , SRCCOPY ) ;
	}
	else
	{
		SetStretchBltMode(destmemdc , COLORONCOLOR) ;
		StretchBlt( destmemdc , nDstX , nDstY , nDstWidth , nDstHeight ,
				sourcememdc , 0 , 0 , bm.bmWidth , bm.bmHeight , SRCCOPY ) ;
	}
	
	HBITMAP hDestBmp = (HBITMAP) SelectObject( destmemdc , hOldDestBmp ) ;
	DeleteDC( destmemdc ) ;
	
	SelectObject( sourcememdc , hOldSourceBmp ) ;
	DeleteDC( sourcememdc ) ;

	DeleteObject( hbrush ) ;

	ReleaseDC( NULL , hdc ) ;

	return hDestBmp ;
}

HBITMAP StretchBitmap( HBITMAP hSourceBitmap , int nWidth , int nHeight )				   
{
	if ( !hSourceBitmap )
	{
		return NULL ;
	}
	if ( nHeight <= 0 || nWidth <= 0 )
	{
		return NULL ;
	}

	BITMAP bm ;
	::GetObject( hSourceBitmap , sizeof(bm) , (void*)&bm ) ;

	HDC hdc = GetDC( NULL ) ;

	HDC destmemdc,sourcememdc;
	destmemdc = ::CreateCompatibleDC( hdc ) ;
	sourcememdc = ::CreateCompatibleDC( hdc ) ;

	HBITMAP hBitmap = ::CreateCompatibleBitmap( hdc , nWidth , nHeight ) ;
	HBITMAP hOldDestBmp = (HBITMAP) ::SelectObject( destmemdc , hBitmap );
	HBITMAP hOldSourceBmp = (HBITMAP) ::SelectObject( sourcememdc , hSourceBitmap ) ;

	if ( bm.bmWidth == nWidth &&
		 bm.bmHeight == nHeight )
	{
		BitBlt( destmemdc , 0 , 0 , nWidth , nHeight ,
				sourcememdc , 0 , 0 , SRCCOPY ) ;
	}
	else
	{
		SetStretchBltMode(destmemdc , COLORONCOLOR) ;
		StretchBlt( destmemdc , 0 , 0 , nWidth , nHeight ,
					sourcememdc , 0 , 0 , bm.bmWidth , bm.bmHeight , SRCCOPY ) ;
	}
	
	HBITMAP hDestBmp = (HBITMAP) SelectObject( destmemdc , hOldDestBmp ) ;
	DeleteDC( destmemdc ) ;
	
	if ( hOldSourceBmp )
	{
		SelectObject( sourcememdc , hOldSourceBmp ) ;
	}
	DeleteDC( sourcememdc ) ;

	ReleaseDC( NULL , hdc ) ;
	
	return hDestBmp ;
}

HBITMAP GetBitmapFromBitmap( HBITMAP hSourceBitmap , int x , int y , int cx , int cy )				   
{
	if ( !hSourceBitmap )
	{
		return NULL ;
	}
	if ( x < 0 || y < 0 || cx <= 0 || cy <= 0 )
	{
		return NULL ;
	}

	BITMAP bm ;
	::GetObject( hSourceBitmap , sizeof(bm) , (void*)&bm ) ;
	
	HDC hdc = ::GetDC( NULL ) ;
	HDC destmemdc,sourcememdc;
	destmemdc = ::CreateCompatibleDC( hdc ) ;
	sourcememdc = ::CreateCompatibleDC( hdc ) ;

	HBITMAP hBitmap = ::CreateCompatibleBitmap( hdc , cx , cy ) ;
	HBITMAP hOldDestBmp = (HBITMAP) ::SelectObject( destmemdc , hBitmap );
	HBITMAP hOldSourceBmp = (HBITMAP) ::SelectObject( sourcememdc , hSourceBitmap ) ;

	CRect destrc( 0 , 0 , cx , cy ) ;
	LOGBRUSH lbr ;
	lbr.lbColor = RGB(0,0,0) ;
	lbr.lbStyle = BS_SOLID ;	
	HBRUSH hbrush = CreateBrushIndirect( &lbr ) ;

	::FillRect( destmemdc , &destrc , hbrush );

	SetStretchBltMode(destmemdc , COLORONCOLOR) ;
	StretchBlt( destmemdc , 0 , 0 , cx , cy ,
				sourcememdc , x , y , cx , cx , SRCCOPY ) ;
	
	BitBlt( destmemdc , 0 , 0 , cx , cy ,
			sourcememdc , 0 , 0 , SRCCOPY ) ;

	HBITMAP hDestBmp = (HBITMAP) SelectObject( destmemdc , hOldDestBmp ) ;
	DeleteDC( destmemdc ) ;
	
	if ( hOldSourceBmp )
	{
		SelectObject( sourcememdc , hOldSourceBmp ) ;
	}
	
	DeleteDC( sourcememdc ) ;

	ReleaseDC( NULL , hdc ) ;
	DeleteObject( hbrush ) ;
	return hDestBmp ;
}

BOOL GetLNKFilePath( TCHAR *lpszLinkToPath , TCHAR *lpszLinkFile ) 
{ 
	if ( !lpszLinkFile || !lpszLinkToPath )
	{
		return FALSE ;
	}

    HRESULT hres; 
    IShellLink* psl; 
    TCHAR szGotPath[MAX_PATH]; 
    WIN32_FIND_DATA wfd; 
 
    *lpszLinkToPath = 0; // assume failure 
 
    // Get a pointer to the IShellLink interface. 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IShellLink, (void **)&psl); 
    if (SUCCEEDED(hres)) 
    { 
        IPersistFile* ppf; 
 
        // Get a pointer to the IPersistFile interface. 
        hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf); 
                 
        if (SUCCEEDED(hres)) 
        { 
            WCHAR wsz[MAX_PATH]; 
 
            // Ensure that the string is Unicode. 
#ifdef UNICODE
			wcscpy( wsz , lpszLinkFile ) ;
#else
			MB2WC( wsz , lpszLinkFile , MAX_PATH ) ;
#endif
			 
            // TODO: Check return value from MultiByteWideChar to ensure 
            //         success.
 
            // Load the shortcut. 
            hres = ppf->Load(wsz, STGM_READ); 
            
            if (SUCCEEDED(hres)) 
            { 
                // Resolve the link. 
               // hres = psl->Resolve(hwnd, 0); 
 
                if (SUCCEEDED(hres)) 
                { 
                    // Get the path to the link target. 
                    hres = psl->GetPath(szGotPath, 
                                        MAX_PATH, 
                                        (WIN32_FIND_DATA*)&wfd, 
                                        SLGP_SHORTPATH); 
 
                    if (hres==NOERROR) 
                    { 
                        // Get the description of the target. 
                        _tcscpy( lpszLinkToPath , szGotPath ) ;
                    }
                } 
            } 
 
            // Release the pointer to the IPersistFile interface. 
            ppf->Release(); 
        } 
 
        // Release the pointer to the IShellLink interface. 
        psl->Release(); 
    } 
    return (hres==NOERROR); 
}

HRESULT ShellCopyFile( HWND hWnd , TCHAR *cSrcFolder , TCHAR *cDestFolder )
{
	SHFILEOPSTRUCT sfo ;
    sfo.hwnd = hWnd ;
    sfo.wFunc = FO_COPY ;
    sfo.pFrom = cSrcFolder ;
    sfo.pTo = cDestFolder ;
    sfo.fFlags = FOF_NOCONFIRMMKDIR ;

	HCURSOR hOldCursor = GetCursor() ;
	HCURSOR hCurCursor = LoadCursor( NULL , IDC_WAIT ) ;
	if ( hCurCursor )
	{
		SetCursor( hCurCursor ) ;
	}

	HRESULT hr = SHFileOperation(&sfo) ;

	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH, (LPCVOID) cDestFolder, 0);
	
	SetCursor( hOldCursor ) ;

    return hr ;
}

Win32SysVersion GetSystemVersion( void )
{
	Win32SysVersion  SysVerType;

	DWORD winVer;
	OSVERSIONINFO *osvi;
	
	winVer=GetVersion();
	if(winVer<0x80000000)
	{
		/*NT */
		SysVerType=WindowsNT3;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		
		if (osvi!=NULL)
		{
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L)
			{
				SysVerType = WindowsNT4;
			}
			else if( (osvi->dwMajorVersion==5L) && (osvi->dwMinorVersion==0L) )
			{
				SysVerType = Windows2000;
			}
			else if( (osvi->dwMajorVersion==5L) && (osvi->dwMinorVersion==1L) )
			{
				SysVerType = WindowsXP;
			}

			free(osvi);
		}
	}
	else if  ( LOBYTE(LOWORD(winVer))<4 )
	{
		SysVerType=Windows32s;
	}
	else
	{
		SysVerType=Windows95;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL)
		{
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if( (osvi->dwMajorVersion==4L) && (osvi->dwMinorVersion==10L) )
			{
				SysVerType=Windows98;
			}
			else if( (osvi->dwMajorVersion==4L) && (osvi->dwMinorVersion==90L) )
			{
				SysVerType=WindowsME;
			}
			free(osvi);
		}
	}
	
	return SysVerType;
}

void SaveHbitmapToFile( HBITMAP hBitmap , TCHAR *cFileName )
{
	if ( !hBitmap || !cFileName )
	{
		return ;
	}

	unsigned char *pBuffer = (unsigned char *)DDBtoDIB( hBitmap ) ;
	if ( !pBuffer )
	{
		return ;
	}

	DWORD nSize = GlobalSize( pBuffer ) ;			
	
	CFile bitmapFile(cFileName, 
		CFile::modeReadWrite | 
		CFile::modeCreate | 
		CFile::typeBinary );
	
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;
	
	lpbi = (LPBITMAPINFOHEADER)pBuffer;
	
	int nColors = 1 << lpbi->biBitCount;
	if (nColors > 256)
		nColors = 0;
	
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	//always is "BM"
	hdr.bfSize		= nSize + sizeof( hdr );
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits	= (DWORD) (sizeof(BITMAPFILEHEADER) + lpbi->biSize +
		nColors * sizeof(RGBQUAD));
	
	bitmapFile.Write(&hdr, sizeof(BITMAPFILEHEADER));
	bitmapFile.Write(pBuffer, nSize);
	bitmapFile.Close();	

	GlobalFree( pBuffer ) ;	
}

HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, COLORREF cTolerance)
{
	HRGN hRgn = NULL;
	
	if (hBmp)
	{
		HDC hMemDC = CreateCompatibleDC(NULL);
		if (hMemDC)
		{
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);
			
			//´´½¨Ò»¸ö32Î»É«µÄÎ»Í¼£¬²¢Ñ¡½øÄÚ´æÉè±¸»·¾³
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {
						sizeof(BITMAPINFOHEADER),		// biSize 
							bm.bmWidth,					// biWidth; 
							bm.bmHeight,				// biHeight; 
							1,							// biPlanes; 
							32,							// biBitCount 
							BI_RGB,						// biCompression; 
							0,							// biSizeImage; 
							0,							// biXPelsPerMeter; 
							0,							// biYPelsPerMeter; 
							0,							// biClrUsed; 
							0							// biClrImportant; 
													};
			VOID * pbits32; 
			HBITMAP hbm32 = CreateDIBSection(hMemDC,(BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);
				
				// Create a DC just to copy the bitmap into the memory DC
				HDC hDC = CreateCompatibleDC(hMemDC);
				if (hDC)
				{
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits)
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32);
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;
					
					// Copy the bitmap into the memory DC
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY);
					
					// For better performances, we will use the ExtCreateRegion() function to create the
					// region. This function take a RGNDATA structure on entry. We will add rectangles by
					// amount of ALLOC_UNIT number in this structure.
#define ALLOC_UNIT	100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
					
					// Keep on hand highest and lowest values for the "transparent" pixels
					BYTE rTolerance = GetRValue(cTolerance) ;
					BYTE gTolerance = GetGValue(cTolerance) ;
					BYTE bTolerance = GetBValue(cTolerance) ;

					BYTE cr = GetRValue(cTransparentColor);
					BYTE cg = GetGValue(cTransparentColor);
					BYTE cb = GetBValue(cTransparentColor);
					
					BYTE lr = max(0x00, cr - rTolerance) ;
					BYTE lg = max(0x00, cg - gTolerance) ;
					BYTE lb = max(0x00, cb - bTolerance) ;
					BYTE hr = min(0xff, cr + rTolerance);
					BYTE hg = min(0xff, cg + gTolerance);
					BYTE hb = min(0xff, cb + bTolerance);
					
					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically)
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to right
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}
							
							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the region
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1;
								pData->rdh.nCount++;
								
								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is too
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps.
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}
						
						// Go to next row (remember, the bitmap is inverted vertically)
						p32 -= bm32.bmWidthBytes;
					}
					
					// Create or extend the region with the remaining rectangles
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;
					
					// Clean up
					GlobalFree(hData);
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}				
				DeleteObject(SelectObject(hMemDC, holdBmp));
			}			
			DeleteDC(hMemDC);
		}
	}	
	return hRgn;	
}

BOOL IsValidUserName( WCHAR *wszUserName )
{
	if ( !wszUserName )
	{
		return FALSE ;
	}

	wszUserName[20] = L'\0' ;
	
	int nLength = wcslen( wszUserName ) ;
	
	BOOL bValid = TRUE ;
	int i = 0 ; 
	while ( i < nLength )
	{
		if ( (wszUserName[i] >= L'A' && wszUserName[i] <= L'Z') ||
			 (wszUserName[i] >= L'a' && wszUserName[i] <= L'z') ||
			 (wszUserName[i] >= L'0' && wszUserName[i] <= L'9') ||
			 (wszUserName[i] == L'_') )
		{
			i++ ;
			continue ;
		}
		else
		{
			bValid = FALSE ;
			break ;
		}

		i ++ ;
	}

	if ( wszUserName[0] >= L'0' && wszUserName[0] <= L'9' ) 
	{
		bValid = FALSE ;
	}

	if ( i == 0 )
	{
		bValid = FALSE ;
	}

	return bValid ;
}

BOOL IsValidDotAddress( WCHAR *wszIPAddress )
{
	if ( !wszIPAddress )
	{
		return FALSE ;
	}

	WCHAR *wszTemp = wszIPAddress ;

	int n = 0 ;
	for ( n=0 ; n < 4 ; n++ )
	{
		WCHAR wszIP[4] ;
		WCHAR *wszDot = wcschr( wszTemp , L'.' ) ;

		if ( !wszDot )
		{
			if ( n < 3 )
			{
				return FALSE ;
			}
			else
			{
				wszDot = wszIPAddress+wcslen(wszIPAddress) ;
			}
		}

		int number = wszDot - wszTemp ;
		if ( number > 3 || number < 1 )
		{
			return FALSE ;
		}

		wcsncpy( wszIP , wszTemp , number ) ;
		wszIP[number] = L'\0' ;
		
		if ( !IsNumber( wszIP ) )
		{
			return FALSE ;
		}

		int nIP = _wtoi( wszIP ) ;
		if ( nIP < 0 || nIP > 255 )
		{
			return FALSE ;
		}

		wszTemp = wszDot + 1 ;		
	}

	return TRUE ;
}

BOOL IsNumber( WCHAR *wszChar )
{
	if ( !wszChar )
	{
		return FALSE ;
	}

	WCHAR *wszTemp = wszChar ;

	while ( *wszTemp )
	{
		if ( *wszTemp < '0' || *wszTemp > '9' )
		{
			return FALSE ;
		}

		wszTemp++ ;
	}

	return TRUE ;
}

void ChangeSysTimeToString(SYSTEMTIME systemTime , TCHAR *cSystemTime)
{
	TCHAR tempchar[11] ;
	CString m_sSendTime ;

	ConvertLongToChar(systemTime.wYear , tempchar , 4) ;
	m_sSendTime = tempchar ;
	m_sSendTime += _T("Äê") ;
	ConvertLongToChar(systemTime.wMonth , tempchar , 2) ;
	m_sSendTime += tempchar ;
	m_sSendTime += _T("ÔÂ") ;
	ConvertLongToChar(systemTime.wDay , tempchar , 2) ;
	m_sSendTime += tempchar ;
	m_sSendTime += _T("ÈÕ,") ;
	
	ConvertLongToChar(systemTime.wHour , tempchar , 2) ;
	m_sSendTime += tempchar ;
	m_sSendTime += _T(":") ;
	ConvertLongToChar(systemTime.wMinute , tempchar , 2) ;
	m_sSendTime += tempchar ;
	m_sSendTime += _T(":") ;
	ConvertLongToChar(systemTime.wSecond , tempchar , 2) ;
	m_sSendTime += tempchar ;
	
	if ( cSystemTime )
	{
		_tcscpy( cSystemTime , m_sSendTime ) ;
	}	
}

int WC2MB( char *mb , WCHAR *wc , int nLength )
{
	if ( !wc || !mb )
	{
		return NULL ;
	}

	return WideCharToMultiByte( CP_ACP , NULL , wc , nLength , mb , nLength , NULL , NULL ) ;
}

int MB2WC( WCHAR *wc , char *mb , int nLength )
{
	if ( !wc || !mb )
	{
		return NULL ;
	}
	return MultiByteToWideChar( CP_ACP , NULL , mb , nLength , wc , nLength ) ;
}

void ConvertCFW2CF(_charformatw cfw, CHARFORMAT &cf)
{
	cf.cbSize = sizeof(CHARFORMAT) ;

	cf.bCharSet = cfw.bCharSet ;
	cf.bPitchAndFamily = cfw.bPitchAndFamily ;
	cf.crTextColor = cfw.crTextColor ;
	cf.dwEffects = cfw.dwEffects ;
	cf.dwMask = cfw.dwMask ;

#if (_RICHEDIT_VER >= 0x0200)
#ifdef UNICODE
	wcscpy( cf.szFaceName , cfw.szFaceName ) ;
#else
	WC2MB( cf.szFaceName , cfw.szFaceName , LF_FACESIZE ) ;
#endif /* UNICODE */
#else
	WC2MB( cf.szFaceName , cfw.szFaceName , LF_FACESIZE ) ;
#endif /* _RICHEDIT_VER >= 0x0200 */

	cf.yHeight = cfw.yHeight ;
	cf.yOffset = cfw.yOffset ;
}

void ConvertCF2CFW( CHARFORMAT cf , _charformatw &cfw )
{
	cfw.cbSize = sizeof(_charformatw) ;

	cfw.bCharSet = cf.bCharSet ;
	cfw.bPitchAndFamily = cf.bPitchAndFamily ;
	cfw.crTextColor = cf.crTextColor ;
	cfw.dwEffects = cf.dwEffects ;
	cfw.dwMask = cf.dwMask ;

#if (_RICHEDIT_VER >= 0x0200)
#ifdef UNICODE
	wcscpy( cfw.szFaceName , cf.szFaceName ) ;
#else
	MB2WC( cfw.szFaceName , cf.szFaceName , LF_FACESIZE ) ;
#endif /* UNICODE */
#else
	MB2WC( cfw.szFaceName , cf.szFaceName , LF_FACESIZE ) ;
#endif /* _RICHEDIT_VER >= 0x0200 */

	cfw.yHeight = cf.yHeight ;
	cfw.yOffset = cf.yOffset ;
}

void ConvertGbToBig5(const WCHAR *wszGbJt,WCHAR *wszBig5)
{
	int nGbJtLen = wcslen(wszGbJt); 
	
	WCHAR *wszGbFt = new WCHAR[nGbJtLen+1]; 
	memset(wszGbFt,0,nGbJtLen+1);
	
	LANGID langid = MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED) ;
	LCID lcid = MAKELCID(langid,SORT_CHINESE_BIG5) ;
	if ( LCMapStringW(lcid,LCMAP_TRADITIONAL_CHINESE,
					wszGbJt,nGbJtLen+1,wszGbFt,nGbJtLen+1) != 0 )
	{
		wcscpy( wszBig5 , wszGbFt ) ;
	}

	delete[] wszGbFt; 	
}

void ConvertBig5ToGb(const WCHAR *wszBig5,WCHAR *wszGbJt)
{
	int nGbBigLen = wcslen(wszBig5); 
	
	WCHAR *wszTempGbJt = new WCHAR[nGbBigLen+1]; 
	memset(wszTempGbJt,0,nGbBigLen+1);
	
	LANGID langid = MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED) ;
	LCID lcid = MAKELCID(langid,SORT_CHINESE_BIG5) ;
	if ( LCMapStringW(lcid,LCMAP_SIMPLIFIED_CHINESE,
				   wszBig5,nGbBigLen+1,wszTempGbJt,nGbBigLen+1) != 0)
	{
		wcscpy( wszGbJt , wszTempGbJt ) ;		
	}

	delete[] wszTempGbJt; 	
}

BOOL IsChineseBetweenA( char cStartChinese[3] , char cStopChinese[3] , char cCompChinese[3] )
{
	if ( !cStartChinese || !cStopChinese || !cCompChinese )
	{
		return FALSE ;
	}

	int nResult1 = lstrcmpiA( cCompChinese , cStartChinese ) ;
	int nResult2 = lstrcmpiA( cCompChinese , cStopChinese ) ;

	if ( nResult1 >= 0 && nResult2 <= 0) 
	{
		return TRUE ;
	}
	else 
	{
		return FALSE ;
	}
}

BOOL IsChineseBetweenW(WCHAR wszStartChinese[2] , WCHAR wszStopChinese[2] , WCHAR wszCompChinese[2] )
{
	if ( !wszStartChinese || !wszStopChinese || !wszCompChinese )
	{
		return FALSE ;
	}

	int nResult1 = lstrcmpiW( wszCompChinese , wszStartChinese ) ;
	int nResult2 = lstrcmpiW( wszCompChinese , wszStopChinese ) ;

	if ( nResult1 >= 0 && nResult2 < 0) 
	{
		return TRUE ;
	}
	else 
	{
		return FALSE ;
	}
}

char GetChineseFirstCharacter( char cChinese[2] )
{
	char cCompChinese[3] ;
	memcpy( cCompChinese , cChinese , 2 ) ;
	cCompChinese[2] = '\0' ;

	if ( IsChineseBetweenA("°¡" , "°Å" , cCompChinese ) )
	{
		return 'A' ;
	}
	if ( IsChineseBetweenA("°Å" , "²Á" , cCompChinese ) )
	{
		return 'B' ;
	}
	if ( IsChineseBetweenA("²Á" , "´î" , cCompChinese ) )
	{
		return 'C' ;
	}
	if ( IsChineseBetweenA("´î" , "¶ê" , cCompChinese ) )
	{
		return 'D' ;
	}
	if ( IsChineseBetweenA("¶ê" , "·¢" , cCompChinese ) )
	{
		return 'E' ;
	}
	if ( IsChineseBetweenA("·¢" , "¸Á" , cCompChinese ) )
	{
		return 'F' ;
	}
	if ( IsChineseBetweenA("¸Á" , "¹þ" , cCompChinese ) )
	{
		return 'G' ;
	}
	if ( IsChineseBetweenA("¹þ" , "»÷" , cCompChinese ) )
	{
		return 'H' ;
	}
	if ( IsChineseBetweenA("»÷" , "¿¦" , cCompChinese ) )
	{
		return 'J' ;
	}
	if ( IsChineseBetweenA("¿¦" , "À¬" , cCompChinese ) )
	{
		return 'K' ;
	}
	if ( IsChineseBetweenA("À¬" , "Âè" , cCompChinese ) )
	{
		return 'L' ;
	}
	if ( IsChineseBetweenA("Âè" , "ÄÃ" , cCompChinese ) )
	{
		return 'M' ;
	}
	if ( IsChineseBetweenA("ÄÃ" , "Å¶" , cCompChinese ) )
	{
		return 'N' ;
	}
	if ( IsChineseBetweenA("Å¶" , "Å¾" , cCompChinese ) )
	{
		return 'O' ;
	}
	if ( IsChineseBetweenA("Å¾" , "ÆÚ" , cCompChinese ) )
	{
		return 'P' ;
	}
	if ( IsChineseBetweenA("ÆÚ" , "È»" , cCompChinese ) )
	{
		return 'Q' ;
	}
	if ( IsChineseBetweenA("È»" , "Èö" , cCompChinese ) )
	{
		return 'R' ;
	}
	if ( IsChineseBetweenA("Èö" , "Ëú" , cCompChinese ) )
	{
		return 'S' ;
	}
	if ( IsChineseBetweenA("Ëú" , "ÍÚ" , cCompChinese ) )
	{
		return 'T' ;
	}
	if ( IsChineseBetweenA("ÍÚ" , "Îô" , cCompChinese ) )
	{
		return 'W' ;
	}
	if ( IsChineseBetweenA("Îô" , "Ñ¹" , cCompChinese ) )
	{
		return 'X' ;
	}
	if ( IsChineseBetweenA("Ñ¹" , "ÔÑ" , cCompChinese ) )
	{
		return 'Y' ;
	}
	if ( IsChineseBetweenA("ÔÑ" , "×ù" , cCompChinese ) )
	{
		return 'Z' ;
	}

	//·±Ìå
	if ( IsChineseBetweenA("°¡" , "°Å" , cCompChinese ) )
	{
		return 'A' ;
	}
	if ( IsChineseBetweenA("°Å" , "²Á" , cCompChinese ) )
	{
		return 'B' ;
	}
	if ( IsChineseBetweenA("²Á" , "´î" , cCompChinese ) )
	{
		return 'C' ;
	}
	if ( IsChineseBetweenA("´î" , "¶ê" , cCompChinese ) )
	{
		return 'D' ;
	}
	if ( IsChineseBetweenA("¶ê" , "óŒ" , cCompChinese ) )
	{
		return 'E' ;
	}
	if ( IsChineseBetweenA("óŒ" , "¸Á" , cCompChinese ) )
	{
		return 'F' ;
	}
	if ( IsChineseBetweenA("¸Á" , "¹þ" , cCompChinese ) )
	{
		return 'G' ;
	}
	if ( IsChineseBetweenA("¹þ" , "“ô" , cCompChinese ) )
	{
		return 'H' ;
	}
	if ( IsChineseBetweenA("“ô" , "¿¦" , cCompChinese ) )
	{
		return 'J' ;
	}
	if ( IsChineseBetweenA("¿¦" , "À¬" , cCompChinese ) )
	{
		return 'K' ;
	}
	if ( IsChineseBetweenA("À¬" , "‹Œ" , cCompChinese ) )
	{
		return 'L' ;
	}
	if ( IsChineseBetweenA("‹Œ" , "ÄÃ" , cCompChinese ) )
	{
		return 'M' ;
	}
	if ( IsChineseBetweenA("ÄÃ" , "Å¶" , cCompChinese ) )
	{
		return 'N' ;
	}
	if ( IsChineseBetweenA("Å¶" , "Å¾" , cCompChinese ) )
	{
		return 'O' ;
	}
	if ( IsChineseBetweenA("Å¾" , "ÆÚ" , cCompChinese ) )
	{
		return 'P' ;
	}
	if ( IsChineseBetweenA("ÆÚ" , "È»" , cCompChinese ) )
	{
		return 'Q' ;
	}
	if ( IsChineseBetweenA("È»" , "Èö" , cCompChinese ) )
	{
		return 'R' ;
	}
	if ( IsChineseBetweenA("Èö" , "Ëú" , cCompChinese ) )
	{
		return 'S' ;
	}
	if ( IsChineseBetweenA("Ëú" , "ÍÚ" , cCompChinese ) )
	{
		return 'T' ;
	}
	if ( IsChineseBetweenA("ÍÚ" , "Îô" , cCompChinese ) )
	{
		return 'W' ;
	}
	if ( IsChineseBetweenA("Îô" , "‰º" , cCompChinese ) )
	{
		return 'X' ;
	}
	if ( IsChineseBetweenA("‰º" , "ÔÑ" , cCompChinese ) )
	{
		return 'Y' ;
	}
	if ( IsChineseBetweenA("ÔÑ" , "×ù" , cCompChinese ) )
	{
		return 'Z' ;
	}

	return char(0);
}

int GetPressedKey(void)
{
	for ( int i = 0 ; i < 256 ; i++ ) 
	{
		if ( GetKeyState(i)&0x80 )
		{
			return i ;
		}
	}
	
	return 0 ;
}

void GetMyIp( WCHAR *wszMyIp )
{
	if ( !wszMyIp )
	{
		return ;
	}

	char cMyIP[16] ;
	
	unsigned char MyIpAddress[5];
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	
	if (!WSAStartup(wVersionRequested, &wsaData)) 
	{
		char hostname[256];
		int res = gethostname(hostname, sizeof(hostname));
		
		if (res == 0) 
		{
			hostent* pHostent = gethostbyname(hostname);
			if (pHostent!=NULL) 
			{
				hostent& he = *pHostent;
				sockaddr_in sa;
				
				for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) 
				{
					memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
					// Output the machines IP Address.
				}	
				WSACleanup();
				
				MyIpAddress[0] = sa.sin_addr.S_un.S_un_b.s_b1;
				MyIpAddress[1] = sa.sin_addr.S_un.S_un_b.s_b2;
				MyIpAddress[2] = sa.sin_addr.S_un.S_un_b.s_b3;
				MyIpAddress[3] = sa.sin_addr.S_un.S_un_b.s_b4;

				MyIpAddress[4] = '\0' ;
			}
			else
				strcpy((char *)MyIpAddress,"");
		}
		else
			strcpy((char *)MyIpAddress,"");
	}
	else
		strcpy((char *)MyIpAddress,"");

	strcpy(cMyIP , "") ;
	for(int i = 0 ; i < 4 ; i++)
	{
		char tempchar[4] ;
		itoa(MyIpAddress[i] , tempchar , 10) ;
		tempchar[3] = '\0' ;

		strcat(cMyIP , tempchar) ;
		if(i != 3)
		{
			strcat(cMyIP , ".") ;
		}
	}

	cMyIP[15] = '\0' ;

	MB2WC( wszMyIp , cMyIP , 16 ) ;
}

void GetChatTempPath( OUT TCHAR *cFileDirectory )
{
	GetTempPath( MAX_PATH , cFileDirectory ) ;

	int nLength = _tcslen( cFileDirectory ) ;
	if ( nLength > 0 && cFileDirectory[nLength-1] != _T('\\') )
	{
		_tcscat( cFileDirectory , _T("\\") ) ;
	}

	_tcscat( cFileDirectory , _T("chat\\") ) ;

	CreateMultiDirectory( cFileDirectory ) ;
}

void GetFileNameAuto( OUT TCHAR *cFileName , IN TCHAR *cExtName , IN TCHAR *cDir )
{
	if ( !cFileName || !cExtName )
	{
		return ;
	}
	
	if ( !cDir )
	{
		GetChatTempPath( cFileName ) ;
	}
	else
	{
		_tcscpy( cFileName , cDir ) ;
	}
	
	int nLength = _tcslen( cFileName ) ;
	if ( nLength > 0 && cFileName[nLength-1] != _T('\\') )
	{
		_tcscat( cFileName , _T("\\") ) ;
	}

	_tcscat( cFileName , _T("Temp") ) ;
	
	TCHAR cTempFileName[MAX_PATH] ;
	int i = 0 ;
	while ( 1 )
	{
		TCHAR cFileLastName[6] ;
		ConvertLongToChar( i , cFileLastName , 5 ) ;
		cFileLastName[5] = _T('\0') ;
		
		_tcscpy( cTempFileName , cFileName ) ;
		_tcscat( cTempFileName , _T("_") ) ;
		_tcscat( cTempFileName , cFileLastName ) ;
		_tcscat( cTempFileName , _T(".") ) ;
		_tcscat( cTempFileName , cExtName ) ;
		
		if ( !IsFileArchive( cTempFileName ) )
		{
			break ;
		}
		
		i++ ;
		if ( i == 1000 )
		{
			break ;
		}
	}
	
	_tcscpy( cFileName , cTempFileName ) ;
}