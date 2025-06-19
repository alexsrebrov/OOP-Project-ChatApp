#pragma once
#include "Chat.h"

class Dm : public Chat
{
public:


	Dm(const String& user1, const String& user2);
	~Dm() = default;

	Chat* clone() const override;
	ChatType getChatType() const override;
	const String& getChatName(const String& username) const override;

	void addUser(const String& username, const String& toAdd) override;
	void removeUser(const String& username) override;
	void groupStats() const override;
	void seetRequests() const override;
	void setAdmin(const String& username) override;
	void makeChatPrivate() override;

	bool isInChat(const String& username) override;
	RoleType getUserRoleInChat(const String& username) override;

private:
	ChatParticipant user1;
	ChatParticipant user2;
};



