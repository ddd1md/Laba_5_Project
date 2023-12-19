#include "Message.h"
#include "Writer.h"
#include <vector>
#include <stack>

#ifndef LABA_5_PROJECT_CHAT_H
#define LABA_5_PROJECT_CHAT_H


enum AccessType { // уровни доступа
    write,
    read,
    admin
};

enum ChatType { // уровни чатов
    publicChat,
    privateChat
};

class Chat {
public:
    Chat() = default; // конструктор по-умолчанию
    Chat(const Chat& other) = default; // конструктор копирования
    Chat(const std::vector<std::pair<Writer, AccessType>>& members, const std::stack<Message>& history,
         const std::string& title, const std::string& description); // конструктор инициализации
    ~Chat() = default; // деструктор

    virtual ChatType identify() const; // функция идентификатор

    bool writeToChat(const std::pair<Writer, AccessType>& person, const Message& message); // написать в чат
    void clearHistory(const std::pair<Writer, AccessType>& admin); // очистить чат (доступ только для админа)
    bool setAccess(const std::pair<Writer, AccessType>& admin, // установить статус (read, write, admin)
                   const std::pair<Writer, AccessType>& person,
                   const AccessType& mode);
    bool containWriter(const std::pair<Writer, AccessType>& person); // проверка на содержание в чате указанного пользователя
    bool operator<<(std::pair<Writer, AccessType>& newMember); // добавить в чат пользователя

    std::vector<std::pair<Writer, AccessType>> getMembers() const; // получить список подписчиков
    AccessType getAccessWriter(const Writer &person) const; // получить уровень доступа (read, write, admin)
    std::string getTitle() const; // получить название чата
    std::string getDescription() const; // получить описание чата
    unsigned long long getMessageCount() const; // получить количество сообщений в чате
    std::stack<Message> getHistory() const; // получить стек со всеми сообщениями
    unsigned long long getMembersCount() const; // получить количество пользователей

    void setTitle(const std::string& title); // установить название
    void setDescription(const std::string& description); // установить описание
protected:
    std::vector<std::pair<Writer, AccessType>> members_; // писатели и их уровень доступа
    std::stack<Message> history_; // история сообщений чата
    std::string title_; // название чата
    std::string description_; // описание чата
};

Chat::Chat(const std::vector<std::pair<Writer, AccessType>> &members, const std::stack<Message> &history,
           const std::string &title, const std::string &description) {
    members_ = members;
    if (!members_.empty()) {
        members_[0].second = admin;
        members_[0].first.addToChatsList(title_);
        for (int i = 1; i < members_.size(); ++i) {
            members_[i].second = read;
            members_[i].first.addToChatsList(title_);
        }
    }
    history_ = history;
    title_ = title;
    description_ = description;
}

ChatType Chat::identify() const {
    return publicChat;
}

bool Chat::writeToChat(const std::pair<Writer, AccessType>& person, const Message& message) {
    if ((person.second == write || person.second == admin) && person.first.isOnline() && containWriter(person)) {
        history_.push(message);

        for (auto & member : members_) {
            if (member.first.isOnline()) {
                member.first.addToHistory(message);
            }
        }

        return true;
    }
    return false;
}

void Chat::clearHistory(const std::pair<Writer, AccessType>& admin) {
    if (admin.first == members_[0].first && admin.second == members_[0].second) {
        while (!history_.empty()) {
            history_.pop();
        }
    }
}

bool Chat::setAccess(const std::pair<Writer, AccessType>& admin,
                     const std::pair<Writer, AccessType>& person,
                     const AccessType& mode) {
    if (admin.first == members_[0].first && admin.second == members_[0].second) {
        for (auto & member : members_) {
            if (member == person) {
                member.second = mode;
                return true;
            }
        }
    }
    return false;
}

bool Chat::operator<<(std::pair<Writer, AccessType> &newMember) {
    if (containWriter(newMember)) {
        return false;
    }

    newMember.first.addToChatsList(title_);
    members_.push_back(newMember);
    return true;
}

AccessType Chat::getAccessWriter(const Writer &person) const {
    for (const auto & member : members_) {
        if (member.first == person) {
            return member.second;
        }
    }
}

bool Chat::containWriter(const std::pair<Writer, AccessType>& person) {
    for (const auto & member : members_) {
        if (member.first == person.first && member.second == person.second) {
            return true;
        }
    }
    return false;
}

std::string Chat::getTitle() const {
    return title_;
}

std::string Chat::getDescription() const {
    return description_;
}

unsigned long long Chat::getMessageCount() const {
    return history_.size();
}

std::stack<Message> Chat::getHistory() const {
    return history_;
}

unsigned long long Chat::getMembersCount() const {
    return members_.size();
}

void Chat::setTitle(const std::string& title) {
    title_ = title;
}

void Chat::setDescription(const std::string& description) {
    description_ = description;
}

std::vector<std::pair<Writer, AccessType>> Chat::getMembers() const {
    return members_;
}

#endif //LABA_5_PROJECT_CHAT_H
