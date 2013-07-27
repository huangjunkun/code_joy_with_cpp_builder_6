//---------------------------------------------------------------------------

#ifndef setclockH
#define setclockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSetClock : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TColorDialog *ColorDialog1;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TDateTimePicker *DateTimePicker1;
    TPanel *Panel1;
    TRadioGroup *RadioGroup1;
    TBitBtn *BitBtnCancel;
    TBitBtn *BitBtnApp;
    TBitBtn *BitBtnOK;
    TRadioGroup *RadioGroup2;
    TBitBtn *BitBtnSetSize;
    TLabeledEdit *LabeledEdit1;
    TCheckBox *CBTransparent;
    TBitBtn *BitBtnDefault;
    TCheckBox *CBFormStyle;
    TCheckBox *CBTrayIcon;
    TGroupBox *GroupBox3;
    TTrackBar *TrackBar1;
    void __fastcall RadioGroup1Click(TObject *Sender);
    void __fastcall BitBtnCancelClick(TObject *Sender);
    void __fastcall BitBtnOKClick(TObject *Sender);
    void __fastcall BitBtnSetSizeClick(TObject *Sender);
    void __fastcall LabeledEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall BitBtnAppClick(TObject *Sender);
    void __fastcall LabeledEdit1Exit(TObject *Sender);
    void __fastcall BitBtnDefaultClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall CBTrayIconClick(TObject *Sender);
    void __fastcall CBFormStyleClick(TObject *Sender);
    void __fastcall CBTransparentClick(TObject *Sender);
private:	// User declarations
    int        s_width ,m_width ,h_width ,fontsize; //秒，分，时针的宽度
    TColor     s_color ,m_color ,h_color ,c_color ,f_color;
public:		// User declarations
    __fastcall TSetClock(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetClock *SetClock;
//---------------------------------------------------------------------------
#endif
