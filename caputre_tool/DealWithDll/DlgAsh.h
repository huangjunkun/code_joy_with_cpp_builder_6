#if !defined(AFX_DLGASH_H__0E9B46B2_1ABD_4BBF_86BF_DEA0BF8D8A61__INCLUDED_)
#define AFX_DLGASH_H__0E9B46B2_1ABD_4BBF_86BF_DEA0BF8D8A61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAsh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAsh dialog

class CDlgAsh : public CMainDlg
{
// Construction
public:
	void ColorTotal();
	int nCount[3][256];
	CDib m_dib;
	CDlgAsh(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAsh)
	enum { IDD = IDD_DIALOGASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAsh)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAsh)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASH_H__0E9B46B2_1ABD_4BBF_86BF_DEA0BF8D8A61__INCLUDED_)
