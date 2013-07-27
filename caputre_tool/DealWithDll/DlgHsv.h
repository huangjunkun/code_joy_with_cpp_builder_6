#if !defined(AFX_DLGHSV_H__3398E9F0_348D_4355_B44B_757C50D19C8E__INCLUDED_)
#define AFX_DLGHSV_H__3398E9F0_348D_4355_B44B_757C50D19C8E__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHsv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHsv dialog

class CDlgHsv : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Hsv();
	HBITMAP HsvTrans(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	CDlgHsv(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHsv)
	enum { IDD = IDD_DIAHSV };
	CSliderCtrl	m_Slider3;
	CSliderCtrl	m_Slider2;
	CSliderCtrl	m_Slider1;
	int		m_H;
	int		m_S;
	int		m_V;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHsv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHsv)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHSV_H__3398E9F0_348D_4355_B44B_757C50D19C8E__INCLUDED_)
