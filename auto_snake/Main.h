//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>

#include <vector>
using namespace std;

//---------------------------------------------------------------------------

#define UP      '8'//VK_UP
#define DOWN    '5'//VK_DOWN
#define LEFT    '4'//VK_LEFT
#define RIGHT   '6'//VK_RIGHT
#define STOP    '0'//VK_RIGHT
#define MAN           true
#define COMPUTER      false
//#define MAX_LEN      30      //


//---------------------------------------------------------------------------

class   MySnake //
{
private:
//public:
    char    go_direction_flag;
//        int     TShape_nums ,snake_length;
    bool    food_exist;
    long     count_time;  //游戏一回合计时、、、
    int     one_time;
    bool    player;
    unsigned int     max_speed ,up_speed;
    int     X_max ,Y_max;
    unsigned int     max_length;
    int     init_speed;
    TTimer  *TimerGo; //,*TimerFood
    vector<TShape*> Shape_vec;  // ShapeArray
    //TShape  **ShapeArray;
    static  int     SnakeNum;
public:
    TShape  *Shape_Head;
    /* 0号单元不用，最后一个单元为snake_length==max_length 时 食物预用  */
    void    MoveSnake();
    void    NewShape();
    void    FindDirection();
    void    InitSnake();
    void    GetFood();
    void    __fastcall TimerGoTimer(TObject *Sender);
    MySnake()
    {
        Shape_Head = NULL;
        TimerGo = NULL;
    };
    //MySnake(int length);
    MySnake(TShape *Head ,int length = 20);
    ~MySnake();
};
//---------------------------------------------------------------------------
int     MySnake::SnakeNum = 0;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer_Go;
    TTimer *Time_Food;
    TLabel *DeaFlag;
    TLabel *Label_X;
    TLabel *Label_Y;
    TPopupMenu *PopupMenu1;
    TMenuItem *ItemPause;
    TMenuItem *ContinueItem;
    TMenuItem *ItemExit;
    TMenuItem *ItemSetGame;
    TImage *Image_Client;
    TMenuItem *ItemAddSnake;
    TMenuItem *ItemDelSnake;
    TShape *Shape_Head;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *ItemBackground;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer_GoTimer(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall Time_FoodTimer(TObject *Sender);
    void __fastcall ItemPauseClick(TObject *Sender);
    void __fastcall ContinueItemClick(TObject *Sender);
    void __fastcall ItemExitClick(TObject *Sender);
    void __fastcall ItemSetGameClick(TObject *Sender);
    void __fastcall Image_ClientMouseDown(TObject *Sender,
                                          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ItemAddSnakeClick(TObject *Sender);
    void __fastcall ItemDelSnakeClick(TObject *Sender);
    void __fastcall ItemBackgroundClick(TObject *Sender);



private:	// User declarations
    char    go_direction_flag;
    int     TShape_nums ,snake_length;
    bool    food_exist;
    long     count_time;  //游戏一回合计时、、、
    unsigned int     max_speed ,up_speed;
    bool    player;
    bool    mouse_exist;
    int     X_max ,Y_max;
    int     MAX_LEN;
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);

    TShape **ShapeArray;
    /* 0号单元不用，最后一个单元为snake_length==Max_length 时 食物预用  */
    void    Move_Snake();
    void    New_Shape();
    void    Find_Direction();
    void    Init_Snake();
    void    Get_Food();
    friend  MySnake;

    //vector<TShape*>  TShape_vec;
    //TShape TShapeArray[10];
    //TShapeArray = (TShape)malloc( 10*sizeof(TShape) );

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
