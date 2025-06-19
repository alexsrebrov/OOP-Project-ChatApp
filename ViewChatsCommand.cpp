#include "ViewChatsCommand.h"

void ViewChatsCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	chats.viewUserChats(currUser,users);
}
