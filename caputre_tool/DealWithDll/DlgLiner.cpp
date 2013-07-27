// DlgLiner.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgLiner.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLiner dialog


CDlgLiner::CDlgLiner(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgLiner::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgLiner)
    m_Slope = 2;
    m_Intercept = -100;
    m_K = 50;
    //}}AFX_DATA_INIT
    m_laplas=0;
    Tbitmap=NULL;
}


void CDlgLiner::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLiner)
    DDX_Control(pDX, IDC_SLIDER3, m_Slider3);
    DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
    DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
    DDX_Text(pDX, IDC_EDIT1, m_Slope);
    DDX_Text(pDX, IDC_EDIT2, m_Intercept);
    DDX_Text(pDX, IDC_EDIT3, m_K);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLiner, CDialog)
    //{{AFX_MSG_MAP(CDlgLiner)
    ON_WM_DESTROY()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLiner message handlers

void CDlgLiner::OnDestroy()
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

BOOL CDlgLiner::OnInitDialog()
{
    CMainDlg::OnInitDialog();
    ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);

    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(-10,10);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(-255,255);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetRange(0,100);
    m_Slider1.SetRange(-10,10);
    m_Slider2.SetRange(-255,255);
    m_Slider3.SetRange(0,100);
    m_Slider1.SetPos(m_Slope);
    m_Slider2.SetPos(m_Intercept);
    m_Slider3.SetPos(m_K);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->EnableWindow(false);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(false);
    // TODO: Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLiner::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER1))
    {
        m_Slope=m_Slider1.GetPos();
        CString str;
        str.Format("%d",m_Slider1.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER2))
    {
        m_Intercept=m_Slider2.GetPos();
        CString str;
        str.Format("%d",m_Slider2.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER3))
    {
        m_K=m_Slider3.GetPos();
        CString str;
        str.Format("%d",m_Slider3.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*************************************************************************
 * 函数名称: Translation()
 * 函数类型: HBITMAP
 * 函数功能: 图像线性增强或对数增强
 *************************************************************************/

HBITMAP CDlgLiner::Translation(COLORREF *pco, BITMAP bm, BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP bmp;
    int i,j;
    int nWidth = bm.bmWidth;
    int nHeight = bm.bmHeight;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(int k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    int r=0,g=0,b=0;
    switch(m_laplas)
    {
    case 0:
    {
        for (i = 0; i < nWidth; i++)
        {
            for (j = 0; j < nHeight; j++)
            {
                r=GetRValue(pcol[i+j*nWidth]);
                g=GetGValue(pcol[i+j*nWidth]);
                b=GetBValue(pcol[i+j*nWidth]);

                r=m_Slope*r+m_Intercept;
                g=m_Slope*g+m_Intercept;
                b=m_Slope*b+m_Intercept;

                if(r>255)
                    r=255;
                else if(r<0)
                    r=0;
                if(g>255)
                    g=255;
                else if(g<0)
                    g=0;
                if(b>255)
                    b=255;
                else if(b<0)
                    b=0;
                pcol[i+j*nWidth]=RGB(r,g,b);
            }
        }
        break;
    }
    case 1:
    {
        for(i=0; i<nWidth; i++)
        {
            for(j=0; j<nHeight; j++)
            {
                r=GetRValue(pcol[i+j*nWidth]);
                g=GetGValue(pcol[i+j*nWidth]);
                b=GetBValue(pcol[i+j*nWidth]);

                r=(int)(m_K*log(r+1));
                g=(int)(m_K*log(g+1));
                b=(int)(m_K*log(b+1));

                if(r>255)
                    r=255;
                else if(r<0)
                    r=0;
                if(g>255)
                    g=255;
                else if(g<0)
                    g=0;
                if(b>255)
                    b=255;
                else if(b<0)
                    b=0;
                pcol[i+j*nWidth]=RGB(r,g,b);
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

void CDlgLiner::OnRadio1()
{
    // TODO: Add your control notification handler code here
    m_laplas=0;
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->EnableWindow(true);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->EnableWindow(true);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->EnableWindow(true);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->EnableWindow(true);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->EnableWindow(false);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(false);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgLiner::OnRadio2()
{
    // TODO: Add your control notification handler code here
    m_laplas=1;
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->EnableWindow(false);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->EnableWindow(false);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->EnableWindow(false);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->EnableWindow(false);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->EnableWindow(true);
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(true);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

HBITMAP CDlgLiner::Translat()
{
    return Translation(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgLiner::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider1.SetPos(m_Slope);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgLiner::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider2.SetPos(m_Intercept);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgLiner::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider3.SetPos(m_K);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Translation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}
