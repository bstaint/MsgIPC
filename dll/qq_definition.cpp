#include "qq_definition.h"

ULONG_PTR CheckVideoMsgPtr = NULL;
CheckVideoMsg_t CheckVideoMsg = NULL;
GetMsgTime_t GetMsgTime = NULL;
GetMsgAbstract_t GetMsgAbstract = NULL;
GetNickname_t GetNickname = NULL;
GetSelfUin_t GetSelfUin = NULL;

void InitQQPtr()
{
    HMODULE hModule = GetModuleHandleA("KernelUtil");

    GetMsgTime = (GetMsgTime_t)GetProcAddress(hModule, GetMsgTime_Symbol);
    GetMsgAbstract = (GetMsgAbstract_t)GetProcAddress(hModule, GetMsgAbstract_Symbol);
    GetNickname = (GetNickname_t)GetProcAddress(hModule, GetNickname_Symbol);
    GetSelfUin = (GetSelfUin_t)GetProcAddress(hModule, GetSelfUin_Symbol);

    CheckVideoMsgPtr = (ULONG_PTR)GetProcAddress(hModule, CheckVideoMsg_Symbol);
    CheckVideoMsg = (CheckVideoMsg_t)CheckVideoMsgPtr;
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
