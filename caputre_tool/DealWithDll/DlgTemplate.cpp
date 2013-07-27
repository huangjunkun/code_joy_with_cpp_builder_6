// DlgTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate dialog


CDlgTemplate::CDlgTemplate(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgTemplate::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgTemplate)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    aver = (float)(1.0/4.0);
    int smoothg[9] = {0,1,0,1,0,1,0,1,0};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    Tbitmap=NULL;
}


void CDlgTemplate::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgTemplate)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemplate, CDialog)
    //{{AFX_MSG_MAP(CDlgTemplate)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
    ON_BN_CLICKED(IDC_RADIO5, OnRadio8)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate message handlers

void CDlgTemplate::OnDestroy()
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

//DEL void CDlgTemplate::OnOK()
//DEL {
//DEL 	// TODO: Add extra validation here
//DEL 	if(((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck()==1)
//DEL 	{
//DEL 		aver = (float)(1.0/4.0);
//DEL 		int smoothg[9] = {0,1,0,1,0,1,0,1,0};
//DEL 		for(int k=0;k<9;k++)
//DEL 		{
//DEL 			smooth[k]=smoothg[k];
//DEL 		}
//DEL 	}
//DEL 	else if(((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck()==1)
//DEL 	{
//DEL 		aver = (float)(1.0/8.0);
//DEL 		int smoothg[9] = {1,1,1,1,0,1,1,1,1};
//DEL 		for(int k=0;k<9;k++)
//DEL 		{
//DEL 			smooth[k]=smoothg[k];
//DEL 		}
//DEL 	}
//DEL 	CDialog::OnOK();
//DEL }

/*************************************************************************
 * 函数名称: Template()
 * 函数类型: HBITMAP
 * 函数功能: 图像平滑（邻域平均法）
 *************************************************************************/

HBITMAP CDlgTemplate::Template(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
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

BOOL CDlgTemplate::OnInitDialog()
{
    CMainDlg::OnInitDialog();
    ((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(m_dib.newbmp);
//	((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(m_dib.newbmp);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Template(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    // TODO: Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

HBITMAP CDlgTemplate::PicTemplate()
{
    return Template(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgTemplate::OnRadio4()
{
    // TODO: Add your control notification handler code here
    aver = (float)(1.0/4.0);
    int smoothg[9] = {0,1,0,1,0,1,0,1,0};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Template(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgTemplate::OnRadio8()
{
    // TODO: Add your control notification handler code here
    aver = (float)(1.0/8.0);
    int smoothg[9] = {1,1,1,1,0,1,1,1,1};
    for(int k=0; k<9; k++)
    {
        smooth[k]=smoothg[k];
    }
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Template(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}
