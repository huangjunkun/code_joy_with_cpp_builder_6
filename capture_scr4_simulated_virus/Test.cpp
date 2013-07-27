//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("TryVirus.cpp", MyForm);
//---------------------------------------------------------------------------

//#include <Windows.h>
 /*
int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int)
{    //°´×°µ×²ã¼üÅÌ¹³×Ó
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL,
                            LowLevelKeyboardProc, hinstExe, 0) ;
	MessageBox( NULL, TEXT("Alt+Esc, Ctrl+Esc, and Alt+Tab are now disabled.\n")
    TEXT("Click \"Ok\" to terminate this application and re-enable            these keys."),
    TEXT("Disable Low-Level Keys"), MB_OK);
    UnhookWindowsHookEx(hhkLowLevelKybd);
    //return(0);
}     */
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TMyForm), &MyForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
