// DlgLinTrans.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgLinTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinTrans dialog


CDlgLinTrans::CDlgLinTrans(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgLinTrans::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgLinTrans)
    R_oralow = 0;
    R_orahig = 0;
    G_oralow = 0;
    G_orahig = 0;
    B_oralow = 0;
    B_orahig = 0;
    R_newlow = 0;
    R_newhig = 0;
    G_newlow = 0;
    G_newhig = 0;
    B_newlow = 0;
    B_newhig = 0;
    //}}AFX_DATA_INIT
    Tbitmap=NULL;
}


void CDlgLinTrans::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLinTrans)
    DDX_Text(pDX, IDC_EDIT1, R_oralow);
    DDV_MinMaxInt(pDX, R_oralow, 0, 255);
    DDX_Text(pDX, IDC_EDIT2, R_orahig);
    DDV_MinMaxInt(pDX, R_orahig, 0, 255);
    DDX_Text(pDX, IDC_EDIT3, G_oralow);
    DDV_MinMaxInt(pDX, G_oralow, 0, 255);
    DDX_Text(pDX, IDC_EDIT4, G_orahig);
    DDV_MinMaxInt(pDX, G_orahig, 0, 255);
    DDX_Text(pDX, IDC_EDIT5, B_oralow);
    DDV_MinMaxInt(pDX, B_oralow, 0, 255);
    DDX_Text(pDX, IDC_EDIT6, B_orahig);
    DDV_MinMaxInt(pDX, B_orahig, 0, 255);
    DDX_Text(pDX, IDC_EDIT7, R_newlow);
    DDV_MinMaxInt(pDX, R_newlow, 0, 255);
    DDX_Text(pDX, IDC_EDIT8, R_newhig);
    DDV_MinMaxInt(pDX, R_newhig, 0, 255);
    DDX_Text(pDX, IDC_EDIT9, G_newlow);
    DDV_MinMaxInt(pDX, G_newlow, 0, 255);
    DDX_Text(pDX, IDC_EDIT10, G_newhig);
    DDV_MinMaxInt(pDX, G_newhig, 0, 255);
    DDX_Text(pDX, IDC_EDIT11, B_newlow);
    DDV_MinMaxInt(pDX, B_newlow, 0, 255);
    DDX_Text(pDX, IDC_EDIT12, B_newhig);
    DDV_MinMaxInt(pDX, B_newhig, 0, 255);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLinTrans, CDialog)
    //{{AFX_MSG_MAP(CDlgLinTrans)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_ANCEL, OnAncel)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON1, OnButtonlook)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinTrans message handlers

void CDlgLinTrans::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    this->EndDialog(false);
    CDialog::OnClose();
}

/*************************************************************************
 * 函数名称: grayLinTrans()
 * 函数类型: HBITMAP
 * 函数功能: 图像颜色度显示范围拉伸
 *************************************************************************/

HBITMAP CDlgLinTrans::grayLinTrans(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP m_bmp;
    int i,j;
    int r=0,g=0,b=0,cx=bm.bmWidth;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(int k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    for(i=0; i<bm.bmWidth; i++)
    {
        for(j=0; j<bm.bmHeight; j++)
        {
            r=GetRValue(pcol[i+j*cx]);
            g=GetGValue(pcol[i+j*cx]);
            b=GetBValue(pcol[i+j*cx]);

            r=Choosevault(r,R_oralow,R_orahig,R_newlow,R_newhig);
            g=Choosevault(g,G_oralow,G_orahig,G_newlow,G_newhig);
            b=Choosevault(b,B_oralow,B_orahig,B_newlow,B_newhig);
            /*			if(r<0)
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
            				b=255;*/
            pcol[i+j*cx]=RGB(r,g,b);
        }
    }
    m_bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                         CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    return m_bmp;
}

/*************************************************************************
 * 函数名称: Choosevault()
 * 函数类型: int
 * 函数功能: 颜色变换，将[oralow,orahig]拉伸为[newlow,newhig]
 *************************************************************************/

int CDlgLinTrans::Choosevault(int vault, int oralow, int orahig, int newlow, int newhig)
{
    int outmap=0;
    if(vault <= oralow)
    {
        if(newlow > 0)
        {
            outmap=newlow;
        }
        else
        {
            outmap=0;
        }
    }
    else if(vault <= orahig)
    {
        if(orahig != oralow)
        {
            outmap=newlow + (newhig - newlow) * (vault - oralow)/(orahig-oralow);
        }
        else
        {
            outmap=newlow;
        }
    }
    else if(vault <= newhig)
    {
        if(newhig <= 255)
        {
            outmap=newhig;
        }
        else
        {
            outmap=255;
        }
    }
    return outmap;
}

void CDlgLinTrans::OnAncel()
{
    // TODO: Add your control notification handler code here
    OnClose();
}


void CDlgLinTrans::OnDestroy()
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

HBITMAP CDlgLinTrans::LinTrans()
{
    return grayLinTrans(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

BOOL CDlgLinTrans::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLinTrans::OnButtonlook()
{
    // TODO: Add your control notification handler code here
    this->UpdateData(true);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=grayLinTrans(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}
