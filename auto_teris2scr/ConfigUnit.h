//---------------------------------------------------------------------------

#ifndef ConfigUnitH
#define ConfigUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TConfigForm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBoxSet;
    TPageControl *PageControlSet;
    TTabSheet *TabSheetLevel;
    TLabel *LabelLevel;
    TComboBox *ComboBoxLevel;
    TCheckBox *CBPlayMusic;
    TTrackBar *tbMainVolume;
    TTrackBar *tbLeftVolume;
    TTrackBar *tbRightVolume;
    TTabSheet *TabSheetFace;
    TLabel *LabelAP;
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TBitBtn *BitBtnImage;
    TTrackBar *TrackBarAP;
    TCheckBox *cbRandColor;
    TBitBtn *BitBtnOK;
    TBitBtn *BitBtnNO;
private:	// User declarations
public:		// User declarations
    __fastcall TConfigForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
