//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR p, int)
{
    //p是指向命令行参数的指针
    String StartType;    //屏保运行的启动模式
    AnsiString Command = p,temp;
    //owMessage(Command);
    Command.UpperCase();
    HWND FatherWindow =NULL;
    if(Command=="")
        StartType = "/S"; //默认全屏模式
    else
        StartType=Command.SubString(1,2);//获取命令行的前两个字符
    try
    {
        Application->Initialize();
        if(StartType=="/S") //正常运行屏保
            Application->CreateForm(__classid(TMainForm), &MainForm);
        else  if(StartType=="/C") ////启动设置窗口
          ;// Stay----
        else  if(StartType=="/P") //将屏保在父窗体指定范围内运行
        {
            //将MainForm显示在父窗口的指定区域
            Application->CreateForm(__classid(TMainForm), &MainForm);
            //获得父窗体的句柄
            FatherWindow=(HWND)(atol(ParamStr(2).c_str()));
            //获取窗口的风格
            long   style=GetWindowLong(Application->MainForm->Handle,GWL_STYLE);
            //在Style中添加子窗体属性
            style=style|WS_CHILD;
            //设置ManiForm窗口为子窗口
            SetWindowLong(Application->MainForm->Handle,GWL_STYLE,style);
            //设置屏保预览窗口为MainForm的父窗口
            SetParent(Application->MainForm->Handle,FatherWindow);
            //获取屏保预览窗口的客户区
            RECT PreviewRect;
            GetClientRect(FatherWindow,&PreviewRect);
            //将MainForm的窗口覆盖屏保预览窗口的客户区，并显示它
            SetWindowPos(Application->MainForm->Handle,HWND_TOP,0,0,
                         PreviewRect.right,PreviewRect.bottom ,
                         SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
        }
        //-------------------------------------------------------------
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    catch (...)
    {
        try
        {
            throw Exception("");
        }
        catch (Exception &exception)
        {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
