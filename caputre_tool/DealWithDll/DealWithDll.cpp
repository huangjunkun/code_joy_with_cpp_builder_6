// DealWithDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DealWithDll.h"
#include "MainDlg.h"
#include "DlgAsh.h"
#include "DlgLinTrans.h"
#include "DlgSoften.h"
#include "DlgTemplate.h"
#include "DlgMedianFilt.h"
#include "DlgLaplacSharp.h"
#include "DlgCarveRilievo.h"
#include "DlgRever.h"
#include "DlgRot.h"
#include "DlgLiner.h"
#include "DlgHsv.h"
#include "DlgRgb.h"
#include "DlgAshTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CDealWithDllApp

BEGIN_MESSAGE_MAP(CDealWithDllApp, CWinApp)
    //{{AFX_MSG_MAP(CDealWithDllApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDealWithDllApp construction

CDealWithDllApp::CDealWithDllApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDealWithDllApp object

CDealWithDllApp theApp;

HBITMAP GrayLinTrans(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgLinTrans dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.LinTrans();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}

HBITMAP HistEnhance(HBITMAP hbitmap)
{
    CDlgAsh dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.DoModal();
    }
    return NULL;
}

HBITMAP TemplateSoften(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgSoften dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Soften();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}

HBITMAP NearbySoften(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgTemplate dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.PicTemplate();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}

HBITMAP MedianFilter(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgMedianFilt dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            CCmdTarget mg;
            mg.BeginWaitCursor();
            m_bp=dlg.Filter();
            mg.EndWaitCursor();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP LaplacSharp(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgLaplacSharp dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Sharp();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP CarveRilievo(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgCarveRilievo dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.CarOrRil();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP ImageRever(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgRever dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.ReverPic();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}



HBITMAP RotaTion(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgRot dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.Initdlg(hbitmap);
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.RotationPic();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP LinerTranslation(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgLiner dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Translat();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP HSVTranslation(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgHsv dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Hsv();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}


HBITMAP RGBTranslation(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgRgb dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Rgb();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}




HBITMAP AshTrans(HBITMAP hbitmap)
{
    HBITMAP m_bp;
    CDlgAshTrans dlg;
    if(dlg.m_dib.GetColorref(hbitmap))
    {
        dlg.m_dib.Initnewpic();
        int nResponse=dlg.DoModal();
        if(nResponse==IDOK)
        {
            m_bp=dlg.Ash();
        }
        else
        {
            return hbitmap;
        }
    }
    else
    {
        return hbitmap;
    }
    return m_bp;
}
