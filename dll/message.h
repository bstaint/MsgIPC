#ifndef MESSAGE_H
#define MESSAGE_H

#include "precompiled.h"

namespace msgipc {

enum err {
    PUNKNOWN = -1,
    PERROR = 0,
    POK = 1,
    PSELFUIN,
    PCHAT,
    PTEST
};

class Message
{
protected:
    uint8_t errno_;
    String message_;

public:
    Message() :  errno_(PUNKNOWN),  message_("") {}
    Message(const uint8_t err, const String& message) :
        errno_(err), message_(message) {}

    uint8_t err() const { return errno_; }
    virtual void fill(Property& item) { item.put("message", message_); }

    virtual ~Message() {}
};

class MessageChat : public Message
{
    uint32_t sender_;
    uint32_t group_;
    String nickname_;

public:
    MessageChat() : Message(), sender_(0), group_(0), nickname_("") {}
    MessageChat(uint32_t sender, uint32_t group,
                const String& nickname, const String& message) :
        Message(PCHAT, message),
        sender_(sender), group_(group), nickname_(nickname) {}

    void fill(Property& item)
    {
        Property subitem;
        subitem.put("sender", sender_);
        subitem.put("group", group_);
        subitem.put("nickname", nickname_);
        subitem.put("text", message_);

        item.push_back(std::make_pair("message", subitem));
    }
};

Property MessageLoad(const String &text);
String MessageDump(Message *message);

}

#endif // MESSAGE_H
