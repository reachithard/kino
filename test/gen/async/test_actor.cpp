////
//// Created by luo on 2023/4/5.
////
//
//#include "gen/async/actor.h"
//
//#include "gtest/gtest.h"
//
//class receiver : public Actor
//{
//public:
//    receiver()
//            : Actor(system_executor())
//    {
//        RegisterHandler(&receiver::message_handler, MessageType::S2C_LOGIN);
//    }
//
//    // Block until a message has been received.
//    Message wait()
//    {
//        std::unique_lock<std::mutex> lock(mutex_);
//        condition_.wait(lock, [this]{ return !message_queue_.empty(); });
//        std::cout << "wait" << std::endl;
//        Message msg(std::move(message_queue_.front()));
//        message_queue_.pop_front();
//        return msg;
//    }
//
//private:
//    // Handle a new message by adding it to the queue and waking a waiter.
//    void message_handler(Message msg, ActorAddress /* from */)
//    {
//        std::lock_guard<std::mutex> lock(mutex_);
//        message_queue_.push_back(std::move(msg));
//        condition_.notify_one();
//    }
//
//    std::mutex mutex_;
//    std::condition_variable condition_;
//    std::deque<Message> message_queue_;
//};
//
//#include <asio/thread_pool.hpp>
//#include <iostream>
//
//using asio::thread_pool;
//
//class member : public Actor
//{
//public:
//    explicit member(any_io_executor e)
//            : Actor(std::move(e))
//    {
//        RegisterHandler(&member::init_handler, MessageType::C2S_LOGIN);
//        RegisterHandler(&member::token_handler, MessageType::C2S_REGISTER);
//    }
//
//private:
//    void init_handler(Message msg, ActorAddress from)
//    {
//
//        std::cout << "call init handler" << std::endl;
//        caller_ = from;
//
//    }
//
//    void token_handler(Message msg, ActorAddress /*from*/)
//    {
//        ActorAddress to(caller_);
//
////        if (token > 0)
////        {
////            msg = token - 1;
////            to = next_;
////        }
////
////        tail_send(msg, to);
//    }
//
//    ActorAddress next_;
//    ActorAddress caller_;
//};
//
//TEST(actor, test) {
//    const std::size_t num_threads = 2;
//    const int num_hops = 50000000;
//    const std::size_t num_actors = 3;
//    const int token_value = (num_hops + num_actors - 1) / num_actors;
//    const std::size_t actors_per_thread = num_actors / num_threads;
//
//    struct single_thread_pool : thread_pool { single_thread_pool() : thread_pool(1) {} };
//    single_thread_pool pools[num_threads];
//    std::vector<std::shared_ptr<member>> members(num_actors);
//    receiver rcvr;
//
//    for (std::size_t i = 0; i < num_actors; ++i)
//        members[i] = std::make_shared<member>(pools[(i / actors_per_thread) % num_threads].get_executor());
//
//    for (std::size_t i = num_actors, next_i = 0; i > 0; next_i = --i) {
//        Message message(MessageType::C2S_LOGIN);
//
//        Send(std::move(message), rcvr.Address(), members[i - 1]->Address());
//    }
//
//    std::cout << "end" << std::endl;
//    for (std::size_t i = 0; i < num_actors; ++i) {
//        std::cout << "end" << std::endl;
//        rcvr.wait();
//    }
//
//    std::cout << "end" << std::endl;
//}