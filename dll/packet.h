#ifndef PACKET_H
#define PACKET_H

#include "precompiled.h"

namespace msgipc {

typedef boost::property_tree::ptree Property;

enum type {
    PRECV,
    PSEND
};

enum err {
    PUNKNOWN = -2,
    PERROR = -1,
    POK = 0,
    PTEST,
    PAUTOREPLY
};

class Message
{
protected:
    std::string message_;
public:
    Message() : message_("") { }
    Message(const std::string& message) : message_(message) { }

    virtual void fill(Property& item)
    {
        item.put("message", message_);
    }

    virtual ~Message() {}
};

class MessageChat : public Message
{
    uint32_t sender_;
    uint32_t group_;
    std::string nickname_;

public:
    MessageChat() :
        Message(""),
        sender_(0),
        group_(0),
        nickname_("")
    {}

    MessageChat(uint32_t sender, uint32_t group, const std::string& nickname, 
                                                 const std::string& message) :
        Message(message),
        sender_(sender),
        group_(group),
        nickname_(nickname)
    {}

    virtual void fill(Property& item)
    {
        Property subitem;
        subitem.put("sender", sender_);
        subitem.put("group", group_);
        subitem.put("nickname", nickname_);
        subitem.put("text", message_);
        item.push_back(std::make_pair("message", subitem));
    }
};

Property PacketLoad(const std::string &text);
std::string PacketDump(uint8_t type,
                        int8_t err,
                        Message *message);

}

#endif // PACKET_H
