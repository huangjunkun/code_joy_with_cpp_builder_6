// DlgAshTrans.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgAshTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAshTrans dialog


CDlgAshTrans::CDlgAshTrans(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgAshTrans::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgAshTrans)
    m_Ash = 0;
    //}}AFX_DATA_INIT
    Tbitmap=NULL;
    m_las=1;
}


void CDlgAshTrans::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAshTrans)
    DDX_Control(pDX, IDC_SLIDER1, m_Slider);
    DDX_Text(pDX, IDC_EDIT1, m_Ash);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAshTrans, CDialog)
    //{{AFX_MSG_MAP(CDlgAshTrans)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
    ON_WM_HSCROLL()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAshTrans message handlers

BOOL CDlgAshTrans::OnInitDialog() //初始化
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=AshTranslation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);

    CSpinButtonCtrl* gg=(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);
    gg->SetRange(-100,100);
    m_Slider.SetRange(-100, 100, TRUE);
    m_Slider.SetTicFreq(200/10);
    m_Slider.SetPos(0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAshTrans::OnDestroy()
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
 * 函数名称: AshTranslation()
 * 函数类型: HBITMAP
 * 函数功能: 实现灰度变换
 *************************************************************************/
HBITMAP CDlgAshTrans::AshTranslation(COLORREF *pco, BITMAP bm, BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP bmp;
    int i,j;
    int nWidth = bm.bmWidth;
    int nHeight = bm.bmHeight;
    int r,g,b,gray;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(int k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    switch(m_las)
    {
    case 1:
    {
        for(i=0; i<nWidth; i++)
        {
            for(j=0; j<nHeight; j++)
            {
                r=GetRValue(pcol[(i)+(j)*nWidth]);
                g=GetGValue(pcol[(i)+(j)*nWidth]);
                b=GetBValue(pcol[(i)+(j)*nWidth]);

                gray=(int)(r*0.3+g*0.59+b*0.11);

                gray=gray+m_Ash;
                if(gray<0)
                    gray=0;
                else if(gray>255)
                    gray=255;
                pcol[i+j*nWidth]=RGB(gray,gray,gray);
            }
        }
        break;
    }
    case 2:
    {
        for(i=0; i<nWidth; i++)
        {
            for(j=0; j<nHeight; j++)
            {
                r=GetRValue(pcol[(i)+(j)*nWidth]);
                g=GetGValue(pcol[(i)+(j)*nWidth]);
                b=GetBValue(pcol[(i)+(j)*nWidth]);

                gray=(r+g+b)/3;

                gray=gray+m_Ash;
                if(gray<0)
                    gray=0;
                else if(gray>255)
                    gray=255;
                pcol[i+j*nWidth]=RGB(gray,gray,gray);
            }
        }
        break;
    }
    }
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete [] pcol;
    return bmp;
}

void CDlgAshTrans::OnRadio1()
{
    // TODO: Add your control notification handler code here
    m_las=1;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=AshTranslation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgAshTrans::OnRadio2()
{
    // TODO: Add your control notification handler code here
    m_las=2;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=AshTranslation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgAshTrans::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_Slider.SetPos(m_Ash);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=AshTranslation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}

HBITMAP CDlgAshTrans::Ash()
{
    return AshTranslation(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgAshTrans::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER1))
    {
        m_Ash=m_Slider.GetPos();
        CString str;
        str.Format("%d",m_Slider.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=AshTranslation(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
