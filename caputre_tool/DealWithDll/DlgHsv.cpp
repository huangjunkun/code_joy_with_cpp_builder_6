// DlgHsv.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgHsv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHsv dialog


CDlgHsv::CDlgHsv(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgHsv::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgHsv)
    m_H = 0;
    m_S = 0;
    m_V = 0;
    //}}AFX_DATA_INIT
    Tbitmap=NULL;
}


void CDlgHsv::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgHsv)
    DDX_Control(pDX, IDC_SLIDER3, m_Slider3);
    DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
    DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
    DDX_Text(pDX, IDC_EDIT1, m_H);
    DDX_Text(pDX, IDC_EDIT2, m_S);
    DDX_Text(pDX, IDC_EDIT3, m_V);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHsv, CDialog)
    //{{AFX_MSG_MAP(CDlgHsv)
    ON_WM_DESTROY()
    ON_WM_HSCROLL()
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHsv message handlers

BOOL CDlgHsv::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here

    CSpinButtonCtrl* gg=(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);
    gg->SetRange(-180,180);
    m_Slider1.SetRange(-180, 180, TRUE);
    m_Slider1.SetTicFreq(360/10);
    m_Slider1.SetPos(0);


    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(-50,50);
    m_Slider2.SetRange(-50, 50, TRUE);
    m_Slider2.SetTicFreq(100/10);
    m_Slider2.SetPos(0);

    ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetRange(-50,50);
    m_Slider3.SetRange(-50, 50, TRUE);
    m_Slider3.SetTicFreq(100/10);
    m_Slider3.SetPos(0);

    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHsv::OnDestroy()
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

void CDlgHsv::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER1))
    {
        m_H=m_Slider1.GetPos();
        CString str;
        str.Format("%d",m_Slider1.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER2))
    {
        m_S=m_Slider2.GetPos();
        CString str;
        str.Format("%d",m_S);
        ((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    else if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER3))
    {
        m_V=m_Slider3.GetPos();
        CString str;
        str.Format("%d",m_V);
        ((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*************************************************************************
 * 函数名称: HsvTrans()
 * 函数类型: HBITMAP
 * 函数功能: 色度/饱和度/对比度变换
 *************************************************************************/

HBITMAP CDlgHsv::HsvTrans(COLORREF *pco, BITMAP bm, BITMAPINFOHEADER RGBBITSBITMAPINFO)
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
    float H,S,V,f;
    int m_max,m_min,m,A,B,C;
    int r,g,b,cx=nWidth;
    for(i=0; i<bm.bmWidth; i++)
    {
        for(j=0; j<bm.bmHeight; j++)
        {
            r=GetRValue(pcol[i+j*cx]);
            g=GetGValue(pcol[i+j*cx]);
            b=GetBValue(pcol[i+j*cx]);

            m_max=max(max(r,g),b);
            m_min=min(min(r,g),b);
            if((m_max-m_min)!=0)
            {
                if(r==m_max)
                    H = ((float)(g-b))/(m_max-m_min);
                if(g==m_max)
                    H = 2 + ((float)(b-r))/(m_max-m_min);
                if(b==m_max)
                    H = 4 + ((float)(r-g))/(m_max-m_min);
                H=H*60;
                if (H < 0)
                    H = H + 360;
                V=((float)m_max)/255;
                S=((float)(m_max-m_min))/m_max;
                H=H+m_H;
                V=V+((float)m_V)/100;
                S=S+((float)m_S)/100;

            }
            else
            {
                S=0;
                H=0;
                V=((float)m_max)/255;
                V=V+((float)m_V)/100;
            }


            if(H<0)
                H=H+360;
            else if(H>360)
                H=H-360;
            if(V<0)
                V=0;
            else if(V>1)
                V=1;
            if(S<0)
                S=0;
            else if(S>1)
                S=1;

            if((float)0==S)
                r=g=b=(int)(V*255);
            else
            {
                H/=60;
                m=(int)H;
                f=H-m;
                A = (int)(V * ( 1 - S ) * 255);//m_min
                B = (int)(V * ( 1 - S * f ) * 255);
                C = (int)(V * ( 1 - S * (1 - f ) ) *255);

                switch(m)
                {
                case 0:
                {
                    r=(int)(V*255);
                    g=C;
                    b=A;
                    break;
                }
                case 1:
                {
                    r=B;
                    g=(int)(V*255);
                    b=A;
                    break;
                }
                case 2:
                {
                    r=A;
                    g=(int)(V*255);
                    b=C;
                    break;
                }
                case 3:
                {
                    r=A;
                    g=B;
                    b=(int)(V*255);
                    break;
                }
                case 4:
                {
                    r=C;
                    g=A;
                    b=(int)(V*255);
                    break;
                }
                case 5:
                {
                    r=(int)(V*255);
                    g=A;
                    b=B;
                    break;
                }
                }
            }
            pcol[i+j*cx]=RGB(r,g,b);
        }
    }
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    return bmp;
}

HBITMAP CDlgHsv::Hsv()
{
    return HsvTrans(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgHsv::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider1.SetPos(m_H);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgHsv::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider2.SetPos(m_S);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

void CDlgHsv::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider3.SetPos(m_V);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=HsvTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}
