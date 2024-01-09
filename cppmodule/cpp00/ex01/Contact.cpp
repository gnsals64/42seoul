#include "Contact.hpp"

Contact::Contact(){
	return ;
}

Contact::~Contact(){
	return ;
}

std::string	Contact::GetFirstName(){
	return this->firstName;
}

std::string	Contact::GetLastName(){
	return this->lastName;
}

std::string	Contact::GetNickName(){
	return this->nickName;
}

std::string	Contact::GetPhoneNumber(){
	return this->phoneNumber;
}

std::string	Contact::GetDarkestSecret(){
	return this->darkestSecret;
}

int	Contact::GetIndex(){
	return this->index;
}

void	Contact::WriteFirstName(std::string input){
	this->firstName = input;
}

void	Contact::WriteLastName(std::string input){
	this->lastName = input;
}

void	Contact::WriteNickName(std::string input){
	this->nickName = input;
}

void	Contact::WritePhoneNumber(std::string input){
	this->phoneNumber = input;
}

void	Contact::WriteDarkestSecret(std::string input){
	this->darkestSecret = input;
}

void	Contact::SetIndex(int index){
	if (index > 25000){
		std::cout << "index full" << std::endl;
		exit(1);
	}
	this->index = index;
}

