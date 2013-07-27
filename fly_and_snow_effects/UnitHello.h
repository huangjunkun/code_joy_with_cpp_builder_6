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
    "������ʫ" ,\
    "��Ҳ�գ���Ҳ�գ����ذ��޷���������Ե��Եǰ��������Ҳ�ð�����ȴ�״" ,\
    "��Ҳ�գ���Ҳ�գ���������������Ц�ڳ������ɷ򣬿�Ҳ��������Ҳ������" ,\
    "��Ҳ�գ���Ҳ�գ��Ҹ�������Ǯ�ܣ������񵭸�ǧ�����Իͣ���Ҳ���š�" ,\
    "��Ҳ�գ���Ҳ�գ�����ξ����Ѵ����������ǽ��ݣ����ǵ�ͷ�����Ƚ��¡�" ,\
    "��Ҳ�գ���Ҳ�գ�Ī�Գɰ��۸��£�ү�Ƿܶ���Ӣ�ۣ���Ҳ��������Ҳ������" ,\
    "��Ҳ�գ�ʧҲ�գ����û�ʧ���껪�����¸���ֻ���������˸��ã�ʧҲûɶ��" ,\
    "��Ҳ�գ���Ҳ�գ��������ƺ��㻰������С���ƶ�֣���Ҳ��������Ҳ������" ,\
    "��Ҳ�գ���Ҳ�գ����ǷǷ�����ɶ���Ӷ�������ʮ�꣬�ǵĴ������ǵĶ�����" ,\
    "��Ҳ�գ���Ҳ�գ����Ѱ���Ϊ��ѣ��������Ҵ��ǻۣ����Ǵ�������Ҳ��ɵ��" ,\
    "��Ҳ�գ���Ҳ�գ�������ϲ�����£��������������£���Ҳ���٣���Ҳΰ��"
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
//��ֹ�ػ����ڱ���
    void    __fastcall OnWmBkgnd(TMessage &Msg);
    /*  //�� API AnimateWindow(...)�г�ͻ ...ע��ע��
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
