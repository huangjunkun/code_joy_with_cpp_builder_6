
/*--------------------------------------------------------------------------

//  默认人机对战，人先下，人先执黑
本程序由黄俊坤精心打造，欢迎使用！谢谢！
描述：hjk 五子棋 1.0
作者：黄俊坤
声明：本程序代码可供学习，任何人可以修改复制，
但必须注明原作者信息
注意：版权所属：黄俊坤

/---------------------------------------------------------------------------*/
/*  其格式一般为: #Pragma Para
　　其中Para 为参数，下面来看一些常用的参数。

    (1)message 参数。 Message 参数是我最喜欢的一个参数，它能够在编译信息输出窗口中输出相应的信息，这对于源代码信息的控制是非常重要的。其使用方法为：
　　#Pragma message(“消息文本”)
　　当编译器遇到这条指令时就在编译输出窗口中将消息文本打印出来。
　　当我们在程序中定义了许多宏来控制源代码版本的时候，我们自己有可能都会忘记有没有正确的设置这些宏，此时我们可以用这条指令在编译的时候就进行检查。假设我们希望判断自己有没有在源代码的什么地方定义了_X86这个宏可以用下面的方法
　　#ifdef _X86
　　#Pragma message(“_X86 macro activated!”)
　　#endif
　　当我们定义了_X86这个宏以后，应用程序在编译时就会在编译输出窗口里显示“_X86 macro activated!”。我们就不会因为不记得自己定义的一些特定的宏而抓耳挠腮了。

    (2)另一个使用得比较多的pragma参数是code_seg。格式如：
　　#pragma code_seg(["section-name"[,"section-class"] ])
　　它能够设置程序中函数代码存放的代码段，当我们开发驱动程序的时候就会使用到它。
　　(3)#pragma once (比较常用）
　　只要在头文件的最开始加入这条指令就能够保证头文件被编译一次，这条指令实际上
    在VC6中就已经有了，但是考虑到兼容性并没有太多的使用它。
*/
#include <vcl.h>
#pragma hdrstop
/* (4)#pragma hdrstop表示预编译头文件到此为止，后面的头文件不进行预编译。
BCB可以预编译头文件以加快链接的速度，但如果所有头文件都进行预编译又可能
占太多磁盘空间，所以使用这个选项排除一些头文件。 */

#include "wuziqi.h"

//---------------------------------------------------------------------------
//有时单元之间有依赖关系，比如单元A依赖单元B，所以单元B要先于单元A编译。你可以用#pragma startup指定编译优先级
#pragma package(smart_init)//使用了#pragma package(smart_init) ，BCB就会根据优先级的大小先后编译。

#pragma resource "*.dfm" //表示把*.dfm文件中的资源加入工程。*.dfm中包括窗体外观的定义。

//---------------------------------------------------------------------------
/*  //OR :  NO!!!!!!??????
         //人机对战时电脑分析最优下棋方案结构变量
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
        bool    exit_flag = false;  */
//---------------------------------------------------------------------------
#include "MyFunction.cpp"
//---------------------------------------------------------------------------
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    //注意棋盘的x，y和数组行列相反 ！！！！！！！！！！！
    winner = ' ';
    //用于悔棋和人机对战时电脑根据其选择最优下棋方案的存放下棋位置数组！

    //索引以上两数组当前下棋位置
    back_i = 0;
    //人机对战标志
    computer_to_man = 1;
    //禁手规则标志 游戏默认禁手规则 和因禁手输赢标志
    NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
    //棋子标志
    black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//平局对手
    //black 黑方 先下棋
    player = 'b';
    //定义退出标志以避免在菜单确认退出之后又在窗口确认退出
    exit_flag = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    InitBoard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewGame1Click(TObject *Sender)
{
    //初始化棋盘
    if(winner==black)
    {
        ClipCursor(0);
        Image1->Visible = false;
        Label1->Caption="(Ctrl+n)继续比赛?";
        Label3->Visible = false;
        ScrollBox1->Visible = true;
    }
    if(winner==white)
    {
        ClipCursor(0);
        Image1->Visible = false;
        Label1->Caption="(Ctrl+n)继续比赛?";
        Label3->Visible = false;
        ScrollBox1->Visible = true;
    }
    InitBoard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
    //int     i;
    //控制键盘下棋位置，并限定在棋盘范围之内（以青色亮点为标志）
    if((Key=='d'||Key=='6')&&Shape1->Left-Image2->Left<440)// d键控制棋子向右移
        Shape1->Left=Shape1->Left+30;
    if((Key=='w'||Key=='8')&&Shape1->Top-Image2->Top>40)// w键控制棋子向上移
        Shape1->Top=Shape1->Top-30;
    if((Key=='a'||Key=='4')&&Shape1->Left-Image2->Left>40)// a键控制棋子向左移
        Shape1->Left=Shape1->Left-30;
    if((Key=='s'||Key=='5')&&Shape1->Top-Image2->Top<440)// s键控制棋子向下移
        Shape1->Top=Shape1->Top+30;
    if(Key==13)//回车键控制下棋 &&winner==' ' 在里面处理比较好些
    {
        if(winner!=' ')// 游戏输赢之后直接回车鼠标解锁
        {
            ClipCursor(0);
            if(winner=='w')
            {
                Image3->Visible = false;
                Label1->Caption="(Ctrl+n)继续比赛???";
                Label3->Visible = false;
                ScrollBox1->Visible = true;
            }
            else
            {
                ClipCursor(0);
                Image1->Visible = false;
                Label1->Caption="(Ctrl+n)继续比赛???";
                Label3->Visible = false;
                ScrollBox1->Visible = true;
            }
            return;
        }
        int ix,iy;
        ix=(Shape1->Left-15)/30; //将鼠标坐标位置转换为相应的数组位置或是相应棋盘位置
        iy=(Shape1->Top-15)/30;
        //注意棋盘的x，y和数组行列相反
        if(board[iy][ix]==empty)
        {
            back_x[back_i] = iy; //悔棋存放
            back_y[back_i] = ix;
            back_i++;
            Label2->Caption = "请您认真下棋！";
            if(player==black)
            {
                DrawChess(ix,iy,10,black);
                board[iy][ix]=black;
                player = 'w';
                Label1->Caption="白方请下棋";
            }
            else
            {
                DrawChess(ix,iy,10,white);
                board[iy][ix]=white;
                player = 'b';
                // Computer();
                Label1->Caption="黑方请下棋";
            }

            if(player == 'w'&&NO_three_and_three_flag==1)
            {
                if(NoThreeAndThree(iy,ix))
                {
                    break_three_and_three_flag = 1;
                    winner = 'w';
                    Label1->Caption="黑方禁手：白方赢！";
                    Gameover();
                }
            }

            if(IsWin(iy,ix)==black)
            {
                Label1->Caption="黑方赢，白方输";
                Gameover();
            }
            //处理当棋盘即将布满棋子时
            if(back_i==225)//走满了棋盘还没有输赢当然是平局啦！
            {
                Label1->Caption="黑白对战：平局！";
                winner = no_winner;
                Gameover();
            }
            if((IsWin(iy,ix)==white)&&computer_to_man==0)
            {
                Label1->Caption="白方赢，黑方输";
                Gameover();
            }

            if(computer_to_man == 1&&winner==' ')
            {
                Computer(); //;
                player = 'b'; //下一步就黑方下棋
                if(IsWin(bestpos.x,bestpos.y)==white)
                {
                    Label1->Caption="白方赢，黑方输";
                    Gameover();
                }
                Label1->Caption="黑方请下棋...";
            }

        }

        else
            Label2->Caption = "您现在不能在此下棋子！"; //StatusLine->Panels->Items[5]->Text="Can't put chess here!";

        Update();   // 更新数据、、、
        /*
         if(IsWin(iy,ix)==black)
         {
                 Label1->Caption="黑方赢，白方输";
                 Gameover();
         }
         if((IsWin(iy,ix)==white))
         {
                 Label1->Caption="白方赢，黑方输";
                 Gameover();
         }
         */
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Return1Click(TObject *Sender)
{
    if(winner==no_winner)
    {
        Label1->Caption="平局!\n抱歉您不能悔棋了!";
        return;
    }

    if(back_i!=0)
    {
        back_i--;
        //在黑方未获胜且没有出现禁手的条件下，和电脑对弈悔棋定为两步、、、
        if(computer_to_man==1&&winner!='b'&&!break_three_and_three_flag)
        {
            //&&(NO_three_and_three_flag==1&&winner==white)
            board[back_x[back_i]][back_y[back_i]] = empty;
            //画回圆为之前的背景颜色、、、
            DrawChess(back_y[back_i],back_x[back_i],10,gray);
            //恢复棋盘的网格、、、
            {
                Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
                Image2->Canvas->MoveTo(back_y[back_i]*30+30,back_x[back_i]*30+30-12);  //行
                Image2->Canvas->LineTo(back_y[back_i]*30+30,back_x[back_i]*30+30+12);
                Image2->Canvas->MoveTo(back_y[back_i]*30+30-12,back_x[back_i]*30+30);  //列
                Image2->Canvas->LineTo(back_y[back_i]*30+30+12,back_x[back_i]*30+30);
            }
            /*
                          Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
                          Image2->Canvas->LineTo(back_y[back_i]*30+30-15,back_y[back_i]*30+30+15);

                          {
                          Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
                          Image2->Canvas->MoveTo(back_y[back_i]*30+30,30);  //行
                          Image2->Canvas->LineTo(back_y[back_i]*30+30,451);
                          Image2->Canvas->MoveTo(30,back_x[back_i]*30+30);  //列
                          Image2->Canvas->LineTo(450,back_x[back_i]*30+30);
                          }
                          */
            back_i--;
        }

        player = board[back_x[back_i]][back_y[back_i]];
        board[back_x[back_i]][back_y[back_i]] = empty;
        //画回圆为之前的背景颜色、、、
        //注意：棋盘的行列（x，y）和数组行列相反

        DrawChess(back_y[back_i],back_x[back_i],10,gray);
        //恢复棋盘的网格、、、
        {
            Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
            Image2->Canvas->MoveTo(back_y[back_i]*30+30,back_x[back_i]*30+30-12);  //行
            Image2->Canvas->LineTo(back_y[back_i]*30+30,back_x[back_i]*30+30+12);
            Image2->Canvas->MoveTo(back_y[back_i]*30+30-12,back_x[back_i]*30+30);  //列
            Image2->Canvas->LineTo(back_y[back_i]*30+30+12,back_x[back_i]*30+30);
        }
        /*
                  Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
                  Image2->Canvas->LineTo(back_y[back_i]*30+30-15,back_y[back_i]*30+30+15);

                  {
                  Image2->Canvas->Pen->Color=clBlack;// 给点画笔颜色为黑色
                  Image2->Canvas->MoveTo(back_y[back_i]*30+30,30);  //行
                  Image2->Canvas->LineTo(back_y[back_i]*30+30,451);
                  Image2->Canvas->MoveTo(30,back_x[back_i]*30+30);  //列
                  Image2->Canvas->LineTo(450,back_x[back_i]*30+30);
                  } */

        if(player=='w')
            Label1->Caption="悔棋成功,白方下棋！";
        else
            Label1->Caption="悔棋成功,黑方下棋！";
    }
    else
        Label1->Caption="抱歉您不能悔棋了！";
    Shape1->Left=Image2->Left+back_y[back_i]*30+30;//标明之前对方下棋子位置
    Shape1->Top=Image2->Top+back_x[back_i]*30+30;
    winner = ' ';
    break_three_and_three_flag = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{

    if(Application->MessageBoxA("您是否真的要退出游戏？","确认退出！",MB_YESNOCANCEL)==IDYES)
    {
        exit_flag = true;
        Close();
    }

}
//---------------------------------------------------------------------------
//注意棋盘的x，y和数组行列相反 !!!!!!
void __fastcall TMainForm::Image1MouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //鼠标右键直接返回，以显示菜单不予下棋
    if(Button==mbRight)
        return;
    int ix,iy;
    ix=(X-15)/30; //将鼠标坐标位置转换为相应的数组位置或是相应棋盘位置
    iy=(Y-15)/30; //ix实际为数组的列，iy实际为数组的行

    //控制鼠标下棋位置，并限定在棋盘范围之内
    if(ix<0||iy<0||ix>14||iy>14)
        return;

    if(board[iy][ix]==empty&&winner==' ')
    {
        back_x[back_i] = iy; //悔棋存放
        back_y[back_i] = ix;
        back_i++;
        Label2->Caption = "请您认真下棋！";
        if(player==black)
        {
            DrawChess(ix,iy,10,black);
            board[iy][ix]=black;
            player = 'w';
            Label1->Caption="白方请下棋...";
        }
        else
        {
            DrawChess(ix,iy,10,white);
            board[iy][ix]=white;
            player = 'b';
            Label1->Caption="黑方请下棋...";
        }
        Shape1->Left=Image2->Left+ix*30+25;//标明之前对方下棋子位置
        Shape1->Top=Image2->Top+iy*30+25;
        if(player == 'w'&& NO_three_and_three_flag==1)
        {
            if(NoThreeAndThree(iy,ix))
            {
                break_three_and_three_flag = 1;
                winner = 'w';
                Label1->Caption="黑方禁手：白方赢！";
                Gameover();
            }

        }

        if(IsWin(iy,ix)==black)
        {
            Label1->Caption="黑方赢，白方输";
            Gameover();
        }
        //处理当棋盘即将布满棋子时
        if(back_i==225)//走满了棋盘还没有输赢当然是平局啦！
        {
            Label1->Caption="黑白对战：平局！";
            winner = no_winner;
            Gameover();
        }
        if((IsWin(iy,ix)==white)&&computer_to_man==0)
        {
            Label1->Caption="白方赢，黑方输";
            Gameover();
        }

        if(computer_to_man == 1&&winner==' ')
        {
            Computer(); //;
            player = 'b'; //下一步就黑方下棋
            if(IsWin(bestpos.x,bestpos.y)==white)
            {
                Label1->Caption="白方赢，黑方输";
                Gameover();
            }
            //if(winner==' ')
            else //用else效率比较高！
                Label1->Caption="黑方请下棋...";
        }
    }
    else
        Label2->Caption = "您现在不能在此下棋子！"; //StatusLine->Panels->Items[5]->Text="Can't put chess here!";

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image3Click(TObject *Sender)
{
    ClipCursor(0);
    Image3->Visible = false;
    Label1->Caption="(Ctrl+n)继续比赛???";
    Label3->Visible = false;
    ScrollBox1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1Click(TObject *Sender)
{
    ClipCursor(0);
    Image1->Visible = false;
    Label1->Caption="(Ctrl+n)继续比赛???";
    Label3->Visible = false;
    ScrollBox1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Image5Click(TObject *Sender)
{
    ClipCursor(0);
    Image5->Visible = false;
    Label1->Caption="(Ctrl+n)继续比赛???";
    Label3->Visible = false;
    ScrollBox1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Mantoman1Click(TObject *Sender)
{
    Mantoman1->Checked = true;
    Computertoman1->Checked = false;
    Mantoman2->Checked = true;
    Computertoman2->Checked = false;
    computer_to_man = 0;
    InitBoard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Computertoman1Click(TObject *Sender)
{
    Mantoman1->Checked = false;
    Computertoman1->Checked = true;
    Mantoman2->Checked = false;
    Computertoman2->Checked = true;
    computer_to_man = 1;
    InitBoard();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Switch_playerClick(TObject *Sender)
{
    //若游戏已分出胜负切换无效！！！
    if(winner!= ' ')
    {
        Label1->Caption="切换对手无效！";
        return;
    }
    if(computer_to_man==1)
    {
        computer_to_man = 0;
        Mantoman1->Checked = true;
        Computertoman1->Checked = false;
        Mantoman2->Checked = true;
        Computertoman2->Checked = false;
        computer_to_man = 0;

    }
    else
    {
        computer_to_man = 1;
        Mantoman1->Checked = false;
        Computertoman1->Checked = true;
        Mantoman2->Checked = false;
        Computertoman2->Checked = true;
        computer_to_man = 1;

        if(player=='w')
        {
            Computer();
            player = 'b'; //下一步就黑方下棋
            if(IsWin(bestpos.x,bestpos.y)==white)
            {
                Label1->Caption="白方赢，黑方输";
                Gameover();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Computertocomputer1Click(TObject *Sender)
{
    //该功能还未实现！！！！！！
    /*
    while(true)
    {
    if(player=='b')
    {
        Computer(); //
        player = 'w';
        if(IsWin(bestpos.x,bestpos.y)==black)
        {
                Label1->Caption="黑方赢，白方输";
                Gameover();
        }


    }
    else
    {
        Computer(); //
        player = 'b';
        if(IsWin(bestpos.x,bestpos.y)==white)
        {
                Label1->Caption="白方赢，黑方输";
                Gameover();
        }
    }
    if(winner!=' ')
        break;
    }
    */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject *Sender)
{
    //以下三种信息框任选
    //ShowMessage("!!! 该程序由黄俊坤精心打造 !!! \n     !!!软件工程（三）班!!!   \n      !!! 学号06065072 !!!     \n           !!! 谢谢 !!!          ");
    Application->MessageBoxA("      !星仔生日快乐！\n！！！hjk 五子棋 1.0\n\n！！！该程序由黄俊坤精心打造 ！！！\n\n     ！！！软件工程（三）班！！！   \n\n      ！！！ 学号06065072 ！！！     \n\n           ！！！ 谢谢 ！！！           ","软件版本",MB_OK);
    //MessageBox(Handle ,"!!! 该程序由黄俊坤精心打造 !!! \n\n     !!!软件工程（三）班!!!   \n\n      !!! 学号06065072 !!!     \n\n           !!! 谢谢 !!!           ","软件版本",MB_OK);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Rule1Click(TObject *Sender)//三三禁手设置
{
    if(NO_three_and_three_flag==1)
    {
        Rule1->Checked = false;
        Rule2->Checked = false;
        NO_three_and_three_flag = 0;
        Application->MessageBoxA("成功取消禁手规则","三三禁手规则提示！",MB_OK);
    }
    else
    {
        Rule1->Checked = true;
        Rule2->Checked = true;
        NO_three_and_three_flag = 1;
        Application->MessageBoxA("成功设置禁手规则","三三禁手规则提示！",MB_OK);
    }
}
//---------------------------------------------------------------------------

//关闭窗口确认！
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(exit_flag == true||Application->MessageBoxA("您是否真的要退出游戏？","确认退出！",MB_YESNOCANCEL)==IDYES)
        CanClose=true;
    else
        CanClose=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Help2Click(TObject *Sender)
{

    ShellExecute(Handle,"open","help.doc",NULL,NULL,SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------



