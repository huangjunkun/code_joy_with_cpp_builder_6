/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------

//键盘钩子 封锁 windows 热键
LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam) //LRESULT --long
{
    static bool bCapture = false;
    KBDLLHOOKSTRUCT *pkbhs;
    if (code < 0)
    {
        return CallNextHookEx(OldHook,code, wParam, lParam);
    }
    pkbhs = (KBDLLHOOKSTRUCT*) lParam;

    if (pkbhs->vkCode == 81 && GetAsyncKeyState(VK_MENU)<0 && GetAsyncKeyState(VK_CONTROL)<0)//
    {
        ShowMessage("Hello");
        return 1; //
    }
    if (!bCapture && pkbhs->vkCode== 65 && GetAsyncKeyState(VK_LSHIFT) &&
            GetAsyncKeyState(VK_LCONTROL)<0) //pkbhs->flags&LLKHF_ALTDOWN && // ALT
    {
        //ShowMessage("Hello");     // CTRL + SHIFT + 'a' 截图
        bCapture = true;
        MainForm->miCaptureRegionClick(MainForm);
        bCapture = false;
        return 1;
    }


    return CallNextHookEx(OldHook,code, wParam, lParam);
}
//---------------------------------------------------------------------------
void  TMainForm::CaptureWinImage(TRect rect)
{
    pBitmap->Width = rect.Right - rect.Left;
    pBitmap->Height = rect.Bottom - rect.Top;
    // 从截获的桌面图像中获取指定区域的图像
    HDC  ScreenDC= GetDC(0);
    try
    {
        StretchBlt(pBitmap->Canvas->Handle, 0, 0,
                   pBitmap->Width, pBitmap->Height, ScreenDC,
                   rect.Left, rect.Top,
                   pBitmap->Width,
                   pBitmap->Height,
                   SRCCOPY);
    }
    __finally
    {
        ReleaseDC(0, ScreenDC);
    }
}
//---------------------------------------------------------------------------
void  TMainForm::CaptureDesktop(HDC ImageHandle)
{
    HDC hdc = GetDC(0); //获取桌面显示设备描述
    //图像拷贝、、、
    BitBlt(ImageHandle,0,0,Screen->Width,
           Screen->Height,hdc,0,0,SRCCOPY);
    //释放桌面设备HDC
    ReleaseDC(0, hdc);
}
//---------------------------------------------------------------------------
HWND TMainForm::GetTopWin(void)
{
    //获得当前活动窗口句柄
    HWND hwnd=GetTopWindow(0);
    while (hwnd != 0)
    {
        /******************************/
        if (IsWindowVisible(hwnd)&&
                (GetWindowLong(hwnd,GWL_EXSTYLE) & WS_EX_TOPMOST)==0)
        {
            //如果所有窗体都被最小化了，桌面便成了当前活动窗口了
            if (IsIconic(hwnd))
                hwnd=GetDesktopWindow();
            return hwnd;
        }
        hwnd=GetNextWindow(hwnd,GW_HWNDNEXT);
    }
    return NULL;
}
//---------------------------------------------------------------------------

