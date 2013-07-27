#if !defined(AFX_DLGRGB_H__380551DF_3989_4E5A_891D_4A60F8064347__INCLUDED_)
#define AFX_DLGRGB_H__380551DF_3989_4E5A_891D_4A60F8064347__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRgb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRgb dialog

class CDlgRgb : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Rgb();
	HBITMAP RgbTrans(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	CDlgRgb(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRgb)
	enum { IDD = IDD_DIARGB };
	CSliderCtrl	m_Slider3;
	CSliderCtrl	m_Slider2;
	CSliderCtrl	m_Slider1;
	int		m_R;
	int		m_G;
	int		m_B;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRgb)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRgb)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRGB_H__380551DF_3989_4E5A_891D_4A60F8064347__INCLUDED_)
