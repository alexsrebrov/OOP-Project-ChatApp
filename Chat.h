#pragma once
#include "MyVector.hpp";
#include "ChatParticipant.h"
#include "Message.h"

enum class ChatType
{
	Dm,Group
};

class Chat
{
public:


	Chat();
	virtual ~Chat() = default;

	size_t getChatId() const;
	virtual Chat* clone() const = 0;
	virtual ChatType getChatType() const = 0;
	virtual const String& getChatName(const String& username) const = 0;

	void seeMessages() const;
	void addMessage(const Message& message);

	virtual void addUser(const String& username, const String& toAdd) = 0;
	virtual void removeUser(const String& username) = 0;
	virtual void groupStats() const = 0;
	virtual void seetRequests() const = 0;
	virtual void setAdmin(const String& username) = 0;
	virtual void makeChatPrivate() = 0;

	virtual bool isInChat(const String& username) = 0;
	virtual RoleType getUserRoleInChat(const String& username) = 0;
private:
	size_t chatId;
	static size_t chatIdcreator;
protected:
	MyVector<Message> messages;
};

