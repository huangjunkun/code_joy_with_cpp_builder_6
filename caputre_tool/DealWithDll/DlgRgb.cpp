// DlgRgb.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgRgb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRgb dialog


CDlgRgb::CDlgRgb(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgRgb::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgRgb)
    m_R = 0;
    m_G = 0;
    m_B = 0;
    //}}AFX_DATA_INIT
    Tbitmap=NULL;
}


void CDlgRgb::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRgb)
    DDX_Control(pDX, IDC_SLIDER3, m_Slider3);
    DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
    DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
    DDX_Text(pDX, IDC_EDIT1, m_R);
    DDX_Text(pDX, IDC_EDIT2, m_G);
    DDX_Text(pDX, IDC_EDIT3, m_B);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRgb, CDialog)
    //{{AFX_MSG_MAP(CDlgRgb)
    ON_WM_HSCROLL()
    ON_WM_DESTROY()
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRgb message handlers

BOOL CDlgRgb::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(-256,256);

    m_Slider1.SetRange(-256, 256, TRUE);
    m_Slider1.SetTicFreq(512/10);
    m_Slider1.SetPos(0);

    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(-256,256);
    m_Slider2.SetRange(-256, 256, TRUE);
    m_Slider2.SetTicFreq(512/10);
    m_Slider2.SetPos(0);

    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetRange(-256,256);
    m_Slider3.SetRange(-256, 256, TRUE);
    m_Slider3.SetTicFreq(512/10);
    m_Slider3.SetPos(0);

    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRgb::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER1))
    {
        m_R=m_Slider1.GetPos();
        CString str;
        str.Format("%d",m_R);
        ((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER2))
    {
        m_G=m_Slider2.GetPos();
        CString str;
        str.Format("%d",m_G);
        ((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER3))
    {
        m_B=m_Slider3.GetPos();
        CString str;
        str.Format("%d",m_B);
        ((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgRgb::OnDestroy()
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
 * 函数名称: RgbTrans()
 * 函数类型: HBITMAP
 * 函数功能: 图像RGB值变换
 *************************************************************************/

HBITMAP CDlgRgb::RgbTrans(COLORREF *pco, BITMAP bm, BITMAPINFOHEADER RGBBITSBITMAPINFO)
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
    int r,g,b,cx=nWidth;
    for(i=0; i<bm.bmWidth; i++)
    {
        for(j=0; j<bm.bmHeight; j++)
        {
            r=GetRValue(pcol[i+j*cx]);
            g=GetGValue(pcol[i+j*cx]);
            b=GetBValue(pcol[i+j*cx]);

            r=r+m_R;
            g=g+m_G;
            b=b+m_B;
            if(r<0)
                r=0;
            else if(r>255)
                r=255;
            if(g<0)
                g=0;
            else if(g>255)
                g=255;
            if(b<0)
                b=0;
            else if(b>255)
                b=255;
            pcol[i+j*cx]=RGB(r,g,b);
        }
    }
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    return bmp;
}

HBITMAP CDlgRgb::Rgb()
{
    return RgbTrans(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgRgb::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider1.SetPos(m_R);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgRgb::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider2.SetPos(m_G);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgRgb::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider3.SetPos(m_B);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=RgbTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}
