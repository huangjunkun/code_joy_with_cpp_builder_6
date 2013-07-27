//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFlyBody.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFlyBodyForm *FlyBodyForm;
//---------------------------------------------------------------------------
__fastcall TFlyBodyForm::TFlyBodyForm(TComponent* Owner)
    : TForm(Owner)
{
    //Images = {Image1,Image2,Image3,Image4,Image5,Image6};
    Images1[0] = Image1;
    Images1[1] = Image2;
    Images1[2] = Image3;
    Images1[3] = Image4;
    Images1[4] = Image5;
    Images1[5] = Image6;
    Images2[0] = Image7;
    Images2[1] = Image8;
    Images2[2] = Image9;
    Images2[3] = Image10;
    Images2[4] = Image11;
    Images2[5] = Image12;

    Top = Screen->Height + 10;
    Left = Screen->Width + 10;
}
//---------------------------------------------------------------------------
void __fastcall TFlyBodyForm::OnWmBkgnd(TMessage &Msg)
{
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
      (for example, when a window is resized). The message is sent to prepare an
      invalidated portion of a window for painting.           */
    Msg.Result = true;
}
//---------------------------------------------------------------------------
void __fastcall TFlyBodyForm::FormCreate(TObject *Sender)
{
    for(int i=0; i<IMAGECOUNT; i++)
    {
        Images1[i]->Visible=false;
        Images1[i]->Transparent=true; //图片透明
        Images1[i]->Top = Screen->Height + 10;
        Images1[i]->Left = Screen->Width + 10;
        Images2[i]->Visible=false;
        Images2[i]->Transparent=true; //图片透明
        Images2[i]->Top = Screen->Height + 10;
        Images2[i]->Left = Screen->Width + 10;
    }
    FormStyle=fsStayOnTop; //使窗口始终处于最上层
//使应用程序不出现在任务栏
    ::SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
}
//---------------------------------------------------------------------------

