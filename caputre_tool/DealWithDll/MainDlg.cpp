// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
    : CDialog(nIDTemplate, pParent)
{
    //{{AFX_DATA_INIT(CMainDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMainDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
    //{{AFX_MSG_MAP(CMainDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    //===================º”‘ÿ∆§∑Ù≤¢«“…Ë÷√∆§∑Ù¥∞ø⁄================*/
    VERIFY(1 == InitSkinMagicLib(AfxGetInstanceHandle(),"SDI",
                                 NULL,
                                 NULL));

    VERIFY(1 == LoadSkinFromResource(AfxGetInstanceHandle(),"TUSK1","SKINMAGIC"));

    VERIFY(1 == SetWindowSkin(m_hWnd,"MainFrame"));
    VERIFY(1 == SetDialogSkin("Dialog"));
    /*==========================END==============================*/


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMainDlg::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class

    return CDialog::PreCreateWindow(cs);
}
