#include "Group.h"

Group::Group(const String& groupName, const String& creator)
	: Chat(),groupName(groupName)
{
	participants.add(ChatParticipant(creator, RoleType::Admin));
}

Chat* Group::clone() const
{
	return new Group(*this);
}

ChatType Group::getChatType() const
{
	return ChatType::Group;
}

const String& Group::getChatName(const String& username) const
{
	return groupName;
}

void Group::addUser(const String& username, const String& toAdd)
{
	if (isInChat(toAdd))
		throw std::runtime_error("User already in chat!");
	if (!isGroupPrivate) 
	{
		participants.add(ChatParticipant((toAdd), RoleType::Participant));
		return;
	}
	RoleType role = getUserRoleInChat(username);
	if (role == RoleType::Admin)
		participants.add(ChatParticipant((toAdd), RoleType::Participant));
	else if (role == RoleType::Participant)
		requests.add(toAdd);
}

void Group::removeUser(const String& username)
{
	if (getUserRoleInChat(username) == RoleType::Admin)
		throw std::runtime_error("Cannot remove admin!");
	participants.remove(ChatParticipant(username, getUserRoleInChat(username)));
}

void Group::groupStats() const
{
	std::cout << groupName << "; " << participants.getSize() << " members," << messages.getSize()
		<< " msg, Top: ";
	getTopContributor();
}

void Group::seetRequests() const
{
	for (size_t i = 0; i < requests.getSize(); i++)
	{
		std::cout << requests[i] << (i == requests.getSize() - 1 ? "" : ", ");
	}
}

void Group::setAdmin(const String& username)
{
	if (isInChat(username) && getUserRoleInChat(username) == RoleType::Participant)
	{
		participants.remove(ChatParticipant(username, RoleType::Participant));
		participants.add(ChatParticipant(username, RoleType::Admin));
	}
}

void Group::makeChatPrivate()
{
	isGroupPrivate = true;
}

bool Group::isInChat(const String& username)
{
	for (size_t i = 0; i < participants.getSize(); i++)
	{
		if (username == participants[i].getName()) return true;
	}
	return false;
}

RoleType Group::getUserRoleInChat(const String& username)
{
	if (!isInChat(username)) throw std::runtime_error("User not found");
	for (size_t i = 0; i < participants.getSize(); i++)
	{
		if (username == participants[i].getName()) return participants[i].getRole();
	}
}

void Group::getTopContributor() const
{
	size_t messCnt = 0;
	String top;
	for (size_t i = 0; i < participants.getSize(); i++)
	{
		size_t currCnt = 0;
		for (size_t j = 0; j < messages.getSize(); j++)
		{
			if (participants[i].getName() == messages[i].getSender()) currCnt++;
		}
		if (messCnt < currCnt)
		{
			messCnt = currCnt;
			top = participants[i].getName();
		}
	}
	std::cout << top << " (" << messCnt << " msg)";
}
