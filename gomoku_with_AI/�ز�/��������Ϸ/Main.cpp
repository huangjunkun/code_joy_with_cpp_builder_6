//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <shellapi.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Main.h"
#include "SockSet.h"
#include "DebugFm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
const int black=1,white=2,empty=4;
//clr:color<1---black,2---white,4---empty>
//black^11=white,white^11=black
//有效棋盘的x,y范围[4,22]
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpContents(TObject *Sender)
{
	Application->HelpCommand(HELP_CONTENTS, 0);
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpAbout(TObject *Sender)
{
ShellAbout(Handle,"","\n五子棋(V1.2)\n版权所有(C) 1999-2002 NowCan. ",NULL);
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
InitBoard();
randomize();
Level=2;
man=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InitBoard()
{
Image2->Canvas->Pen->Color=clGray;//初始化棋盘背景
for(int i=0;i<401;i++)
  {
  Image2->Canvas->MoveTo(i,0);
  Image2->Canvas->LineTo(i,401);
  }
Image2->Canvas->Pen->Color=clBlack;// 初始化棋盘网格
for(int i=20;i<=380;i+=20)
  {
  Image2->Canvas->MoveTo(i,20);
  Image2->Canvas->LineTo(i,381);
  Image2->Canvas->MoveTo(20,i);
  Image2->Canvas->LineTo(380,i);
  }
for(int i=7;i<=19;i+=6)
  for(int j=7;j<=19;j+=6)
    DrawChess(i,j,3,black);
for(int i=0;i<=26;i++)
  for(int j=0;j<=26;j++)
    ch5[i][j]=empty;
for(int i=0;i<=5;i++)
  StatusLine->Panels->Items[i]->Text=" ";//界面下方的状态显示
Label1->Caption="";
Shape1->Left=Image2->Left+200-4;//???
Shape1->Top=Image2->Top+200-4;
}
//---------------------------------------------------------
void __fastcall TMainForm::DrawChess(int x,int y,int r,int color) //r为棋子大小
{
x=(x-3)*20;
y=(y-3)*20;
if(color==black)//  white    //棋盘中的黑点标志
{
  Image2->Canvas->Pen->Color=clBlack;//棋子边缘颜色
  Image2->Canvas->Brush->Color=clBlack;//棋子颜色、、、、
}
else
{
  Image2->Canvas->Pen->Color=clWhite;
  Image2->Canvas->Brush->Color=clWhite;
}
Image2->Canvas->Ellipse(x-r,y-r,x+r+1,y+r+1);
}
//---------------------------------------------------------
bool __fastcall TMainForm::Check5(int color)
{
int n;
for(int i=4;i<=22;i++)     //down
  for(int j=4;j<=18;j++)
    if(ch5[i][j]==color)
      {
      n=4;
      while(n&&ch5[i][j+n]==color)n--;
      if(!n)return true;
      }
for(int i=4;i<=18;i++)     //right-down
  for(int j=4;j<=18;j++)
    if(ch5[i][j]==color)
      {
      n=4;
      while(n&&ch5[i+n][j+n]==color)n--;
      if(!n)return true;
      }
for(int i=4;i<=18;i++)     //right
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==color)
      {
      n=4;
      while(n&&ch5[i+n][j]==color)n--;
      if(!n)return true;
      }
for(int i=8;i<=22;i++)     //left-down
  for(int j=4;j<=18;j++)
    if(ch5[i][j]==color)
      {
      n=4;
      while(n&&ch5[i-n][j+n]==color)n--;
      if(!n)return true;
      }
return false;
}
//---------------------------------------------------------

void __fastcall TMainForm::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int ix,iy;
ix=(X+10)/20+3; //取坐标位置？？？？
iy=(Y+10)/20+3;
if(!(Check5(black)|Check5(white))&&man)
{
  if(ch5[ix][iy]==empty)
    {
    DrawChess(ix,iy,7,black);
    ch5[ix][iy]=black;
    Shape1->Left=Image2->Left+(ix-3)*20-4;
    Shape1->Top=Image2->Top+(iy-3)*20-4;
    StatusLine->Panels->Items[5]->Text="";
    Update();   // 窗体更新、、、
    if(Check5(black))
      Label1->Caption="赢";
    else
      Computer();
    }
  else
    StatusLine->Panels->Items[5]->Text="Can't put chess here!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::New1Click(TObject *Sender)
{
InitBoard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveBoard()
{
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    chb[i][j]=ch5[i][j];
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RestoreBoard()
{
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    ch5[i][j]=chb[i][j];
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::To5(int x,int y,int color)
{
if(ch5[x][y]==empty)
  {
  if(ch5[x-1][y]&ch5[x-2][y]&ch5[x-3][y]&ch5[x-4][y]&color)
    return(true);
  if(ch5[x-1][y-1]&ch5[x-2][y-2]&ch5[x-3][y-3]&ch5[x-4][y-4]&color)
    return(true);
  if(ch5[x-1][y+1]&ch5[x-2][y+2]&ch5[x-3][y+3]&ch5[x-4][y+4]&color)
    return(true);
  if(ch5[x][y-1]&ch5[x][y-2]&ch5[x][y-3]&ch5[x][y-4]&color)
    return(true);
  if(ch5[x][y+1]&ch5[x][y+2]&ch5[x][y+3]&ch5[x][y+4]&color)
    return(true);
  if(ch5[x+1][y]&ch5[x+2][y]&ch5[x+3][y]&ch5[x+4][y]&color)
    return(true);
  if(ch5[x+1][y-1]&ch5[x+2][y-2]&ch5[x+3][y-3]&ch5[x+4][y-4]&color)
    return(true);
  if(ch5[x+1][y+1]&ch5[x+2][y+2]&ch5[x+3][y+3]&ch5[x+4][y+4]&color)
    return(true);

  if(ch5[x-1][y]&ch5[x-2][y]&ch5[x-3][y]&ch5[x+1][y]&color)
    return(true);
  if(ch5[x-1][y-1]&ch5[x-2][y-2]&ch5[x-3][y-3]&ch5[x+1][y+1]&color)
    return(true);
  if(ch5[x-1][y+1]&ch5[x-2][y+2]&ch5[x-3][y+3]&ch5[x+1][y-1]&color)
    return(true);
  if(ch5[x][y-1]&ch5[x][y-2]&ch5[x][y-3]&ch5[x][y+1]&color)
    return(true);
  if(ch5[x][y+1]&ch5[x][y+2]&ch5[x][y+3]&ch5[x][y-1]&color)
    return(true);
  if(ch5[x+1][y]&ch5[x+2][y]&ch5[x+3][y]&ch5[x-1][y]&color)
    return(true);
  if(ch5[x+1][y-1]&ch5[x+2][y-2]&ch5[x+3][y-3]&ch5[x-1][y+1]&color)
    return(true);
  if(ch5[x+1][y+1]&ch5[x+2][y+2]&ch5[x+3][y+3]&ch5[x-1][y-1]&color)
    return(true);

  if(ch5[x-1][y]&ch5[x-2][y]&ch5[x+2][y]&ch5[x+1][y]&color)
    return(true);
  if(ch5[x-1][y-1]&ch5[x-2][y-2]&ch5[x+2][y+2]&ch5[x+1][y+1]&color)
    return(true);
  if(ch5[x-1][y+1]&ch5[x-2][y+2]&ch5[x+2][y-2]&ch5[x+1][y-1]&color)
    return(true);
  if(ch5[x][y-1]&ch5[x][y-2]&ch5[x][y+2]&ch5[x][y+1]&color)
    return(true);
  if(ch5[x][y+1]&ch5[x][y+2]&ch5[x][y-2]&ch5[x][y-1]&color)
    return(true);
  if(ch5[x+1][y]&ch5[x+2][y]&ch5[x-2][y]&ch5[x-1][y]&color)
    return(true);
  if(ch5[x+1][y-1]&ch5[x+2][y-2]&ch5[x-2][y+2]&ch5[x-1][y+1]&color)
    return(true);
  if(ch5[x+1][y+1]&ch5[x+2][y+2]&ch5[x-2][y-2]&ch5[x-1][y-1]&color)
    return(true);

  return(false);
  }
return(false);
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::To4(int x,int y,int color)
{
int ret=0;
if(ch5[x][y]==empty)
  {
  //Ebbbe
  if((ch5[x+4][y]==empty)&&(ch5[x+1][y]&ch5[x+2][y]&ch5[x+3][y]&color))
    ret++;
  if((ch5[x+4][y+4]==empty)&&(ch5[x+1][y+1]&ch5[x+2][y+2]&ch5[x+3][y+3]&color))
    ret++;
  if((ch5[x+4][y-4]==empty)&&(ch5[x+1][y-1]&ch5[x+2][y-2]&ch5[x+3][y-3]&color))
    ret++;
  if((ch5[x][y+4]==empty)&&(ch5[x][y+1]&ch5[x][y+2]&ch5[x][y+3]&color))
    ret++;
  if((ch5[x][y-4]==empty)&&(ch5[x][y-1]&ch5[x][y-2]&ch5[x][y-3]&color))
    ret++;
  if((ch5[x-4][y]==empty)&&(ch5[x-1][y]&ch5[x-2][y]&ch5[x-3][y]&color))
    ret++;
  if((ch5[x-4][y+4]==empty)&&(ch5[x-1][y+1]&ch5[x-2][y+2]&ch5[x-3][y+3]&color))
    ret++;
  if((ch5[x-4][y-4]==empty)&&(ch5[x-1][y-1]&ch5[x-2][y-2]&ch5[x-3][y-3]&color))
    ret++;
  //Ebbeb
  if((ch5[x+3][y]==empty)&&(ch5[x+4][y]&ch5[x+2][y]&ch5[x+1][y]&color))
    ret++;
  if((ch5[x+3][y+3]==empty)&&(ch5[x+4][y+4]&ch5[x+2][y+2]&ch5[x+1][y+1]&color))
    ret++;
  if((ch5[x+3][y-3]==empty)&&(ch5[x+4][y-4]&ch5[x+2][y-2]&ch5[x+1][y-1]&color))
    ret++;
  if((ch5[x][y+3]==empty)&&(ch5[x][y+4]&ch5[x][y+2]&ch5[x][y+1]&color))
    ret++;
  if((ch5[x][y-3]==empty)&&(ch5[x][y-4]&ch5[x][y-2]&ch5[x][y-1]&color))
    ret++;
  if((ch5[x-3][y]==empty)&&(ch5[x-4][y]&ch5[x-2][y]&ch5[x-1][y]&color))
    ret++;
  if((ch5[x-3][y+3]==empty)&&(ch5[x-4][y+4]&ch5[x-2][y+2]&ch5[x-1][y+1]&color))
    ret++;
  if((ch5[x-3][y-3]==empty)&&(ch5[x-4][y-4]&ch5[x-2][y-2]&ch5[x-1][y-1]&color))
    ret++;
  //Ebebb
  if((ch5[x+2][y]==empty)&&(ch5[x+1][y]&ch5[x+3][y]&ch5[x+4][y]&color))
    ret++;
  if((ch5[x+2][y+2]==empty)&&(ch5[x+1][y+1]&ch5[x+3][y+3]&ch5[x+4][y+4]&color))
    ret++;
  if((ch5[x+2][y-2]==empty)&&(ch5[x+1][y-1]&ch5[x+3][y-3]&ch5[x+4][y-4]&color))
    ret++;
  if((ch5[x][y+2]==empty)&&(ch5[x][y+1]&ch5[x][y+3]&ch5[x][y+4]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y-1]&ch5[x][y-3]&ch5[x][y-4]&color))
    ret++;
  if((ch5[x-2][y]==empty)&&(ch5[x-1][y]&ch5[x-3][y]&ch5[x-4][y]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x-1][y+1]&ch5[x-3][y+3]&ch5[x-4][y+4]&color))
    ret++;
  if((ch5[x-2][y-2]==empty)&&(ch5[x-1][y-1]&ch5[x-3][y-3]&ch5[x-4][y-4]&color))
    ret++;
  //Eebbb
  if((ch5[x+1][y]==empty)&&(ch5[x+2][y]&ch5[x+3][y]&ch5[x+4][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x+2][y+2]&ch5[x+3][y+3]&ch5[x+4][y+4]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x+2][y-2]&ch5[x+3][y-3]&ch5[x+4][y-4]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y+2]&ch5[x][y+3]&ch5[x][y+4]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y-2]&ch5[x][y-3]&ch5[x][y-4]&color))
    ret++;
  if((ch5[x-1][y]==empty)&&(ch5[x-2][y]&ch5[x-3][y]&ch5[x-4][y]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x-2][y+2]&ch5[x-3][y+3]&ch5[x-4][y+4]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x-2][y-2]&ch5[x-3][y-3]&ch5[x-4][y-4]&color))
    ret++;
  //bEbbe
  if((ch5[x+3][y]==empty)&&(ch5[x+2][y]&ch5[x+1][y]&ch5[x-1][y]&color))
    ret++;
  if((ch5[x+3][y+3]==empty)&&(ch5[x+2][y+2]&ch5[x+1][y+1]&ch5[x-1][y-1]&color))
    ret++;
  if((ch5[x+3][y-3]==empty)&&(ch5[x+2][y-2]&ch5[x+1][y-1]&ch5[x-1][y+1]&color))
    ret++;
  if((ch5[x][y+3]==empty)&&(ch5[x][y+2]&ch5[x][y+1]&ch5[x][y-1]&color))
    ret++;
  if((ch5[x][y-3]==empty)&&(ch5[x][y-2]&ch5[x][y-1]&ch5[x][y+1]&color))
    ret++;
  if((ch5[x-3][y]==empty)&&(ch5[x-2][y]&ch5[x-1][y]&ch5[x+1][y]&color))
    ret++;
  if((ch5[x-3][y+3]==empty)&&(ch5[x-2][y+2]&ch5[x-1][y+1]&ch5[x+1][y-1]&color))
    ret++;
  if((ch5[x-3][y-3]==empty)&&(ch5[x-2][y-2]&ch5[x-1][y-1]&ch5[x+1][y+1]&color))
    ret++;
  //bEebb
  if((ch5[x+1][y]==empty)&&(ch5[x-1][y]&ch5[x+2][y]&ch5[x+3][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-1][y-1]&ch5[x+2][y+2]&ch5[x+3][y+3]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-1][y+1]&ch5[x+2][y-2]&ch5[x+3][y-3]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-1]&ch5[x][y+2]&ch5[x][y+3]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+1]&ch5[x][y-2]&ch5[x][y-3]&color))
    ret++;
  if((ch5[x-1][y]==empty)&&(ch5[x+1][y]&ch5[x-2][y]&ch5[x-3][y]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+1][y-1]&ch5[x-2][y+2]&ch5[x-3][y+3]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+1][y+1]&ch5[x-2][y-2]&ch5[x-3][y-3]&color))
    ret++;
  //bEbeb
  if((ch5[x+2][y]==empty)&&(ch5[x-1][y]&ch5[x+1][y]&ch5[x+3][y]&color))
    ret++;
  if((ch5[x+2][y+2]==empty)&&(ch5[x-1][y-1]&ch5[x+1][y+1]&ch5[x+3][y+3]&color))
    ret++;
  if((ch5[x+2][y-2]==empty)&&(ch5[x-1][y+1]&ch5[x+1][y-1]&ch5[x+3][y-3]&color))
    ret++;
  if((ch5[x][y+2]==empty)&&(ch5[x][y-1]&ch5[x][y+1]&ch5[x][y+3]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y+1]&ch5[x][y-1]&ch5[x][y-3]&color))
    ret++;
  if((ch5[x-2][y]==empty)&&(ch5[x+1][y]&ch5[x-1][y]&ch5[x-3][y]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x+1][y-1]&ch5[x-1][y+1]&ch5[x-3][y+3]&color))
    ret++;
  if((ch5[x-2][y-2]==empty)&&(ch5[x+1][y+1]&ch5[x-1][y-1]&ch5[x-3][y-3]&color))
    ret++;
  //bbEbe
  if((ch5[x+2][y]==empty)&&(ch5[x-2][y]&ch5[x-1][y]&ch5[x+1][y]&color))
    ret++;
  if((ch5[x+2][y+2]==empty)&&(ch5[x-2][y-2]&ch5[x-1][y-1]&ch5[x+1][y+1]&color))
    ret++;
  if((ch5[x+2][y-2]==empty)&&(ch5[x-2][y+2]&ch5[x-1][y+1]&ch5[x+1][y-1]&color))
    ret++;
  if((ch5[x][y+2]==empty)&&(ch5[x][y-2]&ch5[x][y-1]&ch5[x][y+1]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y+2]&ch5[x][y+1]&ch5[x][y-1]&color))
    ret++;
  if((ch5[x-2][y]==empty)&&(ch5[x+2][y]&ch5[x+1][y]&ch5[x-1][y]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x+2][y-2]&ch5[x+1][y-1]&ch5[x-1][y+1]&color))
    ret++;
  if((ch5[x-2][y-2]==empty)&&(ch5[x+2][y+2]&ch5[x+1][y+1]&ch5[x-1][y-1]&color))
    ret++;
  //bbEeb
  if((ch5[x+1][y]==empty)&&(ch5[x-2][y]&ch5[x-1][y]&ch5[x+2][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-2][y-2]&ch5[x-1][y-1]&ch5[x+2][y+2]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-2][y+2]&ch5[x-1][y+1]&ch5[x+2][y-2]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-2]&ch5[x][y-1]&ch5[x][y+2]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+2]&ch5[x][y+1]&ch5[x][y-2]&color))
    ret++;
  if((ch5[x-1][y]==empty)&&(ch5[x+2][y]&ch5[x+1][y]&ch5[x-2][y]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+2][y-2]&ch5[x+1][y-1]&ch5[x-2][y+2]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+2][y+2]&ch5[x+1][y+1]&ch5[x-2][y-2]&color))
    ret++;
  //bbbEe
  if((ch5[x+1][y]==empty)&&(ch5[x-3][y]&ch5[x-2][y]&ch5[x-1][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-3][y-3]&ch5[x-2][y-2]&ch5[x-1][y-1]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-3][y+3]&ch5[x-2][y+2]&ch5[x-1][y+1]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-3]&ch5[x][y-2]&ch5[x][y-1]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+3]&ch5[x][y+2]&ch5[x][y+1]&color))
    ret++;
  if((ch5[x-1][y]==empty)&&(ch5[x+3][y]&ch5[x+2][y]&ch5[x+1][y]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+3][y-3]&ch5[x+2][y-2]&ch5[x+1][y-1]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+3][y+3]&ch5[x+2][y+2]&ch5[x+1][y+1]&color))
    ret++;
  }
return(ret);
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::To3(int x,int y,int color)
{
int ret=0;
if(ch5[x][y]==empty)
  {
  //eEbbe
  if((ch5[x-1][y]==empty)&&(ch5[x+3][y]==empty)&&(ch5[x+1][y]&ch5[x+2][y]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+3][y+3]==empty)&&(ch5[x+1][y+1]&ch5[x+2][y+2]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+3][y-3]==empty)&&(ch5[x+1][y-1]&ch5[x+2][y-2]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+3]==empty)&&(ch5[x][y+1]&ch5[x][y+2]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-3]==empty)&&(ch5[x][y-1]&ch5[x][y-2]&color))
    ret++;
  if((ch5[x+1][y]==empty)&&(ch5[x-3][y]==empty)&&(ch5[x-1][y]&ch5[x-2][y]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-3][y+3]==empty)&&(ch5[x-1][y+1]&ch5[x-2][y+2]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-3][y-3]==empty)&&(ch5[x-1][y-1]&ch5[x-2][y-2]&color))
    ret++;
  //ebEbe
  if((ch5[x-2][y-2]==empty)&&(ch5[x+2][y+2]==empty)&&(ch5[x-1][y-1]&ch5[x+1][y+1]&color))
    ret++;
  if((ch5[x-2][y]==empty)&&(ch5[x+2][y]==empty)&&(ch5[x-1][y]&ch5[x+1][y]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x+2][y-2]==empty)&&(ch5[x-1][y+1]&ch5[x+1][y-1]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y+2]==empty)&&(ch5[x][y-1]&ch5[x][y+1]&color))
    ret++;
  //eEbebe
  if((ch5[x-1][y]==empty)&&(ch5[x+2][y]==empty)&&(ch5[x+4][y]==empty)&&(ch5[x+1][y]&ch5[x+3][y]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+2][y+2]==empty)&&(ch5[x+4][y+4]==empty)&&(ch5[x+1][y+1]&ch5[x+3][y+3]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+2][y-2]==empty)&&(ch5[x+4][y-4]==empty)&&(ch5[x+1][y-1]&ch5[x+3][y-3]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+2]==empty)&&(ch5[x][y+4]==empty)&&(ch5[x][y+1]&ch5[x][y+3]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-2]==empty)&&(ch5[x][y-4]==empty)&&(ch5[x][y-1]&ch5[x][y-3]&color))
    ret++;
  if((ch5[x+1][y]==empty)&&(ch5[x-2][y]==empty)&&(ch5[x-4][y]==empty)&&(ch5[x-1][y]&ch5[x-3][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-2][y-2]==empty)&&(ch5[x-4][y-4]==empty)&&(ch5[x-1][y-1]&ch5[x-3][y-3]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-2][y+2]==empty)&&(ch5[x-4][y+4]==empty)&&(ch5[x-1][y+1]&ch5[x-3][y+3]&color))
    ret++;
  //eEebbe
  if((ch5[x-1][y]==empty)&&(ch5[x+1][y]==empty)&&(ch5[x+4][y]==empty)&&(ch5[x+2][y]&ch5[x+3][y]&color))
    ret++;
  if((ch5[x-1][y+1]==empty)&&(ch5[x+1][y-1]==empty)&&(ch5[x+4][y-4]==empty)&&(ch5[x+2][y-2]&ch5[x+3][y-3]&color))
    ret++;
  if((ch5[x-1][y-1]==empty)&&(ch5[x+1][y+1]==empty)&&(ch5[x+4][y+4]==empty)&&(ch5[x+2][y+2]&ch5[x+3][y+3]&color))
    ret++;
  if((ch5[x][y+1]==empty)&&(ch5[x][y-1]==empty)&&(ch5[x][y-4]==empty)&&(ch5[x][y-2]&ch5[x][y-3]&color))
    ret++;
  if((ch5[x][y-1]==empty)&&(ch5[x][y+1]==empty)&&(ch5[x][y+4]==empty)&&(ch5[x][y+2]&ch5[x][y+3]&color))
    ret++;
  if((ch5[x+1][y]==empty)&&(ch5[x-1][y]==empty)&&(ch5[x-4][y]==empty)&&(ch5[x-2][y]&ch5[x-3][y]&color))
    ret++;
  if((ch5[x+1][y+1]==empty)&&(ch5[x-1][y-1]==empty)&&(ch5[x-4][y-4]==empty)&&(ch5[x-2][y-2]&ch5[x-3][y-3]&color))
    ret++;
  if((ch5[x+1][y-1]==empty)&&(ch5[x-1][y+1]==empty)&&(ch5[x-4][y+4]==empty)&&(ch5[x-2][y+2]&ch5[x-3][y+3]&color))
    ret++;
  //ebEebe
  if((ch5[x-2][y]==empty)&&(ch5[x+1][y]==empty)&&(ch5[x+3][y]==empty)&&(ch5[x-1][y]&ch5[x+2][y]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x+1][y-1]==empty)&&(ch5[x+3][y-3]==empty)&&(ch5[x-1][y+1]&ch5[x+2][y-2]&color))
    ret++;
  if((ch5[x-2][y-2]==empty)&&(ch5[x+1][y+1]==empty)&&(ch5[x+3][y+3]==empty)&&(ch5[x-1][y-1]&ch5[x+2][y+2]&color))
    ret++;
  if((ch5[x][y+2]==empty)&&(ch5[x][y-1]==empty)&&(ch5[x][y-3]==empty)&&(ch5[x][y+1]&ch5[x][y-2]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y+1]==empty)&&(ch5[x][y+3]==empty)&&(ch5[x][y-1]&ch5[x][y+2]&color))
    ret++;
  if((ch5[x+2][y]==empty)&&(ch5[x-1][y]==empty)&&(ch5[x-3][y]==empty)&&(ch5[x+1][y]&ch5[x-2][y]&color))
    ret++;
  if((ch5[x+2][y+2]==empty)&&(ch5[x-1][y-1]==empty)&&(ch5[x-3][y-3]==empty)&&(ch5[x+1][y+1]&ch5[x-2][y-2]&color))
    ret++;
  if((ch5[x+2][y-2]==empty)&&(ch5[x-1][y+1]==empty)&&(ch5[x-3][y+3]==empty)&&(ch5[x+1][y-1]&ch5[x-2][y+2]&color))
    ret++;
  }
return(ret);
}
//--------------------------------------------------------------------------------
int __fastcall TMainForm::To2(int x,int y,int color)
{
int ret=0;
if(ch5[x][y]==empty)
  {
  //ebEe
  if((ch5[x-2][y]==empty)&&(ch5[x+1][y]==empty)&&(ch5[x-1][y]&color))
    ret++;
  if((ch5[x-2][y-2]==empty)&&(ch5[x+1][y+1]==empty)&&(ch5[x-1][y-1]&color))
    ret++;
  if((ch5[x-2][y+2]==empty)&&(ch5[x+1][y-1]==empty)&&(ch5[x-1][y+1]&color))
    ret++;
  if((ch5[x][y+2]==empty)&&(ch5[x][y-1]==empty)&&(ch5[x][y+1]&color))
    ret++;
  if((ch5[x][y-2]==empty)&&(ch5[x][y+1]==empty)&&(ch5[x][y-1]&color))
    ret++;
  if((ch5[x+2][y]==empty)&&(ch5[x-1][y]==empty)&&(ch5[x+1][y]&color))
    ret++;
  if((ch5[x+2][y+2]==empty)&&(ch5[x-1][y-1]==empty)&&(ch5[x+1][y+1]&color))
    ret++;
  if((ch5[x+2][y-2]==empty)&&(ch5[x-1][y+1]==empty)&&(ch5[x+1][y-1]&color))
    ret++;
  //ebeEe
  if((ch5[x-3][y]==empty)&&(ch5[x-1][y]==empty)&&(ch5[x+1][y]==empty)&&(ch5[x-2][y]&color))
    ret++;
  if((ch5[x-3][y+3]==empty)&&(ch5[x-1][y+1]==empty)&&(ch5[x+1][y-1]==empty)&&(ch5[x-2][y+2]&color))
    ret++;
  if((ch5[x-3][y-3]==empty)&&(ch5[x-1][y-1]==empty)&&(ch5[x+1][y+1]==empty)&&(ch5[x-2][y-2]&color))
    ret++;
  if((ch5[x][y+3]==empty)&&(ch5[x][y+1]==empty)&&(ch5[x][y-1]==empty)&&(ch5[x][y+2]&color))
    ret++;
  if((ch5[x][y-3]==empty)&&(ch5[x][y-1]==empty)&&(ch5[x][y+1]==empty)&&(ch5[x][y-2]&color))
    ret++;
  if((ch5[x+3][y]==empty)&&(ch5[x+1][y]==empty)&&(ch5[x-1][y]==empty)&&(ch5[x+2][y]&color))
    ret++;
  if((ch5[x+3][y+3]==empty)&&(ch5[x+1][y+1]==empty)&&(ch5[x-1][y-1]==empty)&&(ch5[x+2][y+2]&color))
    ret++;
  if((ch5[x+3][y-3]==empty)&&(ch5[x+1][y-1]==empty)&&(ch5[x-1][y+1]==empty)&&(ch5[x+2][y-2]&color))
    ret++;
  }
return(ret);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocket1Listen(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label4->Caption="Port "+IntToStr(ServerSocket1->Port)+" ... Listen";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
int width=ClientWidth,h=ClientHeight;
for(int i=h;i>=0;i--)
  {
  Canvas->Pen->Color=RGB(i*255/h/10,i*255/h/20,i*255/h);
  Canvas->MoveTo(0,i);
  Canvas->LineTo(width,i);
  }
  
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label4->Caption="Connected.";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label4->Caption="Disconnected.";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ClientSocket1Lookup(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label5->Caption="Searching...";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Connecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label5->Caption="Connecting...";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label5->Caption="Connected";
SockForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Disconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label5->Caption="Disconnected";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
ErrorCode=0;
Label5->Caption="";
Application->MessageBox("遇到错误！请检查服务器地址和端口！",
  "An Error Occurs!",0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
ErrorCode=0;
Label4->Caption="ERROR!!!";
}
void __fastcall TMainForm::Debug()
{
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    DebugForm->SG->Cells[i-4][j-4]=ch5[i][j];
DebugForm->Update();
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::Value(int x,int y,int color)
{
int ret=0;
//if(To5(x,y,color))ret+=10000000;
//if(To4(x,y,color)!=0&&To3(x,y,color)!=0)ret+=1000000;
//if(To4(x,y,color)>=2)ret+=1000000;
if(To3(x,y,color)>=2)ret+=200000+rand()%10000;
if(To4(x,y,color)==1)ret+=100000+rand()%10000;
if(To3(x,y,color)==1)ret+=90000+rand()%1000;
ret+=500*To2(x,y,color)+rand()%100;
return(ret);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Computer()
{
dots=0;
best bestpos;
man=false;
bestpos=Search(white,Level);
DrawChess(bestpos.x,bestpos.y,7,white);
ch5[bestpos.x][bestpos.y]=white;
Shape1->Left=Image2->Left+(bestpos.x-3)*20-4;
Shape1->Top=Image2->Top+(bestpos.y-3)*20-4;
man=true;
if(Check5(white))
  Label1->Caption="输";
Debug();
}
//--------------------------------------------------------
TMainForm::best __fastcall TMainForm::Search(int color,int Depth)
{
int v=0;
best ret;
ret.x=0;
ret.y=0;
ret.value=0;
dots++;
if(Depth>0)
{
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To5(i,j,color))
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To5(i,j,3-color))
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To4(i,j,color)>1)
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To4(i,j,3-color)>1)
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To4(i,j,color)!=0&&To3(i,j,color)!=0)
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }
for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    if(ch5[i][j]==empty&&To4(i,j,3-color)!=0&&To3(i,j,3-color)!=0)
      {
      ret.x=i;
      ret.y=j;
      ret.value=99999999;
      return(ret);
      }

for(int i=4;i<=22;i++)
  for(int j=4;j<=22;j++)
    {
    if(Depth==Level)
      {
      StatusLine->Panels->Items[3]->Text=((i-4)*19+j-4)*100/361;
      StatusLine->Panels->Items[4]->Text=dots;
      Application->ProcessMessages();
      }
    if(ch5[i][j]==empty)
      {
//      SaveBoard();
      v=Value(i,j,color)+200;
      if(v>ret.value)
        {
        ret.x=i;
        ret.y=j;
        ret.value=v;
        }
      v=Value(i,j,3-color);
      if(v>ret.value)
        {
        ret.x=i;
        ret.y=j;
        ret.value=v;
        }
      ch5[i][j]=color;
//      Debug();
      if(v>400)
        {
        v+=Search(3-color,Depth-1).value;
        if(v>ret.value)
          {
          ret.x=i;
          ret.y=j;
          ret.value=v;
          }
        }
      ch5[i][j]=empty;
//      RestoreBoard();
      }
    }
}
return(ret);
}

void __fastcall TMainForm::Level21Click(TObject *Sender)
{
Level21->Checked=true;
Level=3;  
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Level11Click(TObject *Sender)
{
Level11->Checked=true;
Level=2;  
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Level31Click(TObject *Sender)
{
Level31->Checked=true;
Level=4;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Demo1Click(TObject *Sender)
{
int finish=0;
dots=0;
best bestpos;
DrawChess(14,14,7,black);
ch5[14][14]=black;
while(!Check5(white)&&!Check5(black)&&finish<361)
{
    bestpos=Search(white,Level);
    finish++;
    DrawChess(bestpos.x,bestpos.y,7,white);
    ch5[bestpos.x][bestpos.y]=white;
    Shape1->Left=Image2->Left+(bestpos.x-3)*20-4;
    Shape1->Top=Image2->Top+(bestpos.y-3)*20-4;
    if(Check5(white))
      Label1->Caption="白棋赢";
    Update();
    Debug();
    bestpos=Search(black,Level);
    finish++;
    DrawChess(bestpos.x,bestpos.y,7,black);
    ch5[bestpos.x][bestpos.y]=black;
    Shape1->Left=Image2->Left+(bestpos.x-3)*20-4;
    Shape1->Top=Image2->Top+(bestpos.y-3)*20-4;
    if(Check5(black))
      Label1->Caption="黑棋赢";
    Update();
    Debug();
    Application->ProcessMessages();
    }
    if(finish>=361)
      Label1->Caption="和";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DebugForm1Click(TObject *Sender)
{
DebugForm1->Checked=!DebugForm1->Checked;
if(DebugForm1->Checked)
  DebugForm->Show();
else
  DebugForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewNetworkGame1Click(TObject *Sender)
{
SockForm->Show();
InitBoard(); 
}
//---------------------------------------------------------------------------



