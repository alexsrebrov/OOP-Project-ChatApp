#include "DeleteUserCommand.h"

void DeleteUserCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String user;
	std::cin >> user;
	if (users.getUserType(currUser) != UserType::Admin)
	{
		std::cout << "Error";
		return;
	}
	users.remove(user);
}
