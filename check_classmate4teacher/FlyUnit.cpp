//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "ThreadUnit.h"
#include "FlyUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"
TFlyForm *FlyForm;
//---------------------------------------------------------------------------
__fastcall TFlyForm::TFlyForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFlyForm::OnWmBkgnd(TMessage &Msg)
{
    ///????///
    Msg.Result=true;
}
//---------------------------------------------------------------------------
void __fastcall TFlyForm::FormCreate(TObject *Sender)
{
//隐藏所有图片，并使图片处于同一位置
    TImage *images[]= {Image1,Image2,Image3,Image4,Image5,Image6};
    Caption=""; //窗口无标题
    BorderStyle=bsNone; //无边框
    BorderIcons.Clear(); //无系统菜单及按钮
    FormStyle=fsStayOnTop; //使窗口始终处于最上层
    for(int i=0; i<IMAGECOUNT; i++)
    {
        Images[i]=images[i];
        Images[i]->Visible=false;
        Images[i]->Transparent=true; //图片透明
        Images[i]->Left=0;
        Images[i]->Top=0;
    }
    Width=Image1->Width;
    Height=Image1->Height;
    Left=Screen->Width+20;
    Top=Screen->Height+20;
//使应用程序不出现在任务栏
    SetWindowLong(this->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    //ShowMessage("SetWindowLong(...)");
}
//---------------------------------------------------------------------------
void __fastcall TFlyForm::ThreadDone(TObject *)
{
//线程结束时自动调用
    StartFlyAngelAction->Enabled=true;
    StopFlyAngelAction->Enabled=false;
    Left = Screen->Width+20;
}
//---------------------------------------------------------------------------

void __fastcall TFlyForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//若线程结束后才能退出程序
    if(StartFlyAngelAction->Enabled)
        Action=caFree;
    else
        Action=caNone;
}

//---------------------------------------------------------------------------

void __fastcall TFlyForm::StartFlyAngelActionExecute(TObject *Sender)
{
    End = false;
    StartFlyAngelAction->Enabled = false;
    StopFlyAngelAction->Enabled = true;
    //创建线程
    flythread = new TFlyThread(false);
    //followthread = new TFollowThread(false);
    flythread->OnTerminate = ThreadDone; //指定线程结束事件处理函数
}
//---------------------------------------------------------------------------

void __fastcall TFlyForm::StopFlyAngelActionExecute(TObject *Sender)
{
    End = true;
    flythread->Terminate();
}
//---------------------------------------------------------------------------

