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

////////////////////////////////////图像增强////////////////////////////////////////////
//图像直方图分析
HBITMAP HistEnhance(HBITMAP hbitmap);
//颜色分量线性增强
HBITMAP GrayLinTrans(HBITMAP hbitmap);
//图像颜色分量变换
HBITMAP LinerTranslation(HBITMAP hbitmap);
//图像平滑（消噪声掩膜法）
HBITMAP TemplateSoften(HBITMAP hbitmap);
//图像平滑（邻域平均法）
HBITMAP NearbySoften(HBITMAP hbitmap);
//图像锐化
HBITMAP LaplacSharp(HBITMAP hbitmap);
//中值滤波
HBITMAP MedianFilter(HBITMAP hbitmap);
//图像层次处理(浮雕或雕刻)
HBITMAP CarveRilievo(HBITMAP hbitmap);
/////////////////////////////////////图像几何变换/////////////////////////////////////////////////
//图像翻转
HBITMAP ImageRever(HBITMAP hbitmap);
//图像旋转
HBITMAP RotaTion(HBITMAP hbitmap);
/////////////////////////////////////////图像级别处理//////////////////////////////////////////////
//色度/饱和度/对比度 (HSV变换)
HBITMAP HSVTranslation(HBITMAP hbitmap);
//红/绿/蓝(RGB变换)
HBITMAP RGBTranslation(HBITMAP hbitmap);
//图像灰度变换
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

