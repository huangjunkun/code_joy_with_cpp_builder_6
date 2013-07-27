/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Region.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define MIN(X ,Y)   ((X<Y)? X:Y)
#define MAX(X ,Y)   ((X>Y)? X:Y)


TRForm *RForm;
//TPoint  GetLeftUpPt(const TPoint& p1 ,const TPoint& p2);
//---------------------------------------------------------------------------
__fastcall TRForm::TRForm(TComponent* Owner)
    : TForm(Owner)
{
    iWhichShapeDraw = 0;
    tbRectangle->Tag = 1;
    tbRound->Tag = 2;
    tbWord->Tag = 3;
    tbLine->Tag = 4;
    tbRoundRect->Tag = 5;
    shapeTemp = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TRForm::FormCreate(TObject *Sender)
{
    RForm->DoubleBuffered = true;
    //plImage2->DoubleBuffered = true;
    this->ShowHint = true;
    SetBounds(0, 0, Screen->Width, Screen->Height);
    // 初始化 Image2 最大画布 Canvas范围 ....
    //Image2->Width = Screen->Width;
    //Image2->Height = Screen->Height;
    //Image2->Picture->Assign(NULL);
    //Image2->Canvas->FillRect(Image2->Canvas->ClipRect);
    Image2->Cursor = TCursor(crPen_);
    Image2->AutoSize = true;

    InitAllPenBrush();// ....
}
//---------------------------------------------------------------------------
void __fastcall TRForm::FormShow(TObject *Sender)
{
    //  ----    //初始化画图区域相关数据
    InitRegionCapture();
}
//---------------------------------------------------------------------------
void __fastcall TRForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    // .... this->Visible = false ,没有触发 ！！！！
    //ShowMessage("TRForm::FormClose");
    MainForm->Visible=true;
    Action = caHide; //...
}
//---------------------------------------------------------------------------
void __fastcall TRForm::FormDestroy(TObject *Sender)
{
    delete TRectangle::curPen;
    delete TRectangle::curBrush;
    delete TRound::curPen;
    delete TRound::curBrush;
    delete TLine::curPen;
    delete TLine::curBrush;
    delete TRoundRect::curPen;
    delete TRoundRect::curBrush;
}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbExitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
/*
TPoint  GetLeftUpPt(const TPoint& p1 ,const TPoint& p2)
{
    return  TPoint(MIN(p1.x ,p2.x) ,MIN(p1.y ,p2.y));
}       */
//---------------------------------------------------------------------------
void __fastcall TRForm::Image1MouseDown(TObject *Sender,
                                        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //ShowMessage("Image1MouseDown");
    if(Button==mbLeft)
    {
        leftDownPt = Point(X, Y);
        if(!bIsRegionSelected)
            movePt = originPt = leftDownPt;
        bLeftMDown = true;   /*
        if(Image1->Cursor!=TCursor(crCursor_))
            bCursorFlag = true;  */
    }
    else if(Button==mbRight&&bIsRegionSelected &&
            Image1->Cursor != TCursor(crSizeAll_)) //crSizeAll
    {
        // 清除选中区域，可以重新选择
        /*   */
        DrawRect(originPt, movePt, pmNotXor);
        InitRegionCapture(); //还原画图区域相关数据
        Image1->Repaint(); // .....
    }
    else if(Button==mbRight&&!bIsRegionSelected)
    {
        // Exit ...   //还原画图区域相关数据
        //InitRegionCapture();
        Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TRForm::Image1MouseMove(TObject *Sender, TShiftState Shift,
                                        int X, int Y)
{
    if (bLeftMDown&&!bIsRegionSelected)
    {
        DrawRect(originPt, movePt, pmNotXor);
        movePt = Point(X, Y);
        movePt.x=movePt.x+Image1->Left;
        movePt.y=movePt.y+Image1->Top;
        DrawRect(originPt, movePt, pmNotXor);

        //this->ShowHint = true;
        this->Hint = "Width: " + IntToStr(abs(originPt.x-X)) +
                     "  , Height: " + IntToStr(abs(originPt.y-Y));
    }
    else if(!bLeftMDown&&bIsRegionSelected) //
    {
        // -----------------
        ShowCusorOnImg(X ,Y);
    }
    else if(bLeftMDown&& vecShapes.empty()) // && No Draw
        HandleSelRect(X ,Y);

    ShowlblCapture(X ,Y ,abs(movePt.x-originPt.x) ,abs(movePt.y-originPt.y) , \
                   Image1->Canvas->Pixels[X][Y]);
}
//---------------------------------------------------------------------------
void __fastcall TRForm::Image1MouseUp(TObject *Sender, TMouseButton Button,
                                      TShiftState Shift, int X, int Y)
{
    /*---  */  //ShowMessage("Image1MouseUp");
    if(Button==mbLeft)
    {
        bLeftMDown = false;
        bIsRegionSelected = true;
        SetSelectedRt(); // 记录选择区域 -
        //TPoint  ptLU =  GetLeftUpPt(originPt ,movePt);

        lblCapture->Left = selectedRt.Left>0 ? selectedRt.Left:0;
        int     top =  selectedRt.Top-lblCapture->Height;
        lblCapture->Top = top>0 ? top:0;
        //lblCapture->Visible = true; //可略 ...
        if(CoolBar1->Visible)
        {
            int     left = selectedRt.right-CoolBar1->Width;
            CoolBar1->Left = left>0 ? left:0;
            top = selectedRt.bottom;
            CoolBar1->Top = top>0 ? top:0;
            //CoolBar1->Visible = true; //可略
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TRForm::Image1DblClick(TObject *Sender)
{
    //ShowMessage("Image1DblClick");
    if (bIsRegionSelected)
    {
        bIsRegionSelected=false; //...
        CaptureRegion();
    }
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbRectangleClick(TObject *Sender)
{
    TToolButton*    tbPtr = (TToolButton*)Sender;
    if(tbPtr->Tag==iWhichShapeDraw)
    {
        // 重复选择同一个 ToolButton 弹起
        if(shapeTemp!=NULL)
        {
            delete shapeTemp;
            shapeTemp = NULL;
        }
        tbPtr->Down = false;
        iWhichShapeDraw = 0;//,0--No Draw
        if(vecShapes.empty())
        {
            Image2->Visible = false;
            Image1->Repaint();
        }
        return;
    }   /*   */
    tbRectangle->Down = false;
    tbRound->Down = false;
    tbWord->Down = false;
    tbLine->Down = false;
    tbRoundRect->Down = false;
    tbPtr->Down = true;
    iWhichShapeDraw = tbPtr->Tag;
// ....
    if(vecShapes.empty())
    {
        /*
         Image2->Width = selectedRt.Width();
         Image2->Height = selectedRt.Height();
         //Image2->Canvas->FillRect(selectedRt);//->Picture->Bitmap
         Image2->Canvas->CopyRect(TRect(0 ,0 ,Image2->Width ,Image2->Height) , \
                                       Image1->Canvas ,selectedRt);
         */
        Graphics::TBitmap *bmp = new Graphics::TBitmap;
        bmp->Width = selectedRt.Width();
        bmp->Height = selectedRt.Height();
        bmp->Canvas->CopyRect(TRect(0 ,0 ,bmp->Width ,bmp->Height) , \
                              Image1->Canvas ,selectedRt);
        Image2->Picture->Assign(bmp);
        Image2->Left = selectedRt.Left;
        Image2->Top = selectedRt.Top;
        delete bmp;
        Image2->Visible = true;
    }

}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbUndoClick(TObject *Sender)
{
    if(!vecShapes.empty())
    {
        vector<TShape_*>::iterator  it = vecShapes.end()-1;
        (*it)->Clear(Image2->Canvas); // 先擦除画布上的内容
        delete  *it;// 析构 new 变量 ....
        vecShapes.erase(it);
        if(vecShapes.empty())
        {
            //  ShowMessage("vecShapes.empty()");
            Image2->Visible = false;
            {
                iWhichShapeDraw = 0;
                tbRectangle->Down = false;
                tbRound->Down = false;
                tbWord->Down = false;
                tbLine->Down = false;
                tbRoundRect->Down = false;
            }
            Image1->Repaint();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TRForm::Image2MouseDown(TObject *Sender,
                                        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
        bLeftMDown_ = true;
        leftDownPt.x = X;
        leftDownPt.y = Y;
        switch(iWhichShapeDraw)
        {
        case 1 : //tbRectangle->Tag
            shapeTemp = new TRectangle();
            break;
        case 2 ://tbRound->Tag
            shapeTemp = new TRound();
            break;
        case 3 ://tbWord->Tag
        {
            shapeTemp = new TWord();
            shapeTemp->GetLeftTop() = leftDownPt;
            editWord->Font = TWord::curFont;
            editWord->Left = X+Image2->Left;
            editWord->Top = Y+Image2->Top;
            editWord->Visible = true;
            //editWord->Show();
            editWord->Focused(); //....
            Image2->Repaint();
            break;
        }
        case 4 ://tbLine->Tag
            shapeTemp = new TLine();
            break;
        case 5 ://tbRoundRect->Tag
            shapeTemp = new TRoundRect();
            break;
        default:
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::Image2MouseMove(TObject *Sender, TShiftState Shift,
                                        int X, int Y)
{
    if(bLeftMDown_&&shapeTemp&&iWhichShapeDraw!=3)
    {
        shapeTemp->Clear(Image2->Canvas);
        shapeTemp->SetRect(leftDownPt,TPoint(X ,Y));
        shapeTemp->Draw(Image2->Canvas);
    }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::Image2MouseUp(TObject *Sender, TMouseButton Button,
                                      TShiftState Shift, int X, int Y)
{
    if(iWhichShapeDraw==3)  // 写文字
        editWord->Focused(); //....
    else if(bLeftMDown_&&shapeTemp)
    {
        // ShowMessage("vecShapes.push_back(shapeTemp);");
        vecShapes.push_back(shapeTemp);
        shapeTemp = NULL; //...
        bLeftMDown_ = false;
        Image2->Repaint();
    }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbOKCaptureClick(TObject *Sender)
{
    // ............copy image to clipboard....
    //Clipboard()->Open();
    unsigned DataHandle; // int error!!!!
    HPALETTE APalette;
    unsigned short MyFormat;  //=CF_BITMAP
    Graphics::TBitmap *Bitmap = new Graphics::TBitmap();
    Bitmap->Width = selectedRt.Width();
    Bitmap->Height = selectedRt.Height();
    /* */
    try
    {
        if(Image2->Visible)// copy from Image2
            Bitmap->Canvas->CopyRect(Bitmap->Canvas->ClipRect ,Image2->Canvas ,
                                     TRect(0 ,0 ,selectedRt.Width() ,selectedRt.Height()));
        else // copy from Image1
            Bitmap->Canvas->CopyRect(Bitmap->Canvas->ClipRect ,Image1->Canvas ,selectedRt);
        Bitmap->SaveToClipboardFormat(MyFormat,DataHandle,APalette); //
        Clipboard()->SetAsHandle(MyFormat,DataHandle);
    }
    catch (Exception& e)
    {
        ShowMessage("Failed to copy image to clipboard!");
    }
    delete Bitmap;
    Image1DblClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::Image2DblClick(TObject *Sender)
{
    //    ShowMessage(" TRForm::Image2DblClick");
}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbFontClick(TObject *Sender)
{
    if(FontDialog1->Execute())
    {
        TWord::curFont = RForm->FontDialog1->Font;
    }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::tbSetPenBrushClick(TObject *Sender)
{
    if(panelPenBrush->Visible)
    {
        panelPenBrush->Visible = false;
        return;
    }
    switch(iWhichShapeDraw)
    {
        /*   */
    case 1 :
        curSetPen = TRectangle::curPen;
        curSetBrush = TRectangle::curBrush;
        break;
    case 2 :
        curSetPen = TRound::curPen;
        curSetBrush = TRound::curBrush;
        break;
    case 4 :
        curSetPen = TLine::curPen;
        curSetBrush = TLine::curBrush;
        break;
    case 5 :
        curSetPen = TRoundRect::curPen;
        curSetBrush = TRoundRect::curBrush;
        break;
    default:
        return; //error
    }
    ShowPenBrush(curSetPen , curSetBrush);

    panelPenBrush->Left = CoolBar1->Left;
    panelPenBrush->Top = CoolBar1->Top+CoolBar1->Height;
    panelPenBrush->Visible = true;

}
//---------------------------------------------------------------------------
void __fastcall TRForm::btnSetPBOKClick(TObject *Sender)
{
    //
    SetCurPenBrush(curSetPen , curSetBrush);
    panelPenBrush->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TRForm::FormKeyDown(TObject *Sender, WORD &Key,
                                    TShiftState Shift)
{
    if(!bIsRegionSelected)
        return;
    if(Shift.Contains(ssShift)) //
        switch(Key)
        {
        case VK_UP:
            ResizeSelectedRt(0 ,-2);
            break;
        case VK_DOWN:
            ResizeSelectedRt(0 ,2);
            break;
        case VK_LEFT:
            ResizeSelectedRt(-2 ,0);
            break;
        case VK_RIGHT:
            ResizeSelectedRt(2 ,0);
            break;
        default:
            return;
        }
    else if(Shift.Contains(ssCtrl))
        switch(Key)
        {
        case VK_UP:
            MoveSelectedRt(0 ,-2);
            break;
        case VK_DOWN:
            MoveSelectedRt(0 ,2);
            break;
        case VK_LEFT:
            MoveSelectedRt(-2 ,0);
            break;
        case VK_RIGHT:
            MoveSelectedRt(2 ,0);
            break;
        default:
            return;
        }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::editWordKeyPress(TObject *Sender, char &Key)
{
    if(Key==13)
    {
        if(!editWord->Text.IsEmpty())
        {
            TWord* wordPtr = (TWord*)shapeTemp; //???
            wordPtr->text = editWord->Text;
            wordPtr->Draw(Image2->Canvas);
            vecShapes.push_back(shapeTemp);
        }
        else
            delete shapeTemp;
        shapeTemp = NULL;
        bLeftMDown = false;
        editWord->Text = "";
        editWord->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRForm::tbSaveAsClick(TObject *Sender)
{
    SaveDialog1->FileName = "";
    SaveDialog1->Title = "图像另存为...";
    if(SaveDialog1->Execute())  //
    {
        Graphics::TBitmap *bmp = new Graphics::TBitmap;
        bmp->Width = selectedRt.Width();
        bmp->Height = selectedRt.Height();
        if(Image2->Visible)//
            bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,Image2->Canvas , \
                                  TRect(0 ,0 ,Image2->Width ,Image2->Height));
        else
            bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,Image1->Canvas , \
                                  selectedRt);
        SaveAsImage(bmp ,SaveDialog1->FilterIndex ,SaveDialog1->FileName);
        delete  bmp;
    }
    /* */
}
//---------------------------------------------------------------------------
void    TRForm::SaveAsImage(Graphics::TBitmap* bmp ,int imgExt ,String fileName)
{
    /*--  */
    switch(imgExt)
    {
    case 1 : //jpg
    {
        fileName = fileName + ".jpg";
        TJPEGImage    *imagejpg = new TJPEGImage; //
        imagejpg->Assign(bmp);
        imagejpg->CompressionQuality = 100;//压缩质量 。。。。
        imagejpg->Compress();  //执行压缩 、、、、
        imagejpg->SaveToFile(fileName);
        delete imagejpg;
        break;
    }
    case 2 : //bmp
    {
        fileName = fileName + ".bmp";
        bmp->SaveToFile(fileName);   //不必处理
        break;
    }
    case 3 : //ico
    {
        fileName = fileName + ".ico";
        TImageList  *imgList = new TImageList(this);
        imgList->Width = bmp->Width;
        imgList->Height = bmp->Height;
        imgList->Add(bmp ,NULL);
        TIcon*  icon = new TIcon;
        icon->Width = imgList->Width;
        icon->Height = imgList->Height;
        imgList->GetIcon(0 ,icon);
        icon->SaveToFile(fileName);

        delete icon;
        delete imgList;
        break;
    }
    case 4 ://wmf
    {
        fileName = fileName + ".wmf";
        Graphics::TMetafile *imagewmf = new Graphics::TMetafile;
        imagewmf->Width = bmp->Width;
        imagewmf->Height = bmp->Height;
        TMetafileCanvas *pCanvas = new TMetafileCanvas(imagewmf, 0);
        pCanvas->Draw(0 ,0 ,bmp);
        delete pCanvas;
        imagewmf->SaveToFile(fileName);
        delete imagewmf;
        break;
    }
    default:
        break; // error
    }
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miAddRectangleClick(TObject *Sender)
{
    tbRectangleClick(tbRectangle);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miAddRoundClick(TObject *Sender)
{
    tbRectangleClick(tbRound);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miaddWordClick(TObject *Sender)
{
    tbRectangleClick(tbWord);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miAddLineClick(TObject *Sender)
{
    tbRectangleClick(tbLine);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miAddRoundRectClick(TObject *Sender)
{
    tbRectangleClick(tbRoundRect);
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miShowHideTBClick(TObject *Sender)
{
    if(!CoolBar1->Visible)
    {
        int     left = selectedRt.right-CoolBar1->Width;
        CoolBar1->Left = left>0 ? left:0;
        int     top = selectedRt.bottom;
        CoolBar1->Top = top>0 ? top:0;
    }
    CoolBar1->Visible = !CoolBar1->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TRForm::miReCaptureClick(TObject *Sender)
{
    DrawRect(originPt, movePt, pmNotXor);
    InitRegionCapture(); //还原画图区域相关数据
    Image1->Repaint(); // .....
}
//---------------------------------------------------------------------------

