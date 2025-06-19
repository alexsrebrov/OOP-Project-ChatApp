#include "Dm.h"

Dm::Dm(const String& user1, const String& user2)
	: Chat(), user1(user1,RoleType::Admin),user2(user2, RoleType::Admin)
{}

Chat* Dm::clone() const
{
	return new Dm(*this);
}

ChatType Dm::getChatType() const
{
	return ChatType::Dm;
}

const String& Dm::getChatName(const String& username) const
{
	if (username == user1.getName()) return user2.getName();
	else if (username == user2.getName()) return user1.getName();
	else return user1.getName() + "-" + user2.getName();
}

void Dm::addUser(const String& username,const String& toAdd)
{
	throw std::runtime_error("Cannot add member to dm chat");
}

void Dm::removeUser(const String& username)
{
	throw std::runtime_error("Cannot remove member from dm chat");
}

void Dm::groupStats() const
{
	throw std::runtime_error("Invalid function for this chat");
}

void Dm::seetRequests() const
{
	throw std::runtime_error("Invalid function for this chat");
}

void Dm::setAdmin(const String& username)
{
	throw std::runtime_error("Invalid function for this chat");
}

void Dm::makeChatPrivate()
{
	throw std::runtime_error("Invalid function for this chat");
}

bool Dm::isInChat(const String& username)
{
	return username == user1.getName() || username  == user2.getName();
}

RoleType Dm::getUserRoleInChat(const String& username)
{
	throw std::runtime_error("Invalid function for this chat");
}
