#if !defined(AFX_DLGLINTRANS_H__99A02EAA_FFC3_4017_8B05_D41087EA308D__INCLUDED_)
#define AFX_DLGLINTRANS_H__99A02EAA_FFC3_4017_8B05_D41087EA308D__INCLUDED_

#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLinTrans dialog

class CDlgLinTrans : public CMainDlg
{
// Construction
public:
	HBITMAP Tbitmap;
	HBITMAP LinTrans();
	int Choosevault(int vault,int oralow,int orahig,int newlow,int newhig);
	HBITMAP grayLinTrans(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO);
	CDib m_dib;
	CDlgLinTrans(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinTrans)
	enum { IDD = IDD_GRAY_ENHANCE };
	int		R_oralow;
	int		R_orahig;
	int		G_oralow;
	int		G_orahig;
	int		B_oralow;
	int		B_orahig;
	int		R_newlow;
	int		R_newhig;
	int		G_newlow;
	int		G_newhig;
	int		B_newlow;
	int		B_newhig;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinTrans)
	afx_msg void OnClose();
	afx_msg void OnAncel();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonlook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINTRANS_H__99A02EAA_FFC3_4017_8B05_D41087EA308D__INCLUDED_)
