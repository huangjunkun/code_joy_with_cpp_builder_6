// DlgRever.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgRever.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRever dialog


CDlgRever::CDlgRever(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgRever::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgRever)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_laplas=1;
    Tbitmap=NULL;
}


void CDlgRever::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRever)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRever, CDialog)
    //{{AFX_MSG_MAP(CDlgRever)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRever message handlers

void CDlgRever::OnDestroy()
{
    CDialog::OnDestroy();
    RemoveWindowSkin(this->m_hWnd);
    RemoveDialogSkin();
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    // TODO: Add your message handler code here

}

/*************************************************************************
 * 函数名称: Rever()
 * 函数类型: HBITMAP
 * 函数功能: 图像翻转
 *************************************************************************/

HBITMAP CDlgRever::Rever(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP bmp;
    int i,j;
    int nWidth = bm.bmWidth;
    int nHeight = bm.bmHeight;
    COLORREF clr;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(int k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    switch(m_laplas)
    {
    case 1:
    {
        for(i=0; i<(nHeight+1)/2; i++)
        {
            for(j=0; j<nWidth; j++)
            {
                clr=pcol[j+i*nWidth];
                pcol[j+i*nWidth]=pcol[j+(nHeight-i-1)*nWidth];
                pcol[j+(nHeight-i-1)*nWidth]=clr;
            }
        }
        break;
    }
    case 2:
    {
        for(i=0; i<nHeight; i++)
        {
            for(j=0; j<(nWidth+1)/2; j++)
            {
                clr=pcol[j+i*nWidth];
                pcol[j+i*nWidth]=pcol[(nWidth-j-1)+i*nWidth];
                pcol[(nWidth-j-1)+i*nWidth]=clr;
            }
        }
        break;
    }
    }
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    return bmp;
}

BOOL CDlgRever::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
//	((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Rever(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgRever::OnRadio1()
{
    // TODO: Add your control notification handler code here
    m_laplas=1;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Rever(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgRever::OnRadio6()
{
    // TODO: Add your control notification handler code here
    m_laplas=2;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Rever(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

HBITMAP CDlgRever::ReverPic()
{
    return Rever(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}
