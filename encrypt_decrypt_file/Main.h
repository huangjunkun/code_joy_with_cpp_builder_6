//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <FileCtrl.hpp>

#include <stdlib.h>
#include <time.h>
#include <ComCtrls.hpp>
#include <vector>    //for vector
using namespace std;

#define     KEYLEN 64

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TPanel *Panel1;
    TPanel *Panel2;
    TComboBox *cbInFile;
    TBitBtn *btnInFile;
    TBitBtn *btnOutFile;
    TBitBtn *btnEncrypt;
    TBitBtn *btnhDecrypt;
    TDirectoryListBox *DirectoryListBox1;
    TBevel *Bevel1;
    TEdit *eOutFile;
    TStatusBar *StatusBar1;
    TProgressBar *ProgressBar1;
    TTimer *Timer1;
    TCheckBox *CheckBoxKey;
    TBitBtn *btnCancel;
    void __fastcall btnInFileClick(TObject *Sender);
    void __fastcall btnOutFileClick(TObject *Sender);
    void __fastcall btnEncryptClick(TObject *Sender);
    void __fastcall btnhDecryptClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall DirectoryListBox1Change(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall StatusBar1DblClick(TObject *Sender);
    void __fastcall CheckBoxKeyClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
    bool    NeedKey;
    TFileStream   *InStream;
    TFileStream   *OutStream;
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    bool    EncryptFile(String   Key ,bool NeedKey=true);
    bool    DncryptFile(String   Key="" ,bool NeedKey=true);
    void    DeleteFileStream();

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
