#include "message.h"

namespace msgipc {

Property MessageLoad(const String& text)
{
    std::istringstream iss;
    iss.str(text);

    Property item;
    boost::property_tree::json_parser::read_json(iss, item);

    return item;
}

String MessageDump(Message *message)
{
    std::stringstream is;

    Property item;

    item.put("errno", message->err());
    message->fill(item);

    boost::property_tree::write_json(is, item);
    return is.str();
}

}
