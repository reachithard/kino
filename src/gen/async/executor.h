//
// Created by luo on 2023/4/11.
//

#ifndef KINO_EXECUTOR_H
#define KINO_EXECUTOR_H

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <atomic>
#include <thread>

#include "conf.h"
#include "message.h"
#include "actor.h"

#include "asio/io_context.hpp"

class Gen;
class Executor final {
public:
    Executor(Gen *gen, uint32_t id);

    ~Executor();

    static uint32_t ExecutorId(uint32_t actorId);

    void Run();

    void Stop();

    uint32_t GetCnt() const;

    void Wait();

    uint32_t NewActor(std::unique_ptr<Conf> conf);

    void RemoveActor(uint32_t actorId, uint32_t sender);

    uint32_t GetId() const {
        return id_;
    }

    void Send(std::shared_ptr<Message> msg);
private:
    static constexpr  uint32_t MAX_ACTOR = 0xFFFFFF;
    static constexpr  uint32_t MAX_ACTOR_SHIFT = 6;
    std::atomic<uint32_t> cnts_;
    Gen* gen_;
    std::thread thread_;
    asio::io_context ctx_;
    asio::executor_work_guard<asio::io_context::executor_type> exeType_;
    uint32_t id_;
    uint32_t nextId_;
    std::unordered_map<uint32_t, std::unique_ptr<Actor>> actors_;
};


#endif //KINO_EXECUTOR_H
