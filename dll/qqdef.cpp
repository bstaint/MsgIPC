#include "qqdef.h"
#include "spdlog/spdlog.h"

ULONG_PTR MsgHookTarget = NULL;
CheckVideoMsg_t CheckVideoMsg = NULL;
GetMsgTime_t GetMsgTime = NULL;
GetMsgAbstract_t GetMsgAbstract = NULL;
GetNickname_t GetNickname = NULL;

void InitQQPtr()
{
    HMODULE hModule = GetModuleHandleA("KernelUtil");

    MsgHookTarget = (ULONG_PTR)GetProcAddress(hModule, CheckVideoMsg_Symbol);
    ULONG_PTR GetMsgTimeAddress = (ULONG_PTR)GetProcAddress(hModule, GetMsgTime_Symbol);
    ULONG_PTR GetMsgAbstractAddress = (ULONG_PTR)GetProcAddress(hModule, GetMsgAbstract_Symbol);
    ULONG_PTR GetNicknameAddress = (ULONG_PTR)GetProcAddress(hModule, GetNickname_Symbol);

//    ULONG_PTR GetMsgAbstractAddress = (ULONG_PTR)GetProcAddress(hModule, GetMsgDumpString_Symbol);
    GetMsgTime = (GetMsgTime_t)GetMsgTimeAddress;
    GetMsgAbstract = (GetMsgAbstract_t)GetMsgAbstractAddress;
    GetNickname = (GetNickname_t)GetNicknameAddress;
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
