//---------------------------------------------------------------------------

#ifndef FlyUnitH
#define FlyUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Trayicon.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include "ThreadUnit.h"

#define IMAGECOUNT      6  //ͼƬ����
//---------------------------------------------------------------------------
class TFlyForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image6;
    TImage *Image5;
    TImage *Image4;
    TImage *Image3;
    TImage *Image2;
    TImage *Image1;
    TActionList *ActionList1;
    TAction *StartFlyAngelAction;
    TAction *StopFlyAngelAction;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall StartFlyAngelActionExecute(TObject *Sender);
    void __fastcall StopFlyAngelActionExecute(TObject *Sender);
private:	// User declarations
    TFlyThread      *flythread;
//   TFollowThread   *followthread;
public:		// User declarations
    __fastcall TFlyForm(TComponent* Owner);
    void __fastcall ThreadDone(TObject *);
//��ֹ�ػ����ڱ���
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    TImage  *Images[IMAGECOUNT];
    bool    End;  //����������־

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFlyForm *FlyForm;
//---------------------------------------------------------------------------
#endif
