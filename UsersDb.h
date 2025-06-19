#pragma once
#include "UserCollection.h"
#include "UserFactory.h"

class UsersDb
{
public:

	void printAll() const
	{
		std::cout << "----------USERS----------\n";
		for (size_t i = 0; i < users.getSize(); i++)
		{
			std::cout << users[i]->getUsername() << ", ";
		}
		std::cout << "\n--------------------------\n";
	}


	UsersDb();
	~UsersDb();

	bool validateLogin(const String& username, const String& password);
	void add(UserType type, const String& username, const String& password);
	void remove(const String& username);
	UserType getUserType(const String& username) const;
	size_t getSize() const;
	const User* operator[](size_t idx) const;
	bool isUserReal(const String& username) const;

	void changePassword(const String& username, const String& oldPass, const String& newPass);
	void addMessage(const String& username,size_t chatID);
	void seeChat(const String& username,size_t chatID);
	void printUserUnread(const String& username, size_t chatId) const;

	void serializeTxt();
	void serializeBin();
	void deserializeTxt();
	void deserializeBin();
private:
	UserCollection users;
	static UserFactory* factory;

	void shouldAdd(const String& username, const String& password);
};