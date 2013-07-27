//---------------------------------------------------------------------------

#ifndef wuziqiH
#define wuziqiH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------

#include <string>
#include <shellapi.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <fstream.h>
#include <fcntl.h>
#include <io.h>
using namespace std;
//---------------------------------------------------------------------------
//定义最佳位置为结构体、、、
struct	best
{
    int	from;//来自于四个方向的其一：1，横 2，竖 3，正对角线 4，负对角线
    int	x ,y;//最佳位置
};
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TImage *Image1;
    TImage *Image2;
    TLabel *Label2;
    TImage *Image3;
    TShape *Shape1;
    TMainMenu *MainMenu1;
    TMenuItem *d1;
    TMenuItem *NewGame1;
    TMenuItem *Return1;
    TMenuItem *Exit1;
    TMenuItem *Playmaner1;
    TMenuItem *Mantoman1;
    TMenuItem *Computertoman1;
    TPopupMenu *PopupMenu1;
    TLabel *Label3;
    TMenuItem *Switch_player;
    TMenuItem *Help1;
    TMenuItem *Help2;
    TMenuItem *About1;
    TLabel *Label4;
    TScrollBox *ScrollBox1;
    TImage *Image4;
    TMenuItem *Computertocomputer1;
    TMenuItem *Rule1;
    TMenuItem *Return2;
    TMenuItem *Switchplayer1;
    TMenuItem *Mantoman2;
    TMenuItem *Computertoman2;
    TMenuItem *Rule2;
    TMenuItem *NewGame2;
    TMenuItem *Exit2;
    TImage *Image5;
    void __fastcall Image1MouseDown(TObject *Sender,
                                    TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall Image3Click(TObject *Sender);
    void __fastcall Image1Click(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall NewGame1Click(TObject *Sender);
    void __fastcall Return1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Mantoman1Click(TObject *Sender);
    void __fastcall Computertoman1Click(TObject *Sender);
    void __fastcall Switch_playerClick(TObject *Sender);
    void __fastcall Computertocomputer1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall Rule1Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall Help2Click(TObject *Sender);
    void __fastcall Image5Click(TObject *Sender);

private:	// User declarations

public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void   DrawChess(int x,int y,int r,char color);
    void   InitBoard();
    char   IsWin(int row , int col);
    void   Gameover();
    void   Computer();
    //人机对战电脑选择最优下棋位置相关函数说明！
    best	SearchForFirst(int row ,int col ,string item);
    //根据给定棋子位置(row，col)的四个方向，从中找出和item字符串一致相应位置，并返回第一个位置！
    best	SearchForBest();//电脑（白方）找出最佳下棋位置
    void	FirstChangeBest(best& b ,int i);//将函数search_for_first返回的第一个位置转化为最佳位置！
    bool    NoThreeAndThree(int row ,int col); //游戏是三三禁手规则

    best    bestpos;
    //注意棋盘的x，y和数组行列相反 ！！！！！！！！！！！
    char    winner ,board[15][15] ,back_board[15][15];
    //用于悔棋和人机对战时电脑根据其选择最优下棋方案的存放下棋位置数组！
    //  back_x[225] , back_y[225] ,数据一一对应
    int     back_x[225] , back_y[225];
    //索引以上两数组当前下棋位置
    int     back_i;
    //人机对战标志
    int     computer_to_man;
    //禁手规则标志 游戏默认禁手规则 和因禁手输赢标志
    int     NO_three_and_three_flag ,break_three_and_three_flag;
    //棋子标志
    char    black ,white  ,gray  ,empty   ,no_winner;//平局对手
    //black 黑方 先下棋
    char    player;
    //定义退出标志以避免在菜单确认退出之后又在窗口确认退出
    bool    exit_flag;

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
/*// OR :
//人机对战时电脑分析最优下棋方案结构变量
//#ifndef DATAH
//#define DATAH
        best    bestpos;
        //注意棋盘的x，y和数组行列相反 ！！！！！！！！！！！
        char    winner = ' ',board[15][15] ,back_board[15][15];
        //用于悔棋和人机对战时电脑根据其选择最优下棋方案的存放下棋位置数组！
        //  back_x[225] , back_y[225] ,数据一一对应
        int     back_x[225] , back_y[225];
        //索引以上两数组当前下棋位置
        int     back_i = 0;
        //人机对战标志
        int     computer_to_man = 1;
        //禁手规则标志 游戏默认禁手规则 和因禁手输赢标志
        int     NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
        //棋子标志
        const  char black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//平局对手
        //black 黑方 先下棋
        static char player = 'b';
        //定义退出标志以避免在菜单确认退出之后又在窗口确认退出
        bool    exit_flag = false;      */
//#endif

//---------------------------------------------------------------------------
#endif
