//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "Region.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{ /*
    this->WindowState = wsMaximized ;
    this->BorderStyle = bsNone ;
    this->FormStyle = fsStayOnTop ;
    Image1->Align = alClient ;
    //this->Hide() ; */
}
//---------------------------------------------------------------------------
void     TMainForm::CaptureDesktop(HDC ImageHandle )
{
    HDC hdc = GetDC(0) ;
    BitBlt(ImageHandle ,0 ,0 ,Screen->Width ,
            Screen->Height ,hdc ,0 ,0 ,SRCCOPY ) ;
    ReleaseDC(0 ,hdc) ;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==27)
        Close() ;
}
//---------------------------------------------------------------------------



