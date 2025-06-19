#include "String.h"
#include <iostream>
#pragma warning(disable:4996)

static constexpr size_t buffLen = 1024;
void String::free()
{
	delete[] str;
	len = 0;
}

void String::copyFrom(const String& other)
{
	len = other.len;
	str = new char[len + 1];
	strcpy(str, other.str);
}

void String::moveFrom(String&& other)
{
	len = other.len;
	str = other.str;
	other.str = nullptr;
}


String::String()
{
	len = 0;
	str = new char[len + 1];
	strcpy(str, "");
}

String::String(const char* str)
{
	len = strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String::String(String&& other)
{
	moveFrom(std::move(other));
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

String::~String()
{
	free();
}

size_t String::getLen() const
{
	return len;
}

const char* String::c_string() const
{
	return str;
}

void String::setString(const char* str)
{
	if (str == nullptr) return;
	len = strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
}

void String::split(String& lhs, String& rhs, char del) const
{
	char* temp = new char[len + 1];
	strcpy(temp, str);
	lhs.setString(strtok(str, &del));
	rhs.setString(str + lhs.len + 1);
}

bool String::isNum() const
{
	for (size_t i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i]>'9') return false;
	}
	return true;
}

void String::serialize(std::ostream& os) const
{
	os.write((const char*)&len, sizeof(size_t));
	os.write(str, len + 1);
}

void String::deserialize(std::ifstream& ifs)
{
	size_t len = 0;
	ifs.read((char*)&len, sizeof(size_t));
	char* str = new char[len + 1];
	ifs.read(str, len + 1);
	this->len = len;
	this->setString(str);
	delete[] str;
}


String operator+(const String& lhs, const String& rhs)
{
	char buff[1024];
	return String(strcat(strcpy(buff, lhs.c_string()), rhs.c_string()));
}

bool operator==(const String& lhs, const String& rhs)
{
	return !strcmp(lhs.str, rhs.str);
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !operator==(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.str;
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[buffLen + 1];
	is >> buff;
	str = String(buff);
	return is;
}