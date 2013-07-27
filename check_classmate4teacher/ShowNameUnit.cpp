//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowNameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TShowNameForm *ShowNameForm;
//---------------------------------------------------------------------------
__fastcall TShowNameForm::TShowNameForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TShowNameForm::FormCreate(TObject *Sender)
{
    LabelShow->AutoSize = true;
    LabelShow->Left = (Screen->Width-LabelShow->Width)/2;
    LabelShow->Top = 0; // (Screen->Height-LabelShow->Height)/2
    /*
        LONG    Style = ::GetWindowLong(this->Handle ,GWL_EXSTYLE);
        Style = Style|WS_EX_TOOLWINDOW;
        ::SetWindowLong(this->Handle ,GWL_EXSTYLE ,Style);    */
}
//---------------------------------------------------------------------------
void __fastcall TShowNameForm::LabelShowDblClick(TObject *Sender)
{
    TFontDialog *FontDialog = new TFontDialog(this);
    FontDialog->Font = LabelShow->Font;
    if(FontDialog->Execute())
    {
        LabelShow->Font = FontDialog->Font;
        ShowNameForm->LabelShow->Left = (Screen->Width-ShowNameForm->LabelShow->Width)/2;
    }
    delete  FontDialog;
}
//---------------------------------------------------------------------------

