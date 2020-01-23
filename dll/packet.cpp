#include "packet.h"

namespace msgipc {

boost::property_tree::ptree PacketLoad(const std::string& text)
{
    std::istringstream iss;
    iss.str(text);

    boost::property_tree::ptree item;
    boost::property_tree::json_parser::read_json(iss, item);

    return item;
}

std::string PacketDump(uint8_t type, int8_t err, Message *message)
{
    std::stringstream is;
    boost::property_tree::ptree item;
    item.put("type", type);
    item.put("errno", err);
    message->fill(item);

    boost::property_tree::write_json(is, item);
    return is.str();
}

}
