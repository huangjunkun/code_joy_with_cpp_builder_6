//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitHello.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"
#pragma resource "Music.RES"// ...
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)//
{
    //---
    imageList = ImageList1;
    bmpWidth = imageList->Width; //200
    bmpHeight = imageList->Height;//200
    bmpIndex = 0;
    for(int i=0; i<Screen->Width; i+=bmpWidth) //
        for(int j=Screen->Height-bmpHeight-30; j>0-bmpHeight; j-=bmpHeight)
            ptVec.push_back(TPoint(i ,j));
    indexVec.reserve(ptVec.size());
    for(unsigned int i=0; i<ptVec.size(); i++)
        indexVec.push_back(i);
    random_shuffle(indexVec.begin() ,indexVec.end());
    blockIndex = 0;//bIsPlay = true;
    rose_Tread = new TRose_Thread(Canvas ,imageList);
    rose = new TRose(this ,Canvas ,imageList);
    // ----
    TImage* images[] = {Image13 ,Image14 ,Image15 ,Image16 ,Image17 ,Image18 ,\
                        Image19 ,Image20 ,Image21 ,Image22 ,Image23 ,Image24
                       };
    TSnow::initImageExamples(images ,sizeof(images)/sizeof(TImage*));//...
    snow = new TSnow(this);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
    // ---
    //rose_Tread->doStop(); //...should ...
    rose_Tread->Terminate();
    if(snow) delete snow;
    if(rose) delete rose;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnWmBkgnd(TMessage &Msg)
{
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
      (for example, when a window is resized). The message is sent to prepare an
      invalidated portion of a window for painting.           */
    Msg.Result = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    /*       */
    time_t  t;
    srand(time(&t));//初始化随机种子
    BorderStyle = bsNone;
    WindowState = wsMaximized;
    FormStyle = fsStayOnTop; //fsNormal
    //使应用程序不出现在任务栏
    ::SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    LabelHello->Visible = false;
    LabelHello->Caption = "Happy birthday";
    LabelHello->Left = (Screen->Width-LabelHello->Width)>>1;
    LabelHello->Top = (Screen->Height-LabelHello->Height)>>1;//;
    // ---
    sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
    HRSRC temp=FindResourceA(HInstance,"START", "WAV");//从内存中载入声音
    assert(temp);// ...
    HGLOBAL h=LoadResource(HInstance,temp);
    char *chWavHandle = (char *)LockResource(h);
    if(!sndPlaySound(chWavHandle,SND_MEMORY|SND_SYNC))//or :  SND_ASYNC,SND_LOOP
        MessageDlg("sndPlaySound ,Error" ,mtWarning , \
                   TMsgDlgButtons()<<mbOK ,0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    //---
    Timer1->Enabled = true;
    //rose_Tread->doPlay();
    sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
    HRSRC temp=FindResourceA(HInstance,"MUSIC", "WAV");//从内存中载入声音
    assert(temp);// ...
    /* // or:
    if(temp==NULL)
      MessageDlg("FindResource DEFAULTMUSIC ,Error" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
    else  {}            */
    HGLOBAL h=LoadResource(HInstance,temp);
    char    *chWavHandle = (char *)LockResource(h);
    if(!sndPlaySound(chWavHandle,SND_MEMORY|SND_ASYNC|SND_LOOP))//or :SND_SYNC  ,SND_LOOP
        MessageDlg("sndPlaySound ,Error" ,mtWarning , \
                   TMsgDlgButtons()<<mbOK ,0);
    snow->doSnow(TSnow::middleSnow);
    rose->doPlay();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //---
    TrayIcon1->Visible = false;
    //sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
    HRSRC temp=FindResourceA(HInstance,"EXIT", "WAV");//从内存中载入声音
    assert(temp);// ...
    /*  */
    HGLOBAL h=LoadResource(HInstance,temp);
    char *chWavHandle = (char *)LockResource(h);
    if(!sndPlaySound(chWavHandle,SND_MEMORY|SND_SYNC))//or :  SND_ASYNC,SND_LOOP
        MessageDlg("sndPlaySound ,Error" ,mtWarning , \
                   TMsgDlgButtons()<<mbOK ,0);
    rose_Tread->doStop();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::doPlay()
{
    //---
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miHelloClick(TObject *Sender)
{
    Hide();// ....
    TrayIcon1->Visible = false;
    HelloForm->FormStyle = fsStayOnTop; //
    HelloForm->ShowModal();
    FormStyle = fsStayOnTop; //Repaint();
    Show(); // ....
    TrayIcon1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miExitClick(TObject *Sender)
{
    //---
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
    if(Key==27)     miExitClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    LabelHello->Visible = !LabelHello->Visible;
    //LabelHello->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miTESTClick(TObject *Sender)
{
    //---
    //rose_Tread->doStop();
    snow->doSnow(TSnow::middleSnow);
    if(rose->isPlay())
        rose->doStop();
    else
        rose->doPlay();
    //rose->setPalyInterval(200);
    /*=====================*/
}
//---------------------------------------------------------------------------



