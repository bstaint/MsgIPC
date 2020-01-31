#include "message.h"

using namespace boost::property_tree;

namespace msgipc {

Property MessageLoad(const String& text)
{
    std::istringstream iss;
    iss.str(text);

    Property item;
    json_parser::read_json(iss, item);

    return item;
}

String MessageDump(Message *message)
{
    Property item;
    std::stringstream is;

    item.put("errno", message->err());
    message->fill(item);
    write_json(is, item);

    return is.str();
}

}
