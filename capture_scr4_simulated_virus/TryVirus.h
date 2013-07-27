//---------------------------------------------------------------------------

#ifndef TryVirusH
#define TryVirusH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Registry.hpp>
//---------------------------------------------------------------------------
class TMyForm : public TForm
{
__published:	// IDE-managed Components
    TImage *ImageScreen;
    TTimer *Timer1;
    TImage *ImageHello;
    TLabeledEdit *LabeledEdit1;
    TTimer *Timer2;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall ImageScreenMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall LabeledEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMyForm(TComponent* Owner);
    void __fastcall WMKEYDOWN(TWMKey &Msg);
    void __fastcall WMKEYUP(TWMKey &Msg);
    void __fastcall MYHOTKEY(TWMHotKey &Msg) ;

    void    CaptureDesktop(HDC ImageHandle ) ;
   
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_KEYDOWN,TWMKey,WMKEYDOWN)
        MESSAGE_HANDLER(WM_KEYUP,TWMKey,WMKEYUP)
        MESSAGE_HANDLER(WM_HOTKEY ,TWMHotKey ,MYHOTKEY)
    END_MESSAGE_MAP(TForm) //
};
//---------------------------------------------------------------------------
extern PACKAGE TMyForm *MyForm;
//---------------------------------------------------------------------------
#endif
