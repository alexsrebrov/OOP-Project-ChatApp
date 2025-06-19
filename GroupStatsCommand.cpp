#include "GroupStatsCommand.h"

void GroupStatsCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String id;
	std::cin >> id;
	if (!id.isNum())
	{
		std::cout << "Error\n";
		return;
	}

	size_t chatId = atoi(id.c_string());
	chats.groupStats(chatId);
}
