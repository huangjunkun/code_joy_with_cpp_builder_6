//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
// MediaPlayer 播放mp3音乐是否成功;
bool    MediaPlayerFlag = true;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    //构造函数
    //格式界面
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
    Panel_Client->DoubleBuffered = true; //防止方块下落时的闪动
    ShapeExample->Width  = 30;
    ShapeExample->Height = 30;
    ImageBackground->Transparent = true;
    LabelHello->Transparent = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //ShowMessage(String(MediaPlayer->Length));
    //取消 程序任务栏显示运行 ！
    LONG style = GetWindowLong(Application->Handle ,GWL_EXSTYLE);
    SetWindowLong(Application->Handle ,GWL_EXSTYLE ,style|WS_EX_TOOLWINDOW);
    time_t t;
    srand((unsigned) time(&t));
//或：srand((unsigned) time(0));//只能初始化一次！！！！
    ScanForward = false;
    //AutoPlayItem->Checked = false;
    /*
    if(Timer_Down->Interval > Timer_Display->Interval)
        Timer_Down->Interval = Timer_Display->Interval;
    else
        Timer_Display->Interval = Timer_Down->Interval;
    */
    //获取系统音量 数据 并显示于 TTrackBar 组件
    tbMainVolume->Max = 255;
    tbLeftVolume->Max = 255;
    tbRightVolume->Max = 255;
    unsigned long     volume;
    waveOutGetVolume(0 ,&volume);
    tbLeftVolume->Position = tbLeftVolume->Max -(double(volume&0x0000FFFF))/0xFFFF*tbLeftVolume->Max;
    tbRightVolume->Position = tbRightVolume->Max -(double((volume&0xFFFF0000)>>16))/0xFFFF*tbRightVolume->Max;
    if(tbRightVolume->Position<tbLeftVolume->Position)// 声道音量大小与位置Position 相反
        tbMainVolume->Position = tbRightVolume->Max-tbRightVolume->Position;
    else
        tbMainVolume->Position = tbLeftVolume->Max-tbLeftVolume->Position;

    GroupBoxGame->Left = (Screen->Width-GroupBoxGame->Width)/2;
    GroupBoxGame->Top  = (Screen->Height-GroupBoxGame->Height)/2;
    GroupBoxSet->Visible = false;
    ShowCursor(false);
    //自动开始游戏
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
            //异步，循环，播放指定文件--,SND_ASYNC |SND_LOOP | SND_FILENAME
            if(! sndPlaySound(WavePath.c_str() ,SND_ASYNC | SND_LOOP | SND_FILENAME))
                throw 'e';
        }
        catch(char e)
        {
            ShowMessage("请把媒体文件Music.wav \n一同Copy到与应用程序同一目录！");
        }
        ShowMessage("请把媒体文件Music.mp3 \n一同Copy到与应用程序同一目录！");
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
    if(cur_diamonds[0]==NULL)//游戏还未开始
        return;
    /*    ?????  用于：事件FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
    方向键(←)： VK_LEFT (37)
    方向键(↑)： VK_UP (38)
    方向键(→)： VK_RIGHT (39)
    方向键(↓)： VK_DOWN (40)
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
        //处理暂停--继续（空格）恢复智能
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
            First_Left = cur_diamonds[0]->Left;  //可略
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
            First_Left = cur_diamonds[0]->Left;  //可略
        }
        break;
        //case 40 :
    case VK_DOWN :
    case 's' ://向下
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
            First_Top = cur_diamonds[0]->Top;  //可略
        }
    }
    break;
    case VK_PAUSE : //?????Pause Break键： VK_PAUSE (19)
    {
        Timer_Down->Enabled = false;
    }
    case 46: //Delete键、、、？？？
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
        //判断方块是否到底 、、、、到底即处理，存储数据
        if(Check_End())
        {
            //方块下落到底，存储相关数据到数组board
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
            Remove_Diamonds();//判断消除方块

            New_Diamonds();
            /*   //输出方块数组board[][]的数据
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
    MessageDlg("    Hello,智能俄罗斯方块 \n   AI Tetris 1.0 Written by hjk \n   Copy it Free          --only !" ,
               mtInformation , TMsgDlgButtons()<<mbOK ,0); //mtConfirmation  mtCustom
    //以下三种信息框任选
    //ShowMessage("!!! 该程序由黄俊坤精心打造 !!! \n     !!!软件工程（三）班!!!   \n      !!! 学号06065072 !!!     \n           !!! 谢谢 !!!          ");
    //Application->MessageBoxA("!!! 该软件由黄俊坤精心打造 !!! \n\n     !!!软件工程（三）班!!!   \n\n      !!! 学号06065072 !!!     \n\n           !!! 谢谢 !!!           ","软件版本",MB_OK);
    //MessageBox(Handle ,"!!! 该程序由黄俊坤精心打造 !!! \n\n     !!!软件工程（三）班!!!   \n\n      !!! 学号06065072 !!!     \n\n           !!! 谢谢 !!!           ","软件版本",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
    if(Application->MessageBoxA("您是否真的要退出游戏？","确认退出！",MB_YESNOCANCEL)==IDYES)
    {
        exit_flag = true;
        Close();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(exit_flag == true||Application->MessageBoxA("您是否真的要退出游戏？","确认退出！",MB_YESNOCANCEL)==IDYES)
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
        MediaPlayer->Play();//控制循环播放

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
        char    ward;//方向
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
        moved = 0;   //清零方块已经移动位移量
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
        //释放原有鼠标捕捉状态，
        //并同时送出鼠标单击位置等同于窗口标题栏可拖曳窗口的属性
        ::ReleaseCapture();
        SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0); //or :  SNDMSG(...)
    }
}
//---------------------------------------------------------------------------

