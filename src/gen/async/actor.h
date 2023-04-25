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
#include "gen.h"

class Actor {
public:
    virtual ~Actor() {}

    void Send(std::shared_ptr<Message> msg)
    {
        // Execute the message handler in the context of the target's executor.
//        Actor *to = gen.
        CallHandler(msg);
    }

    void SetId(uint32_t id) {
        id_ = id;
    }

    virtual bool Init(std::unique_ptr<Conf> conf) {
        return true;
    }

    void SetContext(Gen *gen, Executor *ctx) {
        gen_ = gen;
        ctx_ = ctx;
    }
protected:
    Actor() {
    }

    template <class Actor>
    void RegisterHandler(void (Actor::* mf)(std::shared_ptr<Message>), MessageType msgType)
    {
        handlers_.push_back(
                std::make_shared<MfMessageHandler<Actor>>(
                mf, static_cast<Actor*>(this), msgType));
    }

    template <class Actor>
    void DeregisterHandler(void (Actor::* mf)(std::shared_ptr<Message>), MessageType msgType)
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
    void CallHandler(std::shared_ptr<Message> msg)
    {
        for (auto& h: handlers_)
        {
            if (h->GetMsgType() == msg->GetMsgType())
            {
                auto mh = static_cast<MessageHandler*>(h.get());
                mh->HandleMessage(msg);
            }
        }
    }

private:
    Gen *gen_ = nullptr;
    Executor *ctx_ = nullptr;
    std::vector<std::shared_ptr<MessageHandler>> handlers_;
    uint32_t id_;
};


#endif //KINO_ACTOR_H
