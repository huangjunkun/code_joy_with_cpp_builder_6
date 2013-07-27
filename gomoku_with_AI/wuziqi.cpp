
/*--------------------------------------------------------------------------

//  Ĭ���˻���ս�������£�����ִ��
�������ɻƿ������Ĵ��죬��ӭʹ�ã�лл��
������hjk ������ 1.0
���ߣ��ƿ���
���������������ɹ�ѧϰ���κ��˿����޸ĸ��ƣ�
������ע��ԭ������Ϣ
ע�⣺��Ȩ�������ƿ���

/---------------------------------------------------------------------------*/
/*  ���ʽһ��Ϊ: #Pragma Para
��������Para Ϊ��������������һЩ���õĲ�����

    (1)message ������ Message ����������ϲ����һ�����������ܹ��ڱ�����Ϣ��������������Ӧ����Ϣ�������Դ������Ϣ�Ŀ����Ƿǳ���Ҫ�ġ���ʹ�÷���Ϊ��
����#Pragma message(����Ϣ�ı���)
��������������������ָ��ʱ���ڱ�����������н���Ϣ�ı���ӡ������
�����������ڳ����ж���������������Դ����汾��ʱ�������Լ��п��ܶ���������û����ȷ��������Щ�꣬��ʱ���ǿ���������ָ���ڱ����ʱ��ͽ��м�顣��������ϣ���ж��Լ���û����Դ�����ʲô�ط�������_X86��������������ķ���
����#ifdef _X86
����#Pragma message(��_X86 macro activated!��)
����#endif
���������Ƕ�����_X86������Ժ�Ӧ�ó����ڱ���ʱ�ͻ��ڱ��������������ʾ��_X86 macro activated!�������ǾͲ�����Ϊ���ǵ��Լ������һЩ�ض��ĺ��ץ�������ˡ�

    (2)��һ��ʹ�õñȽ϶��pragma������code_seg����ʽ�磺
����#pragma code_seg(["section-name"[,"section-class"] ])
�������ܹ����ó����к��������ŵĴ���Σ������ǿ������������ʱ��ͻ�ʹ�õ�����
����(3)#pragma once (�Ƚϳ��ã�
����ֻҪ��ͷ�ļ����ʼ��������ָ����ܹ���֤ͷ�ļ�������һ�Σ�����ָ��ʵ����
    ��VC6�о��Ѿ����ˣ����ǿ��ǵ������Բ�û��̫���ʹ������
*/
#include <vcl.h>
#pragma hdrstop
/* (4)#pragma hdrstop��ʾԤ����ͷ�ļ�����Ϊֹ�������ͷ�ļ�������Ԥ���롣
BCB����Ԥ����ͷ�ļ��Լӿ����ӵ��ٶȣ����������ͷ�ļ�������Ԥ�����ֿ���
ռ̫����̿ռ䣬����ʹ�����ѡ���ų�һЩͷ�ļ��� */

#include "wuziqi.h"

//---------------------------------------------------------------------------
//��ʱ��Ԫ֮����������ϵ�����絥ԪA������ԪB�����Ե�ԪBҪ���ڵ�ԪA���롣�������#pragma startupָ���������ȼ�
#pragma package(smart_init)//ʹ����#pragma package(smart_init) ��BCB�ͻ�������ȼ��Ĵ�С�Ⱥ���롣

#pragma resource "*.dfm" //��ʾ��*.dfm�ļ��е���Դ���빤�̡�*.dfm�а���������۵Ķ��塣

//---------------------------------------------------------------------------
/*  //OR :  NO!!!!!!??????
         //�˻���սʱ���Է����������巽���ṹ����
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
        bool    exit_flag = false;  */
//---------------------------------------------------------------------------
#include "MyFunction.cpp"
//---------------------------------------------------------------------------
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    //ע�����̵�x��y�����������෴ ����������������������
    winner = ' ';
    //���ڻ�����˻���սʱ���Ը�����ѡ���������巽���Ĵ������λ�����飡

    //�������������鵱ǰ����λ��
    back_i = 0;
    //�˻���ս��־
    computer_to_man = 1;
    //���ֹ����־ ��ϷĬ�Ͻ��ֹ��� ���������Ӯ��־
    NO_three_and_three_flag = 1 ,break_three_and_three_flag = 0;
    //���ӱ�־
    black='b',white='w',gray = 'g' ,empty = '0' ,no_winner = 'n';//ƽ�ֶ���
    //black �ڷ� ������
    player = 'b';
    //�����˳���־�Ա����ڲ˵�ȷ���˳�֮�����ڴ���ȷ���˳�
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
    //��ʼ������
    if(winner==black)
    {
        ClipCursor(0);
        Image1->Visible = false;
        Label1->Caption="(Ctrl+n)��������?";
        Label3->Visible = false;
        ScrollBox1->Visible = true;
    }
    if(winner==white)
    {
        ClipCursor(0);
        Image1->Visible = false;
        Label1->Caption="(Ctrl+n)��������?";
        Label3->Visible = false;
        ScrollBox1->Visible = true;
    }
    InitBoard();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
    //int     i;
    //���Ƽ�������λ�ã����޶������̷�Χ֮�ڣ�����ɫ����Ϊ��־��
    if((Key=='d'||Key=='6')&&Shape1->Left-Image2->Left<440)// d����������������
        Shape1->Left=Shape1->Left+30;
    if((Key=='w'||Key=='8')&&Shape1->Top-Image2->Top>40)// w����������������
        Shape1->Top=Shape1->Top-30;
    if((Key=='a'||Key=='4')&&Shape1->Left-Image2->Left>40)// a����������������
        Shape1->Left=Shape1->Left-30;
    if((Key=='s'||Key=='5')&&Shape1->Top-Image2->Top<440)// s����������������
        Shape1->Top=Shape1->Top+30;
    if(Key==13)//�س����������� &&winner==' ' �����洦��ȽϺ�Щ
    {
        if(winner!=' ')// ��Ϸ��Ӯ֮��ֱ�ӻس�������
        {
            ClipCursor(0);
            if(winner=='w')
            {
                Image3->Visible = false;
                Label1->Caption="(Ctrl+n)��������???";
                Label3->Visible = false;
                ScrollBox1->Visible = true;
            }
            else
            {
                ClipCursor(0);
                Image1->Visible = false;
                Label1->Caption="(Ctrl+n)��������???";
                Label3->Visible = false;
                ScrollBox1->Visible = true;
            }
            return;
        }
        int ix,iy;
        ix=(Shape1->Left-15)/30; //���������λ��ת��Ϊ��Ӧ������λ�û�����Ӧ����λ��
        iy=(Shape1->Top-15)/30;
        //ע�����̵�x��y�����������෴
        if(board[iy][ix]==empty)
        {
            back_x[back_i] = iy; //������
            back_y[back_i] = ix;
            back_i++;
            Label2->Caption = "�����������壡";
            if(player==black)
            {
                DrawChess(ix,iy,10,black);
                board[iy][ix]=black;
                player = 'w';
                Label1->Caption="�׷�������";
            }
            else
            {
                DrawChess(ix,iy,10,white);
                board[iy][ix]=white;
                player = 'b';
                // Computer();
                Label1->Caption="�ڷ�������";
            }

            if(player == 'w'&&NO_three_and_three_flag==1)
            {
                if(NoThreeAndThree(iy,ix))
                {
                    break_three_and_three_flag = 1;
                    winner = 'w';
                    Label1->Caption="�ڷ����֣��׷�Ӯ��";
                    Gameover();
                }
            }

            if(IsWin(iy,ix)==black)
            {
                Label1->Caption="�ڷ�Ӯ���׷���";
                Gameover();
            }
            //�������̼�����������ʱ
            if(back_i==225)//���������̻�û����Ӯ��Ȼ��ƽ������
            {
                Label1->Caption="�ڰ׶�ս��ƽ�֣�";
                winner = no_winner;
                Gameover();
            }
            if((IsWin(iy,ix)==white)&&computer_to_man==0)
            {
                Label1->Caption="�׷�Ӯ���ڷ���";
                Gameover();
            }

            if(computer_to_man == 1&&winner==' ')
            {
                Computer(); //;
                player = 'b'; //��һ���ͺڷ�����
                if(IsWin(bestpos.x,bestpos.y)==white)
                {
                    Label1->Caption="�׷�Ӯ���ڷ���";
                    Gameover();
                }
                Label1->Caption="�ڷ�������...";
            }

        }

        else
            Label2->Caption = "�����ڲ����ڴ������ӣ�"; //StatusLine->Panels->Items[5]->Text="Can't put chess here!";

        Update();   // �������ݡ�����
        /*
         if(IsWin(iy,ix)==black)
         {
                 Label1->Caption="�ڷ�Ӯ���׷���";
                 Gameover();
         }
         if((IsWin(iy,ix)==white))
         {
                 Label1->Caption="�׷�Ӯ���ڷ���";
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
        Label1->Caption="ƽ��!\n��Ǹ�����ܻ�����!";
        return;
    }

    if(back_i!=0)
    {
        back_i--;
        //�ںڷ�δ��ʤ��û�г��ֽ��ֵ������£��͵��Զ��Ļ��嶨Ϊ����������
        if(computer_to_man==1&&winner!='b'&&!break_three_and_three_flag)
        {
            //&&(NO_three_and_three_flag==1&&winner==white)
            board[back_x[back_i]][back_y[back_i]] = empty;
            //����ԲΪ֮ǰ�ı�����ɫ������
            DrawChess(back_y[back_i],back_x[back_i],10,gray);
            //�ָ����̵����񡢡���
            {
                Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
                Image2->Canvas->MoveTo(back_y[back_i]*30+30,back_x[back_i]*30+30-12);  //��
                Image2->Canvas->LineTo(back_y[back_i]*30+30,back_x[back_i]*30+30+12);
                Image2->Canvas->MoveTo(back_y[back_i]*30+30-12,back_x[back_i]*30+30);  //��
                Image2->Canvas->LineTo(back_y[back_i]*30+30+12,back_x[back_i]*30+30);
            }
            /*
                          Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
                          Image2->Canvas->LineTo(back_y[back_i]*30+30-15,back_y[back_i]*30+30+15);

                          {
                          Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
                          Image2->Canvas->MoveTo(back_y[back_i]*30+30,30);  //��
                          Image2->Canvas->LineTo(back_y[back_i]*30+30,451);
                          Image2->Canvas->MoveTo(30,back_x[back_i]*30+30);  //��
                          Image2->Canvas->LineTo(450,back_x[back_i]*30+30);
                          }
                          */
            back_i--;
        }

        player = board[back_x[back_i]][back_y[back_i]];
        board[back_x[back_i]][back_y[back_i]] = empty;
        //����ԲΪ֮ǰ�ı�����ɫ������
        //ע�⣺���̵����У�x��y�������������෴

        DrawChess(back_y[back_i],back_x[back_i],10,gray);
        //�ָ����̵����񡢡���
        {
            Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
            Image2->Canvas->MoveTo(back_y[back_i]*30+30,back_x[back_i]*30+30-12);  //��
            Image2->Canvas->LineTo(back_y[back_i]*30+30,back_x[back_i]*30+30+12);
            Image2->Canvas->MoveTo(back_y[back_i]*30+30-12,back_x[back_i]*30+30);  //��
            Image2->Canvas->LineTo(back_y[back_i]*30+30+12,back_x[back_i]*30+30);
        }
        /*
                  Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
                  Image2->Canvas->LineTo(back_y[back_i]*30+30-15,back_y[back_i]*30+30+15);

                  {
                  Image2->Canvas->Pen->Color=clBlack;// ���㻭����ɫΪ��ɫ
                  Image2->Canvas->MoveTo(back_y[back_i]*30+30,30);  //��
                  Image2->Canvas->LineTo(back_y[back_i]*30+30,451);
                  Image2->Canvas->MoveTo(30,back_x[back_i]*30+30);  //��
                  Image2->Canvas->LineTo(450,back_x[back_i]*30+30);
                  } */

        if(player=='w')
            Label1->Caption="����ɹ�,�׷����壡";
        else
            Label1->Caption="����ɹ�,�ڷ����壡";
    }
    else
        Label1->Caption="��Ǹ�����ܻ����ˣ�";
    Shape1->Left=Image2->Left+back_y[back_i]*30+30;//����֮ǰ�Է�������λ��
    Shape1->Top=Image2->Top+back_x[back_i]*30+30;
    winner = ' ';
    break_three_and_three_flag = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{

    if(Application->MessageBoxA("���Ƿ����Ҫ�˳���Ϸ��","ȷ���˳���",MB_YESNOCANCEL)==IDYES)
    {
        exit_flag = true;
        Close();
    }

}
//---------------------------------------------------------------------------
//ע�����̵�x��y�����������෴ !!!!!!
void __fastcall TMainForm::Image1MouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //����Ҽ�ֱ�ӷ��أ�����ʾ�˵���������
    if(Button==mbRight)
        return;
    int ix,iy;
    ix=(X-15)/30; //���������λ��ת��Ϊ��Ӧ������λ�û�����Ӧ����λ��
    iy=(Y-15)/30; //ixʵ��Ϊ������У�iyʵ��Ϊ�������

    //�����������λ�ã����޶������̷�Χ֮��
    if(ix<0||iy<0||ix>14||iy>14)
        return;

    if(board[iy][ix]==empty&&winner==' ')
    {
        back_x[back_i] = iy; //������
        back_y[back_i] = ix;
        back_i++;
        Label2->Caption = "�����������壡";
        if(player==black)
        {
            DrawChess(ix,iy,10,black);
            board[iy][ix]=black;
            player = 'w';
            Label1->Caption="�׷�������...";
        }
        else
        {
            DrawChess(ix,iy,10,white);
            board[iy][ix]=white;
            player = 'b';
            Label1->Caption="�ڷ�������...";
        }
        Shape1->Left=Image2->Left+ix*30+25;//����֮ǰ�Է�������λ��
        Shape1->Top=Image2->Top+iy*30+25;
        if(player == 'w'&& NO_three_and_three_flag==1)
        {
            if(NoThreeAndThree(iy,ix))
            {
                break_three_and_three_flag = 1;
                winner = 'w';
                Label1->Caption="�ڷ����֣��׷�Ӯ��";
                Gameover();
            }

        }

        if(IsWin(iy,ix)==black)
        {
            Label1->Caption="�ڷ�Ӯ���׷���";
            Gameover();
        }
        //�������̼�����������ʱ
        if(back_i==225)//���������̻�û����Ӯ��Ȼ��ƽ������
        {
            Label1->Caption="�ڰ׶�ս��ƽ�֣�";
            winner = no_winner;
            Gameover();
        }
        if((IsWin(iy,ix)==white)&&computer_to_man==0)
        {
            Label1->Caption="�׷�Ӯ���ڷ���";
            Gameover();
        }

        if(computer_to_man == 1&&winner==' ')
        {
            Computer(); //;
            player = 'b'; //��һ���ͺڷ�����
            if(IsWin(bestpos.x,bestpos.y)==white)
            {
                Label1->Caption="�׷�Ӯ���ڷ���";
                Gameover();
            }
            //if(winner==' ')
            else //��elseЧ�ʱȽϸߣ�
                Label1->Caption="�ڷ�������...";
        }
    }
    else
        Label2->Caption = "�����ڲ����ڴ������ӣ�"; //StatusLine->Panels->Items[5]->Text="Can't put chess here!";

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image3Click(TObject *Sender)
{
    ClipCursor(0);
    Image3->Visible = false;
    Label1->Caption="(Ctrl+n)��������???";
    Label3->Visible = false;
    ScrollBox1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1Click(TObject *Sender)
{
    ClipCursor(0);
    Image1->Visible = false;
    Label1->Caption="(Ctrl+n)��������???";
    Label3->Visible = false;
    ScrollBox1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Image5Click(TObject *Sender)
{
    ClipCursor(0);
    Image5->Visible = false;
    Label1->Caption="(Ctrl+n)��������???";
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
    //����Ϸ�ѷֳ�ʤ���л���Ч������
    if(winner!= ' ')
    {
        Label1->Caption="�л�������Ч��";
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
            player = 'b'; //��һ���ͺڷ�����
            if(IsWin(bestpos.x,bestpos.y)==white)
            {
                Label1->Caption="�׷�Ӯ���ڷ���";
                Gameover();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Computertocomputer1Click(TObject *Sender)
{
    //�ù��ܻ�δʵ�֣�����������
    /*
    while(true)
    {
    if(player=='b')
    {
        Computer(); //
        player = 'w';
        if(IsWin(bestpos.x,bestpos.y)==black)
        {
                Label1->Caption="�ڷ�Ӯ���׷���";
                Gameover();
        }


    }
    else
    {
        Computer(); //
        player = 'b';
        if(IsWin(bestpos.x,bestpos.y)==white)
        {
                Label1->Caption="�׷�Ӯ���ڷ���";
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
    //����������Ϣ����ѡ
    //ShowMessage("!!! �ó����ɻƿ������Ĵ��� !!! \n     !!!������̣�������!!!   \n      !!! ѧ��06065072 !!!     \n           !!! лл !!!          ");
    Application->MessageBoxA("      !�������տ��֣�\n������hjk ������ 1.0\n\n�������ó����ɻƿ������Ĵ��� ������\n\n     ������������̣������࣡����   \n\n      ������ ѧ��06065072 ������     \n\n           ������ лл ������           ","����汾",MB_OK);
    //MessageBox(Handle ,"!!! �ó����ɻƿ������Ĵ��� !!! \n\n     !!!������̣�������!!!   \n\n      !!! ѧ��06065072 !!!     \n\n           !!! лл !!!           ","����汾",MB_OK);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Rule1Click(TObject *Sender)//������������
{
    if(NO_three_and_three_flag==1)
    {
        Rule1->Checked = false;
        Rule2->Checked = false;
        NO_three_and_three_flag = 0;
        Application->MessageBoxA("�ɹ�ȡ�����ֹ���","�������ֹ�����ʾ��",MB_OK);
    }
    else
    {
        Rule1->Checked = true;
        Rule2->Checked = true;
        NO_three_and_three_flag = 1;
        Application->MessageBoxA("�ɹ����ý��ֹ���","�������ֹ�����ʾ��",MB_OK);
    }
}
//---------------------------------------------------------------------------

//�رմ���ȷ�ϣ�
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(exit_flag == true||Application->MessageBoxA("���Ƿ����Ҫ�˳���Ϸ��","ȷ���˳���",MB_YESNOCANCEL)==IDYES)
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



