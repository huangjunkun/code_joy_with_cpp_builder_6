//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
using namespace std;

#pragma hdrstop
//Skin++
//#include "Skin++\SkinPPBCB.h"
//CSkinPPDynamicCallDll SkinPPObj("Skin++\\SkinPPBCB.dll");
//---------------------------------------------------------------------------
USEFORM("MainUnit.cpp", MainForm);
USEFORM("RandomPlayUnit.cpp", PlayRandomForm);
USEFORM("About.cpp", AboutBox);
USEFORM("FlyUnit.cpp", FlyForm);
USEFORM("ShowNameUnit.cpp", ShowNameForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //Skin++
    //SkinPPObj.LoadSkin("Skin++\\PixOS.ssk",false);
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TPlayRandomForm), &PlayRandomForm);
        Application->CreateForm(__classid(TAboutBox), &AboutBox);
        Application->CreateForm(__classid(TFlyForm), &FlyForm);
        Application->CreateForm(__classid(TShowNameForm), &ShowNameForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        ofstream   fout;
        fout.open("BugLog.log" ,ios::app|ios::out);
        fout << Now().DateTimeString().c_str() << "-------"
        <<  exception.Message.c_str() << endl;
        fout.close();
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
            /*----   */
            Application->ShowException(&exception);
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
