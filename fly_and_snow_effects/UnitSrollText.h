//---------------------------------------------------------------------------

#ifndef UnitSrollTextH
#define UnitSrollTextH
//---------------------------------------------------------------------------
class TSrollText
{
private:
    TPaintBox*  paintBox;
    TTimer*     srollTimer;
    TStringList*    srollText;
    // ---------
    RECT *StringRectangles;
    int *StringColorIndexs;
    int StringColorCount;
    COLORREF **StringColors;
    TCursor *StringCursors;
    typedef void __fastcall (__closure *PFNOnClick)(TObject *);
    PFNOnClick *StringOnClicks;
    int StringCount;
    int StringMaximumWidth;
    int StringsHeight;
    int CurrentStringIndex;
    int PictureTop;
    // --- function
    void __fastcall DrawAboutFlash();
protected:
    void __fastcall srollOnTimer(TObject *Sender);
    void __fastcall paintBoxClick(TObject *Sender);
    void __fastcall paintBoxMouseMove(TObject *Sender,
                                      TShiftState Shift, int X, int Y);
    void __fastcall LabelEMailClick(TObject *Sender);
    void __fastcall LabelHomePageClick(TObject *Sender);

public:
    enum { defaultSrollSpeed = 100 };
    TSrollText(TWinControl* AOwner ,TStringList* Text);
    ~TSrollText();
    void initSrollText();
    TTimer* getSrollTimer() const
    {
        return srollTimer;
    }
    TPaintBox* getPaintBox() const
    {
        return paintBox;
    }
    void setPosition(const TPoint& pt)
    {
        paintBox->Left = pt.x;
        paintBox->Top = pt.y;
    }
    void updateText(TStringList* Text)
    {
        srollText->Assign(Text);
        initSrollText();
    }
    void doSrollText() // move Sroll ...
    {
        srollTimer->Enabled = true;
        paintBox->Visible = true;
    }
    void stopSrollText()
    {
        srollTimer->Enabled = false;
        paintBox->Visible = false;
    }

};
TSrollText::TSrollText(TWinControl* AOwner ,TStringList* Text)
{
    paintBox = new TPaintBox(AOwner);
    paintBox->Parent = AOwner;
    paintBox->OnMouseMove = paintBoxMouseMove;
    paintBox->OnClick = paintBoxClick;
    srollTimer = new TTimer(AOwner);
    srollTimer->Enabled = false;
    srollTimer->Interval = defaultSrollSpeed;// ...
    srollTimer->OnTimer = srollOnTimer;
    srollText = new TStringList;
    srollText->Assign(Text);
    initSrollText();
}
TSrollText::~TSrollText()
{
    if(StringColors)
        for(int i=0; i<StringColorCount; i++)
        {
            delete[] StringColors[i];
        }
    if(StringColors)        delete[] StringColors;
    if(StringOnClicks)      delete[] StringOnClicks;
    if(StringCursors)       delete[] StringCursors;
    if(StringColorIndexs)   delete[] StringColorIndexs;
    if(StringRectangles)    delete[] StringRectangles;

    if(srollText)   delete srollText;
    if(srollTimer)  delete srollTimer;
    if(paintBox)    delete paintBox;
}
void TSrollText::initSrollText()
{
    AnsiString  S;
    int width,height;
    int i ;
    srollText->Add("E-Mail :");
    srollText->Add("only.hjky@yahoo.com.cn");
    srollText->Add("The Home Page :");
    srollText->Add("http://user.qzone.qq.com/410746866/");
    StringCount=srollText->Count;
    StringColorCount = 3;
    StringRectangles=new RECT[StringCount];
    StringColorIndexs=new int[StringCount];
    StringCursors=new TCursor[StringCount];
    StringOnClicks = new PFNOnClick[StringCount];
    StringMaximumWidth = 0;
    StringsHeight = 0;
    for(int i=0; i<srollText->Count; i++)
    {
        StringColorIndexs[i] = 2;
        StringCursors[i]=crDefault;
        StringOnClicks[i]=NULL;
        S=srollText->Strings[i];
        width=paintBox->Canvas->TextWidth(S);
        height=paintBox->Canvas->TextHeight(S);
        if(width>StringMaximumWidth)
            StringMaximumWidth = width;
        StringsHeight+=height;
    }  /*   */
    StringCursors[srollText->Count-3]=crHandPoint;
    StringOnClicks[srollText->Count-3]=LabelEMailClick;
    StringCursors[srollText->Count-1]=crHandPoint;
    StringOnClicks[srollText->Count-3]=LabelHomePageClick;

    double s0,s1;
    COLORREF color0,color1;
    BYTE r0,g0,b0,r1,g1,b1;
    int j;
    int s;
    height=paintBox->Height;
    color0=ColorToRGB(clBlack);
    r0=GetRValue(color0);
    g0=GetGValue(color0);
    b0=GetBValue(color0);
    StringColors=new COLORREF*[StringColorCount];
    s=(height+1)>>1;
    for(i=0; i<StringColorCount; i++)
    {
        if(i==0)    color1=ColorToRGB(clYellow);
        if(i==1)    color1=ColorToRGB(clWhite);
        if(i==2)    color1=ColorToRGB(clLime);
        r1=GetRValue(color1);
        g1=GetGValue(color1);
        b1=GetBValue(color1);
        StringColors[i]=new COLORREF[height];
        for(j=0; j<s; j++)
        {
            s0=(double)(s-j)/s;
            s1=(double)j/s;
            StringColors[i][height-j-1]=StringColors[i][j]=RGB(r0*s0+r1*s1,g0*s0+g1*s1,b0*s0+b1*s1);
        }
    }
    PictureTop=s;
    CurrentStringIndex=-1;
    int left,top;
    top=0;
    for(i=0; i<StringCount; i++)
    {
        S=srollText->Strings[i];
        if(!S.IsEmpty())
        {
            width=paintBox->Canvas->TextWidth(S);
            height=paintBox->Canvas->TextHeight(S);
            left=(StringMaximumWidth-width)>>1;
            StringRectangles[i].left=left;
            StringRectangles[i].right=left+width;
            StringRectangles[i].top=top;
            StringRectangles[i].bottom=top+height;
            top+=height;
        }
    }
    paintBox->Width = StringMaximumWidth;
    //paintBox->Height = 200;
    //paintBox->Left=(Screen->Width-StringMaximumWidth)>>1;//paintBox->Parent->Width ...
    //paintBox->Top=0;//(Screen->Height-paintBox->Height);//paintBox->Parent->Height ...
    // сроб╫г
    //setPosition(TPoint((Screen->Width-StringMaximumWidth)-10 , // \
    //                   (Screen->Height-paintBox->Height)-30));
    setPosition(TPoint((Screen->Width-StringMaximumWidth),10));//срио╫г
}
void __fastcall TSrollText::srollOnTimer(TObject *Sender)
{
    DrawAboutFlash();
    PictureTop-=1;
    if(PictureTop+StringsHeight<=0)
    {
        PictureTop=paintBox->Height-1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TSrollText::DrawAboutFlash()
{
    Graphics::TBitmap *Bitmap=new Graphics::TBitmap();
    int width,height;
    int texttop;
    int textwidth,textheight;
    int x,y,k;
    int y0,y1;
    BYTE *p;
    int colorindex;
    COLORREF color;
    int top,bottom;
    int i;

    width=paintBox->Width;
    height=paintBox->Height;
    Bitmap->PixelFormat=pf24bit;
    Bitmap->Width=width;
    Bitmap->Height=height;
    Bitmap->Canvas->Pen->Color=clBlack;
    Bitmap->Canvas->Brush->Color=clBlack;
    Bitmap->Canvas->Rectangle(0,0,width,height);
    Bitmap->Canvas->Font->Color=clWhite;

    top=0;
    bottom=paintBox->Height;
    top-=PictureTop;
    bottom-=PictureTop;
    for(i=0; i<StringCount; i++)
    {
        if(StringRectangles[i].top>=top && StringRectangles[i].top<=bottom || \
                StringRectangles[i].bottom>=top && StringRectangles[i].bottom<=bottom)
        {
            Bitmap->Canvas->TextOutA(StringRectangles[i].left,StringRectangles[i].top+PictureTop,srollText->Strings[i]);
            colorindex=StringColorIndexs[i];
            textwidth=StringRectangles[i].right-StringRectangles[i].left;
            textheight=StringRectangles[i].bottom-StringRectangles[i].top;
            texttop=StringRectangles[i].top+PictureTop;
            y0=texttop;
            if(y0<0)    y0=0;
            if(y0>height)   y0=height;
            y1=texttop+textheight;
            if(y1<0)    y1=0;
            if(y1>height)   y1=height;
            for(y=y0; y<y1; y++)
            {
                color=StringColors[colorindex][y];
                p=(BYTE *)Bitmap->ScanLine[y];
                p+=StringRectangles[i].left*3;
                for(x=0; x<textwidth; x++)
                {
                    k=x+x+x;
                    if(p[k]==0xff)
                    {
                        p[k]=GetBValue(color);
                        p[k+1]=GetGValue(color);
                        p[k+2]=GetRValue(color);
                    }
                    else
                    {
                        p[k]=GetBValue(ColorToRGB(clBlack));
                        p[k+1]=GetGValue(ColorToRGB(clBlack));
                        p[k+2]=GetRValue(ColorToRGB(clBlack));
                    }
                }
            }
        }
    }
    paintBox->Canvas->Draw(0,0,Bitmap);
    Bitmap->Dormant();
    Bitmap->FreeImage();
    delete Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TSrollText::paintBoxClick(TObject *Sender)
{
    PFNOnClick pfnOnClick;
    if(CurrentStringIndex>=0)
    {
        if(StringOnClicks[CurrentStringIndex]!=NULL)
        {
            pfnOnClick=(PFNOnClick)StringOnClicks[CurrentStringIndex];
            pfnOnClick(Sender);
        }
    }
    //srollTimer->Enabled = true;  /* */
}
//---------------------------------------------------------------------------
void __fastcall TSrollText::paintBoxMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    //srollTimer->Enabled=false;  /* */
    int     i;
    CurrentStringIndex=-1;
    for(i=0; i<StringCount; i++)
    {
        if(X>=StringRectangles[i].left && X<StringRectangles[i].right && \
                Y-PictureTop>=StringRectangles[i].top && Y-PictureTop<StringRectangles[i].bottom)
        {
            paintBox->Cursor=StringCursors[i];
            CurrentStringIndex=i;
            break;
        }
    }
}  //---------------------------------------------------------------------------
void __fastcall TSrollText::LabelEMailClick(TObject *Sender)
{
    AnsiString EMailAddress;
    if(CurrentStringIndex>=0)
    {
        EMailAddress="mailto:"+srollText->Strings[CurrentStringIndex]+"?subject=Hello &body=[©у]";
        ShellExecuteA(Application->Handle,"open",EMailAddress.c_str(),NULL,NULL,SW_SHOWNORMAL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSrollText::LabelHomePageClick(TObject *Sender)
{
    /*
     if(CurrentStringIndex>=0)
     {
       ShellExecuteA(Application->Handle,"open",srollText->Strings[CurrentStringIndex].c_str(),\
         NULL,NULL,SW_SHOWNORMAL);
     }      */
    AnsiString WebsiteAddress;
    AnsiString S;
    char url[MAX_PATH];
    char *pstring0,*pstring1;

    if(CurrentStringIndex>=0)
    {
        strcpy(url,srollText->Strings[CurrentStringIndex].c_str());
        pstring0=url;
        pstring1=strstr(pstring0,"(");
        if(pstring1!=NULL)
        {
            pstring0=pstring1+1;
            pstring1=strstr(pstring0,")");
            if(pstring1!=NULL)
                *pstring1='\0';
            WebsiteAddress="http://"+AnsiString(pstring0);
            ShellExecuteA(Application->Handle,"open",WebsiteAddress.c_str(),NULL,NULL,SW_SHOWNORMAL);

        }
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
