//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Head.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <winuser.h>
#include <jpeg.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Graphics.hpp>

#define		INIT_PLACE	65	//left��ʼ������λ��--�߶�Ϊ0
#define		SIDE		30//����߳�
#define		PIECE		4 //������Ŀ
#define		DOWN		30//����λ��==SIDE
#define		ROW		20
#define		COL		10


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer_Down;
    TTimer *Timer_Display;
    TGroupBox *GroupBoxGame;
    TPanel *Panel_R;
    TShape *ShapeExample;
    TPanel *Panel_Client;
    TImage *ImageBackground;
    TPopupMenu *PopupMenu1;
    TMenuItem *Game1;
    TMenuItem *ExitItem;
    TMenuItem *PauseItem;
    TMenuItem *ContinueItem;
    TMenuItem *NewGameItem;
    TMenuItem *SetGame1;
    TMenuItem *AutoPlayItem;
    TMenuItem *Help1;
    TMenuItem *AboutItem;
    TMenuItem *HelpItem;
    TMenuItem *LevelSetItem;
    TMenuItem *interfaceSetItem;
    TPageControl *PageControlSet;
    TTabSheet *TabSheetLevel;
    TLabel *LabelLevel;
    TComboBox *ComboBoxLevel;
    TTabSheet *TabSheetFace;
    TGroupBox *GroupBoxSet;
    TBitBtn *BitBtnOK;
    TBitBtn *BitBtnNO;
    TSavePictureDialog *SavePictureDialog1;
    TBitBtn *BitBtnImage;
    TTrackBar *TrackBarAP;
    TLabel *LabelAP;
    TColorDialog *ColorDialog1;
    TCheckBox *cbRandColor;
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TLabel *LabelHello;
    TLabel *LabelScore;
    TCheckBox *CBPlayMusic;
    TTrackBar *tbMainVolume;
    TTrackBar *tbLeftVolume;
    TTrackBar *tbRightVolume;
    void __fastcall Timer_DownTimer(TObject *Sender);
    void __fastcall NewGameItemClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ContinueItemClick(TObject *Sender);
    void __fastcall PauseItemClick(TObject *Sender);
    void __fastcall ExitItemClick(TObject *Sender);
    void __fastcall HelpItemClick(TObject *Sender);
    void __fastcall AboutItemClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AutoPlayItemClick(TObject *Sender);
    void __fastcall Timer_DisplayTimer(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
                                  TShiftState Shift, int X, int Y);
    void __fastcall BitBtnNOClick(TObject *Sender);
    void __fastcall BitBtnImageClick(TObject *Sender);
    void __fastcall ComboBoxLevelChange(TObject *Sender);
    void __fastcall LevelSetItemClick(TObject *Sender);
    void __fastcall BitBtnOKClick(TObject *Sender);
    void __fastcall TrackBarAPChange(TObject *Sender);
    void __fastcall cbRandColorClick(TObject *Sender);
    void __fastcall Image1DblClick(TObject *Sender);
    void __fastcall Image2DblClick(TObject *Sender);
    void __fastcall Image3DblClick(TObject *Sender);
    void __fastcall CBPlayMusicClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall tbMainVolumeChange(TObject *Sender);
    void __fastcall tbLeftVolumeChange(TObject *Sender);
    void __fastcall tbRightVolumeChange(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
                                TShiftState Shift);
    void __fastcall ImageBackgroundMouseDown(TObject *Sender,
            TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
    TMediaPlayer *MediaPlayer;
    typedef struct Position
    {
        int	    Left_Top[4][2];

    } Position;
    typedef struct Value
    {
        int     LackNum;//©�շ�����
        int     FullNum;//��������
        int     Height;//λ�õĸ߶ȣ��������Ӧ���кţ�Խ��Խ�ã�ʵ�ʵ�Խ��Խ��
    } Value;//������ŵļ�ֵ
    typedef struct BestPlan
    {
        Position    Pos;//��Ӧ�ķ���λ�ã���״��
        int     Kind;//���෽�����Ӧ����
        int     Move;//����ˮƽ�ƶ�λ�ƣ��������Ҹ�������
    } BestPlan;//�������λ�ã�������

    typedef	vector<Position> Position_Vec;//ͬһ�෽��Ĳ�ͬ����
    typedef vector<Position_Vec>	Diamonds_Vec;//�������ࡢ����
    Position    savepos; // ��¼ԭʼ���ͷ���λ��
    int     save_position_kind;//��¼ԭʼ���ͷ�������
    Position    changepos; // ��¼���任�����鲻ͬ����ԭʼλ��
    Position    lowpos;// ��¼�����ڲ�ͬ�е���λ��
    //��ǰ����cur_diamonds[0] ������λ��
    int     First_Left ,First_Top;
    //��¼ next����͵�ǰ�����������ࣩ����״
    int     pre_diamonds_kind ,diamonds_kind;
    int     pre_position_kind ,position_kind;
    //��Ų�ͬ����ĸ�������//�ܹ����߸�����
    Diamonds_Vec	diamonds_vec;
    //  next����͵�ǰ����
    TShape *cur_diamonds[PIECE];
    TShape *pre_diamonds[PIECE];
    //�����Ϸ�����еķ���--ͬʱ��¼��λ�ã���壩
    TShape *board[ROW][COL] ,*temp_board[ROW][COL];
    bool    exit_flag; // //��Ϸ�Գ���־
    bool    ScanForward; //ɨ�跽���־
    //ɨ��֮�������ֵ����ѷ��� ���ṹ��--���ϣ�
    Value   maxvalue;
    BestPlan    bestplan;
    //��Ϸ������־
    bool    gameoverflag;
    TColor  DiamondsColor;

public:		// User declarations
    void    Init_Position(int First_Teft,int First_Top);
    void    New_Diamonds();  //TObject *Sender
    bool    Check_Move(char Key);//   ,TShape* *cur_diamonds
    bool    Check_Change();     //int left ,int top
    bool    Check_End();
    bool    Check_Dead(int Left_Top[4][2]);  //   (int left ,int top)
    void    NewGame();//TObject *Sender
    bool    Remove_Diamonds();
    bool    Check_Row_Full(int row);
    bool    Delete_Row_Full(int row);
    void    OutBoard(ostream& fout);

    void    AutoPlay();  //TObject *Sender
    void    ScanBoard(bool    ScanForward);   //TObject *Sender
    void    PlaceDiamonds();
    void    SaveBoard();
    void    LoadBoard();
    int     CountLackNum();
    bool    CountValue();
    void    UpdateBestplan(Value curvalue);
    //bool    CheckEdge(char Key);

    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
