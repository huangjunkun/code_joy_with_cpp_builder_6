#if !defined(AFX_DLGMEDIANFILT_H__0C6F4C03_EA22_496F_94A7_8D0F5C9648B7__INCLUDED_)
#define AFX_DLGMEDIANFILT_H__0C6F4C03_EA22_496F_94A7_8D0F5C9648B7__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMedianFilt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilt dialog

class CDlgMedianFilt : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP Filter();
	int MedianValue(int* FiltValue,int mFilterLen);
	HBITMAP medianFilter(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	int		mFilterH;
	int		mFilterW; 
	int		mFilterMX;
	int		mFilterMY;
	CDlgMedianFilt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMedianFilt)
	enum { IDD = IDD_MEDIAN_FILTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMedianFilt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMedianFilt)
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

#endif // !defined(AFX_DLGMEDIANFILT_H__0C6F4C03_EA22_496F_94A7_8D0F5C9648B7__INCLUDED_)
