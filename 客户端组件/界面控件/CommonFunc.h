#ifndef _VIDEO_COMMON_H
#define _VIDEO_COMMON_H

#include "stdafx.h"

#define			VK_0				48
#define			VK_1				49
#define			VK_2				50
#define			VK_3				51
#define			VK_4				52
#define			VK_5				53
#define			VK_6				54
#define			VK_7				55
#define			VK_8				56
#define			VK_9				57
#define			VK_A				'A'
#define			VK_B				'B'
#define			VK_C				'C'
#define			VK_D				'D'
#define			VK_E				'E'
#define			VK_F				'F'
#define			VK_G				'G'
#define			VK_H				'H'
#define			VK_I				'I'
#define			VK_J				'J'
#define			VK_K				'K'
#define			VK_L				'L'
#define			VK_M				'M'
#define			VK_N				'N'
#define			VK_O				'O'
#define			VK_P				'P'
#define			VK_Q				'Q'
#define			VK_R				'R'
#define			VK_S				'S'
#define			VK_T				'T'
#define			VK_U				'U'
#define			VK_V				'V'
#define			VK_W				'W'
#define			VK_X				'X'
#define			VK_Y				'Y'
#define			VK_Z				'Z'

#ifndef			VK_OEM_2
#define			VK_OEM_2			191
#endif

#define Get3Min(x1,x2,x3) ((x1<x2?x1:x2)<x3?(x1<x2?x1:x2):x3)
#define Get3Max(x1,x2,x3) ((x1>x2?x1:x2)>x3?(x1>x2?x1:x2):x3)

typedef			unsigned (__stdcall *PTHREAD_START)(void*);
#define			_BEGINTHREADEX(psa , cbStack , pfnStartAddr ,	\
				pvParam , fdwCreate , pdwThreadID)				\
				((HANDLE)_beginthreadex(						\
				(void *)(psa),									\
				(unsigned)(cbStack),							\
				(PTHREAD_START)(pfnStartAddr),					\
				(void *)(pvParam),								\
				(unsigned)(fdwCreate),							\
				(unsigned *)(pdwThreadID)))

#define SAFE_RELEASE( x )   \
    if ( x )                \
    {                       \
        x->Release();       \
        x = NULL;           \
    }
    
#define SAFE_ADDREF( x )    \
    if ( x )                \
    {                       \
        x->AddRef();        \
    }

#define SAFE_DELETE( x )    \
    if ( x )                \
    {                       \
        delete x;           \
        x = NULL;           \
    }

#define SAFE_ARRAYDELETE( x )   \
    if ( x )                    \
    {                           \
        delete[] x;             \
        x = NULL;               \
    }

#define SAFE_SYSFREESTRING( x ) \
    if ( x )                    \
    {                           \
        SysFreeString( x );     \
        x = NULL;               \
    }

#define SAFE_CLOSEHANDLE( x )               \
    if ( x && INVALID_HANDLE_VALUE != x )   \
    {                                       \
        CloseHandle( x );                   \
        x = NULL;                           \
    }

typedef enum _Win32SysVersion
{
   Windows32s ,
   WindowsNT3 ,
   Windows95 ,
   Windows98 ,
   WindowsME ,
   WindowsNT4 ,
   Windows2000 ,
   WindowsXP
} Win32SysVersion ;

typedef enum _PictureType
{
	BMP_FILE = 0 ,
	JPG_FILE ,
	GIF_FILE ,
	TIF_FILE ,
	PNG_FILE ,
	UNKNOWN_PIC_FILE ,
} PictureType ;

typedef struct _TRIANGLE
{
	CPoint		p1 ;
	CPoint		p2 ;
	CPoint		p3 ;
} TRIANGLE ;

	BOOL IsValidUserName( WCHAR *wszUserName ) ;
	BOOL IsValidDotAddress( WCHAR *wszIPAddress ) ;
	BOOL IsNumber( WCHAR *wszChar ) ;
	void GetMyIp( WCHAR *wszMyIp ) ;

/************************************************************************/
/* Bitmap operation function                                            */
/************************************************************************/
	// Convert file to a special format
	BOOL ConvertFile( IN TCHAR *cSourceFileName , OUT TCHAR *cDestFileName , PictureType mSaveType=BMP_FILE ) ;
	int  GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function
	
	// CopyHBitmap
	// copy the source hbitmap to a new hbitmap
	HBITMAP CopyHBitmap( HBITMAP hSourceBitmap ) ;

	// GetBmpFromImageList
	// Get a bitmap from a imagelist object
	HBITMAP GetBmpFromImageList(CImageList *pImagelist , int nFaceNumber,COLORREF bkcolor) ;
	
	// CreateColorBmp
	// this function create a color bitmap 
	HBITMAP CreateColorBmp( int nWidth , int nHeight , COLORREF clr ) ;

	// ResizeBitmap
	// this function resize a bitmap to a special size , holding the scale
	HBITMAP ResizeBitmap( HBITMAP hSourceBitmap , int nWidth , int nHeight , COLORREF clrBack ) ;
	
	// StretchBitmap
	// this function stretch a bitmap to a special size , not holding the scale
	HBITMAP StretchBitmap( HBITMAP hSourceBitmap , int nWidth , int nHeight ) ;

	// GetBitmapFromBitmap
	// this function get a bitmap from the source bitmap
	HBITMAP GetBitmapFromBitmap( HBITMAP hSourceBitmap , int x , int y , int cx , int cy ) ;

	// LoadBitmapFromResource(MFC) , LoadBitmapFromFile
	HBITMAP LoadBitmapFromResource( int ResourceID ) ;
	HBITMAP LoadBitmapFromFile(LPCTSTR lpszFileName) ;

	void GetChatTempPath( OUT TCHAR *cFileDirectory ) ;

	// cExtName : not contain dot , such as "txt" ;
	void GetFileNameAuto( OUT TCHAR *cFileName , IN TCHAR *cExtName , IN TCHAR *cDir=NULL ) ;
	
	// BitmapToRegion -- create rgn from bitmap , 
	// cTransparentColor -- transparent color
	// color tolerance , (cTransparentColor - cTolerance , cTransparentColor + cTolerance)
	HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, 
						COLORREF cTolerance=RGB(0,0,0)) ;

	// Get Special window bitmap
	HBITMAP GetWindowBitMap( HWND hWnd ) ;

	//void 
	void SetTransParentWnd(HWND hWnd , BYTE bValue) ;
	
	// DDBtoDIB :change bitmap handle to a buffer handle
	HANDLE  DDBtoDIB( HBITMAP bitmap)  ;
	
	// DIBtoDDB :change buffer handle to a bitmap handle
	HBITMAP DIBToDDB( HANDLE hDIB ) ;

	// SaveHbitmapToFile : save a hbitmap object
	void SaveHbitmapToFile( HBITMAP hBitmap , TCHAR *cFileName ) ;

	// GetTriangleRect:get special triangle bounding rect
	CRect GetTriangleRect( TRIANGLE mTriangle ) ;

	// Draw a Triangle with special color
	void DrawTriangle( CDC *memDC , TRIANGLE mTriangle , COLORREF color ) ;

	// fill special rect or rgn with special color
	void FillBackGround( CDC *memDC , CRgn *rgn , COLORREF bkColor ) ;
	void FillBackGround( CDC *memDC , CRect rc , COLORREF bkColor ) ;

	// fill special rect with a bitmap
	void DrawBitmap(CDC *memDC , CRect rc, HBITMAP hBkBmp , BOOL bStretch , COLORREF crTransparent=0xFFFFFFFF ) ;
	void DrawBitmap(CDC *memDC , CRect rc , UINT uBmpID , BOOL bStretch , COLORREF crTransparent=0xFFFFFFFF) ;

	// fill special rect(mDestRect) from a rect(mBoundRect) with a bitmap
	void DrawSpecialRect(CDC *memDC , CRect mBoundRect , CRect mDestRect , HBITMAP hBkBmp ) ;
	
	// usually use to erase back ground
	BOOL RepaintBk( CDC *pDC , UINT nResourceID , CRect rc ) ;
	BOOL RepaintBk( CDC *pDC , HBITMAP hBitmap , CRect rc ) ;

	//   DrawParentText: Draw select font text , transparent
	void DrawParentText( CDC *memDC , CRect rc , int m_nFontSize , TCHAR *m_FontName , 
						CString mString , COLORREF m_FontColor , int m_DrawDirect ,
						BYTE bCharset=ANSI_CHARSET ) ;

	// CutRect :cut a rect with special rect , source rect will be seprate
	// to none or one or two rect(s) , if the rect is (-1,-1,-1,-1) , this
	// rect can not be use
	void CutRect(CRect SourceRc, CRect CutRc, CRect *DestRc1, CRect *DestRc2) ;
/************************************************************************/
/* Bitmap operation function                                            */
/************************************************************************/

/************************************************************************/
/* useful functions or system functions									*/
/************************************************************************/
	void ConvertCFW2CF( _charformatw cfw , CHARFORMAT &cf );
	void ConvertCF2CFW( CHARFORMAT cf , _charformatw &cfw );
	
	// WCHAR <-> MULTIBYTE
	int WC2MB( char *mb , WCHAR *wc , int nLength ) ;
	int MB2WC( WCHAR *wc , char *mb , int nLength ) ;

	// BIG<->GB
	void ConvertBig5ToGb(const WCHAR *wszBig5,WCHAR *wszGbJt) ;
	void ConvertGbToBig5(const WCHAR *wszGbJt,WCHAR *wszBig5) ;
	
	int  GetPressedKey(void) ;

	// chinese to pinyin
	char GetChineseFirstCharacter( char cChinese[2] ) ;	
	BOOL IsChineseBetweenA( char cStartChinese[3] , char cStopChinese[3] , char cCompChinese[3] ) ;
	BOOL IsChineseBetweenW( WCHAR wszStartChinese[2] , WCHAR wszStopChinese[2] , WCHAR wszCompChinese[2] ) ;

	// convert system time to string
	void ChangeSysTimeToString(SYSTEMTIME systemTime , TCHAR *cSystemTime) ;

	// convert time to string , such as : 100(s)->_T("00:01:40")
	CString FormatTimeToString(LONGLONG ntime) ;

	// convert string to time , such as : _T("00:02:00")->120(s)
	LONGLONG FormatStringToTime(CString mTime) ;

	// convert time to string , such as : 25*3600s->_T("1Ìì1Ð¡Ê±");
	CString FormatTime(LONGLONG nTime) ;

	// ConvertLongToChar :this function convert long to a string
	// such as :
	// TCHAR cNumber[7] ;
	// convertLongToChar(12 , cNumber , 6) ;
	// Number is now : _T("000012") ;
	void ConvertLongToChar(long number, TCHAR *cNumber , int numbers) ;

	// IsMediaPlayVersionUpperThan90 detect if the window 
	// media player version is higher than 9.0
	BOOL IsMediaPlayVersionUpperThan90( void ) ;
	
	// IsDirectShowVersionUpperThan90 detect if directshow
	// version is higher than 9.0
	BOOL IsDirectShowVersionUpperThan90( void ) ;

	// Delete2DArray :delete the 2D array created by Make2DArray function  
	void Delete2DArray( BOOL **&x , int rows );

	// Make2DArray :create 2D array , return the head adress
	void Make2DArray( BOOL ** &x , int rows , int cols );

	// SortStrings :call quick sort or bubble sort
	void SortStrings( TCHAR **SortStrings , int nSortNumber ) ;

	// BubbleSortForStrings :sort strings
	void BubbleSortForStrings( TCHAR **SortStrings , int nSortNumber ) ;

	WCHAR *GetLastPosInStringW( WCHAR *DestiString , int DestLength ,
							    WCHAR *SearchString , int SearchLength ) ;
	char  *GetLastPosInStringA( char *DestiString , int DestLength ,
							    char *SearchString , int SearchLength ) ;
	//GetLastPosInString :compare two strings , if find searchstrings ,
	//return the last same charactor address	
	#ifdef UNICODE
		#define GetLastPosInString GetLastPosInStringW
	#else
		#define GetLastPosInString GetLastPosInStringA
	#endif	

	void DumpMessage( BOOL* pEndFlagPtr=NULL , DWORD dwDelayTime=0 ) ;

	/************************************************************************/
	/* RegisterFilter : Register special filter or control                  */
	/************************************************************************/
	BOOL RegisterFilter(TCHAR *cilterFileName) ;

/************************************************************************/
/* useful functions or system functions									*/
/************************************************************************/

/************************************************************************/
/* file operation functions                                             */
/************************************************************************/
	Win32SysVersion GetSystemVersion( void ) ;
	BOOL GetSaveOpenFileName( IN HWND hWnd , IN TCHAR *cFilter , IN BOOL bSave,
							  IN TCHAR *strTitle , IN TCHAR *szPath , 
							  IN TCHAR *szFile , OUT TCHAR *cFileName ) ;
	BOOL GetSaveOpenFolderName( HWND hParent, CString &strFolder ) ;
	LPITEMIDLIST ConvertFolderToPIDL( CString strFolderName ) ;

	void GetProgramFilePathW( WCHAR *wszFilePath ) ;
	void GetProgramFilePathA( TCHAR *cFilePath ) ;
	#ifdef UNICODE
	#define GetProgramFilePath GetProgramFilePathW
	#else
	#define GetProgramFilePath GetProgramFilePathA
	#endif
	
	BOOL GetFileParentDirW( OUT WCHAR *wszFileParentDir , IN WCHAR *wszSrcFileName ) ;
	BOOL GetFileParentDirA( OUT char *cFileParentDir , IN char *cSrcFileName ) ;
	#ifdef UNICODE
		#define GetFileParentDir GetFileParentDirW
	#else
		#define GetFileParentDir GetFileParentDirA
	#endif

	BOOL GetFileShortNameW( OUT WCHAR *wszFileShortName , IN WCHAR *wszSrcFileName ) ;
	BOOL GetFileShortNameA( OUT char *cFileShortName , IN char *cSrcFileName ) ;
	#ifdef UNICODE
		#define GetFileShortName GetFileShortNameW
	#else
		#define GetFileShortName GetFileShortNameA
	#endif

	void GetFileExtNameW( OUT WCHAR *wszExtName , IN WCHAR *wszSrcFileName ) ;
	void GetFileExtNameA( OUT char *cExtName , IN char *cSrcFileName ) ;
	#ifdef UNICODE
		#define GetFileExtName GetFileExtNameW
	#else
		#define GetFileExtName GetFileExtNameA
	#endif
	
	void SetFileExtNameW( IN OUT WCHAR *wszFileName , IN WCHAR *wszExtName ) ;
	void SetFileExtNameA( IN OUT char *cFileName , IN char *cExtName ) ;
	#ifdef UNICODE
		#define SetFileExtName SetFileExtNameW
	#else
		#define SetFileExtName SetFileExtNameA
	#endif

	FILETIME GetFileLastWriteTimeW( WCHAR *wszFileName ) ;
	FILETIME GetFileLastWriteTimeA( char *cFileName ) ;
	#ifdef UNICODE
		#define GetFileLastWriteTime GetFileLastWriteTimeW
	#else
		#define GetFileLastWriteTime GetFileLastWriteTimeA
	#endif

	LONGLONG GetFileSizeLongA( char *cFileName ) ;
	LONGLONG GetFileSizeLongW( WCHAR *cFileName ) ;
	#ifdef UNICODE
		#define GetFileSizeLong GetFileSizeLongW
	#else
		#define GetFileSizeLong GetFileSizeLongA
	#endif

	BOOL IsFileArchiveW(WCHAR *wszFileName) ;
	BOOL IsFileArchiveA(char *wszFileName) ;
	#ifdef UNICODE
	#define IsFileArchive IsFileArchiveW
	#else
	#define IsFileArchive IsFileArchiveA
	#endif

	BOOL IsFileDirectoryW(WCHAR *wszFileName) ;
	BOOL IsFileDirectoryA(char *cFileName) ;
	#ifdef UNICODE
	#define IsFileDirectory IsFileDirectoryW
	#else
	#define IsFileDirectory IsFileDirectoryA
	#endif

	BOOL IsDriverW(WCHAR *wszFileName) ;
	BOOL IsDriverA(char *cFileName) ;
	#ifdef UNICODE
	#define IsDriver IsDriverW
	#else
	#define IsDriver IsDriverA
	#endif

	void CreateMultiDirectory( TCHAR *cFolderName ) ;
	HRESULT ShellCopyFile( HWND hWnd , TCHAR *cSrcFolder , TCHAR *cDestFolder ) ;
	void DelFolderTree( TCHAR *cFolderName ) ;
	void ClearFileContext( TCHAR *cFileName ) ;	
	BOOL IsLNKFileType( TCHAR *cFileName ) ;
	BOOL SetFileLastWriteTime( TCHAR *cFileName , FILETIME mWriteTime ) ;
	BOOL IsValidFileName( TCHAR *cFileName ) ;
	void GetDriverList(TCHAR *cDriverList[100] , int &nDriverNumber) ;
	void GetLocalFileList(TCHAR *cFolder ,
						  TCHAR *cSortedFolderList[10000] ,
						  TCHAR *cSortedFileList[10000] ,
						  int *nFolderNumber ,
						  int *nFileNumber ) ;
	BOOL GetLNKFilePath( TCHAR *lpszLinkToPath , TCHAR *lpszLinkFile ) ;
/************************************************************************/
/* file operation functions                                             */
/************************************************************************/

class CMemDC : public CDC 
{
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		if ( m_bitmap )
		{
			m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
			m_oldBitmap = SelectObject(m_bitmap);
		}		
		m_pDC = pDC;
		m_rcBounds = rcBounds;
	}
	~CMemDC() 
	{
		m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) 
			delete m_bitmap;
	}
	CMemDC* operator->() 
	{
		return this;
	}
};

#endif //_VIDEO_COMMON_H
