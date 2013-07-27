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
//�������λ��Ϊ�ṹ�塢����
struct	best
{
    int	from;//�������ĸ��������һ��1���� 2���� 3�����Խ��� 4�����Խ���
    int	x ,y;//���λ��
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
    //�˻���ս����ѡ����������λ����غ���˵����
    best	SearchForFirst(int row ,int col ,string item);
    //���ݸ�������λ��(row��col)���ĸ����򣬴����ҳ���item�ַ���һ����Ӧλ�ã������ص�һ��λ�ã�
    best	SearchForBest();//���ԣ��׷����ҳ��������λ��
    void	FirstChangeBest(best& b ,int i);//������search_for_first���صĵ�һ��λ��ת��Ϊ���λ�ã�
    bool    NoThreeAndThree(int row ,int col); //��Ϸ���������ֹ���

    best    bestpos;
    //ע�����̵�x��y�����������෴ ����������������������
    char    winner ,board[15][15] ,back_board[15][15];
    //���ڻ�����˻���սʱ���Ը�����ѡ���������巽���Ĵ������λ�����飡
    //  back_x[225] , back_y[225] ,����һһ��Ӧ
    int     back_x[225] , back_y[225];
    //�������������鵱ǰ����λ��
    int     back_i;
    //�˻���ս��־
    int     computer_to_man;
    //���ֹ����־ ��ϷĬ�Ͻ��ֹ��� ���������Ӯ��־
    int     NO_three_and_three_flag ,break_three_and_three_flag;
    //���ӱ�־
    char    black ,white  ,gray  ,empty   ,no_winner;//ƽ�ֶ���
    //black �ڷ� ������
    char    player;
    //�����˳���־�Ա����ڲ˵�ȷ���˳�֮�����ڴ���ȷ���˳�
    bool    exit_flag;

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
/*// OR :
//�˻���սʱ���Է����������巽���ṹ����
//#ifndef DATAH
//#define DATAH
        best    bestpos;
        //ע�����̵�x��y�����������෴ ����������������������
        char    winner = ' ',board[15][15] ,back_board[15][15];
        //���ڻ�����˻���սʱ���Ը�����ѡ���������巽���Ĵ������λ�����飡
        //  back_x[225] , back_y[225] ,����һһ��Ӧ
        int     back_x[225] , back_y[225];
        //�������������鵱ǰ����λ��
        int     back_i = 0;
        //�˻���ս��־
        int     computer_to_man = 1;
        //���ֹ����־ ��ϷĬ�Ͻ��ֹ��� ���������Ӯ��־
        int     NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
        //���ӱ�־
        const  char black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//ƽ�ֶ���
        //black �ڷ� ������
        static char player = 'b';
        //�����˳���־�Ա����ڲ˵�ȷ���˳�֮�����ڴ���ȷ���˳�
        bool    exit_flag = false;      */
//#endif

//---------------------------------------------------------------------------
#endif
