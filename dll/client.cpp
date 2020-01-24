#include "client.h"
#include "precompiled.h"

using websocketpp::lib::bind;

void OnClose(asio_client* c, websocketpp::connection_hdl hdl) {
    Sleep(10000);
    msgipc::kClient.retry_connect(10000);
}

void OnMessage(asio_client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    if (msgipc::kClient.callback())
        msgipc::kClient.callback()(msg->get_payload());
}

namespace msgipc
{

Client kClient("ws://192.168.10.1:5678");

Client::Client(const String& connect_str) :
    connected_(nullptr),
    callback_(nullptr),
    connect_str_(connect_str)
{
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.init_asio();
    client_.set_message_handler(bind(&OnMessage,&client_, std::placeholders::_1, std::placeholders::_2));
    client_.set_close_handler(bind(&OnClose, &client_, std::placeholders::_1));
}

void Client::connect()
{
    websocketpp::lib::error_code ec;
    connected_ = client_.get_connection(connect_str_.c_str(), ec);
    if (ec) {
        spdlog::error("could not create connection because: {}", ec.message());
        return;
    }

    client_.connect(connected_);
}

void Client::retry_connect(uint32_t timeout)
{
    spdlog::info("connecting...");
    connect();

    while(!is_connected())
    {
        client_.run_one();
        switch (connected_->get_state()) {
        case websocketpp::session::state::connecting:
            Sleep(1000);
            break;
        case websocketpp::session::state::closed:
        case websocketpp::session::state::closing:
            spdlog::info("retry connecting...");
            connect();
            Sleep(timeout);
            break;
        default:
            break;
        }
    }

    spdlog::info("connect success");
    client_.run();
}

void Client::close()
{
    if(is_connected())
    {
        websocketpp::close::status::value val{};
        connected_->close(val, "");
        spdlog::info("connected close.");
    }
}

}
