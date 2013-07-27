//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <vcl\sysutils.hpp>
#include <vcl\windows.hpp>
#include <vcl\messages.hpp>
#include <vcl\sysutils.hpp>
#include <vcl\classes.hpp>
#include <vcl\graphics.hpp>
#include <vcl\controls.hpp>
#include <vcl\forms.hpp>
#include <vcl\dialogs.hpp>
#include <vcl\stdctrls.hpp>
#include <vcl\buttons.hpp>
#include <vcl\extctrls.hpp>
#include <vcl\menus.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <ScktComp.hpp>

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu;
	TMenuItem *HelpContentsItem;
	TMenuItem *HelpAboutItem;
	TStatusBar *StatusLine;
  TMenuItem *Game1;
  TMenuItem *New1;
  TMenuItem *Exit1;
  TImage *Image2;
  TLabel *Label1;
  TShape *Shape1;
  TClientSocket *ClientSocket1;
  TServerSocket *ServerSocket1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TMenuItem *Level1;
  TMenuItem *Level11;
  TMenuItem *Level21;
  TMenuItem *Level31;
  TMenuItem *Demo1;
  TMenuItem *Special1;
  TMenuItem *DebugForm1;
  TMenuItem *NewNetworkGame1;
  void __fastcall HelpContents(TObject *Sender);
	void __fastcall HelpAbout(TObject *Sender);
  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall Image2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall New1Click(TObject *Sender);
  void __fastcall ServerSocket1Listen(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall ServerSocket1ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ServerSocket1ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Lookup(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
  void __fastcall ServerSocket1ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
  void __fastcall Level21Click(TObject *Sender);
  void __fastcall Level11Click(TObject *Sender);
  void __fastcall Level31Click(TObject *Sender);
  void __fastcall Demo1Click(TObject *Sender);
  void __fastcall DebugForm1Click(TObject *Sender);
  void __fastcall NewNetworkGame1Click(TObject *Sender);
private:
  int ch5[26][26],chb[26][26];
  void __fastcall InitBoard();
  void __fastcall DrawChess(int x,int y,int r,int color);
  bool __fastcall Check5(int color);
  void __fastcall Computer();
  int __fastcall Value(int x,int y,int color);
  void __fastcall SaveBoard();
  void __fastcall RestoreBoard();
  bool __fastcall To5(int x,int y,int color);
//bbbbE,bbbEb,bbEbb   ÒÔºÚÆåÎªÀý
  int __fastcall To4(int x,int y,int color);
//Ebbbe,Ebbeb,Ebebb,Eebbb
//bEbbe,bEebb,bEbeb
//bbEbe,bbEeb
//bbbEe
  int __fastcall To3(int x,int y,int color);
//eEbbe,eEbebe,eEebbe
//ebEbe,ebEebe,
  int __fastcall To2(int x,int y,int color);
//ebEe,ebeEe
  struct best
    {
    int x,y,value;
    };
  best __fastcall Search(int color,int Depth);
  int dots;
  int Level;
  bool man;
  void __fastcall Debug();

     // private user declarations
public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
