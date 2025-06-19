#pragma once
#include "Dm.h"
#include "Group.h"

class ChatFactory
{
public:
	Chat* createChat(ChatType type, const String& input1, const String& input2) const;
};

