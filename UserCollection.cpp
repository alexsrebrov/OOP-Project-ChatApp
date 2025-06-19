#include "UserCollection.h"
#include "Admin.h"
#include "NormalUser.h"
static constexpr size_t START_CAPACITY = 10;
static constexpr char usersBin[] = "users.bin";
static constexpr char usersTxt[] = "users.txt";

UserCollection::UserCollection()
{
	size = 0;
	capacity = START_CAPACITY;
	users = new User * [capacity];
}

UserCollection::UserCollection(const UserCollection& other)
{
	copyFrom(other);
}

UserCollection& UserCollection::operator=(const UserCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

UserCollection::UserCollection(UserCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

UserCollection& UserCollection::operator=(UserCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

UserCollection::~UserCollection()
{
	free();
}

size_t UserCollection::getSize() const
{
	return size;
}

bool UserCollection::validateLogin(const String& username, const String& password)
{
	size_t idx = find(username);
	return users[idx]->checkPassword(password);
}

void UserCollection::add(User* add)
{
	if (!isUsernameFree(add->getUsername()))
		throw std::runtime_error("Username already taken!");

	if (size >= capacity) resize(capacity * 2);
	users[size++] = add;
}

void UserCollection::remove(const String& username)
{
	if (isEmpty()) return;
	size_t idx = find(username);
	std::swap(users[idx], users[--size]);
	delete users[size];
}

void UserCollection::changePassword(const String& username,
				const String& oldPass,const String& newPass)
{
	size_t idx = find(username);
	users[idx]->changePassword(oldPass, newPass);
}

void UserCollection::addMessage(const String& username, size_t chatID)
{
	size_t idx = find(username);
	users[idx]->addMessage(chatID);
}

void UserCollection::seeChat(const String& username, size_t chatID)
{
	size_t idx = find(username);
	users[idx]->seeChat(chatID);
}

size_t UserCollection:: getUnread(const String& username, size_t chatId) const
{
	size_t idx = find(username);
	return users[idx]->getUnread(chatId);
}

const User* UserCollection::operator[](size_t index) const
{
	if (index < 0 || index >= size) 
		throw std::runtime_error("Index out of bounds");
	
	return users[index];
}

User* UserCollection::operator[](size_t index)
{
	if (index < 0 || index >= size)
		throw std::runtime_error("Index out of bounds");

	return users[index];
}

bool UserCollection::isEmpty() const
{
	return !size;
}

void UserCollection::resize(size_t newCap)
{
	if (newCap < capacity) newCap = capacity * 2;
	User** res = new User * [newCap];
	for (size_t i = 0; i < capacity; i++)
	{
		res[i] = users[i]->clone();
		delete users[i];
	}
	delete[]users;
	users = res;
	capacity = newCap;
}

void UserCollection::copyFrom(const UserCollection& other)
{
	capacity = other.capacity;
	size = other.size;
	if (size >= capacity) capacity = size;
	users = new User * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		users[i] = other.users[i]->clone();
	}
}

void UserCollection::moveFrom(UserCollection&& other)
{
	capacity = other.capacity;
	size = other.size;
	users = other.users;
	other.users = nullptr;
}

void UserCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete users[i];
	}
	delete users;
}

bool UserCollection::isUsernameFree(const String& username) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (username == users[i]->getUsername()) return false;
	}
	return true;
}

size_t UserCollection::find(const String& username) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (username == users[i]->getUsername()) return i;
	}
	throw std::invalid_argument("User not found!");
}

void UserCollection::serializeTxt()
{
	std::ofstream ofs(usersTxt, std::ios::out);
	if (!ofs.is_open())
	{
		std::cout << "Couldn't save!";
		return;
	}
	ofs << size << "\n";
	for (size_t i = 0; i < size; i++)
	{
		ofs << (int)users[i]->getUserType()<<"\n";
		users[i]->serializeTxt(ofs);
	}
	ofs.close();
}

void UserCollection::serializeBin()
{
	std::ofstream ofs(usersBin, std::ios::out|std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Couldn't save!";
		return;
	}
	ofs.write((const char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		ofs.write((const char*)users[i]->getUserType(), sizeof(UserType));
		users[i]->serializeBin(ofs);
	}
	ofs.close();
}

void UserCollection::deserializeTxt()  
{  
	std::ifstream ifs(usersTxt, std::ios::in);  
	if (!ifs.is_open())  
	{  
		std::cout << "Couldn't save!";  
		return;  
	}  
	ifs >> size;  
	int type;  
	for (size_t i = 0; i < size; i++)  
	{  
		ifs >> type;  
		if (type == static_cast<int>(UserType::Admin))  
		{  
			Admin* a;
			users[i] = a->deserializeTxt(ifs);
		}  
		else if (type == static_cast<int>(UserType::NormalUser))  
		{  
			NormalUser* a;
			users[i] = a->deserializeTxt(ifs);
		}  
	}  
	ifs.close();  
}


void UserCollection::deserializeBin()
{
	std::ifstream ifs(usersTxt, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "Couldn't save!";
		return;
	}
	ifs.read((char*)*&size;
	int type;
	for (size_t i = 0; i < size; i++)
	{
		ifs >> type;
		if (type == static_cast<int>(UserType::Admin))
		{
			Admin* a;
			users[i] = a->deserializeBin(ifs);
		}
		else if (type == static_cast<int>(UserType::NormalUser))
		{
			NormalUser* a;
			users[i] = a->deserializeBin(ifs);
		}
	}
	ifs.close();
}
