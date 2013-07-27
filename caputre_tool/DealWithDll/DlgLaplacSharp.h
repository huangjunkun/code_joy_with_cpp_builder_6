#if !defined(AFX_DLGLAPLACSHARP_H__A6C12115_B801_44EC_AF40_6EBDD53E9EDA__INCLUDED_)
#define AFX_DLGLAPLACSHARP_H__A6C12115_B801_44EC_AF40_6EBDD53E9EDA__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLaplacSharp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLaplacSharp dialog

class CDlgLaplacSharp : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Sharp();
	HBITMAP laplacSharp(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	int m_laplas;
	int smooth[9];
	CDib m_dib;
	CDlgLaplacSharp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLaplacSharp)
	enum { IDD = IDD_LAPLAC_TEMP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLaplacSharp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLaplacSharp)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLAPLACSHARP_H__A6C12115_B801_44EC_AF40_6EBDD53E9EDA__INCLUDED_)
