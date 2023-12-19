#include "Message.h"
#include "Writer.h"
#include <vector>
#include <stack>

#ifndef LABA_5_PROJECT_CHAT_H
#define LABA_5_PROJECT_CHAT_H


enum AccessType { // ������ �������
    write,
    read,
    admin
};

enum ChatType { // ������ �����
    publicChat,
    privateChat
};

class Chat {
public:
    Chat() = default; // ����������� ��-���������
    Chat(const Chat& other) = default; // ����������� �����������
    Chat(const std::vector<std::pair<Writer, AccessType>>& members, const std::stack<Message>& history,
         const std::string& title, const std::string& description); // ����������� �������������
    ~Chat() = default; // ����������

    virtual ChatType identify() const; // ������� �������������

    bool writeToChat(const std::pair<Writer, AccessType>& person, const Message& message); // �������� � ���
    void clearHistory(const std::pair<Writer, AccessType>& admin); // �������� ��� (������ ������ ��� ������)
    bool setAccess(const std::pair<Writer, AccessType>& admin, // ���������� ������ (read, write, admin)
                   const std::pair<Writer, AccessType>& person,
                   const AccessType& mode);
    bool containWriter(const std::pair<Writer, AccessType>& person); // �������� �� ���������� � ���� ���������� ������������
    bool operator<<(std::pair<Writer, AccessType>& newMember); // �������� � ��� ������������

    std::vector<std::pair<Writer, AccessType>> getMembers() const; // �������� ������ �����������
    AccessType getAccessWriter(const Writer &person) const; // �������� ������� ������� (read, write, admin)
    std::string getTitle() const; // �������� �������� ����
    std::string getDescription() const; // �������� �������� ����
    unsigned long long getMessageCount() const; // �������� ���������� ��������� � ����
    std::stack<Message> getHistory() const; // �������� ���� �� ����� �����������
    unsigned long long getMembersCount() const; // �������� ���������� �������������

    void setTitle(const std::string& title); // ���������� ��������
    void setDescription(const std::string& description); // ���������� ��������
protected:
    std::vector<std::pair<Writer, AccessType>> members_; // �������� � �� ������� �������
    std::stack<Message> history_; // ������� ��������� ����
    std::string title_; // �������� ����
    std::string description_; // �������� ����
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
