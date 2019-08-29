#ifndef PUSHSERVER_H
#define PUSHSERVER_H

#include "zmq.hpp"
#include "msgpack.hpp"
class PushServer
{
    zmq::socket_t pub;

public:
    PushServer(zmq::context_t *ctx) : pub(*ctx, zmq::socket_type::pub)
    {
        pub.setsockopt(ZMQ_LINGER, 1);
        pub.bind("tcp://*:5555");
    }

    void push(ULONG senderUin, ULONG groupUin, const wchar_t *nickname, const wchar_t *text);

    ~PushServer() { pub.close(); }
};

#endif // PUSHSERVER_H
