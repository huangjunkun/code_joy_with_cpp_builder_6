//---------------------------------------------------------------------------

#ifndef ShowNameUnitH
#define ShowNameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TShowNameForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *LabelShow;
    TMainMenu *MainMenu1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall LabelShowDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TShowNameForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TShowNameForm *ShowNameForm;
//---------------------------------------------------------------------------
#endif
