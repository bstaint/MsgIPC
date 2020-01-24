#include "qq_definition.h"

ULONG_PTR MsgHookTarget = NULL;
CheckVideoMsg_t CheckVideoMsg = NULL;
GetMsgTime_t GetMsgTime = NULL;
GetMsgAbstract_t GetMsgAbstract = NULL;
GetNickname_t GetNickname = NULL;
GetSelfUin_t GetSelfUin = NULL;

void InitQQPtr()
{
    HMODULE hModule = GetModuleHandleA("KernelUtil");

    MsgHookTarget = (ULONG_PTR)GetProcAddress(hModule, CheckVideoMsg_Symbol);
    ULONG_PTR GetMsgTimePtr = (ULONG_PTR)GetProcAddress(hModule, GetMsgTime_Symbol);
    ULONG_PTR GetMsgAbstractPtr = (ULONG_PTR)GetProcAddress(hModule, GetMsgAbstract_Symbol);
    ULONG_PTR GetNicknamePtr = (ULONG_PTR)GetProcAddress(hModule, GetNickname_Symbol);
    ULONG_PTR GetSelfUinPtr = (ULONG_PTR)GetProcAddress(hModule, GetSelfUin_Symbol);

//    ULONG_PTR GetMsgAbstractAddress = (ULONG_PTR)GetProcAddress(hModule, GetMsgDumpString_Symbol);
    GetMsgTime = (GetMsgTime_t)GetMsgTimePtr;
    GetMsgAbstract = (GetMsgAbstract_t)GetMsgAbstractPtr;
    GetNickname = (GetNickname_t)GetNicknamePtr;
    GetSelfUin = (GetSelfUin_t)GetSelfUinPtr;

    CheckVideoMsg = (CheckVideoMsg_t)MsgHookTarget;
}

bool CheckPtrVaild()
{
    spdlog::info("GetMsgTime: {0:x}, CheckVideoMsg: {1:x}, GetMsgAbstract: {2:x}, GetNickname: {3:x}",
                 (ULONG_PTR)GetMsgTime,
                 (ULONG_PTR)CheckVideoMsg,
                 (ULONG_PTR)GetMsgAbstract,
                 (ULONG_PTR)GetNickname);
    if(GetMsgTime &&  CheckVideoMsg && GetMsgAbstract &&  GetNickname)
        return true;

    return false;
}
