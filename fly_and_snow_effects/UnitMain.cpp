//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "UnitThread.h"
#include "UnitMain.h"
#include <fstream>
using namespace std;
#include "UnitFlyBody.h"
#include "UnitHello.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"
#pragma resource "Music.RES"// ...

TMainForm *MainForm;

HHOOK   OldHook;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)// ,chWavHandle(NULL)
{
    //创建线程  TFlyFollow ...
    flyFollowCursor = new TFlyFollowCursor(this); //true ...
    flyFollowCursor->OnTerminate = ThreadDone; //指定线程结束事件处理函数

    drawCurves = new TDrawCurves(this ,this->Canvas);
    flyFollowPath = new TFlyFollowPath(this ,drawCurves->getFlyPathPtr());//&flyPath

    //TImage* images1[IMAGECOUNT] = { Image1,Image2,Image3,Image4,Image5,Image6 };
    //flyAngel = new TFlyAngel(new TFlyAngelImpl(this ,images1 ,&path1));
    //
    TImage* images2[] = {FlyBodyForm->Image13 ,FlyBodyForm->Image14 ,FlyBodyForm->Image15 , \
                         FlyBodyForm->Image16 ,FlyBodyForm->Image17 ,FlyBodyForm->Image18 ,    \
                         FlyBodyForm->Image19 ,FlyBodyForm->Image20 ,FlyBodyForm->Image21 , \
                         FlyBodyForm->Image22 ,FlyBodyForm->Image23 ,FlyBodyForm->Image24
                        };
    TSnow::initImageExamples(images2 ,sizeof(images2)/sizeof(TImage*));
    snow = new TSnow(this);
    flyFollowPath->setLinkSnow(snow);

    TStringList *text=new TStringList();
    try
    {
        text->LoadFromFile("SrollText.txt") ;
    }
    catch(...) //Exception& e
    {
        //MessageDlg("请将 SrollText.txt 拷贝到同一目录 ！" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
        for(int i=0; i<DEF_SROLLTEXT_LENGTH; i++)
            text->Add(DEF_SROLLTEXT[i]);
    }
    srollText = new TSrollText(this ,text);
    delete text;
    //srollText->setPosition(TPoint((Screen->Width-(srollText->getPaintBox())->Width-10),10));
    /************Constant*******************/
    miItemClicks[0] = miLittleSnowsClick;
    miItemClicks[1] = miFlyFromMeClick;
    miItemClicks[2] = miDrawCurvesClick;
    miItemClicks[3] = miSrollTextClick;
    miItemClicks[4] = miMusicClick;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
    //TrayIcon1->FreeOnRelease();//
    // delete flyFollowCursor;
    //delete flyAngel;// ...
    flyFollowCursor->Terminate();
    flyFollowPath->Terminate();
    //flyAngel->Terminate();
    if(srollText) delete srollText;
    if(snow) delete snow;
    if(drawCurves) delete drawCurves;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam) // TMainForm::
{
    //键盘钩子 ...
    KBDLLHOOKSTRUCT *pkbhs;
    if (code < 0)
    {
        //ShowMessage("code < 0");
        return CallNextHookEx(OldHook,code, wParam, lParam);
    }
    pkbhs = (KBDLLHOOKSTRUCT*) lParam;
    /*.注意 wParam 可能包含的值 .... */
    if(wParam==WM_KEYDOWN)// pass other: WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP....
        //MainForm->keyDownUpdate(WORD(pkbhs->vkCode));
        MainForm->drawCurves->keyDownAndUpdate(WORD(pkbhs->vkCode));
    return CallNextHookEx(OldHook,code, wParam, lParam);
    //return NULL;
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
    OldHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyProc, HInstance, 0);
    //Image1->Left = Screen->Width+10;
    //Image1->Top = Screen->Height+10;
    Caption=""; //窗口无标题
    BorderStyle=bsNone; //无边框
    BorderIcons.Clear(); //无系统菜单及按钮
    //FormStyle=fsStayOnTop; //使窗口始终处于最上层
    this->WindowState = wsMaximized;
    this->TransparentColor = true;
    this->DoubleBuffered = true;
    this->ShowHint = true;
    Application->ShowHint = true; // ...
    String date = Date(); //"YYYY-MM-DD
    date = date.SubString(6 ,date.Length()-5);
    //ShowMessage(date);
    if(date=="1-1")
        LabelHello->Caption = "Happy new year ";//
    else if(date=="12-25")
        LabelHello->Caption = "Merry Chrismas ";//
    else
        LabelHello->Caption = "Wish you happy ";//

    LabelHello->Transparent = true;
    LabelHello->Left = Screen->Width-LabelHello->Width;
    LabelHello->Top  = Screen->Height-LabelHello->Height-10;
    // ---------------------------
    FlyBodyForm->Hide();
    if(!loadIniFile())//加载iniflie配置信息 ...
    {
        miAllStartClick(this);//加载失败,则 ...
    }
    //else ShowMessage("loadIniFile ,OK");
    /*  */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miCloseClick(TObject *Sender)
{
    Close();
    FlyBodyForm->Close();// Applition end ...
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miAllStartClick(TObject *Sender)
{
    /*
        flyFollowCursor->Resume();
        flyFollowPath->Resume();
        //flyAngel->Resume();
        drawCurves->doDraw();
        snow->doSnow(TSnow::littleSnow);//...
        srollText->doSrollText();   */
    miLittleSnowsClick(miLittleSnows);
    miFlyFromMeClick(miAllFly);
    miDrawCurvesClick(miDrawCurves);
    miSrollTextClick(miSrollText);
    miMusicClick(miMusic);
    miAllStart->Enabled = false;
    miClose->Enabled = false;
    miAllStop->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miAllStopClick(TObject *Sender)
{
    //ShowMessage("miAllStopClick ... ");
    /*-------  */
    miLittleSnowsClick(miNoSnows);
    miFlyFromMeClick(miNoFly);
    miDrawCurvesClick(miNoDrawCurves);
    miSrollTextClick(miNoSrollText);
    miMusicClick(miNoMusic);

    miAllStart->Enabled=true;
    miClose->Enabled=true;
    miAllStop->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ThreadDone(TObject *)
{
    //线程结束时自动调用
    miAllStart->Enabled=true;
    miClose->Enabled=true;
    miAllStop->Enabled=false;
    //ShowMessage("void __fastcall TMainForm::ThreadDone(TObject *) ... ");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    //窗口显示时自动开始动画 ...
    //FlyBodyForm->Hide();
    FormStyle=fsStayOnTop; //使窗口始终处于最上层
    /*
    if(!loadIniFile())//加载iniflie配置信息 ...
    {
      miAllStartClick(this);//加载失败,则 ...
    }      */
    //else ShowMessage("loadIniFile ,OK");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //若线程结束后才能退出程序
    if(miAllStart->Enabled)
        Action=caFree;
    else
        Action=caNone;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miLittleSnowsClick(TObject *Sender)
{
    // ...Checked
    miLittleSnows->Enabled = true;
    miSoSoSnows->Enabled = true;
    miManySnows->Enabled = true;
    miNoSnows->Enabled = true;
    if(Sender==miLittleSnows) //
        snow->doSnow(TSnow::littleSnow);
    else if(Sender==miSoSoSnows) //
        snow->doSnow(TSnow::middleSnow);
    else if(Sender==miManySnows) //
        snow->doSnow(TSnow::muchSnow);
    else if(Sender==miNoSnows) //
        snow->stopSnow();
    else
        throw Exception("miLittleSnowsClick ,error ...");
    static_cast<TMenuItem*>(Sender)->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miFlyFromMeClick(TObject *Sender)
{
    miFlyFromMe->Enabled = true;
    miFlyFreely->Enabled = true;
    miAllFly->Enabled = true;
    miNoFly->Enabled = true;
    if(Sender==miFlyFromMe) //
        flyFollowCursor->Resume();
    else if(Sender==miFlyFreely) //
        flyFollowPath->Resume();
    else if(Sender==miAllFly) //
    {
        flyFollowCursor->Resume();
        flyFollowPath->Resume(); // ...
        miFlyFromMe->Enabled = false;
        miFlyFreely->Enabled = false;
    }
    else if(Sender==miNoFly) //
    {
        //避免多次线程挂起 ...
        if(!flyFollowCursor->Suspended)
            flyFollowCursor->Suspend();
        if(!flyFollowPath->Suspended)
            flyFollowPath->Suspend();
    }
    else
        throw Exception("miFlyFromMeClick ,error ...");
    static_cast<TMenuItem*>(Sender)->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miDrawCurvesClick(TObject *Sender)
{
    miDrawCurves->Enabled = true;
    miNoDrawCurves->Enabled = true;
    if(Sender==miDrawCurves) //
        drawCurves->doDraw();
    else if(Sender==miNoDrawCurves) //
        drawCurves->stopDraw();
    else
        throw Exception("miDrawCurvesClick ,error ...");
    static_cast<TMenuItem*>(Sender)->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miSrollTextClick(TObject *Sender)
{
    miSrollText->Enabled = true;
    miNoSrollText->Enabled = true;
    miSrollTextForMe->Enabled = true;
    if(Sender==miSrollText) //
        srollText->doSrollText();
    else if(Sender==miNoSrollText) //
        srollText->stopSrollText();
    else if(Sender==miSrollTextForMe) //
    {
        // ...
        OpenDialog1->Title = "打开文本文档(滚动字幕)";
        OpenDialog1->Filter = "文本文档(*.txt)|*.txt";
        OpenDialog1->FileName = "";
        if(OpenDialog1->Execute())
        {
            TStringList *text = new TStringList;
            textFileName = OpenDialog1->FileName;
            text->LoadFromFile(OpenDialog1->FileName);
            srollText->updateText(text);
            delete text;
            srollText->doSrollText();//notice ...
        }
    }
    else
        throw Exception("miSrollTextClick ,error ...");
    static_cast<TMenuItem*>(Sender)->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miMusicClick(TObject *Sender)
{
    // ...
    miMusic->Enabled = true;
    miNoMusic->Enabled = true;
    miMusicForMe->Enabled = true;
    if(Sender==miMusic) //
    {
        MediaPlayer1->Close();
        bMediaPlayerFlag = false;
        try
        {
            /* */
            sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
            String    path = ExtractFilePath(Application->ExeName) + "\\"+"Music.mp3";
            MediaPlayer1->FileName = path;
            MediaPlayer1->Open();
            MediaPlayer1->Play();
            bMediaPlayerFlag = true;
        }
        catch(...)//Exception& e
        {
            HRSRC temp=FindResourceA(HInstance,"DEFAULTMUSIC", "WAV");//从内存中载入声音
            /*
            if(temp==NULL)
              MessageDlg("FindResource DEFAULTMUSIC ,Error" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
            else
            {   }            */
            assert(temp);// ...
            HGLOBAL h=LoadResource(HInstance,temp);
            char *chWavHandle = (char *)LockResource(h);
            if(!sndPlaySound(chWavHandle,SND_MEMORY|SND_ASYNC|SND_LOOP))//or :SND_SYNC  ,SND_LOOP
                MessageDlg("sndPlaySound chWavHandle ,Error" ,mtWarning , \
                           TMsgDlgButtons()<<mbOK ,0);
        }
    }
    else if(Sender==miNoMusic) //
    {
        MediaPlayer1->Close();
        bMediaPlayerFlag = false;
        sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
        //if(chWavHandle) delete[] chWavHandle; // ...
    }
    else if(Sender==miMusicForMe) //
    {
        // ...
        OpenDialog1->Title = "打开MP3音频文件(背景音乐)";
        OpenDialog1->Filter = "MP3音频文件(*.mp3)|*.mp3";
        OpenDialog1->FileName = "";
        if(OpenDialog1->Execute())
        {
            //MediaPlayer1->Stop(); // ...
            sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
            MediaPlayer1->FileName = musicFileName = OpenDialog1->FileName;
            MediaPlayer1->Open();// ...
            MediaPlayer1->Play();
            bMediaPlayerFlag = true;
        }
    }
    else
        throw Exception("miMusicClick ,error ...");
    static_cast<TMenuItem*>(Sender)->Enabled = false;
}
//---------------------------------------------------------------------------
bool TMainForm::loadIniFile(const String& filename)
{
    if(!FileExists(filename))    return false;//配置信息文件不存在...
    /************Constant*******************/
    TObject* miSnows[4]= {miLittleSnows,miSoSoSnows,miManySnows,miNoSnows};
    TObject* miFlyAngles[4]= {miFlyFromMe,miFlyFreely,miAllFly,miNoFly};
    TObject* miDrawCurveses[4]= {miDrawCurves,miNoDrawCurves,NULL,NULL};
    TObject* miSrollTexts[4]= {miSrollText,miNoSrollText,miSrollTextForMe,NULL};
    TObject* miMusics[4]= {miMusic,miNoMusic,miMusicForMe,NULL};
    TObject  **miItems[5]= {miSnows,miFlyAngles,miDrawCurveses,miSrollTexts,miMusics};
    String   strIdents[5]= {"miSnows","miFlyAngles","miDrawCurveses","miSrollTexts","miMusics" };
    //typedef void __fastcall (__closure *MenuItemClick)(TObject *Sender);
    //typedef void __fastcall (__closure *TNotifyEvent)(System::TObjectTObject* Sender);
    //typedef TNotifyEvent MenuItemClick; // ...
    //Application->ExeName指向本可执行文件的文件名（包含全路径）
    String FileName = ExtractFilePath(Application->ExeName)+filename;
    ////Notice: Usually INI files are stored in the \WINDOWS directory.
    TIniFile    *pIniFile = new TIniFile(FileName);
    try
    {
        for(int i=0; i<5; i++) //miItemClicks
        {
            int   miIndex=pIniFile->ReadInteger("MenuItemConfig" ,strIdents[i] ,-1);
            if(miIndex!=-1)
            {
                if(i==3&&miIndex==2)
                {
                    textFileName=pIniFile->ReadString("LinkFileConfig" ,"SrollTextFile" ,NULL);
                    if(textFileName==NULL)
                        return false; //throw Exception("SrollTextFile of LinkFileConfig is NULL ,error");
                    TStringList *text = new TStringList;
                    text->LoadFromFile(textFileName);
                    srollText->updateText(text);
                    delete text;
                    srollText->doSrollText();//notice ...
                }
                else if(i==4&&miIndex==2)
                {
                    musicFileName=pIniFile->ReadString("LinkFileConfig" ,"BackMusicFile" ,NULL);
                    if(musicFileName==NULL)
                        return false;//throw Exception("MusicFile of LinkFileConfig is NULL ,error");
                    sndPlaySound(NULL,SND_ASYNC);//Close sndPlaySound ...
                    MediaPlayer1->FileName = musicFileName;
                    MediaPlayer1->Open();// ...
                    MediaPlayer1->Play();
                    bMediaPlayerFlag = true;
                }
                else
                    miItemClicks[i](miItems[i][miIndex]);// ...
            }
        }
    }
    catch(Exception& e) //__finally//
    {
        //ShowMessage(e.Message);
        if(pIniFile)    delete pIniFile;
        return false;
    }
    FileSetAttr(filename ,2); //隐藏文件（ .ini ）
    return true;
}
//---------------------------------------------------------------------------
bool TMainForm::saveIniFile(const String& filename)
{
    /************Constant*******************/
    TObject* miSnows[4]= {miLittleSnows,miSoSoSnows,miManySnows,miNoSnows};
    TObject* miFlyAngles[4]= {miFlyFromMe,miFlyFreely,miAllFly,miNoFly};
    TObject* miDrawCurveses[4]= {miDrawCurves,miNoDrawCurves,NULL,NULL};
    TObject* miSrollTexts[4]= {miSrollText,miNoSrollText,miSrollTextForMe,NULL};
    TObject* miMusics[4]= {miMusic,miNoMusic,miMusicForMe,NULL};
    TObject  **miItems[5]= {miSnows,miFlyAngles,miDrawCurveses,miSrollTexts,miMusics};
    String   strIdents[5]= {"miSnows","miFlyAngles","miDrawCurveses","miSrollTexts","miMusics" };
    //Application->ExeName指向本可执行文件的文件名（包含全路径）
    String FileName = ExtractFilePath(Application->ExeName)+filename;
    ////Notice: Usually INI files are stored in the \WINDOWS directory.
    TIniFile    *pIniFile = new TIniFile(FileName);
    try
    {
        for(int i=0; i<5; i++)
            for(int j=0; j<4; j++)
                if(miItems[i][j]&& //!=NULL
                        !(static_cast<TMenuItem*>(miItems[i][j])->Enabled))//==false
                {
                    pIniFile->WriteInteger("MenuItemConfig" ,strIdents[i] ,j);
                    if(i==3&&j==2)
                        pIniFile->WriteString("LinkFileConfig" ,"SrollTextFile" ,textFileName);
                    else if(i==4&&j==2)
                        pIniFile->WriteString("LinkFileConfig" ,"BackMusicFile" ,musicFileName);

                    break;
                }
    }
    catch(Exception& e) //__finally//
    {
        //ShowMessage(e.Message);
        if(pIniFile)    delete pIniFile;
        return false;
    }
    FileSetAttr(filename ,2); //隐藏文件（ .ini ）
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    if(bMediaPlayerFlag && \
            MediaPlayer1->Position==MediaPlayer1->Length)
        MediaPlayer1->Play();
    LabelHello->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miSaveConfigClick(TObject *Sender)
{
    if(saveIniFile())
        MessageDlg(" 信息保存完成，成功^_^\n 注意：YourConfig.ini信息文件勿动哦 ^_^ ~~~" ,
                   mtInformation ,TMsgDlgButtons()<<mbOK ,0);
    else
        MessageDlg(" 信息保存出错，失败！~_~ " ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TEST1Click(TObject *Sender)
{
//   ShowMessage(Date());
    //saveIniFile();    //loadIniFile();
    /*
        // --- test TFlyFollowPath::shiftFlyDiretion .....
        Timer1->Enabled = !Timer1->Enabled;
        if((drawCurves->getDrawTimer())->Enabled)
                drawCurves->stopDraw();
        else    drawCurves->doDraw();
        /*
        // --- test TSnow .....
        if((snow->getsnowFallTimer())->Enabled)// ==true
            snow->stopSnow();
        else
            snow->doSnow(-1);
        // --- test TFlyFollowPath::shiftFlyDiretion .....
        flyFollowPath->shiftFlyDiretion();
        /* ====================*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miAboutClick(TObject *Sender)
{
    Hide();// ....
    TrayIcon1->Visible = false;
    HelloForm->FormStyle = fsStayOnTop;
    HelloForm->ShowModal();
    FormStyle = fsStayOnTop; //Repaint();
    Show(); // ....
    TrayIcon1->Visible = true;
}
//---------------------------------------------------------------------------

