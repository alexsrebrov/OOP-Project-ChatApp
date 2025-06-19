#pragma once
#include "String.h"

enum class RoleType
{
	Participant,Admin
};

class ChatParticipant
{
public:
	ChatParticipant() = default;
	ChatParticipant(const String& name, RoleType role);

	void makeAdmin();
	void makeParticipant();

	const String& getName() const;
	RoleType getRole() const;

	bool operator==(const ChatParticipant& other);
private:
	RoleType role = RoleType::Participant;
	String name;
};

