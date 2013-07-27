#if !defined(AFX_DLGREVER_H__6EB532BD_A582_4662_989F_B709591EFB63__INCLUDED_)
#define AFX_DLGREVER_H__6EB532BD_A582_4662_989F_B709591EFB63__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRever.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRever dialog

class CDlgRever : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP ReverPic();
	HBITMAP Rever(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	int m_laplas;
	CDib m_dib;
	CDlgRever(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRever)
	enum { IDD = IDD_DIAREVER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRever)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRever)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREVER_H__6EB532BD_A582_4662_989F_B709591EFB63__INCLUDED_)
