/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#ifndef RegionH
#define RegionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Clipbrd.hpp>
#include <Dialogs.hpp>

#include "main.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class  TShape_;// 声明 -------
class TRForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
    TLabel *lblCapture;
    TCoolBar *CoolBar1;
    TToolBar *ToolBar1;
    TToolButton *tbRectangle;
    TToolButton *tbRound;
    TToolButton *tbWord;
    TToolButton *tbLine;
    TToolButton *tbUndo;
    TToolBar *ToolBar2;
    TToolButton *tbSetPenBrush;
    TToolButton *tbFont;
    TToolButton *tbSaveAs;
    TToolButton *tbExit;
    TToolButton *ToolButton1;
    TToolButton *tbOKCapture;
    TToolButton *ToolButton2;
    TPopupMenu *PopupMenu1;
    TMenuItem *miAddRectangle;
    TMenuItem *miAddRound;
    TMenuItem *miaddWord;
    TImageList *ImageList1;
    TPanel *panelPenBrush;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label1;
    TComboBox *cbPenMode;
    TComboBox *cbBrushStyle;
    TComboBox *cbPenStyle;
    TBitBtn *btnPenColor;
    TBitBtn *btnBrushColor;
    TUpDown *UpDown1;
    TEdit *etPenWidth;
    TToolButton *tbRoundRect;
    TImage *Image2;
    TPanel *plImage2;
    TColorDialog *ColorDialog1;
    TFontDialog *FontDialog1;
    TBitBtn *btnSetPBOK;
    TEdit *editWord;
    TSaveDialog *SaveDialog1;
    TMenuItem *miAddLine;
    TMenuItem *miAddRoundRect;
    TMenuItem *N3;
    TMenuItem *miReCapture;
    TMenuItem *miOKCapture;
    TMenuItem *miSaveAsCapture;
    TMenuItem *N7;
    TMenuItem *miShowHideTB;
    TMenuItem *miExit;
    TMenuItem *miUndo;
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Image1DblClick(TObject *Sender);
    void __fastcall tbRectangleClick(TObject *Sender);
    void __fastcall tbUndoClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Image2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Image2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall tbOKCaptureClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Image2DblClick(TObject *Sender);
    void __fastcall tbExitClick(TObject *Sender);
    void __fastcall tbFontClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall SetPenBrushColorClick(TObject *Sender);
    void __fastcall tbSetPenBrushClick(TObject *Sender);
    void __fastcall btnSetPBOKClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall editWordKeyPress(TObject *Sender, char &Key);
    void __fastcall tbSaveAsClick(TObject *Sender);
    void __fastcall miAddRectangleClick(TObject *Sender);
    void __fastcall miAddRoundClick(TObject *Sender);
    void __fastcall miaddWordClick(TObject *Sender);
    void __fastcall miAddLineClick(TObject *Sender);
    void __fastcall miAddRoundRectClick(TObject *Sender);
    void __fastcall miShowHideTBClick(TObject *Sender);
    void __fastcall miReCaptureClick(TObject *Sender);
private:	// User declarations
        enum TRectPos { epLeftUp ,epRightUp ,epLeftDown,epRightDown };
        TRectPos    selectdPos;
        TRect   selectedRt;
//画图操作：1--画矩形，2--画圆，3--写字，4--画线条,5--画圆矩形，0--No Draw
        int     iWhichShapeDraw;
        vector<TShape_*>    vecShapes;
        TShape_*    shapeTemp;//临时画图的对象
        TPen*   curSetPen;
        TBrush* curSetBrush;
private:
        void    ShowlblCapture(int x ,int y ,int  w ,int h ,TColor c);
        void    HandleSelRect(int   X ,int  Y);
        void    ShowCusorOnImg(int   X ,int  Y);

        void    DrawRect(TPoint TopLeft, TPoint BottomRight, TPenMode Mode);
        void    ShowPenBrush(TPen* p ,TBrush* b);
        void    SetCurPenBrush(TPen* p ,TBrush* b);
public:
        bool    bIsRegionSelected;
        bool    bLeftMDown ,bLeftMDown_; //bLeftMBDown--Image1 ,bLeftMBDown_--Image2
        TPoint  originPt, movePt ,leftDownPt;
public:		// User declarations
        __fastcall TRForm(TComponent* Owner);
        void    CaptureRegion(void);
        void    SaveAsImage(Graphics::TBitmap* bmp ,int imgExt ,String fileName);
        void    SetSelectedRt();
        void    InitRegionCapture();
        void    InitAllPenBrush();
        void    MoveSelectedRt(int  x ,int  y);
        void    ResizeSelectedRt(int  x ,int  y);
};

extern PACKAGE TRForm *RForm;
//---------------------------------------------------------------------------
class  TShape_
{
//private:
public:
//    TColor  penColor ,brushColor;
//    int     penWidth;
protected:
    TPoint  ptLeftTop ,ptRightBottom;
    TPen*    pen;
    TBrush*  brush;
    void    DeleteObj()
    {
        if(pen!=NULL)
        {
            delete pen;
            pen = NULL;
        }
        if(brush!=NULL)
        {
            delete brush;
            brush = NULL;
        }
    }
    void    SetPenBrush_(TPen* p ,TBrush* b)
    {
        NewPenBrush();
        SetPen(p);
        SetBrush(b);
    }
private:
    void    SetPen(TPen* p)
    {
        pen->Assign(p);
    }
    void    SetBrush(TBrush* b)
    {
        brush->Assign(b);
    }
    void    NewPenBrush()
    {
        pen = new TPen;
        brush = new TBrush;
    }
public:
    TShape_() { pen=NULL;brush=NULL;}
    explicit TShape_(const TPoint& p1 ,const TPoint& p2)
             : ptLeftTop(p1) ,ptRightBottom(p2)
    { NewPenBrush(); }
    void    SetRect(const TPoint& p1 ,const TPoint& p2)
    {
        ptLeftTop = p1;
        ptRightBottom = p2;
    }
    TPoint& GetLeftTop()
    {
        return  ptLeftTop;
    }
    virtual void Draw(TCanvas* pC) = 0;
    virtual void Clear(TCanvas* pC) = 0;
    virtual ~TShape_() { DeleteObj(); }  // ....
};
class   TRectangle : public TShape_
{
public:
    static TPen*   curPen;
    static TBrush* curBrush;
public:
    TRectangle():TShape_() { SetPenBrush(); }
    explicit TRectangle(const TPoint& p1 ,const TPoint& p2)
             :TShape_(p1 ,p2) { SetPenBrush(); }

    void SetPenBrush() { SetPenBrush_(curPen ,curBrush); }
    void Draw(TCanvas* pC);
    void Clear(TCanvas* pC);
    virtual ~TRectangle()
    {
        DeleteObj();
    }
};

class   TRound : public TShape_
{
public:
    static TPen*   curPen;
    static TBrush* curBrush;
public:
    TRound():TShape_() { SetPenBrush(); }
    explicit TRound(const TPoint& p1 ,const TPoint& p2)
             :TShape_(p1 ,p2) { SetPenBrush(); }

    void SetPenBrush() { SetPenBrush_(curPen ,curBrush); }
    void Draw(TCanvas* pC);
    void Clear(TCanvas* pC);
    virtual ~TRound()
    {
        DeleteObj();
    }
};
class   TLine : public TShape_
{
public:
    static TPen*   curPen;
    static TBrush* curBrush;
public:
    TLine():TShape_() { SetPenBrush(); }
    explicit TLine(const TPoint& p1 ,const TPoint& p2)
             :TShape_(p1 ,p2) { SetPenBrush(); }

    void SetPenBrush() { SetPenBrush_(curPen ,curBrush); }
    void Draw(TCanvas* pC);
    void Clear(TCanvas* pC);
    virtual ~TLine()
    {
        DeleteObj();
    }
};
class   TRoundRect : public TShape_
{
public:
    static TPen*   curPen;
    static TBrush* curBrush;
public:
    TRoundRect():TShape_() { SetPenBrush(); }
    explicit TRoundRect(const TPoint& p1 ,const TPoint& p2)
             :TShape_(p1 ,p2) { SetPenBrush(); }

    void SetPenBrush() { SetPenBrush_(curPen ,curBrush); }
    void Draw(TCanvas* pC);
    void Clear(TCanvas* pC);
    virtual ~TRoundRect()
    {
        DeleteObj();
    }
};
class   TWord : public TShape_
{  /*
public:
    static TPen*   curPen;
    static TBrush* curBrush;    */
public:
    static TFont* curFont; // form FontDialog .....
    TFont*  font;
    //TImage* image;
    Graphics::TBitmap   *bmp;
    String  text;
public:
    TWord():TShape_() //SetPenBrush();
    {
        font = new TFont;
        font->Assign(curFont);
        bmp = new Graphics::TBitmap;
        /*
        image = new TImage(RForm);
        image->Parent = RForm;
        image->Visible = false;*/

    }
    explicit TWord(const TPoint& p1 ,const TPoint& p2)
             :TShape_(p1 ,p2) {}

    //void SetPenBrush() { SetPenBrush_(curPen ,curBrush); }
    void Draw(TCanvas* pC);
    void Clear(TCanvas* pC);
    virtual ~TWord()
    {
        DeleteObj();
        delete  font;
        delete  bmp;
        //delete image;
    }
};
//---------------------------------------------------------------------------
#endif
