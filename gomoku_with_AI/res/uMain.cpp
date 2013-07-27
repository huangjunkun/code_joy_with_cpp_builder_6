//---------------------------------------------------------------------------
// 描述：SK 五子棋 1.0
// 作者：seeker
// 声明：本代码仅供学习，任何人可以修改复制，但必须注明原作者信息！
// 注意：版权所属：seeker
// 日期：2006-12-31
// 更新：2007-12-28
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <MMSystem.h>
#include "uMain.h"
#include "ulogin.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 // 初始化种子
  srand((unsigned)time(NULL)) ;

  Memo1->DoubleBuffered=true;
  this->DoubleBuffered=true;
  // 读入图片资源
  QIPANBMP=new Graphics::TBitmap();
  BAIQI=new Graphics::TBitmap();
  HEIQI=new Graphics::TBitmap();
  // 设置透明色
  BAIQI->Transparent=true;
  BAIQI->TransparentColor=clFuchsia;
  HEIQI->Transparent=true;
  HEIQI->TransparentColor=clFuchsia;
  Image1->Picture->Bitmap->Transparent=true;
  Image1->Picture->Bitmap->TransparentColor=clFuchsia;
  // 从资源读取位图
  Image1->Picture->Bitmap->LoadFromResourceName((int)HInstance,"beijing");
  QIPANBMP->LoadFromResourceName((int)HInstance,"qipan");
  BAIQI->LoadFromResourceName((int)HInstance,"baiqi");
  HEIQI->LoadFromResourceName((int)HInstance,"heiqi");
 // 初始化一些变量
  offsetx=18; offsety=86; // 图片位移
  begin=false;
  gamenum=0;  ying=0;   ping=0;  shu=0; //游戏统计量
  snd=true;bgsnd=true; tmpsnd=true;
 // 准心
 Shape1->Left=7*35+17+offsetx;
 Shape1->Top=7*35+17+offsety;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateParams(TCreateParams & Params)
{
    TForm::CreateParams(Params);
    Params.Caption="SK五子棋【作者：seeker】";
    strcpy(Params.WinClassName, "http://myseeker.bokee.com");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
 //Graphics::TBitmap的Hanle只是一个HBITMAP，并不是HDC。
 //只有Canvas的Handle才是HDC
 // 画背景图
 BitBlt(this->Canvas->Handle,offsetx,offsety,532,532,QIPANBMP->Canvas->Handle,0,0,SRCCOPY);
 // 画所有已下的棋子
 for(int i=0;i<15;i++)
 {
   for(int j=0;j<15;j++)
   {
     if(ch5.CH5[i][j]==2) //白棋
     {
       //i*35+3+offsetx --> i*35+20-17+offsetx,
       this->Canvas->Draw(i*35+3+offsetx,j*35+3+offsety,BAIQI);
     }
     else if(ch5.CH5[i][j]==1)//黑
     {
       this->Canvas->Draw(i*35+3+offsetx,j*35+3+offsety,HEIQI);
     }
   }//for_j
 }//for_i
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{ // 新游戏
  ch5.Reset(); //重置
  this->Invalidate();// 重画
  SpeedButton7->Enabled=true;
  begin=true;
  usercolor=1;
  gamenum++;
  Label5->Caption="游戏场数："+String(gamenum);
  Label6->Caption="赢："+String(ying)+"   平："
   +String(ping)+"   输："
   +String(shu)+" 废："
   +String(gamenum-ping-ying-shu);
  Memo1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 // 悔棋
 if(!ch5.Retract())
 {
   SpeedButton3->Enabled=false;
   MessageBox(Handle,"汗！没棋可以给你悔，还悔什么棋啊？！","SK五子棋",MB_OK);
   return;
 }
 if(snd)
 //  sndPlaySound(undo,SND_MEMORY|SND_ASYNC);
   PlaySound((ps+"undo.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
 Memo1->Lines->Delete(Memo1->Lines->Count-1);
 Memo1->Lines->Delete(Memo1->Lines->Count-1);
 this->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
 //最小化
 SendMessage(Application->Handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

   if(Button!=mbLeft) return;
   // 限制鼠标有效范围
   if(X>550||X<20||Y>610||Y<90)
   {
     //移动窗体
     ReleaseCapture();
     Perform(WM_NCLBUTTONDOWN,HTCAPTION, 0);
     return;
   }
   if(!begin)
   {
     MessageBox(Handle,"点击右上角的【新游戏】开始人机对弈。\n\n【让先】可以让机器先走。","SK五子棋",MB_OK);
     return;
   }
   int px,py,res;
   Label1->Caption=String(X)+","+String(Y);
   int x=(X-20-offsetx);//坐标转化
   int y=(Y-20-offsety+3);
     // 判断在哪个棋格
   Qx=(x+17)/35;
   Qy=(y+17)/35;
   px=Qx;
   py=Qy;

   if(!( (x+10)>Qx*35 && (y+10)>Qy*35 )) //判断落子坐标是否合法
     return ;

    if(snd) //sndPlaySound(put,SND_MEMORY|SND_ASYNC);
      PlaySound((ps+"put.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);

   SpeedButton7->Enabled=false;
   res=ch5.PutChess( Qx, Qy, px, py);//eeeee
   this->Invalidate();
   Shape1->Left=px*35+17+offsetx;
   Shape1->Top=py*35+17+offsety;
   Label2->Caption="用户最后落子：【"+String(Qx)+"，"+String(Qy)+"】 步数："+String(ch5.StepLen);

   if(!(px==Qx&&py==Qy))
   {
     Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]：( "+String(Qx)+","+String(Qy)+","+String(usercolor)+" )");
     Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]：( "+String(px)+","+String(py)+","+String(3-usercolor)+" )");;
   }
   switch(res)
   {
    case -2:
    break;
    case -1:
         SpeedButton3->Enabled=true;  // 可以悔棋了
    break;
    case 0:
      ping++;
      Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(shu)+" 废："
      +String(gamenum-ping-ying-shu);
      SpeedButton3->Enabled=false; //悔棋按钮
      MessageBox(Handle,"平局！","SK五子棋",MB_OK);
    break;
    case 1:
    case 2:
      if(usercolor==res)
      {
        ying++;
       Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(gamenum-ping-ying)+" 废："
      +String(gamenum-ping-ying-(gamenum-ping-ying));
        SpeedButton3->Enabled=false; //悔棋按钮
       if(snd) //sndPlaySound(win,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"win.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
        MessageBox(Handle,"恭喜你！你赢了！","SK五子棋",MB_OK);
      }
      if(usercolor==3-res)
      {
       shu++;
       Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(shu)+" 废："
      +String(gamenum-ping-ying-shu);
       SpeedButton3->Enabled=false; //悔棋按钮
      if(snd) // sndPlaySound(lose,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"lose.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"很可惜，你输了！","SK五子棋",MB_OK);
      }
    break;
    case 3:
      shu++;
      Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(shu)+" 废："
      +String(gamenum-ping-ying-shu);
      SpeedButton3->Enabled=false; //悔棋按钮
     if(snd)// sndPlaySound(lose,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"lose.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"注意！你禁手了！重新来过。","SK五子棋",MB_OK);
    break;
    case 4:
      ying++;
      SpeedButton3->Enabled=false; //悔棋按钮
      Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(shu)+" 废："
      +String(gamenum-ping-ying-shu);
       if(snd) //sndPlaySound(win,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"win.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"我服了你！我认输！再来。","SK五子棋",MB_OK);
    break;
   };

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
  // 让先
  SpeedButton7->Enabled=false;
  usercolor=2;
  ch5.SetFirst(3,false);
  int qx,qy,px,py;
  qx=rand()%15;
  Sleep(10);
  qy=(rand()+1)%15;
  if(snd) //sndPlaySound(put,SND_MEMORY|SND_ASYNC);
   PlaySound((ps+"put.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
  ch5.PutChess( qx, qy, px, py);
  this->Invalidate();
  Shape1->Left=px*35+17+offsetx;
  Shape1->Top=py*35+17+offsety;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  static int ttt=0;
  if(ttt++>1)
  {
    if(tmpsnd)
    {
      // sndPlaySound(main,SND_MEMORY|SND_LOOP|SND_ASYNC);
       PlaySound((ps+"main.wav").c_str(), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
       tmpsnd=false;
    }
    ttt=0;
  }
  LabelTime->Caption=FormatDateTime("'当前时间：'YYYY-MM-DD HH:MM:SS",Now());
  SetProcessWorkingSetSize(GetCurrentProcess(),0xFFFFFFFF,0xFFFFFFFF);
}
//---------------------------------------------------------------------------
// 保存文件
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
  FILE *fp;
  String s="";
  if(SaveDialog1->Execute())
  {
    s=SaveDialog1->FileName;
    if(!(UpperCase(ExtractFileExt(s))==".FQP"))
      s+=".FQP";
    fp=fopen(s.c_str(),"w");
    if(!fp)
    {
      MessageBox(Handle,"无法创建文件！磁盘写保护或空间不足！","SK五子棋",MB_OK);
      return;
    }
    // 写入文件.
    int tx,ty,tc;
    fprintf(fp,"%d ",usercolor); // 2 or 1
    
    for(int i=0;i<ch5.StepLen;i++)
    {
      ch5.GetStepOfIndex(i,tx,ty,tc);
      fprintf(fp,"%d %d %d ",tx,ty,tc);
    }
    fclose(fp);
  }
}
//---------------------------------------------------------------------------
//调试信息！
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
  FILE *fp;
  //保存
  String s="";
  if(OpenDialog1->Execute())
  {
    s=OpenDialog1->FileName;
    fp=fopen(s.c_str(),"r");
    if(!fp)
    {
      MessageBox(Handle,"无法读取文件！文件不可访问！","SK五子棋",MB_OK);
      return;
    }
    // 从文件读入
    ch5.Reset();//先复位。
    usercolor=1; // 人机对战---轮到人下棋
    Memo1->Text="";
    Memo1->Lines->Add("读取文件：");
    Memo1->Lines->Add(s);
    Memo1->Lines->Add("【数据】");
    int i=0,flag=3,tcc=-1;

    fscanf(fp,"%d",&tcc);
    if(tcc==2) //说明该文件是原来机器先下的！
    {
       SpeedButton7->Enabled=false;
       usercolor=2;
       ch5.SetFirst(2,true);
       flag=1;
    }

    for(;;)
    {
      int tx,ty,tc;
      if(fscanf(fp,"%d%d%d",&tx,&ty,&tc)!=EOF)
      {
        ch5.SetStepOfIndex(i,tx,ty,tc); //设置棋盘每个步骤
        ch5.CH5[tx][ty]=tc;
        ch5.StepLen++;
        i++;
        // 信息显示
        // 机器先下
        if(flag==1)
        {
          Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]：( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=2;
        }
        else if(flag==2)
        {
          Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]：( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=1;
        }
        // 人先下
        else if(flag==3)
        {
          Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]：( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=4;
        }
        else if(flag==4)
        {
          Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]：( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=3;
        }
      }
      else break;
    }//for
    fclose(fp);
    this->Invalidate();
    Label2->Caption="步数："+String(ch5.StepLen);

    //判断是否读入输赢的文件
    if(ch5.StepLen>=225)
    {
      begin=false;
      ShowMessage("该棋谱是一个胜负以分的结局，不能再继续了，重新来过。");
    }
    else
    {
      begin=true;
      gamenum++;
      SpeedButton3->Enabled=true;
    }
     Label5->Caption="游戏场数："+String(gamenum);
     Label6->Caption="赢："+String(ying)+"   平："
      +String(ping)+"   输："
      +String(shu)+" 废："
      +String(gamenum-ping-ying-shu-1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  pt=ExtractFilePath(ParamStr(0));//当前程序所在路径;
  ps=pt+"\\res\\";
  if(!FileExists(pt+"\WZQHISTORY.mdb"))
  {
    ShowMessage(">>> 数据库文件 "+pt+"WZQHISTORY.mdb不存在！");
    Application->Terminate();
  }
  else
  {
    //初始化数据库连接
    ADOConnection1->Close(); //关闭连接
    ADOConnection1->ConnectionString= //设置数据库连接路径
    "Provider=Microsoft.Jet.OLEDB.4.0;Mode=Share Deny None;User ID=Admin;Data Source="
   +pt+"\WZQHISTORY.mdb;Persist security Info=False";
    ADOConnection1->Open();//设置完成，开启数据库联接。
  }
 //----------------------------------
  TForm2 *f=new TForm2(this);
  if(f->ShowModal()!=mrOk)
  {
    Application->Terminate();
  }
  Label4->Caption="用户："+UserName ;
  Label5->Caption="游戏场数："+String(gamenum);
  Label6->Caption="赢："+String(ying)+"   平："
   +String(ping)+"   输："
   +String(shu)+" 废："
   +String(gamenum-ping-ying-shu);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 if(IDYES==MessageBox(Handle,"是否退出游戏？ 游戏记录将自动保存！","SK五子棋",MB_YESNO))
 {
  // 保存记录
  AnsiString s="update [USER] set gamenum="+String(gamenum)+",ying="+String(ying)
  +",shu="+String(shu)+",ping="+String(ping)+"  where useID='"+this->UserName+"'";
  ADOQuery1->Close();
  ADOQuery1->SQL->Clear();
  ADOQuery1->SQL->Add(s);
  ADOQuery1->ExecSQL();
 }
 else CanClose=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
   Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
  if(CheckBox2->Checked)
  {
     bgsnd=true;
    // sndPlaySound((ps+"main.wav").c_str(),SND_FILENAME|SND_LOOP|SND_ASYNC);
     PlaySound((ps+"main.wav").c_str(),NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
  }
  else
  {
     bgsnd=false;
    PlaySound(NULL, NULL, 0);
  //  sndPlaySound(NULL,0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
  snd=CheckBox1->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  delete QIPANBMP;
  delete BAIQI;
  delete HEIQI;
}
//---------------------------------------------------------------------------

