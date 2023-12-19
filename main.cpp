#include "Writer.h"
#include "PrivateChat.h"
#include <cassert>
#include <iostream>

int main() {
    // 1.Тесты для класса Message.h
    Message testMessageClass1;
    Message testMessageClass2;
    Message testMessageClass3;
    Message testMessageClassDefault = Message();
    Message testMessageClassInit = Message("Hello, Hello!!", 123);

    // по-умолчанию
    assert(testMessageClassDefault.getContent().empty());
    assert(testMessageClassDefault.getTime() == 0);

    // инициализации
    assert(testMessageClassInit.getContent() == "Hello, Hello!!");
    assert(testMessageClassInit.getTime() == 123);

    // копирования
    Message testMessageClassCopy = Message(testMessageClassInit);
    assert(testMessageClassCopy.getContent() == "Hello, Hello!!");
    assert(testMessageClassCopy.getTime() == 123);

    testMessageClass1.editContent("Hello, team!");
    testMessageClass2.editContent("Hi, My name is Dima.");
    testMessageClass3.editContent("Hello, friends.");

    // тесты геттеров
    assert(testMessageClass1.getContent() == "Hello, team!");
    assert(testMessageClass2.getContent() == "Hi, My name is Dima.");
    assert(testMessageClass3.getContent() == "Hello, friends.");

    std::cout << "Tests for class Message have been successfully passed." << std::endl;

    // 2.Тесты для класса Writer old.h
    std::stack<Message> hist;
    std::vector<std::string> chats;

    Writer testWriterClass1;
    Writer testWriterClass2;
    Writer testWriterClass3;
    Writer testWriterDefault = Writer();
    Writer testWriterInit = Writer(hist, chats, "Nikita", true);
    Writer testWriterCopy = Writer(testWriterInit);

    // по-умолчанию
    assert(testWriterDefault.isOnline() == false);
    assert(testWriterDefault.getName().empty());
    assert(testWriterDefault.getHistory().empty());
    assert(testWriterDefault.getChatsList().empty());
    // инициализация
    assert(testWriterInit.isOnline() == true);
    assert(testWriterInit.getName() == "Nikita");
    assert(testWriterInit.getHistory().empty());
    assert(testWriterInit.getChatsList() == chats);
    // копирования
    assert(testWriterCopy.isOnline() == true);
    assert(testWriterCopy.getName() == "Nikita");
    assert(testWriterCopy.getHistory().empty());
    assert(testWriterCopy.getChatsList() == chats);

    testWriterClass1.setName("Victor");
    testWriterClass2.setName("Dmitry");
    testWriterClass3.setName("Vladimir");

    // тесты геттеров
    assert(testWriterClass1.getName() == "Victor");
    assert(testWriterClass2.getName() == "Dmitry");
    assert(testWriterClass3.getName() == "Vladimir");


    testWriterClass1.setOnline(true);
    testWriterClass2.setOnline(false);
    testWriterClass3.setOnline(true);

    // тесты геттеров
    assert(testWriterClass1.isOnline() == true);
    assert(testWriterClass2.isOnline() == false);
    assert(testWriterClass3.isOnline() == true);

    // тест оператора сравнения имен писателей
    assert(!(testWriterClass1 == testWriterClass2));
    Writer testWriterClass4;
    testWriterClass4.setName("Dmitry");
    assert(testWriterClass2 == testWriterClass4);

    std::cout << "Tests for class Writer have been successfully passed." << std::endl;

    // 3.Тесты для класса Chat.h
    std::vector<std::pair<Writer, AccessType>> defaultVector = std::vector<std::pair<Writer, AccessType>>();
    std::vector<std::pair<Writer, AccessType>> subs = std::vector<std::pair<Writer, AccessType>>();
    std::vector<std::pair<Writer, AccessType>> subsInit = std::vector<std::pair<Writer, AccessType>>();
    std::vector<std::pair<Writer, AccessType>> subsPrivateInit = std::vector<std::pair<Writer, AccessType>>();

    subsPrivateInit.push_back(std::make_pair(testWriterClass1, admin));
    subsPrivateInit.push_back(std::make_pair(testWriterClass2, admin));

    subs.push_back(std::make_pair(testWriterClass1, read));
    subs.push_back(std::make_pair(testWriterClass2, write));

    subsInit.push_back(std::make_pair(testWriterClass1, admin));
    subsInit.push_back(std::make_pair(testWriterClass2, read));
    std::stack<Message> hist2;

    Chat testChatClass1;
    Chat testChatClass2;
    Chat testChatClassDefault = Chat();
    Chat testChatClassInit = Chat(subs, hist2, "VKChat", "Main chat...");
    Chat testChatClassCopy = Chat(testChatClassInit);

    // по-умолчанию
    assert(testChatClassDefault.getTitle().empty());
    assert(testChatClassDefault.getDescription().empty());
    assert(testChatClassDefault.getHistory().empty());
    assert(testChatClassDefault.getMembersCount() == 0);
    // инициализации
    assert(testChatClassInit.getTitle() == "VKChat");
    assert(testChatClassInit.getDescription() == "Main chat...");
    assert(testChatClassInit.getHistory().empty());
    assert(testChatClassInit.getMembers() == subsInit);
    // копирования
    assert(testChatClassCopy.getTitle() == "VKChat");
    assert(testChatClassCopy.getDescription() == "Main chat...");
    assert(testChatClassCopy.getHistory().empty());
    assert(testChatClassCopy.getMembers() == subsInit);

    testChatClass1.setTitle("Family Chat  old");
    testChatClass2.setTitle("University Chat  old");
    // геттеры
    assert(testChatClass1.getTitle() == "Family Chat  old");
    assert(testChatClass2.getTitle() == "University Chat  old");

    // проверка идентификатора
    assert(testChatClass1.identify() == publicChat);

    // проверка оператора добавления в чат писателей
    testChatClassDefault.setTitle("Job chat");
    Writer writer1;
    Writer writer2;
    Writer writer3;

    writer1.setName("Dima");
    writer1.setOnline(true);
    writer2.setName("Senya");
    writer2.setOnline(false);
    writer3.setName("Anton");
    writer3.setOnline(true);

    std::pair<Writer, AccessType> writerPair1 = std::make_pair(writer1, admin);
    std::pair<Writer, AccessType> writerPair2 = std::make_pair(writer2, read);
    std::pair<Writer, AccessType> writerPair3 = std::make_pair(writer3, write);

    testChatClassDefault << writerPair1;
    testChatClassDefault << writerPair2;
    testChatClassDefault << writerPair3;

    assert(testChatClassDefault.getMembersCount() == 3);

    // проверка метода добавления в чат сообщения
    testChatClassDefault.writeToChat(writerPair1, testMessageClassInit);
    assert(testChatClassDefault.getMessageCount() == 1);

    // проверка метода очистки чата
    testChatClassDefault.clearHistory(writerPair1);
    assert(testChatClassDefault.getMessageCount() == 0);

    // проверка метода установки статуса
    testChatClassDefault.setAccess(writerPair1, writerPair2, admin);
    assert(testChatClassDefault.getAccessWriter(writer2) == admin);

    // проверка метода на содержание в чате указанного пользователя
    assert(testChatClassDefault.containWriter(writerPair3) == true);

    std::cout << "Tests for class Chat have been successfully passed." << std::endl;

    // проверка метода getChatsList
    assert(testChatClassDefault.getMembers()[0].first.getChatsList()[0] == "Job chat");

    // проверка метода getHistory в классе Writer
    assert(testChatClassDefault.getMembers()[0].first.getHistory().top().getContent() == testMessageClassInit.getContent());


    std::cout << "*Extra tests for class Writer have been successfully passed." << std::endl;

    // 4.Тесты для класса PrivateChat.h
    PrivateChat privateChatClassDefault = PrivateChat();
    PrivateChat privateChatClassInit = PrivateChat(subs, hist2, "VKChat", "Main chat...");
    PrivateChat privateChatClassCopy = PrivateChat(privateChatClassInit);

    // по-умолчанию
    assert(privateChatClassDefault.getTitle().empty());
    assert(privateChatClassDefault.getDescription().empty());
    assert(privateChatClassDefault.getHistory().empty());
    assert(privateChatClassDefault.getMembersCount() == 0);
    // инициализации
    assert(privateChatClassInit.getTitle() == "VKChat");
    assert(privateChatClassInit.getDescription() == "Main chat...");
    assert(privateChatClassInit.getHistory().empty());
    assert(privateChatClassInit.getMembers() == subsPrivateInit);
    // копирования
    assert(privateChatClassCopy.getTitle() == "VKChat");
    assert(privateChatClassCopy.getDescription() == "Main chat...");
    assert(privateChatClassCopy.getHistory().empty());
    assert(privateChatClassCopy.getMembers() == subsPrivateInit);

    // метод идентификатор
    assert(privateChatClassDefault.identify() == privateChat);

    std::cout << "Tests for class PrivateChat have been successfully passed." << std::endl;

    return 0;
}
