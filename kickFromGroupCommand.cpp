#include "kickFromGroupCommand.h"

void kickFromGroupCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String user, id;
	std::cin >> id >> user;
	if (!id.isNum())
	{
		std::cout << "Error\n";
		return;
	}
	size_t chatId = atoi(id.c_string()); 
	if (chats.getRoleTypeInChat(currUser, chatId) != RoleType::Admin)
	{
		std::cout << "Error";
		return;
	}
	chats.removeUser(user, chatId);
}
