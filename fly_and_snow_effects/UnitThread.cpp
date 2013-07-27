//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitThread.h"
#include "UnitMain.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TFlyFollowCursor::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TFlyFollow::TFlyFollow(TWinControl* AOwner ,\
                                  TFlyBody::FlyType flyType ,bool CreateSuspended)
    : TThread(CreateSuspended) ,flyBody(new TFlyBody(AOwner ,flyType)) ,\
    linkSnow(0)//NULL

{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
__fastcall TFlyFollowCursor::TFlyFollowCursor(TWinControl* AOwner)
    : TFlyFollow(AOwner ,TFlyBody::ftLEFT) //
{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
void __fastcall TFlyFollowCursor::Execute()
{
    //---- Place thread code here ---- /*  */
    const int   STEPS = 5; //用5步追到鼠标目的地 ...
    POINT   cursorPt; //鼠标位置
    int     Left=Screen->Width + 10 ,Top=Screen->Height + 10;
    int imgIndex = 0;
    while(true)
    {
        (*flyBody)[imgIndex]->Visible = false;
        imgIndex = (imgIndex+1)%IMAGECOUNT;
        GetCursorPos(&cursorPt);  //读鼠标位置
        //边界调整
        if(cursorPt.x>=Screen->Width-(*flyBody)[imgIndex]->Width)
            cursorPt.x-=(*flyBody)[imgIndex]->Width+16;
        if(cursorPt.y>=Screen->Height-(*flyBody)[imgIndex]->Height)
            cursorPt.y-=(*flyBody)[imgIndex]->Height+16;
        else
            cursorPt.y+=16; //避开鼠标热点
        Left+=(cursorPt.x-Left)/STEPS;
        Top+=(cursorPt.y-Top)/STEPS;
        (*flyBody)[imgIndex]->Left = Left;
        (*flyBody)[imgIndex]->Top = Top;
        (*flyBody)[imgIndex]->Visible = true;
        ::Sleep(200);
    }

}
//---------------------------------------------------------------------------

__fastcall TFlyFollowPath::TFlyFollowPath(TWinControl* AOwner ,const vector<TPoint> *lpPathVec ,\
        bool bReturn)//
    : TFlyFollow(AOwner ,TFlyBody::ftRIGHT),lpPathVec_(lpPathVec) , \
    iMoveTo(1) ,bReturnPath(bReturn)
{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
void __fastcall TFlyFollowPath::Execute()
{
    //---- Place thread code here ----
    int     Left=(*lpPathVec_)[0].x ,Top=(*lpPathVec_)[0].y;
    unsigned int pathIndex = 0;
    (*flyBody)[0]->Left = Left;
    (*flyBody)[0]->Top = Top;
    while(true)
    {
        if(pathIndex==0&&iMoveTo!=1)// or: == -1
        {
            iMoveTo = 1;
            shiftFlyDiretion();
        }
        else if(pathIndex==(*lpPathVec_).size()-1)
        {
            if(bReturnPath)
            {
                iMoveTo = -1;
                shiftFlyDiretion();
            }
            else
            {
                iMoveTo = 1;
                pathIndex = -1;
            }
        }
        pathIndex = (pathIndex+iMoveTo);
        const TPoint& destPt = (*lpPathVec_)[pathIndex];// ...
        moveFly(destPt);
        //ShowMessage(String(pathIndex));/* */
        if(linkSnow->isFallSnow() && \
                0==(pathIndex+1)%TDrawCurves::ONE_PERIOD_DIVIDES)
        {
            int i=10;
            while(i--)
            {
                //ShowMessage("0==(pathIndex+2)%8");
                this->fallSnow(destPt);// ...
                Sleep(200);
            }
        }
    }
}
//---------------------------------------------------------------------------
void TFlyFollowPath::moveFly(const TPoint& dest)
{
    const int   STEPS = 10; //用10步追到目的地 ...
    static int imgIndex = 0;
    int     Left=(*flyBody)[imgIndex]->Left ,
                 Top=(*flyBody)[imgIndex]->Top;
    while(true)
    {
        (*flyBody)[imgIndex]->Visible = false;
        imgIndex = (imgIndex+1)%IMAGECOUNT;

        Left += (dest.x-Left)/STEPS;
        Top += (dest.y-Top)/STEPS;
        (*flyBody)[imgIndex]->Left = Left;
        (*flyBody)[imgIndex]->Top = Top;
        (*flyBody)[imgIndex]->Visible = true;
        ::Sleep(150);
        if(abs(dest.y-Top)<10&&abs(dest.x-Left)<10)//
            return;
    }

}
//---------------------------------------------------------------------------
__fastcall TFlyAngel::TFlyAngel(TFlyAngelImpl *flyAngel ,bool CreateSuspended)
    : TThread(CreateSuspended) ,flyAngelImpl(flyAngel) // ...
{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
void __fastcall TFlyAngel::Execute()
{
    flyAngelImpl->flyPathLoop();
}
//---------------------------------------------------------------------------

