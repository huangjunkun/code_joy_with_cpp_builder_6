//---------------------------------------------------------------------------

#ifndef UnitRoseH
#define UnitRoseH
#include <vcl.h>

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithms>
#include <iterator>
using namespace std;

//#include "UnitMain.h" //error ...Ñ­»·#include
//---------------------------------------------------------------------------
class   TRose_Thread : public TThread
{
private:
    TCanvas      *canvas;
    TImageList   *imageList;
//    TLabel       *lblHello;
    int     bmpWidth ,bmpHeight;
    vector<TPoint>  ptVec;
    //bool    bIsPlay;
public:
    TRose_Thread(TCanvas *Canvas ,TImageList *ImageList);
    __fastcall virtual ~TRose_Thread() { } // ...
    void __fastcall     doPlay()
    {
        TThread::Resume();
    }
    void __fastcall     doStop()
    {
        TThread::Suspend();
    }
    virtual void __fastcall Execute(void);
    // ...
};

//---------------------------------------------------------------------------
class   TRose //  TRose_No_Thread
{
private:
    enum { defaultPalyInterval = 50 };
    TCanvas     *canvas;//link...
    TImageList  *imageList;//link...
    TTimer      *TimerDraw;// new ...
    TTimer      *TimerClear;// new ...
//    TLabel       *lblHello;
    int     bmpWidth ,bmpHeight ,bmpIndex;
    vector<TPoint>  ptVec;
    vector<int>     indexVec;
    int     blockIndex;
private:
    void    initDrawRose();
    void    initClearRose();
public:
    TRose(TWinControl* AOwner ,TCanvas *Canvas ,TImageList *ImageList);
    __fastcall virtual ~TRose()
    {
        delete TimerDraw;
        delete TimerClear;
    } // ...
    void __fastcall TimerDrawTimer(TObject *Sender);
    void __fastcall TimerClearTimer(TObject *Sender);
    void __fastcall doPlay()
    {
        TimerDraw->Enabled = true;
    }
    void __fastcall doStop()
    {
        bmpIndex = blockIndex = 0;
        TimerDraw->Enabled = false;
        TimerClear->Enabled = false;
        canvas->Brush->Style = bsSolid;
        canvas->Brush->Color = clBlack;
        canvas->FillRect(canvas->ClipRect);
    }
    bool isPlay() const
    {
        return TimerClear->Enabled||TimerDraw->Enabled;
    }
    TTimer* getTimerDraw()
    {
        return TimerDraw;
    }
    TTimer* getTimerClear()
    {
        return TimerClear;
    }
    void    setPalyInterval(int interval)
    {
        TimerDraw->Interval = interval;
        TimerClear->Interval = interval;
    }
};
TRose::TRose(TWinControl* AOwner ,TCanvas *Canvas ,TImageList *ImageList)
    : canvas(Canvas) ,imageList(ImageList)
{
    // two Timers ...
    if(!canvas || !imageList)
        throw Exception("TRose::TRose(...) ,error ...");
    // or :assert(canvas&&imageList); // ...
    TimerDraw = new TTimer(AOwner);
    TimerClear = new TTimer(AOwner);
    TimerDraw->Enabled = false;
    TimerClear->Enabled = false;
    TimerDraw->Interval = defaultPalyInterval;//
    TimerClear->Interval = defaultPalyInterval;//
    TimerDraw->OnTimer = TimerDrawTimer;
    TimerClear->OnTimer = TimerClearTimer;
    //  ... other ...
    bmpWidth = imageList->Width; //200
    bmpHeight = imageList->Height;//200
    bmpIndex = 0;
    for(int i=0; i<Screen->Width; i+=bmpWidth) //
        for(int j=Screen->Height-bmpHeight-30; j>0-bmpHeight; j-=bmpHeight)
            ptVec.push_back(TPoint(i ,j));
    indexVec.reserve(ptVec.size());
    for(unsigned int i=0; i<ptVec.size(); i++)
        indexVec.push_back(i);
    random_shuffle(indexVec.begin() ,indexVec.end());
    blockIndex = 0;//bIsPlay = true;
}
void    TRose::initDrawRose()
{ }
void    TRose::initClearRose()
{ }
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
