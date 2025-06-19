#pragma once
#include "Usersdb.h"
#include "ChatCollection.h"
#include "ChatFactory.h"

class ChatDb
{
public:
	void serializeTxt();
	void serializeBin();
	void deserializeTxt();
	void deserializeBin();


	ChatDb() = default;
	~ChatDb() = default;

	void addChat(ChatType type,const String& input1,const String& input2);
	void removeChat(size_t chatId);

	void selectChat(const String& username, size_t chatId);
	void addUserToChat(const String& username, const String& toAdd, size_t chatId);
	void removeUser(const String& username, size_t chatId);
	void setAdmin(const String& username, size_t chatId);
	void groupStats(size_t chatId);
	void addMessage(const Message& message, size_t chatId);
	size_t getChatId(const String& chatName);
	void viewUserChats(const String& username,const UsersDb& users) const;

	RoleType getRoleTypeInChat(const String& username, size_t chatId);
	void printGroupName(const String& username,size_t chatId) const;
private:
	ChatCollection chats;
	static ChatFactory* factory;

};
