#include "DeleteGroupCommand.h"

void DeleteGroupCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String id;
	std::cin >> id;
	if (!id.isNum())
	{
		std::cout << "Error\n";
		return;
	}
	if (users.getUserType(currUser) != UserType::Admin)
	{
		std::cout << "Invalid command!\n";
		return;
	}
	chats.removeChat(atoi(id.c_string()));
}
