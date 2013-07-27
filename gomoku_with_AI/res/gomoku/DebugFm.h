//---------------------------------------------------------------------------
#ifndef DebugFmH
#define DebugFmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TDebugForm : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *SG;
private:	// User declarations
public:		// User declarations
  __fastcall TDebugForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDebugForm *DebugForm;
//---------------------------------------------------------------------------
#endif
