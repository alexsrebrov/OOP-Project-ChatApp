#include "ViewAllChatsCommand.h"

void ViewAllChatsCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	if (users.getUserType(currUser) != UserType::Admin)
	{
		std::cout << "Error";
		return;
	}
	for (size_t i = 0; i < users.getSize(); i++)
	{
		chats.viewUserChats(users[i]->getUsername(), users);
	}
}
