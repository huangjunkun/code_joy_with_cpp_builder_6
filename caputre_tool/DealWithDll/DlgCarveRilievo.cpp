// DlgCarveRilievo.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgCarveRilievo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCarveRilievo dialog


CDlgCarveRilievo::CDlgCarveRilievo(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgCarveRilievo::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgCarveRilievo)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_laplas=1;
    Tbitmap=NULL;
}


void CDlgCarveRilievo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgCarveRilievo)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCarveRilievo, CDialog)
    //{{AFX_MSG_MAP(CDlgCarveRilievo)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCarveRilievo message handlers

void CDlgCarveRilievo::OnDestroy()
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
 * 函数名称: CarveOrRilievo()
 * 函数类型: HBITMAP
 * 函数功能: 浮雕或雕刻效果
 *************************************************************************/

HBITMAP CDlgCarveRilievo::CarveOrRilievo(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP bmp;
    int i,j;
    int nWidth = bm.bmWidth;
    int nHeight = bm.bmHeight;
    int r[2],g[2],b[2];
    int r0,g0,b0;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(int k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    switch(m_laplas)
    {
    case 1:
    {

        for(i=0; i<nWidth-1; i++)
        {
            for(j=0; j<nHeight-1; j++)
            {
                r[0]=GetRValue(pcol[(i)+(j)*nWidth]);
                g[0]=GetGValue(pcol[(i)+(j)*nWidth]);
                b[0]=GetBValue(pcol[(i)+(j)*nWidth]);

                r[1]=GetRValue(pcol[(i+1)+(j+1)*nWidth]);
                g[1]=GetGValue(pcol[(i+1)+(j+1)*nWidth]);
                b[1]=GetBValue(pcol[(i+1)+(j+1)*nWidth]);

                r0=r[1]-r[0]+128;
                g0=g[1]-g[0]+128;
                b0=b[1]-b[0]+128;
                if(r0>255)
                    r0 = 255;
                else if(r0<0)
                    r0 = 0;
                if(g0>255)
                    g0 = 255;
                else if(r0<0)
                    g0 = 0;
                if(b0>255)
                    b0 = 255;
                else if(r0<0)
                    b0 = 0;
                pcol[i+j*nWidth]=RGB(r0,g0,b0);
            }
        }
        break;
    }
    case 2:
    {
        for(i=nWidth-1; i>0; i--)
        {
            for(j=nHeight-1; j>0; j--)
            {
                r[0]=GetRValue(pcol[(i)+(j)*nWidth]);
                g[0]=GetGValue(pcol[(i)+(j)*nWidth]);
                b[0]=GetBValue(pcol[(i)+(j)*nWidth]);

                r[1]=GetRValue(pcol[(i-1)+(j-1)*nWidth]);
                g[1]=GetGValue(pcol[(i-1)+(j-1)*nWidth]);
                b[1]=GetBValue(pcol[(i-1)+(j-1)*nWidth]);

                r0=r[1]-r[0]+128;
                g0=g[1]-g[0]+128;
                b0=b[1]-b[0]+128;
                if(r0>255)
                    r0 = 255;
                else if(r0<0)
                    r0 = 0;
                if(g0>255)
                    g0 = 255;
                else if(r0<0)
                    g0 = 0;
                if(b0>255)
                    b0 = 255;
                else if(r0<0)
                    b0 = 0;
                pcol[i+j*nWidth]=RGB(r0,g0,b0);
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

BOOL CDlgCarveRilievo::OnInitDialog()
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
    Tbitmap=CarveOrRilievo(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCarveRilievo::OnRadio1()
{
    // TODO: Add your control notification handler code here
    m_laplas=1;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=CarveOrRilievo(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgCarveRilievo::OnRadio2()
{
    // TODO: Add your control notification handler code here
    m_laplas=2;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=CarveOrRilievo(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

HBITMAP CDlgCarveRilievo::CarOrRil()
{
    return CarveOrRilievo(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}
