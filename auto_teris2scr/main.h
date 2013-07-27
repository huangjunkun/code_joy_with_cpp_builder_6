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

#define		INIT_PLACE	65	//left初始化方块位置--高度为0
#define		SIDE		30//方块边长
#define		PIECE		4 //方块数目
#define		DOWN		30//下移位移==SIDE
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
        int     LackNum;//漏空方块数
        int     FullNum;//消块行数
        int     Height;//位置的高度，（数组对应的行号）越高越好，实际的越低越好
    } Value;//方块落放的价值
    typedef struct BestPlan
    {
        Position    Pos;//对应的方块位置（形状）
        int     Kind;//该类方块的相应变形
        int     Move;//方块水平移动位移，正的向右负的向左；
    } BestPlan;//方块最佳位置（方案）

    typedef	vector<Position> Position_Vec;//同一类方块的不同方块
    typedef vector<Position_Vec>	Diamonds_Vec;//方块种类、、、
    Position    savepos; // 记录原始类型方块位置
    int     save_position_kind;//记录原始类型方块类型
    Position    changepos; // 记录（变换）方块不同类型原始位置
    Position    lowpos;// 记录方块在不同列的首位置
    //当前方块cur_diamonds[0] 的坐标位置
    int     First_Left ,First_Top;
    //记录 next方块和当前方块的类别（种类）和形状
    int     pre_diamonds_kind ,diamonds_kind;
    int     pre_position_kind ,position_kind;
    //存放不同方块的各个坐标//总共有七个分类
    Diamonds_Vec	diamonds_vec;
    //  next方块和当前方块
    TShape *cur_diamonds[PIECE];
    TShape *pre_diamonds[PIECE];
    //存放游戏过程中的方块--同时记录其位置（面板）
    TShape *board[ROW][COL] ,*temp_board[ROW][COL];
    bool    exit_flag; // //游戏对出标志
    bool    ScanForward; //扫描方向标志
    //扫描之后的最大价值与最佳方案 （结构体--见上）
    Value   maxvalue;
    BestPlan    bestplan;
    //游戏结束标志
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
