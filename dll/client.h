#ifndef CLIENT_H
#define CLIENT_H

#include "precompiled.h"

typedef websocketpp::client<websocketpp::config::asio_client> asio_client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

//typedef void (*MessageCallback)(const std::string& text);

typedef  std::function<void(const std::string&)> MessageCallback;

namespace msgipc
{

class Client
{
    std::string connect_str_;
    asio_client client_;
    asio_client::connection_ptr connected_;
    MessageCallback callback_;
public:
    Client(const std::string &connect_str);
    void connect();
    void retry_connect(uint32_t timeout=3000);
    bool is_connected()
    {
        return connected_ != nullptr && connected_->get_state() == websocketpp::session::state::open;
    }
    void send(const std::string& text)
    {
        client_.send(connected_, text, websocketpp::frame::opcode::text);
    }
    void close();

    void setCallback(MessageCallback cb)
    {
        callback_ = cb;
    }

    MessageCallback callback() const
    {
        return callback_;
    }

};

extern Client kClient;

}
#endif // CLIENT_H
