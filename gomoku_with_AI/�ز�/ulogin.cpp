//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "ulogin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
  // ��ʼ������
  srand((unsigned)time(NULL)) ;
 this->DoubleBuffered=true;
 UserName->DoubleBuffered=true;
 PassWord->DoubleBuffered=true;
}
//----------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton3Click(TObject *Sender)
{
  this->ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton2Click(TObject *Sender)
{
  //��¼
  if(PassWord->Text.Trim().IsEmpty()||UserName->Text.Trim().IsEmpty())
  {
    ShowMessage("�û��������벻��Ϊ�գ����������롣");
    return;
  }
  AnsiString s="select * from [USER] where useID='"+UserName->Text.Trim()+"'and usepw='"+PassWord->Text.Trim()+"'";
  ADOQuery1->Close();
  ADOQuery1->SQL->Clear();
  ADOQuery1->SQL->Add(s);
  ADOQuery1->Open();
  if(ADOQuery1->RecordCount==0)
  {
    ShowMessage("�û���������������������롣");
    return;
  }
  else
  {
    Form1->UserName=UserName->Text.Trim();
    Form1->gamenum=ADOQuery1->FieldByName("gamenum")->AsInteger;
    Form1->ying=ADOQuery1->FieldByName("ying")->AsInteger;
    Form1->shu=ADOQuery1->FieldByName("shu")->AsInteger;
    Form1->ping=ADOQuery1->FieldByName("ping")->AsInteger;
  }
  this->ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
  // ע��
  if(PassWord->Text.Trim().IsEmpty()||UserName->Text.Trim().IsEmpty())
  {
    ShowMessage("�û��������벻��Ϊ�գ����������롣");
    return;
  }
   String ss="select * from [USER] where useID='"+ UserName->Text.Trim()+"'";
  ADOQuery1->Close();
  ADOQuery1->SQL->Clear();
  ADOQuery1->SQL->Add(ss);
  ADOQuery1->Open();
  if(ADOQuery1->RecordCount>=1)
  {
    ShowMessage("���û����Ѵ��ڣ�������ע�ᣡ���������롣");
    return;
  }


  //
  AnsiString s="insert into [USER](useID,usepw,gamenum,ying,shu,ping) values('"+
  UserName->Text.Trim()+"','"+PassWord->Text.Trim()+"',"
  +String(0)+","+String(0)+","+String(0)+","+String(0)+")";

  ADOQuery1->Close();
  ADOQuery1->SQL->Clear();
  ADOQuery1->SQL->Add(s);
  ADOQuery1->ExecSQL();

    Form1->UserName=UserName->Text.Trim();
    Form1->gamenum=0;
    Form1->ying=0;
    Form1->shu=0;
    Form1->ping=0;
  MessageBox(Handle,"ע��ɹ���","SK������",MB_OK);
  this->ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PassWordKeyPress(TObject *Sender, char &Key)
{
  if(Key==13)
     SpeedButton2->Click();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(Button!=mbLeft) return;
       //�ƶ�����
   ReleaseCapture();
   Perform(WM_NCLBUTTONDOWN,HTCAPTION, 0);
}
//---------------------------------------------------------------------------
