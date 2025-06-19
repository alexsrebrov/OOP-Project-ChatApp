#include "NormalUser.h"

void NormalUser::serializeTxt(std::ofstream& ofs)
{
	ofs << getUsername() << "\n";
	ofs << getPass() << "\n";
	ofs << userChats.getSize() << "\n";
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		ofs << userChats[i].getChatID() << "\n";
		ofs << userChats[i].getUnread() << "\n";
	}
}

void NormalUser::serializeBin(std::ofstream& ofs)
{
	getUsername().serialize(ofs);
	getPass().serialize(ofs);
	ofs.write((const char*)userChats.getSize(), sizeof(size_t));
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		ofs.write((const char*)userChats[i].getChatID(), sizeof(size_t));
		ofs.write((const char*)userChats[i].getUnread(), sizeof(size_t));
	}
}

User* NormalUser::deserializeTxt(std::ifstream& ifs)
{
	String username, pass;
	ifs >> username >> pass;
	size_t amdinID, adminIdCreator, chatsCnt;
	NormalUser a(username, pass);
	size_t chatId, unread;
	for (size_t i = 0; i < chatsCnt; i++)
	{
		ifs >> chatId >> unread;
		a.userChats.add(UserChatInfo(chatId, unread));
	}
	return &a;
}

User* NormalUser::deserializeBin(std::ifstream& ifs)
{
	String username, pass;
	username.deserialize(ifs);
	pass.deserialize(ifs);
	size_t amdinID, adminIdCreator, chatsCnt;
	ifs.read((char*)&chatsCnt, sizeof(size_t));
	NormalUser a(username, pass);
	size_t chatId, unread;
	for (size_t i = 0; i < chatsCnt; i++)
	{
		ifs.read((char*)&chatId, sizeof(size_t));
		ifs.read((char*)&unread, sizeof(size_t));
		a.userChats.add(UserChatInfo(chatId, unread));
	}
	return &a;
}

NormalUser::NormalUser(const String& username, const String& password)
 : User(username,password){}

UserType NormalUser::getUserType() const
{
	return UserType::NormalUser;
}

User* NormalUser::clone() const
{
	return new NormalUser(*this);
}
