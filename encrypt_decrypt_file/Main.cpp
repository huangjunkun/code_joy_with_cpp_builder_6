//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Base64.h"
#include "About.h"

const   String  MyTitle = "Hello ,World ! FileEnDecrypt for only !";
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    InStream = NULL;
    OutStream = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    time_t  t;
    srand((unsigned int)time(&t));

    CheckBoxKey->Checked = NeedKey = true;
    btnOutFile->Enabled = false;
    StatusBar1->Panels[0][0]->Text = "---��ӭʹ��,лл   E-mail:only.hjky@yahoo.com.cn ";
    StatusBar1->Hint = " ---˫�� for About... ";
    this->Caption = "�����ļ����ܽ�����--written by only ";
    //DirectoryListBox1->Visible = false;
}
//---------------------------------------------------------------------------
void    TMainForm::DeleteFileStream()
{
    if(InStream != NULL)
        delete  InStream;
    if(OutStream != NULL)
        delete  OutStream;
    InStream = NULL;
    OutStream = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnInFileClick(TObject *Sender)
{
    ProgressBar1->Position  = 0;
    OpenDialog1->Filter = " All Files(*.*)|*.*";
    OpenDialog1->Title = "�����ļ�";
    if(OpenDialog1->Execute())
    {
        cbInFile->Items->Add(OpenDialog1->FileName);
        //cbInFile->Text = OpenDialog1->FileName;
        cbInFile->ItemIndex = cbInFile->Items->Count-1;
        cbInFile->Hint = cbInFile->Text;
        String  dir = OpenDialog1->FileName;
        int index;
        for(index=cbInFile->Text.Length(); index>0; index--)
        {
            if(cbInFile->Text[index]=='\\')
                break;
        }
        index--;
        dir.SetLength(index);
        //ShowMessage(dir);
        DirectoryListBox1->Directory = dir;
        DirectoryListBox1Change(Sender);
        btnOutFile->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnOutFileClick(TObject *Sender)
{
    DirectoryListBox1->Visible = !DirectoryListBox1->Visible;
}
//---------------------------------------------------------------------------

bool    TMainForm::EncryptFile(String   Key,bool NeedKey)
{
    InStream = new TFileStream(cbInFile->Text ,fmOpenRead);
    OutStream = new TFileStream(eOutFile->Text ,fmCreate);
    try
    {
        OutStream->Position = 0;    ///!!!!!
        OutStream->Write(MyTitle.c_str() ,MyTitle.Length());
        if(NeedKey==false)
            OutStream->Write(Key.c_str() ,Key.Length()); // KEYLEN
        //ShowMessage(String(Key.Length()) + Key);
        InStream->Position = 0;
        ProgressBar1->Position = 0;

        int     MAXFILE = (6 << 20);
        if(InStream->Size > MAXFILE)
        {
            //ShowMessage(String(InStream->Size)+" > "+String(MAXFILE));
            ProgressBar1->Max = MAXFILE + 1000;
            TMemoryStream   *TempStream = new TMemoryStream();
            TempStream->LoadFromStream(InStream);
            TempStream->SetSize(MAXFILE);
            //ShowMessage(String(TempStream->Size));
            TempStream->Position = 0;
            EncodeStream(TempStream ,OutStream ,Key); //�����ļ�

            InStream->Position = MAXFILE;
            OutStream->CopyFrom(InStream ,InStream->Size-MAXFILE);
            //OutStream->Write(InStream ,InStream->Size-MAXFILE);//!!!!! NONO ???
            //InStream->Read(OutStream ,InStream->Size-MAXFILE); //  !!!!! NONO ???

            ProgressBar1->Position += 1000;
            delete TempStream;
            /*
                      EncodeStream(InStream ,OutStream); //�����ļ�
                      OutStream->Write(InStream ,InStream->Size);  */
        }
        else
        {
            ProgressBar1->Max = InStream->Size;
            EncodeStream(InStream ,OutStream,Key); //�����ļ�
            //OutStream->Write(InStream ,InStream->Size);  //NONONO !!!
        }
        //
        DeleteFileStream();
        //delete  InStream;
        //delete  OutStream;
        return true;
    }
    catch(...)
    {
        DeleteFileStream();
        //delete  InStream;
        //delete  OutStream;
        return  false;
    }
}
//---------------------------------------------------------------------------

bool    TMainForm::DncryptFile(String   Key,bool NeedKey)
{
    InStream = new TFileStream(cbInFile->Text ,fmOpenRead);
    OutStream = new TFileStream(eOutFile->Text ,fmCreate);
    try
    {
        String      Str;
        Str.SetLength(MyTitle.Length());
        InStream->Position = 0;
        InStream->Read(Str.c_str() ,MyTitle.Length());  //&Str[1]
        if(MyTitle!=Str)
        {
            ShowMessage("�뵼����ȷ�ļ����ļ� ��");
            DeleteFileStream();
            //delete  InStream;
            //delete  OutStream;
            return false;
        }
        if(NeedKey==false)  // or Key==""
        {
            if(InStream->Size>(KEYLEN+MyTitle.Length()))
            {
                Str.SetLength(KEYLEN);
                InStream->Read(Str.c_str() ,Str.Length());  //&Str[1]
                Key = Str;
                //ShowMessage(String(Key.Length()) + Key);
            }
            else
            {
                ShowMessage("�뵼����ȷ�ļ����ļ� ,��Կ�ļ� ��");
                DeleteFileStream();
                //delete  InStream;
                //delete  OutStream;
                return false;
            }
        } /*  */
        OutStream->Position = 0;
        //ShowMessage(String(InStream->Size));
        ProgressBar1->Position  = 0;
        int     MAXFILE = (8 << 20)+MyTitle.Length() + ((!NeedKey) ? KEYLEN : 0);  //
        if(InStream->Size > MAXFILE)
        {
            //ShowMessage(String(InStream->Size)+" > "+String(MAXFILE));
            ProgressBar1->Max = MAXFILE+1000;
            TMemoryStream   *TempStream = new TMemoryStream();
            TempStream->LoadFromStream(InStream);
            TempStream->SetSize(MAXFILE);
            TempStream->Position = MyTitle.Length()+((!NeedKey) ? KEYLEN : 0); //0
            DecodeStream(TempStream ,OutStream ,Key); ////�����ļ�������

            InStream->Position = MAXFILE;  //
            delete TempStream;
            OutStream->CopyFrom(InStream ,InStream->Size-MAXFILE);
            ProgressBar1->Position  += 1000;
            //OutStream->Write(InStream ,InStream->Size-MAXFILE);//!!!!! NONO ???
            //InStream->Read(OutStream ,InStream->Size-MAXFILE); //  !!!!! NONO ???
        }
        else
        {
            ProgressBar1->Max = InStream->Size;
            DecodeStream(InStream ,OutStream,Key);//�����ļ�������
            //OutStream->Write(InStream ,InStream->Size); //NONONO !!!!
        }
        DeleteFileStream();
        //delete  InStream;
        //delete  OutStream;
        return true;
    }
    catch(String& e)
    {
        DeleteFileStream();
        //delete  InStream;
        //delete  OutStream;
        //ShowMessage(e);
        return  false;
    }
    catch(...)
    {
        return  false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnEncryptClick(TObject *Sender)
{
    if(cbInFile->Text==""||eOutFile->Text =="")
    {
        ShowMessage("�������ú� �������ļ�·�� ��\n �����ļ�·�� ��");
        return;
    }
    bool    Encrypt = false;
    String  Key = MakeRandomKey();
    if(NeedKey)
    {
        SaveDialog1->Title = "������Կ�ļ�(*.ikey)";
        SaveDialog1->Filter = "��Կ�ļ� ��*.ikey��|*.ikey";
        SaveDialog1->DefaultExt = ".ikey";
        SaveDialog1->FileName = "";
        if(SaveDialog1->Execute())
        {
            TMemoryStream   *OutKey = new TMemoryStream();
            OutKey->Position = 0;
            OutKey->Write(Key.c_str() ,Key.Length());   // &Key[1]
            OutKey->SaveToFile(SaveDialog1->FileName);
            delete  OutKey;
            ShowMessage("��Կ :"+SaveDialog1->FileName+" \n �����Ʊ��� ��");
            /*  */
            Encrypt = EncryptFile(Key);
        }
    }
    else
        Encrypt = EncryptFile(Key ,false);
    if(Encrypt)
    {
        MessageDlg("�ļ�������� �������ɹ� !" ,mtInformation ,TMsgDlgButtons()<<mbOK ,0);
        StatusBar1->Panels[0][0]->Text = "���ܳɹ�:" +eOutFile->Text;
        StatusBar1->Hint =  "���ܳɹ�:" +eOutFile->Text;
    }
    else
        StatusBar1->Panels[0][0]->Text = "  ����ʧ��: error !";
    cbInFile->ItemIndex = -1;
    eOutFile->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnhDecryptClick(TObject *Sender)
{
    if(cbInFile->Text==""||eOutFile->Text =="")
    {
        ShowMessage("�������ú� �������ļ�·�� ��\n �����ļ�·�� ��");
        return;
    }
    bool    Dncrypt = false;
    if(NeedKey)
    {
        OpenDialog1->Title = "������Կ�ļ���*.ikey��";
        OpenDialog1->Filter = "��Կ�ļ���*.ikey��|*.ikey";
        OpenDialog1->FileName = "";
        if(OpenDialog1->Execute())
        {
            String  Key;
            TMemoryStream   *OutKey = new TMemoryStream();
            OutKey->LoadFromFile(OpenDialog1->FileName);
            OutKey->Position = 0;
            Key.SetLength(KEYLEN);  //
            OutKey->Read(Key.c_str() ,Key.Length());  // Key.Length() ???????
            delete  OutKey;

            Dncrypt = DncryptFile(Key);
        }
    }
    else
        Dncrypt = DncryptFile("" ,false); //Key==""
    if(Dncrypt)
    {
        MessageDlg("�ļ�������� �������ɹ� !" ,mtInformation ,TMsgDlgButtons()<<mbOK ,0);
        StatusBar1->Panels[0][0]->Text = "���ܳɹ�:" +eOutFile->Text;
        StatusBar1->Hint = "���ܳɹ�:" +eOutFile->Text;
    }
    else
    {
        DeleteFile(eOutFile->Text);
        StatusBar1->Panels[0][0]->Text = "����ʧ��: error ! ";
    }

    OpenDialog1->Filter = "";
    cbInFile->ItemIndex = -1;
    eOutFile->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DirectoryListBox1Change(TObject *Sender)
{
    if(cbInFile->Text=="")
        return;
    int index;
    for(index=cbInFile->Text.Length(); index>0; index--)
    {
        if(cbInFile->Text[index]=='\\')
            break;
    }
    index++;
    //ShowMessage(cbInFile->Text.SubString(index ,cbInFile->Text.Length()-index+1));
    String  filename = "New" + cbInFile->Text.SubString(index ,cbInFile->Text.Length()-index+1);
    eOutFile->Text = DirectoryListBox1->Directory + "\\" + filename;
    eOutFile->Hint = eOutFile->Text;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    StatusBar1->Panels[0][1]->Text = "  " + Now();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StatusBar1DblClick(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBoxKeyClick(TObject *Sender)
{
    NeedKey = CheckBoxKey->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnCancelClick(TObject *Sender)
{
    DeleteFileStream();
}
//---------------------------------------------------------------------------

