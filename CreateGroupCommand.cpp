#include "CreateGroupCommand.h"

static constexpr size_t BUFF_SIZE = 1024;
void CreateGroupCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String groupName,userToAdd;
	std::cin >> groupName;
	chats.addChat(ChatType::Group, groupName, currUser);
	size_t chatId = chats.getChatId(groupName);
	while (true)
	{
		if (std::cin.peek() == '\n')
		{
			std::cout << "Group " << groupName << " added!\n";
			return;
		}
		std::cin >> userToAdd;
		if(users.isUserReal(userToAdd))
			chats.addUserToChat(currUser, userToAdd, chatId);
	}
}
