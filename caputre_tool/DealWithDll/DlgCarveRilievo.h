#if !defined(AFX_DLGCARVERILIEVO_H__307FA3C3_2062_485B_8E2F_92C49247352D__INCLUDED_)
#define AFX_DLGCARVERILIEVO_H__307FA3C3_2062_485B_8E2F_92C49247352D__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCarveRilievo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCarveRilievo dialog

class CDlgCarveRilievo : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP CarOrRil();
	HBITMAP CarveOrRilievo(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	int m_laplas;
	CDib m_dib;
	CDlgCarveRilievo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCarveRilievo)
	enum { IDD = IDD_RILIEVOCARVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCarveRilievo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCarveRilievo)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARVERILIEVO_H__307FA3C3_2062_485B_8E2F_92C49247352D__INCLUDED_)
