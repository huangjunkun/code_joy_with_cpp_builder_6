//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <math.h>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
//#include "trayicon.h"

#define  WM_MYNOTIFY   (WM_APP+100)
#define  ID_MYICON     1000;///; ????????

using namespace std;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TShape *Shape_S;
    TLabel *Label2;
    TPopupMenu *PopupMenu1;
    TMenuItem *SetItem;
    TMenuItem *PauseItem;
    TMenuItem *ContinueItem;
    TMenuItem *N1;
    TMenuItem *ExitItem;
    TStatusBar *StatusBar1;
    TTimer *TimerClock;
    TLabel *Label_Hi;
    TMenuItem *N2;
    TMenuItem *HideShowItem;
    TLabel *Label1;
    TMenuItem *AboutItem;
    void __fastcall TimerClockTimer(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDblClick(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
                                  int X, int Y);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
                              TShiftState Shift);
    void __fastcall SetItemClick(TObject *Sender);
    void __fastcall PauseItemClick(TObject *Sender);
    void __fastcall ContinueItemClick(TObject *Sender);
    void __fastcall ExitItemClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall HideShowItemClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
                                  TShiftState Shift, int X, int Y);
    void __fastcall AboutItemClick(TObject *Sender);
    void __fastcall FormDragDrop(TObject *Sender, TObject *Source, int X,
                                 int Y);
    void __fastcall FormDragOver(TObject *Sender, TObject *Source, int X,
                                 int Y, TDragState State, bool &Accept);
    void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
    typedef struct position
    {
        int left;
        int top;
    } position;
    position    seconds[60] ,minute[60] ,hour[60];//秒，分，时针坐标
    position    dot;//圆点
    int     s_i ,m_i ,h_i;
    //double  angle;//角度
    int     R;//半径
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall CreateParams(TCreateParams &Params);
    void __fastcall WMLBUTTONDOWN(TMessage &Msg); //法一，消息映射
    void __fastcall WMMOVE(TWMMove &Msg);
    void __fastcall WMMOVING(TMessage &Msg);
    void __fastcall WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg);
    void __fastcall WMNCHITTEST(TWMMouse &Msg);
    void __fastcall MYNOTIFY(TMessage &Msg);
    void __fastcall MYHOTKEY(TWMHotKey &Msg);
//    void __fastcall WndProc(TMessage &Msg);

    int     s_width ,m_width ,h_width ,fontsize; //秒，分，时针的宽度
    TColor  s_color ,m_color ,h_color ,f_color;

    void    Account_SMH();
    void    DrawLine(TColor color ,int width ,int x ,int y);
    void    ClearLine(int width ,int x ,int y);
    void    PaintClock();
    void    Init_SMH();
    void    AddTrayIcon();
    void    DeleteTrayIcon();
    //（截获消息）消息映射表
    BEGIN_MESSAGE_MAP
        // MESSAGE_HANDLER(WM_LBUTTONDOWN,TMessage,WMLBUTTONDOWN) //法一，消息映射
        MESSAGE_HANDLER(WM_MOVE ,TWMMove,WMMOVE)
        MESSAGE_HANDLER(WM_MOVING ,TMessage ,WMMOVING)
        MESSAGE_HANDLER(WM_GETMINMAXINFO,TWMGetMinMaxInfo,WMGetMinMaxInfo)
        //MESSAGE_HANDLER(WM_NCHITTEST,TWMMouse,WMNCHITTEST)
        MESSAGE_HANDLER(WM_MYNOTIFY ,TMessage ,MYNOTIFY)
        MESSAGE_HANDLER(WM_HOTKEY ,TWMHotKey ,MYHOTKEY)
    END_MESSAGE_MAP(TForm) // TImage
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
