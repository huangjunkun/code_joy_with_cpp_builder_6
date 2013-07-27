#if !defined(AFX_DLGTEMPLATE_H__AA63AEDE_B157_4E76_8445_812CA6049DBA__INCLUDED_)
#define AFX_DLGTEMPLATE_H__AA63AEDE_B157_4E76_8445_812CA6049DBA__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate dialog

class CDlgTemplate : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP PicTemplate();
	HBITMAP Template(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	int smooth[9];
	float aver;
	CDlgTemplate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTemplate)
	enum { IDD = IDD_DIATEMPLATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemplate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemplate)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio4();
	afx_msg void OnRadio8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPLATE_H__AA63AEDE_B157_4E76_8445_812CA6049DBA__INCLUDED_)
