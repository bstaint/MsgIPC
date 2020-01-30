#include "precompiled.h"
#include "qq_definition.h"
#include "message.h"
#include "websocket_client.h"

using namespace msgipc;

std::shared_ptr<spdlog::sinks::msvc_sink_mt> sink(nullptr);
std::shared_ptr<spdlog::logger> logger(nullptr);

moodycamel::BlockingConcurrentQueue<Message *> kQueue;

//      如果groupUin = 0 则为私聊
void __cdecl MyCheckVideoMsg(int a, unsigned long senderUin, /*unsigned long unknown, */unsigned long groupUin, unsigned long * msg)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

    wchar_t * nickname = NULL;
    wchar_t * text = NULL;
//        获取消息时间
//    __int64 timestamp = GetMsgTime(msg);
    GetNickname(&nickname, senderUin);
    GetMsgAbstract(&text, msg);

    spdlog::info("senderUin: {0:x}, groupUin: {1:x}", senderUin, groupUin);
    kQueue.enqueue(new MessageChat(senderUin,
                                   groupUin,
                                   conv.to_bytes(nickname),
                                   conv.to_bytes(text)));

    CheckVideoMsg(a, senderUin/*, unknown*/, groupUin, msg);
}

void OnMessageCallback(const String& text)
{
    spdlog::info(text);

    kQueue.enqueue(new Message(PSELFUIN, std::to_string(GetSelfUin())));
//    Property item;
//    try {
//        item = PacketLoad(text);
//        if(item.get<int>("type") != PSEND)
//        {
//            spdlog::error("invaild type");
//            return;
//        }

//        switch (item.get<int>("errno")) {
//        case PTEST:
//            std::cout << "This is a test command\n";
//            break;
//        default:
//            break;
//        }

//    } catch (...) {
//        spdlog::error("unknown message");
//    }
}

DWORD WINAPI WebSocketProc(HMODULE hModule)
{
    kClient.setConnectStr("ws://192.168.10.1:5678");
    kClient.setTimeout(10000);
    kClient.setCallback(OnMessageCallback);
    kClient.connect();
    return 0;
}

DWORD WINAPI RecvMsgProc(HMODULE hModule)
{
    Message* message;
    while(1)
    {
        kQueue.wait_dequeue(message);
        String s = MessageDump( message);
        if(kClient.is_connected())
            kClient.send(s);

        delete message;
    }
    return 0;
}

BOOL SetHook(LPVOID pTarget, LPVOID pDest, LPVOID pOld)
{
    MH_STATUS ret = MH_OK;

    spdlog::info("SetHook begin, pTarget: {}", pTarget);
    ret = MH_CreateHook(pTarget, pDest, reinterpret_cast<LPVOID*>(pOld));
    if (ret != MH_OK)
    {
        spdlog::error("MH_CreateHook failed, MH_STATUS: {}", MH_StatusToString(ret));
        return FALSE;
    }

    if ((ret = MH_EnableHook((LPVOID)pTarget)) != MH_OK)
    {
        spdlog::error("MH_CreateHook failed, MH_STATUS: {}", MH_StatusToString(ret));
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
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls((HINSTANCE)hInst);
        // 设置日志默认输出
        sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        logger = std::make_shared<spdlog::logger>("MsgIPC", sink);
        spdlog::set_default_logger(logger);

        // 初始化minhook并hook
        MH_Initialize();
        if(!InitQQPtr()) return FALSE;

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WebSocketProc, NULL, 0, NULL);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsgProc, NULL, 0, NULL);

        if(SetHook((LPVOID)CheckVideoMsgPtr, &MyCheckVideoMsg, &CheckVideoMsg))
            spdlog::info("SetHook OK.");
    }
        break;
    case DLL_PROCESS_DETACH:
    {
//        TODO: DLL Detach Crash.
        if(UnHook((LPVOID)CheckVideoMsgPtr))
            spdlog::info("UnHook OK.");

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
