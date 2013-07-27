//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitHello.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THelloForm *HelloForm;
//---------------------------------------------------------------------------
__fastcall THelloForm::THelloForm(TComponent* Owner)
    : TForm(Owner)
{
    /*     */
    Visible = false;
    this->AutoSize = false;
}
//---------------------------------------------------------------------------
void __fastcall THelloForm::OnWmBkgnd(TMessage &Msg)
{
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
      (for example, when a window is resized). The message is sent to prepare an
      invalidated portion of a window for painting.           */
    Msg.Result = true;
}
//---------------------------------------------------------------------------
void    THelloForm::ImageFadeOut(TCanvas* canvas)
{
    Byte    *ptr;
    Graphics::TBitmap* p = new Graphics::TBitmap;
    try
    {
        p->Assign(imgExample->Picture->Bitmap);
        p->PixelFormat = pf24bit;
        for (int i=0; i<256; i++)
        {
            for (int y=0; y<p->Height; y++)
            {
                ptr = (Byte *)p->ScanLine[y];
                for (int x=0; x<p->Width*3; x++)
                {
                    if (ptr[x]>0)
                        ptr[x] = Byte(ptr[x]-1);
                }
                Application->ProcessMessages();
            }
            canvas->Draw(0,0,p);
            ::Sleep(10);
        }
        //throw Exception("test throw ...");//test ...
    }
    catch(...)//Exception& e
    {
        //if(p)  delete p;
        //Close(); //ShowMessage(e.Message)
    }
    //ShowMessage("delete p;");
    if(p)  delete p;
}
//---------------------------------------------------------------------------
void    THelloForm::ImageFadeIn(TCanvas* canvas)
{
    //  int     i,x,y;
    Byte *ptr1 , *ptr2;
    Graphics::TBitmap* p1 = new Graphics::TBitmap;
    Graphics::TBitmap* p2 = new Graphics::TBitmap;
    try
    {
        p1->Assign(imgExample->Picture->Bitmap);
        p2->Assign(imgExample->Picture->Bitmap);
        p1->PixelFormat = pf24bit;
        p2->PixelFormat = pf24bit;
        for (int y=0; y<p2->Height; y++)
        {
            ptr2 = (Byte *)p2->ScanLine[y];
            for (int x=0; x<p2->Width*3; x++)
            {
                ptr2[x] = 0;
            }
            Application->ProcessMessages();
        }
        //µ­³ö
        for (int i=0; i<256; i++)
        {
            for (int y=0; y<p2->Height; y++)
            {
                ptr1 = (Byte *)p1->ScanLine[y];
                ptr2 = (Byte *)p2->ScanLine[y];
                for (int x=0; x<p2->Width*3; x++)
                    if (ptr2[x]<ptr1[x])
                        ptr2[x] = Byte(ptr2[x]+1);
                Application->ProcessMessages();
            }
            canvas->Draw(0,0,p2);
            ::Sleep(10);
        }
    }
    catch(...)
    {
        //if(p1) delete p1; if(p2) delete p2;
        //Close();// ...
    }
    if(p1) delete p1;
    if(p2) delete p2;
}
//---------------------------------------------------------------------------
void __fastcall THelloForm::FormCreate(TObject *Sender)
{
    /*    */
    imgExample->Visible = false;
    LabelHello->Transparent = true;
    LabelHello->Caption = "You're welcome!";
    LabelHello->Top  = 2;
    LabelHello->Left = 2;
    LabelMe->Transparent = true;
    LabelMe->Caption = "Esc for exit";
    LabelMe->Left = 2;
    LabelMe->Top  = Height-LabelMe->Height-10;
}
//---------------------------------------------------------------------------
/*
#define AW_HOR_POSITIVE             0x00000001
#define AW_HOR_NEGATIVE             0x00000002
#define AW_VER_POSITIVE             0x00000004
#define AW_VER_NEGATIVE             0x00000008
#define AW_CENTER                   0x00000010
#define AW_HIDE                     0x00010000
#define AW_ACTIVATE                 0x00020000
#define AW_SLIDE                    0x00040000
#define AW_BLEND                    0x00080000
*/
void __fastcall THelloForm::FormShow(TObject *Sender)
{
    /*      */
    //FormStyle = fsStayOnTop; // Error .........
    Left = (Screen->Width-Width)>>1;//
    Top  = (Screen->Height-Height)>>1;
    this->Color = clRed;
    AnimateWindow(this->Handle ,3000 ,AW_CENTER |AW_BLEND);//AW_SLIDE |AW_HOR_POSITIVE |AW_VER_POSITIVE
    ::Sleep(1000);
    ImageFadeIn(this->Canvas);
    this->Repaint(); //...
    /*
    //Canvas->CopyRect(Canvas->ClipRect ,imgExample->Canvas , \
    //    imgExample->Canvas->ClipRect);
    //::Sleep(5000);
    this->Close();   */
}
//---------------------------------------------------------------------------
void __fastcall THelloForm::FormPaint(TObject *Sender)
{
    /*   */
    //this->Canvas->FillRect(this->GetClientRect());
    this->Canvas->Draw(0 ,0 ,imgExample->Picture->Bitmap);
}
//---------------------------------------------------------------------------
void __fastcall THelloForm::FormClose(TObject *Sender,
                                      TCloseAction &Action)
{
    ImageFadeOut(this->Canvas);
    ::Sleep(1000);
    //ShowMessage("FormClose ...");
    this->Color = clSkyBlue;
    AnimateWindow(Handle ,3000 , \
                  AW_HIDE | AW_SLIDE |AW_HOR_POSITIVE |AW_VER_POSITIVE);// AW_BLEND
}
//---------------------------------------------------------------------------
void __fastcall THelloForm::FormKeyUp(TObject *Sender, WORD &Key,
                                      TShiftState Shift)
{
    if(Key==27)
        Close();
}
//---------------------------------------------------------------------------


