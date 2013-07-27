//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("CH5.res");
USEFORM("Main.cpp", MainForm);
USEFORM("SockSet.cpp", SockForm);
USEFORM("DebugFm.cpp", DebugForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->HelpFile = "CH5.hlp";
     Application->Title = "Îå×ÓÆå";
     Application->CreateForm(__classid(TMainForm), &MainForm);
     Application->CreateForm(__classid(TSockForm), &SockForm);
     Application->CreateForm(__classid(TDebugForm), &DebugForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
