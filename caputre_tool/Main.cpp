/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Region.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#pragma resource "extrares.res"

TMainForm *MainForm;
HHOOK   OldHook;

#include "SubUnit.cpp"

//键盘钩子 封锁 windows 热键
LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam);
// 调用 动态链接库dll 文件的 图像处理方法
HBITMAP CallDllFunc(const String& FuncName ,HBITMAP hb ,const String& DllName="DealWithDll.dll");

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    pBitmap = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WMLBUTTONDOWN(TMessage &Msg)
{
    //截获,处理WM_LBUTTONDOWN消息
    if(this->WindowState!=wsMaximized)
        Perform(WM_NCLBUTTONDOWN,HTCAPTION,NULL);
}
//---------------------------------------------------------------------------
void    MyWndProc(TMessage &Msg)
{
    // 窗口消息处理函数 ....
    if(Msg.Msg==WM_NCLBUTTONDOWN)
        PostMessage(MainForm->Handle ,WM_NCLBUTTONDOWN,HTCAPTION,NULL);   // Perform
    //TScrollBox::WndProc(Msg);
    //MainForm->ScrollBox1->WndProc(Msg);
    ShowMessage("11111");
    PostMessage(MainForm->ScrollBox1->Handle ,Msg.Msg,Msg.WParam,Msg.LParam);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    /*      */
    OldHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyProc, HInstance, 0);
    // ....设置鼠标
    Screen->Cursors[crCursor_] = LoadCursor(HInstance, "Cursor");
    Screen->Cursors[crCross_] = LoadCursor(HInstance, "Cross");
    Screen->Cursors[crPen_] = LoadCursor(HInstance, "Pen");
    Screen->Cursors[crSizeNWSE_] = LoadCursor(HInstance, "Resizeright");
    Screen->Cursors[crSizeNESW_] = LoadCursor(HInstance, "Resizeleft");
    Screen->Cursors[crSizeAll_] = LoadCursor(HInstance, "Resizeall");

    //ScrollBox2->Cursor = TCursor(crSizeAll_); // test ---
    Image1->AutoSize = true;
    ScrollBox1->DoubleBuffered = true;
    ScrollBox2->DoubleBuffered = true;
    lblTime->Parent = StatusBar1;
    lblTime->Top = 4;
    lblTime->Left = StatusBar1->Width-lblTime->Width;

    //::SetWindowLong(ScrollBox1->Handle ,GWL_WNDPROC ,(long)MyWndProc); //???

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    GroupBox2->Width = Panel1->Width>>1;
    lblTime->Left = StatusBar1->Width-lblTime->Width;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
//    Image1->Canvas->CopyRect(Image1->Canvas->ClipRect ,Image2->Canvas ,  \
    Image2->Canvas->ClipRect);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miCaptureScreenClick(TObject *Sender)
{
    MainForm->Visible=false;

    //等待屏幕刷新
    Sleep(1000);

    //拷贝截获的图像
    Graphics::TBitmap *bmp = new Graphics::TBitmap;
    bmp->Width = Screen->Width;
    bmp->Height = Screen->Height;
    CaptureDesktop(bmp->Canvas->Handle);
    Image1->Picture->Assign(bmp);
    delete    bmp;
    //重新显示窗体
    MainForm->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miCaptureWindowClick(TObject *Sender)
{
    TRect rect;
    MainForm->Visible=false;
    Sleep(1000);
    // 获取当前活动的窗体句柄
    HWND WinHandle =GetTopWin();
    // 获取此窗口的尺寸
    GetWindowRect(WinHandle, &rect);
    // 截获窗体图像
    CaptureWinImage(rect);
    // 将工作变量pBitmao中的图像拷贝到Image1中
    Image1->Width = pBitmap->Width;
    Image1->Height = pBitmap->Height;
    Image1->Picture->Bitmap = pBitmap;
    MainForm->Visible=true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    pBitmap->Free();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miCaptureRegionClick(TObject *Sender)
{
    if(!MainForm->Visible)//==false
        return;//控制截图的唯一操作
    MainForm->Visible = false;
    Sleep(500);
    // 在RForm的Image组件中填充截获到的桌面图像
    CaptureDesktop(RForm->Image1->Canvas->Handle);
    //RForm->Visible = true;  // ...
    RForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miFileAdvancedDrawItem(TObject *Sender,
        TCanvas *ACanvas, TRect &ARect, TOwnerDrawState State)
{
    //自己绘制菜单
    //ACanvas->TextWidth(TMenuItem(Sender)->Caption);
    TJPEGImage  *jpeg = new TJPEGImage();
    jpeg->LoadFromFile("hehe.jpg");
    TRect mrect = Rect(0 ,0 ,jpeg->Width ,jpeg->Height);
    ACanvas->Draw(ARect.left ,ARect.Top-ARect.Bottom ,jpeg);
    //ACanvas->TextRect()
    //ACanvas->Assign(jpeg);
    SetBkMode(ACanvas->Handle , TRANSPARENT);
    DrawText(ACanvas->Handle ," \n文\n件\n菜\n单 " ,-1 ,&mrect ,DT_LEFT+DT_CENTER);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrayIcon1Click(TObject *Sender)
{
    this->Visible = !this->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tbGrayLinTransMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    /*
    if(String(Sender->ClassName())!="TToolButton")
        return;
    TToolButton*    tbPtr = (TToolButton*)Sender; */
    TControl*   Control = dynamic_cast<TControl*>(Sender);
    if(Control!=NULL)
        panelHint->Caption = Control->Hint;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miOpenImgClick(TObject *Sender)
{
    // -----
    if(OpenDialog1->Execute())
    {
        Image1->Picture->LoadFromFile(OpenDialog1->FileName);
        if(String(Image1->Picture->Graphic->ClassName())!="TBitmap")
        {
            // -- 更换位图文件，以可以图像处理 ---
            Graphics::TBitmap *bmp = new Graphics::TBitmap;
            bmp->Width = Image1->Picture->Width;
            bmp->Height = Image1->Picture->Height;
            bmp->Assign(Image1->Picture->Graphic);
            Image1->Picture->Assign(bmp);
            delete bmp;

        }
        StatusBar1->Panels->Items[1]->Text = String(Image1->Picture->Width)+"x"+ \
                                             String(Image1->Picture->Height)+"x24b";
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miSaveImgClick(TObject *Sender)
{
    if(Image1->Picture->Graphic==NULL)
        return;
    TSaveDialog     *pSaveDialog = RForm->SaveDialog1;
    pSaveDialog->FileName = "";
    pSaveDialog->Title = "保存原图像为...";
    if(pSaveDialog->Execute())  //
        RForm->SaveAsImage(Image1->Picture->Bitmap ,pSaveDialog->FilterIndex , \
                           pSaveDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miSaveAsImgClick(TObject *Sender)
{
    // -----
    if(Image2->Picture->Graphic==NULL)
        return;
    TSaveDialog     *pSaveDialog = RForm->SaveDialog1;
    pSaveDialog->FileName = "";
    pSaveDialog->Title = "处理图像另存为...";
    if(pSaveDialog->Execute())  //
        RForm->SaveAsImage(Image2->Picture->Bitmap ,pSaveDialog->FilterIndex , \
                           pSaveDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miExitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Image1MouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
        bLeftMBDown =  true;
        originPt.x = X;
        originPt.y = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1MouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bLeftMBDown = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1MouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    StatusBar1->Panels->Items[0]->Text = String("X: ")+String(X)+ \
                                         " ,Y: "+String(Y);
    if(bLeftMBDown)
    {
        TImage* pImage = dynamic_cast<TImage*>(Sender);
        int     left = pImage->Left + (X-originPt.x);
        int     top = pImage->Top  + (Y-originPt.y);

        TScrollBox* pScrollBox = dynamic_cast<TScrollBox*>(pImage->Parent);

        if(pScrollBox!=NULL)
        {
            if(left>pScrollBox->Width-10||left<10-pImage->Width || \
                    top>pScrollBox->Height+10 ||top<10-pImage->Height)
                return;
            pImage->Left = left;
            pImage->Top  =  top;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miCopyImgClick(TObject *Sender)
{
    // ----
    if(Image2->Picture->Graphic==NULL)
    {
        MessageDlg("处理图像为空!" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
        return;
    }
    unsigned DataHandle;
    HPALETTE APalette;
    unsigned short MyFormat;
    try
    {
        Image2->Picture->SaveToClipboardFormat(MyFormat,DataHandle,APalette);
        Clipboard()->SetAsHandle(MyFormat,DataHandle);
        //ShowMessage("Success to copy image to clipboard!");
    }
    catch(Exception& e)
    {
        ShowMessage("Failed to copy image to clipboard!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miPasteImgClick(TObject *Sender)
{
    // ----

    int     ImageHandle;
    Clipboard()->Open();
    try
    {
        ImageHandle = Clipboard()->GetAsHandle(CF_BITMAP);
        Image1->Picture->LoadFromClipboardFormat(CF_BITMAP ,ImageHandle ,0);
    }
    catch(Exception& e)
    {
        Clipboard()->Close();
        ShowMessage("Failed to Paste image to clipboard!");
        //throw;
    }
    Clipboard()->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miCutImgClick(TObject *Sender)
{
    // ----
    if(Image2->Picture->Graphic==NULL)
    {
        //MessageDlg("处理图像为空!" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
        MessageBox(this->Handle ,"处理图像为空!" ,NULL ,MB_OK|MB_ICONWARNING);
        return;
    }
    miCopyImgClick(Sender);
    Image2->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miClearProImgClick(TObject *Sender)
{
    // --
    Image2->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

Graphics::TBitmap* TMainForm::GetBitmapToProcess()
{
    Graphics::TBitmap  *bmp = NULL;
    if(Image2->Picture->Graphic!=NULL)
    {
        bmp = new Graphics::TBitmap;
        bmp->Width = Image2->Picture->Width;
        bmp->Height = Image2->Picture->Height;
        //bmp->Assign(Image2->Picture->Graphic); //...???
        bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,Image2->Canvas ,
                              Image2->Canvas->ClipRect);
    }
    else if(Image1->Picture->Graphic!=NULL)
    {
        /*  */
        bmp = new Graphics::TBitmap;
        bmp->Width = Image1->Picture->Width;
        bmp->Height = Image1->Picture->Height;
        //bmp->Assign(Image1->Picture->Graphic); //???
        //Image2->Picture->Assign(bmp);
        bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,Image1->Canvas , \
                              Image1->Canvas->ClipRect);

    }
    return  bmp;
}
//---------------------------------------------------------------------------

HBITMAP CallDllFunc(const String& FuncName ,HBITMAP hb ,const String& DllName)
{
    HINSTANCE   ins;
    ins = LoadLibrary(DllName.c_str());
    if(ins==NULL)
        throw Exception(DllName+" DLL isn't found ,error !");

    FARPROC  proc = GetProcAddress(ins ,FuncName.c_str());
    if(proc==NULL)
    {
        FreeLibrary(ins);
        throw Exception(FuncName+" address isn't found ,error !");
    }

    typedef HBITMAP (*FUNC) (HBITMAP);
    FUNC aFunc = (FUNC)proc;
    HBITMAP temp = aFunc(hb);
    if(!FreeLibrary(ins))
    {
        throw Exception(DllName+" DLL free error ! ");
    }
    return temp;
}
//---------------------------------------------------------------------------
void TMainForm::ProcessImg(const String& strFunc)
{
    Graphics::TBitmap* bmp = GetBitmapToProcess();
    if(bmp) // !=NULL
    {
        HBITMAP hBitmap;
        hBitmap = CallDllFunc(strFunc ,bmp->Handle);
        if(bmp->Handle!=hBitmap&&hBitmap!=NULL) //
            Image2->Picture->Bitmap->Handle = hBitmap;
        delete bmp;// 析构缓冲TBitmap ...
    }
    else
        ShowMessage("bmp==NULL");//
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miGrayLinTransClick(TObject *Sender)
{
    // ----
    ProcessImg("GrayLinTrans");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miLinerTranslationClick(TObject *Sender)
{
    // ----
    ProcessImg("LinerTranslation");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miTemplateSoftenClick(TObject *Sender)
{
    // ----
    ProcessImg("TemplateSoften");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miNearbySoftenClick(TObject *Sender)
{
    // ----
    ProcessImg("NearbySoften");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miLaplacSharpClick(TObject *Sender)
{
    // ----
    ProcessImg("LaplacSharp");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miMedianFilterClick(TObject *Sender)
{
    // ----
    ProcessImg("MedianFilter");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miCarveRilievoClick(TObject *Sender)
{
    // ----
    ProcessImg("CarveRilievo");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miImageReverClick(TObject *Sender)
{
    // ----
    ProcessImg("ImageRever");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miRotaTionClick(TObject *Sender)
{
    // ----
    ProcessImg("RotaTion");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miHSVTranslationClick(TObject *Sender)
{
    // ----
    ProcessImg("HSVTranslation");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miRGBTranslationClick(TObject *Sender)
{
    // ----
    ProcessImg("RGBTranslation");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miHistEnhanceClick(TObject *Sender)
{
    // ----
    ProcessImg("HistEnhance");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miAshTransClick(TObject *Sender)
{
    // ----
    ProcessImg("AshTrans");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miHelpFileClick(TObject *Sender)
{
    // --- 显示用户帮助文档 ---
    ShellExecute(Handle,"open","help.doc",NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miAboutAppClick(TObject *Sender)
{
    //---- 显示软件说明页面操作 ---
#include "AboutUnit.h"
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButton19Click(TObject *Sender)
{
    /* -----  test
    MessageBox(this->Handle ,"处理图像为空!" ,NULL ,MB_OK|MB_ICONWARNING);
    if(Image1->Parent==ScrollBox1)
        ShowMessage("Image1->Parent==ScrollBox1");
    else
        ShowMessage("Image1->Parent!=ScrollBox1");

    HBITMAP hDestBitmap = CallDllFunc("RotaTion" ,Image1->Picture->Bitmap->Handle);
    //DeleteObject(Image1->Picture->Bitmap->Handle);  //...
    Image1->Picture->Bitmap->Handle = hDestBitmap;
     */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    lblTime->Caption = Now();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ScrollBox1MouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    /*   //法二，发送消息    */
    if(this->WindowState!=wsMaximized)
    {
        //释放原有鼠标捕捉状态，
        //并同时送出鼠标单击位置等同于窗口标题栏可拖曳窗口的属性
        ::ReleaseCapture();
        SNDMSG(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
        //PostMessage(Handle ,WM_NCLBUTTONDOWN,HTCAPTION,0);
        //SendMessage(Handle ,WM_NCLBUTTONDOWN,HTCAPTION,0);
    }
}
//---------------------------------------------------------------------------

