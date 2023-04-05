//
// Created by luo on 2023/4/5.
//

#ifndef KINO_MESSAGE_HANDLER_H
#define KINO_MESSAGE_HANDLER_H

#include "message.h"

class Actor;
typedef Actor* ActorAddress;
class MessageHandler {
public:
    virtual ~MessageHandler() {}

    virtual void HandleMessage(Message &&msg, ActorAddress from) = 0;

    virtual MessageType GetMsgType() const = 0;
};

template<class Actor>
class MfMessageHandler : public  MessageHandler {
public:
    MfMessageHandler(void (Actor::* mf)(Message, ActorAddress), Actor *a, MessageType msgType) : function_(mf), actor_(a), msgType_(msgType) {
    }

    MessageType GetMsgType() const override{
        return msgType_;
    }

    virtual void HandleMessage(Message &&msg, ActorAddress from) {
        (actor_->*function_)(std::move(msg), from);
    }

    bool IsFunction(void (Actor::* mf)(Message, ActorAddress)) {
        return mf == function_;
    }

private:
    MessageType msgType_;
    Actor *actor_;
    void (Actor::* function_)(Message, ActorAddress);
};

#endif //KINO_MESSAGE_HANDLER_H
