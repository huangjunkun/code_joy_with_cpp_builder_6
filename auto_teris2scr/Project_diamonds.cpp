//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR p, int)
{
    //p��ָ�������в�����ָ��
    String StartType;    //�������е�����ģʽ
    AnsiString Command = p,temp;
    //owMessage(Command);
    Command.UpperCase();
    HWND FatherWindow =NULL;
    if(Command=="")
        StartType = "/S"; //Ĭ��ȫ��ģʽ
    else
        StartType=Command.SubString(1,2);//��ȡ�����е�ǰ�����ַ�
    try
    {
        Application->Initialize();
        if(StartType=="/S") //������������
            Application->CreateForm(__classid(TMainForm), &MainForm);
        else  if(StartType=="/C") ////�������ô���
          ;// Stay----
        else  if(StartType=="/P") //�������ڸ�����ָ����Χ������
        {
            //��MainForm��ʾ�ڸ����ڵ�ָ������
            Application->CreateForm(__classid(TMainForm), &MainForm);
            //��ø�����ľ��
            FatherWindow=(HWND)(atol(ParamStr(2).c_str()));
            //��ȡ���ڵķ��
            long   style=GetWindowLong(Application->MainForm->Handle,GWL_STYLE);
            //��Style������Ӵ�������
            style=style|WS_CHILD;
            //����ManiForm����Ϊ�Ӵ���
            SetWindowLong(Application->MainForm->Handle,GWL_STYLE,style);
            //��������Ԥ������ΪMainForm�ĸ�����
            SetParent(Application->MainForm->Handle,FatherWindow);
            //��ȡ����Ԥ�����ڵĿͻ���
            RECT PreviewRect;
            GetClientRect(FatherWindow,&PreviewRect);
            //��MainForm�Ĵ��ڸ�������Ԥ�����ڵĿͻ���������ʾ��
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
