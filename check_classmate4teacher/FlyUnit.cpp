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
//��������ͼƬ����ʹͼƬ����ͬһλ��
    TImage *images[]= {Image1,Image2,Image3,Image4,Image5,Image6};
    Caption=""; //�����ޱ���
    BorderStyle=bsNone; //�ޱ߿�
    BorderIcons.Clear(); //��ϵͳ�˵�����ť
    FormStyle=fsStayOnTop; //ʹ����ʼ�մ������ϲ�
    for(int i=0; i<IMAGECOUNT; i++)
    {
        Images[i]=images[i];
        Images[i]->Visible=false;
        Images[i]->Transparent=true; //ͼƬ͸��
        Images[i]->Left=0;
        Images[i]->Top=0;
    }
    Width=Image1->Width;
    Height=Image1->Height;
    Left=Screen->Width+20;
    Top=Screen->Height+20;
//ʹӦ�ó��򲻳�����������
    SetWindowLong(this->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    //ShowMessage("SetWindowLong(...)");
}
//---------------------------------------------------------------------------
void __fastcall TFlyForm::ThreadDone(TObject *)
{
//�߳̽���ʱ�Զ�����
    StartFlyAngelAction->Enabled=true;
    StopFlyAngelAction->Enabled=false;
    Left = Screen->Width+20;
}
//---------------------------------------------------------------------------

void __fastcall TFlyForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//���߳̽���������˳�����
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
    //�����߳�
    flythread = new TFlyThread(false);
    //followthread = new TFollowThread(false);
    flythread->OnTerminate = ThreadDone; //ָ���߳̽����¼�������
}
//---------------------------------------------------------------------------

void __fastcall TFlyForm::StopFlyAngelActionExecute(TObject *Sender)
{
    End = true;
    flythread->Terminate();
}
//---------------------------------------------------------------------------

