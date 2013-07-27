#if !defined(AFX_DLGROT_H__A1D08F22_77B3_4280_ABD1_F8605CCC07DF__INCLUDED_)
#define AFX_DLGROT_H__A1D08F22_77B3_4280_ABD1_F8605CCC07DF__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRot dialog

class CDlgRot : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	int m_mark;
	HBITMAP RotationPic();
	HDC memdc;
	BITMAP bm;
	HBITMAP srcbmp;
	COLORREF* pcol;
	HBITMAP newbmp;
	BITMAPINFOHEADER RGB32BITSBITMAPINFO;
	void Initdlg(HBITMAP m_bmp);
	CDib m_dib;
	HBITMAP Rotation(COLORREF* pco,BITMAP Bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDlgRot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRot)
	enum { IDD = IDD_DLGROTATION };
	CSliderCtrl	m_slider;
	int		m_rotAngle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRot)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButtonLook();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROT_H__A1D08F22_77B3_4280_ABD1_F8605CCC07DF__INCLUDED_)
