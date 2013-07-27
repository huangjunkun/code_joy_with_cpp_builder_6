//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RandomPlayUnit.h"
#include "MainUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlayRandomForm *PlayRandomForm;
//---------------------------------------------------------------------------
__fastcall TPlayRandomForm::TPlayRandomForm(TComponent* Owner)
    : TForm(Owner)
{
    DelayTime = new TTimer(this);
    DelayTime->Interval = 2000;
    DelayTime->OnTimer = DelayTimeTimer;
}
//---------------------------------------------------------------------------
void __fastcall TPlayRandomForm::FormCreate(TObject *Sender)
{
    Timer1->Enabled = false;
    Label1->Caption = "";
    Label1->Transparent = true;
    this->AlphaBlend = true;
    this->AlphaBlendValue = 150;
}
//---------------------------------------------------------------------------
void __fastcall TPlayRandomForm::FormShow(TObject *Sender)
{
    Left =  MainForm->Left+(MainForm->Width-Width)/2;
    Top  =  MainForm->Top+(MainForm->Height-Height)/2;
    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPlayRandomForm::Timer1Timer(TObject *Sender)
{
    static  int i=-1;
    //MainForm->Caption = "sss"; //
    ++i;
    i=i%MainForm->ListBoxCheck->Count;
    Label1->Caption = MainForm->ListBoxCheck->Items[0][i];
    if(i==MainForm->RondomNO)
    {
        Timer1->Enabled = false;
        i=-1;
        DelayTime->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TPlayRandomForm::FormKeyPress(TObject *Sender, char &Key)
{
    if(Key==27)
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TPlayRandomForm::DelayTimeTimer(TObject *Sender)
{
    DelayTime->Enabled = false;
    Close();
}
//---------------------------------------------------------------------------
