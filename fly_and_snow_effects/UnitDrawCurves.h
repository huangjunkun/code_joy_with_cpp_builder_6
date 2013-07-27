//---------------------------------------------------------------------------

#ifndef UnitDrawCurvesH
#define UnitDrawCurvesH
//#include <winuser.h> //GetAsyncKeyState ..
#include "UnitFlyBody.h"
//---------------------------------------------------------------------------
class TDrawCurves
{
public:
    enum { DRAW_PEN_UPDATE = 20 };//DRAW_PEN_UPDATE timerticks更新一次linkCanvas->Pen ...
    enum { POINTNUMS = 40  };
    //enum { ANGLE =  (360.0/POINTNUMS) };
#define ANGLE   (360.0/POINTNUMS)
    enum { PIECE  = 40   };
    enum { PERIODS = 2   };
    enum { ONE_PERIOD_DIVIDES = 4 };
    enum { defaultPenWidth = 15 };
    enum { PEN_WIDTH_STEP = 1 };
    enum { MAX_PEN_WIDTH = 30 };
    enum { MIN_PEN_WIDTH = 1 };
    enum { TIME_STEP = 50 };
    enum { MIN_TIME_INTERVAL=50 ,MAX_TIME_INTERVAL=2000 ,defaultInterval=1200 };
private:
    TWinControl* Owner;
    TCanvas* linkCanvas;
    TTimer* drawTimer;
    // 绘制正弦曲线属性 ...
    double  dSin[POINTNUMS];
    int     iAmplitude;  // 振幅/2
    int     iPeriod; // 周期 period
    vector<TPoint>  flyPath;
    void __fastcall initdSinAndflyPath();//function ...
public:
    __fastcall TDrawCurves(TWinControl* AOwner ,TCanvas* canvas);
    ~TDrawCurves();
    void __fastcall drawTimerTimer(TObject *Sender);
    TTimer* getDrawTimer() const
    {
        return drawTimer;
    }
    const vector<TPoint>*  getFlyPathPtr() const
    {
        return &flyPath;
    }
    int getAmplitude() const
    {
        return iAmplitude;
    }
    int getPeriod() const
    {
        return iPeriod;
    }

    void  __fastcall  doDraw();
    void  __fastcall  stopDraw();
    bool  __fastcall  updatePeriodAmplitude(int period ,int amplitude);
    void __fastcall   keyDownAndUpdate(WORD Key);

};
//---------------------------------------------------------------------------
_fastcall TDrawCurves::TDrawCurves(TWinControl* AOwner ,TCanvas* canvas)
    : Owner(AOwner) ,linkCanvas(canvas)
{
    drawTimer = new TTimer(AOwner);
    drawTimer->Enabled = false;
    drawTimer->Interval = defaultInterval;
    drawTimer->OnTimer = drawTimerTimer;
    linkCanvas->Pen->Color = clLime;
    linkCanvas->Pen->Width = defaultPenWidth;
    iAmplitude = (Screen->Height-50)/2;// ...
    iPeriod = Screen->Width/2-100;// ...
    initdSinAndflyPath(); // ...
}
TDrawCurves::~TDrawCurves()
{
    delete drawTimer;
}
//---------------------------------------------------------------------------
void __fastcall TDrawCurves::initdSinAndflyPath()
{
    if(!linkCanvas) throw Exception("linkCanvas is NULL ,error ...");
    for(int i=0; i<POINTNUMS; i++)
        dSin[i] =  (iAmplitude-10)*sin(ANGLE*i/180*M_PI)+iAmplitude; //sin(angle*i/180*M_PI);
    int   offset = iPeriod/4;
    flyPath.clear();// 清空原始路径 ...
    for(int i=0; i<PERIODS; i++)
    {
        int temp = i*iPeriod;
        flyPath.push_back(TPoint(temp ,dSin[0]));
        flyPath.push_back(TPoint(temp+offset ,dSin[12]+25));
        flyPath.push_back(TPoint(temp+2*offset ,dSin[20]));
        flyPath.push_back(TPoint(temp+3*offset ,dSin[32]-25));
    }
    //linkCanvas->FillRect(linkCanvas->ClipRect);// ...
}
//---------------------------------------------------------------------------
void __fastcall TDrawCurves::drawTimerTimer(TObject *Sender)
{
    //ShowMessage("drawTimerTimer ...");
    static  int iY = 0;
    linkCanvas->FillRect(linkCanvas->ClipRect);//or: ...
    /* // Clear ...
    TColor  clTemp=linkCanvas->Pen->Color;
    TPenStyle psTemp=linkCanvas->Pen->Style;
    linkCanvas->Pen->Color = clBlack;
    linkCanvas->Pen->Style = psClear;
    linkCanvas->MoveTo(0 ,iAmplitude);
    for(unsigned int i=0 ,j=iY;i<POINTNUMS*PERIODS;i++ ,j++)
    {
        int     x = i*iPeriod/POINTNUMS;
        linkCanvas->LineTo(x ,dSin[j%POINTNUMS]);
    }
    linkCanvas->Pen->Color = clTemp;  // ...
    linkCanvas->Pen->Style = psTemp;     */
    linkCanvas->MoveTo(0 ,iAmplitude);
    for(unsigned int i=0 ,j=iY=(++iY)%POINTNUMS; i<POINTNUMS*PERIODS; i++ ,j++)
    {
        int     x = i*iPeriod/POINTNUMS;
        linkCanvas->LineTo(x ,dSin[j%POINTNUMS]);
    }   /*
    static TColor colors[] = { clRed,clYellow,clBlack,clSkyBlue,clWhite,clGray,cl3DDkShadow,\
        clGreen,clPurple,clCream,clDkGray,clFuchsia,clMaroon,clOlive,clBlue,clHighlight, \
        clWindow,cl3DLight,clTeal,clSilver,clInactiveBorder,clAqua,clScrollBar };   */
    static TColor colors[] = { clLime,clRed,clYellow,clOlive,clBlue,clMaroon,clGreen };
    const int COLORKINDS = sizeof(colors)/sizeof(TColor);
    static TPenStyle styles[] = {psSolid, psDash, psDot, psDashDot, psDashDotDot, psClear, psInsideFrame };
    const int STYLEKINDS = sizeof(styles)/sizeof(TPenStyle);
    TPenMode modes[] = {pmBlack, pmWhite, pmNop, pmNot, pmCopy, pmNotCopy, \
                        pmMergePenNot, pmMaskPenNot, pmMergeNotPen, pmMaskNotPen, pmMerge, \
                        pmNotMerge, pmMask, pmNotMask, pmXor, pmNotXor
                       };
    const int MODEKINDS = sizeof(modes)/sizeof(TPenMode);
    //ShowMessage(String(STYLEKINDS));
    static int tickCount = 0;
    tickCount++;
    if(tickCount==DRAW_PEN_UPDATE)// ...
    {
        static int colorIndex=-1 ,styleIndex=-1 ,modeIndex=-1;//not int okokok ???
        colorIndex = (++colorIndex)%COLORKINDS;
        styleIndex = (++styleIndex)%STYLEKINDS;
        modeIndex = (++modeIndex)%MODEKINDS;
        linkCanvas->Pen->Color = colors[colorIndex];
        linkCanvas->Pen->Style = styles[styleIndex]	;//
        linkCanvas->Pen->Mode = modes[modeIndex];//
        tickCount = 0;
    }
}
//---------------------------------------------------------------------------
void  __fastcall  TDrawCurves::doDraw()
{
    drawTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void  __fastcall  TDrawCurves::stopDraw()
{
    drawTimer->Enabled = false;
    linkCanvas->FillRect(linkCanvas->ClipRect);
}
bool  __fastcall  TDrawCurves::updatePeriodAmplitude(int period ,
        int amplitude)
{
    if(period==iPeriod&&amplitude==iAmplitude)
        return false;// ...
    iPeriod = period;
    iAmplitude = amplitude;
    initdSinAndflyPath();
    return true;
}
void __fastcall   TDrawCurves::keyDownAndUpdate(WORD Key)
{
    if(drawTimer->Enabled)// doDraw ....
    {
        int period = getPeriod();
        int amplitude = getAmplitude();
        switch(Key)
        {
        case VK_RIGHT: //ShowMessage("VK_RIGHT");
            if(GetAsyncKeyState(VK_CONTROL)<0)//and Ctrl ...
            {
                int width = linkCanvas->Pen->Width+PEN_WIDTH_STEP;
                linkCanvas->Pen->Width = (width<MAX_PEN_WIDTH ? width :MAX_PEN_WIDTH);
                return;
            }
            if(Screen->Width-FlyBodyForm->Image1->Width>period*PERIODS+PIECE)
                period += PIECE;
            else    return;
            break;
        case VK_LEFT:
            if(GetAsyncKeyState(VK_CONTROL)<0)//and Ctrl ...
            {
                int width = linkCanvas->Pen->Width-PEN_WIDTH_STEP;
                linkCanvas->Pen->Width = (width>MIN_PEN_WIDTH ? width :MIN_PEN_WIDTH);
                return;
            }
            if(0<period-PIECE) period -= PIECE;
            else    return;
            break;
        case VK_UP:
            if(GetAsyncKeyState(VK_CONTROL)<0)
            {
                int interval=drawTimer->Interval-TIME_STEP;
                drawTimer->Interval = (interval>MIN_TIME_INTERVAL?interval :MIN_TIME_INTERVAL);
                return;
            }
            if(0<amplitude-PIECE) amplitude -= PIECE;
            else    return;
            break;
        case VK_DOWN:
            if(GetAsyncKeyState(VK_CONTROL)<0)
            {
                int interval=drawTimer->Interval+TIME_STEP;
                drawTimer->Interval = (interval<MAX_TIME_INTERVAL?interval :MAX_TIME_INTERVAL);
                return;
            }
            if(Screen->Height-FlyBodyForm->Image1->Height >amplitude*2+PIECE)
                amplitude += PIECE;
            else    return;
            break;
        default :
            return;
        }
        updatePeriodAmplitude(period ,amplitude);
    }//drawTimer->Enabled
}
//---------------------------------------------------------------------------
#endif
