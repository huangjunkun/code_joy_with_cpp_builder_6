/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "trayicon.h"
#include <Graphics.hpp>
#include <ExtDlgs.hpp>
const int crCursor_    = 1;
const int crCross_  = 2;
const int crPen_    = 3;
const int crSizeNWSE_    = 4;
const int crSizeNESW_  = 5;
const int crSizeAll_  = 6;
/*   */
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *miFile;
    TMenuItem *miSaveImg;
    TMenuItem *N2;
    TMenuItem *miExit;
    TCoolBar *CoolBar1;
    TStatusBar *StatusBar1;
    TToolBar *ToolBar1;
    TToolButton *tbOpenImg;
    TImageList *ImageList1;
    TToolButton *tbSaveImg;
    TToolButton *tbSaveAsImg;
    TToolButton *tbPasteImg;
    TToolButton *ToolButton11;
    TToolButton *tbCopyImg;
    TToolButton *tbCutImg;
    TToolButton *tbClearProImg;
    TPanel *Panel1;
    TCoolBar *CoolBar2;
    TToolBar *ToolBar2;
    TToolButton *tbGrayLinTrans;
    TToolButton *tbLinerTranslation;
    TToolButton *tbTemplateSoften;
    TToolButton *tbNearbySoften;
    TToolButton *ToolButton24;
    TToolButton *tbLaplacSharp;
    TToolButton *tbMedianFilter;
    TPanel *panelHint;
    TTrayIcon *TrayIcon1;
    TPopupMenu *PopupMenu1;
    TMenuItem *pmExit;
    TImage *Image3;
    TToolButton *tbCarveRilievo;
    TToolButton *tbImageRever;
    TToolButton *ToolButton7;
    TToolButton *tbRotaTion;
    TToolButton *tbHSVTranslation;
    TToolButton *tbRGBTranslation;
    TToolButton *tbHistEnhance;
    TToolButton *tbAshTrans;
    TToolButton *ToolButton19;
    TToolButton *ToolButton20;
    TMenuItem *miCapture;
    TMenuItem *miCaptureScreen;
    TMenuItem *miCaptureWindow;
    TMenuItem *miCaptureRegion;
    TMenuItem *miProcess;
    TMenuItem *miHelp;
    TMenuItem *miHelpFile;
    TMenuItem *miAboutApp;
    TMenuItem *N3;
    TMenuItem *miOpenImg;
    TMenuItem *miSaveAsImg;
    TToolButton *ToolButton5;
    TToolButton *tbCaptureScreen;
    TToolButton *tmCaptureWindow;
    TToolButton *tbCaptureRegion;
    TToolButton *ToolButton15;
    TToolButton *tbHelpFile;
    TToolButton *tbAboutApp;
    TOpenDialog *OpenDialog1;
    TMenuItem *miGrayLinTrans;
    TImageList *ImageList2;
    TMenuItem *miLinerTranslation;
    TMenuItem *miTemplateSoften;
    TMenuItem *miNearbySoften;
    TMenuItem *miMedianFilter;
    TMenuItem *miCarveRilievo;
    TMenuItem *N9;
    TMenuItem *miImageRever;
    TMenuItem *miRotaTion;
    TMenuItem *N12;
    TMenuItem *miHSVTranslation;
    TMenuItem *miRGBTranslation;
    TMenuItem *miHistEnhance;
    TMenuItem *miLaplacSharp;
    TMenuItem *pmCaptureScreen;
    TMenuItem *pmCaptureWindow;
    TMenuItem *pmCaptureRegion;
    TMenuItem *N6;
    TMenuItem *N1;
    TMenuItem *miCutImg;
    TMenuItem *miPasteImg;
    TMenuItem *miCopyImg;
    TGroupBox *GroupBox1;
    TScrollBox *ScrollBox1;
    TImage *Image1;
    TSplitter *Splitter1;
    TGroupBox *GroupBox2;
    TScrollBox *ScrollBox2;
    TImage *Image2;
    TTimer *Timer1;
    TLabel *lblTime;
    TToolButton *tbtest;
    TMenuItem *miClearProImg;
    TMenuItem *miAshTrans;
    void __fastcall miCaptureScreenClick(TObject *Sender);
    void __fastcall miCaptureWindowClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall miCaptureRegionClick(TObject *Sender);
    void __fastcall miSaveImgClick(TObject *Sender);
    void __fastcall miExitClick(TObject *Sender);
    void __fastcall miFileAdvancedDrawItem(TObject *Sender,
                                           TCanvas *ACanvas, TRect &ARect, TOwnerDrawState State);
    void __fastcall tbGrayLinTransMouseMove(TObject *Sender,
                                            TShiftState Shift, int X, int Y);
    void __fastcall miOpenImgClick(TObject *Sender);
    void __fastcall miSaveAsImgClick(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
                                    int X, int Y);
    void __fastcall miCopyImgClick(TObject *Sender);
    void __fastcall miPasteImgClick(TObject *Sender);
    void __fastcall miCutImgClick(TObject *Sender);
    void __fastcall miRotaTionClick(TObject *Sender);
    void __fastcall miHelpFileClick(TObject *Sender);
    void __fastcall miAboutAppClick(TObject *Sender);
    void __fastcall TrayIcon1Click(TObject *Sender);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
                                    TShiftState Shift, int X, int Y);
    void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
                                  TShiftState Shift, int X, int Y);
    void __fastcall ToolButton19Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall miClearProImgClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall miGrayLinTransClick(TObject *Sender);
    void __fastcall miLinerTranslationClick(TObject *Sender);
    void __fastcall miTemplateSoftenClick(TObject *Sender);
    void __fastcall miNearbySoftenClick(TObject *Sender);
    void __fastcall miLaplacSharpClick(TObject *Sender);
    void __fastcall miMedianFilterClick(TObject *Sender);
    void __fastcall miCarveRilievoClick(TObject *Sender);
    void __fastcall miImageReverClick(TObject *Sender);
    void __fastcall miHSVTranslationClick(TObject *Sender);
    void __fastcall miRGBTranslationClick(TObject *Sender);
    void __fastcall miHistEnhanceClick(TObject *Sender);
    void __fastcall miAshTransClick(TObject *Sender);
    void __fastcall ScrollBox1MouseDown(TObject *Sender,
                                        TMouseButton Button, TShiftState Shift, int X, int Y);

private:	// User declarations
    Graphics::TBitmap *pBitmap;
    void CaptureDesktop(HDC DesImage);
    void CaptureWinImage(TRect rect);
    HWND GetTopWin(void);
    Graphics::TBitmap* GetBitmapToProcess();
    void ProcessImg(const String& strFunc);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    bool    bLeftMBDown;
    TPoint  originPt; //, movePt ,leftDownPt


    void __fastcall WMLBUTTONDOWN(TMessage &Msg);
    //void __fastcall WndProc(TMessage &Msg);
    friend void    MyWndProc(TMessage &Msg); /*
//（截获消息）消息映射表
    BEGIN_MESSAGE_MAP
       // MESSAGE_HANDLER(WM_LBUTTONDOWN,TMessage,WMLBUTTONDOWN) //法一，消息映射
    END_MESSAGE_MAP(TMainForm) //     */
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern PACKAGE HHOOK   OldHook;
//---------------------------------------------------------------------------
#endif
