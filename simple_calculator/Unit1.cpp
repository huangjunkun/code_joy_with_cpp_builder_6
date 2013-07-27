//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <time.h>
#pragma hdrstop

#include "Unit1.h"

#include<iostream>

#include<stack>
#include<String>//用于定义string变量
#include<cstdlib>
#include <conio.h>
#include<windows.h>
#include<String>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


float   operate(float a,char theta,float b);
char	precede(char a,char b);
int	isptr	(char c);
void error();
//int   caozuo(String&  S);
int   caozuo();
TForm1 *Form1;
//计算器全局变量
int     i = 0;
char    _str[100] ,str[300];
//电子时钟全局变量
int     d [10][7];  //init_time[9];
//_strtime(init_time);
//Sting   S_time = init_time;
int     s = 0 ,m = 0 ,h = 0;
int     strat_flag = 0;

//_str = str;


//String  str;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    str[i++] = '1';
    Edit1->Text = str;
    //this->UpdateAction(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
    str[i++] = '2';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
    str[i++] = '3';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    str[i++] = '4';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
    str[i++] = '5';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    str[i++] = '6';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button15Click(TObject *Sender)
{
    str[i++] = '+';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    str[i++] = '7';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
    str[i++] = '8';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    str[i++] = '9';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    str[i++] = '0';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
    str[i++] = '.';
    Edit1->Text = str;
    //this->Update(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
    str[i++] = '-';
    Edit1->Text = str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button16Click(TObject *Sender)
{
    str[i++] = '*';
    Edit1->Text = str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button14Click(TObject *Sender)
{
    str[i++] = '/';
    Edit1->Text = str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button19Click(TObject *Sender)
{
    if (isdigit(str[i-1])||str[i-1]==')')
        str[i++] = '*';
    str[i++] = '(';
    Edit1->Text = str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button17Click(TObject *Sender)
{
    str[i++] = ')';
    Edit1->Text  = str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::jisuan(TObject *Sender)
{
    int     error_flag;
    //String  S = Edit1->Text;
    error_flag = caozuo();
    if (error_flag==1)
        Edit1->Text = "!!!error!!!";
    else
        Edit2->Text = str;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

int	isptr	(char c)
{
    int		flag;
    switch(c)
    {
    case'#' :
    case'+' :
    case'-' :
    case'*' :
    case'/' :
    case'(' :
    case')' :
        flag = 1;
        break;
    default :
        flag = 0;
        break;
    }
    if (flag)
        return 1;
    else
        return 0;
}


float operate(float a,char theta,float b)
{
    float	sum;
    switch	(theta)
    {
    case '+':
        sum	= a + b;
        break;
    case '-' :
        sum	= a - b;
        break;
    case '*' :
        sum	= a * b;
        break;
    case '/' :
        sum	= a / b;
        break;
    default	:
        //cout << " 程序有错误！！！\n";
        exit(1);
    }

    return	sum	;

}


char	precede(char a,char b)
{
    if (a == '#')
        return	'<';
    if (b == '#')
        return	'>';
    if (a == '#' && b == '#')
        return	'=';
    if (a == '(' && b == ')')
        return	'=';
    if (a == '(' && b != ')')
        return	'<';
    if (a != '(' && b == ')')
        return	'>';
    if (a == ')')
        return	'>';
    if (b == ')')
        return	'>';
    if (b == '(')
        return	'<';
    if ((a == '+' && b == '+')||(a == '+' && b == '-')||(a == '-' && b == '-')||(a == '-' && b == '+'))
        return	'>';
    if ((a == '*' && b == '*')||(a == '*' && b == '/')||(a == '/' && b == '/')||(a == '/' && b == '*'))
        return	'>';
    if ((b == '+' || b == '-')&&(a == '*' || a == '/'))
        return	'>';
    if ((a == '+' || a == '-')&&(b == '*' || b == '/'))
        return	'<';
    //cout << "		输入错误！！！\n";
    exit(0);
    return	'<';
}
void __fastcall TForm1::ce(TObject *Sender)
{
    Edit1->Text = " 0.0";
    //char    c[100];
    for (int m=0; m<100; m++)
        str[m] = _str[m];
    i = 0;

}
void error()
{
    for (int m=0; m<100; m++)
        str[m] = _str[m];
    i = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Backspace(TObject *Sender)
{
    if (i!=0)
        str[--i] = ' ';
    if (i==0)
        Edit1->Text = " 0.0";
    else
        Edit1->Text = str;

}
//---------------------------------------------------------------------------
int     caozuo() //String&  S
{
    //str[i++] = '#';
    String  S;
    int     error_flag = 0;
    int	mul_flag = 0;//默认相乘标记
    /*
    for (int n=1;n<=S.Length();n++)
            str[n-1] =S[n];
            */
    str[i++] = '#';
    stack<float>	s;
    stack<char>		optr , temp;
    optr.push('#');
    float	_num , a , b;
    //String  str;
    char	theta , next , pre_next = '#' ,aft_next;
    i = 0;
    next = str[i++];
    /*
    	if (!isptr(next) && !isdigit(next))
    {
    error();
            Edit1->Text = "!!!error!!!";
    }
    */

    while(next != '#' || optr.top()!='#')
    {
        if(!isptr(next)||(next=='-'&&isptr(pre_next)))
        {
            if(!isptr(next) && !isdigit(next))
            {
                cin.ignore(100, '\n');
            }
            int		j=0;
            char	num[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
            while (isdigit(next) || next == '.'||(next=='-'&&isptr(pre_next)))//isdigit(next)
            {
                num[j] = next;
                j++;
                pre_next = next;
                next = str[i++];
            }
            if (next=='\n')
                next = '#';
            if (num[0]=='-'&& !isdigit(num[1]))
            {
                //error();
                S = "!!!error!!!";
                error_flag = 1;
                break;
            }
            _num = atof(num);
            s.push(_num);
        }
        else
            switch (precede (optr.top(),next))
            {
            case '<' :
                optr.push(next);
                pre_next = next;
                if (mul_flag == 1)
                {
                    next = aft_next;
                    mul_flag = 0;
                }
                else
                {
                    next = str[i++];
                    if (next=='\n')
                        next = '#';
                }
                break;
            case '=' :
                if ((next != '#'))
                    temp.push(next);
                temp.push(optr.top());
                optr.pop();
                pre_next = next;
                if	(mul_flag == 1)
                {
                    next = aft_next;
                    mul_flag = 0;
                }
                else
                {
                    next = str[i++];
                    if (next=='\n')
                        next = '#';
                }
                break;
            case '>' :
                if (s.size() < 2)
                {
                    //error();
                    S = "!!!error!!!";
                    //exit(0);
                    error_flag = 1;
                    break;
                }
                //if (error_size == 1)
                //break;
                theta = optr.top();
                temp.push(theta);
                optr.pop();
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                if	(theta == '/' && b == 0)
                {
                    //error();
                    S = "!!!error!!!";
                    error_flag = 1;
                    break;
                }
                s.push (operate(a,theta,b));
                break;
            }
        if (error_flag == 1)
            break;
        if (next=='(' && (isdigit(pre_next)|| pre_next==')') ||(isdigit(next)&& pre_next==')'))
        {
            aft_next = next;
            next = '*';
            mul_flag = 1;
        }
    }
    //exit(0);
    //AnsiString  _s;

    if (S != "!!!error!!!"&&!s.empty())
        S = s.top();
    //char    _s_1 = _s[0];
    if (S == "!!!error!!!"||s.empty())
        error();
    else
    {
        //_s = S;
        int     _j=S.Length() ,_i = 1;
        //char    _c = _s[_i];

        while (_j--)
        {
            str[_i-1] =S[_i];
            _i++;
            //_c = _s[_i];
        }

        //char    c[100];
        for (int m=--_i; m<100; m++)
            str[m] = _str[m];
        i = _i;
    }
    return error_flag;
}
//---------------------------------------------------------------------------








/*
 //String  S = Edit1->Text;
        caozuo(Edit1->Text);
        Edit1->Text = str;
        *//*
void __fastcall TForm1::Edit1Enter(TObject *Sender)
{

        int     error_flag;
        int     num = 1;
        do
        {
                cin.get(Edit1->Text[num++]);
                if (Edit1->Text[num++]=='\n')
                        break;
        }while(true);
        //num--;
        //String  S = Edit1->Text;
        error_flag = caozuo(Edit1->Text);
        if (error_flag==1)
                Edit1->Text = "!!!error!!!";
        else
                Edit1->Text = str;


}

*/
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
    static int      replay_flag = 0;

    if (Key!=13&&(isdigit(Key)||isptr(Key)))
    {
        str[i++] = Key;
    }
    if (Key==8)
        i--;
    if (replay_flag==1)
        Edit1->Text = str;

    if (Key==13)//回车字符ACSII码
    {
        int     error_flag;
        error_flag = caozuo();
        if (error_flag==1)
            Edit1->Text = "!!!error!!!";
        else
            Edit2->Text = str;
        replay_flag = 1;
    }

    //Edit2->Text = str;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
    d[0][0] = 1;
    d[0][1] = 1;
    d[0][2] = 1;
    d[0][3] = 0;
    d[0][4] = 1;
    d[0][5] = 1;
    d[0][6] = 1;

    d[1][0] = 0;
    d[1][1] = 0;
    d[1][2] = 1;
    d[1][3] = 0;
    d[1][4] = 0;
    d[1][5] = 0;
    d[1][6] = 1;

    d[2][0] = 0;
    d[2][1] = 1;
    d[2][2] = 1;
    d[2][3] = 1;
    d[2][4] = 1;
    d[2][5] = 1;
    d[2][6] = 0;

    d[3][0] = 0;
    d[3][1] = 1;
    d[3][2] = 1;
    d[3][3] = 1;
    d[3][4] = 0;
    d[3][5] = 1;
    d[3][6] = 1;

    d[4][0] = 1;
    d[4][1] = 0;
    d[4][2] = 1;
    d[4][3] = 1;
    d[4][4] = 0;
    d[4][5] = 0;
    d[4][6] = 1;

    d[5][0] = 1;
    d[5][1] = 1;
    d[5][2] = 0;
    d[5][3] = 1;
    d[5][4] = 0;
    d[5][5] = 1;
    d[5][6] = 1;

    d[6][0] = 1;
    d[6][1] = 1;
    d[6][2] = 0;
    d[6][3] = 1;
    d[6][4] = 1;
    d[6][5] = 1;
    d[6][6] = 1;

    d[7][0] = 0;
    d[7][1] = 1;
    d[7][2] = 1;
    d[7][3] = 0;
    d[7][4] = 0;
    d[7][5] = 0;
    d[7][6] = 1;

    d[8][0] = 1;
    d[8][1] = 1;
    d[8][2] = 1;
    d[8][3] = 1;
    d[8][4] = 1;
    d[8][5] = 1;
    d[8][6] = 1;

    d[9][0] = 1;
    d[9][1] = 1;
    d[9][2] = 1;
    d[9][3] = 1;
    d[9][4] = 0;
    d[9][5] = 1;
    d[9][6] = 1;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void    TForm1::showA (int n)
{
    if (d[n][0]==1)
        Panel1->Visible = true;
    else
        Panel1->Visible = false;
    if (d[n][1]==1)
        Panel2->Visible = true;
    else
        Panel2->Visible = false;
    if (d[n][2]==1)
        Panel3->Visible = true;
    else
        Panel3->Visible = false;
    if (d[n][3]==1)
        Panel4->Visible = true;
    else
        Panel4->Visible = false;
    if (d[n][4]==1)
        Panel5->Visible = true;
    else
        Panel5->Visible = false;
    if (d[n][5]==1)
        Panel6->Visible = true;
    else
        Panel6->Visible = false;
    if (d[n][6]==1)
        Panel7->Visible = true;
    else
        Panel7->Visible = false;

}

//---------------------------------------------------------------------------
void    TForm1::showB (int n)
{
    if (d[n][0]==1)
        Panel8->Visible = true;
    else
        Panel8->Visible = false;
    if (d[n][1]==1)
        Panel9->Visible = true;
    else
        Panel9->Visible = false;
    if (d[n][2]==1)
        Panel10->Visible = true;
    else
        Panel10->Visible = false;
    if (d[n][3]==1)
        Panel11->Visible = true;
    else
        Panel11->Visible = false;
    if (d[n][4]==1)
        Panel12->Visible = true;
    else
        Panel12->Visible = false;
    if (d[n][5]==1)
        Panel13->Visible = true;
    else
        Panel13->Visible = false;
    if (d[n][6]==1)
        Panel14->Visible = true;
    else
        Panel14->Visible = false;

}

//---------------------------------------------------------------------------
void    TForm1::showC (int n)
{
    if (d[n][0]==1)
        Panel17->Visible = true;
    else
        Panel17->Visible = false;
    if (d[n][1]==1)
        Panel18->Visible = true;
    else
        Panel18->Visible = false;
    if (d[n][2]==1)
        Panel19->Visible = true;
    else
        Panel19->Visible = false;
    if (d[n][3]==1)
        Panel20->Visible = true;
    else
        Panel20->Visible = false;
    if (d[n][4]==1)
        Panel21->Visible = true;
    else
        Panel21->Visible = false;
    if (d[n][5]==1)
        Panel22->Visible = true;
    else
        Panel22->Visible = false;
    if (d[n][6]==1)
        Panel23->Visible = true;
    else
        Panel23->Visible = false;

}

//---------------------------------------------------------------------------
void    TForm1::showD (int n)
{
    if (d[n][0]==1)
        Panel24->Visible = true;
    else
        Panel24->Visible = false;
    if (d[n][1]==1)
        Panel25->Visible = true;
    else
        Panel25->Visible = false;
    if (d[n][2]==1)
        Panel26->Visible = true;
    else
        Panel26->Visible = false;
    if (d[n][3]==1)
        Panel27->Visible = true;
    else
        Panel27->Visible = false;
    if (d[n][4]==1)
        Panel28->Visible = true;
    else
        Panel28->Visible = false;
    if (d[n][5]==1)
        Panel29->Visible = true;
    else
        Panel29->Visible = false;
    if (d[n][6]==1)
        Panel30->Visible = true;
    else
        Panel30->Visible = false;
}
//---------------------------------------------------------------------------
void    TForm1::showE (int n)
{
    if (d[n][0]==1)
        Panel33->Visible = true;
    else
        Panel33->Visible = false;
    if (d[n][1]==1)
        Panel34->Visible = true;
    else
        Panel34->Visible = false;
    if (d[n][2]==1)
        Panel35->Visible = true;
    else
        Panel35->Visible = false;
    if (d[n][3]==1)
        Panel36->Visible = true;
    else
        Panel36->Visible = false;
    if (d[n][4]==1)
        Panel37->Visible = true;
    else
        Panel37->Visible = false;
    if (d[n][5]==1)
        Panel38->Visible = true;
    else
        Panel38->Visible = false;
    if (d[n][6]==1)
        Panel39->Visible = true;
    else
        Panel39->Visible = false;

}

//---------------------------------------------------------------------------
void    TForm1::showF (int n)
{
    if (d[n][0]==1)
        Panel40->Visible = true;
    else
        Panel40->Visible = false;
    if (d[n][1]==1)
        Panel41->Visible = true;
    else
        Panel41->Visible = false;
    if (d[n][2]==1)
        Panel42->Visible = true;
    else
        Panel42->Visible = false;
    if (d[n][3]==1)
        Panel43->Visible = true;
    else
        Panel43->Visible = false;
    if (d[n][4]==1)
        Panel44->Visible = true;
    else
        Panel44->Visible = false;
    if (d[n][5]==1)
        Panel45->Visible = true;
    else
        Panel45->Visible = false;
    if (d[n][6]==1)
        Panel46->Visible = true;
    else
        Panel46->Visible = false;
}


int     seconds (int s1,int s2)
{
    int s = s1+s2;
    if (s==60)
        s = 0;
    return s;

}

int     minutes (int m1,int m2)
{
    int m = m1+m2;
    if (m==60)
        m = 0;
    return m;

}
int     hours (int h1,int h2)
{
    int h = h1+h2;
    if (h==24)
        h = 0;
    return h;

}

void    TForm1::showSeconds (int s)
{
    String strm = s;
    if (strm.Length()==1)
    {
        showF(strm.ToInt());
        showE(0);
    }
    else
    {
        showF(strm.SubString(2,1).ToInt());
        showE(strm.SubString(1,1).ToInt());
    }
}

void    TForm1::showMinutes (int m)
{
    String strm = m;
    if (strm.Length()==1)
    {
        showD(strm.ToInt());
        showC(0);
    }
    else
    {
        showD(strm.SubString(2,1).ToInt());
        showC(strm.SubString(1,1).ToInt());
    }
}
void    TForm1::showHours (int h)
{
    String strh = h;
    if (strh.Length()==1)
    {
        showB(strh.ToInt());
        showA(0);
    }
    else
    {
        showB(strh.SubString(2,1).ToInt());
        showA(strh.SubString(1,1).ToInt());
    }
}


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    String  S;
    char time[9];
    _strtime(time);
    S = time;

    if (strat_flag == 0||m!=S.SubString(4,2).ToInt())
    {
        //s = time;
        Panel15->Visible = true;
        Panel16->Visible = true;
        Panel31->Visible = true;
        Panel32->Visible = true;
        h = S.SubString(1,2).ToInt();
        m = S.SubString(4,2).ToInt();
        s = S.SubString(7,2).ToInt();
        showHours(h);
        showMinutes(m);
        showSeconds(s);
        strat_flag = 1;
        char date[9];
        char date_show[11];
        _strdate(date);
        date_show[0]='2';
        date_show[1]='0';
        date_show[2]=date[6];
        date_show[3]=date[7];
        date_show[4]='-',date_show[5]=date[0],date_show[6]=date[1];
        date_show[7]='-',date_show[8]=date[3],date_show[9]=date[4],date_show[10]='\0';
        //Edit1->Text = "现在日期是";
        //Edit1->Text = date_show;
        Edit3->Text = date_show;
    }

    int     tm ,ts;

    /*
    if (Panel15->Visible)
    {
            Panel15->Visible = false;
            Panel16->Visible = false;
    }
    else
    {
            Panel15->Visible = true;
            Panel16->Visible = true;
    }
    */
    //if (s>(ts = minutes(s,1)))

    //ts = minutes(s,1);
    if (s>(ts = minutes(s,1)))
    {
        if (m>(tm = minutes(m,1)))
        {
            h = hours(h,1);
            showHours(h);
        }
        m = tm;
        showMinutes(m);
    }
    s = ts;
    showSeconds(s);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Enter(TObject *Sender)
{
    Edit1->SelectAll();
}
//---------------------------------------------------------------------------

