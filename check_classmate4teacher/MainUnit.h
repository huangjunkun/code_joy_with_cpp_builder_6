//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Jpeg.hpp>
//#include "pies.h"
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <math.h>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <ExtDlgs.hpp>
#include <FileCtrl.hpp>  //  TOpenPictureDialog
#include <Windowsx.h.h>

#include <fstream>
#include <string>
#include <stdlib>
#include <time.h>

using namespace std;

#define PI 3.1415926535897932385
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *PanelView;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *OpenAllMenu;
    TMenuItem *OpenAbsenceMenu;
    TOpenDialog *OpenDialog1;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TMemo *MemoAbsence;
    TButton *ButtonAbsenseEdit;
    TButton *ButtonAbsenceSave;
    TButton *ButtonAbsenceRefresh;
    TTabSheet *TabSheet3;
    TMemo *MemoStudent;
    TButton *ButtonAllEdit;
    TButton *ButtonAllSave;
    TButton *ButtonAllRefresh;
    TTabSheet *TabSheet4;
    TMenuItem *OpenStudentMenu;
    TLabel *LabelStatistics;
    TImage *ImageStatistics;
    TMenuItem *N1;
    TMenuItem *ExitMenu;
    TStatusBar *StatusBar1;
    TMenuItem *Help1;
    TImageList *ImageList1;
    TMenuItem *HelpMenu;
    TMenuItem *AboutMenu;
    TBitBtn *BitBtnStatistics;
    TBitBtn *BitBtnAllSave;
    TBitBtn *BitBtnAbsenceSave;
    TSaveDialog *SaveDialog1;
    TPopupMenu *PopupMenu1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TPaintBox *PaintBoxAbout;
    TTimer *TimerFlash;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *SetDiplayPopup;
    TMenuItem *Play1;
    TMenuItem *FlyAngelMenu;
    TMenuItem *FlyAngelPopup;
    TCheckBox *CheckBoxFileSta;
    TPanel *PanelFileSta;
    TPanel *PanelSelFile;
    TDriveComboBox *DriveComboBox1;
    TDirectoryListBox *DirectoryListBox1;
    TFilterComboBox *FilterComboBox1;
    TFileListBox *FileListBox1;
    TPopupMenu *PopupMenu2;
    TMenuItem *ImportFilePopup;
    TMenuItem *ImportFileAbout;
    TEdit *Edit1;
    TSplitter *Splitter1;
    TStringGrid *StringGrid1;
    TMenuItem *ExportFilePopup;
    TScrollBox *ScrollBox1;
    TListBox *ListBoxCheck;
    TLabeledEdit *LabeledEdit2;
    TButton *ButtonAbsence;
    TButton *ButtonCheck;
    TCheckBox *CheckBoxRandom;
    TLabeledEdit *LabeledEdit1;
    TButton *ButtonRondomCheck;
    TImage *Image1;
    TMenuItem *SetSkinMenu;
    TMenuItem *IsLoadSkinMenu;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ListBoxCheckKeyPress(TObject *Sender, char &Key);
    void __fastcall ButtonCheckClick(TObject *Sender);
    void __fastcall ButtonAbsenceClick(TObject *Sender);
    void __fastcall ButtonAbsenseEditClick(TObject *Sender);
    void __fastcall ButtonAbsenceSaveClick(TObject *Sender);
    void __fastcall ButtonAbsenceRefreshClick(TObject *Sender);
    void __fastcall CheckBoxRandomClick(TObject *Sender);
    void __fastcall ButtonRondomCheckClick(TObject *Sender);
    void __fastcall LabeledEdit1Change(TObject *Sender);
    void __fastcall ButtonAllEditClick(TObject *Sender);
    void __fastcall ButtonAllSaveClick(TObject *Sender);
    void __fastcall ButtonAllRefreshClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall OpenAllMenuClick(TObject *Sender);
    void __fastcall OpenAbsenceMenuClick(TObject *Sender);
    void __fastcall OpenStudentMenuClick(TObject *Sender);
    void __fastcall ExitMenuClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall PageControl1Change(TObject *Sender);
    void __fastcall Image1DblClick(TObject *Sender);
    void __fastcall BitBtnStatisticsClick(TObject *Sender);
    void __fastcall AboutMenuClick(TObject *Sender);
    void __fastcall HelpMenuClick(TObject *Sender);
    void __fastcall BitBtnAbsenceSaveClick(TObject *Sender);
    void __fastcall BitBtnAllSaveClick(TObject *Sender);
    void __fastcall TimerFlashTimer(TObject *Sender);
    void __fastcall PaintBoxAboutMouseMove(TObject *Sender,
                                           TShiftState Shift, int X, int Y);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ListBoxCheckMouseMove(TObject *Sender,
                                          TShiftState Shift, int X, int Y);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ButtonCheckMouseDown(TObject *Sender,
                                         TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ButtonCheckMouseUp(TObject *Sender,
                                       TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall SetDiplayPopupClick(TObject *Sender);
    void __fastcall FlyAngelMenuClick(TObject *Sender);
    void __fastcall CheckBoxFileStaClick(TObject *Sender);
    void __fastcall ImportFileAboutClick(TObject *Sender);
    void __fastcall ImportFilePopupClick(TObject *Sender);
    void __fastcall ExportFilePopupClick(TObject *Sender);
    void __fastcall ListBoxCheckClick(TObject *Sender);
    void __fastcall IsLoadSkinMenuClick(TObject *Sender);
    void __fastcall SetSkinMenuClick(TObject *Sender);

private:	// User declarations
//   void __fastcall WndProc(TMessage    &Message);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall TimerTimer(TObject *Sender);
    void    SaveAbsenceRecord(String filename);

    String  AbsenceFile ,RosterFile;//缺勤文件名 ，花名册文件名
    int     RondomNum ,RondomNO;
    TTimer *NowTimer;
//文字滚动----------
    TStringList *AboutStringList;
    RECT *StringRectangles;
    int *StringColorIndex;
    int StringColorCount;
    COLORREF **StringColors;
    TCursor *StringCursors;
    typedef void __fastcall (__closure *PFNOnClick)(TObject *);
    PFNOnClick *StringOnClicks;
    int StringCount;
    int StringMaximumWidth;
    int StringsHeight;
    int CurrentStringIndex;
    int PictureTop;
    void    TMainForm::InitScrollWords();
    void __fastcall DrawAboutFlash(TObject *Sender);
    bool    bShowWord;
    /*
        void __fastcall WMNCHITTEST(TMessage &Message);
        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(WM_NCHITTEST,TMessage,WMNCHITTEST)
        END_MESSAGE_MAP(TForm) //     */
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
