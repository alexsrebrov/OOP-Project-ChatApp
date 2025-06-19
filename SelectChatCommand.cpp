#include "SelectChatCommand.h"

void SelectChatCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String id;
	std::cin >> id;
	if (!id.isNum())
	{
		std::cout << "Invalid id!";
		return;
	}
	size_t chatId = atoi(id.c_string());
	chats.selectChat(currUser, chatId);
	users.seeChat(currUser, chatId);
}

