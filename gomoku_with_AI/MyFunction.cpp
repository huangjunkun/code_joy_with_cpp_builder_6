
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "wuziqi.h"
//---------------------------------------------------------
/*  //OR :   NO!!!!!!??????
        //人机对战时电脑分析最优下棋方案结构变量
extern        best    bestpos;
        //注意棋盘的x，y和数组行列相反 ！！！！！！！！！！！
extern        char    winner = ' ',board[15][15] ,back_board[15][15];
        //用于悔棋和人机对战时电脑根据其选择最优下棋方案的存放下棋位置数组！
        //  back_x[225] , back_y[225] ,数据一一对应
extern        int     back_x[225] , back_y[225];
        //索引以上两数组当前下棋位置
extern        int     back_i = 0;
        //人机对战标志
extern        int     computer_to_man = 1;
        //禁手规则标志 游戏默认禁手规则 和因禁手输赢标志
extern        int     NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
        //棋子标志
extern        const  char black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//平局对手
        //black 黑方 先下棋
extern        char player = 'b';
        //定义退出标志以避免在菜单确认退出之后又在窗口确认退出
extern        bool    exit_flag = false;   */
//---------------------------------------------------------

//---------------------------------------------------------
void    TMainForm::InitBoard()
{
    winner = ' ';
    Image1->Visible = false; //  黑方获胜标志 、、、
    Image3->Visible = false;//   白方获胜标志
    player = 'b'; //初始化黑方先下棋、、、
    back_i = 0; //初始化悔棋设置、、、
    Label3->Visible = false;

    Image2->Canvas->Pen->Color=clGray;//初始化棋盘背景
    for(int i=0; i<481; i++)
    {
        Image2->Canvas->MoveTo(i,0);
        Image2->Canvas->LineTo(i,481);
    }
    Image2->Canvas->Pen->Color=clBlack;// 初始化棋盘网格
    for(int i=30; i<=450; i+=30)
    {
        Image2->Canvas->MoveTo(i,30);   //列
        Image2->Canvas->LineTo(i,450);
        Image2->Canvas->MoveTo(30,i);   //行
        Image2->Canvas->LineTo(450,i);
    }
    for(int i=3; i<=13; i+=4) //格式棋盘之中的黑点标志
        for(int j=3; j<=13; j+=4)
            DrawChess(i,j,3,black);
    //初始化数组、、、
    for(int i=0; i<=14; i++)
        for(int j=0; j<=14; j++)
            board[i][j]=empty;
    for(int i=0; i<=5; i++)
        // StatusLine->Panels->Items[i]->Text=" ";//界面下方的状态显示
        Label1->Caption="游戏开始！";
    Shape1->Left=Image2->Left+240-4;//键盘下棋子标志
    Shape1->Top=Image2->Top+240-4;
}
//---------------------------------------------------------
void   TMainForm::DrawChess(int x,int y,int r,char color) //r为棋子大小
{
    x = x*30+30; //?????
    y = y*30+30;
    //x=(x-3)*20;
    //y=(y-3)*20;
    if(color==gray)
    {
        Image2->Canvas->Pen->Color=clGray;//棋子边缘颜色
        Image2->Canvas->Brush->Color=clGray;//棋子颜色、、、

    }
    else
    {
        if(color==black)//  white    //棋盘中的黑点标志
        {
            Image2->Canvas->Pen->Color=clBlack;//棋子边缘颜色
            Image2->Canvas->Brush->Color=clBlack;//棋子颜色、、、、
        }
        else
        {
            Image2->Canvas->Pen->Color=clWhite;
            Image2->Canvas->Brush->Color=clWhite;
        }
    }
    Image2->Canvas->Ellipse(x-r,y-r,x+r+1,y+r+1); //画圆
}
//---------------------------------------------------------------------------

char    TMainForm::IsWin(int row , int col) //列，行
{
    int     i , j;
    string   str_w = "wwwww" , str_b = "bbbbb";
    string   s;
    char    array[16];
    array[15] = '\0';////多定义一个元素为存放'\0’，方便转化string
    // 横向判断输赢
    for(i=0; i<15; i++)
        array[i] = board[row][i];

    s = array;
    if(s.find(str_w,0)< s.length())
    {
        winner = 'w';
        return 'w';//白方获胜、、、
    }
    if(s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//白方获胜、、、
    }
    //纵向判断输赢
    for(i=0; i<15; i++)
        array[i] = board[i][col];
    s = array;
    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//白方获胜、、、
    }

    if( s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//白方获胜、、、
    }
    // 对角线判断输赢 (2)
    if(row<=col)// LR左下到右上对角线 --即正对角线
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //去除遗留字符、、、、
        array[i] = ' ';
    s = array;

    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//白方获胜、、、
    }
    if( s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//白方获胜、、、
    }

    if(row+col<15)//RL右下到左上对角线 --即负对角线
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//去除遗留字符、、、、
    s = array;
    //s.append("\0");
    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//白方获胜、、、
    }

    if(s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//白方获胜、、、
    }
    return '*';
}
//---------------------------------------------------------------------------
//三三禁手判断：若在指定位置(row,col)下棋子出现函数NoThreeAndThree返回true，否则返回false

bool    TMainForm::NoThreeAndThree(int row ,int col)
{
    int     i ,j;
    int     three_and_three_nums = 0;
    string   s;
    char    array[16];
    array[15] = '\0';
    ////多定义一个元素为存放'\0’，方便转化string
    // 横向判断输赢
    for(i=0; i<15; i++)
        array[i] = board[row][i];

    s = array;
    {
        if(s.find("0bbb00",0)< s.length())
            three_and_three_nums++;

        else if(s.find("00bbb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0b0bb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0bb0b0",0)< s.size())
            three_and_three_nums++;
    }
    //纵向判断输赢
    for(i=0; i<15; i++)
        array[i] = board[i][col];
    s = array;
    {
        if(s.find("0bbb00",0)< s.length())
            three_and_three_nums++;

        else if(s.find("00bbb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0b0bb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0bb0b0",0)< s.size())
            three_and_three_nums++;
    }
    // 对角线判断输赢 (2)

    if(row<=col)// LR左下到右上对角线 --即正对角线
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //去除遗留字符、、、、
        array[i] = ' ';
    s = array;

    {
        if(s.find("0bbb00",0)< s.length())
            three_and_three_nums++;

        else if(s.find("00bbb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0b0bb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0bb0b0",0)< s.size())
            three_and_three_nums++;
    }
    if(row+col<15)//RL右下到左上对角线 --即负对角线
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//去除遗留字符、、、、
    s = array;
    //s.append("\0");
    {
        if(s.find("0bbb00",0)< s.length())
            three_and_three_nums++;

        else if(s.find("00bbb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0b0bb0",0)< s.size())
            three_and_three_nums++;

        else if(s.find("0bb0b0",0)< s.size())
            three_and_three_nums++;
    }
    if(three_and_three_nums>=2)
        return  true;
    else
        return  false;

}

//---------------------------------------------------------
void    TMainForm::Gameover()
{
    /*
    TRect MyArea=this->BitBtn1->BoundsRect;
    MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
    ClipCursor(&MyArea);
    */
    //锁定鼠标提示输赢，并以单击解锁
    ScrollBox1->Visible = false;
    if(winner==white)
    {
        Image3->Visible = true;
        TRect MyArea=this->Image3->BoundsRect;//锁定鼠标、、、
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    else if(winner==black)
    {
        Image1->Visible = true;
        TRect MyArea=this->Image1->BoundsRect;// 锁定鼠标、、、
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    else
    {
        Image5->Visible = true;
        TRect MyArea=this->Image5->BoundsRect;// 锁定鼠标、、、
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    Label3->Visible =true;
    Label3->Caption="请单击解锁或是直接回车！";

}

//---------------------------------------------------------------------------
best	TMainForm::SearchForFirst(int row ,int col ,string item)
{
    best	b;
    b.from = 0;
    int     i , j;
    string   s;
    char    array[16];
    array[15] = '\0';////多定义一个元素为存放'\0’，方便转化string
    // 横向判断输赢
    for(i=0; i<15; i++)
        array[i] = board[row][i];

    s = array;
    if(s.find(item,0)< s.size())
    {
        b.from = 1;
        b.x = row;
        b.y = s.find(item,0); //- 1
        return b;
    }
    //纵向判断输赢

    for(i=0; i<15; i++)
        array[i] = board[i][col];
    s = array;
    if(s.find(item,0)< s.size())
    {
        b.from = 2;
        b.x = s.find(item,0);  // - 1
        b.y = col;
        return b;
    }
    // 对角线判断输赢 (2)

    if(row<=col)// LR左下到右上对角线 --即正对角线
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //去除遗留字符、、、、
        array[i] = ' ';
    s = array;
    if(s.find(item,0)< s.size())
    {
        b.from = 3;
        if(row<=col)
        {
            b.x = s.find(item,0);  // - 1
            b.y = (col-row)+s.find(item,0);  // - 1
        }
        else
        {
            b.x = (row-col)+s.find(item,0);  //  - 1
            b.y = s.find(item,0);  // - 1
        }

        return b;
    }

    if(row+col<15)//RL右下到左上对角线 --即负对角线
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//去除遗留字符、、、、
    s = array;

    if(s.find(item,0)< s.size())
    {
        b.from = 4;
        if(row+col<15)
        {
            b.x = (row+col) - s.find(item,0); //  + 1
            b.y = s.find(item,0);  //     - 1
        }
        else
        {
            b.x = 14 - s.find(item,0); // + 1
            b.y = (row+col-14) + s.find(item,0); // - 1
        }

        return b;
    }

    return b;
}
//---------------------------------------------------------------------------
void	TMainForm::FirstChangeBest(best& b ,int i)
{
    if(i<=1)//
        return;
    switch(b.from)
    {
    case 1: //行
        //b.x = row;
        b.y = b.y+i-1;
        break;
    case 2:  //列
        b.x = b.x+i-1;
        break;
    case 3: //正对角线
        b.x = b.x+i-1;
        b.y = b.y+i-1;
        break;
    case 4: //负对角线
        b.x = b.x-i+1;
        b.y = b.y+i-1;
        break;
    default:
        ////......
        break;
    }
}
//---------------------------------------------------------------------------

//注意棋盘的x，y和数组行列相反 ！！！！！！！！！！！
void    TMainForm::Computer()
{
    //dots=0;
    //static  int     i=0;
    //best bestpos; //不在此定义，定义为全局变量比较好
    //man=false;
    bestpos = SearchForBest();
    //bestpos.x = i;
    //bestpos.y = i++;
    if(board[bestpos.x][bestpos.y]==empty)
    {
        board[bestpos.x][bestpos.y] = white;
        DrawChess(bestpos.y,bestpos.x,10,white);
        back_x[back_i] = bestpos.x; //悔棋存放
        back_y[back_i] = bestpos.y;
        back_i++;

    }
    else
        Label1->Caption="下棋有误！";

    //标明之前对方/(电脑）下棋子位置
    Shape1->Left=Image2->Left+bestpos.y*30+25;
    Shape1->Top=Image2->Top+bestpos.x*30+25;
    /* //该功能还未实现
    player = 'b'; //在外面执行为方便机-机对战！！！！
    if(iswin(bestpos.x,bestpos.y)==white)
        {
          Label1->Caption="白方赢，黑方输";
          Gameover();
        }      */
}
//---------------------------------------------------------------------------
//函数会产生一条有唯一特征码8070的警告信息，如此可暂时终止该警告。

#pragma warn - 8070 // Turn off the warning message for warning #8070


best	TMainForm::SearchForBest()
{
    int     i;
    best bestpos;
    if(back_i>=7)
    {

        //攻五
        for(int i=back_i; i>=3; i-=2)
            //for(int i=3;i<back_i;i+=2)
        {
            //i = back_i;// 循环判断比较，加大难度、、、所以这里省略、
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0wwww");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,1);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "w0www");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "ww0ww");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "www0w");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "wwww0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,5);
                return	bestpos;
            }
        }//for(int i=back_i;i>=3;i-=2)

        //防五
        for(int i=back_i; i>=3; i-=2)
        {
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0bbbb");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,1);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "b0bbb");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bb0bb");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bbb0b");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bbbb0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,5);
                return	bestpos;
            }
        }//for(int i=back_i;i>=3;i-=2)

    }//if(back_i>=7)
    if(back_i>=5)
    {

//攻四
        for(int i=back_i; i>=3; i-=2)
        {
            //i = back_i; // 循环判断比较，加大游戏难度、、、所以这里省略、
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "00www");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "www00");

            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0www0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,1);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0w0ww");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0ww0w");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "ww0w0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
        }// for(int i=back_i;i>=3;i-=2)

//防四
        for(int i=back_i; i>=3; i-=2)
        {
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0bbb0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,1);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bb0b0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0bb0b");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "b0bb0");//???!!!
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0b0bb");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0bb0b");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }
        }// for(int i=back_i;i>=3;i-=2)

    }//if(back_i>=5)


    if(back_i>=3)
    {

        //攻三
        for(int i=back_i; i>=3; i-=2)
        {
            //for(int i=3;i<=back_i;i+=2)         {
            //i = back_i;// 循环判断比较，加大难度、、、所以这里省略、
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0ww00");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "00ww0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0w00w");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "w00w0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-2],back_y[i-2], "0w0w0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
        }//for(int i=back_i;i>=3;i-=2)
        //防三

        for(int i=back_i; i>=3; i-=2)
        {
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0bb00");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,4);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "00bb0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }

            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "b00b0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,2);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0b00b");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
            bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "0b0b0");
            if(bestpos.from!=0)
            {
                FirstChangeBest(bestpos,3);
                return	bestpos;
            }
        }//for(int i=back_i;i>=3;i-=2)

    }//if(back_i>=3)
    /*
    bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "000bb");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,3);
        return	bestpos;
    }
        bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bb000");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,3);
        return	bestpos;
    }
        */
    /*
    for(int i=back_i;i>=3;i-=2)
    {
    bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "000bb");
            if(bestpos.from!=0)
            {
    FirstChangeBest(bestpos,3);
    return	bestpos;
            }
    bestpos = SearchForFirst(back_x[i-1],back_y[i-1], "bb000");
            if(bestpos.from!=0)
            {
    FirstChangeBest(bestpos,3);
    return	bestpos;
            }
    }//for(int i=back_i;i>=3;i-=2) */
    //攻二
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "0w000");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,3);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "00w00");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,2);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "000w0");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,3);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "0000w");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,4);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "w0000");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,2);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "0w");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,1);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-2],back_y[back_i-2], "w0");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,2);
        return	bestpos;
    }
    //防二
    static int      random_1 = 1; //游戏刚开始时控制变化白方 下棋落子位置
    if(random_1==1)
    {
        bestpos = SearchForFirst(back_x[back_i-1],back_y[back_i-1], "b0000");
        if(bestpos.from!=0)
        {
            static int      random_2 = 3; //控制变化起始时白方 下棋落子位置
            best    bestpos_temp;
            do
            {
                //即从正对角线开始
                bestpos_temp = bestpos;
                if(random_2==5)
                    random_2 = 1;
                bestpos_temp.from = random_2++;
                FirstChangeBest(bestpos_temp,2);
            }
            while((bestpos_temp.x>14 || bestpos_temp.y>14)||!(board[bestpos_temp.x][bestpos_temp.y]==empty));  //  !(bestpos.x>=0&&&&bestpos.y>=0&&)
            return	bestpos_temp;
        }
        random_1 = 2;
    }
    else
    {
        bestpos = SearchForFirst(back_x[back_i-1],back_y[back_i-1], "0000b");
        if(bestpos.from!=0)
        {
            FirstChangeBest(bestpos,4);//转化为第四个位置 即目标位置定位于第四个位置
            static int      random_2 = 3; //控制变化起始时白方 下棋落子位置
            best    bestpos_temp;
            do
            {
                //即从正对角线开始
                bestpos_temp = bestpos;
                if(random_2==5)
                    random_2 = 1;
                bestpos_temp.from = random_2++;
                FirstChangeBest(bestpos_temp,2);
            }
            while((bestpos_temp.x>14 || bestpos_temp.y>14)||!(board[bestpos_temp.x][bestpos_temp.y]==empty));  //  !(bestpos.x>=0&&&&bestpos.y>=0&&)
            return	bestpos_temp;
        }
        random_1 = 1;
    }
    bestpos = SearchForFirst(back_x[back_i-1],back_y[back_i-1], "0b");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,1);
        return	bestpos;
    }
    bestpos = SearchForFirst(back_x[back_i-1],back_y[back_i-1], "b0");
    if(bestpos.from!=0)
    {
        FirstChangeBest(bestpos,2);
        return	bestpos;
    }
}
//恢复该警告
#pragma warn + 8070 // Turn the warning message for warning #8070 back on
//---------------------------------------------------------------------------
