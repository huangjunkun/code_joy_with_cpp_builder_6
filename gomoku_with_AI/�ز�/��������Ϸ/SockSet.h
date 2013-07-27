//---------------------------------------------------------------------------
#ifndef SockSetH
#define SockSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSockForm : public TForm
{
__published:	// IDE-managed Components
  TEdit *Edit1;
  TLabel *Label1;
  TEdit *Edit2;
  TButton *Button1;
  TLabel *Label2;
  TLabel *Label3;
  TRadioGroup *RadioGroup1;
  TRadioButton *RB1;
  TRadioButton *RB2;
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall RB2Click(TObject *Sender);
  void __fastcall RB1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TSockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSockForm *SockForm;
//---------------------------------------------------------------------------
#endif
