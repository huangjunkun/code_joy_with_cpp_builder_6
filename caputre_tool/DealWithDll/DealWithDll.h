// DealWithDll.h : main header file for the DEALWITHDLL DLL
//

#if !defined(AFX_DEALWITHDLL_H__06BD85D8_E5EE_48C1_B06B_E79338F8F5ED__INCLUDED_)
#define AFX_DEALWITHDLL_H__06BD85D8_E5EE_48C1_B06B_E79338F8F5ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDealWithDllApp
// See DealWithDll.cpp for the implementation of this class
//

////////////////////////////////////ͼ����ǿ////////////////////////////////////////////
//ͼ��ֱ��ͼ����
HBITMAP HistEnhance(HBITMAP hbitmap);
//��ɫ����������ǿ
HBITMAP GrayLinTrans(HBITMAP hbitmap);
//ͼ����ɫ�����任
HBITMAP LinerTranslation(HBITMAP hbitmap);
//ͼ��ƽ������������Ĥ����
HBITMAP TemplateSoften(HBITMAP hbitmap);
//ͼ��ƽ��������ƽ������
HBITMAP NearbySoften(HBITMAP hbitmap);
//ͼ����
HBITMAP LaplacSharp(HBITMAP hbitmap);
//��ֵ�˲�
HBITMAP MedianFilter(HBITMAP hbitmap);
//ͼ���δ���(�������)
HBITMAP CarveRilievo(HBITMAP hbitmap);
/////////////////////////////////////ͼ�񼸺α任/////////////////////////////////////////////////
//ͼ��ת
HBITMAP ImageRever(HBITMAP hbitmap);
//ͼ����ת
HBITMAP RotaTion(HBITMAP hbitmap);
/////////////////////////////////////////ͼ�񼶱���//////////////////////////////////////////////
//ɫ��/���Ͷ�/�Աȶ� (HSV�任)
HBITMAP HSVTranslation(HBITMAP hbitmap);
//��/��/��(RGB�任)
HBITMAP RGBTranslation(HBITMAP hbitmap);
//ͼ��Ҷȱ任
HBITMAP AshTrans(HBITMAP hbitmap);



class CDealWithDllApp : public CWinApp
{
public:
	CDealWithDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDealWithDllApp)
	public:
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDealWithDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEALWITHDLL_H__06BD85D8_E5EE_48C1_B06B_E79338F8F5ED__INCLUDED_)

