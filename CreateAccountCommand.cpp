#include "CreateAccountCommand.h"

void CreateAccountCommand::execute(const String& currUser, UsersDb& users, ChatDb& chats) const
{
	String role,username,pass;
	std::cin >> username >> pass;
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	while (true)
	{
	std::cout << "Please choose you role:(admin/user)";
	std::cin >> role;
		if (role == "admin" || role == "ADMIN")
		{
			users.add(UserType::Admin, username, pass);
			return;
		}
		else if (role == "user" || role == "USER")
		{
			users.add(UserType::NormalUser, username, pass);
			return;
		}
		std::cout << "Invalid input!";
	} 
}
