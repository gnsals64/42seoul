#include "PhoneBook.hpp"

void	start(void)
{
	std::cout << " ######   ##   ##   #####   ##   ##  #######          ######    #####    #####   ###  ##\n";
	std::cout << "  ##  ##  ##   ##  ##   ##  ###  ##   ##   #           ##  ##  ##   ##  ##   ##   ##  ##\n";
	std::cout << "  ##  ##  ##   ##  ##   ##  #### ##   ## #             ##  ##  ##   ##  ##   ##   ## ##\n";
	std::cout << "  #####   #######  ##   ##  ## ####   ####             #####   ##   ##  ##   ##   ####\n";
	std::cout << "  ##      ##   ##  ##   ##  ##  ###   ## #             ##  ##  ##   ##  ##   ##   ## ##\n";
	std::cout << "  ##      ##   ##  ##   ##  ##   ##   ##   #           ##  ##  ##   ##  ##   ##   ##  ##\n";
	std::cout << " ####     ##   ##   #####   ##   ##  #######          ######    #####    #####   ###  ##\n";
	std::cout << "\n\nYou can use three commands: add, search, and exit\n";

}

int main()
{
	std::string	cmd;
	PhoneBook	phoneBook;

	start();
	while (true)
	{
		std::cout << "command> ";
		std::getline(std::cin, cmd);
		if (cmd == "ADD" || cmd == "add")
		{
			phoneBook.AddContact();
		}
		else if (cmd == "SEARCH" || cmd == "search")
		{
			continue ;
		}
		else if (cmd == "EXIT" || cmd == "exit")
		{
			std::cout << "goodbye" << std::endl;
			break ;
		}
		else if (cmd == "")
			continue ;
		else
			std::cout << "command not found\nYou can use three commands: add, search, and exit\n";
	}
}
