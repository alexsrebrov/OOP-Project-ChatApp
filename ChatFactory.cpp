#include "ChatFactory.h"

Chat* ChatFactory::createChat(ChatType type, const String& input1, const String& input2) const
{
	switch (type)
	{
	case ChatType::Dm:
		return new Dm(input1,input2);
	case ChatType::Group:
		return new Group(input1,input2);
	}
}
