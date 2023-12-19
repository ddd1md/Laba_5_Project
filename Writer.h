#include <string>
#include <vector>
#include <stack>
#include "Message.h"

#ifndef LABA_5_PROJECT_WRITER_H
#define LABA_5_PROJECT_WRITER_H


class Writer {
public:
    Writer() = default; // конструктор по-умолчанию
    Writer(const Writer& other) = default; // конструктор копирования
    Writer(const std::stack<Message>& history, const std::vector<std::string>& chatsList,
           const std::string& name, const bool& online); // инициализация
    ~Writer() = default; // деструктор

    void clearHistory(); // очистить историю сообщений со всех чатов, в которых состоит писатель
    bool operator==(const Writer& other) const; // оператор сравнения имен писателей
    void addToHistory(const Message& other); // метод, добавляющий в историю писателя сообщение
    void addToChatsList(const std::string& other); // метод, добавляющий название чата в список чатов писателя

    std::vector<std::string> getChatsList() const; // получить список чатов, в которых есть писатель
    std::stack<Message> getHistory() const; // получить историю сообщений
    std::string getName() const; // получить имя автора
    bool isOnline() const; // получить его статус (online/offline)

    void setName(const std::string& name); // установить имя
    void setOnline(const bool& online); // установить статус
private:
    std::stack<Message> history_; // история сообщений со всех чатов, где есть писатель
    std::vector<std::string> chatsList_; // список чатов, в которых есть писатель
    std::string name_; // имя писателя
    bool online_{}; // статус
};

Writer::Writer(const std::stack<Message>& history, const std::vector<std::string>& chatsList,
               const std::string& name, const bool& online) {
    name_ = name;
    chatsList_ = chatsList;
    online_ = online;
    history_ = history;
}

void Writer::clearHistory() {
    while (!history_.empty()) {
        history_.pop();
    }
}

std::string Writer::getName() const {
    return name_;
}

bool Writer::isOnline() const {
    return online_;
}

void Writer::setName(const std::string &name) {
    name_ = name;
}

void Writer::setOnline(const bool& online) {
    online_ = online;
}

bool Writer::operator==(const Writer& other) const {
    return name_ == other.name_;
}

std::stack<Message> Writer::getHistory() const {
    return history_;
}

void Writer::addToHistory(const Message &other) {
    history_.push(other);
}

std::vector<std::string> Writer::getChatsList() const {
    return chatsList_;
}

void Writer::addToChatsList(const std::string &other) {
    chatsList_.push_back(other);
}

#endif //LABA_5_PROJECT_WRITER_H
