#include "pushserver.h"
#include <Windows.h>
#include <vector>
#include <string>

#include "MinHook.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/msvc_sink.h"
#include "qqdef.h"

PushServer *server = NULL;

//      如果groupUin = 0 则为私聊
void __cdecl MyCheckVideoMsg(int a, unsigned long senderUin, unsigned long groupUin, unsigned long * msg)
{
    if(!CheckPtrVaild()) return;

    wchar_t * nickname = NULL;
    wchar_t * text = NULL;
//        获取消息时间
//    __int64 timestamp = GetMsgTime(msg);
    GetNickname(&nickname, senderUin);
    GetMsgAbstract(&text, msg);

//        spdlog::info("timestamp = {0} groupUin = {1}, buddyUin = {2}", timestamp, groupUin, buddyUin);
    server->push(senderUin, groupUin, nickname, text);

    CheckVideoMsg(a, senderUin, groupUin, msg);
}


BOOL SetHook(LPVOID pTarget, LPVOID pDest, LPVOID pOld)
{
    MH_STATUS ret = MH_OK;

    ret = MH_CreateHook(pTarget, pDest, reinterpret_cast<LPVOID*>(pOld));
    if (ret != MH_OK)
    {
        spdlog::error("MH_CreateHook failed, MH_STATUS = {0:d}", ret);
        return FALSE;
    }

    if ((ret = MH_EnableHook((LPVOID)pTarget)) != MH_OK)
    {
        spdlog::error("MH_CreateHook failed, MH_STATUS = {0:d}", ret);
        return FALSE;
    }

    return TRUE;
}

BOOL UnHook(LPVOID pTarget)
{
    if (MH_DisableHook(pTarget) != MH_OK)
        return FALSE;

    if(MH_Uninitialize() != MH_OK)
        return FALSE;

    return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID lpReserved)
{
//    https://github.com/zeromq/libzmq/issues/1144
//    load DLL image
//    a.context_t::context_t
//    DllMain(LOAD)
//    DllMain(UNLOAD)
//    a.context_t::~context_t  <= Assertion failed: Successful WSASTARTUP not yet ...
//    unload DLL image
//    不要把context_t声明成全局变量，不然DLL_PROCESS_DETACH时会假死
    zmq::context_t *ctx = NULL;

    std::shared_ptr<spdlog::sinks::msvc_sink_mt> sink(nullptr);
    std::shared_ptr<spdlog::logger> logger(nullptr);

    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 设置日志默认输出
        sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        logger = std::make_shared<spdlog::logger>("MsgIPC", sink);
        spdlog::set_default_logger(logger);

        // 启动Push服务器
        ctx = new zmq::context_t(1);
        server = new PushServer(ctx);

        // 初始化minhook并挂钩
        MH_Initialize();
        InitQQPtr();

        if(SetHook((LPVOID)MsgHookTarget, &MyCheckVideoMsg, &CheckVideoMsg))
            spdlog::info("SetHook OK!");
    }
        break;
    case DLL_PROCESS_DETACH:
    {
        if(UnHook((LPVOID)MsgHookTarget))
            spdlog::info("UnHook OK!");

        if(server) delete server;
        if(ctx) delete ctx;

        MH_Uninitialize();
    }
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
