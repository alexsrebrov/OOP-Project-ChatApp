#pragma once
#include <fstream>


class String
{
public:
	String();
	String(const char* str);
	String(const String& other);
	String& operator=(const String& other);
	String(String&& other);
	String& operator=(String&& other);
	~String();

	size_t getLen() const;
	const char* c_string() const;
	void setString(const char* str);
	void split(String& lhs, String& rhs, char del) const;
	bool isNum() const;

	void serialize(std::ostream& os) const;
	void deserialize(std::ifstream& ifs);

	friend String operator+(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);
private:
	char* str;
	size_t len;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);
};

