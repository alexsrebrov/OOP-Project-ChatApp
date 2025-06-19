#include "UsersDb.h"

UserFactory* UsersDb::factory = new UserFactory();
UsersDb::UsersDb() : users()
{
	
}

UsersDb::~UsersDb()
{
	
}

bool UsersDb::isUserReal(const String& username) const
{
	try
	{
		users.find(username);
	}
	catch (const std::exception& e)
	{
		std::cout << "User "<<username << "not found!" << std::endl;
		return false;
	}
	return true;
}

bool UsersDb::validateLogin(const String& username, const String& password)
{
	try
	{
		if (users.validateLogin(username, password))
		{
			std::cout << "Welcome, " << username << "!\n";
			return true;
		}
	}
	catch (const std::exception&)
	{
		std::cout << "Account not found. Create?(y/n) ";
		shouldAdd(username, password);
		return false;
	}
	std::cout << "Wrong password!\n";
	return false;
}

void UsersDb::add(UserType type, const String& username, const String& password)
{
	try
	{
		users.add(factory->createUser(type,username,password));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what()<<std::endl;
		return;
	}
	std::cout << "Account created!\n";
}

void UsersDb::remove(const String& username)
{
	try
	{
		users.remove(username);
	}
	catch (const std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
		return;
	}
	std::cout << "User " << username << " deleted!\n";
}

UserType UsersDb::getUserType(const String& username) const
{
	return users[users.find(username)]->getUserType();
}

size_t UsersDb::getSize() const
{
	return users.getSize();
}

const User* UsersDb::operator[](size_t idx) const
{
	return users[idx];
}

void UsersDb::changePassword(const String& username, const String& oldPass, const String& newPass)
{
	try
	{
		users.changePassword(username, oldPass, newPass);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what()<<std::endl;
		return;
	}
	std::cout << "Password changed!\n";
}

void UsersDb::addMessage(const String& username, size_t chatID)
{
	if (!isUserReal(username)) return;
	try
	{
		users.addMessage(username, chatID);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what()<<std::endl;
		return;
	}
}

void UsersDb::seeChat(const String& username, size_t chatID)
{
	if (!isUserReal(username)) return;
	try
	{
		users.seeChat(username, chatID);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}

void UsersDb::printUserUnread(const String& username, size_t chatId) const
{
	try
	{
		std::cout<<"( "<<
			users.getUnread(username, chatId)<<" unread)";

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}

void UsersDb::serializeTxt()
{
	users.serializeTxt();
}

void UsersDb::serializeBin()
{
	users.serializeBin();
}

void UsersDb::deserializeTxt()
{
	users.deserializeTxt();
}

void UsersDb::deserializeBin()
{
	users.deserializeBin();
}



void UsersDb::shouldAdd(const String& username, const String& password)
{
	String input;
	std::cin>>input;
	bool res = (input =="y" || input == "Y");
	if (res)
	{
		std::cout << "Choose role type (admin/user): ";
		std::cin >> input;
		if (input == "amdin" || input == "ADMIN")
			add(UserType::Admin, username, password);
		else if (input == "user" || input == "USER")
			add(UserType::NormalUser, username, password);
	}
}
