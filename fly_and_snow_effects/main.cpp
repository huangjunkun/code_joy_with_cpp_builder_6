//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitThread.h"
#include "main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnWmBkgnd(TMessage &Msg)
{
    ///????///
    Msg.Result=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
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
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mStartClick(TObject *Sender)
{
    End = false;
    mStart->Enabled = false;
    mClose->Enabled = false;
    mEnd->Enabled = true;
//�����߳�
    flythread = new TFlyThread(false);
    followthread = new TFollowThread(false);
    flythread->OnTerminate = ThreadDone; //ָ���߳̽����¼�������
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mEndClick(TObject *Sender)
{
    End = true;
    flythread->Terminate();
    flythread->Terminate();
}

void __fastcall TMainForm::ThreadDone(TObject *)
{
//�߳̽���ʱ�Զ�����
    mStart->Enabled=true;
    mClose->Enabled=true;
    mEnd->Enabled=false;
    Left = Screen->Width+20;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
//��������ʾʱ�Զ���ʼ����
    mStartClick(this);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//���߳̽���������˳�����
    if(mStart->Enabled)
        Action=caFree;
    else
        Action=caNone;
}

//---------------------------------------------------------------------------

