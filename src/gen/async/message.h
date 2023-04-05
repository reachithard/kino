//
// Created by luo on 2023/4/5.
//

#ifndef KINO_MESSAGE_H
#define KINO_MESSAGE_H

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <memory>

enum class MessageType {
    UNKNOW,
    C2S_LOGIN,
    S2C_LOGIN,
    C2S_REGISTER,
    S2c_REGISTER
};

class Message {
public:
    explicit Message(MessageType msgType) : msgType_(msgType)
    {
    }

    ~Message()
    {
    }

    Message(const Message&) = delete;

    Message& operator=(const Message&) = delete;

    Message(Message&& other) noexcept
    :msgType_(other.msgType_)
    , sender_(std::exchange(other.sender_, 0))
    , receiver_(std::exchange(other.receiver_, 0))
    , sessionid_(std::exchange(other.sessionid_, 0))
    , header_(std::move(other.header_))
    , data_(std::move(other.data_))
    {
    }

    Message& operator=(Message&& other) noexcept
    {
        if (this != std::addressof(other))
        {
            msgType_ = other.msgType_;
            sender_ = std::exchange(other.sender_, 0);
            receiver_ = std::exchange(other.receiver_, 0);
            sessionid_ = std::exchange(other.sessionid_, 0);
            header_ = std::move(other.header_);
            data_ = std::move(other.data_);
        }
        return *this;
    }

    MessageType GetMsgType() const {
        return msgType_;
    }

private:
    MessageType msgType_ = MessageType::UNKNOW;
    uint32_t sender_ = 0;
    uint32_t receiver_ = 0;
    int32_t sessionid_ = 0;
    std::unique_ptr<std::string> header_;
    std::vector<unsigned char> data_;
};


#endif //KINO_MESSAGE_H
