//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
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
#include <ImgList.hpp>
#include <MPlayer.hpp>
#include <Dialogs.hpp>
#include <Mmsystem.h.> //sndPlaySound
//#include <Winbase.h>
#include <IniFiles.hpp>

#include <vector>
#include <math.h>
using namespace std;

#include "UnitThread.h"
#include "UnitSnow.h"
#include "UnitSrollText.h"
#include "UnitDrawCurves.h"

#define IMAGECOUNT      6  //Í¼Æ¬×ÜÊý
//---------------------------------------------------------------------------
/*
 #define POINTNUMS 40
 #define ANGLE   (360.0/POINTNUMS)
 #define PIECE   20
 #define PERIODS 2
*/
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMenuItem *miAllStart;
    TMenuItem *miAllStop;
    TMenuItem *N2;
    TMenuItem *miClose;
    TTrayIcon *TrayIcon1;
    TPopupMenu *PopupMenu1;
    TTimer *Timer1;
    TMenuItem *TEST1;
    TImage *Image6;
    TImage *Image5;
    TImage *Image4;
    TImage *Image3;
    TImage *Image2;
    TImage *Image1;
    TImageList *ImageList1;
    TMenuItem *miAbout;
    TMenuItem *N1;
    TMenuItem *miSnowTest;
    TMenuItem *miFlyAngleTest;
    TMenuItem *miDrawCurvesTest;
    TMenuItem *miSrollTextTest;
    TMenuItem *miMusicTest;
    TMenuItem *miLittleSnows;
    TMenuItem *miSoSoSnows;
    TMenuItem *miManySnows;
    TMenuItem *miNoSnows;
    TMenuItem *miFlyFromMe;
    TMenuItem *miFlyFreely;
    TMenuItem *miAllFly;
    TMenuItem *miNoFly;
    TMenuItem *miDrawCurves;
    TMenuItem *miNoDrawCurves;
    TMenuItem *miSrollText;
    TMenuItem *miNoSrollText;
    TMenuItem *miSrollTextForMe;
    TMenuItem *miMusic;
    TMenuItem *miNoMusic;
    TMenuItem *miMusicForMe;
    TMenuItem *miForHint;
    TMediaPlayer *MediaPlayer1;
    TOpenDialog *OpenDialog1;
    TMenuItem *miSaveConfig;
    TMenuItem *N3;
    TMenuItem *miSnowHint;
    TMenuItem *miFlyAngleHint;
    TMenuItem *miDrawCurvesHint;
    TMenuItem *miSrollTextHint;
    TMenuItem *miMusicHint;
    TMenuItem *miLittleSnowsHint;
    TMenuItem *miSoSoSnowsHint;
    TMenuItem *miManySnowsHint;
    TMenuItem *miNoSnowsHint;
    TMenuItem *miFlyFromMeHint;
    TMenuItem *miFlyFreelyHint;
    TMenuItem *miAllFlyHint;
    TMenuItem *miNoFlyHint;
    TMenuItem *miNoDrawCurvesHint;
    TMenuItem *miSrollHint;
    TMenuItem *miNoSrollHint;
    TMenuItem *miSrollTextForMeHint;
    TMenuItem *miMusicHints;
    TMenuItem *miNoMusicHint;
    TMenuItem *miMusicForMeHint;
    TMenuItem *Ctrl1;
    TMenuItem *miAllStartHint;
    TMenuItem *miAllStopHint;
    TMenuItem *miCloseHint;
    TMenuItem *miAboutHint;
    TLabel *LabelHello;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall miAllStartClick(TObject *Sender);
    // void __fastcall TrayIcon1Create(TObject *Sender);
    void __fastcall miAllStopClick(TObject *Sender);
    void __fastcall miCloseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall TEST1Click(TObject *Sender);
    void __fastcall miLittleSnowsClick(TObject *Sender);
    void __fastcall miFlyFromMeClick(TObject *Sender);
    void __fastcall miDrawCurvesClick(TObject *Sender);
    void __fastcall miSrollTextClick(TObject *Sender);
    void __fastcall miMusicClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall miSaveConfigClick(TObject *Sender);
    void __fastcall miAboutClick(TObject *Sender);
public:       /*
    enum { POINTNUMS = 40  };
    //enum { ANGLE =  (360.0/POINTNUMS) };
    #define ANGLE   (360.0/POINTNUMS)
    enum { PIECE  = 40   };
    enum { PERIODS = 2   };  enum { ONE_PERIOD_DIVIDES = 4 };    */
private:	// User declarations
    // ·ÉÄñ ....
    TFlyFollowCursor   *flyFollowCursor;
    TFlyFollowPath     *flyFollowPath;//*flyFollowPath1 ,*flyFollowPath2;
    TFlyAngel          *flyAngel;// Test ...
    // ÏÂÑ© ...
    TSnow*   snow;
    // ¹ö¶¯×ÖÄ¸ ...
    TSrollText  *srollText;
    String      textFileName;
    // »æÖÆÕýÏÒÇúÏß ...
    TDrawCurves *drawCurves;
    // ±³¾°ÒôÀÖ ...
    //char *chWavHandle;//¶¨ÒåÉùÒô¾ä±ú
    bool    bMediaPlayerFlag;
    String      musicFileName;
    // ±£´æConfig ÐÅÏ¢
    TNotifyEvent miItemClicks[5];
    // ...
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall ThreadDone(TObject *);
//ÖÆÖ¹ÖØ»­´°¿Ú±³¾°
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    //void __fastcall keyDownUpdate(WORD Key);
    friend LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam);
    bool    loadIniFile(const String& filename="YourConfig.ini");
    bool    saveIniFile(const String& filename="YourConfig.ini");
    /*//Notice: (TIniFile)Usually INI files are stored in the \WINDOWS directory.
    To work with an INI file in another location, specify the full path name of the file
    in the FileName parameter passed to the Create method of TCustomIniFile.  */

    /*     */
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
    END_MESSAGE_MAP(TForm)
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
    (for example, when a window is resized). The message is sent to prepare an
    invalidated portion of a window for painting.           */
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
