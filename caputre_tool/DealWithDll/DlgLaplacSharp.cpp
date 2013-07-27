// DlgLaplacSharp.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgLaplacSharp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLaplacSharp dialog


CDlgLaplacSharp::CDlgLaplacSharp(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgLaplacSharp::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgLaplacSharp)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    int smoothg[9] = {0,-1,0,-1,4,-1,0,-1,0};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    m_laplas=0;
    Tbitmap=NULL;
}


void CDlgLaplacSharp::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLaplacSharp)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLaplacSharp, CDialog)
    //{{AFX_MSG_MAP(CDlgLaplacSharp)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLaplacSharp message handlers

void CDlgLaplacSharp::OnDestroy()
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
 * 函数名称: laplacSharp()
 * 函数类型: HBITMAP
 * 函数功能: 图像锐化
 *************************************************************************/

HBITMAP CDlgLaplacSharp::laplacSharp(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
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
    switch(m_laplas)
    {
    case 0:
    {
        for (i = 1; i < nWidth-1; i++)
        {
            for (j = 1; j < nHeight-1; j++)
            {
                int rr = 0, gg = 0, bb = 0;
                int index = 0;
                for (int col = -1; col <= 1; col++)
                {
                    for (int row = -1; row <= 1; row++)
                    {
                        COLORREF clr = pcol[i+row+(j+col)*nWidth];
                        rr += GetRValue(clr) * smooth[index];
                        gg += GetGValue(clr) * smooth[index];
                        bb += GetBValue(clr) * smooth[index];
                        index++;
                    }
                }
                // 处理溢出点
                if ( rr > 255 ) rr = 255;
                else if ( rr < 0 ) rr = -rr;
                if ( gg > 255 ) gg = 255;
                else if ( gg < 0 ) gg = -gg;
                if ( bb > 255 ) bb = 255;
                else if ( bb < 0 ) bb = -bb;
                pcol[ (i)+ (j)*nWidth]= RGB(rr,gg,bb);
            }
        }
        break;
    }
    case 1:
    {
        int r[2]= {0,0},g[2]= {0,0},b[2]= {0,0},cx=nWidth;
        for(i=1; i<nWidth-1; i++)
        {
            for(j=1; j<nHeight-1; j++)
            {
                r[1]=GetRValue(pcol[i+j*cx]);
                g[1]=GetGValue(pcol[i+j*cx]);
                b[1]=GetBValue(pcol[i+j*cx]);

                r[0]=GetRValue(pcol[(i-1)+(j-1)*cx]);
                g[0]=GetGValue(pcol[(i-1)+(j-1)*cx]);
                b[0]=GetBValue(pcol[(i-1)+(j-1)*cx]);
                r[1]+=(r[1]-r[0])/2;
                g[1]+=(g[1]-g[0])/2;
                b[1]+=(b[1]-b[0])/2;

                if(r[1]<0)r[1]=0;
                if(g[1]<0)g[1]=0;
                if(b[1]<0)b[1]=0;
                if(r[1]>255)r[1]=255;
                if(g[1]>255)g[1]=255;
                if(b[1]>255)b[1]=255;
                pcol[i+j*cx]=RGB(r[1],g[1],b[1]);
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

BOOL CDlgLaplacSharp::OnInitDialog()
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
    Tbitmap=laplacSharp(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

HBITMAP CDlgLaplacSharp::Sharp()
{
    return laplacSharp(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgLaplacSharp::OnRadio1()
{
    // TODO: Add your control notification handler code here
    int smoothg[9] = {0,-1,0,-1,4,-1,0,-1,0};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    m_laplas=0;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=laplacSharp(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgLaplacSharp::OnRadio2()
{
    // TODO: Add your control notification handler code here
    int smoothg[9] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    m_laplas=0;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=laplacSharp(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgLaplacSharp::OnRadio3()
{
    // TODO: Add your control notification handler code here
    m_laplas=1;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=laplacSharp(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}
