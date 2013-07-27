//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPanel *Client;
    TLabel *Label1;
    TEdit *Edit1;
    TButton *Button1;
    TButton *Button3;
    TButton *Button4;
    TButton *Button2;
    TButton *Button5;
    TButton *Button7;
    TButton *Button8;
    TButton *Button9;
    TButton *Button10;
    TButton *Button11;
    TButton *Button12;
    TButton *Button13;
    TButton *Button14;
    TButton *Button15;
    TButton *Button16;
    TButton *Button17;
    TButton *Button18;
    TButton *Button19;
    TButton *Button20;
    TButton *Button6;
    TEdit *Edit2;
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TPanel *Panel5;
    TPanel *Panel9;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TPanel *Panel14;
    TPanel *Panel6;
    TPanel *Panel7;
    TPanel *Panel8;
    TPanel *Panel15;
    TPanel *Panel16;
    TPanel *Panel17;
    TPanel *Panel18;
    TPanel *Panel19;
    TPanel *Panel20;
    TPanel *Panel21;
    TPanel *Panel22;
    TPanel *Panel23;
    TPanel *Panel24;
    TPanel *Panel25;
    TPanel *Panel26;
    TPanel *Panel27;
    TPanel *Panel28;
    TPanel *Panel29;
    TPanel *Panel30;
    TPanel *Panel31;
    TPanel *Panel32;
    TPanel *Panel33;
    TPanel *Panel34;
    TPanel *Panel35;
    TPanel *Panel36;
    TPanel *Panel37;
    TPanel *Panel38;
    TPanel *Panel39;
    TPanel *Panel40;
    TPanel *Panel41;
    TPanel *Panel42;
    TPanel *Panel43;
    TPanel *Panel44;
    TPanel *Panel45;
    TPanel *Panel46;
    TEdit *Edit3;
    TEdit *Edit4;
    TTimer *Timer1;
    void __fastcall Button11Click(TObject *Sender);
    void __fastcall jisuan(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button15Click(TObject *Sender);
    void __fastcall Button19Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button13Click(TObject *Sender);
    void __fastcall Button17Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button12Click(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
    void __fastcall Button16Click(TObject *Sender);
    void __fastcall ce(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button10Click(TObject *Sender);
    //void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button14Click(TObject *Sender);
    void __fastcall Backspace(TObject *Sender);
    void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall Edit1Enter(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    void    TForm1::showA (int n);
    void    TForm1::showB (int n);
    void    TForm1::showC (int n);
    void    TForm1::showD (int n);
    void    TForm1::showE (int n);
    void    TForm1::showF (int n);
    void    TForm1::showMinutes (int m);
    void    TForm1::showHours (int h);
    void    TForm1::showSeconds (int h);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

