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
    CString str;// �ַ���
    long lMaxCount[3] = {0,0,0};// ������
    int i;

    CDC* pDC = GetDC();
    pDC->SetBkMode(TRANSPARENT);
    CPen* pPenGreen = new CPen;// �������ʶ���
    pPenGreen->CreatePen(PS_SOLID,2,RGB(0,255,0));// ��ɫ����

    CPen* pPenBlue = new CPen;// �������ʶ���
    pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0, 255));// ��ɫ����

    CPen* pPenRed =new CPen;
    pPenRed->CreatePen(PS_SOLID,2,RGB(255,0, 0));// ��ɫ����

    pDC->MoveTo(10,10);// ����R������
    pDC->LineTo(10,280);// R��ֱ��
    pDC->LineTo(300,280);// Rˮƽ��

    pDC->MoveTo(350,10);// ����G������
    pDC->LineTo(350,280);// G��ֱ��
    pDC->LineTo(640,280);// Gˮƽ��


    pDC->MoveTo(10,320);// ����B������
    pDC->LineTo(10,590);// B��ֱ��
    pDC->LineTo(300,590);// Bˮƽ��


    str.Format("0");// дR_X��̶�ֵ
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


    str.Format("0");// дG_X��̶�ֵ
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

    str.Format("0");// дB_X��̶�ֵ
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

    for (i = 0; i < 256; i += 5)// ����R_X��̶�
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 10, 280);// 10�ı���
            pDC->LineTo(i + 10, 284);
        }
        else
        {
            pDC->MoveTo(i + 10, 280);
            pDC->LineTo(i + 10, 282);
        }
    }

    for (i = 0; i < 256; i += 5)// ����G_X��̶�
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 350, 280);// 10�ı���
            pDC->LineTo(i + 350, 284);
        }
        else
        {
            pDC->MoveTo(i + 350, 280);
            pDC->LineTo(i + 350, 282);
        }
    }

    for (i = 0; i < 256; i += 5)// ����B_X��̶�
    {
        if ((i & 1) == 0)
        {
            pDC->MoveTo(i + 10, 590);// 10�ı���
            pDC->LineTo(i + 10, 594);
        }
        else
        {
            pDC->MoveTo(i + 10, 590);
            pDC->LineTo(i + 10, 592);
        }
    }

    pDC->MoveTo(295,275);// ����R_X���ͷ
    pDC->LineTo(300,280);
    pDC->LineTo(295,285);

    pDC->MoveTo(10,10);// ����R_Y���ͷ
    pDC->LineTo(5,15);
    pDC->MoveTo(10,10);
    pDC->LineTo(15,15);

    pDC->MoveTo(635,275);// ����G_X���ͷ
    pDC->LineTo(640,280);
    pDC->LineTo(635,285);

    pDC->MoveTo(350,10);// ����G_Y���ͷ
    pDC->LineTo(345,15);
    pDC->MoveTo(350,10);
    pDC->LineTo(355,15);


    pDC->MoveTo(295,585);// ����B_X���ͷ
    pDC->LineTo(300,590);
    pDC->LineTo(295,595);

    pDC->MoveTo(10,320);// ����B_Y���ͷ
    pDC->LineTo(5,325);
    pDC->MoveTo(10,320);
    pDC->LineTo(15,325);


    for (i =0; i <=255; i ++)// ����������ֵ
    {
        if (nCount[0][i] > lMaxCount[0])//R�Ƿ���ڵ�ǰ���ֵ
        {
            lMaxCount[0] = nCount[0][i];// �������ֵ
        }
        if (nCount[1][i] > lMaxCount[1])//G�Ƿ���ڵ�ǰ���ֵ
        {
            lMaxCount[1] = nCount[1][i];// �������ֵ
        }
        if (nCount[2][i] > lMaxCount[2])//B�Ƿ���ڵ�ǰ���ֵ
        {
            lMaxCount[2] = nCount[2][i];// �������ֵ
        }
    }
    pDC->MoveTo(10, 25);// ���R������ֵ
    pDC->LineTo(14, 25);
    str.Format("%d", lMaxCount[0]);
    pDC->TextOut(11, 26, str);

    pDC->MoveTo(350, 25);// ���G������ֵ
    pDC->LineTo(354, 25);
    str.Format("%d", lMaxCount[1]);
    pDC->TextOut(351, 26, str);

    pDC->MoveTo(10, 335);// ���B������ֵ
    pDC->LineTo(14, 335);
    str.Format("%d", lMaxCount[2]);
    pDC->TextOut(11, 336, str);

    CGdiObject* pOldPen=pDC->SelectObject(pPenRed);// ���ĳɺ�ɫ����
    str.Format("ͼ���Rֱ��ͼ");//���R����
    pDC->TextOut(185, 5, str);
    if (lMaxCount[0] > 0)// �ж��Ƿ��м���
    {
        for (i = 0; i <= 255; i ++)// ����Rֱ��ͼ
        {
            pDC->MoveTo(i + 10, 280);
            pDC->LineTo(i + 10, 280 - (int) (nCount[0][i] * 256 / lMaxCount[0]));
        }
    }

    pDC->SelectObject(pPenGreen);
    str.Format("ͼ���Gֱ��ͼ");//���G����
    pDC->TextOut(525, 5, str);

    if (lMaxCount[1] > 0)// �ж��Ƿ��м���
    {
        for (i = 0; i <= 255; i ++)// ����Gֱ��ͼ
        {
            pDC->MoveTo(i + 350, 280);
            pDC->LineTo(i + 350, 280 - (int) (nCount[1][i] * 256 / lMaxCount[1]));
        }
    }

    pDC->SelectObject(pPenBlue);
    str.Format("ͼ���Bֱ��ͼ");//���B����
    pDC->TextOut(185, 315, str);
    if (lMaxCount[2] > 0)// �ж��Ƿ��м���
    {
        for (i = 0; i <= 255; i ++)// ����Bֱ��ͼ
        {
            pDC->MoveTo(i + 10, 590);
            pDC->LineTo(i + 10, 590 - (int) (nCount[2][i] * 256 / lMaxCount[2]));
        }
    }

    pDC->SelectObject(pOldPen);	// �ָ��ɻ���

    delete pPenGreen;// ɾ���½��Ļ��ʶ���
    delete pPenBlue;
    delete pPenRed;
    // Do not call CDialog::OnPaint() for painting messages
}
