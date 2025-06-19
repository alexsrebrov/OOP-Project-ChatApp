#include "Admin.h"

size_t Admin::adminIDCreator = 0;

void Admin::serializeTxt(std::ofstream& ofs)
{
	ofs << getUsername() <<"\n";
	ofs << getPass() << "\n";
	ofs << adminIDCreator << "\n";
	ofs << adminID << "\n";
	ofs << userChats.getSize() << "\n";
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		ofs << userChats[i].getChatID() << "\n";
		ofs << userChats[i].getUnread() << "\n";
	}
}

void Admin::serializeBin(std::ofstream& ofs)
{
	getUsername().serialize(ofs);
	getPass().serialize(ofs);
	ofs.write((const char*)&adminIDCreator, sizeof(size_t));
	ofs.write((const char*)&adminID, sizeof(size_t));
	ofs.write((const char*)userChats.getSize(), sizeof(size_t));
	for (size_t i = 0; i < userChats.getSize(); i++)
	{
		ofs.write((const char*)userChats[i].getChatID(), sizeof(size_t));
		ofs.write((const char*)userChats[i].getUnread(), sizeof(size_t));
	}
}

User* Admin::deserializeTxt(std::ifstream& ifs)
{
	String username, pass;
	ifs >> username >> pass;
	size_t amdinID, adminIdCreator, chatsCnt;
	ifs >> adminIDCreator >> adminID >>chatsCnt;
	Admin a(username, pass);
	a.adminID = adminID;
	a.adminIDCreator = adminIDCreator;
	size_t chatId, unread;
	for (size_t i = 0; i < chatsCnt; i++)
	{
		ifs >> chatId >> unread;
		a.userChats.add(UserChatInfo(chatId,unread));
	}
	return &a;
}

User* Admin::deserializeBin(std::ifstream& ifs)
{
	String username, pass;
	username.deserialize(ifs);
	pass.deserialize(ifs);
	size_t amdinID, adminIdCreator, chatsCnt;
	ifs.read((char*)&adminID, sizeof(size_t)); 
	ifs.read((char*)&adminIDCreator, sizeof(size_t)); 
	ifs.read((char*)&chatsCnt, sizeof(size_t)); 
	Admin a(username, pass);
	a.adminID = adminID;
	a.adminIDCreator = adminIDCreator;
	size_t chatId, unread;
	for (size_t i = 0; i < chatsCnt; i++)
	{
		ifs.read((char*)&chatId, sizeof(size_t)); 
		ifs.read((char*)&unread, sizeof(size_t));
		a.userChats.add(UserChatInfo(chatId, unread));
	}
	return &a;
}

Admin::Admin(const String& username, const String& password)
	: User(username,password)
{
	adminID = adminIDCreator++;
}

UserType Admin::getUserType() const
{
	return UserType::Admin;
}

User* Admin::clone() const
{
	return new Admin(*this);
}
