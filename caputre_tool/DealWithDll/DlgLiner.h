#if !defined(AFX_DLGLINER_H__58EDD901_DAF6_44C9_9D2C_6C7CD75B003C__INCLUDED_)
#define AFX_DLGLINER_H__58EDD901_DAF6_44C9_9D2C_6C7CD75B003C__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLiner.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLiner dialog

class CDlgLiner : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Translat();
	int m_laplas;
	HBITMAP Translation(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	CDlgLiner(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLiner)
	enum { IDD = IDD_DLG_PIXEL };
	CSliderCtrl	m_Slider3;
	CSliderCtrl	m_Slider2;
	CSliderCtrl	m_Slider1;
	int		m_Slope;
	int		m_Intercept;
	int		m_K;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLiner)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLiner)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINER_H__58EDD901_DAF6_44C9_9D2C_6C7CD75B003C__INCLUDED_)
