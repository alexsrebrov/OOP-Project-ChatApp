#include "AddToGroup.h"

void AddToGroup::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String toAdd, id;
	std::cin >> id >> toAdd;
	if (!id.isNum())
	{
		std::cout << "Error\n";
		return;
	}
	size_t chatId = atoi(id.c_string());

	if(users.isUserReal(toAdd))
		chats.addUserToChat(currUser, toAdd,chatId);
}
