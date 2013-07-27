//---------------------------------------------------------------------------

#ifndef UnitThreadH
#define UnitThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <assert.h>
#include <vector>
using namespace std;

#include "UnitFlyBody.h"
#include "UnitSnow.h"
//#include "UnitMain.h"
//---------------------------------------------------------------------------
//const int IMAGECOUNT = 6;
//---------------------------------------------------------------------------
class  TFlyFollow : public TThread
{
protected:
    enum { IMAGECOUNT = 6 };
    TFlyBody* flyBody;
    void __fastcall Execute() = 0;
    TSnow   *linkSnow;
private:
    void __fastcall hideFlyBody();// inline...
public:
    __fastcall TFlyFollow(TWinControl* AOwner , \
                          TFlyBody::FlyType flyType=TFlyBody::ftRIGHT ,bool CreateSuspended=true);
    __fastcall ~TFlyFollow(void)
    {
        delete flyBody;
    }
    void __fastcall Suspend(void)
    {
        TThread::Suspend();
        hideFlyBody();
    }
    void shiftFlyDiretion()
    {
        flyBody->shiftBody();
    }
    TSnow* setLinkSnow(TSnow *snow)
    {
        TSnow* temp=linkSnow;
        linkSnow=snow;
        return temp;
    }
    enum { defaultFallSnows = 1 };
    void fallSnow(const TPoint& pt) // or: bool fallSnow() ...
    {
        //if(!linkSnow) throw Exception("linkSnow is NULL ,error ...");
        assert(linkSnow);//
        linkSnow->fallNSnow(pt ,defaultFallSnows);
    } // ...
};
//---------------------------------------------------------------------------
void __fastcall TFlyFollow::hideFlyBody() // inline
{
    for(int i=0; i<IMAGECOUNT; i++)
        (*flyBody)[i]->Visible = false;
}
class TFlyFollowCursor : public TFlyFollow
{
private:
    //
protected:
    void __fastcall Execute();
public:
    __fastcall TFlyFollowCursor(TWinControl* AOwnerbool);//

};
//---------------------------------------------------------------------------
class TFlyFollowPath : public TFlyFollow
{
private:
    //
    const vector<TPoint> *lpPathVec_;  //pathVec_ ...
    int    iMoveTo;// 1 -- forward ,-1 -- backward ...
    bool bReturnPath;
protected:
    void __fastcall Execute();
public:
    __fastcall TFlyFollowPath(TWinControl* AOwner ,const vector<TPoint> *lpPathVec , \
                              bool bReturn=true);//
    void moveFly(const TPoint& dest);
};
//---------------------------------------------------------------------------
class TFlyAngel : public TThread
{
private:
    TFlyAngelImpl *flyAngelImpl;
    void    hideFlyBody() const
    {
        (flyAngelImpl->getBodyImg())->Visible = false;
    }
    void    showFlyBody() const
    {
        (flyAngelImpl->getBodyImg())->Visible = true;
    }
protected:
    void __fastcall Execute();
public:
    __fastcall TFlyAngel(TFlyAngelImpl *flyAngel ,bool CreateSuspended=true);
    __fastcall ~TFlyAngel(void)
    {
        delete flyAngelImpl;
    }
    void __fastcall Suspend(void)
    {
        TThread::Suspend();
        hideFlyBody();
    }
    void __fastcall Resume(void)
    {
        TThread::Resume();
        showFlyBody();
    }
    // ...
};
//---------------------------------------------------------------------------
#endif
