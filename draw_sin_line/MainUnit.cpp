//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    iAmplitude = 200;
    iPeriod    = 400;
}
//---------------------------------------------------------------------------

void TMainForm::InitdSin()
{
    //double  angle = 360/NUM;
    for(int i=0; i<NUM; i++)
        dSin[i] =  iAmplitude*sin(ANGLE*i/180*M_PI)+iAmplitude; //sin(angle*i/180*M_PI);
    this->Canvas->Pen->Color = clLime;
    this->DoubleBuffered = true;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //-----
    InitdSin();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
    /*    //-----  test --------
      this->Canvas->MoveTo(0 ,200);
      for(int i=0;i<NUM*3;i++)
      {
          double  angle = 360/NUM;
          int     x = i*5;
          int     y = dSin[i%NUM];//;x*dSin[i%NUM]+200;
          this->Canvas->LineTo(x ,y);
      }       */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    static  int iY = 0;
    this->Canvas->FillRect(this->Canvas->ClipRect);
    this->Canvas->MoveTo(0 ,iAmplitude);
    for(unsigned int i=0 ,j=(iY++)%NUM; i<NUM*6; i++ ,j++)
    {
        int     x = i*iPeriod/NUM;
        int     y = dSin[j%NUM]; //;x*dSin[i%NUM]+200;
        this->Canvas->LineTo(x ,y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
                                       TShiftState Shift)
{
    switch(Key)
    {
    case VK_RIGHT:
        iPeriod    += PIECE;
        break;
    case VK_LEFT:
        iPeriod    -= PIECE;
        break;
    case VK_UP:
        iAmplitude += PIECE;
        break;
    case VK_DOWN:
        iAmplitude -= PIECE;
        break;
    default :
        return;
    }
    InitdSin();
}
//---------------------------------------------------------------------------

