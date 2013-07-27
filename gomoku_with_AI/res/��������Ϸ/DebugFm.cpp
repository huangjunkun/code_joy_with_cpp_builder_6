//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DebugFm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDebugForm *DebugForm;
//---------------------------------------------------------------------------
__fastcall TDebugForm::TDebugForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
