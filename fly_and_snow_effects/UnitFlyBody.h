//---------------------------------------------------------------------------

#ifndef UnitFlyBodyH
#define UnitFlyBodyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
//#define IMAGECOUNT      6  //图片总数

class TFlyBodyForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image5;
    TImage *Image4;
    TImage *Image3;
    TImage *Image2;
    TImage *Image1;
    TImage *Image6;
    TImage *Image12;
    TImage *Image7;
    TImage *Image8;
    TImage *Image9;
    TImage *Image10;
    TImage *Image11;
    TImageList *ImageList1;
    TImageList *ImageList2;
    TImage *Image13;
    TImage *Image14;
    TImage *Image15;
    TImage *Image16;
    TImage *Image17;
    TImage *Image18;
    TImage *Image19;
    TImage *Image20;
    TImage *Image21;
    TImage *Image22;
    TImage *Image23;
    TImage *Image24;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFlyBodyForm(TComponent* Owner);
    enum { IMAGECOUNT = 6 };
    TImage  *Images1[IMAGECOUNT];
    TImage  *Images2[IMAGECOUNT];
//制止重画窗口背景
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    /*     */
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
    END_MESSAGE_MAP(TForm)
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
    (for example, when a window is resized). The message is sent to prepare an
    invalidated portion of a window for painting.           */
};
//---------------------------------------------------------------------------
extern PACKAGE TFlyBodyForm *FlyBodyForm;
//---------------------------------------------------------------------------
class TFlyAngelImpl
{
    enum { IMAGECOUNT = 6 };
public:
    static const int FLYSTEPS;
private:
    TImage* linkImages[IMAGECOUNT];
    TImage* bodyImg;
    Graphics::TBitmap   *bmpTemp;
    //TImageList* linkImgList;
    vector<TPoint>* lpPathVec;
    int     imageIndex;
    bool    bEndFly;
public:
    TFlyAngelImpl(TWinControl* AOwner , \
                  TImage* images[IMAGECOUNT],vector<TPoint>* lpPath);
    ~TFlyAngelImpl()
    {
        /* TODO : 析构 ... */
        if(bodyImg) delete bodyImg;
        if(bmpTemp) delete bmpTemp;
    }
    TImage* getBodyImg() const
    {
        return bodyImg;
    }
    void setLinkImages(TImage* images[IMAGECOUNT])
    {
        /*
        if(linkImages) linkImgList = linkImages;
        else
            throw Exception("TImageList* linkImages ,NULL error ...");
            */

    }
    void flyPathLoop();
protected:
    void __fastcall flyAction(const TPoint& dest);
    // ...
};

const int TFlyAngelImpl::FLYSTEPS = 20;////用5步追到目的地 ...

TFlyAngelImpl::TFlyAngelImpl(TWinControl* AOwner , \
                             TImage* images[IMAGECOUNT],vector<TPoint>* lpPath)
    : bodyImg(new TImage(AOwner)) ,lpPathVec(lpPath) , \
    bmpTemp(new Graphics::TBitmap) ,imageIndex(0),bEndFly(false)
{
    for(int i=0; i<IMAGECOUNT; i++) //
    {
        images[i]->Parent =  AOwner;
        linkImages[i] = images[i];
    }

    bodyImg->Parent = AOwner;
    bodyImg->Transparent = true;
    bodyImg->Width = linkImages[0]->Width;
    bodyImg->Height = linkImages[0]->Height;
    //linkImgList->GetBitmap(imageIndex ,bmpTemp); //
    //bodyImg->Picture->Assign(bmpTemp);//
    bodyImg->Picture->Assign(linkImages[0]->Picture);
    bodyImg->Left = (*lpPathVec)[0].x;// ...
    bodyImg->Top = (*lpPathVec)[0].y;
    //bodyImg->Visible = true;
}
void __fastcall TFlyAngelImpl::flyAction(const TPoint& dest)
{
    TPoint offest(dest.x-bodyImg->Left ,dest.y-bodyImg->Top);
    offest.x /= FLYSTEPS;
    offest.y /= FLYSTEPS;
    //ShowMessage(String(offest.x));
    for(int i=0; i<FLYSTEPS; i++)
    {
        imageIndex = (++imageIndex)%IMAGECOUNT; //linkImgList->Count
        //Graphics::TBitmap *bmpTemp = new Graphics::TBitmap;
        //linkImgList->GetBitmap(imageIndex ,bodyImg->Picture->Bitmap); //
        bodyImg->Left += offest.x;
        bodyImg->Top += offest.y;
        //bodyImg->Picture->Assign(bmpTemp);//...
        //delete bmpTemp;
        //bodyImg->Picture->Assign(linkImages[imageIndex]->Picture);// ...
        bodyImg->Canvas->CopyRect(bodyImg->Canvas->ClipRect ,\
                                  linkImages[imageIndex]->Canvas ,linkImages[imageIndex]->Canvas->ClipRect);
        ::Sleep(500);
    }
}
void TFlyAngelImpl::flyPathLoop()
{
    //
    unsigned int pathIndex = 0;
    int    iMoveTo;
    linkImages[imageIndex]->Visible = true;
    while(!bEndFly)
    {
        if(pathIndex==0)
            iMoveTo = 1;
        else if(pathIndex==lpPathVec->size()-1)
            iMoveTo = -1;
        pathIndex = (pathIndex+iMoveTo);
        TPoint& destPt = (*lpPathVec)[pathIndex];
        flyAction(destPt); // ...
        //ShowMessage("*******");
    }
}
//---------------------------------------------------------------------------

//#define ftLEFT -1
class TFlyBody
{
private:
    enum { IMAGECOUNT = 6 };
    TImage* flyImgs[IMAGECOUNT];
public:
    //typedef short FlyType;
    //static const FlyType  ftLEFT;
    //static const FlyType  ftRIGHT;
    enum FlyType { ftLEFT=-1 ,ftRIGHT=1 };
private:
    FlyType flyType;
public:
    TFlyBody(TWinControl* AOwner ,FlyType flyType_=ftLEFT);// Classes::TComponent
    ~TFlyBody();
    const TImage* operator[] (int index) const
    {
        if(index>=IMAGECOUNT || index <0)
            throw Exception("TImage* FlyBody::operator[] (int index) ,throw ...");
        return flyImgs[index];
    }
    TImage* operator[] (int index)
    {
        /*  // 11111
         if(index>=IMAGECOUNT || index <0)
             throw Exception("TImage* FlyBody::operator[] (int index) ,throw ...");
         return flyImgs[index];       */
        // ....
        return const_cast<TImage*>((static_cast<const TFlyBody*>(this))->operator[](index));
    }
    void shiftBody();
};
//const TFlyBody::FlyType  TFlyBody::ftLEFT = -1;
//const TFlyBody::FlyType  TFlyBody::ftRIGHT = 1;

TFlyBody::TFlyBody(TWinControl* AOwner ,FlyType flyType_)// Classes::TComponent
    : flyType(flyType_)
{
    /*;   */
    TImage**  images;
    if(ftLEFT==flyType_) //flyType
        images = FlyBodyForm->Images1;
    else // FLYRIGHT
        images = FlyBodyForm->Images2;
    for(int i=0; i<IMAGECOUNT; i++)
    {
        flyImgs[i] = new TImage(AOwner);
        flyImgs[i]->Visible = false;
        flyImgs[i]->Transparent = true;
        flyImgs[i]->Parent = AOwner;
        flyImgs[i]->Width = images[i]->Width;
        flyImgs[i]->Height = images[i]->Height;
        flyImgs[i]->Picture->Assign(images[i]->Picture);
        flyImgs[i]->Left = images[i]->Left;
        flyImgs[i]->Top = images[i]->Top;
    }
}
TFlyBody::~TFlyBody() // inline ...
{
    for(int i=0; i<IMAGECOUNT; i++)
        delete flyImgs[i];
}
void TFlyBody::shiftBody()
{
    TImage**  shiftImages;
    if(ftLEFT==flyType)
    {
        shiftImages = FlyBodyForm->Images2;
        flyType = ftRIGHT;
    }
    else // FLYRIGHT
    {
        shiftImages = FlyBodyForm->Images1;
        flyType = ftLEFT;
    }
    for(int i=0; i<IMAGECOUNT; i++)
        flyImgs[i]->Picture->Assign(shiftImages[i]->Picture);
}
//---------------------------------------------------------------------------
#endif
