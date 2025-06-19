#include "User.h"

User::User(const String& username, const String& password)
: username(username),password(password),userChats(){}


void User::changePassword(const String& oldPass, const String& newPass)
{
	if (checkPassword(oldPass)) password = newPass;
	else throw std::runtime_error("Wrong password!");
}

size_t User:: getUnread(size_t chatId) const
{
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		if (userChats[i].getChatID() == chatId)
			return userChats[i].getUnread();
	}
}

bool User::checkPassword(const String& pass)
{
	return pass == password;
}

void User::addMessage(size_t chatID)
{
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		if(userChats[i].getChatID() == chatID)
		{
			userChats[i].addMessage();
			return;
		}
	}
	userChats.add(UserChatInfo(chatID));
}

void User::seeChat(size_t chatID)
{
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		if (chatID == userChats[i].getChatID()) userChats[i].seeMessages();
	}
}

const String& User::getUsername() const
{
	return username;
}

const String& User::getPass() const
{
	return password;
}
