// DlgRot.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgRot.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRot dialog


CDlgRot::CDlgRot(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgRot::IDD, pParent)
{
    m_mark=1;
    //{{AFX_DATA_INIT(CDlgRot)
    m_rotAngle = 0;
    //}}AFX_DATA_INIT
    Tbitmap=NULL;
}


void CDlgRot::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRot)
    DDX_Control(pDX, IDC_SLIDER1, m_slider);
    DDX_Text(pDX, IDC_EDIT1, m_rotAngle);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRot, CDialog)
    //{{AFX_MSG_MAP(CDlgRot)
    ON_WM_DESTROY()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_BUTTON1, OnButtonLook)
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRot message handlers

BOOL CDlgRot::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    CSpinButtonCtrl* pSpinAng=(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2);
    pSpinAng->SetRange(0,360);

    ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
    m_slider.SetRange(0, 360, TRUE);
    m_slider.SetTicFreq(360/10);
    m_slider.SetPos(0);
    ((CStatic *)GetDlgItem(IDC_STATIC1))->SetBitmap(newbmp);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(newbmp);
//	Initdlg();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRot::OnDestroy()
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

#define pi 3.1415926535
double AngleToRadian(int angle)
{
    return ((angle)*pi/180.0);
}

/*************************************************************************
 * 函数名称: Rotation()
 * 函数类型: HBITMAP
 * 函数功能: 图像旋转
 *************************************************************************/

HBITMAP CDlgRot::Rotation(COLORREF* pco,BITMAP Bm,BITMAPINFOHEADER RGBBITSBITMAPINFO)
{

    float fRotateAngle = (float) AngleToRadian(m_rotAngle);// 将旋转角度从度转换到弧度
    float fSina = (float) sin((double)fRotateAngle);// 计算旋转角度的正余弦
    float fCosa = (float) cos((double)fRotateAngle);
    float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;// 旋转前四个角的坐标（以图象中心为坐标系原点）
    float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;// 旋转后四个角的坐标（以图象中心为坐标系原点）
    long	lSrcWidth=Bm.bmWidth;      //图象的宽度和高度
    long	lSrcHeight=Bm.bmHeight;
    long	lDstWidth;      //临时图象的宽度和高度
    long	lDstHeight;
    fSrcX1 = (float) (- (lSrcWidth  - 1) / 2);// 计算原图的四个角的坐标
    fSrcY1 = (float) (  (lSrcHeight - 1) / 2);
    fSrcX2 = (float) (  (lSrcWidth  - 1) / 2);
    fSrcY2 = (float) (  (lSrcHeight - 1) / 2);
    fSrcX3 = (float) (- (lSrcWidth  - 1) / 2);
    fSrcY3 = (float) (- (lSrcHeight - 1) / 2);
    fSrcX4 = (float) (  (lSrcWidth  - 1) / 2);
    fSrcY4 = (float) (- (lSrcHeight - 1) / 2);

    fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;// 计算新图四个角的坐标
    fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
    fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
    fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
    fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
    fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
    fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
    fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

    lDstWidth= (long) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);// 计算旋转后的图象实际宽度
    lDstHeight= (long) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);// 计算旋转后的图象高度

    float varFloat1;        //浮点参数变量1
    float varFloat2;        //浮点参数变量2
    float varFloat3;
    float varFloat4;
    varFloat1= (float) (-0.5 * (lSrcWidth - 1) * fCosa - 0.5 * (lSrcHeight - 1) * fSina// 将经常用到的两个常数事先求出，以便作为常数使用
                        + 0.5 * (lSrcWidth  - 1));
    varFloat2= (float) ( 0.5 * (lSrcWidth - 1) * fSina - 0.5 * (lSrcHeight - 1) * fCosa
                         + 0.5 * (lSrcHeight - 1));
    varFloat3= (float) (-0.5 * (lDstWidth - 1) * fCosa - 0.5 * (lDstHeight - 1) * fSina// 将经常用到的两个常数事先求出，以便作为常数使用
                        + 0.5 * (lSrcWidth  - 1));
    varFloat4= (float) ( 0.5 * (lDstWidth - 1) * fSina - 0.5 * (lDstHeight - 1) * fCosa
                         + 0.5 * (lSrcHeight - 1));
    long i;                 //行循环变量
    long j;                 //列循环变量
    long i1;                 //行循环变量
    long j1;                 //列循环变量
    HBITMAP gg;
    switch(m_mark)
    {
    case 1:
    {
        COLORREF* pcol2=new COLORREF[Bm.bmHeight*Bm.bmWidth];
        for(i = 0; i < lSrcHeight; i++)// 行操作
        {
            for(j = 0; j < lSrcWidth; j++)// 列操作
            {

                i1= (long) (-((float) j) * fSina + ((float) i) * fCosa + varFloat2 + 0.5);// 计算该像素在源DIB中的坐标
                j1= (long) ( ((float) j) * fCosa + ((float) i) * fSina + varFloat1 + 0.5);
                if( (j1>= 0) && (j1< lSrcWidth) && (i1>= 0) && (i1< lSrcHeight))
                {
                    // 判断是否在源图内
                    pcol2[j+i*lSrcWidth]=pco[j1+i1*lSrcWidth];
                }
                else
                {
                    pcol2[j+i*lSrcWidth] = RGB(255,255,255);// 源图中不存在的像素，赋为255
                }
            }
        }


        gg=CreateDIBitmap(memdc,&RGBBITSBITMAPINFO,
                          CBM_INIT,pcol2,(BITMAPINFO*)&RGBBITSBITMAPINFO,DIB_RGB_COLORS);
        delete[] pcol2;
        break;
    }
    case 2:
    {
        COLORREF* pcol2=new COLORREF[lDstWidth*lDstHeight];
        for(i = 0; i < lDstHeight; i++)// 行操作
        {
            for(j = 0; j < lDstWidth; j++)// 列操作
            {

                i1= (long) (-((float) j) * fSina + ((float) i) * fCosa + varFloat4 + 0.5);// 计算该像素在源DIB中的坐标
                j1= (long) ( ((float) j) * fCosa + ((float) i) * fSina + varFloat3 + 0.5);
                if( (j1>= 0) && (j1< lSrcWidth) && (i1>= 0) && (i1< lSrcHeight))
                {
                    // 判断是否在源图内
                    pcol2[j+i*lDstWidth]=pco[j1+i1*lSrcWidth];
                }
                else
                {
                    pcol2[j+i*lDstWidth] = RGB(255,255,255);// 源图中不存在的像素，赋为255
                }
            }
        }
        BITMAPINFOHEADER RGB32BITSBITMAPINFO1=
        {
            sizeof(BITMAPINFOHEADER),lDstWidth,lDstHeight,
            1,bm.bmPlanes*bm.bmBitsPixel,BI_RGB,0,0,0,0
        };
        gg=CreateDIBitmap(memdc,&RGB32BITSBITMAPINFO1,
                          CBM_INIT,pcol2,(BITMAPINFO*)&RGB32BITSBITMAPINFO1,DIB_RGB_COLORS);
        delete[] pcol2;
        break;
    }
    }

    return gg;
}

void CDlgRot::OnOK()
{
    // TODO: Add extra validation here

    CDialog::OnOK();
}


HBITMAP Zoom(HBITMAP bitmap,int lDstWidth,int lDstHeight)
{
    HDRAWDIB hdraw;
    COLORREF*pcol;
    HBITMAP srcbmp;
    float fverRatio;
    float fhorRatio;
    BITMAP bm;
    hdraw=DrawDibOpen();
    CBitmap bmp;
    bmp.Attach(bitmap);
    bmp.GetBitmap(&bm);
    fverRatio=((float)lDstWidth)/bm.bmWidth;
    fhorRatio=((float)lDstHeight)/bm.bmHeight;
    BITMAPINFOHEADER RGB32BITSBITMAPINFO=
    {
        sizeof(BITMAPINFOHEADER),bm.bmWidth,bm.bmHeight,
        1,bm.bmPlanes*bm.bmBitsPixel,BI_RGB,0,0,0,0
    };
    HDC memdc=CreateCompatibleDC(NULL);
    srcbmp=CreateDIBSection(memdc,(BITMAPINFO*)&RGB32BITSBITMAPINFO,
                            DIB_RGB_COLORS,(VOID**)&pcol,NULL,0);
    if(srcbmp)
    {
        HBITMAP hOldBmp=(HBITMAP)SelectObject(memdc,srcbmp);
        HDC hDC=CreateCompatibleDC(memdc);
        if(hDC)
        {
            HBITMAP hOldBmp2=(HBITMAP)SelectObject(hDC,bmp);
            //将DDB的数据复制到DIB中
            BitBlt(memdc,0,0,bm.bmWidth,bm.bmHeight,hDC,
                   0,0,SRCCOPY);
            SelectObject(hDC,hOldBmp2);
            DeleteDC(hDC);
        }
    }
    COLORREF *pcol1=new COLORREF[lDstWidth*lDstHeight];
    int i,j;
    int i1,j1;
    for(j=0; j<lDstHeight; j++)
    {
        for(i=0; i<lDstWidth; i++)
        {
            i1=(int)(i/fverRatio+0.5);
            j1=(int)(j/fhorRatio+0.5);
            if((i1>=0) && (i1<bm.bmWidth) && (j1>=0) && (j1<bm.bmHeight))
            {
                pcol1[i+j*lDstWidth]=pcol[i1+j1*bm.bmWidth];
            }
            else
            {
                pcol1[i+j*lDstWidth]=RGB(255,255,255);
            }
        }
    }
    HBITMAP newpicture;
    BITMAPINFOHEADER RGB32BITSBITMAPINFO1=
    {
        sizeof(BITMAPINFOHEADER),lDstWidth,lDstHeight,
        1,bm.bmPlanes*bm.bmBitsPixel,BI_RGB,0,0,0,0
    };
    newpicture=CreateDIBitmap(memdc,&RGB32BITSBITMAPINFO1,
                              CBM_INIT,pcol1,(BITMAPINFO*)&RGB32BITSBITMAPINFO1,DIB_RGB_COLORS);
    DrawDibClose(hdraw);
    delete[] pcol1;
    bmp.Detach();
    return newpicture;
}


void CDlgRot::Initdlg(HBITMAP m_bmp)
{
    int wider,height;
    if(m_dib.bm.bmWidth>m_dib.bm.bmHeight)
    {
        wider=100;
        height=(int)(100*((float)m_dib.bm.bmHeight)/m_dib.bm.bmWidth);
    }
    else
    {
        height=100;
        wider=(int)(100*((float)m_dib.bm.bmWidth)/m_dib.bm.bmHeight);
    }
    newbmp=Zoom(m_bmp,wider,height);
    if(newbmp!=NULL)
    {
        HDRAWDIB hdraw;
        HBITMAP srcbmp;

        hdraw=DrawDibOpen();
        CBitmap bmp;
        bmp.Attach(newbmp);
        bmp.GetBitmap(&bm);
        RGB32BITSBITMAPINFO.biSize=sizeof(BITMAPINFOHEADER);
        RGB32BITSBITMAPINFO.biWidth=bm.bmWidth;
        RGB32BITSBITMAPINFO.biHeight=bm.bmHeight;
        RGB32BITSBITMAPINFO.biPlanes=1;
        RGB32BITSBITMAPINFO.biBitCount=bm.bmPlanes*bm.bmBitsPixel;
        RGB32BITSBITMAPINFO.biCompression=BI_RGB;
        RGB32BITSBITMAPINFO.biSizeImage=0;
        RGB32BITSBITMAPINFO.biXPelsPerMeter=0;
        RGB32BITSBITMAPINFO.biYPelsPerMeter=0;
        RGB32BITSBITMAPINFO.biClrUsed=0;
        RGB32BITSBITMAPINFO.biClrImportant=0;
        memdc=CreateCompatibleDC(NULL);
        srcbmp=CreateDIBSection(memdc,(BITMAPINFO*)&RGB32BITSBITMAPINFO,
                                DIB_RGB_COLORS,(VOID**)&pcol,NULL,0);
        if(srcbmp)
        {
            HBITMAP hOldBmp=(HBITMAP)SelectObject(memdc,srcbmp);
            HDC hDC=CreateCompatibleDC(memdc);
            if(hDC)
            {
                HBITMAP hOldBmp2=(HBITMAP)SelectObject(hDC,bmp);
                //将DDB的数据复制到DIB中
                BitBlt(memdc,0,0,bm.bmWidth,bm.bmHeight,hDC,
                       0,0,SRCCOPY);
                SelectObject(hDC,hOldBmp2);
                DeleteDC(hDC);
            }
        }

        DrawDibClose(hdraw);
        bmp.Detach();
    }
}


void CDlgRot::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
    if (pScrollBar == (CScrollBar*)GetDlgItem(IDC_SLIDER1))
    {
        m_rotAngle=m_slider.GetPos();
        CString str;
        str.Format("%d",m_slider.GetPos());
        ((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
        if(Tbitmap!=NULL)
        {
            DeleteObject(Tbitmap);
            Tbitmap=NULL;
        }
        Tbitmap=Rotation(pcol,bm,RGB32BITSBITMAPINFO);
        ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    }
}

void CDlgRot::OnButtonLook()
{
    // TODO: Add your control notification handler code here
    this->UpdateData();
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Rotation(pcol,bm,RGB32BITSBITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    m_slider.SetPos(m_rotAngle);
}

HBITMAP CDlgRot::RotationPic()
{
    return Rotation(m_dib.pcol,m_dib.bm,m_dib.RGB32BITSBITMAPINFO);
}

void CDlgRot::OnRadio1()
{
    // TODO: Add your control notification handler code here
    m_mark=1;
}

void CDlgRot::OnRadio2()
{
    // TODO: Add your control notification handler code here
    m_mark=2;
}

void CDlgRot::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    this->UpdateData();
    m_slider.SetPos(m_rotAngle);
    if(Tbitmap!=NULL)
    {
        DeleteObject(Tbitmap);
        Tbitmap=NULL;
    }
    Tbitmap=Rotation(pcol,bm,RGB32BITSBITMAPINFO);
    ((CStatic *)GetDlgItem(IDC_STATIC2))->SetBitmap(Tbitmap);
    *pResult = 0;
}
