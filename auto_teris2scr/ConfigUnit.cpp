//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConfigUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner)
    : TForm(Owner)
{
    //ConfigForm->Parent =
    ConfigForm->Parent = NULL;
    GroupBoxSet->Visible = true;
}
//---------------------------------------------------------------------------
