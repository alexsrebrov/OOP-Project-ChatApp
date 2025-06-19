#pragma once
#include "String.h"
#include "MyVector.hpp"
#include "UserChatInfo.h"

enum class UserType
{
	Admin,NormalUser
};



class User
{
public:
	User(const String& username, const String& password);
	virtual ~User() = default;

	virtual void serializeTxt(std::ofstream& ofs) = 0;
	virtual void serializeBin(std::ofstream& ofs) = 0;
	virtual User* deserializeTxt(std::ifstream& ifs) = 0;
	virtual User* deserializeBin(std::ifstream& ifs) = 0;
	void changePassword(const String& oldPass, const String& newPass);
	size_t getUnread(size_t chatId) const;
	bool checkPassword(const String& pass);
	void addMessage(size_t chatID);
	void seeChat(size_t chatID);
	const String& getUsername() const;

	virtual UserType getUserType() const = 0;
	virtual User* clone() const = 0;
protected:
	const String& getPass() const;
	MyVector<UserChatInfo> userChats;
private:
	String username;
	String password;
};
