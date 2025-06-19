#include "SystemDb.h"
static constexpr char savedFileType[] = "savedType.txt";


void SystemDb::load()
{
	std::ifstream ifs(savedFileType,std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "Error";
		return;
	}
	String fileType;
	std::cin >> fileType;
	if (fileType == "txt")
	{
		users.deserializeTxt();
		chats.deserializeTxt();
	}
	else if (fileType == "bin")
	{
		users.deserializeBin();
		chats.deserializeBin();
	}
	else std::cout << "Cannot load!";
}

void SystemDb::save()
{
	String fileTypeToSave;
	std::cout << "How to save system: (txt/bin): ";
	std::cin >> fileTypeToSave;
	if (fileTypeToSave == "txt")
	{
		users.serializeTxt();
		chats.serializeTxt();
		std::ofstream ofs(savedFileType, std::ios::out);
		if (!ofs.is_open())
		{
			std::cout << "Error";
			return;
		}
		ofs << "txt";
	}
	else if (fileTypeToSave == "bin")
	{
		users.serializeBin();
		chats.serializeBin();
		std::ofstream ofs(savedFileType, std::ios::out);
		if (!ofs.is_open())
		{
			std::cout << "Error";
			return;
		}
		ofs << "bin";
	}
	else std::cout << "Didn't save";
}

void SystemDb::execute()
{
	load();
	CommandFactory* fac = new CommandFactory();
	String input, currUser;
	std::cin >> input;
	while (input != "logout")
	{
		try
		{
			currUser = login(input,fac);
			Command* cmd = fac->getCommand(input, currUser);
			cmd->execute(currUser, users, chats);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}
	delete fac;
	save();
}

const String& SystemDb::login(String& input,const CommandFactory* fac)
{
	String currUser,username,pass;
	while (input != "logout")
	{
		try
		{
			if (input == "login")
			{
				std::cin >> username >> pass;
				users.validateLogin(username, pass);
				if (users.validateLogin(username, pass)) return username;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}
}
