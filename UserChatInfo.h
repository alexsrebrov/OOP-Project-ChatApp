#pragma once
#include "String.h"
#include "MyVector.hpp"

class UserChatInfo
{
public:
	UserChatInfo() = default;
	UserChatInfo(size_t chatID);
	UserChatInfo(size_t chatID, size_t unread);
	~UserChatInfo() = default;
	friend std::ostream& operator<<(std::ostream& os, const UserChatInfo& el);
	void seeMessages();
	void addMessage();
	size_t getUnread() const;
	size_t getChatID() const;
private:
	size_t unreadMessages = 0;
	size_t chatID = 0;
};