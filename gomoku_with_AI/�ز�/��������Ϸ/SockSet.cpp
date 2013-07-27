//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SockSet.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSockForm *SockForm;
//---------------------------------------------------------------------------
__fastcall TSockForm::TSockForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSockForm::Button1Click(TObject *Sender)
{
if(RB1->Checked)
  {
  MainForm->ServerSocket1->Close();
  MainForm->ClientSocket1->Close();
  MainForm->ClientSocket1->Port=Edit2->Text.ToInt();
  MainForm->ClientSocket1->Host=Edit1->Text;
  MainForm->ClientSocket1->Open();
  MainForm->Label4->Caption="";
  }
if(RB2->Checked)
  {
  MainForm->ClientSocket1->Close();
  MainForm->ServerSocket1->Close();
  MainForm->ServerSocket1->Port=Edit2->Text.ToInt();
  MainForm->ServerSocket1->Open();
  Edit1->Text=MainForm->ServerSocket1->Socket->LocalHost;
  MainForm->Label5->Caption="";
  }
}
//---------------------------------------------------------------------------
void __fastcall TSockForm::FormPaint(TObject *Sender)
{
  int width=ClientWidth,h=ClientHeight;
  for(int i=h;i>=0;i--)
    {
      Canvas->Pen->Color=RGB(i*255/h/10,i*255/h/20,i*255/h);
      Canvas->MoveTo(0,i);
      Canvas->LineTo(width,i);
    }

}
//---------------------------------------------------------------------------
void __fastcall TSockForm::RB2Click(TObject *Sender)
{
Edit1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TSockForm::RB1Click(TObject *Sender)
{
Edit1->Text="";
Edit1->Enabled=true;
}
//---------------------------------------------------------------------------

