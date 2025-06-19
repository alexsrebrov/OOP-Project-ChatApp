#include "UserChatInfo.h"


UserChatInfo::UserChatInfo(size_t chatID)
: chatID(chatID),unreadMessages(1) {}

UserChatInfo::UserChatInfo(size_t chatID, size_t unread)
: chatID(chatID),unreadMessages(unread){}

void UserChatInfo::seeMessages()
{
	unreadMessages = 0;
}

void UserChatInfo::addMessage()
{
	unreadMessages++;
}

size_t UserChatInfo::getUnread() const
{
	return unreadMessages;
}

size_t UserChatInfo::getChatID() const
{
	return chatID;
}

std::ostream& operator<<(std::ostream& os, const UserChatInfo& el)
{
	os << "(" << el.unreadMessages << " unread)";
	return os;
}

