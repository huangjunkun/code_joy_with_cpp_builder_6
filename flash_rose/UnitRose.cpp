//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitRose.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TRose_Thread::TRose_Thread(TCanvas *Canvas ,TImageList *ImageList)
    : TThread(true) ,canvas(Canvas) ,imageList(ImageList)
{
    //_fastcall TThread(bool CreateSuspended); ...
    //::TThread(true);
    if(!canvas || !imageList)
        throw Exception("TRose_Thread::TRose_Thread(...) ,error ...");
    FreeOnTerminate = true; //...
    bmpWidth = imageList->Width; //200
    bmpHeight = imageList->Height;//200
    for(int i=0; i<Screen->Width; i+=bmpWidth) //
        for(int j=0; j<Screen->Height-bmpHeight; j+=bmpHeight) //
            ptVec.push_back(TPoint(i ,j));
    //bIsPlay = true;
} //...
void __fastcall TRose_Thread::Execute(void)
{
    while(true)//bIsPlay
    {
        vector<int>  vecIndex(ptVec.size());
        for(unsigned int i=0; i<vecIndex.size(); i++)
            vecIndex[i] = i;
        // draw rose ...
        random_shuffle(vecIndex.begin() ,vecIndex.end()); /*
       ofstream fout("test.txt");
       fout << "\n---random_shuffle---------------------------\n";
       copy(vecIndex.begin() ,vecIndex.end() ,ostream_iterator<int>(fout ," ")); */
        Graphics::TBitmap    *bmp = new Graphics::TBitmap;
        bmp->Width = imageList->Width;
        bmp->Height = imageList->Height;
        int  bmpIndex = rand()%imageList->Count;
        for(unsigned int i=0; i<vecIndex.size(); i++)
        {
            TRect   rect(ptVec[vecIndex[i]].x ,ptVec[vecIndex[i]].y ,\
                         ptVec[vecIndex[i]].x+bmpWidth ,ptVec[vecIndex[i]].y+bmpHeight);
            imageList->GetBitmap(bmpIndex ,bmp);
            canvas->Lock();// ...
            canvas->CopyRect(rect ,bmp->Canvas ,bmp->Canvas->ClipRect);
            canvas->Unlock();
            ::Sleep(50);
        }
        delete bmp;
        // show hello ...
        ::Sleep(1000);
        // clear rose ...
        //canvas->FillRect(canvas->ClipRect);
        /*   */
        random_shuffle(vecIndex.begin() ,vecIndex.end());
        const TBrushStyle bsArray[] = {bsClear, bsHorizontal, bsVertical, bsFDiagonal, \
                                       bsBDiagonal, bsCross, bsDiagCross
                                      };//bsSolid,
        const int StyleKinds = sizeof(bsArray) /sizeof(TBrushStyle);
        canvas->Brush->Color = clLime;
        canvas->Brush->Style = bsArray[rand()%StyleKinds];
        for(unsigned int i=0; i<vecIndex.size(); i++)
        {
            TRect   rect(ptVec[vecIndex[i]].x ,ptVec[vecIndex[i]].y ,\
                         ptVec[vecIndex[i]].x+bmpWidth ,ptVec[vecIndex[i]].y+bmpHeight);
            canvas->Lock();// ...
            canvas->FillRect(rect);
            canvas->Unlock();
            ::Sleep(50);
        }
        ::Sleep(1000);
    }
}

//---------------------------------------------------------------------------
void __fastcall TRose::TimerDrawTimer(TObject *Sender)
{
    // draw rose ...
    static  unsigned tickCount = 0;
    Graphics::TBitmap    *bmp = new Graphics::TBitmap;
    bmp->Width = imageList->Width;
    bmp->Height = imageList->Height;
    TRect   rect(ptVec[indexVec[blockIndex]].x ,ptVec[indexVec[blockIndex]].y ,\
                 ptVec[indexVec[blockIndex]].x+bmpWidth ,ptVec[indexVec[blockIndex]].y+bmpHeight);
    imageList->GetBitmap(bmpIndex ,bmp);
    canvas->CopyRect(rect ,bmp->Canvas ,bmp->Canvas->ClipRect);
    delete bmp;
    blockIndex++;
    tickCount++;
    if(tickCount==ptVec.size())
    {
        tickCount=0;
        TimerDraw->Enabled = false;
        // for clear  ...
        random_shuffle(indexVec.begin() ,indexVec.end());
        blockIndex = 0;
        const TColor clArray[] = {clLime ,clRed ,clYellow ,clBlack ,clBlue ,clGreen};
        const int ColorKinds = sizeof(clArray) /sizeof(TColor);
        canvas->Brush->Color = clArray[rand()%ColorKinds];
        const TBrushStyle bsArray[] = {bsSolid ,bsClear, bsHorizontal, bsVertical,\
                                       bsFDiagonal, bsBDiagonal, bsCross, bsDiagCross
                                      };//
        const int StyleKinds = sizeof(bsArray) /sizeof(TBrushStyle);
        canvas->Brush->Style = bsArray[rand()%StyleKinds];
        TimerClear->Enabled = true;
    }

}
//---------------------------------------------------------------------------
void __fastcall TRose::TimerClearTimer(TObject *Sender)
{
    // clear rose ...
    static  unsigned tickCount = 0;
    TRect   rect(ptVec[indexVec[blockIndex]].x ,ptVec[indexVec[blockIndex]].y ,\
                 ptVec[indexVec[blockIndex]].x+bmpWidth ,ptVec[indexVec[blockIndex]].y+bmpHeight);
    canvas->FillRect(rect);
    blockIndex++;
    tickCount++;
    if(tickCount==ptVec.size())
    {
        tickCount=0;
        TimerClear->Enabled = false;
        // for draw  ...
        random_shuffle(indexVec.begin() ,indexVec.end());
        blockIndex = 0;
        TimerDraw->Enabled = true;
        bmpIndex = rand()%imageList->Count;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
