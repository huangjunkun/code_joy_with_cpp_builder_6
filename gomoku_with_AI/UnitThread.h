//---------------------------------------------------------------------------

#ifndef UnitThreadH
#define UnitThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TFlyThread : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TFlyThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
class TFollowThread : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TFollowThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
