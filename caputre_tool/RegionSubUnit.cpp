/*
   * 程序开发者： 黄俊坤，蒙绍亮
   * 项目时间：开始日期:  2009-08. 结束日期:  2009-09
*/


//---------------------------------------------------------------------------
#include "Region.h"

//---------------------------------------------------------------------------
/*
TPen* TRectangle::curPen;
TBrush* TRectangle::curBrush;
TPen* TRound::curPen;
TBrush* TRound::curBrush;
TPen* TLine::curPen;
TBrush* TLine::curBrush;
TPen* TRoundRect::curPen;
TBrush* TRoundRect::curBrush;
TFont* TWord::curFont; //声明 FontDialog1
 */
TPen* TRectangle::curPen = new TPen;
TBrush* TRectangle::curBrush = new TBrush;
TPen* TRound::curPen = new TPen;
TBrush* TRound::curBrush = new TBrush;
TPen* TLine::curPen = new TPen;
TBrush* TLine::curBrush = new TBrush;
TPen* TRoundRect::curPen = new TPen;
TBrush* TRoundRect::curBrush = new TBrush;
TFont* TWord::curFont; //声明 FontDialog1

void TRectangle::Draw(TCanvas* pC)
{
    /*   */
    pC->Pen->Mode = pmNotXor;  // ...
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->Brush->Color = brush->Color;
    //pC->Brush->Style = brush->Style;
    pC->Rectangle(TRect(ptLeftTop ,ptRightBottom));   //
    /* */
}
//---------------------------------------------------------------------------
void TRectangle::Clear(TCanvas* pC)
{
    /**/
    //pC->Pen->Mode = pmXor;  // pmCopy
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->Brush->Color = brush->Color;
    pC->Brush->Style = bsClear;  /*  */
    pC->Rectangle(TRect(ptLeftTop ,ptRightBottom));
}
//---------------------------------------------------------------------------
void TRound::Draw(TCanvas* pC)
{
    pC->Pen->Mode = pmNotXor;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->Brush->Color = brush->Color;
    //pC->Brush->Style = brush->Style;
    pC->Ellipse(TRect(ptLeftTop ,ptRightBottom));
}
//---------------------------------------------------------------------------
void TRound::Clear(TCanvas* pC)
{
    pC->Brush->Color = brush->Color;
    pC->Brush->Style = bsClear;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->Ellipse(TRect(ptLeftTop ,ptRightBottom));
}
//---------------------------------------------------------------------------

void TLine::Draw(TCanvas* pC)
{
    pC->Pen->Mode = pmNotXor;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->MoveTo(ptLeftTop.x ,ptLeftTop.y);//
    pC->LineTo(ptRightBottom.x ,ptRightBottom.y);
}
//---------------------------------------------------------------------------
void TLine::Clear(TCanvas* pC)
{
    //pC->Pen->Mode = pmNotXor;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->MoveTo(ptLeftTop.x ,ptLeftTop.y);//
    pC->LineTo(ptRightBottom.x ,ptRightBottom.y);
}
//---------------------------------------------------------------------------
void TRoundRect::Draw(TCanvas* pC)
{
    pC->Pen->Mode = pmNotXor;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->Brush->Color = brush->Color; // ....
    pC->RoundRect(ptLeftTop.x ,ptLeftTop.y ,ptRightBottom.x ,ptRightBottom.y ,10 ,10);
}
//---------------------------------------------------------------------------
void TRoundRect::Clear(TCanvas* pC)
{
    pC->Brush->Color = brush->Color;
    pC->Brush->Style = bsClear;
    pC->Pen->Color = pen->Color;
    pC->Pen->Width = pen->Width;
    pC->Pen->Style = pen->Style;
    pC->RoundRect(ptLeftTop.x ,ptLeftTop.y ,ptRightBottom.x ,ptRightBottom.y ,10 ,10);
}
//---------------------------------------------------------------------------
void TWord::Draw(TCanvas* pC)
{
    bmp->Width = pC->ClipRect.Width();
    bmp->Height = pC->ClipRect.Height();
    bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,pC ,pC->ClipRect);

    pC->Font = font;
    pC->Brush->Style = bsClear;
    pC->TextOutA(ptLeftTop.x ,ptLeftTop.y ,text);
    TSize   size = pC->TextExtent(text); // ...
    ptRightBottom.x = ptLeftTop.x + size.cx;
    ptRightBottom.y = ptLeftTop.y + size.cy;
    //ShowMessage(String(size.cx)+" ,"+String(size.cy));
}
//---------------------------------------------------------------------------
void TWord::Clear(TCanvas* pC)
{
    pC->CopyRect(pC->ClipRect ,bmp->Canvas , \
                 bmp->Canvas->ClipRect);
    /* */
}
//---------------------------------------------------------------------------

// -----------------------TRForm TRForm TRForm ------------------------------
void  TRForm::CaptureRegion(void)
{
    //MainForm->Image1->Width=selectedRt.Width();//abs(movePt.x-originPt.x);
    //MainForm->Image1->Height=selectedRt.Height();//abs(movePt.y-originPt.y);
    //MainForm->Image1->Canvas->FillRect(MainForm->Image1->Canvas->ClipRect);
    if(Image2->Visible)// 发生截图编辑 ！vecShapes.empty()
        MainForm->Image1->Picture->Assign(Image2->Picture);//->Graphic
    else
    {
        if((movePt.x-originPt.x)!=0 && // selectedRt.Width()!=0
                (movePt.y-originPt.y)!=0)   // selectedRt.Height()!=0
        {
            Graphics::TBitmap   *bmp = new Graphics::TBitmap;
            bmp->Width = selectedRt.Width();
            bmp->Height = selectedRt.Height();
            bmp->Canvas->CopyRect(bmp->Canvas->ClipRect ,Image1->Canvas ,selectedRt);
            MainForm->Image1->Picture->Assign(bmp);
            delete  bmp;
            /*or:
            int Width=selectedRt.Width();
            int Height=selectedRt.Height();
            // 将桌面图像的指定区域拷贝到MainForm上的Image1中
            StretchBlt(MainForm->Image1->Canvas->Handle,
                       0,0,
                       Width,
                       Height,
                       Image1->Canvas->Handle,
                       selectedRt.Left,
                       selectedRt.Top,
                       Width,
                       Height,
                       SRCCOPY);     */
        }
    }
}
//---------------------------------------------------------------------------

void    TRForm::ShowlblCapture(int x ,int y ,int  w ,int h ,TColor c)
{
    // 区域大小:1024*1024         当前RGB:(255,255,255)      双击可以快速完成截图
    String  s0 = "指针位置:";
    String  s1 = "区域大小:";
    String  s2 = "当前RGB:";
    String  s3 = "双击可以快速完成截图";
    s0 = s0+String(x)+" ,"+String(y)+"\n";
    s1 = s1+String(w)+"*"+String(h)+"\n";
    s2 = s2+"("+String(GetRValue(c))+","+String(GetGValue(c))+","+String(GetBValue(c))+")\n";
    lblCapture->Caption = s0+s1+s2+s3;
}
//-----------------------------------------------------------------------------
void    TRForm::InitAllPenBrush()
{
    TRectangle::curPen->Assign(Image2->Canvas->Pen);
    TRectangle::curBrush->Assign(Image2->Canvas->Brush);
    TRound::curPen->Assign(Image2->Canvas->Pen);
    TRound::curBrush->Assign(Image2->Canvas->Brush);
    TLine::curPen->Assign(Image2->Canvas->Pen);
    TLine::curBrush->Assign(Image2->Canvas->Brush);
    TRoundRect::curPen->Assign(Image2->Canvas->Pen);
    TRoundRect::curBrush->Assign(Image2->Canvas->Brush);
    TWord::curFont = RForm->FontDialog1->Font;
}
//---------------------------------------------------------------------------
void    TRForm::InitRegionCapture()
{
    //ShowMessage("InitRegionCapture");
    Image1->Cursor = TCursor(crCursor_);  //TCursor(crCursor_)
    Image2->Visible = false;
    //CoolBar1->Visible = false;
    CoolBar1->Left = Screen->Width+10;
    CoolBar1->Top = Screen->Height+10;
    //lblCapture->Visible = false;
    lblCapture->Left = Screen->Width+10;
    lblCapture->Top = Screen->Height+10;
    panelPenBrush->Visible = false;
    editWord->Visible = false;

    iWhichShapeDraw = 0;
    tbRectangle->Down = false;
    tbRound->Down = false;
    tbWord->Down = false;
    tbLine->Down = false;
    tbRoundRect->Down = false;
    originPt.x = movePt.x = 0;
    originPt.y = movePt.y = 0;
    //selectedRt = TRect(0 ,0 ,0 ,0);
    bLeftMDown = bLeftMDown_ = bIsRegionSelected = false;

    vector<TShape_*>::iterator  it = vecShapes.begin();
    for(; it!=vecShapes.end(); it++)
        delete (*it);
    vecShapes.clear();
    if(shapeTemp!=NULL) // ...
    {
        delete shapeTemp;
        shapeTemp = NULL;
    }
    //Image1->Repaint();
}
//-----------------------------------------------------------------------------
void    TRForm::SetSelectedRt()
{
    if(originPt.x< movePt.x)
    {
        selectedRt.Left = originPt.x;
        selectedRt.Right = movePt.x;
    }
    else
    {
        selectedRt.Left = movePt.x;
        selectedRt.Right = originPt.x;
    }
    if(originPt.y< movePt.y)
    {
        selectedRt.Top = originPt.y;
        selectedRt.Bottom = movePt.y;
    }
    else
    {
        selectedRt.Top = movePt.y;
        selectedRt.Bottom = originPt.y;
    }
    originPt.x = selectedRt.left;
    originPt.y = selectedRt.top;
    movePt.x = selectedRt.right;
    movePt.y = selectedRt.bottom;

}
//---------------------------------------------------------------------------
void    TRForm::ShowCusorOnImg(int   X ,int  Y)
{
#define INV 3
    if((X>selectedRt.Left-INV&&X<selectedRt.Left+INV)&& \
            (Y>selectedRt.Top-INV&&Y<selectedRt.Top+INV))
    {
        Image1->Cursor = TCursor(crSizeNWSE_); //crSizeNWSE
        selectdPos = epLeftUp;
    }
    else if((X>selectedRt.Right-INV&&X<selectedRt.Right+INV)&& \
            (Y>selectedRt.Bottom-INV&&Y<selectedRt.Bottom+INV))
    {
        Image1->Cursor = TCursor(crSizeNWSE_); // crSizeNWSE
        selectdPos = epRightDown;
    }
    else if((X>selectedRt.Left-INV&&X<selectedRt.Left+INV)&& \
            (Y>selectedRt.Bottom-INV&&Y<selectedRt.Bottom+INV))
    {
        Image1->Cursor = TCursor(crSizeNESW_); // crSizeNESW
        selectdPos = epLeftDown;
    }
    else if((X>selectedRt.Right-INV&&X<selectedRt.Right+INV)&& \
            (Y>selectedRt.Top-INV&&Y<selectedRt.Top+INV))
    {
        Image1->Cursor = TCursor(crSizeNESW_); // crSizeNESW
        selectdPos = epRightUp;
    }
    else if(X>selectedRt.Left-INV&&X<selectedRt.Right+INV && \
            Y>selectedRt.Top-INV&&Y<selectedRt.Bottom+INV)
    {
        if(iWhichShapeDraw==0)
            Image1->Cursor = TCursor(crSizeAll_);//crSizeAll
        else
            Image1->Cursor = crCross;// ...

        Image1->PopupMenu = PopupMenu1;
    }
    else
    {
        Image1->Cursor = TCursor(crCursor_);  //TCursor(crCursor_)
        //Screen->Cursor = TCursor(crCursor_);// error ...
        Image1->PopupMenu = NULL;
    }
}
//---------------------------------------------------------------------------
void    TRForm::HandleSelRect(int   X ,int  Y)
{
    TPoint  temp(X ,Y);
    temp -= leftDownPt;
    switch(Image1->Cursor)
    {
    case TCursor(crSizeAll_): // crSizeAll
    {
        DrawRect(originPt, movePt, pmNotXor);
        //DrawRect(Point(selectedRt.left,selectedRt.top) ,
        //         Point(selectedRt.right,selectedRt.bottom) , pmNotXor);
        // 重新构造originPt movePt，左上角，右下角
        originPt = TPoint(selectedRt.left,selectedRt.top);
        originPt += temp;
        movePt = TPoint(selectedRt.right,selectedRt.bottom);
        movePt += temp;
        DrawRect(originPt, movePt, pmNotXor);
        break;
    }
    case TCursor(crSizeNWSE_): //crSizeNWSE
    {
        if(selectdPos==epLeftUp)
        {
            //ShowMessage("selectdPos==epLeftUp");
            DrawRect(originPt, movePt, pmNotXor);
            originPt = TPoint(selectedRt.right,selectedRt.bottom);
            movePt = TPoint(selectedRt.left,selectedRt.top);
            movePt += temp;
            DrawRect(originPt, movePt, pmNotXor);
        }
        else
        {
            DrawRect(originPt, movePt, pmNotXor);
            originPt = TPoint(selectedRt.left,selectedRt.top);
            movePt = TPoint(selectedRt.right,selectedRt.bottom);
            movePt += temp;
            DrawRect(originPt, movePt, pmNotXor);
        }
        break;
    }
    case TCursor(crSizeNESW_): // crSizeNESW
    {
        if(selectdPos==epLeftDown)
        {
            //ShowMessage("selectdPos==epLeftUp");
            DrawRect(originPt, movePt, pmNotXor);
            originPt = TPoint(selectedRt.right,selectedRt.top);
            movePt = TPoint(selectedRt.left,selectedRt.bottom);
            movePt += temp;
            DrawRect(originPt, movePt, pmNotXor);
        }
        else
        {
            DrawRect(originPt, movePt, pmNotXor);
            originPt = TPoint(selectedRt.left,selectedRt.bottom);
            movePt = TPoint(selectedRt.right,selectedRt.top);
            movePt += temp;
            DrawRect(originPt, movePt, pmNotXor);
        }
        break;
    }
    case crCross:
    {
        /*------ */
        break;
    }
    case TCursor(crCursor_):
        break;
    default :
        break;
    }
}
//---------------------------------------------------------------------------
void    TRForm::MoveSelectedRt(int  x ,int  y)
{
    if(selectedRt.left+x>Screen->Width||selectedRt.right+x<0 ||
            selectedRt.top+y>Screen->Height||selectedRt.bottom+y<0)
        return;
    DrawRect(TPoint(selectedRt.left,selectedRt.top) , \
              TPoint(selectedRt.right,selectedRt.bottom) , \
              pmNotXor);  //
    originPt.x = selectedRt.left += x;
    originPt.y = selectedRt.top += y;
    movePt.x = selectedRt.right += x;
    movePt.y = selectedRt.bottom += y;
    DrawRect(TPoint(selectedRt.left,selectedRt.top) , \
              TPoint(selectedRt.right,selectedRt.bottom) , \
              pmNotXor);
    {
        lblCapture->Left += x;
        lblCapture->Top += y;
        CoolBar1->Left += x;
        CoolBar1->Top += y;
    }
}
//---------------------------------------------------------------------------
void  TRForm::DrawRect(TPoint TopLeft, TPoint BottomRight, TPenMode Mode)
{
    /*      */
    Image1->Canvas->Pen->Mode = Mode;
    Image1->Canvas->Pen->Width = 2;
    Image1->Canvas->Brush->Style = bsClear;
    Image1->Canvas->Rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
}
//-----------------------------------------------------------------------------
void    TRForm::ResizeSelectedRt(int  x ,int  y)
{
    if(!(selectedRt.Width()+x>0 &&selectedRt.Height()+y>0))
        return;
    DrawRect(TPoint(selectedRt.left,selectedRt.top) , \
              TPoint(selectedRt.right,selectedRt.bottom) , \
              pmNotXor);

    originPt.x = selectedRt.left;
    originPt.y = selectedRt.top;
    movePt.x = selectedRt.right += x;
    movePt.y = selectedRt.bottom += y;
    DrawRect(TPoint(selectedRt.left,selectedRt.top) , \
              TPoint(selectedRt.right,selectedRt.bottom) , \
              pmNotXor);
    {
        CoolBar1->Left += x;
        CoolBar1->Top += y;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRForm::SetPenBrushColorClick(TObject *Sender)
{
    TBitBtn*    btnPtr = (TBitBtn*)Sender;
    if(ColorDialog1->Execute()) //  &&!iWhichShapeDraw
    {
        btnPtr->Font->Color = ColorDialog1->Color;
    }     /*---- */
}
//---------------------------------------------------------------------------
void    TRForm::ShowPenBrush(TPen* p ,TBrush* b)
{
    if(p==NULL||b==NULL)
    {
        ShowMessage("Error ,p==NULL||b==NULL !");
        return;
    }
    switch(p->Style)
    {
    case psSolid:
        cbPenStyle->ItemIndex = 0;
        break;
    case psDash:
        cbPenStyle->ItemIndex = 1;
        break;
    case psDot:
        cbPenStyle->ItemIndex = 2;
        break;
    case psDashDot:
        cbPenStyle->ItemIndex = 3;
        break;
    case psDashDotDot:
        cbPenStyle->ItemIndex = 4;
        break;
    case psClear:
        cbPenStyle->ItemIndex = 5;
    case psInsideFrame:
        cbPenStyle->ItemIndex = 6;
    default:
        break;
    }
    ShowMessage(String(p->Width));
    etPenWidth->Text = String(p->Width);
    btnPenColor->Font->Color = p->Color;
    btnBrushColor->Font->Color = b->Color;
}
//---------------------------------------------------------------------------
void    TRForm::SetCurPenBrush(TPen* p ,TBrush* b)
{
    //
    if(p==NULL||b==NULL)
    {
        ShowMessage("Error ,p==NULL||b==NULL !");
        return;
    }
    switch(cbPenStyle->ItemIndex)
    {
    case 0:
        p->Style = psSolid;
        break;
    case 1:
        p->Style = psDash;
        break;
    case 2:
        p->Style = psDot;
        break;
    case 3:
        p->Style = psDashDot;
        break;
    case 4:
        p->Style = psDashDotDot;
        break;
    case 5:
        p->Style = psClear;
    case 6:
        p->Style = psInsideFrame;
    default:
        break;
    }
    p->Width = etPenWidth->Text.ToInt();
    p->Color = btnPenColor->Font->Color;
    b->Color = btnBrushColor->Font->Color;
}
//---------------------------------------------------------------------------


