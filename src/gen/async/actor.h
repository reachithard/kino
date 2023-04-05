//
// Created by luo on 2023/4/5.
//

#ifndef KINO_ACTOR_H
#define KINO_ACTOR_H

#include <asio/any_io_executor.hpp>
#include <asio/defer.hpp>
#include <asio/post.hpp>
#include <asio/strand.hpp>
#include <asio/system_executor.hpp>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <typeinfo>
#include <vector>

using asio::any_io_executor;
using asio::defer;
using asio::post;
using asio::strand;
using asio::system_executor;

#include "message_handler.h"

class Actor {
public:
    virtual ~Actor() {}

    ActorAddress  Address() {
        return this;
    }

    friend void Send(Message &&msg, ActorAddress from, ActorAddress to)
    {
        // Execute the message handler in the context of the target's executor.
        post(to->executor_,
             [=, &msg]
             {
                 to->CallHandler(std::move(msg), from);
             });
    }

protected:
    Actor(any_io_executor e)
    : executor_(std::move(e))
    {
    }

    template <class Actor>
    void RegisterHandler(void (Actor::* mf)(Message, ActorAddress), MessageType msgType)
    {
        handlers_.push_back(
                std::make_shared<MfMessageHandler<Actor>>(
                mf, static_cast<Actor*>(this), msgType));
    }

    template <class Actor>
    void DeregisterHandler(void (Actor::* mf)(Message, ActorAddress), MessageType msgType)
    {
        for (auto iter = handlers_.begin(); iter != handlers_.end(); ++iter)
        {
            if ((*iter)->GetMsgType() == msgType)
            {
                auto mh = static_cast<MfMessageHandler<Actor>*>(iter->get());
                if (mh->IsFunction(mf))
                {
                    handlers_.erase(iter);
                    return;
                }
            }
        }
    }

private:
    void CallHandler(Message &&msg, ActorAddress from)
    {
        for (auto& h: handlers_)
        {
            if (h->GetMsgType() == msg.GetMsgType())
            {
                auto mh = static_cast<MessageHandler*>(h.get());
                mh->HandleMessage(std::move(msg), from);
            }
        }
    }

private:
    strand<any_io_executor> executor_;

    std::vector<std::shared_ptr<MessageHandler>> handlers_;
};


#endif //KINO_ACTOR_H
