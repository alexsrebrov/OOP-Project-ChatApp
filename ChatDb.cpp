#include "ChatDb.h"

ChatFactory* ChatDb::factory = new ChatFactory();


void ChatDb::serializeTxt()
{
	chats.serializeTxt();
}

void ChatDb::serializeBin()
{
	chats.serializeBin();
}
void ChatDb::deserializeTxt()
{
	chats.deserializeTxt();
}

void ChatDb::deserializeBin()
{
	chats.deserializeBin();
}

void ChatDb::addChat(ChatType type, const String& input1, const String& input2)
{
	try
	{
		chats.addChat(factory->createChat(type, input1, input2));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatDb::removeChat(size_t chatId)
{
	try
	{
		chats.removeChat(chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatDb::selectChat(const String& username, size_t chatId)
{
	try
	{
		chats.selectChat(username, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}

void ChatDb::addUserToChat(const String& username, const String& toAdd, size_t chatId)
{
	try
	{
		chats.addUser(username, toAdd, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}

void ChatDb::removeUser(const String& username, size_t chatId)
{
	try
	{
		chats.removeUser(username, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatDb::setAdmin(const String& username, size_t chatId)
{
	try
	{
		chats.setAdmin(username, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatDb::groupStats(size_t chatId)
{
	try
	{
		chats.groupStats(chatId);
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatDb::addMessage(const Message& message, size_t chatId)
{
	try
	{
		chats.addMessage(message, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

size_t ChatDb::getChatId(const String& chatName)
{
	return chats.getChatId(chatName);
}

void ChatDb::viewUserChats(const String& username,const UsersDb& users) const
{
	chats.viewUserChats(username,users);
}

RoleType ChatDb::getRoleTypeInChat(const String& username, size_t chatId)
{
	try
	{
		return chats.getRoleInChat(username, chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return RoleType::Participant;
	}
}

void ChatDb::printGroupName(const String& username,size_t chatId) const
{
	try
	{
		chats.getChatName(username,chatId);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
