
//---------------------------------------------------------------------------
#include <vcl.h>
#include "main.h"


//---------------------------------------------------------------------------
void	TMainForm::Init_Position(int First_Left,int First_Top)
{
    diamonds_vec.clear();
    Position	position;
    Position_Vec	position_vec;
    //First_Left = INIT_PLACE;
    {
        //正方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    //diamonds_vec[1].push_back(position);//????????????
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//一分类
    position_vec.clear();
    {
        //横方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = position.Left_Top[1][0]+SIDE;
        position.Left_Top[2][1] = First_Top;
        position.Left_Top[3][0] = position.Left_Top[2][0]+SIDE;
        position.Left_Top[3][1] = First_Top;
    }
    position_vec.push_back(position);
    {
        //竖方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE*2;
        position.Left_Top[3][0] = First_Left;
        position.Left_Top[3][1] = First_Top+SIDE*3;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//二分类
    position_vec.clear();
    {
        //|_|方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left+SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        //_|-方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left-SIDE;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//三分类
    position_vec.clear();
    {
        // |_|方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left-SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left-SIDE;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        //-|_方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left+SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE*2;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//四分类
    position_vec.clear();
    {
        //-||方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left+SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        // __|方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left-SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left-SIDE*2;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    {
        //||_方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE*2;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        // |--方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left+SIDE*2;
        position.Left_Top[2][1] = First_Top;
        position.Left_Top[3][0] = First_Left;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//五分类
    position_vec.clear();
    {
        //||-方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        // |__方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left+SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE*2;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    {
        //_||方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE*2;
        position.Left_Top[3][0] = First_Left-SIDE;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        // --|方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left+SIDE*2;
        position.Left_Top[2][1] = First_Top;
        position.Left_Top[3][0] = First_Left+SIDE*2;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//六分类
    position_vec.clear();
    {
        //_|_方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left-SIDE;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    {
        // |-方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left+SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    {
        //-|-方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left+SIDE;
        position.Left_Top[1][1] = First_Top;
        position.Left_Top[2][0] = First_Left+SIDE+SIDE;
        position.Left_Top[2][1] = First_Top;
        position.Left_Top[3][0] = First_Left+SIDE;
        position.Left_Top[3][1] = First_Top+SIDE;
    }
    position_vec.push_back(position);
    {
        // -|方块
        position.Left_Top[0][0] = First_Left;//Left
        position.Left_Top[0][1] = First_Top;//Top
        position.Left_Top[1][0] = First_Left;
        position.Left_Top[1][1] = First_Top+SIDE;
        position.Left_Top[2][0] = First_Left-SIDE;
        position.Left_Top[2][1] = First_Top+SIDE;
        position.Left_Top[3][0] = First_Left;
        position.Left_Top[3][1] = First_Top+SIDE*2;
    }
    position_vec.push_back(position);
    diamonds_vec.push_back(position_vec);//七分类

}
//---------------------------------------------------------------------------
void   TMainForm::NewGame()   //  TObject *Sender
{
    LabelHello->Caption = " Hello World ";
    LabelScore->Caption = "0";
    Timer_Down->Enabled = false;

    for(int i=0; i<PIECE; i++)
    {
        /*  */
        if(pre_diamonds[i]!= NULL)
        {
            delete pre_diamonds[i];
            pre_diamonds[i] = NULL;
        }
    }
    for(int i=0; i<PIECE; i++)
    {
        //生成 方块pre_diamonds[4]
        TShape *shape;
        shape = new TShape(Application);
        shape->Parent = Panel_R;
        shape->Width = SIDE;
        shape->Height= SIDE;
        shape->Brush = ShapeExample->Brush;
        shape->Pen = ShapeExample->Pen;
        pre_diamonds[i] = shape;
    }
    Init_Position(INIT_PLACE ,0);
    pre_diamonds_kind = rand()%7;
    int change_num = diamonds_vec[pre_diamonds_kind].size();
    pre_position_kind = rand()%change_num;
    /*
    for(int i=0;i<PIECE;i++)
    {
        pre_diamonds[i]->Left = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][0];
        pre_diamonds[i]->Top = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][1];
    }
      */
    for(int i=0; i<ROW; i++)
        for(int j=0; j<COL; j++)
        {
            if(board[i][j]!=NULL)
            {
                delete  board[i][j];
                board[i][j] = NULL;
            }
        }
    /**/
    for(int i=0; i<PIECE; i++)
    {
        if(cur_diamonds[i]!= NULL)
        {
            delete cur_diamonds[i];
            cur_diamonds[i] = NULL;
        }
    }
    New_Diamonds();
    if(AutoPlayItem->Checked==false)
        Timer_Down->Enabled = true;
}
//---------------------------------------------------------------------------
//函数会产生一条有唯一特征码100的警告信息，如此可暂时终止该警告。
#pragma warn - 8018
void    TMainForm::New_Diamonds() //  TObject *Sender
{
    ////构造当前方块

    //TColor  shapecolor = rand()%clMax;
    if(DiamondsColor==clMin)
        ShapeExample->Brush->Color = rand()%clMax;
    else
        ShapeExample->Brush->Color = DiamondsColor;
    // ShapeExample->Brush->Style  = bsDiagCross;
    for(int i=0; i<PIECE; i++)
    {
        //生成 方块cur_diamonds[4]
        TShape *shape;
        shape = new TShape(Application);
        shape->Parent = Panel_Client;
        shape->Width = SIDE;
        shape->Height= SIDE;
        shape->Brush = ShapeExample->Brush;
        shape->Pen = ShapeExample->Pen;
        //shape->Brush->Color = shapecolor;
        cur_diamonds[i] = shape;
    }  /*     */
    diamonds_kind = pre_diamonds_kind;
    position_kind = pre_position_kind;
    //初始化方块位置（二维）向量
    Init_Position(INIT_PLACE ,0);
    for(int i=0; i<PIECE; i++)
    {
        cur_diamonds[i]->Left = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][0];
        cur_diamonds[i]->Top = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][1];
    }
    pre_diamonds_kind = rand()%7;
    int change_num = diamonds_vec[pre_diamonds_kind].size();
    pre_position_kind = rand()%change_num;  /* */
    for(int i=0; i<PIECE; i++)
    {
        pre_diamonds[i]->Left = diamonds_vec[pre_diamonds_kind][pre_position_kind].Left_Top[i][0];
        pre_diamonds[i]->Top = diamonds_vec[pre_diamonds_kind][pre_position_kind].Left_Top[i][1];
    }
    //for(int i=0;i<PIECE;i++)
    {
        //int left = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][0];
        //int top  = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][1];
        if(Check_Dead(diamonds_vec[diamonds_kind][position_kind].Left_Top))
        {
            //游戏结束！！！
            Timer_Down->Enabled = false;
            LabelHello->Caption = " Game Over !";
            //Sleep(2000);
            gameoverflag = true;
            //演示消除方块，重新游戏
            Timer_Display->Enabled = true;
            return;
        }
    }
    if(AutoPlayItem->Checked==true)
    {

        Timer_Down->Enabled = false;
        AutoPlay();
    }
}
//恢复该警告。
#pragma warn + 8018
//---------------------------------------------------------------------------
bool    TMainForm::Check_Change() //int left ,int top
{
    int   left ,top;
    //bool  change_flag = true;
    First_Left =  cur_diamonds[0]->Left;
    First_Top  =  cur_diamonds[0]->Top;
    Init_Position(First_Left ,First_Top);
    position_kind = (position_kind+1)%(diamonds_vec[diamonds_kind].size());
    /*  */
    for(int i=0; i<PIECE; i++)
    {
        left = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][0];
        top = diamonds_vec[diamonds_kind][position_kind].Left_Top[i][1];
        int     row = top/SIDE;
        int     col = left/SIDE;
        if(board[row][col]!= NULL || col>=COL|| col<0 ||
                left<0 || row>=ROW)
        {
            position_kind--;//还原方块类型
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool    TMainForm::Check_Move(char Key)// ,TShape* *cur_diamonds
{
    //判断左右移动方块是否出界,重叠！！！

    int     left;
    int     row;
    int     col;
    if(Key=='6'||Key=='d'||Key=='D')
    {
        //向右
        for(int i=0; i<PIECE; i++)
        {
            row = cur_diamonds[i]->Top/SIDE;
            col = cur_diamonds[i]->Left/SIDE;
            left = cur_diamonds[i]->Left+SIDE*2;
            if(left >= Panel_Client->Width || board[row][col+1]!= NULL)
            {
                return false;
            }
        }
    }
    else//(Key=='4'||Key=='a'||Key=='A')
    {
        //向左
        for(int i=0; i<PIECE; i++)
        {
            row = cur_diamonds[i]->Top/SIDE;
            col = cur_diamonds[i]->Left/SIDE;
            left = cur_diamonds[i]->Left-SIDE;
            if(left < 0 || board[row][col-1]!= NULL)
            {
                return false;
            }
        }
    }
    return  true;
}
//---------------------------------------------------------------------------
/*
bool    TMainForm::CheckEdge(char Key)
{
     int     left;
     if(Key=='6'||Key=='d'||Key=='D')
     {//向右
        for(int i=0;i<PIECE;i++)
        {
           left = cur_diamonds[i]->Left+SIDE*2;
           if(left >= Panel_Client->Width )
           {
                return true;
           }
        }
     }
     else//(Key=='4'||Key=='a'||Key=='A')
     {//向左
        for(int i=0;i<PIECE;i++)
        {
           left = cur_diamonds[i]->Left-SIDE;
           if(left < 0)
           {
                return true;
           }
        }
     }
    return  false;
}                   */
//---------------------------------------------------------------------------
bool    TMainForm::Check_End()
{
    //判断下落是否到底
    for(int i=0; i<PIECE; i++)
    {
        int     row = (cur_diamonds[i]->Top+SIDE)/SIDE;
        int     col = cur_diamonds[i]->Left/SIDE;
        if((cur_diamonds[i]->Top+SIDE >= Panel_Client->Height) ||
                (board[row][col]!= NULL))
        {
            return  true;
        }
    }
    return  false;
}
//---------------------------------------------------------------------------
bool    TMainForm::Check_Dead(int Left_Top[4][2])
{
    //判断方块游戏是否结束！！！--  New_Diamonds()之前

    for(int i=0; i<PIECE; i++)
    {
        int left = Left_Top[i][0];
        int top  = Left_Top[i][1];
        if(board[top/SIDE][left/SIDE] != NULL)
        {
            return true;
        }
    }

    return  false;
}
//---------------------------------------------------------------------------
bool    TMainForm::Check_Row_Full(int row)
{
    bool    full_flag = true;
    for(int j=0; j<COL; j++)
    {
        if(board[row][j] == NULL)
        {
            full_flag = false;
            break;
        }
    }
    return  full_flag;
}
//---------------------------------------------------------------------------
bool    TMainForm::Delete_Row_Full(int row)
{
    for(int col=0; col<COL; col++)
    {
        delete board[row][col];//去除满行的方块
        board[row][col] = NULL;
    }
    LabelHello->Caption = " Hello World ！";
    for(int col=0; col<COL; col++)
    {
        //上面方块往下填补
        for(int r =row-1; r>=0; r--)
        {
            if(board[r][col]!=NULL && r<ROW-1 && board[r+1][col]==NULL)
            {
                //while,下落到底、、、、？？？
                board[r][col]->Top += SIDE;
                board[r+1][col] = board[r][col];
                board[r][col] = NULL;
            }
        }
    }

    return  true;
}
/*    //消块同时方块向下填补、、、、？？？
for(int k =row-1;k>=0;k--)
{
   int  r = k;
   while(board[r][col]!=NULL && r<Row-1 && board[r+1][col]==NULL)
   {//while,下落到底、、、、？？？
      board[r][col]->Top += SIDE;
      board[r+1][col] = board[r][col];
      board[r][col] = NULL;
      r++;  //??????
      //if(r == Row)
        //break;
   }
   if(board[r][col]!=NULL && Check_Row_Full(r))// r != Row &&
   {
      Delete_Row_Full(r);
   }
}  */
//---------------------------------------------------------------------------
void    TMainForm::OutBoard(ostream& fout)
{
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(board[i][j]==NULL)
                fout << "0" << "  ";
            else
                fout << "1" << "  ";
        }
        fout << "\n";
    }
    fout << "  " << maxvalue.LackNum << "  " << maxvalue.FullNum
    << "  " << maxvalue.Height  << "\n";
}
//---------------------------------------------------------------------------
bool    TMainForm::Remove_Diamonds()
{
    vector<int>        row_vec;
    bool       full_flag = true; //可以略去！！！！

    int     row = cur_diamonds[0]->Top/SIDE;
    row_vec.push_back(row);
    for(int i=1; i<PIECE; i++)
    {
        //取行号--消除重复出现的行
        row = cur_diamonds[i]->Top/SIDE;
        if(row!= row_vec[row_vec.size()-1 ])
            row_vec.push_back(row);
        //11111111111111111
    }
    int    deleterow = 0;
    for(unsigned int i=0; i<row_vec.size(); i++)
    {
        full_flag = true;
        full_flag = Check_Row_Full(row_vec[i]);

        if(full_flag == true)
        {
            Delete_Row_Full(row_vec[i]);
            deleterow++;
            LabelScore->Caption = String(StrToInt(LabelScore->Caption)+1);
        }
    }
    if(deleterow>=3)
        LabelHello->Caption = "  Great Great ";
    else if(deleterow!=0)
        LabelHello->Caption = " Hello World ";
    return  true;
}
//11111111111111
/*  //????冗余且有点问题
bool    repeat_flag = false;
for(unsigned int j=0;j<row_vec.size();j++)
{
     if(row==row_vec[i])
     {
        repeat_flag = true;
        break;
     }
}
if(repeat_flag == false)
{
    row_vec.push_back(row);
}    */
//---------------------------------------------------------------------------
void    TMainForm::AutoPlay()  // TObject *Sender
{
    for(int i=0; i<PIECE; i++)
    {
        //记录当前方块位置--方块形状，并隐藏方块
        changepos.Left_Top[i][0] = cur_diamonds[i]->Left;
        changepos.Left_Top[i][1] = cur_diamonds[i]->Top;
        //cur_diamonds[i]->Visible = false;
    }
    //开始扫描，求 bestpos
    ScanForward = !ScanForward;//与上次扫描方向相反
    ScanBoard(ScanForward);
    for(int i=0; i<PIECE; i++)
    {
        //还原当前方块位置，并显示方块
        cur_diamonds[i]->Left = changepos.Left_Top[i][0];
        cur_diamonds[i]->Top  = changepos.Left_Top[i][1];
        cur_diamonds[i]->Visible = true;
    }
    // 找好 maxvalue ，bestplan ， 分析结束 ，安置方块
    //PlaceDiamonds();
    for(int i=0; i<PIECE; i++)
    {
        cur_diamonds[i]->Left = savepos.Left_Top[i][0];
        cur_diamonds[i]->Top  = savepos.Left_Top[i][1];
        cur_diamonds[i]->Visible = true;
    }
    position_kind = save_position_kind;
    Timer_Display->Enabled = true;
}
//---------------------------------------------------------------------------
void    TMainForm::SaveBoard()
{
    for(int i=0; i<ROW; i++)
        for(int j=0; j<COL; j++)
        {
            temp_board[i][j] = board[i][j];
        }
}
//---------------------------------------------------------------------------
void    TMainForm::LoadBoard()
{
    for(int i=0; i<ROW; i++)
        for(int j=0; j<COL; j++)
        {
            board[i][j] = temp_board[i][j];
        }
}
//---------------------------------------------------------------------------
int    TMainForm::CountLackNum()
{
    //求该方案导致落空块格数量LackNum
    int     lacknum = 0;
    int     row;
    int     col;
    for(int i=0; i<PIECE; i++)
    {
        row = cur_diamonds[i]->Top/SIDE;
        col = cur_diamonds[i]->Left/SIDE;
        row++;
        for(int j=i+1; j<PIECE; j++)
        {
            //避免当前方块自身之间的比较（以下while）
            if((cur_diamonds[i]->Top+SIDE)==cur_diamonds[j]->Top &&
                    cur_diamonds[i]->Left==cur_diamonds[j]->Left) //同一列
            {
                row++;
            }
        }
        while(row < ROW && board[row][col]==NULL)
        {
            row++;
            lacknum++;
        }
    }
    return lacknum;
}
//---------------------------------------------------------------------------
void    TMainForm::UpdateBestplan(Value curvalue)
{
    int    cur_col = cur_diamonds[0]->Left/SIDE; //取出该方案位于哪一列
    maxvalue = curvalue;
    bestplan.Kind = position_kind;//--kind--
    bestplan.Move = cur_col - 2;// 2 为方块起始列

    for(int i=0; i<PIECE; i++)
    {
        //记录最佳方案的位置，可略、、、、
        bestplan.Pos.Left_Top[i][0] = lowpos.Left_Top[i][0];
        bestplan.Pos.Left_Top[i][1] = lowpos.Left_Top[i][1];
    }
    //ShowMessage("vvvvvvvvvvvvvvv");
}
//---------------------------------------------------------------------------
bool    TMainForm::CountValue()
{
    Value   curvalue;
    //求该方案位置的高度Height
    curvalue.Height = cur_diamonds[0]->Top/SIDE;
    //求该方案消块行数FullNum :///CountFullNum/////
    int       fullnum = 0;
    vector<int>        row_vec;
    int     row_i = cur_diamonds[0]->Top/SIDE;
    row_vec.push_back(row_i);
    for(int i=1; i<PIECE; i++)
    {
        //取行号--消除重复出现的行FullNum
        row_i = cur_diamonds[i]->Top/SIDE;
        if(row_i!= row_vec[row_vec.size()-1 ])
            row_vec.push_back(row_i);
    }
    for(unsigned int i=0; i<row_vec.size(); i++)
    {
        if(Check_Row_Full(row_vec[i]))
        {
            fullnum++;
            //ShowMessage("fffffffffffffff");
        }
    }
    curvalue.FullNum = fullnum;//求该方案位置的高度Height
    //求该方案导致落空块格数量LackNum
    curvalue.LackNum = CountLackNum();
    //比较curvalue 与 maxvalue
    bool   ChangeFlag = false;
    if(curvalue.FullNum > maxvalue.FullNum)
    {
        ChangeFlag = true;
    }
    else if(curvalue.FullNum == maxvalue.FullNum)
    {
        /*
        if((curvalue.Height-maxvalue.Height) > (curvalue.LackNum-maxvalue.LackNum))
             {
                 ChangeFlag = true;
             }  */

        if((curvalue.Height >= 5 && maxvalue.Height >= 5) || //即 游戏局面（至上而下）第5列以下
                maxvalue.Height==-1)//分Height不同大小情况分析
        {
            if(curvalue.LackNum < maxvalue.LackNum)//!!!!
            {
                ChangeFlag = true;
            }
            else if((curvalue.LackNum == maxvalue.LackNum && curvalue.Height > maxvalue.Height)) //||
                //      curvalue.LackNum == 0&& curvalue.Height-maxvalue.Height <2)//
            {
                ChangeFlag = true;
            }
        } //
        else//(maxvalue.Height<5 curvalue.Height<5)
            if((curvalue.Height-maxvalue.Height) > (curvalue.LackNum-maxvalue.LackNum))
            {
                ChangeFlag = true;
                //ShowMessage("vvvvvvvvvvvvvvv");
            }
    }
    if(ChangeFlag==true)
    {
        UpdateBestplan(curvalue);  /*
        //当前方块再再进行左右试探--是否有更佳方案
        //int     low_row = cur_diamonds[3]->Top/SIDE;
        char    left_to = 'a' ,right_to = 'd';   //？？？？？？
        if(curvalue.LackNum==0 && Check_Move(left_to))
        {
            this->KeyPress(left_to);
            if(CountLackNum()==0)
            {
                UpdateBestplan(curvalue);
            }
        }
        if(curvalue.LackNum==0 && Check_Move(right_to))
        {
            this->KeyPress(right_to);
            if(CountLackNum()==0)
            {
                UpdateBestplan(curvalue);
            }
        }
        //还要在PlaceDiamonds()时记得再Move（左右）一一格*/
        return  true;
    }
    else
        return     false;
}
//---------------------------------------------------------------------------
void    TMainForm::ScanBoard(bool    ScanForward) //TObject *Sender
{
    char    forward ,backward ,down = 's';
    if(ScanForward)
    {
        // 正方向为右
        forward = '6';//向右
        backward = '4';//向左
    }
    else
    {
        // 正方向为左
        forward = '4';//向左
        backward = '6';//向右
    }

    for(int i=0; i<PIECE; i++)
    {
        //记录起初时方块的位置
        savepos.Left_Top[i][0] = cur_diamonds[i]->Left;
        savepos.Left_Top[i][1] = cur_diamonds[i]->Top;
        save_position_kind = position_kind;
        changepos.Left_Top[i][0] = cur_diamonds[i]->Left;
        changepos.Left_Top[i][1] = cur_diamonds[i]->Top;
    }
    //ShowMessage("pppppppppppppp");
    //可以开始扫描,求bestpos maxvalue --初始化
    maxvalue.LackNum = ROW*COL;
    maxvalue.FullNum = 0;
    maxvalue.Height = -1;
    bestplan.Kind = position_kind;
    bestplan.Move = 0;//即不动
    unsigned int     k = 1;
    do
    {
        do
        {
            //先将方块后退至一端
            this->KeyPress(backward);
        }
        while(Check_Move(backward));    // ,cur_diamonds
        //保存当前游戏局面
        SaveBoard();
        int     scannum = 0;
        while(true) //,cur_diamonds
        {
            for(int i=0; i<PIECE; i++)
            {
                lowpos.Left_Top[i][0] = cur_diamonds[i]->Left;
                lowpos.Left_Top[i][1] = cur_diamonds[i]->Top;
            }
            while(!Check_End())
            {
                //将方块落放至底
                this->KeyPress(down);
            }
            //ShowMessage("dddddddddddddd");
            int     row;
            int     col;
            for(int i=0; i<PIECE; i++)
            {
                row = cur_diamonds[i]->Top/SIDE;
                col = cur_diamonds[i]->Left/SIDE;
                board[row][col] =  cur_diamonds[i];
            }
            //计算该方案的 value  ？ maxvalue
            CountValue();

            //恢复游戏局面，准备继续扫描
            LoadBoard();
            for(int i=0; i<PIECE; i++)
            {
                cur_diamonds[i]->Left = lowpos.Left_Top[i][0];
                cur_diamonds[i]->Top  = lowpos.Left_Top[i][1];
            }
            scannum++;
            if(! Check_Move(forward))
                break;
            this->KeyPress(forward);//前进一格
        }//while(true) -- !Check_Move(forward)) //
        //ShowMessage(String(scannum));  //

        if(k >= diamonds_vec[diamonds_kind].size() || maxvalue.FullNum>=2 )// || maxvalue.LackNum==0
        {
            break;//扫描全部退出或是找到所要的maxvalue 退出while(true)循环
        }
        else
        {
            //方块变形继续扫描
            for(int i=0; i<PIECE; i++)
            {
                //恢复起初时方块的位置 --形状
                cur_diamonds[i]->Left = changepos.Left_Top[i][0];
                cur_diamonds[i]->Top  = changepos.Left_Top[i][1];
            }
            //ShowMessage("ccccccccc111111111");
            //恢复 First_Left ，First_Top ，保证 this->KeyPress(change) 正确
            char    change = 13;
            this->KeyPress(change);
            for(int i=0; i<PIECE; i++)
            {
                //记录当前方块位置--方块形状
                changepos.Left_Top[i][0] = cur_diamonds[i]->Left;
                changepos.Left_Top[i][1] = cur_diamonds[i]->Top;
            }
            //ShowMessage("cccccccccccccccccc");
            k++;
        }
    }
    while(true);
}
//---------------------------------------------------------------------------
void    TMainForm::PlaceDiamonds()
{
    /*  //亦可行--只是不能实现过程演示
     position_kind = bestplan.Kind;
     for(int i=0;i<PIECE;i++)
     {
         cur_diamonds[i]->Left = bestplan.Pos.Left_Top[i][0];
         cur_diamonds[i]->Top  = bestplan.Pos.Left_Top[i][1];
     } */
    //
    for(int i=0; i<PIECE; i++)
    {
        cur_diamonds[i]->Left = savepos.Left_Top[i][0];
        cur_diamonds[i]->Top  = savepos.Left_Top[i][1];
        cur_diamonds[i]->Visible = true;
    }

    position_kind = save_position_kind;
    while(position_kind != bestplan.Kind)
    {
        char    change = 13;
        this->KeyPress(change);
        //Sleep(500);
        //ShowMessage("cccccccccccccccccc");
    }
    char    ward;//方向
    if(bestplan.Move >0)
        ward = '6';
    else
        ward = '4';
    for(int i=0; i<abs(bestplan.Move); i++)
    {
        this->KeyPress(ward);
        //Sleep(500);
    }
    Timer_Down->Enabled = true;
}
//---------------------------------------------------------------------------
