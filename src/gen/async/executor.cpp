//
// Created by luo on 2023/4/11.
//

#include "executor.h"

#include "gen.h"

Executor::Executor(Gen *gen, uint32_t id) : gen_(gen), id_(id), ctx_(1), exeType_(asio::make_work_guard(ctx_)) {
}

Executor::~Executor() {
    Wait();
}

uint32_t Executor::ExecutorId(uint32_t actorId) {
    return ((actorId >> Executor::MAX_ACTOR_SHIFT) & 0xFF);
}

void Executor::Run() {
    thread_ = std::thread([this](){
       ctx_.run();
       actors_.clear();
    });
}

void Executor::Stop() {
    // TODO
}

uint32_t Executor::GetCnt() const {
    return cnts_.load(std::memory_order_acquire);
}

void Executor::Wait() {
    ctx_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
}

void Executor::Send(std::shared_ptr<Message> msg) {
    std::shared_ptr<Message> self(msg->shared_from_this());
    asio::post(ctx_, [this, self](){
        std::unordered_map<uint32_t, std::unique_ptr<Actor>>::iterator iter = actors_.find(self->GetReceiver());
        if (iter != actors_.end()) {
            iter->second->Send(self);
        }
    });
}

uint32_t Executor::NewActor(std::unique_ptr<Conf> conf) {
    do {
        size_t cnt = 0;
        uint32_t actorId = 0;
        do {
            if (cnt >= Executor::MAX_ACTOR) {
                actorId = 0;
                break;
            }

            nextId_++;
            if (nextId_ == Executor::MAX_ACTOR) {
                nextId_ = 1;
            }
            actorId = (id_ << Executor::MAX_ACTOR_SHIFT) | nextId_;
            cnt++;
        } while (actors_.find(actorId) != actors_.end());

        if (actorId == 0) {
            break;
        }

        std::unique_ptr<Actor> actor = gen_->MakeActor(conf->type_);
        assert(actor != nullptr);
        actor->SetId(actorId);
        actor->SetContext(gen_, this, ctx_.get_executor());

        if (!actor->Init(std::move(conf))) {
            break;
        }

        cnts_.fetch_add(1, std::memory_order_release);
        actors_.emplace(actorId, std::move(actor));
        return actorId;
    } while (0);
    return 0;
}

void Executor::RemoveActor(uint32_t actorId, uint32_t sender) {

}
