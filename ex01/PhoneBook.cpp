#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){
	return ;
}

PhoneBook::~PhoneBook(){
	return ;
}

void	PhoneBook::AddContact(){
	std::string	buf;

	std::cout << "Firstname is ...> ";
	std::cin >> buf;
	this->table_contact[this->index].WriteFirstName(buf);
	std::cout << "Lastname is ...> ";
	std::cin >> buf;
	this->table_contact[this->index].WriteLastName(buf);
	std::cout << "Nickname is ...> ";
	std::cin >> buf;
	this->table_contact[this->index].WriteNickName(buf);
	std::cout << "Phonenumber is ...> ";
	std::cin >> buf;
	this->table_contact[this->index].WritePhoneNumber(buf);
	std::cout << "Darkestsecret is ...> ";
	std::cin >> buf;
	this->table_contact[this->index].WriteDarkestSecret(buf);
}
