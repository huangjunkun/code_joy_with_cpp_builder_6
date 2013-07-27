//---------------------------------------------------------------------------
// ������SK ������ 1.0
// ���ߣ�seeker
// ���������������ѧϰ���κ��˿����޸ĸ��ƣ�������ע��ԭ������Ϣ��
// ע�⣺��Ȩ������seeker
// ���ڣ�2006-12-31
// ���£�2007-12-28
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
 // ��ʼ������
  srand((unsigned)time(NULL)) ;

  Memo1->DoubleBuffered=true;
  this->DoubleBuffered=true;
  // ����ͼƬ��Դ
  QIPANBMP=new Graphics::TBitmap();
  BAIQI=new Graphics::TBitmap();
  HEIQI=new Graphics::TBitmap();
  // ����͸��ɫ
  BAIQI->Transparent=true;
  BAIQI->TransparentColor=clFuchsia;
  HEIQI->Transparent=true;
  HEIQI->TransparentColor=clFuchsia;
  Image1->Picture->Bitmap->Transparent=true;
  Image1->Picture->Bitmap->TransparentColor=clFuchsia;
  // ����Դ��ȡλͼ
  Image1->Picture->Bitmap->LoadFromResourceName((int)HInstance,"beijing");
  QIPANBMP->LoadFromResourceName((int)HInstance,"qipan");
  BAIQI->LoadFromResourceName((int)HInstance,"baiqi");
  HEIQI->LoadFromResourceName((int)HInstance,"heiqi");
 // ��ʼ��һЩ����
  offsetx=18; offsety=86; // ͼƬλ��
  begin=false;
  gamenum=0;  ying=0;   ping=0;  shu=0; //��Ϸͳ����
  snd=true;bgsnd=true; tmpsnd=true;
 // ׼��
 Shape1->Left=7*35+17+offsetx;
 Shape1->Top=7*35+17+offsety;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateParams(TCreateParams & Params)
{
    TForm::CreateParams(Params);
    Params.Caption="SK�����塾���ߣ�seeker��";
    strcpy(Params.WinClassName, "http://myseeker.bokee.com");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
 //Graphics::TBitmap��Hanleֻ��һ��HBITMAP��������HDC��
 //ֻ��Canvas��Handle����HDC
 // ������ͼ
 BitBlt(this->Canvas->Handle,offsetx,offsety,532,532,QIPANBMP->Canvas->Handle,0,0,SRCCOPY);
 // ���������µ�����
 for(int i=0;i<15;i++)
 {
   for(int j=0;j<15;j++)
   {
     if(ch5.CH5[i][j]==2) //����
     {
       //i*35+3+offsetx --> i*35+20-17+offsetx,
       this->Canvas->Draw(i*35+3+offsetx,j*35+3+offsety,BAIQI);
     }
     else if(ch5.CH5[i][j]==1)//��
     {
       this->Canvas->Draw(i*35+3+offsetx,j*35+3+offsety,HEIQI);
     }
   }//for_j
 }//for_i
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{ // ����Ϸ
  ch5.Reset(); //����
  this->Invalidate();// �ػ�
  SpeedButton7->Enabled=true;
  begin=true;
  usercolor=1;
  gamenum++;
  Label5->Caption="��Ϸ������"+String(gamenum);
  Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
   +String(ping)+"   �䣺"
   +String(shu)+" �ϣ�"
   +String(gamenum-ping-ying-shu);
  Memo1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 // ����
 if(!ch5.Retract())
 {
   SpeedButton3->Enabled=false;
   MessageBox(Handle,"����û����Ը���ڣ�����ʲô�尡����","SK������",MB_OK);
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
 //��С��
 SendMessage(Application->Handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

   if(Button!=mbLeft) return;
   // ���������Ч��Χ
   if(X>550||X<20||Y>610||Y<90)
   {
     //�ƶ�����
     ReleaseCapture();
     Perform(WM_NCLBUTTONDOWN,HTCAPTION, 0);
     return;
   }
   if(!begin)
   {
     MessageBox(Handle,"������Ͻǵġ�����Ϸ����ʼ�˻����ġ�\n\n�����ȡ������û������ߡ�","SK������",MB_OK);
     return;
   }
   int px,py,res;
   Label1->Caption=String(X)+","+String(Y);
   int x=(X-20-offsetx);//����ת��
   int y=(Y-20-offsety+3);
     // �ж����ĸ����
   Qx=(x+17)/35;
   Qy=(y+17)/35;
   px=Qx;
   py=Qy;

   if(!( (x+10)>Qx*35 && (y+10)>Qy*35 )) //�ж����������Ƿ�Ϸ�
     return ;

    if(snd) //sndPlaySound(put,SND_MEMORY|SND_ASYNC);
      PlaySound((ps+"put.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);

   SpeedButton7->Enabled=false;
   res=ch5.PutChess( Qx, Qy, px, py);//eeeee
   this->Invalidate();
   Shape1->Left=px*35+17+offsetx;
   Shape1->Top=py*35+17+offsety;
   Label2->Caption="�û�������ӣ���"+String(Qx)+"��"+String(Qy)+"�� ������"+String(ch5.StepLen);

   if(!(px==Qx&&py==Qy))
   {
     Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]��( "+String(Qx)+","+String(Qy)+","+String(usercolor)+" )");
     Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]��( "+String(px)+","+String(py)+","+String(3-usercolor)+" )");;
   }
   switch(res)
   {
    case -2:
    break;
    case -1:
         SpeedButton3->Enabled=true;  // ���Ի�����
    break;
    case 0:
      ping++;
      Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(shu)+" �ϣ�"
      +String(gamenum-ping-ying-shu);
      SpeedButton3->Enabled=false; //���尴ť
      MessageBox(Handle,"ƽ�֣�","SK������",MB_OK);
    break;
    case 1:
    case 2:
      if(usercolor==res)
      {
        ying++;
       Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(gamenum-ping-ying)+" �ϣ�"
      +String(gamenum-ping-ying-(gamenum-ping-ying));
        SpeedButton3->Enabled=false; //���尴ť
       if(snd) //sndPlaySound(win,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"win.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
        MessageBox(Handle,"��ϲ�㣡��Ӯ�ˣ�","SK������",MB_OK);
      }
      if(usercolor==3-res)
      {
       shu++;
       Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(shu)+" �ϣ�"
      +String(gamenum-ping-ying-shu);
       SpeedButton3->Enabled=false; //���尴ť
      if(snd) // sndPlaySound(lose,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"lose.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"�ܿ�ϧ�������ˣ�","SK������",MB_OK);
      }
    break;
    case 3:
      shu++;
      Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(shu)+" �ϣ�"
      +String(gamenum-ping-ying-shu);
      SpeedButton3->Enabled=false; //���尴ť
     if(snd)// sndPlaySound(lose,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"lose.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"ע�⣡������ˣ�����������","SK������",MB_OK);
    break;
    case 4:
      ying++;
      SpeedButton3->Enabled=false; //���尴ť
      Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(shu)+" �ϣ�"
      +String(gamenum-ping-ying-shu);
       if(snd) //sndPlaySound(win,SND_MEMORY|SND_ASYNC);
        PlaySound((ps+"win.wav").c_str(),NULL, SND_FILENAME|SND_ASYNC);
      MessageBox(Handle,"�ҷ����㣡�����䣡������","SK������",MB_OK);
    break;
   };

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
  // ����
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
  LabelTime->Caption=FormatDateTime("'��ǰʱ�䣺'YYYY-MM-DD HH:MM:SS",Now());
  SetProcessWorkingSetSize(GetCurrentProcess(),0xFFFFFFFF,0xFFFFFFFF);
}
//---------------------------------------------------------------------------
// �����ļ�
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
      MessageBox(Handle,"�޷������ļ�������д������ռ䲻�㣡","SK������",MB_OK);
      return;
    }
    // д���ļ�.
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
//������Ϣ��
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
  FILE *fp;
  //����
  String s="";
  if(OpenDialog1->Execute())
  {
    s=OpenDialog1->FileName;
    fp=fopen(s.c_str(),"r");
    if(!fp)
    {
      MessageBox(Handle,"�޷���ȡ�ļ����ļ����ɷ��ʣ�","SK������",MB_OK);
      return;
    }
    // ���ļ�����
    ch5.Reset();//�ȸ�λ��
    usercolor=1; // �˻���ս---�ֵ�������
    Memo1->Text="";
    Memo1->Lines->Add("��ȡ�ļ���");
    Memo1->Lines->Add(s);
    Memo1->Lines->Add("�����ݡ�");
    int i=0,flag=3,tcc=-1;

    fscanf(fp,"%d",&tcc);
    if(tcc==2) //˵�����ļ���ԭ���������µģ�
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
        ch5.SetStepOfIndex(i,tx,ty,tc); //��������ÿ������
        ch5.CH5[tx][ty]=tc;
        ch5.StepLen++;
        i++;
        // ��Ϣ��ʾ
        // ��������
        if(flag==1)
        {
          Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]��( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=2;
        }
        else if(flag==2)
        {
          Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]��( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=1;
        }
        // ������
        else if(flag==3)
        {
          Memo1->Lines->Add("----> "+ColorName[usercolor]+"[Man]��( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=4;
        }
        else if(flag==4)
        {
          Memo1->Lines->Add("----> "+ColorName[3-usercolor]+"[Rob]��( "+String(tx)+","+String(ty)+","+String(ch5.CH5[tx][ty])+" )");
          flag=3;
        }
      }
      else break;
    }//for
    fclose(fp);
    this->Invalidate();
    Label2->Caption="������"+String(ch5.StepLen);

    //�ж��Ƿ������Ӯ���ļ�
    if(ch5.StepLen>=225)
    {
      begin=false;
      ShowMessage("��������һ��ʤ���ԷֵĽ�֣������ټ����ˣ�����������");
    }
    else
    {
      begin=true;
      gamenum++;
      SpeedButton3->Enabled=true;
    }
     Label5->Caption="��Ϸ������"+String(gamenum);
     Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
      +String(ping)+"   �䣺"
      +String(shu)+" �ϣ�"
      +String(gamenum-ping-ying-shu-1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  pt=ExtractFilePath(ParamStr(0));//��ǰ��������·��;
  ps=pt+"\\res\\";
  if(!FileExists(pt+"\WZQHISTORY.mdb"))
  {
    ShowMessage(">>> ���ݿ��ļ� "+pt+"WZQHISTORY.mdb�����ڣ�");
    Application->Terminate();
  }
  else
  {
    //��ʼ�����ݿ�����
    ADOConnection1->Close(); //�ر�����
    ADOConnection1->ConnectionString= //�������ݿ�����·��
    "Provider=Microsoft.Jet.OLEDB.4.0;Mode=Share Deny None;User ID=Admin;Data Source="
   +pt+"\WZQHISTORY.mdb;Persist security Info=False";
    ADOConnection1->Open();//������ɣ��������ݿ����ӡ�
  }
 //----------------------------------
  TForm2 *f=new TForm2(this);
  if(f->ShowModal()!=mrOk)
  {
    Application->Terminate();
  }
  Label4->Caption="�û���"+UserName ;
  Label5->Caption="��Ϸ������"+String(gamenum);
  Label6->Caption="Ӯ��"+String(ying)+"   ƽ��"
   +String(ping)+"   �䣺"
   +String(shu)+" �ϣ�"
   +String(gamenum-ping-ying-shu);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 if(IDYES==MessageBox(Handle,"�Ƿ��˳���Ϸ�� ��Ϸ��¼���Զ����棡","SK������",MB_YESNO))
 {
  // �����¼
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

