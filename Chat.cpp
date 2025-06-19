#include "Chat.h"

size_t Chat::chatIdcreator = 1;

Chat::Chat() : messages()
{
	chatId = chatIdcreator++;
}

size_t Chat::getChatId() const
{
	return chatId;
}

void Chat::seeMessages() const
{
	messages.printAll();
}

void Chat::addMessage(const Message& message)
{
	messages.add(message);
}

