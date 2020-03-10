#include "websocket_client.h"
#include "precompiled.h"

using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

namespace msgipc
{

Client kClient;

void OnClose(asio_client*, websocketpp::connection_hdl) {
    Sleep(kClient.timeout());

    spdlog::info("retry connecting...");
    kClient.connect();
}

void OnMessage(asio_client*, websocketpp::connection_hdl, message_ptr msg) {
    if (kClient.callback())
        kClient.callback()(msg->get_payload());
}

Client::Client(const String& connect_str) :
    connected_(nullptr),
    callback_(nullptr),
    timeout_(3000),
    connect_str_(connect_str)
{
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.init_asio();
    client_.set_message_handler(bind(&OnMessage, &client_, ::_1, ::_2));
    client_.set_fail_handler(bind(&OnClose, &client_, ::_1));
    client_.set_close_handler(bind(&OnClose, &client_, ::_1));
}

void Client::connect()
{
    spdlog::info("connecting...");
    websocketpp::lib::error_code ec;
    connected_ = client_.get_connection(connect_str_.c_str(), ec);
    if (ec) {
        spdlog::error("could not create connection because: {}", ec.message());
        return;
    }

    client_.connect(connected_);
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
