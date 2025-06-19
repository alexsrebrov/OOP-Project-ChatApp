#pragma once
#include "String.h"
#include "Command.h"
#include "CreateAccountCommand.h"
#include "ViewChatsCommand.h"
#include "SelectChatCommand.h"
#include "CreateGroupCommand.h"
#include "LeaveGroupCommand.h"
#include "AddToGroup.h"
#include "kickFromGroupCommand.h"
#include "SetGroupAdmin.h"
#include "GroupStatsCommand.h"
#include "DeleteUserCommand.h"
#include "DeleteGroupCommand.h"
#include "ViewAllChatsCommand.h"

class CommandFactory
{
public:
	Command* getCommand(const String& cmd, const String& currUser) const;
};

