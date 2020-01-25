#ifndef CLIENT_H
#define CLIENT_H

#include "precompiled.h"

namespace msgipc
{

typedef websocketpp::client<websocketpp::config::asio_client> asio_client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

typedef  std::function<void(const String&)> MessageCallback;

class Client
{
    String connect_str_;
    asio_client client_;
    asio_client::connection_ptr connected_;
    MessageCallback callback_;
    uint32_t timeout_;

public:
    Client(const String &connect_str);
    void connect();
    bool is_connected()
    {
        return connected_ != nullptr && connected_->get_state() == websocketpp::session::state::open;
    }
    void send(const String& text)
    {
        client_.send(connected_, text, websocketpp::frame::opcode::text);
    }
    void close();

    void setTimeout(const uint32_t &timeout) { timeout_ = timeout; }
    void setCallback(MessageCallback cb) { callback_ = cb; }
    void setConnectStr(const String &connect_str) { connect_str_ = connect_str; }

    uint32_t timeout() const { return timeout_; }
    MessageCallback callback() const { return callback_; }
};

extern Client kClient;

}
#endif // CLIENT_H
