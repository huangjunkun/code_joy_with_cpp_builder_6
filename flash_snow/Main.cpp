//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    //��ʼ���������
    time_t  t;
    srand((unsigned) time(&t));
    this->DoubleBuffered = true;
    TimerNewSnow->Enabled = false;
    MediaPlayer = new TMediaPlayer(this);
    MediaPlayer->Parent = this;
    MediaPlayer->Visible = false;
    downrate = 2;
}
//---------------------------------------------------------------------------
void    CallDllFuncA(String DllName ,String FuncName)
{
    HINSTANCE   ins;
    ins = LoadLibrary(DllName.c_str());//"MyWindowsDll.dll"
    if(ins==NULL)
        throw "�Ҳ������ӿ�";

    FARPROC  proc = GetProcAddress(ins ,FuncName.c_str()); //  "_Show_Hello"
    if(proc==NULL)
    {
        FreeLibrary(ins);
        throw "�Ҳ�����������ַ";
    }
    proc();
    if(!FreeLibrary(ins))
    {
        throw "�ͷ����ӿ�ʧ�ܣ�";
    }
}
//---------------------------------------------------------------------------
void    CallDllFuncB(String DllName ,String FuncName ,String Caption)
{
    HINSTANCE   ins;
    ins = LoadLibrary(DllName.c_str());
    if(ins==NULL)
        throw "�Ҳ������ӿ�";

    FARPROC  proc = GetProcAddress(ins ,FuncName.c_str());
    if(proc==NULL)
    {
        FreeLibrary(ins);
        throw "�Ҳ�����������ַ";
    }

    typedef void (*FUNC) (char*);
    FUNC aFunc = (FUNC)proc;
    aFunc(Caption.c_str());

    if(!FreeLibrary(ins))
    {
        throw "�ͷ����ӿ�ʧ�ܣ�";
    }
}
//---------------------------------------------------------------------------
void    TMainForm::NewSnow(int newnum)
{
    TImage  *snow;
    FreeSnow  freesnow;
    try
    {
        for(int i=0; i<newnum; i++) //
        {
            //!!!!!!!!!!!!  ImageExample[(i%SNOWKINDS)] //��ImageExample��ʼ��ѩ��
            snow = new TImage(this);  // freesnow_vec[i].snow this->Controls[i]
            snow->Visible = false;
            snow->Parent = this;
            snow->Stretch = true;
            snow->Transparent = true;
            snow->Picture->Assign(ImageExample[(i%SNOWKINDS)]->Picture->Bitmap);
            snow->Width = ImageExample[(i%SNOWKINDS)]->Width;
            snow->Height = ImageExample[(i%SNOWKINDS)]->Height;
            freesnow.snow = snow; //
            freesnow.free = true;
            freesnow.snow->Top = 0;
            //freesnow.snow->Visible = false;
            freesnow_vec.push_back(freesnow);
        }
    }
    catch(...)
    {
        delete  snow;
        ShowMessage("NewSnow() ����!!!");
    }
    //delete  snow;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    /* */
    //MediaPlayer1->Rewind();   //���õ�ǰλ��Ϊý�忪ʼλ��
    //ShowMessage("���ý���ļ�ʥ����.wma Copy����Ӧ�ó���ͬһĿ¼��");
    GlobalDeleteAtom(GlobalFindAtom(" ȫ��ԭ�� "));
    ControlBarSet->Visible = false;//�������ÿ���
    this->Color = clBlack;
    this->TransparentColorValue = this->Color;
    this->TransparentColor = true;
    this->WindowState = wsMaximized;
    this->BorderStyle = bsNone;
    LabelHello->Caption = " Happy New Year ";  //Birthday
    LabelHello->Transparent = true;
    LabelHello->Left = Screen->Width - LabelHello->Width;
    LabelHello->Top  = Screen->Height -LabelHello->Height*2;
    FreeSnow  freesnow;
    for(int i=0; i<this->ControlCount; i++) //
    {
        if(String(this->Controls[i]->ClassName())=="TImage")
        {
            //   ShowMessage(String(i));
            freesnow.snow = this->Controls[i]; //
            freesnow.free = true;
            freesnow.snow->Top = 0;
            freesnow.snow->Visible = false;
            freesnow_vec.push_back(freesnow);
            if(i<SNOWKINDS)//��ȡSNOWKINDS��ѩ������--�Ա����ƣ�NewSnow(...))
                ImageExample[i] = (TImage*)this->Controls[i];
        }
    }
    NewSnow(30);//��New 30��ѩ����������
    //ShowMessage(String(freesnow_vec.size()));
    int   snownum = freesnow_vec.size();
    //for(int k=0;k<snownum/2;k++)
    for(int k=0; k<snownum; k++) //  unsigned
    {
        queue_index.push(k);
        queue_index.push(snownum-k-1);
    }
    //ʹӦ�ó��򲻳�����������
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    LabelReport->Caption  = "�����������BugҪ˵��";
    try
    {
        /*
          */
        //ShowMessage("���ý���ļ�ʥ����.wav Copy����Ӧ�ó���ͬһĿ¼��");
        MediaPlayerFlag = true;
        String    path = ExtractFilePath(Application->ExeName) + "\\"+"Music.mp3";
        MediaPlayer->FileName = path;
        MediaPlayer->Open();
        MediaPlayer->Play();
        //�첽��ѭ��������ָ���ļ�--,SSND_ASYNC | ND_LOOP | SND_FILENAME
        //OR : BOOL sndPlaySound(LPCSTR lpszSound,    UINT fuSound); API ���� wav�ļ�
        // sndPlaySound(path.c_str() ,SND_ASYNC + SND_LOOP +SND_FILENAME);//
        //��̬�������ӿ⺯����������
        CallDllFuncA("MyWindowsDll.dll" ,"_Show_Hello");
        //or :PlaySound(path.c_str() ,NULL ,SND_FILENAME); //?????
    }
    catch(...)
    {
        MediaPlayerFlag = false;
        ShowMessage("���ý���ļ� Music.Mp3��MyWindowsDll.dll \nһͬCopy����Ӧ�ó���ͬһĿ¼��");
        Application->ProcessMessages();
        TimerNewSnow->Enabled = true;
    }
    TimerNewSnow->Enabled = true;/*
    __finally
    {
        TimerNewSnow->Enabled = true;
    }  */


    //ShowMessage(String(queue_index.size()));
}
//---------------------------------------------------------------------------
void    TMainForm::RandSnow()
{
    if(queue_index.empty())   //busysnow.size()>=40
    {
        //ShowMessage("queue_index.empty");
        //TimerNewSnow->Enabled = false;
        //TimerDown->Enabled = false;
        return;
    }
    int num = -1;
    num = queue_index.front();
    queue_index.pop();
    freesnow_vec[num].free = false;
    //ShowMessage("11111111111111111111111");
    GOFORWARD   goforward;
    goforward.y = downrate;//�����ٶ�
    goforward.x = rand()%6-3; //����Ʈ���ٶ�
    BusySnow    snowflake;//ѩ��
    snowflake.snow = freesnow_vec[num].snow;
    snowflake.snow->Left =  rand()%Width;    //Screen->Width
    snowflake.goforward = goforward;
    snowflake.index = num;
    snowflake.snow->Visible = true;

    busysnow.push_back(snowflake);
    //ShowMessage("222222222222222222222222");

}
//---------------------------------------------------------------------------
bool    TMainForm::CheckOver(int left ,int top)
{
    if(left > Screen->Width || left < 0 ||       //   Screen->Width
            top > Screen->Height)    // || top <0     Screen->Height
        return  true;
    else
        return  false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TimerDownTimer(TObject *Sender)
{
    for(unsigned int i=0; i< busysnow.size(); i++)
    {
        busysnow[i].snow->Left += busysnow[i].goforward.x;
        busysnow[i].snow->Top  += busysnow[i].goforward.y;
        if(CheckOver(busysnow[i].snow->Left ,busysnow[i].snow->Top))
        {
            queue_index.push(busysnow[i].index);
            freesnow_vec[busysnow[i].index].free = true; //���ԡ�����������
            freesnow_vec[busysnow[i].index].snow->Top = 0;
            freesnow_vec[busysnow[i].index].snow->Visible = false;
            busysnow.erase(busysnow.begin()+i);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimerNewSnowTimer(TObject *Sender)
{
    if(MediaPlayerFlag==true && MediaPlayer->Position==MediaPlayer->Length)
        MediaPlayer->Play();
    RandSnow();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key,
                                     TShiftState Shift)
{
    if(Key==27)
    {
        ExitItemClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutItemClick(TObject *Sender)
{
    MessageDlg("    Hello,ѩ��СС���� \n   Snow1.0 Written by hjk \n   Copy it Free          --only !" ,
               mtInformation , TMsgDlgButtons()<<mbOK ,0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
    try
    {
        this->Hide();
        try
        {
            //��̬�������ӿ⺯����������
            CallDllFuncB("MyWindowsDll.dll" ,"_SayHello" ,"лл���ټ���");//
        }
        catch(...)
        {
         ; //ShowMessage("��MyWindowsDll.dll \nһͬCopy����Ӧ�ó���ͬһĿ¼��");
        }
    }
    __finally
    {
        Close();
    }
}
//---------------------------------------------------------------------------
/*������ʹ��mciSendString������һ�������ӣ�
"open cdaudio"������CD�������������������������û��CD���򷵻ش����룬
��ʱ������mciGetErrorString����ȡ�ô�����Ϣ�ַ�����open��MCI�ġ����豸�����
cdaudio��MCI��Լ�����豸����
    char buf[50];
    MCIERROR    mciError;
    mciError=mciSendString("open cdaudio",buf,strlen(buf),NULL);
    if(mciError)
    {
   mciGetErrorString(mciError,buf,strlen(buf));
   ShowMessage(buf);
   return;
    }    */
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtnNOClick(TObject *Sender)
{
    ControlBarSet->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetSnowItemClick(TObject *Sender)
{
    ControlBarSet->Top  = this->Height/2;
    ControlBarSet->Left = this->Width/2;
    ControlBarSet->Visible = true;
    LabeledEditSet->Font->Color  = LabelHello->Font->Color;
    LabeledEditSet->Text = LabelHello->Caption;
    switch(TimerNewSnow->Interval)
    {
    case 1000:
        ComboBoxSnow->ItemIndex = 0;
        break;
    case 500:
        ComboBoxSnow->ItemIndex = 1;
        break;
    case 250:
        ComboBoxSnow->ItemIndex = 2;
        break;
    default:
        break;
    }
    BitBtnOK->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnOKClick(TObject *Sender)
{
    LabelHello->Caption = LabeledEditSet->Text;
    LabelHello->Left = Screen->Width - LabelHello->Width;
    LabelHello->Top  = Screen->Height -LabelHello->Height*2;
    switch(ComboBoxSnow->ItemIndex)
    {
    case 0:
        TimerNewSnow->Interval = 1000;
        downrate = 2;
        break;
    case 1:
        TimerNewSnow->Interval = 500;
        downrate = 4;
        break;
    case 2:
        TimerNewSnow->Interval = 250;
        downrate = 6;
        break;
    default:
        break;
    }
    ControlBarSet->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnFontClick(TObject *Sender)
{
    BitBtnOK->Enabled = true;
    FontDialog1->Font = LabelHello->Font;
    if(FontDialog1->Execute())
    {
        LabelHello->Font = FontDialog1->Font;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LabeledEditSetChange(TObject *Sender)
{
    BitBtnOK->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ComboBoxSnowChange(TObject *Sender)
{
    BitBtnOK->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LabelReportClick(TObject *Sender)
{
    ShellExecute(Handle,

                  "open",

                  "http://user.qzone.qq.com/410746866",

                  NULL,NULL,SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
/*    TImage  *snow;
    try
    {
        {
            snow = new TImage(ImageExample[(1)]);  // freesnow_vec[i].snow this->Controls[i]
        }
    }
    catch(...)
    {
        delete  snow;
        ShowMessage("NewSnow() ����!!!");
    }
    snow->Visible = true;
    snow->Left = 500;     */

//---------------------------------------------------------------------------

void __fastcall TMainForm::HideSnowItemClick(TObject *Sender)
{
    this->Hide();
    HideSnowItem->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrayIcon1Click(TObject *Sender)
{
    if(!this->Visible)
    {
        this->Show();
        HideSnowItem->Enabled = true;
    }
}
//---------------------------------------------------------------------------

