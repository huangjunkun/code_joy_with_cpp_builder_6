#if !defined(AFX_DLGASHTRANS_H__F0E75BBF_289E_4638_ADA3_DFFCB340D150__INCLUDED_)
#define AFX_DLGASHTRANS_H__F0E75BBF_289E_4638_ADA3_DFFCB340D150__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAshTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAshTrans dialog

class CDlgAshTrans : public CMainDlg
{
// Construction
public:
	HBITMAP Ash();
	int m_las;
	HBITMAP AshTranslation(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	HBITMAP Tbitmap;
	CDlgAshTrans(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAshTrans)
	enum { IDD = IDD_DIGASH };
	CSliderCtrl	m_Slider;
	int		m_Ash;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAshTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAshTrans)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASHTRANS_H__F0E75BBF_289E_4638_ADA3_DFFCB340D150__INCLUDED_)
