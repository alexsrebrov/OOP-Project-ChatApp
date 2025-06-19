#pragma once
#include "ChatDb.h"
#include "UsersDb.h"
#include "CommandFactory.h"

class SystemDb
{
public:
	SystemDb() = default;
	void load();
	void save();
	void execute();
	const String& login(String& input,const CommandFactory* fac);
private:
	UsersDb users;
	ChatDb chats;
};

