//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "setclock.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetClock *SetClock;
//---------------------------------------------------------------------------
__fastcall TSetClock::TSetClock(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::FormShow(TObject *Sender)
{
    //记录窗体原来数据
    s_width = MainForm->s_width;
    m_width = MainForm->m_width;
    h_width = MainForm->h_width;
    fontsize = MainForm->fontsize; //秒，分，时针的宽度
    s_color = MainForm->s_color;
    m_color = MainForm->m_color;
    h_color = MainForm->h_color;
    c_color = MainForm->Color;
    f_color = MainForm->Canvas->Font->Color;
//    DateTimePicker1->Refresh(); //?????
    DateTimePicker1->DateTime = Date();
//   DateTimePicker1->Update();  //????????
    RadioGroup1->ItemIndex = -1;
    RadioGroup2->ItemIndex = -2;
    LabeledEdit1->Text = "";
    TrackBar1->Position = MainForm->AlphaBlendValue;
    TabSheet2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::RadioGroup1Click(TObject *Sender)
{
    Sleep(500);
    if(ColorDialog1->Execute())
    {
        switch(RadioGroup1->ItemIndex)
        {
        case 0 :
            c_color =  ColorDialog1->Color;
            break;
        case 1 :
            s_color =  ColorDialog1->Color;
            break;
        case 2 :
            m_color =  ColorDialog1->Color;
            break;
        case 3 :
            h_color =  ColorDialog1->Color;
            break;
        case 4 :
            f_color =  ColorDialog1->Color;
            break;
        default:
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::BitBtnCancelClick(TObject *Sender)
{
//    MainForm->BorderStyle = bsDialog;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::BitBtnOKClick(TObject *Sender)
{
//    MainForm->BorderStyle = bsDialog;
    BitBtnAppClick(Sender);
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::BitBtnSetSizeClick(TObject *Sender)
{
    /*
      MainForm->BorderStyle = bsSizeable;
      MainForm->AutoScroll = false;
      MainForm->SetFocus();      */
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::LabeledEdit1KeyPress(TObject *Sender, char &Key)
{
    /*

      if(Key!=8 || !isdigit(Key) || StrToInt(LabeledEdit1->Text)>4)
      {
          Key = NULL;
      }    */
    if(LabeledEdit1->Text=="")
        return;
    if(Key!=8 && (!isdigit(Key)|| StrToInt(LabeledEdit1->Text)>=4))
    {
        Key = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::BitBtnAppClick(TObject *Sender)
{
    /* */
    MainForm->s_width = s_width;
    MainForm->m_width = m_width;
    MainForm->h_width = h_width;
    MainForm->fontsize = fontsize; //秒，分，时针的宽度
    MainForm->s_color = s_color;
    MainForm->m_color = m_color;
    MainForm->h_color = h_color;
    MainForm->Color = c_color;
    MainForm->f_color = f_color;

    MainForm->StatusBar1->Panels->Items[0]->Text = "   日期： " +
            DateTimePicker1->Date.DateString();
    MainForm->FormPaint(MainForm);
    MainForm->Refresh();
    RadioGroup1->ItemIndex = -1;
    RadioGroup2->ItemIndex = -2;
    LabeledEdit1->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::LabeledEdit1Exit(TObject *Sender)
{
    if(RadioGroup2->ItemIndex!=-1 && LabeledEdit1->Text!="")
    {
        switch(RadioGroup2->ItemIndex)
        {
        case 0 :
            fontsize = StrToInt(LabeledEdit1->Text);
            break;
        case 1 :
            s_width = StrToInt(LabeledEdit1->Text);
            break;
        case 2 :
            m_width = StrToInt(LabeledEdit1->Text);
            break;
        case 3 :
            h_width = StrToInt(LabeledEdit1->Text);
            break;
        default:
            break;
        }
    }
    LabeledEdit1->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TSetClock::BitBtnDefaultClick(TObject *Sender)
{
    MainForm->FormCreate(MainForm);
    MainForm->FormResize(MainForm);
    this->FormShow(Sender);//初始化数据
}
//---------------------------------------------------------------------------



void __fastcall TSetClock::TrackBar1Change(TObject *Sender)
{
    MainForm->AlphaBlend = true;
    MainForm->AlphaBlendValue = TrackBar1->Position;
    if(TrackBar1->Position==225)
        MainForm->AlphaBlend = false;
}
//---------------------------------------------------------------------------


void __fastcall TSetClock::CBTrayIconClick(TObject *Sender)
{
    if(CBTrayIcon->Checked)//true
    {
        //ShowMessage("AddTrayIcon() ");
        MainForm->AddTrayIcon();
        MainForm->HideShowItem->Enabled = true;
    }
    else
    {
        MainForm->DeleteTrayIcon();
        MainForm->HideShowItem->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::CBFormStyleClick(TObject *Sender)
{
    if(CBFormStyle->Checked)
        MainForm->FormStyle = fsStayOnTop;///
    else
        MainForm->FormStyle = fsNormal;
    DWORD dwStyle = ::GetWindowLong(MainForm->Handle, GWL_STYLE);
    ::SetWindowLong(MainForm->Handle, GWL_STYLE, dwStyle | WS_SIZEBOX);
    //修正窗口的实际尺寸与范围
    //以便USER直接调整窗口边沿 //?????????????
    ::MoveWindow(MainForm->Handle, MainForm->Left, MainForm->Top,
                 MainForm->Width, MainForm->Height + 1, true);
}
//---------------------------------------------------------------------------

void __fastcall TSetClock::CBTransparentClick(TObject *Sender)
{
    if(CBTransparent->Checked)
        MainForm->TransparentColor = true;
    else
        MainForm->TransparentColor = false;
}
//---------------------------------------------------------------------------

