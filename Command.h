#pragma once
#include "String.h"
#include "UsersDb.h"
#include "ChatDb.h"

class Command
{
public:
	virtual void execute(const String& currUser, UsersDb& users, ChatDb& chats) const = 0;
};

