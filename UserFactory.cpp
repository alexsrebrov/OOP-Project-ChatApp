#include "UserFactory.h"

User* UserFactory::createUser(UserType type, const String& username,
	const String& password)
{
	switch (type)
	{
	case UserType::Admin:
		return new Admin(username, password);
	case UserType::NormalUser:
		return new NormalUser(username,password);
	return nullptr;
	}
}