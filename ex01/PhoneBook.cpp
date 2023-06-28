#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){
	return ;
}

PhoneBook::~PhoneBook(){
	return ;
}

void	PhoneBook::AddContact(){
	std::string	buf;

	std::cout << "Firstname : ";
	std::cin >> buf;
	this->table_contact[this->index % 8].WriteFirstName(buf);
	std::cout << "Lastname : ";
	std::cin >> buf;
	this->table_contact[this->index % 8].WriteLastName(buf);
	std::cout << "Nickname : ";
	std::cin >> buf;
	this->table_contact[this->index % 8].WriteNickName(buf);
	std::cout << "Phonenumber : ";
	std::cin >> buf;
	this->table_contact[this->index % 8].WritePhoneNumber(buf);
	std::cout << "Darkestsecret : ";
	std::cin >> buf;
	this->table_contact[this->index % 8].WriteDarkestSecret(buf);
	PhoneBook::table_contact[this->index % 8].SetIndex(this->index + 1);
	this->index++;
}

void	PhoneBook::SearchContact(){
	PhoneBook::PrintHead();
	PhoneBook::PrintTable();
	PhoneBook::PrintIndexInfo();
};

void	PhoneBook::PrintHead(){
	std::cout << "|" << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "Firstname" << "|";
	std::cout << std::setw(10) << "Lastname" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
}

void	PhoneBook::PrintTable(){
	int	i;

	i = 0;
	while (i < 8 && i < this->index)
	{
		PhoneBook::PrintRow(PhoneBook::table_contact[i]);
		i++;
	}
}

void	PhoneBook::PrintRow(Contact table){
	std::cout << "|";
	if (table.GetIndex().length() > 10)
		std::cout << std::setw(10) << table.GetIndex().substr(0, 9) + "." << "|";
	else
		std::cout << std::setw(10) << table.GetIndex() << "|";
	if (table.GetFirstName().length() > 10)
		std::cout << std::setw(10) << table.GetFirstName().substr(0, 9) + "." << "|";
	else
		std::cout << std::setw(10) << table.GetFirstName() << "|";
	if (table.GetLastName().length() > 10)
		std::cout << std::setw(10) << table.GetLastName().substr(0, 9) + "." << "|";
	else
		std::cout << std::setw(10) << table.GetLastName() << "|";\
	if (table.GetNickName().length() > 10)
		std::cout << std::setw(10) << table.GetNickName().substr(0, 9) + "." << "|";
	else
		std::cout << std::setw(10) << table.GetNickName() << "|";
	std::cout << std::endl;
}

void PhoneBook::PrintIndexInfo(){
	
}
