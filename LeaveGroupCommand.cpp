#include "LeaveGroupCommand.h"

void LeaveGroupCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String id;
	std::cin >> id;
	if (!id.isNum())  
	{
		  std::cout << "Error";
		  return;
	}

	size_t chatId = atoi(id.c_string());
	chats.removeUser(currUser, chatId);
}
