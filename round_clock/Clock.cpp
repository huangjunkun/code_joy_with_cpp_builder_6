//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", MainForm);
USEFORM("setclock.cpp", SetClock);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {

        Application->Initialize();
        //����Ӧ�ó���ֻ����һ��
        Application->Title="OnlyMyClock";
        CreateMutex(NULL,False,"OnlyMyClock");
        if(GetLastError()==ERROR_ALREADY_EXISTS)
            return 0;
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TSetClock), &SetClock);
        Application->CreateForm(__classid(TSetClock), &SetClock);
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
