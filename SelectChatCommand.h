#pragma once
#include "Command.h"

class SelectChatCommand : public Command
{
public:
	void execute(const String& currUser, UsersDb& users, ChatDb& chats) const override;
};

