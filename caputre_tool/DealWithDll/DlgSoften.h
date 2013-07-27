#if !defined(AFX_DLGSOFTEN_H__71C28606_B28D_4724_808E_32B89539E5C0__INCLUDED_)
#define AFX_DLGSOFTEN_H__71C28606_B28D_4724_808E_32B89539E5C0__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSoften.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSoften dialog

class CDlgSoften : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Soften();
	int smooth[9];
	float aver;
	HBITMAP TempLate(COLORREF* pco,BITMAP Bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	CDlgSoften(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSoften)
	enum { IDD = IDD_TEMPLATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSoften)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSoften)
	afx_msg void OnDestroy();
	afx_msg void OnCancle();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOFTEN_H__71C28606_B28D_4724_808E_32B89539E5C0__INCLUDED_)
