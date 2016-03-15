#if !defined(AFX_GIFBUTTON_H__12225813_E5F4_496B_826B_78C0EC860466__INCLUDED_)
#define AFX_GIFBUTTON_H__12225813_E5F4_496B_826B_78C0EC860466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GifButton.h : header file
//
#include "SkinControlHead.h"
#include "SkinButton.h"
/////////////////////////////////////////////////////////////////////////////
// CGifButton window
#include "pictureex.h"

class SKIN_CONTROL_CLASS CGifButton : public CSkinButton
{
public:
	CPictureEx			m_GifPicture ;
	TCHAR				m_cGifFileName[MAX_PATH] ;

// Construction
public:
	CGifButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	void StartGif( void );
	void SetGifFileName( TCHAR *cFileName );
	virtual ~CGifButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGifButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFBUTTON_H__12225813_E5F4_496B_826B_78C0EC860466__INCLUDED_)
