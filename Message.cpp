#include "Message.h"
#include <iostream>
#pragma warning(disable:4996)


Message::Message(const String & sender, const String & content)
: sender(sender),content(content)
{
	messTime = time(nullptr);
}

const String& Message::getSender() const
{
	return sender;
}

std::ostream& operator<<(std::ostream& os, const Message& mes)
{
	tm* t = localtime(&mes.messTime);
	os << "[" << mes.sender << ",";
	mes.printDate(os, t);
	mes.printTime(os,t);
	os << " " << mes.content;
	return os;
}

void Message::printTime(std::ostream& os, tm* time) const
{
	(time->tm_hour < 10) ? os << '0' << time->tm_hour : os << time->tm_hour;
	os << ":";
	(time->tm_min < 10) ? os << '0' << time->tm_min : os << time->tm_min;
	os << "]";
}

void Message::printDate(std::ostream& os, tm* time) const
{
	(time->tm_mday < 10) ? os << '0' << time->tm_mday : os << time->tm_mday;
	os << '/';
	(time->tm_mon < 9) ? os << '0' << time->tm_mon + 1 : os << time->tm_mon + 1;
	os << '/';
	os << time->tm_year + 1900 << " ";
}
