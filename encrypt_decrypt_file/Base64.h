//---------------------------------------------------------------------------

#ifndef Base64H
#define Base64H
//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#include <vector>    //for vector
using namespace std;

//---------------------------------------------------------------------------
typedef struct MyChar
{
    char    ch;
    bool    used;
}   MyChar;

//---------------------------------------------------------------------------
void     EncodeStream(TStream* InStream ,TStream* OutStream ,String Key="");
byte     SearchBase64Table(const Byte& b);
void     DecodeStream(TStream* InStream ,TStream *OutStream ,String Key="");
String   Base64Encryption(const String& InputStr);
String   Base64Decryption(const String& InputStr);
String   MakeRandomKey();

#endif
