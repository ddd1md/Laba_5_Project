#include "Chat.h"

#ifndef LABA_5_PROJECT_PRIVATECHAT_H
#define LABA_5_PROJECT_PRIVATECHAT_H


class PrivateChat : public Chat {
public:
    PrivateChat() = default; // конструктор по-умолчанию
    PrivateChat(const std::vector<std::pair<Writer, AccessType>>& members, const std::stack<Message>& history,
                const std::string& title, const std::string& description); // конструктор инициализации
    PrivateChat(const PrivateChat& other) = default; // конструктор копирования
    ~PrivateChat() = default; // деструктор

    ChatType identify() const override; // функция идентификации
};

PrivateChat::PrivateChat(const std::vector<std::pair<Writer, AccessType>> &members, const std::stack<Message> &history,
                         const std::string &title, const std::string &description) {
    if (members.size() > 2) {
        members_.push_back(members[0]);
        members_.push_back(members[1]);
        for (auto & member : members_) {
            member.second = admin;
        }
    }
    else {
        members_ = members;
        for (auto & member : members_) {
            member.second = admin;
        }
    }
    history_ = history;
    title_ = title;
    description_ = description;
}

ChatType PrivateChat::identify() const {
    return privateChat;
}

#endif //LABA_5_PROJECT_PRIVATECHAT_H
