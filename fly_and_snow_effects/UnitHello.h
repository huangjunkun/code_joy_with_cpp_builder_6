//---------------------------------------------------------------------------

#ifndef UnitHelloH
#define UnitHelloH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#define DEF_SROLLTEXT_LENGTH  11
const String DEF_SROLLTEXT[DEF_SROLLTEXT_LENGTH] =  \
{
    "人生美诗" ,\
    "爱也罢，恨也罢，心胸爱恨分阔狭，有缘无缘前生定，爱也该爱，恨却白搭。" ,\
    "苦也罢，乐也罢，酸甜从来拌苦辣，笑口常开大丈夫，苦也哈哈，乐也哈哈。" ,\
    "富也罢，穷也罢，幸福不靠金钱架，豪华恬淡各千秋，富便辉煌，穷也清雅。" ,\
    "福也罢，祸也罢，福宏何惧灾难大，人生坎坷是阶梯，福是当头，祸踩脚下。" ,\
    "成也罢，败也罢，莫以成败论高下，爷们奋斗便英雄，成也潇洒，败也潇洒。" ,\
    "得也罢，失也罢，患得患失误年华，凡事该做只管做，得了更好，失也没啥。" ,\
    "褒也罢，贬也罢，过眼烟云何足话，君子小人善恶分，褒也是他，贬也是他。" ,\
    "是也罢，非也罢，是是非非争个啥，河东河西三十年，是的错啦，非的对啦。" ,\
    "醒也罢，醉也罢，半醒半醉为最佳，忘物忘我大智慧，醒是聪明，醉也不傻。" ,\
    "生也罢，死也罢，生不必喜死别怕，在世多做利人事，生也光荣，死也伟大。"
};
//---------------------------------------------------------------------------
class THelloForm : public TForm
{
__published:	// IDE-managed Components
    TImage *imgExample;
    TLabel *LabelHello;
    TLabel *LabelMe;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
                              TShiftState Shift);
private:	// User declarations
public:		// User declarations
    __fastcall THelloForm(TComponent* Owner);
    void    ImageFadeOut(TCanvas* canvas);
    void    ImageFadeIn(TCanvas* canvas);
//制止重画窗口背景
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    /*  //与 API AnimateWindow(...)有冲突 ...注意注意
       BEGIN_MESSAGE_MAP
           MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,OnWmBkgnd)
       END_MESSAGE_MAP(TForm)      */
    /*    The WM_ERASEBKGND message is sent when the window background must be erased
    (for example, when a window is resized). The message is sent to prepare an
    invalidated portion of a window for painting.           */
};
//---------------------------------------------------------------------------
extern PACKAGE THelloForm *HelloForm;
//---------------------------------------------------------------------------
#endif
