// GifButton.cpp : implementation file
//

#include "Stdafx.h"
#include "Resource.h"
#include "GifButton.h"
#include "commonfunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifButton

CGifButton::CGifButton()
{
	_tcscpy( m_cGifFileName , _T("") ) ;
}

CGifButton::~CGifButton()
{
}


BEGIN_MESSAGE_MAP(CGifButton, CButton)
	//{{AFX_MSG_MAP(CGifButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifButton message handlers
BOOL CGifButton::Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
    BOOL m_bSucess = CButton::Create( lpszCaption,dwStyle,rect, pParentWnd, nID );
	StartGif() ;
    return m_bSucess;
}

void CGifButton::SetGifFileName(TCHAR *cFileName)
{
	if ( cFileName ) 
	{
		_tcscpy( m_cGifFileName , cFileName ) ;

		if ( IsWindow( GetSafeHwnd() ) )
		{
			StartGif() ;
		}
	}
}

void CGifButton::StartGif()
{
	if ( !::IsWindow(m_GifPicture.GetSafeHwnd() ) )
	{
		CRect rect;
		GetClientRect(rect);
		m_GifPicture.Create( NULL , WS_CHILD |WS_VISIBLE , rect , this , 0 ) ;
	}

	m_GifPicture.UnLoad() ;
	
	if ( IsFileArchive( m_cGifFileName ) )
	{
		m_GifPicture.Load( m_cGifFileName ) ;
		
		m_GifPicture.Draw() ;
	}	

	//m_AnimateCtrl.Play(0,-1,1);
}
