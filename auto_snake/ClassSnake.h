
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class   MySnake // : public TComponent
{
//private:
public:
    char    go_direction_flag;
//        int     TShape_nums ,snake_length;
    bool    food_exist;
    int     one_display_time;  //游戏一回合计时、、、
    int     one_time;
    bool    player;
    unsigned int     max_speed ,up_speed;
    int     X_max ,Y_max;
    unsigned int     max_length;
    int     init_speed;
    TTimer  *TimerGo; //,*TimerFood
    vector<TShape*> Shape_vec;  // ShapeArray
    //TShape  **ShapeArray;
    TShape  *Shape_Head;
public:
    /* 0号单元不用，最后一个单元为snake_length==max_length 时 食物预用  */
    void    MoveSnake();
    void    NewShape();
    void    FindDirection();
    void    InitSnake();
    void    GetFood();
    void    __fastcall TimerGoTimer(TObject *Sender);
    MySnake() {};
    //MySnake(int length);
    MySnake(TShape *Head ,int length);
};
//---------------------------------------------------------------------------

MySnake::MySnake(TShape *Head ,int length)
{
    //    MySnake();
    X_max = Screen->Width;//
    Y_max = Screen->Height;
    one_time = 120;  //回合时间--秒
    init_speed = 100;
    player = COMPUTER;

    /*
            go_direction_flag = RIGHT;
            max_speed = 150;
            up_speed = 50;
            TimerGo->Enabled = true;
            TimerGo->Interval = init_speed;     */
    //ShowMessage(String(X_max));
    TimerGo = new  TTimer(MainForm);// !!!!
    ShowMessage("!!!!!");
    TimerGo->OnTimer = TimerGoTimer;

    TShape *shape;
    shape = new TShape(MainForm);
    shape->Parent = MainForm;
    shape->Width = Head->Width;
    shape->Height= Head->Height;
    shape->Brush = Head->Brush;
    shape->Pen = Head->Pen;
    shape->Left = 0; // 24*30
    shape->Top  = 0;// 18*30
    Shape_vec.push_back(shape);
    Shape_Head = shape; // Shape_vec[0]

    max_length = length;
}
//---------------------------------------------------------------------------
void    MySnake::InitSnake() //??????
{
    TimerGo->Enabled = true;
    TimerGo->Interval = init_speed;

    go_direction_flag = RIGHT;
    max_speed = 150;
    up_speed = 50;

    for(int i=1; i< Shape_vec.size(); i++) //???????????????? ???
        delete Shape_vec[i]; //
    food_exist = false;
    one_display_time = 0;

}
//---------------------------------------------------------------------------
void __fastcall MySnake::TimerGoTimer(TObject *Sender)
{
    if(one_display_time>=one_time*2) //即30秒    /*  */
    {
        TimerGo->Enabled = false;
        InitSnake();
    }
    if(food_exist==false &&  max_length >=Shape_vec.size())
    {
        NewShape();
        food_exist = true;
    }
    //(--Shape_vec.end())
    if( Shape_Head->Left==Shape_vec[Shape_vec.size()-1]->Left&&
            Shape_Head->Top==Shape_vec[Shape_vec.size()-1]->Top )
    {
        GetFood();
    }
    /*
    if( snake_length==max_length )
         InitSnake();  */

    if(food_exist==false&& max_length >=Shape_vec.size())
    {
        NewShape();
        food_exist = true;
    }
    if(player == COMPUTER)
        FindDirection();
    MoveSnake();
    /* */
    if(Shape_Head->Left<0||Shape_Head->Left+Shape_Head->Width > X_max||
            Shape_Head->Top<0||Shape_Head->Top+Shape_Head->Height > Y_max )
    {
        TimerGo->Enabled = false;
//          DeaFlag->Visible = true;
//          DeaFlag->Caption = "oh ,sorry,你死了哦！";
    }
}
//---------------------------------------------------------------------------
void    MySnake::MoveSnake()
{
    for(int i=Shape_vec.size()-2; i>=1; i--)
    {
        //从蛇尾往蛇头迭代、、、、
        Shape_vec[i]->Left = Shape_vec[i-1]->Left;
        Shape_vec[i]->Top  = Shape_vec[i-1]->Top;
    }
    //Shape_vec[i].Left = TShape_vec[i-1].Left;
    //Shape_vec[i].Top = TShape_vec[i-1].Top;
    switch(go_direction_flag)
    {
    case UP:
        Shape_Head->Top-= 30; //Shape_Head->Height
        break;
    case DOWN:
        Shape_Head->Top+= 30;
        break;
    case LEFT:
        Shape_Head->Left-= 30;//Shape_Head->Width
        break;
    case RIGHT:
        Shape_Head->Left+= 30;
        break;
    default:
      ;//return;
    }
}
//---------------------------------------------------------------------------
void    MySnake::NewShape()
{

    TShape *shape;
    shape = new TShape(Application);
    shape->Parent = MainForm;
    shape->Width = Shape_Head->Width;
    shape->Height= Shape_Head->Height;
    shape->Brush = Shape_Head->Brush;
    shape->Pen = Shape_Head->Pen;
    {
        shape->Left = (rand()%(X_max/30-1))*30; // 24*30
        shape->Top  = (rand()%(Y_max/30-1))*30;// 18*30
    }

    Shape_vec[Shape_vec.size()-1]->Brush->Color = clLime;//注意,食物变为蛇身，颜色
    if( max_length >=Shape_vec.size() )
        Shape_vec.push_back(shape);

}
//---------------------------------------------------------------------------
void    MySnake::FindDirection()
{
    if( (Shape_Head->Left < Shape_vec[Shape_vec.size()-1]->Left)&&
            go_direction_flag!= LEFT )
        go_direction_flag = RIGHT;
    else if( Shape_Head->Left > Shape_vec[Shape_vec.size()-1]->Left &&
             go_direction_flag!= RIGHT  )
        go_direction_flag = LEFT;
    else if( Shape_Head->Top < Shape_vec[Shape_vec.size()-1]->Top )
        go_direction_flag = DOWN;
    else if( Shape_Head->Top > Shape_vec[Shape_vec.size()-1]->Top )
        go_direction_flag = UP;

    else
    {
        GetFood();
        go_direction_flag = STOP; //当即吃到食物、、、
    }
    /* */
}
//---------------------------------------------------------------------------

void    MySnake::GetFood()
{
    if(TimerGo->Interval>=max_speed)
    {
        TimerGo->Interval-=up_speed;
    }
    if(max_length!=Shape_vec.size())
      ;     //snake_length++
    else //(max_length==Shape_vec.size())
    {
        delete  Shape_vec[Shape_vec.size()-1];
        Shape_vec.pop_back();
    }

    food_exist = false;
    Shape_vec[Shape_vec.size()-1]->Brush->Color = Shape_Head->Brush->Color;//食物颜色变为蛇身颜色

}
//---------------------------------------------------------------------------
