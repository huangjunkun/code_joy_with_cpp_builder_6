//---------------------------------------------------------------------------

#include <vcl.h>


#pragma hdrstop


#include "Main.h"

//MySnake     *snake ;
vector<MySnake*> SnakeVec ;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
//#define init_speed   500
int     init_speed = 100 ;
//#define Max_speed    50
//#define one_time      120  //回合时间--秒
int     one_time = 120 ;  //回合时间--秒
//---------------------------------------------------------------------------
MySnake::MySnake(TShape *Head ,int length)
{ 
        if(SnakeNum>=2)
        { //
            MessageDlg( "MAX :SnakeNum = " +String(SnakeNum+1) ,mtInformation, TMsgDlgButtons() << mbOK, 0);
            Shape_Head = NULL ;
            return ;
        }
        X_max = Screen->Width ;//
        Y_max = Screen->Height ;
        one_time = 10 ;  //回合时间--秒
        init_speed = 100 ;
        player = COMPUTER ;// /////
        TimerGo = new  TTimer(MainForm) ;// !!!!
        //ShowMessage("!!!!!") ;
        TimerGo->OnTimer = TimerGoTimer ;
        //TimerGo->Interval = init_speed ;
        TimerGo->Enabled = false ;

        TShape *shape;
        shape = new TShape(MainForm) ;
        shape->Parent = MainForm ;
        shape->Width = Head->Width ;
        shape->Height= Head->Height ;
        shape->Brush = Head->Brush ;
        shape->Pen = Head->Pen ;
        shape->Left = 0 ; // 24*30
        shape->Top  = 0 ;// 18*30
        Shape_vec.push_back(shape)  ;
        Shape_Head = shape ; // Shape_vec[0]   
        max_length = length ;
        SnakeNum++ ;
        InitSnake() ;
}
//---------------------------------------------------------------------------
void    MySnake::InitSnake() //??????
{
        go_direction_flag = RIGHT ;
        max_speed = 150 ;
        up_speed = 50 ;

        for(int i=Shape_vec.size()-1 ;i>0 ;i=Shape_vec.size()-1) //???????????????? ???
        {
            delete Shape_vec[i]  ; //
            Shape_vec.pop_back() ;
        }

        food_exist = false ;
        count_time = one_time*1000 ;

        TimerGo->Interval = init_speed ;
        TimerGo->Enabled = true ;  
}
//---------------------------------------------------------------------------
void __fastcall MySnake::TimerGoTimer(TObject *Sender)
{
        //count_time += (double(TimerGo->Interval))/1000 ;
        //ShowMessage(String((int)count_time)) ;
        count_time -= TimerGo->Interval ;
        if(count_time <= 0) //即 one_time 秒    /*  */
        {
           TimerGo->Enabled = false ;
           InitSnake() ;
           return ;
        }
        if(food_exist==false &&  max_length >=Shape_vec.size())
        {
           NewShape() ;
           food_exist = true ;
        }
        //(--Shape_vec.end())
        if( Shape_Head->Left==Shape_vec[Shape_vec.size()-1]->Left&&
                Shape_Head->Top==Shape_vec[Shape_vec.size()-1]->Top )
        {
            GetFood() ;
        }
        if(food_exist==false&& max_length >=Shape_vec.size())
        {
           NewShape() ;
           food_exist = true ;
        }
        if(player == COMPUTER)
                FindDirection() ;
        MoveSnake() ;
        /* // Man Player 
        if(Shape_Head->Left<0||Shape_Head->Left+Shape_Head->Width > X_max||
        Shape_Head->Top<0||Shape_Head->Top+Shape_Head->Height > Y_max )
        {
          TimerGo->Enabled = false ;
//          DeaFlag->Visible = true ;
//          DeaFlag->Caption = "oh ,sorry,你死了哦！" ;
        }    */
}
//---------------------------------------------------------------------------
void    MySnake::MoveSnake()
  {
     for(int i=Shape_vec.size()-2 ;i>=1 ;i--)
     { //从蛇尾往蛇头迭代、、、、
        Shape_vec[i]->Left = Shape_vec[i-1]->Left ;
        Shape_vec[i]->Top  = Shape_vec[i-1]->Top ;
     }
       //Shape_vec[i].Left = TShape_vec[i-1].Left ;
       //Shape_vec[i].Top = TShape_vec[i-1].Top ;
     switch(go_direction_flag)
      {
      case UP:
              Shape_Head->Top-= 30 ; //Shape_Head->Height
      break ;
      case DOWN:
              Shape_Head->Top+= 30 ;
      break ;
      case LEFT:
              Shape_Head->Left-= 30 ;//Shape_Head->Width
      break ;
      case RIGHT:
              Shape_Head->Left+= 30 ;
      break ;
      default:
              ;//return ;
      }
  }
//---------------------------------------------------------------------------
void    MySnake::NewShape()
{

        TShape *shape;
        shape = new TShape(Application) ;
        shape->Parent = MainForm ;
        shape->Width = Shape_Head->Width ;
        shape->Height= Shape_Head->Height ;
        shape->Brush = Shape_Head->Brush ;
        shape->Brush->Color = clRed ;
        shape->Pen = Shape_Head->Pen ;
        {
            shape->Left = (rand()%(X_max/30-1))*30 ; // 24*30
            shape->Top  = (rand()%(Y_max/30-1))*30 ;// 18*30
        }

        Shape_vec[Shape_vec.size()-1]->Brush->Color = clLime ;//注意,食物变为蛇身，颜色
        if( max_length >=Shape_vec.size() )
                Shape_vec.push_back(shape)  ;

}
//---------------------------------------------------------------------------
void    MySnake::FindDirection()
{
        if( (Shape_Head->Left < Shape_vec[Shape_vec.size()-1]->Left)&&
                go_direction_flag!= LEFT )
            go_direction_flag = RIGHT ;
        else if( Shape_Head->Left > Shape_vec[Shape_vec.size()-1]->Left &&
                go_direction_flag!= RIGHT  )
                go_direction_flag = LEFT ;
             else if( Shape_Head->Top < Shape_vec[Shape_vec.size()-1]->Top )
                     go_direction_flag = DOWN ;
                  else if( Shape_Head->Top > Shape_vec[Shape_vec.size()-1]->Top )
                          go_direction_flag = UP ;
                         
                       else
                       {
                        GetFood() ;
                        go_direction_flag = STOP ; //当即吃到食物、、、
                       }
                      /* */
}
//---------------------------------------------------------------------------

void    MySnake::GetFood()
{
     if(TimerGo->Interval>=max_speed)
     {
            TimerGo->Interval-=up_speed ;
     }
     if(max_length!=Shape_vec.size())
         ;     //snake_length++
     else //(max_length==Shape_vec.size())
     {
        delete  Shape_vec[Shape_vec.size()-1] ;
        Shape_vec.pop_back() ;
     } 
     food_exist = false ;
     Shape_vec[Shape_vec.size()-1]->Brush->Color = Shape_Head->Brush->Color  ;//食物颜色变为蛇身颜色

}
//---------------------------------------------------------------------------
MySnake::~MySnake()
{
    TimerGo->Enabled = false ;
    //TimerGo->~TTimer() ;
    delete  TimerGo ;
    for(unsigned int i=0 ;i<Shape_vec.size() ;i++)
    {
        delete Shape_vec[i] ;
        Shape_vec[i] = NULL ;
    }
    Shape_Head = NULL ;
    SnakeNum-- ;
}
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
    MAX_LEN = 30 ;
    ShapeArray = new TShape*[MAX_LEN+2] ;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
        srand((unsigned) time(NULL));//该函数和rand函数配合使用，产生随机数的起始发生数据
        //randomize() ; //可能出现问题、、、、和上式一样功能
        //窗体初始化、、、
        //X_max = X_max/30 ;
        //Y_max = Y_max/30 ;
        X_max = Screen->Width ;//
        Y_max = Screen->Height ;
        
        Label_X->Left = X_max-40 ;
        Label_X->Top  = 8 ;
        Label_Y->Left = X_max-40 ;
        Label_Y->Top  = 32 ;
        ShowCursor(false) ;
        mouse_exist = false ;
        this->BorderStyle = bsNone ;
        this->WindowState = wsMaximized ;

        player = COMPUTER ;
        go_direction_flag = RIGHT ;
        TShape_nums  = 1 ;
        snake_length = TShape_nums ;
        Shape_Head->Top  = 0 ;
        Shape_Head->Left = 0 ;
        ShapeArray[1] = Shape_Head ;

        Init_Snake() ;
        /*
        count_time = 0 ;
        food_exist  = false ;
        Max_speed = 50 ;
        up_speed = 50 ;  */
        /*
        TShape_vec.push_back() ;
        TShape_vec[0].operator =(Shape_Head) ;
        //Shape_Head->operator =(TShape_vec[0]) ;
        TShape_vec.push_back(Shape2) ;
        TShape_vec.push_back(Shape3) ;   */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer_GoTimer(TObject *Sender)
{

        if(count_time <= 0 ) //即 one_time 秒    /*  */
        {                                      
           Timer_Go->Enabled = false ;
           Init_Snake() ;
        }
        if(food_exist==false && TShape_nums <= MAX_LEN)
        {
           New_Shape() ;
           food_exist = true ;
        }

        if( Shape_Head->Left==ShapeArray[TShape_nums]->Left&&
                Shape_Head->Top==ShapeArray[TShape_nums]->Top )
        {
            Get_Food() ;
        }
        /*
        if( snake_length==MAX_LEN )
             Init_Snake() ;  */

        if(food_exist==false&& TShape_nums <= MAX_LEN)
        {
           New_Shape() ;
           food_exist = true ;
        }
        if(player == COMPUTER)
                Find_Direction() ;
        Move_Snake() ;
        /* */
        if(Shape_Head->Left<0||Shape_Head->Left+Shape_Head->Width > X_max||
        Shape_Head->Top<0||Shape_Head->Top+Shape_Head->Height > Y_max )
        {
          Timer_Go->Enabled = false ;
          DeaFlag->Visible = true ;
          DeaFlag->Caption = "oh ,sorry,你死了哦！" ;
          //unsigned int  delay = 5;
          //sleep(5) ;//程序挂起5秒钟，即暂停、
          //Label1->Visible = false ;
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
        if(Key==27)
            Close() ;
        //if(Key==13)
            //ShowCursor(true) ;
        if(Key==' '&& Timer_Go->Enabled==false)
        {
            Timer_Go->Enabled = true ;
            return ;
        }
        //else
        if(Key==' ')
        {
            Timer_Go->Enabled = false ;

        }
        //人为控制
        /*
        switch(Key)
        {
        case UP:
        if(go_direction_flag!=DOWN)
                go_direction_flag = Key ;
        break ;
        case DOWN:
        if(go_direction_flag!=UP)
                go_direction_flag = Key ;
        break ;
        case LEFT:
        if(go_direction_flag!=RIGHT)
                go_direction_flag = Key ;
        break ;
        case RIGHT:
        if(go_direction_flag!=LEFT)
                go_direction_flag = Key ;
        break ;
        default:
                return ;
        }       */
}
//---------------------------------------------------------------------------
  void    TMainForm::Move_Snake()
  {
     for(int i=snake_length ;i>1 ;i--)
     { //从蛇尾往蛇头迭代、、、、
        ShapeArray[i]->Left = ShapeArray[i-1]->Left ;
        ShapeArray[i]->Top  = ShapeArray[i-1]->Top ;
     }
       //Shape_vec[i].Left = TShape_vec[i-1].Left ;
       //Shape_vec[i].Top = TShape_vec[i-1].Top ;
     switch(go_direction_flag)
      {
      case UP:
              Shape_Head->Top-= 30 ; //Shape_Head->Height
      break ;
      case DOWN:
              Shape_Head->Top+= 30 ;
      break ;
      case LEFT:
              Shape_Head->Left-= 30 ;//Shape_Head->Width 
      break ;
      case RIGHT:
              Shape_Head->Left+= 30 ;
      break ;
      default:
              ;//return ;
      }
  }
//---------------------------------------------------------------------------
void    TMainForm::New_Shape()
{

        TShape *shape;
        shape = new TShape(MainForm) ;
        shape->Parent = MainForm ;
        shape->Width = Shape_Head->Width ;
        shape->Height= Shape_Head->Height ;
        shape->Brush = Shape_Head->Brush ;
        //Shape4->Brush->Color = Shape_Head->Brush->Color ;
        //Shape4->Brush->Style = Shape_Head->Brush->Style ;
        shape->Pen = Shape_Head->Pen ;
        //if(snake_length!=12)
        {
        shape->Left = (rand()%(X_max/30-1))*30 ; // 24*30
        shape->Top  = (rand()%(Y_max/30-1))*30 ;// 18*30
        }
        Label_X->Caption = shape->Left ;
        Label_Y->Caption = shape->Top ;
        /*else
        {
        shape->Left = 24*30  ; // (rand()%25)*30
        shape->Top  = 18*30 ;// (rand()%19)*30
        }   */
        ShapeArray[TShape_nums]->Brush->Color = clLime ;//注意,食物变为蛇身，颜色
        if( TShape_nums <= MAX_LEN )
                ShapeArray[++TShape_nums] = shape ;

        //*Shape4->operator =(&Shape_Head)  ;
        //Shape_Head->Shape
        //Shape4 = Shape_Head ;
        /*
        Shapes->Top  = 300 ;
        Shape4->Left = 300 ;  */
}
//---------------------------------------------------------------------------
void  TMainForm::Find_Direction()
{
        if( (Shape_Head->Left < ShapeArray[TShape_nums]->Left)&&
                go_direction_flag!= LEFT )
            go_direction_flag = RIGHT ;
        else if( Shape_Head->Left > ShapeArray[TShape_nums]->Left &&
                go_direction_flag!= RIGHT  )
                go_direction_flag = LEFT ;
             else if( Shape_Head->Top < ShapeArray[TShape_nums]->Top )
                     go_direction_flag = DOWN ;
                  else if( Shape_Head->Top > ShapeArray[TShape_nums]->Top )
                          go_direction_flag = UP ;
                         
                       else
                       {
                        Get_Food() ;
                        go_direction_flag = STOP ; //当即吃到食物、、、
                       }
                      /* */
}
//---------------------------------------------------------------------------

void  TMainForm::Get_Food()
{
     if(Timer_Go->Interval>=max_speed)
     {
            Timer_Go->Interval-=up_speed ;

     }
     if(snake_length!=MAX_LEN)
        snake_length++ ;
     else
        delete  ShapeArray[TShape_nums--] ;

     food_exist = false ;
     ShapeArray[TShape_nums]->Brush->Color = Shape_Head->Brush->Color  ;//食物颜色变为蛇身颜色

}
//---------------------------------------------------------------------------

void  TMainForm::Init_Snake() //??????
{
        go_direction_flag = RIGHT ;
        max_speed = 150 ;
        up_speed = 50 ;

        for(int i=2 ;i<=TShape_nums ;i++) //???????????????? ???
            delete ShapeArray[i]  ; // 或是 ShapeArray[i]->~TShape() ;
        DeaFlag->Visible = false ;
        food_exist = false ;
        snake_length = 1 ;
        TShape_nums  = 1 ;
        count_time = one_time*1000 ;
        
        Timer_Go->Interval = init_speed ;
        Timer_Go->Enabled = true ;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Time_FoodTimer(TObject *Sender)
{
        count_time -= Time_Food->Interval ; //游戏一回合计时、、、
        //以下为食物闪烁效果、、、
        if( ShapeArray[TShape_nums]->Brush->Color==clLime )
           ShapeArray[TShape_nums]->Brush->Color = clYellow ;
        else if( ShapeArray[TShape_nums]->Brush->Color==clYellow )
                ShapeArray[TShape_nums]->Brush->Color = clGray ;
             else
                ShapeArray[TShape_nums]->Brush->Color = clLime ;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ItemPauseClick(TObject *Sender)
{
        Timer_Go->Enabled = false ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ContinueItemClick(TObject *Sender)
{
        Timer_Go->Enabled = true ;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ItemExitClick(TObject *Sender)
{
        Close() ;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ItemSetGameClick(TObject *Sender)
{
        Timer_Go->Enabled = false ;
        TForm   *Set_Form = new TForm(Application) ;
        Set_Form->Parent = MainForm ;
        Set_Form->Width  = 100 ;
        Set_Form->Height = 100 ;
        Set_Form->Top  = 100 ;
        Set_Form->Left = 100 ;
        Set_Form->Show() ;
        //this->ActiveControl = Set_Form ;//??????????   
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Image_ClientMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button==mbRight)
           return ;

        if(mouse_exist==false)
        {
           ShowCursor(true) ;
           mouse_exist = true ;
        }
        else
        {
           ShowCursor(false) ;
           mouse_exist = false ;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ItemAddSnakeClick(TObject *Sender)
{
    MySnake     *snake = new MySnake(Shape_Head ,15) ;
    if(snake->Shape_Head!=NULL)
        SnakeVec.push_back(snake) ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ItemDelSnakeClick(TObject *Sender)
{
    if(!SnakeVec.empty())
    {
      SnakeVec[SnakeVec.size()-1]->~MySnake() ;
      SnakeVec.pop_back() ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ItemBackgroundClick(TObject *Sender)
{
    TOpenPictureDialog     *openfile = new TOpenPictureDialog(this) ;
    openfile->Filter = "JPG 图像文件(*.jpg)|*.jpg" ;
    openfile->FilterIndex = 1 ;
    if(openfile->Execute())
    {
        Image_Client->Picture->LoadFromFile(openfile->FileName) ;
    }
    else
        Image_Client->Picture->Assign(NULL ) ;
        
    delete  openfile ;
}
//---------------------------------------------------------------------------

