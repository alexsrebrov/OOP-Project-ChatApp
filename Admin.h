#pragma once
#include "User.h"

class Admin : public User
{
public:
	void serializeTxt(std::ofstream& ofs);
	void serializeBin(std::ofstream& ofs);
	User* deserializeTxt(std::ifstream& ifs);
	User* deserializeBin(std::ifstream& ifs);

	Admin(const String& username, const String& password);
	~Admin() = default;

	UserType getUserType() const override;
	User* clone() const override;
private:
	size_t adminID;
	static size_t adminIDCreator;
};
