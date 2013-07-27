//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitThread.h"
#include "main.h"
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
    FreeOnTerminate=true;  //�߳̽���ʱ�Զ�ɾ��
}
//---------------------------------------------------------------------------
void __fastcall TFlyThread::Execute()
{
    //---- Place thread code here ----
    int     num=0;  //��ǰ��ʾͼƬ�����
    int     steps=5; //��5��׷�����
    long    tick0,tick;
    int     Left,Top;
    POINT   cursorPt; //���λ��
    Left=Screen->Width;
    Top=Screen->Height;
    tick0=GetTickCount(); //����ʱ��ֵ
    while(!MainForm->End)
    {
        tick=GetTickCount(); //����ʱ��ǰֵ
        if(tick-tick0>100)
        {
            //ÿ�����ͼƬ10��
            MainForm->Left=Screen->Width+20; //�������Ƴ���Ļ
            MainForm->Top=Screen->Height+20;
            tick0=tick; //���ü�ʱ��ֵ
            for(int i=0; i<IMAGECOUNT; i++)
                if(i==num)
                    MainForm->Images[i]->Visible=true;
                else
                    MainForm->Images[i]->Visible=false;
            num=(num+1)%IMAGECOUNT;  //numȡֵ��ΧΪ0~ͼƬ����-1
            GetCursorPos(&cursorPt);  //�����λ��
            //�߽����
            if(cursorPt.x>=Screen->Width-MainForm->Width)
                cursorPt.x-=MainForm->Width+16;
            if(cursorPt.y>=Screen->Height-MainForm->Height)
                cursorPt.y-=MainForm->Height+16;
            else
                cursorPt.y+=16; //�ܿ�����ȵ�
            Left+=(cursorPt.x-Left)/steps;
            Top+=(cursorPt.y-Top)/steps;
            MainForm->Left=Left;
            MainForm->Top=Top; //������������Ӧλ��
        }
    }
}
//---------------------------------------------------------------------------

__fastcall TFollowThread::TFollowThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    FreeOnTerminate=true;  //�߳̽���ʱ�Զ�ɾ��
}
//---------------------------------------------------------------------------
void __fastcall TFollowThread::Execute()
{
    //---- Place thread code here ----
}
//---------------------------------------------------------------------------
