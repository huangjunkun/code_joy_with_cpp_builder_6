// DlgMedianFilt.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgMedianFilt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilt dialog


CDlgMedianFilt::CDlgMedianFilt(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgMedianFilt::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgMedianFilt)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    //�˲����ĸ߶�Ϊ3
    mFilterH = 3;
    //�˲����Ŀ��Ϊ3
    mFilterW = 3;
    //�˲������ĵ�ĺ�����Ϊ1
    mFilterMX= 1;
    //�˲������ĵ��������Ϊ1
    mFilterMY= 1;
    Tbitmap=NULL;
}


void CDlgMedianFilt::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMedianFilt)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMedianFilt, CDialog)
    //{{AFX_MSG_MAP(CDlgMedianFilt)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilt message handlers

void CDlgMedianFilt::OnDestroy()
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
 * ��������: medianFilter()
 * ��������: HBITMAP
 * ��������: ��ֵ�˲�
 *************************************************************************/

HBITMAP CDlgMedianFilt::medianFilter(COLORREF* pco,BITMAP bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
{
    HBITMAP bmp;
    int* FiltValut_R;
    int* FiltValut_G;
    int* FiltValut_B;
    int i,j,cx=bm.bmWidth;
    int r=0,g=0,b=0,k,l;
    COLORREF *pcol=new COLORREF[bm.bmHeight*bm.bmWidth];
    for(k=0; k<bm.bmHeight*bm.bmWidth; k++)
    {
        pcol[k]=pco[k];
    }
    FiltValut_R=new int[mFilterH*mFilterW];
    FiltValut_G=new int[mFilterH*mFilterW];
    FiltValut_B=new int[mFilterH*mFilterW];
    for(i=mFilterMY; i<bm.bmHeight-mFilterH+mFilterMY+1; i++)
    {
        for(j=mFilterMX; j<bm.bmWidth-mFilterW+mFilterMX+1; j++)
        {
            for(k=0; k<mFilterH; k++)
            {
                for(l=0; l<mFilterW; l++)
                {
                    r=GetRValue(pcol[(j-mFilterMX+l)+(i-mFilterMY+k)*cx]);
                    g=GetGValue(pcol[(j-mFilterMX+l)+(i-mFilterMY+k)*cx]);
                    b=GetBValue(pcol[(j-mFilterMX+l)+(i-mFilterMY+k)*cx]);

                    FiltValut_R[k*mFilterW+l]=r;
                    FiltValut_G[k*mFilterW+l]=g;
                    FiltValut_B[k*mFilterW+l]=b;
                }
            }
            r=MedianValue(FiltValut_R,(mFilterH*mFilterW));
            g=MedianValue(FiltValut_G,(mFilterH*mFilterW));
            b=MedianValue(FiltValut_B,(mFilterH*mFilterW));
            pcol[j+i*cx]=RGB(r,g,b);
        }
    }
    bmp=CreateDIBitmap(m_dib.memdc,&RGBBITSBITMAPINFO,
                       CBM_INIT,pcol,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
    delete[] pcol;
    delete[] FiltValut_R;
    delete[] FiltValut_G;
    delete[] FiltValut_B;
    return bmp;
}

/*************************************************************************
 * ��������: MedianValue()
 * ��������: int
 * ��������: �����м�Ԫ��
 *************************************************************************/

int CDlgMedianFilt::MedianValue(int *FiltValue, int mFilterLen)
{
    int i,j;
    int temp;
    for(j=0; j<mFilterLen-1; j++)
    {
        for(i=0; i<mFilterLen-j-1; i++)
        {
            if(FiltValue[i]>FiltValue[i+1])
            {
                temp=FiltValue[i];
                FiltValue[i]=FiltValue[i+1];
                FiltValue[i+1]=temp;
            }
        }
    }
    if((mFilterLen & 1)>0)//������������Ԫ�أ������м�һ��Ԫ��
    {
        temp=FiltValue[(mFilterLen+1)/2];
    }
    else//������ż����Ԫ�أ������м���������ƽ��ֵ
    {
        temp=(FiltValue[mFilterLen/2]+FiltValue[mFilterLen/2+1])/2;
    }
    return temp;
}

BOOL CDlgMedianFilt::OnInitDialog()
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
    Tbitmap=medianFilter(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

HBITMAP CDlgMedianFilt::Filter()
{
    return medianFilter(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgMedianFilt::OnRadio1()
{
    // TODO: Add your control notification handler code here
    //�˲����ĸ߶�Ϊ3
    mFilterH = 3;
    //�˲����Ŀ��Ϊ3
    mFilterW = 3;
    //�˲������ĵ�ĺ�����Ϊ1
    mFilterMX= 1;
    //�˲������ĵ��������Ϊ1
    mFilterMY= 1;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=medianFilter(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgMedianFilt::OnRadio2()
{
    // TODO: Add your control notification handler code here
    //�˲����ĸ߶�Ϊ5
    mFilterH = 5;
    //�˲����Ŀ��Ϊ5
    mFilterW = 5;
    //�˲������ĵ�ĺ�����Ϊ2
    mFilterMX= 2;
    //�˲������ĵ��������Ϊ2
    mFilterMY= 2;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=medianFilter(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}

void CDlgMedianFilt::OnRadio3()
{
    // TODO: Add your control notification handler code here
    //�˲����ĸ߶�Ϊ7
    mFilterH = 7;
    //�˲����Ŀ��Ϊ7
    mFilterW = 7;
    //�˲������ĵ�ĺ�����Ϊ3
    mFilterMX= 3;
    //�˲������ĵ��������Ϊ3
    mFilterMY= 3;
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=medianFilter(m_dib.newpcol,m_dib.newbm,m_dib.NEWRGB32BITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
}
