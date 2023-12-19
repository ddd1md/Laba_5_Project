#include <string>

#ifndef LABA_5_PROJECT_MESSAGE_H
#define LABA_5_PROJECT_MESSAGE_H

class Message {
public:
    Message() = default; // конструктор по-умолчанию
    Message(const std::string& content, const std::size_t& time); // конструктор инициализации
    Message(const Message& other) = default; // конструктор копирования
    ~Message() = default; // деструктор

    std::string getContent() const; // получить текст сообщения
    std::size_t getTime() const; // получить время отправки

    void editContent(const std::string& content); // установить сообщение
    void editTime(const std::size_t& time); // установить время
private:
    std::string content_; // текст сообщения
    std::size_t time_{}; // время отправки сообщения
};

Message::Message(const std::string &content, const std::size_t &time) {
    content_ = content;
    if (time < 0) {
        time_ = 0;
    }
    else {
        time_ = time;
    }
}

std::string Message::getContent() const {
    return content_;
}

std::size_t Message::getTime() const {
    return time_;
}

void Message::editContent(const std::string &content) {
    content_ = content;
}

void Message::editTime(const std::size_t &time) {
    time_ = time;
}

#endif //LABA_5_PROJECT_MESSAGE_H
