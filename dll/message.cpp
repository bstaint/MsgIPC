#include "message.h"

namespace msgipc {

Property PacketLoad(const String& text)
{
    std::istringstream iss;
    iss.str(text);

    Property item;
    boost::property_tree::json_parser::read_json(iss, item);

    return item;
}

String PacketDump(uint8_t type, int8_t err, Message *message)
{
    std::stringstream is;
    Property item;
    item.put("type", type);
    item.put("errno", err);
    message->fill(item);

    boost::property_tree::write_json(is, item);
    return is.str();
}

}
