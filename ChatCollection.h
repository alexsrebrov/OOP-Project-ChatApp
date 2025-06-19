#pragma once
#include "Chat.h"
#include"UsersDb.h"

class ChatCollection
{
public:
	void serializeTxt();
	void serializeBin();
	void deserializeTxt();
	void deserializeBin();

	ChatCollection();
	ChatCollection(const ChatCollection& other);
	ChatCollection& operator=(const ChatCollection& other);
	ChatCollection(ChatCollection&& other) noexcept;
	ChatCollection& operator=(ChatCollection&& other) noexcept;
	~ChatCollection();

	void addChat(Chat* add);
	void removeChat(size_t chatId);

	void selectChat(const String& username, size_t chatId);
	void addUser(const String& username, const String& toAdd, size_t chatId);
	void removeUser(const String& username, size_t chatId);
	void setAdmin(const String& username, size_t chatId);
	void groupStats(size_t chatId);
	void addMessage(const Message& message, size_t chatId);
	RoleType getRoleInChat(const String& username, size_t chatId);
	const String& getChatName(const String& username,size_t chatId) const;
	size_t getChatId(const String& chatName);
	void viewUserChats(const String& username,const UsersDb& users) const;

	const Chat* operator[](size_t index) const;
	Chat* operator[](size_t index);
	bool isEmpty() const;
	size_t find(size_t chatId) const;

private:
	Chat** chats;
	size_t size;
	size_t capacity;

	void resize(size_t newCap);
	void copyFrom(const ChatCollection& other);
	void moveFrom(ChatCollection&& other);
	void free();


};

