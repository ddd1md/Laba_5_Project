#include <string>
#include <vector>
#include <stack>
#include "Message.h"

#ifndef LABA_5_PROJECT_WRITER_H
#define LABA_5_PROJECT_WRITER_H


class Writer {
public:
    Writer() = default; // ����������� ��-���������
    Writer(const Writer& other) = default; // ����������� �����������
    Writer(const std::stack<Message>& history, const std::vector<std::string>& chatsList,
           const std::string& name, const bool& online); // �������������
    ~Writer() = default; // ����������

    void clearHistory(); // �������� ������� ��������� �� ���� �����, � ������� ������� ��������
    bool operator==(const Writer& other) const; // �������� ��������� ���� ���������
    void addToHistory(const Message& other); // �����, ����������� � ������� �������� ���������
    void addToChatsList(const std::string& other); // �����, ����������� �������� ���� � ������ ����� ��������

    std::vector<std::string> getChatsList() const; // �������� ������ �����, � ������� ���� ��������
    std::stack<Message> getHistory() const; // �������� ������� ���������
    std::string getName() const; // �������� ��� ������
    bool isOnline() const; // �������� ��� ������ (online/offline)

    void setName(const std::string& name); // ���������� ���
    void setOnline(const bool& online); // ���������� ������
private:
    std::stack<Message> history_; // ������� ��������� �� ���� �����, ��� ���� ��������
    std::vector<std::string> chatsList_; // ������ �����, � ������� ���� ��������
    std::string name_; // ��� ��������
    bool online_{}; // ������
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
