
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "wuziqi.h"
//---------------------------------------------------------
/*  //OR :   NO!!!!!!??????
        //�˻���սʱ���Է����������巽���ṹ����
extern        best    bestpos;
        //ע�����̵�x��y�����������෴ ����������������������
extern        char    winner = ' ',board[15][15] ,back_board[15][15];
        //���ڻ�����˻���սʱ���Ը�����ѡ���������巽���Ĵ������λ�����飡
        //  back_x[225] , back_y[225] ,����һһ��Ӧ
extern        int     back_x[225] , back_y[225];
        //�������������鵱ǰ����λ��
extern        int     back_i = 0;
        //�˻���ս��־
extern        int     computer_to_man = 1;
        //���ֹ����־ ��ϷĬ�Ͻ��ֹ��� ���������Ӯ��־
extern        int     NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
        //���ӱ�־
extern        const  char black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//ƽ�ֶ���
        //black �ڷ� ������
extern        char player = 'b';
        //�����˳���־�Ա����ڲ˵�ȷ���˳�֮�����ڴ���ȷ���˳�
extern        bool    exit_flag = false;   */
//---------------------------------------------------------

//---------------------------------------------------------
void    TMainForm::InitBoard()
{
    winner = ' ';
    Image1->Visible = false; //  �ڷ���ʤ��־ ������
    Image3->Visible = false;//   �׷���ʤ��־
    player = 'b'; //��ʼ���ڷ������塢����
    back_i = 0; //��ʼ���������á�����
    Label3->Visible = false;

    Image2->Canvas->Pen->Color=clGray;//��ʼ�����̱���
    for(int i=0; i<481; i++)
    {
        Image2->Canvas->MoveTo(i,0);
        Image2->Canvas->LineTo(i,481);
    }
    Image2->Canvas->Pen->Color=clBlack;// ��ʼ����������
    for(int i=30; i<=450; i+=30)
    {
        Image2->Canvas->MoveTo(i,30);   //��
        Image2->Canvas->LineTo(i,450);
        Image2->Canvas->MoveTo(30,i);   //��
        Image2->Canvas->LineTo(450,i);
    }
    for(int i=3; i<=13; i+=4) //��ʽ����֮�еĺڵ��־
        for(int j=3; j<=13; j+=4)
            DrawChess(i,j,3,black);
    //��ʼ�����顢����
    for(int i=0; i<=14; i++)
        for(int j=0; j<=14; j++)
            board[i][j]=empty;
    for(int i=0; i<=5; i++)
        // StatusLine->Panels->Items[i]->Text=" ";//�����·���״̬��ʾ
        Label1->Caption="��Ϸ��ʼ��";
    Shape1->Left=Image2->Left+240-4;//���������ӱ�־
    Shape1->Top=Image2->Top+240-4;
}
//---------------------------------------------------------
void   TMainForm::DrawChess(int x,int y,int r,char color) //rΪ���Ӵ�С
{
    x = x*30+30; //?????
    y = y*30+30;
    //x=(x-3)*20;
    //y=(y-3)*20;
    if(color==gray)
    {
        Image2->Canvas->Pen->Color=clGray;//���ӱ�Ե��ɫ
        Image2->Canvas->Brush->Color=clGray;//������ɫ������

    }
    else
    {
        if(color==black)//  white    //�����еĺڵ��־
        {
            Image2->Canvas->Pen->Color=clBlack;//���ӱ�Ե��ɫ
            Image2->Canvas->Brush->Color=clBlack;//������ɫ��������
        }
        else
        {
            Image2->Canvas->Pen->Color=clWhite;
            Image2->Canvas->Brush->Color=clWhite;
        }
    }
    Image2->Canvas->Ellipse(x-r,y-r,x+r+1,y+r+1); //��Բ
}
//---------------------------------------------------------------------------

char    TMainForm::IsWin(int row , int col) //�У���
{
    int     i , j;
    string   str_w = "wwwww" , str_b = "bbbbb";
    string   s;
    char    array[16];
    array[15] = '\0';////�ඨ��һ��Ԫ��Ϊ���'\0��������ת��string
    // �����ж���Ӯ
    for(i=0; i<15; i++)
        array[i] = board[row][i];

    s = array;
    if(s.find(str_w,0)< s.length())
    {
        winner = 'w';
        return 'w';//�׷���ʤ������
    }
    if(s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//�׷���ʤ������
    }
    //�����ж���Ӯ
    for(i=0; i<15; i++)
        array[i] = board[i][col];
    s = array;
    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//�׷���ʤ������
    }

    if( s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//�׷���ʤ������
    }
    // �Խ����ж���Ӯ (2)
    if(row<=col)// LR���µ����϶Խ��� --�����Խ���
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //ȥ�������ַ���������
        array[i] = ' ';
    s = array;

    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//�׷���ʤ������
    }
    if( s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//�׷���ʤ������
    }

    if(row+col<15)//RL���µ����϶Խ��� --�����Խ���
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//ȥ�������ַ���������
    s = array;
    //s.append("\0");
    if(s.find(str_w,0)< s.size())
    {
        winner = 'w';
        return 'w';//�׷���ʤ������
    }

    if(s.find(str_b,0)< s.size())
    {
        winner = 'b';
        return 'b';//�׷���ʤ������
    }
    return '*';
}
//---------------------------------------------------------------------------
//���������жϣ�����ָ��λ��(row,col)�����ӳ��ֺ���NoThreeAndThree����true�����򷵻�false

bool    TMainForm::NoThreeAndThree(int row ,int col)
{
    int     i ,j;
    int     three_and_three_nums = 0;
    string   s;
    char    array[16];
    array[15] = '\0';
    ////�ඨ��һ��Ԫ��Ϊ���'\0��������ת��string
    // �����ж���Ӯ
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
    //�����ж���Ӯ
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
    // �Խ����ж���Ӯ (2)

    if(row<=col)// LR���µ����϶Խ��� --�����Խ���
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //ȥ�������ַ���������
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
    if(row+col<15)//RL���µ����϶Խ��� --�����Խ���
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//ȥ�������ַ���������
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
    //���������ʾ��Ӯ�����Ե�������
    ScrollBox1->Visible = false;
    if(winner==white)
    {
        Image3->Visible = true;
        TRect MyArea=this->Image3->BoundsRect;//������ꡢ����
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    else if(winner==black)
    {
        Image1->Visible = true;
        TRect MyArea=this->Image1->BoundsRect;// ������ꡢ����
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    else
    {
        Image5->Visible = true;
        TRect MyArea=this->Image5->BoundsRect;// ������ꡢ����
        MapWindowPoints(Handle,0,(LPPOINT)(&MyArea),2);
        ClipCursor(&MyArea);
    }
    Label3->Visible =true;
    Label3->Caption="�뵥����������ֱ�ӻس���";

}

//---------------------------------------------------------------------------
best	TMainForm::SearchForFirst(int row ,int col ,string item)
{
    best	b;
    b.from = 0;
    int     i , j;
    string   s;
    char    array[16];
    array[15] = '\0';////�ඨ��һ��Ԫ��Ϊ���'\0��������ת��string
    // �����ж���Ӯ
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
    //�����ж���Ӯ

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
    // �Խ����ж���Ӯ (2)

    if(row<=col)// LR���µ����϶Խ��� --�����Խ���
        for(i=0; i<15-(col-row); i++)
            array[i] = board[i][col-row+i];
    else
        for(i=0; i<15-(row-col); i++)
            array[i] = board[row-col+i][i];
    for(; i<15; i++) //ȥ�������ַ���������
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

    if(row+col<15)//RL���µ����϶Խ��� --�����Խ���
        for(i=0 ,j=row+col; i<=row+col; i++,j--)
            array[i] = board[j][i];
    else
        for(i=0 ,j=14; i<=28-(row+col); i++,j--)
            array[i] = board[j][row+col-14+i];
    for(; i<15; i++)
        array[i] = ' ';//ȥ�������ַ���������
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
    case 1: //��
        //b.x = row;
        b.y = b.y+i-1;
        break;
    case 2:  //��
        b.x = b.x+i-1;
        break;
    case 3: //���Խ���
        b.x = b.x+i-1;
        b.y = b.y+i-1;
        break;
    case 4: //���Խ���
        b.x = b.x-i+1;
        b.y = b.y+i-1;
        break;
    default:
        ////......
        break;
    }
}
//---------------------------------------------------------------------------

//ע�����̵�x��y�����������෴ ����������������������
void    TMainForm::Computer()
{
    //dots=0;
    //static  int     i=0;
    //best bestpos; //���ڴ˶��壬����Ϊȫ�ֱ����ȽϺ�
    //man=false;
    bestpos = SearchForBest();
    //bestpos.x = i;
    //bestpos.y = i++;
    if(board[bestpos.x][bestpos.y]==empty)
    {
        board[bestpos.x][bestpos.y] = white;
        DrawChess(bestpos.y,bestpos.x,10,white);
        back_x[back_i] = bestpos.x; //������
        back_y[back_i] = bestpos.y;
        back_i++;

    }
    else
        Label1->Caption="��������";

    //����֮ǰ�Է�/(���ԣ�������λ��
    Shape1->Left=Image2->Left+bestpos.y*30+25;
    Shape1->Top=Image2->Top+bestpos.x*30+25;
    /* //�ù��ܻ�δʵ��
    player = 'b'; //������ִ��Ϊ�����-����ս��������
    if(iswin(bestpos.x,bestpos.y)==white)
        {
          Label1->Caption="�׷�Ӯ���ڷ���";
          Gameover();
        }      */
}
//---------------------------------------------------------------------------
//���������һ����Ψһ������8070�ľ�����Ϣ����˿���ʱ��ֹ�þ��档

#pragma warn - 8070 // Turn off the warning message for warning #8070


best	TMainForm::SearchForBest()
{
    int     i;
    best bestpos;
    if(back_i>=7)
    {

        //����
        for(int i=back_i; i>=3; i-=2)
            //for(int i=3;i<back_i;i+=2)
        {
            //i = back_i;// ѭ���жϱȽϣ��Ӵ��Ѷȡ�������������ʡ�ԡ�
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

        //����
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

//����
        for(int i=back_i; i>=3; i-=2)
        {
            //i = back_i; // ѭ���жϱȽϣ��Ӵ���Ϸ�Ѷȡ�������������ʡ�ԡ�
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

//����
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

        //����
        for(int i=back_i; i>=3; i-=2)
        {
            //for(int i=3;i<=back_i;i+=2)         {
            //i = back_i;// ѭ���жϱȽϣ��Ӵ��Ѷȡ�������������ʡ�ԡ�
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
        //����

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
    //����
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
    //����
    static int      random_1 = 1; //��Ϸ�տ�ʼʱ���Ʊ仯�׷� ��������λ��
    if(random_1==1)
    {
        bestpos = SearchForFirst(back_x[back_i-1],back_y[back_i-1], "b0000");
        if(bestpos.from!=0)
        {
            static int      random_2 = 3; //���Ʊ仯��ʼʱ�׷� ��������λ��
            best    bestpos_temp;
            do
            {
                //�������Խ��߿�ʼ
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
            FirstChangeBest(bestpos,4);//ת��Ϊ���ĸ�λ�� ��Ŀ��λ�ö�λ�ڵ��ĸ�λ��
            static int      random_2 = 3; //���Ʊ仯��ʼʱ�׷� ��������λ��
            best    bestpos_temp;
            do
            {
                //�������Խ��߿�ʼ
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
//�ָ��þ���
#pragma warn + 8070 // Turn the warning message for warning #8070 back on
//---------------------------------------------------------------------------
