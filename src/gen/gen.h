//
// Created by luo on 2023/4/11.
//

#ifndef KINO_GEN_H
#define KINO_GEN_H

#include <memory>
#include <atomic>
#include <unordered_map>
#include <vector>

#include "async/executor.h"
#include "async/conf.h"
#include "async/message.h"

enum class State
{
    UNKNOW,
    INIT,
    READY,
    STOPING,
    STOPED
};

class Actor;
class Gen {
public:
    using RegisterFunc = std::unique_ptr<Actor>(*)();

    Gen();

    ~Gen();

    Gen(const Gen& other) = delete;
    Gen(const Gen&& other) = delete;
    Gen& operator=(const Gen& other) = delete;
    Gen& operator=(const Gen&& other) = delete;

    void Init(uint32_t num, const std::string &file);

    int Run();

    void Stop(int exit);

    State GetState() const;

    void SetState(State state);

    uint32_t ActorCnt() const;

    Executor *NextExecutor();

    Executor *GetExecutor(uint32_t executorId, uint32_t actorId = 0) const;

    uint32_t NewActor(std::unique_ptr<Conf> conf);

    void RemoveActor(uint32_t actorId, uint32_t sender);

    void ScanActor(uint32_t sender, uint32_t executorId);

    bool RegisterActor(const std::string &type, RegisterFunc func);

    std::unique_ptr<Actor> MakeActor(const std::string &type);

    bool SendMsg(std::shared_ptr<Message> msg);
private:
    void Wait();
private:
    volatile int exit_ = std::numeric_limits<int>::max();
    std::atomic<State> state_ = State::UNKNOW;
    std::unordered_map<std::string, RegisterFunc> funcs_;
    std::vector<std::unique_ptr<Executor>> executors_;
};


#endif //KINO_GEN_H
