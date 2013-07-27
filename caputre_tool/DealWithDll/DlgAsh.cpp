// DlgAsh.cpp : implementation file
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgAsh.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAsh dialog


CDlgAsh::CDlgAsh(CWnd* pParent /*=NULL*/)
    : CMainDlg(CDlgAsh::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgAsh)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    for(int i=0; i<256; i++)
    {
        nCount[0][i]=0;
        nCount[1][i]=0;
        nCount[2][i]=0;
    }
}


void CDlgAsh::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAsh)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAsh, CDialog)
    //{{AFX_MSG_MAP(CDlgAsh)
    ON_WM_CLOSE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAsh message handlers


BOOL CDlgAsh::OnInitDialog()
{
    CMainDlg::OnInitDialog();

    // TODO: Add extra initialization here
    ColorTotal();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAsh::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    this->EndDialog(false);
    RemoveWindowSkin(this->m_hWnd);
    RemoveDialogSkin();

    CDialog::OnClose();
}

void CDlgAsh::ColorTotal()
{
    int i,j;
    int r=0,g=0,b=0,cx=m_dib.bm.bmWidth;
    for(i=0; i<m_dib.bm.bmWidth; i++)
    {
        for(j=0; j<m_dib.bm.bmHeight; j++)
        {
            r=GetRValue(m_dib.pcol[i+j*cx]);
            g=GetGValue(m_dib.pcol[i+j*cx]);
            b=GetBValue(m_dib.pcol[i+j*cx]);

            nCount[0][r]++;
            nCount[1][g]++;
            nCount[2][b]++;
        }
    }
}

void CDlgAsh::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // TODO: Add your message handler code here
    CString str;// 字符串
    long lMaxCount[3] = {0,0,0};// 最大计数
    int i;

    CDC* pDC = GetDC();
    pDC->SetBkMode(TRANSPARENT);
    CPen* pPenGreen = new CPen;// 创建画笔对象
    pPenGreen->CreatePen(PS_SOLID,2,RGB(0,255,0));// 绿色画笔

    CPen* pPenBlue = new CPen;// 创建画笔对象
    pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0, 255));// 蓝色画笔

    CPen* pPenRed =new CPen;
    pPenRed->CreatePen(PS_SOLID,2,RGB(255,0, 0));// 红色画笔

    pDC->MoveTo(10,10);// 绘制R坐标轴
    pDC->LineTo(10,280);// R垂直轴
    pDC->LineTo(300,280);// R水平轴

    pDC->MoveTo(350,10);// 绘制G坐标轴
    pDC->LineTo(350,280);// G垂直轴
    pDC->LineTo(640,280);// G水平轴


    pDC->MoveTo(10,320);// 绘制B坐标轴
    pDC->LineTo(10,590);// B垂直轴
    pDC->LineTo(300,590);// B水平轴


    str.Format("0");// 写R_X轴刻度值
    pDC->TextOut(10, 283, str);
    str.Format("50");
    pDC->TextOut(60, 283, str);
    str.Format("100");
    pDC->TextOut(110, 283, str);
    str.Format("150");
    pDC->TextOut(160, 283, str);
    str.Format("200");
    pDC->TextOut(210, 283, str);
    str.Format("255");
    pDC->TextOut(265, 283, str);


    str.Format("0");// 写G_X轴刻度值
    pDC->TextOut(350, 283, str);
    str.Format("50");
    pDC->TextOut(400, 283, str);
    str.Format("100");
    pDC->TextOut(450, 283, str);
    str.Format("150");
    pDC->TextOut(500, 283, str);
    str.Format("200");
    pDC->TextOut(550, 283, str);
    str.Format("255");
    pDC->TextOut(605, 283, str);

    str.Format("0");// 写B_X轴刻度值
    pDC->TextOut(10, 593, str);
    str.Format("50");
    pDC->TextOut(60, 593, str);
    str.Format("100");
    pDC->TextOut(110, 593, str);
    str.Format("150");
    pDC->TextOut(160, 593, str);
    str.Format("200");
    pDC->TextOut(210, 593, str);
    str.Format("255");
    pDC->TextOut(265, 593, str);

    for (i = 0; i < 256; i += 5)// 绘制R_X轴刻度
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 10, 280);// 10的倍数
            pDC->LineTo(i + 10, 284);
        }
        else
        {
            pDC->MoveTo(i + 10, 280);
            pDC->LineTo(i + 10, 282);
        }
    }

    for (i = 0; i < 256; i += 5)// 绘制G_X轴刻度
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 350, 280);// 10的倍数
            pDC->LineTo(i + 350, 284);
        }
        else
        {
            pDC->MoveTo(i + 350, 280);
            pDC->LineTo(i + 350, 282);
        }
    }

    for (i = 0; i < 256; i += 5)// 绘制B_X轴刻度
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 10, 590);// 10的倍数
            pDC->LineTo(i + 10, 594);
        }
        else
        {
            pDC->MoveTo(i + 10, 590);
            pDC->LineTo(i + 10, 592);
        }
    }

    pDC->MoveTo(295,275);// 绘制R_X轴箭头
    pDC->LineTo(300,280);
    pDC->LineTo(295,285);

    pDC->MoveTo(10,10);// 绘制R_Y轴箭头
    pDC->LineTo(5,15);
    pDC->MoveTo(10,10);
    pDC->LineTo(15,15);

    pDC->MoveTo(635,275);// 绘制G_X轴箭头
    pDC->LineTo(640,280);
    pDC->LineTo(635,285);

    pDC->MoveTo(350,10);// 绘制G_Y轴箭头
    pDC->LineTo(345,15);
    pDC->MoveTo(350,10);
    pDC->LineTo(355,15);


    pDC->MoveTo(295,585);// 绘制B_X轴箭头
    pDC->LineTo(300,590);
    pDC->LineTo(295,595);

    pDC->MoveTo(10,320);// 绘制B_Y轴箭头
    pDC->LineTo(5,325);
    pDC->MoveTo(10,320);
    pDC->LineTo(15,325);


    for (i =0; i <=255; i ++)// 计算最大计数值
    {
        if (nCount[0][i] > lMaxCount[0])//R是否大于当前最大值
        {
            lMaxCount[0] = nCount[0][i];// 更新最大值
        }
        if (nCount[1][i] > lMaxCount[1])//G是否大于当前最大值
        {
            lMaxCount[1] = nCount[1][i];// 更新最大值
        }
        if (nCount[2][i] > lMaxCount[2])//B是否大于当前最大值
        {
            lMaxCount[2] = nCount[2][i];// 更新最大值
        }
    }
    pDC->MoveTo(10, 25);// 输出R最大计数值
    pDC->LineTo(14, 25);
    str.Format("%d", lMaxCount[0]);
    pDC->TextOut(11, 26, str);

    pDC->MoveTo(350, 25);// 输出G最大计数值
    pDC->LineTo(354, 25);
    str.Format("%d", lMaxCount[1]);
    pDC->TextOut(351, 26, str);

    pDC->MoveTo(10, 335);// 输出B最大计数值
    pDC->LineTo(14, 335);
    str.Format("%d", lMaxCount[2]);
    pDC->TextOut(11, 336, str);

    CGdiObject* pOldPen=pDC->SelectObject(pPenRed);// 更改成红色画笔
    str.Format("图象的R直方图");//输出R标题
    pDC->TextOut(185, 5, str);
    if (lMaxCount[0] > 0)// 判断是否有计数
    {
        for (i = 0; i <= 255; i ++)// 绘制R直方图
        {
            pDC->MoveTo(i + 10, 280);
            pDC->LineTo(i + 10, 280 - (int) (nCount[0][i] * 256 / lMaxCount[0]));
        }
    }

    pDC->SelectObject(pPenGreen);
    str.Format("图象的G直方图");//输出G标题
    pDC->TextOut(525, 5, str);

    if (lMaxCount[1] > 0)// 判断是否有计数
    {
        for (i = 0; i <= 255; i ++)// 绘制G直方图
        {
            pDC->MoveTo(i + 350, 280);
            pDC->LineTo(i + 350, 280 - (int) (nCount[1][i] * 256 / lMaxCount[1]));
        }
    }

    pDC->SelectObject(pPenBlue);
    str.Format("图象的B直方图");//输出B标题
    pDC->TextOut(185, 315, str);
    if (lMaxCount[2] > 0)// 判断是否有计数
    {
        for (i = 0; i <= 255; i ++)// 绘制B直方图
        {
            pDC->MoveTo(i + 10, 590);
            pDC->LineTo(i + 10, 590 - (int) (nCount[2][i] * 256 / lMaxCount[2]));
        }
    }

    pDC->SelectObject(pOldPen);	// 恢复旧画笔

    delete pPenGreen;// 删除新建的画笔对象
    delete pPenBlue;
    delete pPenRed;
    // Do not call CDialog::OnPaint() for painting messages
}
