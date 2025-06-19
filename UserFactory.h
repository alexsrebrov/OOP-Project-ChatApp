#pragma once
#include "Admin.h"
#include "NormalUser.h"

class UserFactory
{
public:
	User* createUser(UserType type, const String& username, const String& password);
};
