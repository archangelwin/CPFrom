// CTabSheet window
#define MAXPAGE 16

class CTabSheet :public CTabCtrl
{
	// Construction
public:
	CTabSheet();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSheet)
	//}}AFX_VIRTUAL

	// Implementation
public:
	int GetCurSel();
	int SetCurSel(int nItem);
	void Show();
	void SetRect();
	BOOL AddPage(LPCTSTR title, CDialog *pDialog, UINT ID);
	virtual ~CTabSheet();

	// Generated message map functions
protected:
	int m_nCurrentPage;
	int m_nNumOfPages;
	CDialog* m_pPages[MAXPAGE];
	UINT m_IDD[MAXPAGE];
	LPCTSTR m_Title[MAXPAGE];
	//{{AFX_MSG(CTabSheet)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};




