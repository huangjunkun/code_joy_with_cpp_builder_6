//---------------------------------------------------------------------------
// ������SK ������ 1.0 �����㷨
// ���ߣ�seeker
// ���������������ѧϰ���κ��˿����޸ĸ��ƣ�������ע��ԭ������Ϣ��
// ע�⣺��Ȩ������seeker
// ���ڣ�2006-12-31
// ���£�2007-12-28
// ��л�����֮��
//---------------------------------------------------------------------------
#pragma hdrstop

#include "CH5.h"
#include "stdlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//========================================================
MYCH5::MYCH5()
{
   Reset();//��ʼ��
   srand((unsigned(time(0))));
}
//--------------------------------------------------
// �õ��� i ��������ֵ����ɫֵ�����ڱ����ļ�
void MYCH5::GetStepOfIndex(int i,int &tx,int &ty,int &tc)
{
  tx=STEPS[i].x;  ty=STEPS[i].y;  tc=STEPS[i].color;
}
//--------------------------------------------------
// ���õ� i ��������ֵ����ɫֵ��
// ���ڶ�ȡ�ļ�֮����������
void MYCH5::SetStepOfIndex(int i,int tx,int ty,int tc)
{
  STEPS[i].x=tx;  STEPS[i].y=ty;  STEPS[i].color=tc;
}
//--------------------------------------------------
// ��ʼ�������ã����̺���Ϸ״̬
//  Ĭ���˻���ս�������£�����ִ��
void MYCH5::Reset()
{
  int i,j;
  for(i=0;i<15;i++)
    for(j=0;j<15;j++)
       CH5[i][j]=0;

  StepLen=0;    // ��ʼ
  UserColor=BLACK; // Ĭ������ִ��
  PlayState=MAN;  //�˻���ս��������
}
//---------------------------------------------------------------------------
//����˭������
int MYCH5::SetFirst(int playstate,bool read_PcFirst)
{
  // ��֤��Χ�����Բ�Ҫ
  PlayState=(playstate<4&&playstate>0)?playstate:PC;
  // read_PcFirst=true �����ӻ������µ��ļ���ȡ����
  // ��ô��������Ӧ�����û����壬����ɫΪ��ɫ��2����
  if(read_PcFirst)
  {
    PlayState=MAN;      //�����ļ��ֵ����£�����ɫΪ��ɫ
    UserColor=WHITE; //��ɫ
//   return UserColor;
  }
  if(PlayState==PC)     //����ǻ������£������Ϊ��ɫ
    UserColor=WHITE;
  return UserColor;  
}
//---------------------------------------------------------------------------

// ����һ���꣬������λ������ά���鵱��һάʹ��
#define GetBoardXY(x,y) Board[(x)*15+(y)]

// �ú����ж��Ƿ�����Ӯ���������֡�
int MYCH5::JudgeWin(int x,int y,int *Board) //�ж��Ƿ�����ʤ��
{
  int i,j;   // i ��ѭ�������� J ������¼ͬ��ɫ�����������ж��ٸ�
  int t,t1;
  int dx,dy; // ������������ı仯��
  int x1,y1; // �����Ŀ�ʼλ��

  int Color=GetBoardXY(x,y); // ����xy��񴦵�������ɫ

  for (i=0;i<4;i++)	     //i=0��3�ֱ��ʾ4������
  {
    switch (i)
    {
    case 0:dx=0;  dy=1;  break; //����---����
    case 1:dx=1;  dy=0;  break; //����---����
    case 2:dx=1;  dy=1;  break; //����---����
    case 3:dx=1;  dy=-1; break; //����---����
    default:dx=0; dy=0;  break; //����
    }
    j=1;        //J ������¼���ٸ�ͬ��ɫ���ӣ����������ڣ������жϽ��ֻ�����Ӯ
    x1=x; y1=y; //����˵Ҳ�Ǵ�x��yλ�ÿ�ʼ�ж�
    // ����
    while ((x1+dx<=14)&&(y1+dy<=14)&&(y1+dy>=0) //��֤��Χ���ᳬ�����̷�Χ
           &&(GetBoardXY(x1+=dx,y1+=dy)==Color))//�ж���ɫ�Ƿ����
       j++;
       
    x1=x;
    y1=y;
    //����
    while ((x1-dx>=0)&&(y1-dy>=0)&&(y1-dy<=14)
           &&(GetBoardXY(x1-=dx,y1-=dy)==Color))
       j++;
    if ((Color==BLACK)&&(j>5))
        return 2;          //���峤�����ֵ��жϣ��׷�Ӯ
    if (j>4)
      return Color;  // ���5���������򷵻�Ӯ����ɫ
  }// for
  
  if(Color==WHITE)
     return 0;  //�׷����������жϣ�ֱ�ӷ���

  //-------------------
  //˫�Ľ��ֵ��ж�
  //-------------------
  t=0;
  for (i=0;i<4;i++)
  {
    int k,b;  // b��¼������5��λ�����ж��ټ���������
    switch (i)
    {
      case 0:dx=0;  dy=1;  break; //����---����
      case 1:dx=1;  dy=0;  break; //����---����
      case 2:dx=1;  dy=1;  break; //����---����
      case 3:dx=1;  dy=-1; break; //����---����
      default:dx=0; dy=0;  break; //����
    }

    t1=0;
    // ���������ǰλ�õ�����5��λ���У�
    // ���ĸ�Ϊ��������ʣ��һ��Ϊ�գ���Ϊ�ġ�
    for(j=-4;j<1;j++)
    {
       b=0;
       for(k=0;k<5;k++)//����÷�������5��λ��
       {
          //�ж��Ƿ񳬳����̷�Χ
          if((x+(j+k)*dx<0)||(x+(j+k)*dx>14)||
             (y+(j+k)*dy<0)||(y+(j+k)*dy>14))
          {
            b=0;
            break;
          }
          //��������
          if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==Color)
            b++;
          //5��λ���������Է����ӣ��˳��ķ���ļ��㣬������
          if(GetBoardXY(x+(j+k)*dx,y+(j+k)*dy)==3-Color)
          {
            b=0;
            break;
          }
       }//for k

       //���������5��λ�����ڵ�����λ���м����ӣ��������֣������������жϡ�
       if( (b==4)//�ĸ������������ڵ�����λ���м����ӣ�
            &&((x+(j-1)*dx<0)||(y+(j-1)*dy<0)||(y+(j-1)*dy>14)||(GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)!=BLACK))
            &&((x+(j+5)*dx<0)||(y+(j+5)*dy<0)||(y+(j+5)*dy>14)||(GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))
       {
           t1++;
           //����ǻ��ģ������������ֻ����һ���ġ�
           if((x+(j-1)*dx>=0)&&(y+(j-1)*dy>=0)&&(y+(j-1)*dy<=14)
             &&(x+(j+4)*dx<=14)&&(y+(j+4)*dy<=14)&&(y+(j+4)*dy>=0)//���̷�Χ��
             &&(GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)==EMPTY)&&(GetBoardXY(x+(j+4)*dx,y+(j+4)*dy)==EMPTY))
           {
              t1=1;//ֻ����һ����
              break;
           }
       }
    }//for j
    t+=t1;
  }// for i

  if (t>1) return 2; //����г��������Ϸ����ģ����ǽ��֡�

  //-------------------
  //˫�����ֵ��ж�
  //-------------------
  t=0;
  for (i=0;i<4;i++)
  {
     int k,b;
     switch (i)
     {
        case 0:dx=0;  dy=1;  break; //����---����
        case 1:dx=1;  dy=0;  break; //����---����
        case 2:dx=1;  dy=1;  break; //����---����
        case 3:dx=1;  dy=-1; break; //����---����
        default:dx=0; dy=0;  break; //����
     }

     t1=0;
     // ���������ǰλ�����ڵ������ĸ�λ��������Ϊ������
     // ��ʣ�µ�һ���Լ��������ڵ�����ȫ��Ϊ�ո�
     // �����м�ʣ�µ�һ���ǽ��ֻ��壬�������
     for (j=-3;j<1;j++)
     {
        b=0;
        int b1=0;
        for (k=0;k<4;k++) 
        {
           //�ж��Ƿ񳬳����̷�Χ
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

        // 3���������������ж��Ƿ�˫3���ֺ��ų���˫3 ��
        // ����Ƚϸ��ӣ����ӶȲ����ڹ������壬��Ҳ���Ǻ����װ�
        if((b==3)&&
            ((x+(j-1)*dx>=0)&&(y+(j-1)*dy>=0)&&(y+(j-1)*dy<=14)&&
            (x+(j+4)*dx<=14)&&(y+(j+4)*dy<=14)&&(y+(j+4)*dy>=0)&&
            (GetBoardXY(x+(j-1)*dx,y+(j-1)*dy)==EMPTY)&&
            (GetBoardXY(x+(j+4)*dx,y+(j+4)*dy)==EMPTY))&&
            //�������ڵ����ڵ�λ�ò���Ϊ�����ӣ����������֣��Ҹ�λ�ò���������3��
            ((x+(j-2)*dx<0)||(y+(j-2)*dy<0)||(y+(j-2)*dy>14)||(GetBoardXY(x+(j-2)*dx,y+(j-2)*dy)!=BLACK))&&
            ((x+(j+5)*dx>14)||(y+(j+5)*dy<0)||(y+(j+5)*dy>14)||(GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))
        {
           b=1;
           //��Ҫ�ݹ��жϼ�˫���������
           GetBoardXY(x+(j+b1)*dx,y+(j+b1)*dy)=BLACK; //ģ������
           b=b&&(JudgeWin(x+(j+b1)*dx,y+(j+b1)*dy,Board)==0);
           GetBoardXY(x+(j+b1)*dx,y+(j+b1)*dy)=EMPTY;
           t1=t1||b;
        }
     }//for j
     t+=t1;
  }// for i
  if (t>1)
    return 2; //�����˫������
//*****************************
  //��������ж����������Ƿ�����
  //��Ϊ�������¸������²�ͬ
  if(StepLen>=225) //����һ��������˭���¶������ж���
     return -4;    //ƽ��
//******************************
  return 0;
}
//---------------------------------------------------------------------------
// �������Ǽ��㱾����ָ����ɫ���Ӷ����������̸�ֵ�Ӱ��
// ���ص�����������ֵ��
int MYCH5::GetValueXY(int *Board,int x,int y,int Color)
{//
  int i,j,k,t,t1;
  int dx,dy; // ����

  if(Board[x*15+y]) //��λ���Ѿ�������
     return ValueMin;//��Сֵ,��������

  int Value=0;

  Board[x*15+y]=Color;	//λ�ÿգ���ģ�����壬����Ƿ��ʤ��ذ�
  
  if((k=JudgeWin(x,y,Board))==Color)//��ʤ����
  {
     Board[x*15+y]=EMPTY;
     return ValueMax;
  }
  if (k==3-Color) //����
  {
     Board[x*15+y]=EMPTY;
     return ValueMin;
  }

  t=0;
  for(i=0;i<4;i++)	//�ĺͻ��ĵļ��
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
           (GetBoardXY(x+(j+5)*dx,y+(j+5)*dy)!=BLACK)))))//����Ǻڷ������ܳ�����
        {
           t1++; //������Ŀ��Կ����������ģ�������ȶ�
        }
     }//for j
     t+=t1;
  }//for i
  switch (t)
  {
     case 2:case 3:case 4:
       Value+=10*Value4;  //��������
     break;
     default:break;
  }

  for (i=0;i<4;i++)//���ó̶ȵļ��
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
           Value+=b*b*b*ValuePer/10*((i>1)?10:9);//���(i>1)?10:9��ʾ������б��������
        }
    }//for j
  }//for i
  Board[x*15+y]=EMPTY; // ��ԭģ������
  return (Value);  //���ؼ��������ֵ
}
//-----------------------------------------------------------------------
// ����������ȫ�����ӵ�����ֵ�������ж�ѡ����õ�����λ��
// ���� ValueBoard ���������ֵ
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
// ����˼������λ��
// ����һά������ֵ
int MYCH5::Think(int color)
{
	int Board[225],Value_Board[225];
	int i,j,x,y,MaxValue;

	for (i=0;i<225;i++)
		Board[i]=CH5[i/15][i%15];//2ά��1ά��ֵ
	GetValue(Board,Value_Board,color); //��ֵ

	MaxValue=ValueMin;
    x=0; y=0;
    // ѡ�����ֵ
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
		return -1;  //���쳣�����ش���
}
#undef GetBoardXY //ȡ���궨��
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
//�û���ͼ���� ��һ������������
// ���� 0 ��ʾ����ʧ�ܣ�1��ʾ����ɹ�
int MYCH5::Retract()
{
  if(this->PlayState==STOP)  //��Ϸֹͣ�ˣ�����ʲô�壿
    return 0;
  //Ϊʲô�� StepLen>0 �أ����￼�ǵ��˵������µ����
  // �������µ���һ�������Ի��壬���ǳ�ʶ
  if(StepLen>UserColor-1)
  {
    StepLen--;
    CH5[STEPS[StepLen].x][STEPS[StepLen].y]=EMPTY; //�����Ҫ�ָ����̲���״̬
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
    return -2;   // ��Ϸֹͣ����������

   if(PlayState==MAN) //����������ڶԾ��У��˻���ս--�ˣ�
   {
      if(CH5[Qx][Qy]!=EMPTY)   //�Ѿ������ӾͲ������壡
         return -2; 
//�˹�����
      if(UserColor==EMPTY) //��֤��ɫ�Ϸ�
         return -2;
      Someone_Win=put(Qx,Qy,UserColor); //���岢���ж���Ӯ
      if (Someone_Win==-1)
         return -2;
//******************************
       if(Someone_Win==-4)// ƽ��
       {
          PlayState=STOP;
          return 0;
       }
//******************************
      if(Someone_Win==0)  //Someone_Win==0,δ����Ӯ����ʱƽ��
      {
        PlayState=PC;    //�ֵ���������
        if(StepLen>=225) //���������̻�û����Ӯ��Ȼ��ƽ������
        {
         // MessageBox(Handle,"ƽ�֣�","SK������",MB_OK);
          PlayState=STOP;
          return 0;
        }
      }
      else   //����Ӯ
      {
        PlayState=STOP;
        if (Someone_Win==UserColor)
           return UserColor;//MessageBox(Handle,"��Ӯ�ˣ�","SK������",MB_OK);
        else
           return 3;//MessageBox(Handle,"������ˣ�","SK������",MB_OK);
      }
//�ɼ����������
      if (PlayState==PC)
      {
         int i=Think(3-UserColor);  //����˼����
         int qx=i/15;
         int qy=i%15;
         if (i>=0) //���귶Χ�Ϸ�
	     {
            i=put(qx,qy,3-UserColor); //��������
           // �������ӽ���
            posx=qx;
            posy=qy;
//**********************************          
            if(i==-4)// ƽ��
            {
               PlayState=STOP;
               return 0;
            }
//*********************************
            if (i>0)
            {
               PlayState=STOP;
               return 3-UserColor;// MessageBox(Handle,"�����ˣ�","SK������",MB_OK);
            }
            else
            {
               PlayState=MAN; // �ֻص�������
               return -1; // ��������
            }
         }
         else
         {
            PlayState=STOP;  //ֹͣ����
            if (StepLen>=225)
            {
              // MessageBox(Handle,"ƽ�֣�","SK������",MB_OK);
              return 0;
            }
            else
            {
              // MessageBox(Handle,"�������ˣ�","SK������",MB_OK);
              return 4;// ��������
            }
         }
      }//if (PlayState==3)
      else
         return -2;
   }//if PlayState==2                                  

   else //�ɼ����������
   {
      if(PlayState==PC)
      {
        int i=rand()%225; // �������������꣬Ŀ��Ϊ�˸������Ի�
       /* int i=Think(3-UserColor); */  //����˼����

        int qx=i/15;
        int qy=i%15;

        if (i>=0)
	    {
           i=put(qx,qy,3-UserColor); //��������
           // �������ӽ���
           posx=qx;
           posy=qy;
           if (i)
           {
              PlayState=STOP;
              return 3-UserColor;// MessageBox(Handle,"�����ˣ�","SK������",MB_OK);
           }
           else
           {
              PlayState=MAN; // �����ֻص���
              return -1; // ��������
           }
        }
      }//if pc
      else
         return -2; //�޷�����
      return -2; //�޷�����
   }//else
}
//------------------------------------------------------









