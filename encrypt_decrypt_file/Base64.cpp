//---------------------------------------------------------------------------


#pragma hdrstop

#include "Base64.h"
#include "Main.h"
//---------------------------------------------------------------------------
Byte    Base64Table[65] = {'A' ,'B' ,'C' ,'D' ,'E' ,'F' ,'G' ,'H' ,'I' ,'J' ,
                           'K' ,'L' ,'M' ,'N' ,'O' ,'P' ,'Q' ,'R' ,'S' ,'T' ,
                           'U' ,'V' ,'W' ,'X' ,'Y' ,'Z' ,'a' ,'b' ,'c' ,'d' ,
                           'e' ,'f' ,'g' ,'h' ,'i' ,'j' ,'k' ,'l' ,'m' ,'n' ,
                           'o' ,'p' ,'q' ,'r' ,'s' ,'t' ,'u' ,'v' ,'w' ,'x' ,
                           'y' ,'z' ,'0' ,'1' ,'2' ,'3' ,'4' ,'5' ,'6' ,'7' ,
                           '8' ,'9' ,'+' ,'-' ,'='
                          }; //'=' end 当作截止字符
//---------------------------------------------------------------------------
#pragma package(smart_init)

void     EncodeStream(TStream* InStream ,TStream* OutStream ,String Key)
{
    if(Key!="")
    {
        for(int i=0; i<Key.Length()&&i<64; i++)
        {
            Base64Table[i] = Key[i+1];
        }
    }
    int     Count ,iI ,iO;
    Byte    InBuf[45];
    char    OutBuf[63];
    Byte    Temp;
    fill(OutBuf ,OutBuf+62 ,NULL);
    do
    {
        Count = InStream->Read(InBuf ,sizeof(InBuf));
        if(Count==0)
            break;
        iI = 0;
        iO = 0;
        while(iI<Count-2)
        {
            //编码第1个字节
            Temp = (InBuf[iI] >> 2);
            OutBuf[iO] = char(Base64Table[Temp&0x3f]);
            //编码第2个字节
            Temp = (InBuf[iI] << 4) | (InBuf[iI+1] >> 4);
            OutBuf[iO+1] = char(Base64Table[Temp&0x3f]);
            //编码第3个字节
            Temp = (InBuf[iI+1] << 2) | (InBuf[iI+2] >> 6);
            OutBuf[iO+2] = char(Base64Table[Temp&0x3f]);
            //编码第4个字节
            Temp = (InBuf[iI+2] & 0x3f);
            OutBuf[iO+3] = char(Base64Table[Temp]);
            iI += 3;
            iO += 4;
        }
        if(iI<=Count-1)
        {
            //ShowMessage(String(InBuf[I]));
            Temp = (InBuf[iI] >> 2);
            //ShowMessage(String(Temp));
            OutBuf[iO] = char(Base64Table[Temp&0x3f]);
            if(iI==Count-1)
            {
                //一个奇数字节
                Temp = (InBuf[iI] << 4)& 0x30;
                OutBuf[iO+1] = char(Base64Table[Temp&0x3f]);
                OutBuf[iO+2] = '=';
            }
            else //I==Count-2
            {
                //两个奇数字节
                Temp = ((InBuf[iI] << 4)& 0x30) | ((InBuf[iI+1] >> 4)& 0x0f);
                OutBuf[iO+1] = char(Base64Table[Temp&0x3f]);
                Temp = (InBuf[iI+1] << 2) & 0x3c;
                OutBuf[iO+2] = char(Base64Table[Temp&0x3f]);
            }
            OutBuf[iO+3] = '=';
            iO += 4;
        }
        OutStream->Write(OutBuf ,iO);
        MainForm->ProgressBar1->Position += 45;
        Application->ProcessMessages();
    }
    while(!(Count < sizeof(InBuf)));
}
//---------------------------------------------------------------------------
/*
void     EncodeStream(TStream* InStream ,TStream* OutStream ,String Key)
{
    if(Key!="")
    {

    }
} */
//---------------------------------------------------------------------------
byte    SearchBase64Table(const Byte&   b)
{
    for(byte i=0; i<65; i++)
    {
        if(Base64Table[i]==b)
            return i; /*
        ShowMessage(String(i));
        ShowMessage(String(Base64Table[i]));
        ShowMessage(String(b));   */
    }
    return  byte(255);
}
//---------------------------------------------------------------------------
void     DecodeStream(TStream* InStream ,TStream* OutStream ,String Key)
{
    if(Key!="")
    {
        //ShowMessage(String(Key.Length()));
        for(int i=0; i<Key.Length()&&i<64; i++)
        {
            Base64Table[i] = Key[i+1];
        }
    }
    int     Count ,iI ,iO;  // ,c1 ,c2 ,c3
    Byte     c1 ,c2 ,c3;  //
    Byte    InBuf[88];
    Byte    OutBuf[66];
    Byte    Temp;
    do
    {
        Count = InStream->Read(InBuf ,sizeof(InBuf));
        if(Count==0)
            break;
        iI = 0;
        iO = 0;
        while(iI<Count)
        {
            //ShowMessage(String(Count));
            c1 = SearchBase64Table(InBuf[iI]);
            c2 = SearchBase64Table(InBuf[iI+1]);
            c3 = SearchBase64Table(InBuf[iI+2]);
            if(c1==byte(255)||c2==byte(255)||c3==byte(255))
            {
                /*
                  ShowMessage(String(c1));
                  ShowMessage(String(c2));
                  ShowMessage(String(c3)); */
                ShowMessage("   非法字符 ，解密终止 ！");
                String  errStr = "非法字符 ，解密终止！";
                OutStream->Write(errStr.c_str() ,errStr.Length());
                throw String("非法字符 ，解密终止！");  //return throw;//????
            }
            OutBuf[iO] = ((c1<<2)|(c2>>4));
            iO++;
            if(char(InBuf[iI+2]!='='))
            {
                OutBuf[iO] = ((c2<<4)|(c3>>2));
                iO++;
                if(char(InBuf[iI+3]!='='))
                {
                    OutBuf[iO] = ((c3<<6)|SearchBase64Table(InBuf[iI+3]));
                    iO++;
                }
            }
            iI += 4;
        }
        OutStream->Write(OutBuf ,iO);
        MainForm->ProgressBar1->Position += 88;
        Application->ProcessMessages();
    }
    while(!(Count < sizeof(InBuf)));

}
//---------------------------------------------------------------------------
String      Base64Encryption(const String& InputStr)
{
    String  result;
    TMemoryStream   *InStream = new TMemoryStream();
    TMemoryStream   *OutStream = new TMemoryStream();

    InStream->Write(InputStr.c_str() ,InputStr.Length());
    InStream->Position = 0;
    EncodeStream(InStream ,OutStream);
    OutStream->Position = 0;
    result.SetLength(OutStream->Size);
    OutStream->Read(&result[1] ,OutStream->Size);
    delete InStream;
    delete OutStream;
    return  result;
}
//---------------------------------------------------------------------------
String      Base64Decryption(const String& InputStr)
{
    String  result;
    TMemoryStream   *InStream = new TMemoryStream();
    TMemoryStream   *OutStream = new TMemoryStream();

    InStream->Write(InputStr.c_str() ,InputStr.Length()); //  &InputStr
    InStream->Position = 0;
    DecodeStream(InStream ,OutStream);
    OutStream->Position = 0;
    result.SetLength(OutStream->Size);
    OutStream->Read(&result[1] ,OutStream->Size);

    delete InStream;
    delete OutStream;
    return  result;
}
//---------------------------------------------------------------------------
String  MakeRandomKey()
{
    /*
      time_t  t;   //NONONONONO!!!!!!!!!11
      srand((unsigned int)time(&t));
      //法一 ，适用于文件存放 Key ！ String 存放 有Bug
      vector<MyChar>  mychar_vec(256);
      for(int i=0;i<256;i++)
      {
          mychar_vec[i].ch = (char)i;
          mychar_vec[i].used = false;
      }
      mychar_vec[int('=')].used = true;
      String  Key;
      Key.SetLength(KEYLEN);
      int     index = 1;
      while(index <=KEYLEN)
      {
          int     i = rand()%256;
          if(mychar_vec[i].used==false)
          {
              Key[index++] = mychar_vec[i].ch;
              mychar_vec[i].used = true;
          }
      }
      return Key;   */
    //法二 ，适用于文件 ，String存储 Key ！！！！
    String  Key;
    Key.SetLength(64);
    for(int i=0; i<64; i++)
    {
        Key[i+1] = Base64Table[i];
    }
    for(int i=1; i<=64; i++)
    {
        int r = (rand()%64)+1;
        Byte    temp = Key[i];
        Key[i] = Key[r];
        Key[r] = temp;
    }
    return Key;
}
//---------------------------------------------------------------------------

