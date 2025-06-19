#include "CommandFactory.h"
#include "CreateAccountCommand.h"


Command* CommandFactory::getCommand(const String& cmd, const String& currUser) const
{
	if (cmd == "create-account") return new CreateAccountCommand();
	else if (cmd == "view-chats") return new ViewChatsCommand();
	else if (cmd == "select-chat") return new SelectChatCommand();
	else if (cmd == "create-group") return new CreateGroupCommand();
	else if (cmd == "leave-group") return new LeaveGroupCommand();
	else if (cmd == "add-to-group") return new AddToGroup();
	else if (cmd == "kick-from-group") return new kickFromGroupCommand();
	else if (cmd == "set-group-admin") return new SetGroupAdmin();
	else if (cmd == "group-stats") return new GroupStatsCommand();
	else if (cmd == "delete-user") return new DeleteUserCommand();
	else if (cmd == "delete-group") return new DeleteGroupCommand();
	else if (cmd == "view-all-chats") return new ViewAllChatsCommand();
	else throw std::runtime_error("Something went wrong!");
}
