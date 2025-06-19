#pragma once
#include "User.h"

class UserCollection
{
public:

	UserCollection();
	UserCollection(const UserCollection& other);
	UserCollection& operator=(const UserCollection& other);
	UserCollection(UserCollection&& other) noexcept;
	UserCollection& operator=(UserCollection&& other) noexcept;
	~UserCollection();

	size_t getSize() const;
	bool validateLogin(const String& username, const String& password);
	void add(User* add);
	void remove(const String& username);

	void changePassword(const String& username,const String& oldPass,const String& newPass);
	void addMessage(const String& username, size_t chatID);
	void seeChat(const String& username, size_t chatID);
	size_t getUnread(const String& username,size_t chatId) const;

	const User* operator[](size_t index) const;
	User* operator[](size_t index);
	bool isEmpty() const;
	size_t find(const String& username) const;

	void serializeTxt();
	void serializeBin();
	void deserializeTxt();
	void deserializeBin();

private:
	User** users;
	size_t size;
	size_t capacity;

	void resize(size_t newCap);
	void copyFrom(const UserCollection& other);
	void moveFrom(UserCollection&& other);
	void free();

	bool isUsernameFree(const String& username) const;
};