#include "SetGroupAdmin.h"

void SetGroupAdmin::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String user, id;
	std::cin >> id >> user;
	
	if (!id.isNum())
	{
		std::cout << "Error";
		return;
	}
	size_t chatId = atoi(id.c_string());
	chats.setAdmin(user, chatId);
}
