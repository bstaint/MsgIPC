#include "pushserver.h"
#include <codecvt>

void PushServer::push(ULONG senderUin, ULONG groupUin, const wchar_t *nickname, const wchar_t *text)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    msgpack::sbuffer buffer;

    MessageProto t1 = {senderUin, groupUin, conv.to_bytes(nickname), conv.to_bytes(text)};
    msgpack::pack(buffer, t1);
    zmq::message_t message(buffer.data(), buffer.size());

    pub.send(message, zmq::send_flags::dontwait);
}
