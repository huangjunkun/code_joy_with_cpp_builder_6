//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "setclock.h"

#define     MIN(X,Y)    (X<Y ? X:Y)
#define     MAX(X,Y)    (X>Y ? X:Y)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    /*  */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateParams(TCreateParams &Params)
{
    //重载TForm类的成员函数 --消去标题栏
    TForm::CreateParams(Params);
    Params.Style &=~WS_CAPTION;
}
//---------------------------------------------------------------------------
/* */
void __fastcall TMainForm::WMLBUTTONDOWN(TMessage &Msg)
{
    //截获,处理WM_LBUTTONDOWN消息
    if(this->WindowState!=wsMaximized)
        Perform(WM_NCLBUTTONDOWN,HTCAPTION,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WMMOVE(TWMMove &Msg)
{
    /*       */
    if(Msg.XPos<0)
        Left = 0;
    if(Msg.YPos<0)
        Top = 0;
    if(Msg.XPos>Screen->Width-Width+10)
        Left = Screen->Width-Width;
    if(Msg.YPos>Screen->Height-Height+10)
        Top = Screen->Height-Height;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WMMOVING(TMessage &Msg)
{
    /*     ????
      LPRECT  lprect = (LPRECT)Msg.LParam;
      if(lprect->left<0)
          lprect->left = 0;
      if(lprect->top <0)
          lprect->top = 0;
      if(lprect->left>Screen->Width-Width+10)
          lprect->left = Screen->Width-Width;
      if(lprect->top >Screen->Height-Height+10)
          lprect->top = Height-Height;
      if(lprect->right>Screen->Width)
          lprect->right = Screen->Width;
      if(lprect->bottom >Screen->Height)
          lprect->bottom = Screen->Height;       */
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainForm::WndProc(TMessage &Msg)
{   nothing !!!
    if(Msg.Msg==WM_MOVING)
    {

    }
    TMainForm::WndProc(Msg);
}    */
//---------------------------------------------------------------------------

void __fastcall TMainForm::WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg)
{
    //当用户点击窗体状态栏上的最大化按钮时，限制窗体最大化后的长宽
    //Msg.MinMaxInfo->ptMaxSize.x=800;
    //Msg.MinMaxInfo->ptMaxSize.y=800;
    //设定窗体最大化时左上角的屏幕坐标为当前窗体的位置
    Msg.MinMaxInfo->ptMaxPosition.x=0;
    Msg.MinMaxInfo->ptMaxPosition.y=0;
    //当用户用鼠标拖动的方式改变窗体尺寸的时候，限制其最大值
    //Msg.MinMaxInfo->ptMaxTrackSize.x=800;
    //Msg.MinMaxInfo->ptMaxTrackSize.y=800;
    //当用户用鼠标拖动的方式改变窗体尺寸的时候，限制其最小值
    Msg.MinMaxInfo->ptMinTrackSize.x=300;
    Msg.MinMaxInfo->ptMinTrackSize.y=300;
    //显示当前窗体尺寸
//    Label1->Caption="Width="+AnsiString(Width)+
//                    " Height="+AnsiString(Height);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WMNCHITTEST(TWMMouse &Msg)
{
    //截获,处理WM_NCHITTEST消息 ?????????????????
    /*
    if(Msg.Keys == mbRight)
         Perform(WM_RBUTTONDOWN,HTCAPTION,NULL);
     */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MYHOTKEY(TWMHotKey &Msg)
{
    //?????what why ////
    if(Msg.HotKey==VK_F1|VK_CONTROL)
    {
        //ShowMessage(" TWMHotKey -- Ctrl + F1 ");
        AboutItemClick(this);
        SetForegroundWindow(Handle);
    }
    //  TMainForm::Dispatch(&Msg);  //导致消息死循环！！！
}
//---------------------------------------------------------------------------
void    TMainForm::Init_SMH()
{
    /*    */
    //    s_i = 0 ,m_i = 0 ,h_i = 0;
    String   S = Time();
    if(S[3]!=':') //格式化时间为00：00：00
        S.Insert("0" ,1);
    s_i = S.SubString(7 ,2).ToInt();
    m_i = S.SubString(4 ,2).ToInt();
    h_i = (S.SubString(1 ,2).ToInt()%12)*5 + m_i/12;//;
    DrawLine(s_color ,s_width ,seconds[s_i].left ,seconds[s_i].top);
    DrawLine(m_color ,m_width ,minute[m_i].left ,minute[m_i].top);
    DrawLine(h_color ,h_width ,hour[h_i].left ,hour[h_i].top);
}
//---------------------------------------------------------------------------
void    TMainForm::AddTrayIcon()
{
    NOTIFYICONDATA  tnd;
    PSTR     pszTip = "时钟托盘";
    lstrcpyn(tnd.szTip ,pszTip ,sizeof(tnd.szTip));
    tnd.cbSize = sizeof(NOTIFYICONDATA);
    tnd.hWnd  =  this->Handle;
    tnd.uID = ID_MYICON;
    tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    tnd.uCallbackMessage = WM_MYNOTIFY;
    tnd.hIcon = Application->Icon->Handle;
    Shell_NotifyIcon(NIM_ADD ,&tnd);
}
//---------------------------------------------------------------------------
void    TMainForm::DeleteTrayIcon()
{
    NOTIFYICONDATA  tnd;
    /*
    PSTR     pszTip = "时钟托盘";
    lstrcpyn(tnd.szTip ,pszTip ,sizeof(tnd.szTip);
    */
    tnd.cbSize = sizeof(NOTIFYICONDATA);
    tnd.hWnd  =  this->Handle;
    tnd.uID = ID_MYICON;
    tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    tnd.uCallbackMessage = WM_MYNOTIFY; //********//
    tnd.hIcon = this->Icon->Handle;
    Shell_NotifyIcon(NIM_DELETE  ,&tnd);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MYNOTIFY(TMessage &Msg)
{
    /*
      POINT   mousepos;
      switch(Msg.LParam)
      {
          case WM_RBUTTONUP :
              GetCursorPos(&mousepos);
              PopupMenu1->PopupComponent = this;
              SetForegroundWindow(Handle);
              PopupMenu1->Popup(mousepos.x ,mousepos.y);
              break;
          case WM_LBUTTONUP :
              this->Show();
              break;
          default:
              break;
      }
      TMainForm::Dispatch(&Msg);      */
    POINT MousePos;

    switch(Msg.LParam)
    {
    case WM_RBUTTONUP:
        GetCursorPos(&MousePos);
        PopupMenu1->PopupComponent = this;
        SetForegroundWindow(Handle);
        PopupMenu1->Popup(MousePos.x, MousePos.y);
        break;
    case WM_LBUTTONUP:
        /*Show();//111 前端显示（暂时）没有效果？？？？
        //this->Activate(); 222
        //this->SetFocus();  3333
        // SetActiveWindow(Handle);  4444
        SetWindowPos(Handle ,HWND_TOP ,Left ,Top ,  5555
        Width ,Height ,SWP_SHOWWINDOW); //|SWP_DRAWFRAME	|SWP_NOMOVE |SWP_NOSIZE
        */ //前端显示（暂时），获取 前端显示窗口句柄：HWND GetForegroundWindow(VOID)
        Show();
        SetForegroundWindow(Handle);
    default:
        break;
    }
    TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //this->WindowState = wsMaximized;  //
    //Image1->Canvas->Pen->Mode = pmCopy;//颜色指定为画笔颜色
    //Image1->Canvas->Pen->Style = psSolid;//实心填充
    //this->BorderStyle = bsDialog;//

    //this->BorderStyle = bsNone; // or :重载CreateParams(TCreateParams &Params);
    //修改此单字符串窗口组件性质，可自由缩放大小
    DWORD dwStyle = ::GetWindowLong(Handle, GWL_STYLE);
    ::SetWindowLong(Handle, GWL_STYLE, dwStyle | WS_SIZEBOX);
    //修正窗口的实际尺寸与范围
    //以便USER直接调整窗口边沿 //?????????????
    ::MoveWindow(Handle, Left, Top,
                 Width, Height + 1, true);
    Left = Screen->Width-Width;
    Top  = Screen->Height-Height-15;

    StatusBar1->Panels->Items[0]->Text = "   日期： " + DateToStr(Date());
    s_width = 2 ,m_width = 4 ,h_width = 8  ,fontsize = 20;
    s_color = clRed ,m_color = h_color = f_color = clBlack;
    this->Color = clGray;

    this->DoubleBuffered = true;//双倍缓冲，防止画图闪动
    this->TransparentColor = true; // 透明口
    this->AlphaBlend = true;
    this->AlphaBlendValue = 180;
    Label_Hi->Color = this->Color;
    Label_Hi->Transparent = true;//透明标签
    Label1->Left = 0;
    Label1->Top  = 0;
    Label1->Caption = "";
    this->AddTrayIcon();
    //使应用程序不出现在任务栏
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    //注册系统级热键  BOOL RegisterHotKey（HWND hWnd，intid，UINT fsModifiers，UINT vk）
    //该函数定义一个系统范围的热键。
    if(RegisterHotKey(this->Handle ,0x0001 ,MOD_CONTROL ,VK_F1))
      ; //ShowMessage("系统级热键:Ctrl + F1 注册成功 ！");
    else
        ShowMessage("系统级热键:Ctrl + F1 注册失败 ！");  /* GetLastError();
    if(RegisterHotKey(this->Handle ,0x0001 ,MOD_WIN ,NULL))
        ShowMessage("系统级热键:Windows 注册成功 ！");
    else
        ShowMessage("系统级热键:Windows 注册失败 ！");    */

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
    //---------- //制作 时钟
    static  bool    center;
    this->Canvas->FillRect(this->GetClientRect());
    //this->Canvas->FillRect(this->Canvas->ClipRect);   //方法二
    int     X ,Y; /**/
    if(this->Width>800 )
        X = 800-10;
    else
        X = this->Width-40;

    if(this->Height>800)
        Y = 800-10;
    else
        Y = this->Height-60; //40+20:20留状态栏
    if(this->Width>800 || this->Height>650)//
        center = true;
    else
        center = false;  /* */
    dot.left = this->Width/2-20;
    dot.top  = this->Height/2-20;
    R = MIN(X ,Y)/10*5-30; //*5即*10/2;-5以免擦损圆环
    //计算秒分时针转动坐标位置
    Account_SMH();
    //画时钟
    this->Canvas->Pen->Width = m_width;
    //this->Canvas->Brush->Color = clYellow;
    this->Canvas->Pen->Color = f_color; //clBlack clYellow
    if(center == false)
        this->Canvas->Ellipse(20 ,20 ,X ,Y);
    else
    {
        this->Canvas->Ellipse(dot.left-X/2+20,dot.top-Y/2+20 ,dot.left+X/2,dot.top+Y/2);
        //ShowMessage("越界，置中！！！");
    }
    //ShowMessage("PaintClock()");
    PaintClock();
    //初始化时钟当前系统时间
    Init_SMH();  //可能导致画秒针的差错！办法：调节好TimerClock Interval的值 900 左右

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    /*  /--- //制作 时钟
     -----TMainForm::FormPaint(TObject *Sender)------ */  //FormPaint(Sender);
}
//---------------------------------------------------------------------------
void    TMainForm::Account_SMH()
{
    int     r1 = R/5*3 ,r2 = R/5*2;
    int     a = dot.left ,b = dot.top-R ,b1 = dot.top-r1 ,b2 = dot.top-r2;
    double  angle = M_PI/180*6;//角度 :6°
    for(int i=0; i<60; i++)
    {
        seconds[i].left = a+R*sin(i*angle);
        seconds[i].top = b+R*(1-cos(i*angle));
        minute[i].left = a+r1*sin(i*angle);
        minute[i].top = b1+r1*(1-cos(i*angle));
        hour[i].left =  a+r2*sin(i*angle);
        hour[i].top =  b2+r2*(1-cos(i*angle));
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TimerClockTimer(TObject *Sender)
{
    // this->Canvas->CleanupInstance();  //What???
    TimerClock->Enabled = false;  //先暂停计时器 ，避免冲突

    ClearLine(s_width ,seconds[s_i].left ,seconds[s_i].top);
    if(s_i==m_i||s_i==m_i+1||s_i==m_i+2)// 擦损分针，则重画分针
        DrawLine(m_color ,m_width ,minute[m_i].left ,minute[m_i].top);
    if(s_i==h_i||s_i==h_i+1||s_i==h_i+2)// 擦损时针，则重画时针
        DrawLine(h_color ,h_width ,hour[h_i].left ,hour[h_i].top);
    s_i = (++s_i)%60;
    DrawLine(s_color ,s_width ,seconds[s_i].left ,seconds[s_i].top);
    //Shape_S->Left = seconds[s_i].left-15;
    //Shape_S->Top =  seconds[s_i].top-15;
    if(s_i==0)
    {
        ClearLine(m_width ,minute[m_i].left ,minute[m_i].top);
        if(m_i==h_i||m_i==h_i+1||m_i==h_i+2)//// 擦损时针，则重画时针
            DrawLine(h_color ,h_width ,hour[h_i].left ,hour[h_i].top);
        m_i = (++m_i)%60;
        DrawLine(m_color ,m_width ,minute[m_i].left ,minute[m_i].top);
        if(m_i%12==0)
        {
            ClearLine(h_width ,hour[h_i].left ,hour[h_i].top);
            h_i = (++h_i)%60;
            DrawLine(h_color ,h_width ,hour[h_i].left ,hour[h_i].top);
        }
    }
    Label_Hi->Repaint();  //重画标签
    Label1->Caption = m_i;

    TimerClock->Enabled = true; //恢复 计时器 。。。。
}
//---------------------------------------------------------------------------
void    TMainForm::DrawLine(TColor color ,int width ,int x ,int y)
{
    this->Canvas->Pen->Color = color;
    this->Canvas->Pen->Width = width;
    this->Canvas->MoveTo(dot.left ,dot.top);
    this->Canvas->LineTo(x ,y);
}
//---------------------------------------------------------------------------

void    TMainForm::ClearLine(int width ,int x ,int y)
{
    this->Canvas->Pen->Color = this->Canvas->Brush->Color;
    //TPenStyle   olderstyle = this->Canvas->Pen->Style;
    this->Canvas->Pen->Width = width;
    //this->Canvas->Pen->Style = psClear;
    this->Canvas->MoveTo(dot.left ,dot.top);
    this->Canvas->LineTo(x ,y);
    //this->Canvas->Pen->Style = olderstyle;
}
//---------------------------------------------------------------------------
void    TMainForm::PaintClock()
{
    Label_Hi->Left = dot.left - Label_Hi->Width/2;
    Label_Hi->Top  = dot.top  - Label_Hi->Height/2;
    this->Canvas->Font->Size = fontsize;//设置字体大小
    this->Canvas->Font->Color = f_color;
    /*
    this->Canvas->Pen->Color = clBlack;
    this->Canvas->Pen->Width = 10;      */
    this->Canvas->TextOutA(seconds[0].left-10 ,seconds[0].top-20 ,"12");
    this->Canvas->TextOutA(seconds[30].left ,seconds[30].top-20 ,"6");
    for(int i=5; i<30; i += 5)
    {
        //this->Canvas->MoveTo(seconds[i].left ,seconds[i].top);
        //this->Canvas->LineTo(seconds[i+30].left ,seconds[i+30].top);
        this->Canvas->TextOutA(seconds[i].left ,seconds[i].top-20 ,IntToStr(i/5));
        this->Canvas->TextOutA(seconds[i+30].left-10 ,seconds[i+30].top-20 ,IntToStr((i+30)/5));
    }/*  //屏蔽部分为画时钟格线--略去
    this->Canvas->Pen->Color = this->Color;
    this->Canvas->Brush->Color = this->Color;
    this->Canvas->Ellipse(seconds[45].left+10 ,seconds[0].top+10 ,
                            seconds[15].left-10 ,seconds[30].top-10);  */
}
//---------------------------------------------------------------------------


/*  !!!!! Form can not drag !!!!c窗口不能拖拽
//this->Left = X;
    //this->Top  = Y;
    //this->BeginDrag(true ,1);
    //Accept = true;   */
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDblClick(TObject *Sender)
{
    static int s_old ,m_old ,h_old ,f_old;
    if(this->WindowState!=wsMaximized)
    {
        s_old = s_width  ,m_old = m_width  ,h_old = h_width  ,f_old = fontsize;
        s_width = 6 ,m_width = 12 ,h_width = 24 ,fontsize = 40;
        this->WindowState = wsMaximized;
    }
    else
    {
        s_width = s_old ,m_width = m_old ,h_width = h_old ,fontsize = f_old;
        this->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    Cursor = crArrow;
    /*

        if((X<Left+5&&X>Left-5) || (Y<Top+5&&Y>Top-5) || X==Left+Width || Y==Top+Height)
        {
            this->BorderStyle = bsSizeable;
            this->AutoScroll = false;
        }
        else
            this->BorderStyle = bsDialog;
        this->Hint = IntToStr(X) + " , " + IntToStr(Y);
        this->ShowHint = true;
        */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key,
                                     TShiftState Shift)
{
    if(Key == 27)
    {
        Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetItemClick(TObject *Sender)
{
    SetClock->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauseItemClick(TObject *Sender)
{
    TimerClock->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ContinueItemClick(TObject *Sender)
{
    TimerClock->Enabled = true;
    FormResize(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
    this->DeleteTrayIcon();  //可略！！！！
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HideShowItemClick(TObject *Sender)
{
//    this->Hide();
    this->Visible = !Visible;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//      AnimateWindow(this->Handle ,2000 ,AW_HIDE | AW_BLEND);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    /*   //法二，发送消息    */
    if(Cursor == crArrow &&this->WindowState!=wsMaximized)
    {
        //释放原有鼠标捕捉状态，
        //并同时送出鼠标单击位置等同于窗口标题栏可拖曳窗口的属性
        ::ReleaseCapture();
        SNDMSG(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
        //PostMessage(Handle ,WM_NCLBUTTONDOWN,HTCAPTION,0);
//   SendMessage(Handle ,WM_NCLBUTTONDOWN,HTCAPTION,0);
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::AboutItemClick(TObject *Sender)
{
    Application->MessageBoxA("      \n！！！hjk 时钟 1.0\n\n！！！该程序由黄俊坤精心打造 ！！！\n\n     ！！！软件工程（三）班！！！   \n\n      ！！！ 学号06065072 ！！！     \n\n           ！！！ 谢谢 ！！！           ",
                             "软件版本",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDragDrop(TObject *Sender, TObject *Source,
                                        int X, int Y)
{
    /*       ????    */ /*
      TPoint  point;
      point.x = X + Left;
      point.y = Y + Top;
      //point = ClientToScreen(TPoint(X,Y));
      if((point.x>Screen->Width || point.y>Screen->Height))// &&State==dsDragLeave
      { //Accept = false;
          Left = 500;
          Top = 500;
      }

    //GetCursorPos()用于获取鼠标的位置，但这个位置是以屏幕坐标的形式返回的，如果想将这种屏幕相对坐标转换为窗体中的坐标形式，还需要用ScreenToClient()进行坐标转换。
    TPoint   PT;
    ::GetCursorPos(&PT);
    TPoint   P;
    P=ScreenToClient(&PT);
    */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDragOver(TObject *Sender, TObject *Source,
                                        int X, int Y, TDragState State, bool &Accept)
{
    /*       ????    */  /*
       TPoint  point;
       point.x = X + Left;
       point.y = Y + Top;
       //point = ClientToScreen(TPoint(X,Y));
       if((point.x>Screen->Width || point.y>Screen->Height) &&State==dsDragLeave)
       {
           Accept = false;
       }

    //GetCursorPos()用于获取鼠标的位置，但这个位置是以屏幕坐标的形式返回的，如果想将这种屏幕相对坐标转换为窗体中的坐标形式，还需要用ScreenToClient()进行坐标转换。
     TPoint   PT;
     ::GetCursorPos(&PT);
     TPoint   P;
     P=ScreenToClient(&PT);
    */
}
//---------------------------------------------------------------------------


