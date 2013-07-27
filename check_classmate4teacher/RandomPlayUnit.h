//---------------------------------------------------------------------------

#ifndef RandomPlayUnitH
#define RandomPlayUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPlayRandomForm : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer1;
    TLabel *Label1;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// User declarations
    TTimer  *DelayTime;
public:		// User declarations
    __fastcall TPlayRandomForm(TComponent* Owner);
    void __fastcall DelayTimeTimer(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TPlayRandomForm *PlayRandomForm;
//---------------------------------------------------------------------------
#endif
