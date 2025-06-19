#include "ChatParticipant.h"

ChatParticipant::ChatParticipant(const String& name, RoleType role)
 : name(name),role(role){}

void ChatParticipant::makeAdmin()
{
	role = RoleType::Admin;
}

void ChatParticipant::makeParticipant()
{
	role = RoleType::Participant;
}

const String& ChatParticipant::getName() const
{
	return name;
}

RoleType ChatParticipant::getRole() const
{
	return role;
}

bool ChatParticipant::operator==(const ChatParticipant& other)
{
	return name == other.name;
}
