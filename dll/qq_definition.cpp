#include "qq_definition.h"

ULONG_PTR CheckVideoMsgPtr = NULL;
CheckVideoMsg_t CheckVideoMsg = nullptr;
GetMsgTime_t GetMsgTime = nullptr;
GetMsgAbstract_t GetMsgAbstract = nullptr;
GetNickname_t GetNickname = nullptr;
GetSelfUin_t GetSelfUin = nullptr;

bool InitQQPtr()
{
    HMODULE hModule = GetModuleHandleA("KernelUtil");

    GetMsgTime = (GetMsgTime_t)GetProcAddress(hModule, GetMsgTime_Symbol);
    GetMsgAbstract = (GetMsgAbstract_t)GetProcAddress(hModule, GetMsgAbstract_Symbol);
    GetNickname = (GetNickname_t)GetProcAddress(hModule, GetNickname_Symbol);
    GetSelfUin = (GetSelfUin_t)GetProcAddress(hModule, GetSelfUin_Symbol);

    CheckVideoMsgPtr = (ULONG_PTR)GetProcAddress(hModule, CheckVideoMsg_Symbol);
    CheckVideoMsg = (CheckVideoMsg_t)CheckVideoMsgPtr;

    if(GetMsgTime &&  CheckVideoMsg && GetMsgAbstract &&  GetNickname)
        return true;

    spdlog::error("InitQQPtr failed!");
    spdlog::info("GetMsgTime: {0:x}, CheckVideoMsg: {1:x}, GetMsgAbstract: {2:x}, GetNickname: {3:x}",
                 (ULONG_PTR)GetMsgTime,
                 (ULONG_PTR)CheckVideoMsg,
                 (ULONG_PTR)GetMsgAbstract,
                 (ULONG_PTR)GetNickname);
    return false;
}
