//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <math.h>
#include <ExtCtrls.hpp>

#define NUM 40
#define ANGLE   (360.0/NUM)
#define PIECE   20
//#define AMPLITUDE   200  // 振幅/2
//#define PERIOD  400  // 周期 period
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer1;
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
                                TShiftState Shift);
private:	// User declarations
    double  dSin[NUM];
    int     iAmplitude;  // 振幅/2
    int     iPeriod; // 周期 period
//    int     Initphase; //初相位 --
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void    InitdSin();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
