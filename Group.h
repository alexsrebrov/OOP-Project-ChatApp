#pragma once
#include "Chat.h"

class Group : public Chat
{
public:


	Group(const String& groupName,const String& creator);
	~Group() = default;

	Chat* clone() const override;
	ChatType getChatType() const override;
	const String& getChatName(const String& username) const override;

	void addUser(const String& username,const String& toAdd) override;
	void removeUser(const String& username) override;
	void groupStats() const override;
	void seetRequests() const override;
	void setAdmin(const String& username) override;
	void makeChatPrivate() override;

	bool isInChat(const String& username) override;
	RoleType getUserRoleInChat(const String& username) override;
private:
	String groupName;
	MyVector<ChatParticipant> participants;
	MyVector<String> requests;
	bool isGroupPrivate = false;
	void getTopContributor() const;
};


