//---------------------------------------------------------------------------
// 描述：SK 五子棋 1.0 核心算法
// 作者：seeker
// 声明：本代码仅供学习，任何人可以修改复制，但必须注明原作者信息！
// 注意：版权所属：seeker
// 日期：2006-12-31
// 更新：2007-12-28
// 感谢：天地之灵
//---------------------------------------------------------------------------
#pragma hdrstop

#include "CH5.h"
#include "stdlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//========================================================
MYCH5::MYCH5()
{
   Reset();//初始化
   srand((unsigned(time(0))));
}
//--------------------------------------------------
// 得到第 i 步的坐标值和颜色值，用于保存文件
void MYCH5::GetStepOfIndex(int i,int &tx,int &ty,int &tc)
{
  tx=STEPS[i].x;  ty=STEPS[i].y;  tc=STEPS[i].color;
}
//--------------------------------------------------
// 设置第 i 步的坐标值和颜色值，
// 用于读取文件之后设置棋盘
void MYCH5::SetStepOfIndex(int i,int tx,int ty,int tc)
{
  STEPS[i].x=tx;  STEPS[i].y=ty;  STEPS[i].color=tc;
}
//--------------------------------------------------
// 初始化（重置）棋盘和游戏状态
//  默认人机对战，人先下，人先执黑
void MYCH5::Reset()
{
  int i,j;
  for(i=0;i<15;i++)
    for(j=0;j<15;j++)
       CH5[i][j]=0;

  StepLen=0;    // 开始
  UserColor=BLACK; // 默认人先执黑
  PlayState=MAN;  //人机对战，人先下
}
//---------------------------------------------------------------------------
//设置谁先下棋
int MYCH5::SetFirst(int playstate,bool read_PcFirst)
{
  // 保证范围，可以不要
  PlayState=(playstate<4&&playstate>0)?playstate:PC;
  // read_PcFirst=true 表明从机器先下的文件读取数据
  // 那么接下来就应该是用户下棋，且颜色为白色（2）！
  if(read_PcFirst)
  {
    PlayState=MAN;      //读完文件轮到人下，且颜色为白色
    UserColor=WHITE; //白色
//   return UserColor;
  }
  if(PlayState==PC)     //如果是机器先下，则机器为白色
    UserColor=WHITE;
  return UserColor;  
}
//---------------------------------------------------------------------------

// 定义一个宏，用来定位，将二维数组当作一维使用
#define GetBoardXY(x,y) Board[(x)*15+(y)]

// 该函数判断是否有人赢，包括禁手。
int MYCH5::JudgeWin(int x,int y,int *Board) //判断是否有人胜利
{
  int i,j;   // i 是循环变量， J 用来记录同颜色的连续棋子有多少个
  int t,t1;
  int dx,dy; // 用来控制坐标的变化！
  int x1,y1; // 搜索的开始位置

  int Color=GetBoardXY(x,y); // 返回xy棋格处的棋子颜色

  for (i=0;i<4;i++)	     //i=0到3分别表示4个方向。
  {
    switch (i)
    {
    case 0:dx=0;  dy=1;  break; //向下---向上
    case 1:dx=1;  dy=0;  break; //向右---向左
    case 2:dx=1;  dy=1;  break; //右下---左上
    case 3:dx=1;  dy=-1; break; //右上---左下
    default:dx=0; dy=0;  break; //不变
    }
    j=1;        //J 用来记录多少个同颜色棋子（己方）相邻，用于判断禁手或者输赢
    x1=x; y1=y; //不用说也是从x，y位置开始判断
    // 正向
    while ((x1+dx<=14)&&(y1+dy<=14)&&(y1+dy>=0) //保证范围不会超过棋盘范围
           &&(GetBoardXY(x1+=dx,y1+=dy)==Color))//判断颜色是否相等
       j++;
       
    x1=x;
    y1=y;
    //反向
    while ((x1-dx>=0)&&(y1-dy>=0)&&(y1-dy<=14)
           &&(GetBoardXY(x1-=dx,y1-=dy)==Color))
       j++;
    if ((Color==BLACK)&&(j>5))
        return 2;          //黑棋长连禁手的判断，白方赢
    if (j>4)
      return Color;  // 如果5子相连，则返回赢方颜色
  }// for
  
  if(Color==WHITE)
     return 0;  //白方不做禁手判断，直接返回

  //-------------------
  //双四禁手的判断
  //-------------------
  t=0;
  for (i=0;i<4;i++)
  {
    int k,b;  // b记录来连续5个位置中有多少己方的棋子
    switch (i)
    {
      case 0:dx=0;  dy=1;  break; //向下---向上
      case 1:dx=1;  dy=0;  break; //向右---向左
      case 2:dx=1;  dy=1;  break; //右下---左上
      case 3:dx=1;  dy=-1; break; //右上---左下
      default:dx=0; dy=0;  break; //不变
    }

    t1=0;
    // 如果包含当前位置的连续5个位置中，
    // 有四个为己方，且剩下一个为空，则为四。
    for(j=-4;j<1;j++)
    {
       b=0;
       for(k=0;k<5;k++)//计算该方向连续5个位置
       {
          //判断是否超出棋盘范围
          if((x+(j+k)*dx<0)||(x+(j+k)*dx>14)||
             (y+(j+k)*dy<0)||(y+(j+k)*dy>14))
          {
            b=0;
            break;
          }
          //己方棋子
          if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==Color)
            b++;
          //5个位置中遇到对方棋子，退出改方向的计算，换方向
          if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==3-Color)
          {
            b=0;
            break;
          }
       }//for k

       //如果此连续5个位置相邻的两个位置有己方子，则长连禁手，不必做活四判断。
       if( (b==4)//四个相连（即相邻的两个位置有己方子）
            &&((x+(j-1)*dx<0)||(y+(j-1)*dy<0)||(y+(j-1)*dy>14)||(GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)!=BLACK))
            &&((x+(j+5)*dx<0)||(y+(j+5)*dy<0)||(y+(j+5)*dy>14)||(GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))
       {
           t1++;
           //如果是活四，那这个方向上只算有一个四。
           if((x+(j-1)*dx>=0)&&(y+(j-1)*dy>=0)&&(y+(j-1)*dy<=14)
             &&(x+(j+4)*dx<=14)&&(y+(j+4)*dy<=14)&&(y+(j+4)*dy>=0)//棋盘范围内
             &&(GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)==EMPTY)&&(GetBoardXY(x+(j+4)*dx,y+(j+4)*dy)==EMPTY))
           {
              t1=1;//只算有一个四
              break;
           }
       }
    }//for j
    t+=t1;
  }// for i

  if (t>1) return 2; //如果有超过两个合法的四，则是禁手。

  //-------------------
  //双三禁手的判断
  //-------------------
  t=0;
  for (i=0;i<4;i++)
  {
     int k,b;
     switch (i)
     {
        case 0:dx=0;  dy=1;  break; //向下---向上
        case 1:dx=1;  dy=0;  break; //向右---向左
        case 2:dx=1;  dy=1;  break; //右下---左上
        case 3:dx=1;  dy=-1; break; //右上---左下
        default:dx=0; dy=0;  break; //不变
     }

     t1=0;
     // 如果包括当前位置在内的连续四个位置有三个为己方，
     // 且剩下的一个以及左右相邻的两个全部为空格，
     // 并且中间剩下的一个非禁手或五，则算活三
     for (j=-3;j<1;j++)
     {
        b=0;
        int b1=0;
        for (k=0;k<4;k++) 
        {
           //判断是否超出棋盘范围
           if((x+(j+k)*dx<0)||(x+(j+k)*dx>14)||
              (y+(j+k)*dy<0)||(y+(j+k)*dy>14))
           {
              b=0;
              break;
           }
           if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==Color)
             b++;
          else
             b1=k;
          if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==3-Color)
          {
             b=0;
             break;
          }
        }// for k

        // 3个相连，还必须判断是否双3禁手和排除假双3 ，
        // 这里比较复杂，复杂度不亚于国际象棋，我也不是很明白啊
        if((b==3)&&
            ((x+(j-1)*dx>=0)&&(y+(j-1)*dy>=0)&&(y+(j-1)*dy<=14)&&
            (x+(j+4)*dx<=14)&&(y+(j+4)*dy<=14)&&(y+(j+4)*dy>=0)&&
            (GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)==EMPTY)&&
            (GetBoardXY(x+(j+4)*dx,y+(j+4)*dy)==EMPTY))&&
            //必须相邻的相邻的位置不能为己方子，否则长连禁手，且该位置不能算做活3。
            ((x+(j-2)*dx<0)||(y+(j-2)*dy<0)||(y+(j-2)*dy>14)||(GetBoardXY(x+(j-2)*dx,y+(j-2)*dy)!=BLACK))&&
            ((x+(j+5)*dx>14)||(y+(j+5)*dy<0)||(y+(j+5)*dy>14)||(GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))
        {
           b=1;
           //需要递归判断假双三的情况。
           GetBoardXY(x+(j+b1)*dx,y+(j+b1)*dy)=BLACK; //模拟落子
           b=b&&(JudgeWin(x+(j+b1)*dx,y+(j+b1)*dy,Board)==0);
           GetBoardXY(x+(j+b1)*dx,y+(j+b1)*dy)=EMPTY;
           t1=t1||b;
        }
     }//for j
     t+=t1;
  }// for i
  if (t>1)
    return 2; //如果有双三禁手
//*****************************
  //这里最后判断以下棋盘是否满了
  //因为及其先下跟人先下不同
  if(StepLen>=225) //这样一来。无论谁先下都可以判断了
     return -4;    //平局
//******************************
  return 0;
}
//---------------------------------------------------------------------------
// 本函数是计算本坐标指定颜色棋子对于整个棋盘格局的影响
// 返回的是它的作用值。
int MYCH5::GetValueXY(int *Board,int x,int y,int Color)
{//
  int i,j,k,t,t1;
  int dx,dy; // 方向

  if(Board[x*15+y]) //本位置已经有棋子
     return ValueMin;//最小值,不能落子

  int Value=0;

  Board[x*15+y]=Color;	//位置空，就模拟落棋，检查是否必胜或必败
  
  if((k=JudgeWin(x,y,Board))==Color)//必胜落子
  {
     Board[x*15+y]=EMPTY;
     return ValueMax;
  }
  if (k==3-Color) //禁手
  {
     Board[x*15+y]=EMPTY;
     return ValueMin;
  }

  t=0;
  for(i=0;i<4;i++)	//四和活四的检测
  {
     int k,b;
     switch (i)
     {
        case 0:dx=0;dy=1;break;
        case 1:dx=1;dy=0;break;
        case 2:dx=1;dy=1;break;
        case 3:dx=1;dy=-1;break;
        default:return 0;
     }
     t1=0;
     for (j=-4;j<1;j++)
     {
        b=0;
        for (k=-1;k<6;k++)
        {
            if((x+(j+k)*dx<0)||(x+(j+k)*dx>14)||(y+(j+k)*dy<0)||(y+(j+k)*dy>14))
            {
               b=0;
               break;
            }
            if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==Color)
               b++;
            if (GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==3-Color)
            {
               b=0;
               break;
            }
        }// for k
        if((b==4)&&   	
           ((Color==WHITE)||(((x+(j-1)*dx<0)||(y+(j-1)*dy<0)||
            (y+(j-1)*dy>14)||(GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)!=BLACK))
           &&((x+(j+5)*dx<0)||(y+(j+5)*dy<0)||(y+(j+5)*dy>14)||
           (GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))))//如果是黑方，不能长连。
        {
           t1++; //这里活四可以看做是两个四，提高优先度
        }
     }//for j
     t+=t1;
  }//for i
  switch (t)
  {
     case 2:case 3:case 4:
       Value+=10*Value4;  //优先落子
     break;
     default:break;
  }

  for (i=0;i<4;i++)//作用程度的检测
  {
    int k,b;
    switch (i)
    {
       case 0:dx=0;dy=1;break;
       case 1:dx=1;dy=0;break;
       case 2:dx=1;dy=1;break;
       case 3:dx=1;dy=-1;break;
    }
   // t1;
    for (j=-4;j<1;j++)
    {
        b=0;
        for (k=0;k<5;k++)
        {
           if ((x+(j+k)*dx<0)||(x+(j+k)*dx>14)||(y+(j+k)*dy<0)||(y+(j+k)*dy>14))
           {
              b=-1;
              break;
           }
           if (GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==Color)
              b++;
           if (GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==3-Color)
           {
               b=-1;
               break;
           }
        }// for k
        if((b>0)&&
          ((Color==2)||((x+(j-1)*dx<0)||(y+(j-1)*dy<0)||(y+(j-1)*dy>14)||
          (GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)!=BLACK))))
        {
           Value+=b*b*b*ValuePer/10*((i>1)?10:9);//这个(i>1)?10:9表示倾向于斜方向落子
        }
    }//for j
  }//for i
  Board[x*15+y]=EMPTY; // 还原模拟落子
  return (Value);  //返回计算出来的值
}
//-----------------------------------------------------------------------
// 本函数计算全部棋子的作用值，用于判断选择最好的落子位置
// 参数 ValueBoard 保存计算后的值
void MYCH5::GetValue(int *Board,int *ValueBoard,int Color)
{
  int i,j,k;
  for (i=0;i<15;i++)
    for (j=0;j<15;j++)
    {
      ValueBoard[i*15+j]=GetValueXY(Board,i,j,Color)*Attack;
      if ((k=GetValueXY(Board,i,j,3-Color))>10000)
              ValueBoard[i*15+j]+=k*Protect;
      ValueBoard[i*15+j]+=rand()%ValueRandom+(98-(i-7)*(i-7)-(j-7)*(j-7))*ValuePosition;
    }
}
//---------------------------------------------------------------------
// 电脑思考落子位置
// 返回一维的坐标值
int MYCH5::Think(int color)
{
	int Board[225],Value_Board[225];
	int i,j,x,y,MaxValue;

	for (i=0;i<225;i++)
		Board[i]=CH5[i/15][i%15];//2维向1维赋值
	GetValue(Board,Value_Board,color); //估值

	MaxValue=ValueMin;
    x=0; y=0;
    // 选择最大值
	for(i=0;i<15;i++)
	{
      for(j=0;j<15;j++)
	  {
        if(Value_Board[i*15+j]>MaxValue)
        {
           MaxValue=Value_Board[i*15+j];
           x=i;y=j;
        }
	  }// for j
    }//for i
	if (MaxValue>-100000000)
	{
		return (x*15+y);
	}
	else
		return -1;  //有异常，返回错误
}
#undef GetBoardXY //取消宏定义
//--------------------------------------------------
int  MYCH5::put(int x,int y,int color)
{
  if(!color)
     return -1;
  if (!CH5[x][y])
  {
    CH5[x][y]=color;
    STEPS[StepLen].x		=	x;
    STEPS[StepLen].y		=	y;
    STEPS[StepLen].color	=	color;
    StepLen++;
    return JudgeWin(x,y,&CH5[0][0]);
  }
  else return -1;
}
//--------------------------------------------------
//用户试图悔棋 （一次最多悔两步）
// 返回 0 表示悔棋失败，1表示悔棋成功
int MYCH5::Retract()
{
  if(this->PlayState==STOP)  //游戏停止了，还悔什么棋？
    return 0;
  //为什么不 StepLen>0 呢？这里考虑到了电脑先下的情况
  // 电脑先下的那一步不可以悔棋，这是常识
  if(StepLen>UserColor-1)
  {
    StepLen--;
    CH5[STEPS[StepLen].x][STEPS[StepLen].y]=EMPTY; //悔棋就要恢复棋盘布局状态
  }
  else
  {
    return 0;
  }
  while((StepLen>0)&&(STEPS[StepLen-1].color==UserColor))
  {
    StepLen--;
    CH5[STEPS[StepLen].x][STEPS[StepLen].y]=EMPTY;
  }
  return 1;
}
//------------------------------------------------------
int MYCH5::PutChess(int Qx,int Qy,int &posx,int &posy)
{
  int Someone_Win;
  if(PlayState==STOP)
    return -2;   // 游戏停止，不允许动作

   if(PlayState==MAN) //如果现在正在对局中（人机对战--人）
   {
      if(CH5[Qx][Qy]!=EMPTY)   //已经有棋子就不再下棋！
         return -2; 
//人工落子
      if(UserColor==EMPTY) //保证颜色合法
         return -2;
      Someone_Win=put(Qx,Qy,UserColor); //下棋并且判断输赢
      if (Someone_Win==-1)
         return -2;
//******************************
       if(Someone_Win==-4)// 平局
       {
          PlayState=STOP;
          return 0;
       }
//******************************
      if(Someone_Win==0)  //Someone_Win==0,未有输赢，暂时平局
      {
        PlayState=PC;    //轮到机器落子
        if(StepLen>=225) //走满了棋盘还没有输赢当然是平局啦！
        {
         // MessageBox(Handle,"平局！","SK五子棋",MB_OK);
          PlayState=STOP;
          return 0;
        }
      }
      else   //有输赢
      {
        PlayState=STOP;
        if (Someone_Win==UserColor)
           return UserColor;//MessageBox(Handle,"你赢了！","SK五子棋",MB_OK);
        else
           return 3;//MessageBox(Handle,"你禁手了！","SK五子棋",MB_OK);
      }
//由计算机来落子
      if (PlayState==PC)
      {
         int i=Think(3-UserColor);  //机器思考！
         int qx=i/15;
         int qy=i%15;
         if (i>=0) //坐标范围合法
	     {
            i=put(qx,qy,3-UserColor); //机器落子
           // 返回落子焦点
            posx=qx;
            posy=qy;
//**********************************          
            if(i==-4)// 平局
            {
               PlayState=STOP;
               return 0;
            }
//*********************************
            if (i>0)
            {
               PlayState=STOP;
               return 3-UserColor;// MessageBox(Handle,"你输了！","SK五子棋",MB_OK);
            }
            else
            {
               PlayState=MAN; // 轮回到人落子
               return -1; // 继续落子
            }
         }
         else
         {
            PlayState=STOP;  //停止下棋
            if (StepLen>=225)
            {
              // MessageBox(Handle,"平局！","SK五子棋",MB_OK);
              return 0;
            }
            else
            {
              // MessageBox(Handle,"我认输了！","SK五子棋",MB_OK);
              return 4;// 电脑认输
            }
         }
      }//if (PlayState==3)
      else
         return -2;
   }//if PlayState==2                                  

   else //由计算机先落子
   {
      if(PlayState==PC)
      {
        int i=rand()%225; // 这里采用随机坐标，目的为了更加人性化
       /* int i=Think(3-UserColor); */  //机器思考！

        int qx=i/15;
        int qy=i%15;

        if (i>=0)
	    {
           i=put(qx,qy,3-UserColor); //机器落子
           // 返回落子焦点
           posx=qx;
           posy=qy;
           if (i)
           {
              PlayState=STOP;
              return 3-UserColor;// MessageBox(Handle,"你输了！","SK五子棋",MB_OK);
           }
           else
           {
              PlayState=MAN; // 落子轮回到人
              return -1; // 继续落子
           }
        }
      }//if pc
      else
         return -2; //无法下棋
      return -2; //无法下棋
   }//else
}
//------------------------------------------------------









