#pragma once
#include "Command.h"
class ViewAllChatsCommand : public Command
{
public:
	void execute(const String& currUser, UsersDb& users, ChatDb& chats) const override;

};
