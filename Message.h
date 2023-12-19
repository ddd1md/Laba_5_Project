#include <string>

#ifndef LABA_5_PROJECT_MESSAGE_H
#define LABA_5_PROJECT_MESSAGE_H

class Message {
public:
    Message() = default; // ����������� ��-���������
    Message(const std::string& content, const std::size_t& time); // ����������� �������������
    Message(const Message& other) = default; // ����������� �����������
    ~Message() = default; // ����������

    std::string getContent() const; // �������� ����� ���������
    std::size_t getTime() const; // �������� ����� ��������

    void editContent(const std::string& content); // ���������� ���������
    void editTime(const std::size_t& time); // ���������� �����
private:
    std::string content_; // ����� ���������
    std::size_t time_{}; // ����� �������� ���������
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
