#pragma once
#include "Command.h"
class DeleteUserCommand : public Command
{
public:
	void execute(const String& currUser, UsersDb& users, ChatDb& chats) const override;

};

