//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "RandomPlayUnit.h"
#include "About.h"
#include "FlyUnit.h"
#include "ShowNameUnit.h"
//Skin++
//#include "Skin++\SkinPPBCB.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pies"
#pragma resource "*.dfm"
#pragma resource "extrares.RES"
const int crMaletUp    = 15;
const int crMaletDown  = 16;

TMainForm *MainForm;

void    SetDisplay();
void    ResetDisplay();
void    ReadRecord(TControl* control ,String filename);
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    time_t t;
    srand((unsigned) time(&t));//��ʼ���������
    NowTimer = new TTimer(this);

    //--��ʼ�� ������Ļ -----
    InitScrollWords();
}
//---------------------------------------------------------------------------
void    TMainForm::SaveAbsenceRecord(String filename)
{
    MemoAbsence->Lines->SaveToFile(filename);
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainForm::WndProc(TMessage& Message)
{
    if(Message.Msg==WM_NCHITTEST)
    {
        static LPARAM     lParam = Message.LParam;
        static int     xPos = GET_X_LPARAM(lParam); // Windowsx.h
        static int     yPos = GET_Y_LPARAM(lParam);
        //::ScreenToClient(this->Handle ,TPoint(xPos ,yPos));
        static TPoint  ClientPoint = this->ScreenToClient(TPoint(xPos ,yPos));
        static FLASHWINFO   PFLASHWINFO;
        if(ClientPoint.x<0||ClientPoint.y<0 ||ClientPoint.x>Width||ClientPoint.y>Height)
        {     // ��˸ ���� ������
           PFLASHWINFO.cbSize=sizeof(FLASHWINFO);
           PFLASHWINFO.hwnd = Handle;
           PFLASHWINFO.dwFlags=FLASHW_ALL;
           PFLASHWINFO.uCount = 60;  //��˸ʱ�䡢������һ����
           PFLASHWINFO.dwTimeout = 1000;
           FlashWindowEx(&PFLASHWINFO);
        }
        else
        {       // ��˸ ���� ������
           PFLASHWINFO.cbSize=sizeof(FLASHWINFO);
           PFLASHWINFO.hwnd = Handle;
           PFLASHWINFO.dwFlags=FLASHW_ALL;
           PFLASHWINFO.uCount = 1;  //��˸ʱ�䡢������һ����
           PFLASHWINFO.dwTimeout = 1000;
           FlashWindowEx(&PFLASHWINFO);
        }

    }
    TMainForm::WndProc(Message);
}  */  /*
void __fastcall TMainForm::WMNCHITTEST(TMessage &Message)
{ //        ...........
}     */

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    Screen->Cursors[crMaletUp] = LoadCursor(HInstance, "MaLetUp");
    Screen->Cursors[crMaletDown] = LoadCursor(HInstance, "MaLetDown");
    ButtonCheck->Cursor = TCursor(crMaletUp);
    ButtonAbsence->Cursor = TCursor(crMaletDown);

    NowTimer->OnTimer = TimerTimer;
    ImageStatistics->Transparent = true;
    ImageStatistics->Canvas->FillRect(ImageStatistics->Canvas->ClipRect);
    TabSheet1->Show();
    TabSheet4->DoubleBuffered = true;
    PanelView->DoubleBuffered = true;
    ButtonRondomCheck->Enabled = false;
    MemoStudent->ReadOnly = true;
    MemoAbsence->ReadOnly = true;
    MemoAbsence->Lines->Clear(); //MemoAbsence->Clear();

    ListBoxCheck->Items->Clear();
    RosterFile = "AllStudent.txt";
    ReadRecord(ListBoxCheck ,"AllStudent.txt");
    ReadRecord(MemoStudent ,"AllStudent.txt");
    ListBoxCheck->ItemIndex = 0;/*  */

    FileListBox1->MultiSelect = true;
    StringGrid1->Cells[0][0] = "ѧ����Ϣ";
    StringGrid1->Cells[1][0] = "ȱ�ڴ���";

    //ShowMessage("TMainForm::FormCreate(TObject *Sender)");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
    ListBoxCheck->SetFocus();
    CurrentStringIndex=-1;
    TimerFlash->Enabled=true;
    FlyAngelMenuClick(Sender);
    ShowNameForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBoxCheckKeyPress(TObject *Sender, char &Key)
{
    if(Key=='y'||Key=='Y') //    Key==13||
    {
        ButtonCheckClick(Sender);
    }
    if(Key=='n'||Key=='N')//   ||Key==' '
    {
        ButtonAbsenceClick(Sender);
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ButtonCheckClick(TObject *Sender)
{
    //  ButtonCheck->Cursor = TCursor(crMaletDown);
    if(ListBoxCheck->Count>1) //->ItemIndex>=0
    {
        int     index = ListBoxCheck->ItemIndex;
        ListBoxCheck->Items[0].Delete(ListBoxCheck->ItemIndex);
        ListBoxCheck->ItemIndex = (index==ListBoxCheck->Count ? index-1 :index);
        ShowNameForm->LabelShow->Caption = ListBoxCheck->Items->Strings[ListBoxCheck->ItemIndex];
        ShowNameForm->LabelShow->Left = (Screen->Width-ShowNameForm->LabelShow->Width)/2;

        //if(ListBoxCheck->Items->Count==0)
    }
    else if(ListBoxCheck->Count==1)
    {
        ListBoxCheck->Items[0].Delete(ListBoxCheck->ItemIndex);
        AbsenceFile = LabeledEdit2->Text+ Date();
        AbsenceFile += "ѧ��ȱ�μ�¼.txt";
        if(MessageDlg("���������� ,�Զ��������ļ���"+AbsenceFile  ,
                      mtInformation ,TMsgDlgButtons()<<mbYes<<mbNo ,0)==mrYes)
        {
            SaveAbsenceRecord(AbsenceFile);
            MemoAbsence->ReadOnly = true;
            MemoAbsence->Modified = false;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAbsenceClick(TObject *Sender)
{
    /*-------   */
    if(ListBoxCheck->Count>1)   //  ListBoxCheck->ItemIndex>=0
    {
        int     index = ListBoxCheck->ItemIndex;
        MemoAbsence->Lines->Add(ListBoxCheck->Items[0][ListBoxCheck->ItemIndex]);
        ListBoxCheck->Items[0].Delete(ListBoxCheck->ItemIndex);
        ListBoxCheck->ItemIndex = (index==ListBoxCheck->Count ? index-1 :index);
        ShowNameForm->LabelShow->Caption = ListBoxCheck->Items->Strings[ListBoxCheck->ItemIndex];
        ShowNameForm->LabelShow->Left = (Screen->Width-ShowNameForm->LabelShow->Width)/2;
        //if(ListBoxCheck->Items->Count==0)
    }
    else if(ListBoxCheck->Count==1)
    {
        MemoAbsence->Lines->Add(ListBoxCheck->Items[0][ListBoxCheck->ItemIndex]);
        ListBoxCheck->Items[0].Delete(ListBoxCheck->ItemIndex);
        AbsenceFile = LabeledEdit2->Text+ Date();
        AbsenceFile += "ѧ��ȱ�μ�¼.txt";
        if(MessageDlg("���������� ,�Զ��������ļ���"+AbsenceFile  ,
                      mtInformation ,TMsgDlgButtons()<<mbYes<<mbNo ,0)==mrYes)
        {
            SaveAbsenceRecord(AbsenceFile);
            MemoAbsence->ReadOnly = true;
            MemoAbsence->Modified = false;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonRondomCheckClick(TObject *Sender)
{
    if(ListBoxCheck->Items->Count==0)
        return;
    RondomNO = rand()%ListBoxCheck->Items->Count;
    String  RondomStr =  ListBoxCheck->Items[0][RondomNO];
    PlayRandomForm->ShowModal();
    ListBoxCheck->ItemIndex = RondomNO;
    ShowNameForm->LabelShow->Caption = ListBoxCheck->Items->Strings[ListBoxCheck->ItemIndex ];
    ShowNameForm->LabelShow->Left = (Screen->Width-ShowNameForm->LabelShow->Width)/2;

    /*   */
    switch(MessageDlg("���������" + RondomStr ,mtInformation ,
                       TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel ,0))
    {
    case mrYes :
        ButtonCheckClick(Sender);
        break;
    case mrNo :
        ButtonAbsenceClick(Sender);
        break;
    case mrCancel :
        return;
        //break;
    default:
        break;
    }
    RondomNum--;
    LabeledEdit1->Text =  RondomNum;

    if(RondomNum==0)
    {
        ListBoxCheck->ItemIndex = 0;
        AbsenceFile = LabeledEdit2->Text+ Date();
        AbsenceFile += "ѧ��ȱ�μ�¼.txt";
        if(MessageDlg("���������� ,�Զ��������ļ���"+AbsenceFile  ,
                      mtInformation ,TMsgDlgButtons()<<mbYes<<mbNo ,0)==mrYes)
        {
            SaveAbsenceRecord(AbsenceFile);
            MemoAbsence->ReadOnly = true;
            MemoAbsence->Modified = false;
        }
        return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAbsenseEditClick(TObject *Sender)
{
    MemoAbsence->ReadOnly = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAbsenceSaveClick(TObject *Sender)
{
    AbsenceFile = LabeledEdit2->Text+ Date();
    AbsenceFile += "ѧ��ȱ�μ�¼.txt";
    SaveAbsenceRecord(AbsenceFile); //LabeledEdit2
    MemoAbsence->ReadOnly = true;
    MemoAbsence->Modified = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnAbsenceSaveClick(TObject *Sender)
{
    SaveDialog1->FileName = LabeledEdit2->Text+ Date();
    SaveDialog1->FileName = SaveDialog1->FileName+"ѧ��ȱ�μ�¼";
    if(SaveDialog1->Execute())
    {
        MemoAbsence->Lines->SaveToFile(SaveDialog1->FileName);
    }
    MemoAbsence->ReadOnly = true;
    MemoAbsence->Modified = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAbsenceRefreshClick(TObject *Sender)
{
    try
    {
        MemoAbsence->Lines->LoadFromFile(AbsenceFile);
    }
    catch(...)
    {
        ShowMessage("��ǰ�ļ��в�����"+ AbsenceFile);
    }
    MemoAbsence->ReadOnly = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButtonAllSaveClick(TObject *Sender)
{
    //RosterFile = LabeledEdit2->Text+"AllStudent.txt";
    MemoStudent->Lines->SaveToFile(RosterFile);
    MemoStudent->ReadOnly = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnAllSaveClick(TObject *Sender)
{
    SaveDialog1->FileName = RosterFile;
    if(SaveDialog1->Execute())
    {
        MemoStudent->Lines->SaveToFile(SaveDialog1->FileName);
    }
    MemoStudent->ReadOnly = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimerTimer(TObject *Sender)
{
    /*
       if(PanelView->Color==clMax)
       {
           PanelView->Color = clMin;//%clMax;
           //ShowMessage("PanelView->Color==clMax");
       }
       else
           PanelView->Color = (PanelView->Color+1);//  */
    if(bShowWord == false)
    {
        int width = PaintBoxAbout->Width,h = PaintBoxAbout->Height;
        for(int i=h; i>=0; i--)
        {
            PaintBoxAbout->Canvas->Pen->Color= (TColor)RGB(rand()%256 ,rand()%256 ,rand()%256);    //(TColor)RGB(i*255/h/10,i*255/h/20,i*255/h)
            PaintBoxAbout->Canvas->MoveTo(0,i);
            PaintBoxAbout->Canvas->LineTo(width,i);
        }
    }
    StatusBar1->Panels[0][1]->Text = Now();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBoxRandomClick(TObject *Sender)
{
    ButtonRondomCheck->Enabled = CheckBoxRandom->Checked;
    LabeledEdit1->Visible = CheckBoxRandom->Checked;
    if(CheckBoxRandom->Checked)
    {
        LabeledEdit1->Text = String(ListBoxCheck->Items->Count/5);
        MessageDlg("���ȳ�ʼ�������������!"  ,
                   mtInformation ,TMsgDlgButtons()<<mbOK ,0);
        //ButtonRondomCheck->Enabled = true;
        //LabeledEdit1->Visible = true;
    }     /*
    else
    {
        ButtonRondomCheck->Enabled = false;
        LabeledEdit1->Visible = false;
    }     */
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::LabeledEdit1Change(TObject *Sender)
{
    try
    {
        int     num = LabeledEdit1->Text.ToInt();
        if(num > ListBoxCheck->Items->Count ||num <0)
        {
            MessageDlg("����ȷ��ʼ������������� !"  ,
                       mtInformation ,TMsgDlgButtons()<<mbOK ,0);
            LabeledEdit1->Text = String(ListBoxCheck->Items->Count/5);
        }
        RondomNum = num;
    }
    catch(...)
    {
        MessageDlg("����ȷ��ʼ�������������!"  ,
                   mtInformation ,TMsgDlgButtons()<<mbOK ,0);
        LabeledEdit1->Text = String(ListBoxCheck->Items->Count/5);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAllEditClick(TObject *Sender)
{
    MemoStudent->ReadOnly = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonAllRefreshClick(TObject *Sender)
{
    try
    {
        MemoStudent->Lines->LoadFromFile(RosterFile);
    }
    catch(...)
    {
        ShowMessage("��ǰ�ļ��в�����"+ RosterFile);
    }
    MemoStudent->ReadOnly = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenAllMenuClick(TObject *Sender)
{
    if(OpenDialog1->Execute())
    {
        ListBoxCheck->Items->Clear();
        ReadRecord(ListBoxCheck ,OpenDialog1->FileName);
        ListBoxCheck->ItemIndex = 0;
        MemoStudent->Lines->Clear();
        ReadRecord(MemoStudent ,OpenDialog1->FileName);
        //MemoStudent->Lines->LoadFromFile(OpenDialog1->FileName);
        RosterFile = ExtractFileName(OpenDialog1->FileName);
        String  TempFile = ExtractFileName(OpenDialog1->FileName);
        TempFile.SetLength(TempFile.Length()-4);
        LabeledEdit2->Text  = TempFile;
    }
    TabSheet1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenAbsenceMenuClick(TObject *Sender)
{
    if(OpenDialog1->Execute())
    {
        MemoAbsence->Lines->Clear();
        MemoAbsence->Lines->LoadFromFile(OpenDialog1->FileName);
        AbsenceFile =  ExtractFileName(OpenDialog1->FileName);
    }
    TabSheet2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenStudentMenuClick(TObject *Sender)
{
    if(OpenDialog1->Execute())
    {
        MemoStudent->Lines->Clear();
        MemoStudent->Lines->LoadFromFile(OpenDialog1->FileName);
        RosterFile = ExtractFileName(OpenDialog1->FileName);
    }
    TabSheet3->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitMenuClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(MemoAbsence->Modified==true)
    {
        switch(MessageDlg("ѧ��ȱ�μ�¼�и���δ���� ��\n�Ƿ񱣴棨Ĭ���ļ�������"  ,mtInformation ,
                           TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel ,0))
        {
        case mrYes :
            AbsenceFile = LabeledEdit2->Text+ Date();
            AbsenceFile += "ѧ��ȱ�μ�¼.txt";
            SaveAbsenceRecord(AbsenceFile);
            break;
        case mrNo :
        ; //
            break;
        case mrCancel :
            Action = caNone;
            return;
            //break;
        default:
            break;
        }
    }
    TimerFlash->Enabled = false;  //--------
    FlyForm->StopFlyAngelActionExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
    int height;
    int i,j;

    for(i=0; i<StringColorCount; i++)
    {
        delete[] StringColors[i];
    }
    delete[] StringColors;

    delete[] StringOnClicks;
    delete[] StringCursors;
    delete[] StringColorIndex;
    delete[] StringRectangles;

    delete AboutStringList;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
    if(Image1->Picture->Graphic==NULL)
    {
        int width = Image1->Width,h = Image1->Height;
        for(int i=h; i>=0; i--)
        {
            Image1->Canvas->Pen->Color=(TColor)RGB(i*255/h/10,i*255/h/20,i*255/h);
            Image1->Canvas->MoveTo(0,i);
            Image1->Canvas->LineTo(width,i);
        }
    }
    /*
    try
    {
        //Graphics::TBitmap   *bmp = new Graphics::TBitmap;
        //bmp->LoadFromFile("background.bmp");
        TJPEGImage   *jpg = new TJPEGImage; //Graphics::
        jpg->LoadFromFile("background.jpg");
        ListBoxCheck->Canvas->Draw(0 ,0 ,jpg);
    }
    catch(...)
    {
        MessageDlg("���ر���ͼ��--background.jpg ����" ,
                mtWarning ,TMsgDlgButtons()<<mbOK ,0);
    }    */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
    PaintBoxAbout->Left=(MainForm->Width-StringMaximumWidth)>>1;
    PaintBoxAbout->Width = StringMaximumWidth;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControl1Change(TObject *Sender)
{
    //ShowMessage("PageControl1Change");
    if(PageControl1->ActivePage!=TabSheet4)
        if(PageControl1->ActivePage==TabSheet1)
            Image1->Parent = ScrollBox1;
        else
            Image1->Parent = PageControl1->ActivePage;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1DblClick(TObject *Sender)
{
    TOpenPictureDialog  *OpenPicture = new TOpenPictureDialog(this);
    if(OpenPicture->Execute())
    {
        Image1->Picture->LoadFromFile(OpenPicture->FileName);
    }
    else
    {
        Image1->Picture->Graphic = NULL;
        this->Repaint();
    }

    delete OpenPicture;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtnStatisticsClick(TObject *Sender)
{
    for(int i=0; i<MemoStudent->Lines->Count; i++)
        if(MemoStudent->Lines[0][i]=="")
            MemoStudent->Lines->Delete(i--); //Count-- -> i--
    for(int i=0; i<MemoAbsence->Lines->Count; i++)
        if(MemoAbsence->Lines[0][i]=="")
            MemoAbsence->Lines->Delete(i--);

    int     CheckCount = MemoStudent->Lines->Count-MemoAbsence->Lines->Count;

    static double  CheckRate = (static_cast<double>(CheckCount)/MemoStudent->Lines->Count)*2*PI;
    int     R = ImageStatistics->Height/2;//ImageStatistics->Width/2
    //�Ȳ���֮ǰͳ��Canvas
    //ImageStatistics->Canvas->FillRect(ImageStatistics->Canvas->ClipRect);
    ImageStatistics->Canvas->Brush->Color = PageControl1->Canvas->Brush->Color;
    ImageStatistics->Canvas->Pen->Color = PageControl1->Canvas->Brush->Color;
    ImageStatistics->Canvas->Pie(0 ,0 ,ImageStatistics->Width ,ImageStatistics->Height ,
                                 0 ,R ,R*(1-cos(CheckRate)) ,R*(1+sin(CheckRate)));
    CheckRate = (static_cast<double>(CheckCount)/MemoStudent->Lines->Count)*2*PI;
    ImageStatistics->Canvas->Pen->Color = clBlack;
    ImageStatistics->Canvas->Brush->Color = clGreen;
    ImageStatistics->Canvas->Pie(0 ,0 ,ImageStatistics->Width ,ImageStatistics->Height ,
                                 0 ,R ,R*(1-cos(CheckRate)) ,R*(1+sin(CheckRate))); //
    //ImageStatistics->Canvas->Pie(0 ,0 ,ImageStatistics->Width ,ImageStatistics->Height ,
    //                             0 ,R ,R ,2*R);
    //ShowMessage(String(CheckCount));
    LabelStatistics->Caption ="ѧ��������" + String(MemoStudent->Lines->Count) +
                              " ,����������" + String(CheckCount) +
                              " ,ȱ��������" + String(MemoAbsence->Lines->Count);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutMenuClick(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpMenuClick(TObject *Sender)
{
    //
    ShellExecute(Handle,"open","help.doc",NULL,NULL,SW_SHOW);//SW_SHOWNORMAL
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimerFlashTimer(TObject *Sender)
{
    DrawAboutFlash(Sender);
    PictureTop-=1;
    if(PictureTop+StringsHeight<=0)
    {
        PictureTop=PaintBoxAbout->Height-1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PaintBoxAboutMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    TimerFlash->Enabled=false;
    int i;
    CurrentStringIndex=-1;
    for(i=0; i<StringCount; i++)
    {
        if(X>=StringRectangles[i].left && X<StringRectangles[i].right && Y-PictureTop>=StringRectangles[i].top && Y-PictureTop<StringRectangles[i].bottom)
        {
            PaintBoxAbout->Cursor=StringCursors[i];
            CurrentStringIndex=i;
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ListBoxCheckMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y)
{
    if(bShowWord)  // ==true;
        TimerFlash->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonCheckMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    /*     !!!!!!!!1
     if(Sender==ButtonCheck)
         ShowMessage("Sender==ButtonCheck");    */
    //dynamic_cast<TButton*>(Sender)->Cursor = TCursor(crMaletUp);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonCheckMouseUp(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //dynamic_cast<TButton*>(Sender)->Cursor = TCursor(crMaletDown);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetDiplayPopupClick(TObject *Sender)
{
    if(SetDiplayPopup->Checked==false)
        SetDisplay();
    else
        ResetDisplay();
    SetDiplayPopup->Checked = !SetDiplayPopup->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FlyAngelMenuClick(TObject *Sender)
{
    if(FlyAngelMenu->Checked==false)
    {
        FlyForm->Show();
        FlyForm->StartFlyAngelActionExecute(this);
    }
    else
        FlyForm->StopFlyAngelActionExecute(this);
    FlyAngelMenu->Checked = !FlyAngelMenu->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBoxFileStaClick(TObject *Sender)
{
    PanelFileSta->Visible = CheckBoxFileSta->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ImportFileAboutClick(TObject *Sender)
{
    MessageDlg("��ѡ��ȱ�ڼ�¼�ļ� ��Ȼ����ͳ��!"  ,
               mtInformation ,TMsgDlgButtons()<<mbOK ,0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ImportFilePopupClick(TObject *Sender)
{
    /**/
    for(int i=0; i<FileListBox1->Count; i++)
    {
        if(FileListBox1->Selected[i])//==true
        {
            String  FileName = FileListBox1->Directory+"\\"+FileListBox1->Items->Strings[i];
            ifstream    fin;
            fin.open(FileName.c_str() ,ios::in);
            //String  TempName;
            if(fin.fail())
                MessageDlg("���ļ�ʧ�� !"  ,
                           mtInformation ,TMsgDlgButtons()<<mbOK ,0);
            else
            {
                while(!fin.eof()) //    fin >> TempName.c_str()
                {
                    string  TempName;
                    getline(fin ,TempName ,'\n');
                    int j;
                    for(j=0; j<StringGrid1->RowCount; j++)
                        if(StringGrid1->Cells[0][j]==TempName.c_str())  //   &&!TempName.IsEmpty()
                        {
                            //ShowMessage(StringGrid1->Cells[0][j]+"=="+TempName);
                            StringGrid1->Cells[1][j] = StringGrid1->Cells[1][j].ToInt()+1;
                            break;
                        }
                    //ShowMessage("j:"+String(j)+" ,StringGrid1->RowCount: "+String(StringGrid1->RowCount));
                    if(j==StringGrid1->RowCount&&String(TempName.c_str()).Trim()!="")  //!!!!
                    {
                        //ShowMessage(TempName);
                        StringGrid1->RowCount++;
                        StringGrid1->Cells[0][j] = TempName.c_str();
                        StringGrid1->Cells[1][j] = "1";
                    }
                }
                fin.close();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExportFilePopupClick(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {
        TStringList *StringList = new TStringList;
        for(int i=0; i<StringGrid1->RowCount; i++)
        {
            String  Temp;
            for(int j=0; j<StringGrid1->ColCount; j++)
                Temp += StringGrid1->Cells[j][i]+"  ------  ";

            StringList->Add(Temp);
        }
        StringList->SaveToFile(SaveDialog1->FileName);
        delete  StringList;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBoxCheckClick(TObject *Sender)
{
    ShowNameForm->LabelShow->Caption = ListBoxCheck->Items->Strings[ListBoxCheck->ItemIndex ];
    ShowNameForm->LabelShow->Left = (Screen->Width-ShowNameForm->LabelShow->Width)/2;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IsLoadSkinMenuClick(TObject *Sender)
{
    /*
    IsLoadSkinMenu->Checked = !IsLoadSkinMenu->Checked;
    if(IsLoadSkinMenu->Checked)
        SkinPPObj.LoadSkin("Skin++\\PixOS.ssk",false);
    else
        SkinPPObj.RemoveSkin();       */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetSkinMenuClick(TObject *Sender)
{
    //SkinPPObj.Colorize(0,0.5,true);
}
//---------------------------------------------------------------------------

