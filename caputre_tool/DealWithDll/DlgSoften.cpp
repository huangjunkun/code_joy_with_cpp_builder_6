// DlgSoften.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgSoften.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSoften dialog


CDlgSoften::CDlgSoften(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgSoften::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgSoften)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    aver = (float)(1.0/9.0);
    int smoothg[9] = {1,1,1,1,1,1,1,1,1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    Tbitmap=NULL;
}


void CDlgSoften::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgSoften)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSoften, CDialog)
    //{{AFX_MSG_MAP(CDlgSoften)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDCA, OnCancle)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO3, OnRadio2)
    ON_BN_CLICKED(IDC_RADIO4, OnRadio3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSoften message handlers

void CDlgSoften::OnDestroy()
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

void CDlgSoften::OnCancle()
{
    // TODO: Add your control notification handler code here
    this->EndDialog(false);
}

/*************************************************************************
 * 函数名称: TempLate()
 * 函数类型: HBITMAP
 * 函数功能: 图像平滑（消噪声掩膜法）
 *************************************************************************/

HBITMAP CDlgSoften::TempLate(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
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
            rr = (int)(rr*aver);
            gg = (int)(gg*aver);
            bb = (int)(bb*aver);
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
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    return bmp;
}



BOOL CDlgSoften::OnInitDialog()
{
    CMainDlg::OnInitDialog();
    ((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
    // TODO: Add extra initialization here
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
//	((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=TempLate(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSoften::OnRadio1()
{
    // TODO: Add your control notification handler code here
    aver = (float)(1.0/9.0);
    int smoothg[9] = {1,1,1,1,1,1,1,1,1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=TempLate(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgSoften::OnRadio2()
{
    // TODO: Add your control notification handler code here
    aver = (float)(1.0/10.0);
    int smoothg[9] = {1,1,1,1,2,1,1,1,1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=TempLate(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgSoften::OnRadio3()
{
    // TODO: Add your control notification handler code here
    aver = (float)(1.0/16.0);
    int smoothg[9] = {1,2,1,2,4,2,1,2,1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=TempLate(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

HBITMAP CDlgSoften::Soften()
{
    return TempLate(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}
