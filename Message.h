#pragma once
#include "String.h"

class Message
{
public:
	Message() =default;
	Message(const String& sender,const String& content);
	~Message() = default;

	friend std::ostream& operator<<(std::ostream& os, const Message& mes);
	const String& getSender() const;

private:
	String sender;
	String content;
	time_t messTime = NULL;
	void printTime(std::ostream& os, tm* time) const;
	void printDate(std::ostream& os, tm* time) const;
};