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

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <assert.h>
#include <fstream>
#include <algorithms>
using namespace std;
#include "UnitSnow.h"
#include "UnitRose.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TTrayIcon *TrayIcon1;
    TPopupMenu *PopupMenu1;
    TMenuItem *miExit;
    TMenuItem *miHello;
    TMenuItem *miTEST;
    TImageList *ImageList1;
    TLabel *LabelHello;
    TTimer *Timer1;
    TImageList *ImageList2;
    TImage *Image24;
    TImage *Image23;
    TImage *Image22;
    TImage *Image21;
    TImage *Image20;
    TImage *Image19;
    TImage *Image18;
    TImage *Image17;
    TImage *Image16;
    TImage *Image15;
    TImage *Image14;
    TImage *Image13;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall miHelloClick(TObject *Sender);
    void __fastcall miTESTClick(TObject *Sender);
    void __fastcall miExitClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    // 下雪 ...
    TSnow*   snow;
    TImageList  *imageList;
    int     bmpWidth ,bmpHeight ,bmpIndex;
    vector<TPoint>  ptVec;
    vector<int>     indexVec;
    int     blockIndex;
    //bool    bIsPlay;
    TRose_Thread   *rose_Tread;
    TRose   *rose;

public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall     doPlay();
//制止重画窗口背景
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    // ...
    /*//Notice: (TIniFile)Usually INI files are stored in the \WINDOWS directory.
    To work with an INI file in another location, specify the full path name of the file
    in the FileName parameter passed to the Create method of TCustomIniFile.  */
    /*
       BEGIN_MESSAGE_MAP
           MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
       END_MESSAGE_MAP(TForm)    */
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
    (for example, when a window is resized). The message is sent to prepare an
    invalidated portion of a window for painting.           */
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
