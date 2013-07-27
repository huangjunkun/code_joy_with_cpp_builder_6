//---------------------------------------------------------------------------

#ifndef UnitSnowH
#define UnitSnowH
//---------------------------------------------------------------------------

//#include "UnitFlyBody.h"
#include <vcl.h>
#include <vector>
#include <queue>
using namespace std;
//---------------------------------------------------------------------------
class TSnow
{
public:
    typedef TPoint TStep; //
    typedef TImage*   Snow;
    typedef struct FreeSnow
    {
        Snow    snow;
        bool    free;//reseve ...
    } FreeSnow;
    typedef struct BusySnow
    {
        Snow    snow;
        TStep  goforward;
        int     index;
    } BusySnow;
    //enum { imageExamples = 12 };
    enum { ADD_SNOW_NUM = 10 };
    enum { defaultSnows = 30 };
    enum { slowDown=10 ,middleDown=12 ,fastDown=15 ,defaultDown=slowDown };
    enum { slowLeftRight=5 ,middleLeftRight=7 ,fastLeftRight=10 , \
           defaultLeftRight=slowLeftRight
         };
    enum { slowFallSpeed=50 ,middleFallSpeed=slowFallSpeed ,fastFallSpeed=50 ,\
           defaultFallSpeed=slowFallSpeed
         };//...
    enum { slowNewSpeed=2000 ,middleNewSpeed=1000 ,fastNewSpeed=500 ,\
           defaultNewSpeed=slowNewSpeed
         };
    enum ESnowSize { littleSnow ,middleSnow ,muchSnow ,defaultSnowSize=littleSnow };
private:
    TWinControl*     snowOwner;//TComponent ...
    int     downSpeed;//下落速度  ...
    int     letrightSpeed;//左右移动速度 ...
    TTimer  *snowFallTimer ,*snowNewTimer;
    vector<FreeSnow >   freesnows;
    vector<BusySnow>    busysnows;
    queue<int>      indexQue;//?????????
    bool    CheckOver(int left ,int top);//判断雪花是否在屏幕越界
protected:
    void __fastcall snowFallTimerTimer(TObject *Sender);
    void __fastcall snowNewTimerTimer(TObject *Sender);
    void    newSnows(int newnum);
    void    __fastcall randSnowing(const TPoint* ptPos=NULL); //随机产生雪花
public:		// User declarations
    static vector<TImage*>  imageExamples;
    static void     initImageExamples(TImage** images ,int count);
    __fastcall TSnow(TWinControl* Owner ,int snowNums=defaultSnows);
    ~TSnow();
    int setDownrate(int new_)
    {
        int temp = new_;
        downSpeed = new_;
        return temp;
    }
    TTimer* getsnowFallTimer()
    {
        return snowFallTimer;
    }
    TTimer* getsnowNewTimer()
    {
        return snowNewTimer;
    }
    void __fastcall fallNSnow(const TPoint& pt ,int nSnows=1);// ...
    void __fastcall doSnow(ESnowSize size=defaultSnowSize ,int seconds=-1);
    //seconds:0--end ,-1(<-1)--straight ...
    void __fastcall stopSnow();
    bool    isFallSnow() const
    {
        return snowFallTimer->Enabled&&snowNewTimer->Enabled;
    }
};
//---------------------------------------------------------------------------
vector<TImage*> TSnow::imageExamples;
//---------------------------------------------------------------------------
void     TSnow::initImageExamples(TImage** images ,int imageCount)
{
    FreeSnow  freesnow;
    for(int i=0; i<imageCount; i++) //
    {
        freesnow.snow = images[i]; //
        freesnow.free = true;
        freesnow.snow->Visible = false;
        freesnow.snow->Top = 0; // Screen->Height+10
        imageExamples.push_back(images[i]);
    }
}
//---------------------------------------------------------------------------
__fastcall TSnow::TSnow(TWinControl* Owner ,int snowNums)
    : snowOwner(Owner) ,downSpeed (defaultDown) ,letrightSpeed(defaultLeftRight)
{
    if(imageExamples.empty())
        throw Exception("imageExamples is empty,error ...");
    snowFallTimer = new TTimer(Owner);
    snowFallTimer->Enabled = false;
    snowFallTimer->Interval = defaultFallSpeed;// ...
    snowFallTimer->OnTimer =  snowFallTimerTimer;
    snowNewTimer = new TTimer(Owner);
    snowNewTimer->Enabled = false;
    snowNewTimer->Interval = defaultNewSpeed;// ...
    snowNewTimer->OnTimer =  snowNewTimerTimer;
    newSnows(snowNums);
    // 预存大小 、、、、
    freesnows.reserve(snowNums);
    busysnows.reserve(snowNums);
}
//---------------------------------------------------------------------------
TSnow::~TSnow()
{
    snowFallTimer->Enabled = false;
    snowNewTimer->Enabled = false;
    if(snowFallTimer)   delete snowFallTimer;   //
    if(snowNewTimer)   delete snowNewTimer;
    for(unsigned int i=0; i<freesnows.size(); i++)
        delete freesnows[i].snow;
    /* freesnows 包含全部雪花 并包含 busysnows ...
    for(int i=0;i<busysnows.size();i++)
        delete busysnows[i].snow;  */

} // ...
//---------------------------------------------------------------------------
void    TSnow::newSnows(int snowNums)
{
    TImage  *snow;
    FreeSnow  freesnow;
    try
    {
        for(int i=0; i<snowNums; i++) //
        {
            // //以ImageExample初始化雪花
            snow = new TImage(snowOwner);// freesnows[i].snow this->Controls[i]
            snow->Visible = false;
            snow->Parent = snowOwner;
            snow->Stretch = true;
            snow->Transparent = true;
            snow->Width = imageExamples[(i%imageExamples.size())]->Width;
            snow->Height = imageExamples[(i%imageExamples.size())]->Height;
            snow->Picture->Assign(imageExamples[(i%imageExamples.size())]->Picture);
            freesnow.snow = snow; //
            freesnow.free = true;
            freesnow.snow->Top = 0;
            freesnows.push_back(freesnow);
            // --- 雪花下落序列 ....
            indexQue.push(i);
        }
    }
    catch(Exception& e)//...
    {
        if(snow)    delete  snow;
        ShowMessage(e.Message+"newSnows ,error ... ");
    }
}
//---------------------------------------------------------------------------
void __fastcall TSnow::randSnowing(const TPoint* ptPos)
{
    if(indexQue.empty())   //busysnows.size()>=40
    {
        //ShowMessage("indexQue.empty");
        newSnows(ADD_SNOW_NUM);
        return;
    }
    int num =  indexQue.front();
    indexQue.pop();
    freesnows[num].free = false;
    TStep   goforward;
    goforward.y = downSpeed;//下落速度
    goforward.x = rand()%letrightSpeed*2-letrightSpeed; //左右飘动速度
    BusySnow    snowflake;//雪花
    snowflake.snow = freesnows[num].snow;
    if(ptPos==NULL)//随机 ...
        snowflake.snow->Left =  rand()%Screen->Width;    //
    else
    {
        snowflake.snow->Left =  (*ptPos).x;    //
        snowflake.snow->Top =  (*ptPos).y;    //
    }
    snowflake.goforward = goforward;
    snowflake.index = num;
    snowflake.snow->Visible = true;
    busysnows.push_back(snowflake);
}
//---------------------------------------------------------------------------
bool TSnow::CheckOver(int left ,int top)
{
    if(left > Screen->Width || left < 0 ||//   Screen->Width
            top > Screen->Height)    // || top <0     Screen->Height
        return  true;
    else
        return  false;
}
//---------------------------------------------------------------------------
void __fastcall TSnow::snowFallTimerTimer(TObject *Sender)
{
    for(unsigned int i=0; i< busysnows.size(); i++)
    {
        busysnows[i].snow->Left += busysnows[i].goforward.x;
        busysnows[i].snow->Top  += busysnows[i].goforward.y;
        if(CheckOver(busysnows[i].snow->Left ,busysnows[i].snow->Top))
        {
            indexQue.push(busysnows[i].index);
            freesnows[busysnows[i].index].snow->Visible = false;
            freesnows[busysnows[i].index].free = true; //可略、、、、、？
            freesnows[busysnows[i].index].snow->Top = 0;
            busysnows.erase(busysnows.begin()+i);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TSnow::snowNewTimerTimer(TObject *Sender)
{
    randSnowing();
}
//---------------------------------------------------------------------------
void __fastcall TSnow::fallNSnow(const TPoint& pt ,int nSnows)
{
    if(nSnows<0) return;// or:throw ...
    while(nSnows--)
        randSnowing(&pt);
}
//---------------------------------------------------------------------------
void __fastcall TSnow::doSnow(ESnowSize size ,int seconds)
{
    switch(size)
    {
    case littleSnow:
        downSpeed = slowDown;
        letrightSpeed = slowLeftRight;
        snowNewTimer->Interval = slowNewSpeed;
        break;
    case middleSnow:
        downSpeed = middleDown;
        letrightSpeed = middleLeftRight;
        snowNewTimer->Interval = middleNewSpeed;
        break;
    case muchSnow:
        downSpeed = fastDown;
        letrightSpeed = fastLeftRight;
        snowNewTimer->Interval = fastNewSpeed;
        break;
    default:
        return;
    }  // ....
    if(0==seconds)  stopSnow();
    else if(seconds<=-1)
    {
        snowNewTimer->Enabled = true;
        snowFallTimer->Enabled = true;
    }
    else //seconds
    {
        // ..........
    }
}
//---------------------------------------------------------------------------
void __fastcall TSnow::stopSnow()
{
    snowNewTimer->Enabled = false;
    snowFallTimer->Enabled = false;
    for(unsigned int i=0; i< busysnows.size(); i++)
    {
        indexQue.push(busysnows[i].index);
        freesnows[busysnows[i].index].snow->Visible = false;
        freesnows[busysnows[i].index].free = true; //可略、、、、
        freesnows[busysnows[i].index].snow->Top = 0;
    }
    busysnows.clear();
}
//---------------------------------------------------------------------------
#endif
