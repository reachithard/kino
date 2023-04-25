//
// Created by luo on 2023/4/11.
//

#include <cassert>
#include "gen.h"
#include "async/actor.h"

Gen::Gen() {

}

Gen::~Gen() {
    Wait();
}

void Gen::Init(uint32_t num, const std::string &file) {
    num = (num == 0) ? 1 : num;

    for (uint32_t idx = 0; idx < num; idx++) {
        executors_.emplace_back(std::make_unique<Executor>(this, idx + 1));
    }

    for (uint32_t idx = 0; idx < num; idx++) {
        executors_[idx]->Run();
    }

    state_.store(State::INIT, std::memory_order_release);
}

int Gen::Run() {
    bool stopOnce = false;
    state_.store(State::READY, std::memory_order_release);
    while (true) {
        if (exit_ < 0) {
            break;
        }

        if (exit_ != std::numeric_limits<int>::max() && !stopOnce) {
            stopOnce = true;
            for (auto iter = executors_.begin(); iter != executors_.end(); iter++) {
                (*iter)->Stop();
            }
        }

        if (state_.load(std::memory_order_acquire) == State::STOPING) {
            size_t alive = executors_.size();
            for (uint32_t idx = 0; idx < executors_.size(); idx++) {
                executors_[idx]->Run();
                if (executors_[idx]->GetCnt() == 0)
                {
                    --alive;
                }
            }

            if (alive == 0) {
                break;
            }
        }
    }
    Wait();
    return exit_;
}

void Gen::Stop(int exit) {
    exit_ = exit;
}

void Gen::Wait() {
    for (auto iter = executors_.begin(); iter != executors_.end(); iter++) {
        (*iter)->Wait();
    }
    state_.store(State::STOPED, std::memory_order_release);
}

State Gen::GetState() const {
    return state_.load(std::memory_order_acquire);
}

void Gen::SetState(State state) {
    state_.store(state, std::memory_order_release);
}

uint32_t Gen::ActorCnt() const {
    uint32_t ret = 0;
    for (auto &iter : executors_) {
        ret += iter->GetCnt();
    }
    return ret;
}

Executor *Gen::NextExecutor() {
    /*
     * 1. 选择一个数量最少
     */
    assert(executors_.size() > 0);
    uint32_t minCnt = std::numeric_limits<uint32_t>::max();
    uint32_t minExeActorCnt = 1;
    for (auto &exe : executors_) {
        uint32_t cnt = exe->GetCnt();
        if (cnt < minCnt) {
            minCnt = cnt;
            minExeActorCnt = exe->GetId();
        }
    }
    return executors_[minExeActorCnt - 1].get();
}

Executor *Gen::GetExecutor(uint32_t executorId, uint32_t actorId) const {
    if (executorId == 0) {
        executorId = Executor::ExecutorId(actorId);
    }

    if (executorId <= 0 || executorId > static_cast<uint32_t>(executors_.size())) {
        return nullptr;
    }

    return executors_[executorId - 1].get();
}

uint32_t Gen::NewActor(std::unique_ptr<Conf> conf) {
    Executor *exe = GetExecutor(conf->executorId);
    if (exe == nullptr) {
        exe = NextExecutor();
    }

    assert(exe != nullptr);
    return exe->NewActor(std::move(conf));
}

void Gen::RemoveActor(uint32_t actorId, uint32_t sender) {
    Executor *exe = GetExecutor(0, actorId);
    if (exe) {
        exe->RemoveActor(actorId, sender);
    } else {
        // Todo
    }
}

void Gen::ScanActor(uint32_t sender, uint32_t executorId) {
    // TODO
}

bool Gen::RegisterActor(const std::string &type, Gen::RegisterFunc func) {
    auto ret = funcs_.emplace(type, func);
    return ret.second;
}

std::unique_ptr<Actor> Gen::MakeActor(const std::string &type) {
    auto iter = funcs_.find(type);
    if (iter != funcs_.end()) {
        return iter->second();
    }
    return nullptr;
}

bool Gen::SendMsg(std::shared_ptr<Message> msg) {
    Executor *exe = GetExecutor(0, msg->GetReceiver());
    if (exe) {
        exe->Send(msg);
        return true;
    }
    return false;
}


