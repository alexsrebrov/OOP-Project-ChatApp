#pragma once
#include "Command.h"

class LeaveGroupCommand : public Command
{
public:
	void execute(const String& currUser, UsersDb& users, ChatDb& chats) const override;
};

