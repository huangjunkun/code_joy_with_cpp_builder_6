//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Trayicon.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include "trayicon.h"

#define IMAGECOUNT      6  //图片总数
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image6;
    TImage *Image5;
    TImage *Image4;
    TImage *Image3;
    TImage *Image2;
    TImage *Image1;
    TMenuItem *mStart;
    TMenuItem *mEnd;
    TMenuItem *N3;
    TMenuItem *mClose;
    TTrayIcon *TrayIcon1;
    TPopupMenu *PopupMenu1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall mStartClick(TObject *Sender);
    // void __fastcall TrayIcon1Create(TObject *Sender);
    void __fastcall mEndClick(TObject *Sender);
    void __fastcall mCloseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    TFlyThread      *flythread;
    TFollowThread   *followthread;
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall ThreadDone(TObject *);
//制止重画窗口背景
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    TImage  *Images[IMAGECOUNT];
    bool    End;  //动画结束标志

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
