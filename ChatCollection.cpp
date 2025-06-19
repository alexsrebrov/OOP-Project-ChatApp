#include "ChatCollection.h"
#include "Dm.h"
#include "Group.h"

static constexpr size_t START_CAPACITY = 10;

static constexpr char chatsBin[] = "chats.bin";
static constexpr char chatsTxt[] = "chats.txt";

void ChatCollection::serializeTxt()
{
	std::ofstream ofs(chatsTxt, std::ios::out);
	if (!ofs.is_open())
	{
		std::cout << "Couldn't save!";
		return;
	}
	ofs << size << "\n";
	for (size_t i = 0; i < size; i++)
	{
		ofs << (int)chats[i]->getChatType() << "\n";
		chats[i]->serializeTxt(ofs);
	}
	ofs.close();
}

void ChatCollection::serializeBin()
{
	std::ofstream ofs(chatsBin, std::ios::out | std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Couldn't save!";
		return;
	}
	ofs.write((const char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		ofs.write((const char*)chats[i]->getChatType(), sizeof(ChatType));
		chats[i]->serializeBin(ofs);
	}
	ofs.close();
}

void ChatCollection::deserializeTxt()
{
	std::ifstream ifs(chatsTxt, std::ios::in);
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
		if (type == static_cast<int>(ChatType::Dm))
		{
			Dm* a;
			chats[i] = a->deserializeTxt(ifs);
		}
		else if (type == static_cast<int>(ChatType::Group))
		{
			Group* a;
			chats[i] = a->deserializeTxt(ifs);
		}
	}
	ifs.close();
}

void ChatCollection::deserializeBin()
{
	std::ifstream ifs(chats, std::ios::in);
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
		if (type == static_cast<int>(ChatType::Dm))
		{
			Dm* a;
			chats[i] = a->deserializeBin(ifs);
		}
		else if (type == static_cast<int>(ChatType::Group))
		{
			Group* a;
			chats[i] = a->deserializeBin(ifs);
		}
	}
	ifs.close();
}



ChatCollection::ChatCollection()
{
	size = 0;
	capacity = START_CAPACITY;
	chats = new Chat * [capacity];
}

ChatCollection::ChatCollection(const ChatCollection& other)
{
	copyFrom(other);
}

ChatCollection& ChatCollection::operator=(const ChatCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ChatCollection::ChatCollection(ChatCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

ChatCollection& ChatCollection::operator=(ChatCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ChatCollection::~ChatCollection()
{
	free();
}

void ChatCollection::addChat(Chat* add)
{
	if (size >= capacity) resize(capacity * 2);
	chats[size++] = add;
}

void ChatCollection::removeChat(size_t chatId)
{
	if (isEmpty()) return;
	size_t idx = find(chatId);
	std::swap(chats[idx], chats[--size]);
	delete chats[size];
}

void ChatCollection::selectChat(const String& username,size_t chatId)
{
	size_t idx = find(chatId);
	if (!chats[idx]->isInChat(username)) throw std::runtime_error("User not in group");
	std::cout << chats[idx]->getChatName(username) << ": \n";
	chats[idx]->seeMessages();
	std::cout << "\nEnter message: ";
	String input;
	std::cin >> input;
	if (input != "\n") chats[idx]->addMessage(Message(username, input));
}

void ChatCollection::addUser(const String& username, const String& toAdd, size_t chatId)
{
		chats[find(chatId)]->addUser(username, toAdd);
}

void ChatCollection::removeUser(const String& username, size_t chatId)
{
	chats[find(chatId)]->removeUser(username);
}

void ChatCollection::setAdmin(const String& username, size_t chatId)
{
	chats[find(chatId)]->setAdmin(username);
}

void ChatCollection::groupStats(size_t chatId)
{
	chats[find(chatId)]->groupStats();
}

void ChatCollection::addMessage(const Message& message, size_t chatId)
{
	chats[find(chatId)]->addMessage(message);
}

RoleType ChatCollection::getRoleInChat(const String& username, size_t chatId)
{
	return chats[find(chatId)]->getUserRoleInChat(username);
}

const String& ChatCollection::getChatName(const String& username,size_t chatId) const
{
	return chats[find(chatId)]->getChatName(username);
}

size_t ChatCollection::getChatId(const String& chatName)
{
	for (size_t i = 0; i < size; i++)
	{
		if (chats[i]->getChatName("") == chatName) return chats[i]->getChatId();
	};
}

void ChatCollection::viewUserChats(const String& username,const UsersDb& users) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (chats[i]->isInChat(username))
		{
			std::cout << chats[i]->getChatName(username);
			users.printUserUnread(username, chats[i]->getChatId());
			std::cout << "\n";
		}
	}
}


const Chat* ChatCollection::operator[](size_t index) const
{
	if (index < 0 || index >= size)
		throw std::runtime_error("Index out of bounds");

	return chats[index];
}

Chat* ChatCollection::operator[](size_t index)
{
	if (index < 0 || index >= size)
		throw std::runtime_error("Index out of bounds");

	return chats[index];
}

bool ChatCollection::isEmpty() const
{
	return !size;
}

size_t ChatCollection::find(size_t chatId) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (chats[i]->getChatId() == chatId) return i;
	}
	throw std::runtime_error("Chat not found");
}

void ChatCollection::resize(size_t newCap)
{
	if (newCap < capacity) newCap = capacity * 2;
	Chat** res = new Chat * [newCap];
	for (size_t i = 0; i < capacity; i++)
	{
		res[i] = chats[i]->clone();
		delete chats[i];
	}
	delete[]chats;
	chats = res;
	capacity = newCap;
}

void ChatCollection::copyFrom(const ChatCollection& other)
{
	capacity = other.capacity;
	size = other.size;
	if (size >= capacity) capacity = size;
	chats = new Chat* [capacity];
	for (size_t i = 0; i < size; i++)
	{
		chats[i] = other.chats[i]->clone();
	}
}

void ChatCollection::moveFrom(ChatCollection&& other)
{
	capacity = other.capacity;
	size = other.size;
	chats = other.chats;
	other.chats = nullptr;
}

void ChatCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete chats[i];
	}
	delete chats;
}

