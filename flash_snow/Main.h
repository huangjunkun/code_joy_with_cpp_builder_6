//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "trayicon.h"
#include <time.h>
#include <Menus.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <vector>
#include <queue>

using namespace std;

#define     SNOWKINDS     30
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TImage *Image4;
    TImage *Image5;
    TImage *Image6;
    TImage *Image7;
    TImage *Image8;
    TImage *Image9;
    TImage *Image10;
    TImage *Image11;
    TImage *Image12;
    TImage *Image13;
    TImage *Image14;
    TImage *Image15;
    TImage *Image16;
    TImage *Image17;
    TImage *Image18;
    TImage *Image19;
    TImage *Image20;
    TImage *Image21;
    TImage *Image22;
    TImage *Image23;
    TImage *Image24;
    TImage *Image25;
    TImage *Image26;
    TImage *Image27;
    TImage *Image28;
    TImage *Image29;
    TImage *Image30;
    TImage *Image31;
    TImage *Image32;
    TImage *Image33;
    TImage *Image34;
    TImage *Image35;
    TImage *Image36;
    TImage *Image37;
    TImage *Image38;
    TImage *Image39;
    TImage *Image40;
    TTimer *TimerDown;
    TTrayIcon *TrayIcon1;
    TTimer *TimerNewSnow;
    TPopupMenu *PopupMenu1;
    TMenuItem *ExitItem;
    TMenuItem *AboutItem;
    TMenuItem *N1;
    TLabel *LabelHello;
    TControlBar *ControlBarSet;
    TGroupBox *GroupBoxSet;
    TLabeledEdit *LabeledEditSet;
    TBitBtn *BitBtnOK;
    TBitBtn *BitBtnNO;
    TBitBtn *BitBtnFont;
    TFontDialog *FontDialog1;
    TMenuItem *SetTextItem;
    TLabel *LabelReport;
    TComboBox *ComboBoxSnow;
    TMenuItem *HideSnowItem;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall TimerDownTimer(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
                              TShiftState Shift);
    void __fastcall AboutItemClick(TObject *Sender);
    void __fastcall ExitItemClick(TObject *Sender);
    void __fastcall BitBtnNOClick(TObject *Sender);
    void __fastcall SetSnowItemClick(TObject *Sender);
    void __fastcall BitBtnOKClick(TObject *Sender);
    void __fastcall BitBtnFontClick(TObject *Sender);
    void __fastcall LabeledEditSetChange(TObject *Sender);
    void __fastcall LabelReportClick(TObject *Sender);
    void __fastcall ComboBoxSnowChange(TObject *Sender);
    void __fastcall TimerNewSnowTimer(TObject *Sender);
    void __fastcall HideSnowItemClick(TObject *Sender);
    void __fastcall TrayIcon1Click(TObject *Sender);
private:	// User declarations
    TMediaPlayer *MediaPlayer;
    bool    MediaPlayerFlag;
    typedef struct GOFORWARD
    {
        int x;
        int y;
    } GOFORWARD;
    /*    typedef union  FreeBusy
        {
            bool       free;
            GOFORWARD  goforward;
        } FreeBusy;   //FreeBusy    freebusy;
        typedef struct Snow
        {
            TControl    *control;
            //FreeBusy    freebusy;
        } Snow;  */
    typedef TControl*   Snow;
    typedef struct FreeSnow
    {
        Snow    snow;
        bool    free;
    } FreeSnow;
    typedef struct BusySnow
    {
        Snow    snow;
        GOFORWARD  goforward;
        int     index;
    } BusySnow;
    int     downrate;//下落速度
    //FreeSnow    freesnow[SNOWNUM];
    vector<FreeSnow >   freesnow_vec;
    vector<BusySnow>    busysnow;
    queue<int>      queue_index;//?????????
    TImage       *ImageExample[SNOWKINDS];

public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void    RandSnow(); //随机产生雪花
    bool    CheckOver(int left ,int top);//判断雪花是否在屏幕越界
    void    NewSnow(int newnum);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
