/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

/*
//Skin++
#include ".\\Skin++\SkinPPBCB.h"
CSkinPPDynamicCallDll SkinPPObj(".\\Skin++\\SkinPPBCB.dll");

//Skin++
#include "SkinPPBCB.h"
CSkinPPDynamicCallDll SkinPPObj("SkinPPBCB.dll");
*/
USEFORM("Main.cpp", MainForm);
USEFORM("Region.cpp", RForm);
USEFORM("AboutUnit.cpp", AboutBox);
//---------------------------------------------------------------------------
DWORD WINAPI ExitWhile(LPVOID lpParameter)  //
{
    do
    {
        HWND    hWnd = FindWindow(NULL ,"UIPOWER");// Form1
        if(hWnd!=NULL)
        {
            //ShowMessage("hWnd!=NULL");
            HWND    hChildWnd = FindWindowEx(hWnd ,NULL ,NULL ,"否(&N)");
            if(hChildWnd!=NULL)
            {
                PostMessage(hChildWnd ,WM_KEYDOWN ,(WPARAM)'N' ,NULL);
                break;
            }
        }
        Sleep(100);
    }
    while(true);
    return	1;
}
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    //Skin++
    //HANDLE hMyThread=CreateThread(NULL,0,ExitWhile,NULL,0,NULL);
    //SkinPPObj.LoadSkin("PixOS.ssk",false);
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TRForm), &RForm);
        Application->CreateForm(__classid(TAboutBox), &AboutBox);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    //CloseHandle(hMyThread);
    return 0;
}
//---------------------------------------------------------------------------
