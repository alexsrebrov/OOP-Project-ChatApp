#pragma once
#include "User.h"

class NormalUser : public User
{
public:
	void serializeTxt(std::ofstream& ofs);
	void serializeBin(std::ofstream& ofs);
	User* deserializeTxt(std::ifstream& ifs);
	User* deserializeBin(std::ifstream& ifs);

	NormalUser(const String& username,const String& password);
	~NormalUser() = default;

	UserType getUserType() const override;
	User* clone() const override;
};
