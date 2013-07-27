//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
// MediaPlayer ����mp3�����Ƿ�ɹ�;
bool    MediaPlayerFlag = true;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    //���캯��
    //��ʽ����
    this->AutoSize = false;
    this->BorderStyle = bsNone;
    this->Color = clBlack;
    this->WindowState = wsMaximized;
    this->AlphaBlendValue = 180;
    this->AlphaBlend = true;

    DiamondsColor = clMin;
    MediaPlayer = new TMediaPlayer(this);
    MediaPlayer->Parent = this;
    MediaPlayer->Visible = false;

    Panel_Client->Height = SIDE*20;
    Panel_Client->Width = SIDE*10+10;
    Panel_Client->DoubleBuffered = true; //��ֹ��������ʱ������
    ShapeExample->Width  = 30;
    ShapeExample->Height = 30;
    ImageBackground->Transparent = true;
    LabelHello->Transparent = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //ShowMessage(String(MediaPlayer->Length));
    //ȡ�� ������������ʾ���� ��
    LONG style = GetWindowLong(Application->Handle ,GWL_EXSTYLE);
    SetWindowLong(Application->Handle ,GWL_EXSTYLE ,style|WS_EX_TOOLWINDOW);
    time_t t;
    srand((unsigned) time(&t));
//��srand((unsigned) time(0));//ֻ�ܳ�ʼ��һ�Σ�������
    ScanForward = false;
    //AutoPlayItem->Checked = false;
    /*
    if(Timer_Down->Interval > Timer_Display->Interval)
        Timer_Down->Interval = Timer_Display->Interval;
    else
        Timer_Display->Interval = Timer_Down->Interval;
    */
    //��ȡϵͳ���� ���� ����ʾ�� TTrackBar ���
    tbMainVolume->Max = 255;
    tbLeftVolume->Max = 255;
    tbRightVolume->Max = 255;
    unsigned long     volume;
    waveOutGetVolume(0 ,&volume);
    tbLeftVolume->Position = tbLeftVolume->Max -(double(volume&0x0000FFFF))/0xFFFF*tbLeftVolume->Max;
    tbRightVolume->Position = tbRightVolume->Max -(double((volume&0xFFFF0000)>>16))/0xFFFF*tbRightVolume->Max;
    if(tbRightVolume->Position<tbLeftVolume->Position)// ����������С��λ��Position �෴
        tbMainVolume->Position = tbRightVolume->Max-tbRightVolume->Position;
    else
        tbMainVolume->Position = tbLeftVolume->Max-tbLeftVolume->Position;

    GroupBoxGame->Left = (Screen->Width-GroupBoxGame->Width)/2;
    GroupBoxGame->Top  = (Screen->Height-GroupBoxGame->Height)/2;
    GroupBoxSet->Visible = false;
    ShowCursor(false);
    //�Զ���ʼ��Ϸ
    gameoverflag = false;
    NewGame();   /*  */
    try
    {
        MediaPlayerFlag = true;
        String  Mp3Path = ExtractFilePath(Application->ExeName) + "\\Music.mp3 ";
        MediaPlayer->FileName = Mp3Path;
        MediaPlayer->Open();
        MediaPlayer->Play();
        //ShowMessage(String(MediaPlayer->Length));
    }
    catch(...)
    {
        MediaPlayerFlag = false;
        try
        {
            String  WavePath = ExtractFilePath(Application->ExeName) + "\\Music.Wav ";
            //�첽��ѭ��������ָ���ļ�--,SND_ASYNC |SND_LOOP | SND_FILENAME
            if(! sndPlaySound(WavePath.c_str() ,SND_ASYNC | SND_LOOP | SND_FILENAME))
                throw 'e';
        }
        catch(char e)
        {
            ShowMessage("���ý���ļ�Music.wav \nһͬCopy����Ӧ�ó���ͬһĿ¼��");
        }
        ShowMessage("���ý���ļ�Music.mp3 \nһͬCopy����Ӧ�ó���ͬһĿ¼��");
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NewGameItemClick(TObject *Sender)
{
    NewGame();
    ContinueItem->Checked = false;
    PauseItem->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
                                       TShiftState Shift)
{
    if(Key==VK_F5)
    {
        if(this->WindowState==wsMaximized)
        {
            this->WindowState = wsNormal;
            this->AutoSize = true;
        }
        else
        {
            this->AutoSize = false;
            GroupBoxGame->Left = (Screen->Width-GroupBoxGame->Width)/2;
            GroupBoxGame->Top  = (Screen->Height-GroupBoxGame->Height)/2;
            this->WindowState = wsMaximized;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
    if(cur_diamonds[0]==NULL)//��Ϸ��δ��ʼ
        return;
    /*    ?????  ���ڣ��¼�FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
    �����(��)�� VK_LEFT (37)
    �����(��)�� VK_UP (38)
    �����(��)�� VK_RIGHT (39)
    �����(��)�� VK_DOWN (40)
    */
    switch(Key)
    {
    case 13:
    {
        if(Check_Change())   //change_flag == true
        {
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Left = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][0];
                cur_diamonds[i]->Top  = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][1];

            }
        }
    }
    break;

    case ' ' :
        /*        if(Timer_Down->Enabled == true)
             {
                 Timer_Down->Enabled = false;
                 Timer_Display->Enabled = false;
                 ContinueItem->Checked = false;
                 PauseItem->Checked = true;
             }
             else
             {
                 Timer_Down->Enabled = true;
                 Timer_Display->Enabled = true;
                 ContinueItem->Checked = true;
                 PauseItem->Checked = false;
             }      */
        //������ͣ--�������ո񣩻ָ�����
        static bool TimerDisplayFlag;
        if(Timer_Display->Enabled)
            TimerDisplayFlag = true;

        if(Timer_Display->Enabled && !Timer_Down->Enabled )
        {
            Timer_Display->Enabled = false;
        }
        else  if(TimerDisplayFlag)
        {
            Timer_Display->Enabled = true;
            TimerDisplayFlag = false;
        }
        else
            Timer_Down->Enabled = !Timer_Down->Enabled;
        ContinueItem->Checked = Timer_Down->Enabled;
        PauseItem->Checked = !Timer_Down->Enabled;
        break;

        //case 39 :
    case VK_RIGHT :
    case 'd' :
    case 'D' :
    case '6' ://->
        if(Check_Move(Key)) // ,cur_diamonds
        {
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Left += SIDE;
            }
            First_Left = cur_diamonds[0]->Left;  //����
        }
        break;
    case VK_LEFT :
        //case 37 :
    case 'a' :
    case 'A' :
    case '4' ://<-
        if(Check_Move(Key))//   ,cur_diamonds
        {
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Left -= SIDE;
            }
            First_Left = cur_diamonds[0]->Left;  //����
        }
        break;
        //case 40 :
    case VK_DOWN :
    case 's' ://����
    case 'S' :
    case '5' :
    {
        /*
        if(Timer_Down->Enabled==true)
                Timer_DownTimer(MainForm);    */
        if(!Check_End())
        {
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Top += DOWN;
            }
            First_Top = cur_diamonds[0]->Top;  //����
        }
    }
    break;
    case VK_PAUSE : //?????Pause Break���� VK_PAUSE (19)
    {
        Timer_Down->Enabled = false;
    }
    case 46: //Delete��������������
        // Timer_Down->Enabled =true;
        for(int i=0; i<PIECE; i++)
        {
            delete cur_diamonds[i];
        }
        New_Diamonds();
    default :
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer_DownTimer(TObject *Sender)
{
    //this->KeyPress('6');
    if(cur_diamonds[0]!=NULL)
    {
        //�жϷ����Ƿ񵽵� �����������׼������洢����
        if(Check_End())
        {
            //�������䵽�ף��洢������ݵ�����board
            int     row;
            int     col;
            for(int i=PIECE-1; i>=0; i--)
            {
                row = cur_diamonds[i]->Top/SIDE;
                col = cur_diamonds[i]->Left/SIDE;
                board[row][col] =  cur_diamonds[i];
            }
            if(row < 5)
                LabelHello->Caption = "  Go Go Go ";
            Remove_Diamonds();//�ж���������

            New_Diamonds();
            /*   //�����������board[][]������
            ofstream fout;
            fout.open("board.txt");
            OutBoard(fout);
            fout.close();
            */
            return;
        }
        else
        {
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Top += DOWN;
            }
            First_Left = cur_diamonds[0]->Left;
            First_Top = cur_diamonds[0]->Top;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender,
                                     TCloseAction &Action)
{
    for(int i=0; i<ROW; i++)
        for(int j=0; j<COL; j++)
        {
            if(board[i][j]!=NULL)
                delete  board[i][j];
        }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ContinueItemClick(TObject *Sender)
{
    /*    */
    if(Timer_Down->Enabled == false)
        Timer_Down->Enabled = true;
    ContinueItem->Checked = true;
    PauseItem->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauseItemClick(TObject *Sender)
{
    if(Timer_Down->Enabled == true)
        Timer_Down->Enabled = false;
    ContinueItem->Checked = false;
    PauseItem->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpItemClick(TObject *Sender)
{
    ShellExecute(Handle,"open","help.doc",NULL,NULL,SW_SHOWNORMAL);
    //system("help.doc");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutItemClick(TObject *Sender)
{
    MessageDlg("    Hello,���ܶ���˹���� \n   AI Tetris 1.0 Written by hjk \n   Copy it Free          --only !" ,
               mtInformation , TMsgDlgButtons()<<mbOK ,0); //mtConfirmation  mtCustom
    //����������Ϣ����ѡ
    //ShowMessage("!!! �ó����ɻƿ������Ĵ��� !!! \n     !!!������̣�������!!!   \n      !!! ѧ��06065072 !!!     \n           !!! лл !!!          ");
    //Application->MessageBoxA("!!! ������ɻƿ������Ĵ��� !!! \n\n     !!!������̣�������!!!   \n\n      !!! ѧ��06065072 !!!     \n\n           !!! лл !!!           ","����汾",MB_OK);
    //MessageBox(Handle ,"!!! �ó����ɻƿ������Ĵ��� !!! \n\n     !!!������̣�������!!!   \n\n      !!! ѧ��06065072 !!!     \n\n           !!! лл !!!           ","����汾",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
    if(Application->MessageBoxA("���Ƿ����Ҫ�˳���Ϸ��","ȷ���˳���",MB_YESNOCANCEL)==IDYES)
    {
        exit_flag = true;
        Close();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(exit_flag == true||Application->MessageBoxA("���Ƿ����Ҫ�˳���Ϸ��","ȷ���˳���",MB_YESNOCANCEL)==IDYES)
        CanClose=true;
    else
        CanClose=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AutoPlayItemClick(TObject *Sender)
{
    AutoPlayItem->Checked = !AutoPlayItem->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer_DisplayTimer(TObject *Sender)
{
    if(MediaPlayerFlag==true  &&
            MediaPlayer->Position==MediaPlayer->Length)
        MediaPlayer->Play();//����ѭ������

    if(gameoverflag == false)
    {
        while(position_kind != bestplan.Kind)
        {
            char    change = 13;
            this->KeyPress(change);
            return;
            //Sleep(500);
            //ShowMessage("cccccccccccccccccc");
        }
        char    ward;//����
        if(bestplan.Move >0)
            ward = '6';
        else
            ward = '4';
        static int     moved = 0;
        while(moved!=abs(bestplan.Move))
        {
            this->KeyPress(ward);
            //ShowMessage(String(moved));
            moved++;
            return;
            //Sleep(500);
        }
        moved = 0;   //���㷽���Ѿ��ƶ�λ����
        Timer_Down->Enabled = true;
        Timer_Display->Enabled = false;
    }
    else
    {
        for(int i=0; i<ROW; i++)
            for(int j=0; j<COL; j++)
            {
                if(board[i][j]!=NULL)
                {
                    delete  board[i][j];
                    board[i][j] = NULL;
                    return;
                }
            }
        /**/
        for(int i=0; i<PIECE; i++)
        {
            if(cur_diamonds[i]!= NULL)
            {
                delete cur_diamonds[i];
                cur_diamonds[i] = NULL;
                return;
            }
        }
        gameoverflag = false;
        Timer_Display->Enabled = false;
        NewGame();
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button != mbLeft)
        return;
    static  bool    showcursor = false;
    if(showcursor)
    {
        ShowCursor(false);
        showcursor = false;
    }
    else
    {
        ShowCursor(true);
        showcursor = true;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::BitBtnNOClick(TObject *Sender)
{
    GroupBoxSet->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnOKClick(TObject *Sender)
{
    Timer_Down->Interval = StrToInt(ComboBoxLevel->Text);
    GroupBoxSet->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnImageClick(TObject *Sender)
{
    if(SavePictureDialog1->Execute())
    {
        ImageBackground->Picture->CleanupInstance();
        ImageBackground->Picture->LoadFromFile(SavePictureDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBoxLevelChange(TObject *Sender)
{
    BitBtnOK->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LevelSetItemClick(TObject *Sender)
{
    GroupBoxSet->Top = 100;
    GroupBoxSet->Left = Width-GroupBoxSet->Width-20;
    BitBtnOK->Enabled = false;
    TrackBarAP->Position = MainForm->AlphaBlendValue;
    GroupBoxSet->Show();
    if(Sender==LevelSetItem)
        TabSheetLevel->Show();
    else
        TabSheetFace->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBarAPChange(TObject *Sender)
{
    MainForm->AlphaBlend = true;
    MainForm->AlphaBlendValue = TrackBarAP->Position;
    if(TrackBarAP->Position==225)
        MainForm->AlphaBlend = false;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::cbRandColorClick(TObject *Sender)
{
    if(! cbRandColor->Checked)
    {
        if(ColorDialog1->Execute())
        {
            DiamondsColor = ColorDialog1->Color;
        }
        else
            cbRandColor->Checked = !cbRandColor->Checked;
    }
    else
        DiamondsColor = clMin;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1DblClick(TObject *Sender)
{
    ImageBackground->Picture->Assign(Image1->Picture->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image2DblClick(TObject *Sender)
{
    ImageBackground->Picture->Assign(Image2->Picture->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image3DblClick(TObject *Sender)
{
    ImageBackground->Picture->Assign(Image3->Picture->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CBPlayMusicClick(TObject *Sender)
{
    if(CBPlayMusic->Checked)
        MediaPlayer->Play();
    else
        MediaPlayer->Stop();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tbMainVolumeChange(TObject *Sender)
{
    unsigned long      v ,t;
    t = tbMainVolume->Position;
    tbLeftVolume->Position = tbMainVolume->Max-t;
    tbRightVolume->Position = tbMainVolume->Max-t;
    v = (t<<8) | (t<<24);
    waveOutSetVolume(0 ,v);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tbLeftVolumeChange(TObject *Sender)
{
    unsigned long      v ,t;
    t = tbLeftVolume->Max-tbLeftVolume->Position;
    waveOutGetVolume(0 ,&v);
    v = v & 0xffff0000 | (t<<8);
    waveOutSetVolume(0 ,v);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tbRightVolumeChange(TObject *Sender)
{
    unsigned long      v ,t;
    t = tbRightVolume->Max-tbRightVolume->Position;
    waveOutGetVolume(0 ,&v);
    v = v & 0x0000ffff | (t<<24);
    waveOutSetVolume(0 ,v);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ImageBackgroundMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //SendMessage(Handle ,WM_LBUTTONDOWN ,
    if(this->WindowState!=wsMaximized)// Cursor == crArrow &&
    {
        //�ͷ�ԭ����겶׽״̬��
        //��ͬʱ�ͳ���굥��λ�õ�ͬ�ڴ��ڱ���������ҷ���ڵ�����
        ::ReleaseCapture();
        SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0); //or :  SNDMSG(...)
    }
}
//---------------------------------------------------------------------------

