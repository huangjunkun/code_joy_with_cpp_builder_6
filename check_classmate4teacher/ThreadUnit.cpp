//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ThreadUnit.h"
#include "FlyUnit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TFlyThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TFlyThread::TFlyThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
void __fastcall TFlyThread::Execute()
{
    //---- Place thread code here ----
    int     num = 0;  //当前显示图片的序号
    int     steps = 5; //用5步追到鼠标
    long    tick0,tick;
    int     Left,Top;
    POINT   cursorPt; //鼠标位置
    Left=Screen->Width;
    Top=Screen->Height;
    tick0 = GetTickCount(); //读计时初值
    while(!FlyForm->End)
    {
        tick=GetTickCount(); //读计时当前值
        if(tick-tick0>60)
        {
            //每秒更换图片10次
            FlyForm->Left=Screen->Width+20; //将窗口移出屏幕
            FlyForm->Top=Screen->Height+20;
            tick0=tick; //重置计时初值
            for(int i=0; i<IMAGECOUNT; i++)
                if(i==num)
                    FlyForm->Images[i]->Visible=true;
                else
                    FlyForm->Images[i]->Visible=false;
            num=(num+1)%IMAGECOUNT;  //num取值范围为0~图片总数-1
            GetCursorPos(&cursorPt);  //读鼠标位置
            //边界调整
            if(cursorPt.x>=Screen->Width-FlyForm->Width)
                cursorPt.x-=FlyForm->Width+16;
            if(cursorPt.y>=Screen->Height-FlyForm->Height)
                cursorPt.y-=FlyForm->Height+16;
            else
                cursorPt.y+=16; //避开鼠标热点
            Left+=(cursorPt.x-Left)/steps;
            Top+=(cursorPt.y-Top)/steps;
            FlyForm->Left=Left;
            FlyForm->Top=Top; //将窗口移入相应位置      /*   */
            FlyForm->Refresh();
            Sleep(200);
        }
    }

}
//---------------------------------------------------------------------------

__fastcall TFollowThread::TFollowThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    FreeOnTerminate=true;  //线程结束时自动删除
}
//---------------------------------------------------------------------------
void __fastcall TFollowThread::Execute()
{
    //---- Place thread code here ----
    /*   --------  */
}
//---------------------------------------------------------------------------
