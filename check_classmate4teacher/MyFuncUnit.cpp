
#include "MainUnit.h"


// 记录系统分辨率 信息----
DEVMODE     lpDevMode;
bool    DevChange;

void    SetDisplay()
{
    /* //????????！！！！！！    */
    DEVMODE   lpDevMode;
    if(EnumDisplaySettings(NULL ,0 ,&lpDevMode))
    {
        //lpDevMode.dmFields   =   DM_PELSWIDTH | DM_PELSHEIGHT;
        //ShowMessage(String(lpDevMode.dmPelsWidth)+" ," +String(lpDevMode.dmPelsHeight));
        if(!(lpDevMode.dmPelsWidth==1280&&lpDevMode.dmPelsHeight==960)&&
                MessageDlg("修改系统分辨率：1280 ，960 "  ,mtInformation ,
                           TMsgDlgButtons()<<mbYes<<mbNo ,0)==mrYes)
        {
            DEVMODE   temp = lpDevMode;
            temp.dmFields   =   DM_PELSWIDTH | DM_PELSHEIGHT;
            temp.dmPelsWidth = 1280;
            temp.dmPelsHeight = 960;
            if(ChangeDisplaySettings(&temp ,CDS_UPDATEREGISTRY)==DISP_CHANGE_SUCCESSFUL)
                //ShowMessage("DISP_CHANGE_SUCCESSFUL");

                DevChange = true;
            //this->WindowState = wsMaximized;
            //ShowMessage("ChangeDisplaySettings");
        }
    }
}
void    ResetDisplay()
{
    //????????????没有效果 ！！！！！！
    if(DevChange)
    {
        lpDevMode.dmFields   =   DM_PELSWIDTH | DM_PELSHEIGHT;
        ChangeDisplaySettings(&lpDevMode ,CDS_UPDATEREGISTRY);
        //MessageDlg("ChangeDisplaySettings" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
    }
}
//---------------------------------------------------------------------------
void    ReadRecord(TControl* control ,String filename)
{
    ifstream    fin;
    fin.open(filename.c_str()); //"ClassBook.txt"
    if(!fin.fail())
    {
        //char    str[50];
        //int     i =0;
        string  str;
        while(!fin.eof())
        {
            //fin.getline(str ,50);
            getline(fin ,str ,'\n');// getline(fin ,string)
            String  Temp = String(str.c_str()).Trim();
            if(Temp=="")
                break;//过滤空白学生信息
            if(String(control->ClassName())=="TMemo")
                static_cast<TMemo*>(control)->Lines->Add(Temp);
            else if(String(control->ClassName())=="TListBox")
                static_cast<TListBox*>(control)->Items->Add(Temp);
            else
                break;
        }
    }
    fin.close();
}
//---------------------------------------------------------------------------
void    TMainForm::InitScrollWords()
{
    bShowWord = true;
    AnsiString S;
    int width,height;
    int i;
    AboutStringList=new TStringList();
    try
    {
        AboutStringList->LoadFromFile("ShowWords.txt");
    }
    catch(...)
    {
        MessageDlg("请将 ShowWords.txt 拷贝到同一目录 ！" ,mtWarning ,TMsgDlgButtons()<<mbOK ,0);
        PaintBoxAbout->Align = alClient;
        TimerFlash->Enabled = false;
        bShowWord = false;
    }
    //PaintBoxAbout->Canvas->Font->Size = 15;
    StringCount=AboutStringList->Count;
    StringColorCount = 3;
    StringRectangles=new RECT[StringCount];
    StringColorIndex=new int[StringCount];
    StringCursors=new TCursor[StringCount];
    StringOnClicks=new PFNOnClick[StringCount];

    StringMaximumWidth = 0;
    StringsHeight = 0;
    for(int i=0; i<AboutStringList->Count; i++)
    {
        StringColorIndex[i] = 2;
        StringCursors[i]=crDefault;
        StringOnClicks[i]=NULL;
        S=AboutStringList->Strings[i];
        width=PaintBoxAbout->Canvas->TextWidth(S);
        height=PaintBoxAbout->Canvas->TextHeight(S);
        if(width>StringMaximumWidth)
        {
            StringMaximumWidth = width;
        }
        StringsHeight+=height;
    }  /*   */
    double s0,s1;
    COLORREF color0,color1;
    BYTE r0,g0,b0,r1,g1,b1;
    int j;
    int s;
    height=PaintBoxAbout->Height;
    color0=ColorToRGB(clBlack);
    r0=GetRValue(color0);
    g0=GetGValue(color0);
    b0=GetBValue(color0);
    StringColors=new COLORREF*[StringColorCount];
    s=(height+1)>>1;
    for(i=0; i<StringColorCount; i++)
    {
        if(i==0)
        {
            color1=ColorToRGB(clYellow);
        }
        if(i==1)
        {
            color1=ColorToRGB(clWhite);
        }
        if(i==2)
        {
            color1=ColorToRGB(clLime);
        }
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
        S=AboutStringList->Strings[i];
        if(!S.IsEmpty())
        {
            width=PaintBoxAbout->Canvas->TextWidth(S);
            height=PaintBoxAbout->Canvas->TextHeight(S);
            left=(StringMaximumWidth-width)>>1;
            StringRectangles[i].left=left;
            StringRectangles[i].right=left+width;
            StringRectangles[i].top=top;
            StringRectangles[i].bottom=top+height;
            top+=height;
        }
    }
    PaintBoxAbout->Left=(MainForm->Width-StringMaximumWidth)>>1;
    PaintBoxAbout->Width = StringMaximumWidth;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawAboutFlash(TObject *Sender)
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

    width=PaintBoxAbout->Width;
    height=PaintBoxAbout->Height;
    Bitmap->PixelFormat=pf24bit;
    Bitmap->Width=width;
    Bitmap->Height=height;

    Bitmap->Canvas->Pen->Color=clBlack;
    Bitmap->Canvas->Brush->Color=clBlack;
    Bitmap->Canvas->Rectangle(0,0,width,height);

    Bitmap->Canvas->Font->Color=clWhite;

    top=0;
    bottom=PaintBoxAbout->Height;
    top-=PictureTop;
    bottom-=PictureTop;
    for(i=0; i<StringCount; i++)
    {
        if(StringRectangles[i].top>=top && StringRectangles[i].top<=bottom || StringRectangles[i].bottom>=top && StringRectangles[i].bottom<=bottom)
        {
            Bitmap->Canvas->TextOutA(StringRectangles[i].left,StringRectangles[i].top+PictureTop,AboutStringList->Strings[i]);
            colorindex=StringColorIndex[i];
            textwidth=StringRectangles[i].right-StringRectangles[i].left;
            textheight=StringRectangles[i].bottom-StringRectangles[i].top;
            texttop=StringRectangles[i].top+PictureTop;
            y0=texttop;
            if(y0<0)
            {
                y0=0;
            }
            if(y0>height)
            {
                y0=height;
            }
            y1=texttop+textheight;
            if(y1<0)
            {
                y1=0;
            }
            if(y1>height)
            {
                y1=height;
            }
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
    PaintBoxAbout->Canvas->Draw(0,0,Bitmap);
    Bitmap->Dormant();
    Bitmap->FreeImage();
    delete Bitmap;
}
//---------------------------------------------------------------------------
