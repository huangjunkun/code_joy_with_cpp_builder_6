/*
   * ���򿪷��ߣ� �ƿ�����������
   * ��Ŀʱ�䣺��ʼ����:  2009-08. ��������:  2009-09
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------

//���̹��� ���� windows �ȼ�
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
        //ShowMessage("Hello");     // CTRL + SHIFT + 'a' ��ͼ
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
    // �ӽػ������ͼ���л�ȡָ�������ͼ��
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
    HDC hdc = GetDC(0); //��ȡ������ʾ�豸����
    //ͼ�񿽱�������
    BitBlt(ImageHandle,0,0,Screen->Width,
           Screen->Height,hdc,0,0,SRCCOPY);
    //�ͷ������豸HDC
    ReleaseDC(0, hdc);
}
//---------------------------------------------------------------------------
HWND TMainForm::GetTopWin(void)
{
    //��õ�ǰ����ھ��
    HWND hwnd=GetTopWindow(0);
    while (hwnd != 0)
    {
        /******************************/
        if (IsWindowVisible(hwnd)&&
                (GetWindowLong(hwnd,GWL_EXSTYLE) & WS_EX_TOPMOST)==0)
        {
            //������д��嶼����С���ˣ��������˵�ǰ�������
            if (IsIconic(hwnd))
                hwnd=GetDesktopWindow();
            return hwnd;
        }
        hwnd=GetNextWindow(hwnd,GW_HWNDNEXT);
    }
    return NULL;
}
//---------------------------------------------------------------------------

