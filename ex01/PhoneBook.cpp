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
	if (this->index == 0)
	{
		std::cout << "Info does not exist" << std::endl;
		return ;
	}
	PhoneBook::PrintHead();
	PhoneBook::PrintTable();
	PhoneBook::GetIndexInfo();
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

void PhoneBook::GetIndexInfo(){
	std::string			index;
	std::stringstream	stream;
	int					i;
	int					min;

	min = 1;
	std::cout << "You can choose index\n";
	while(true)
	{
		std::cout << "index > ";
		std::getline(std::cin, index);
		stream.str(index);
		stream >> i;
		stream.clear();
		if (this->index > 8)
			min = this->index - 7;
		if (std::cin.eof() == 1)
			exit(1);
		if (index == "")
			continue ;
		else if (i < min || i > this->index)
			std::cout << "wrong index\n";
		else
		{
			PhoneBook::PrintIndexInfo(i);
			break ;
		}
	}
}

void	PhoneBook::PrintIndexInfo(int i){
	std::cout << "Firstname : " << PhoneBook::table_contact[(i - 1) % 8].GetFirstName() << "\n";
	std::cout << "Lastname : " << PhoneBook::table_contact[(i - 1) % 8].GetLastName() << "\n";
	std::cout << "Nickname : " << PhoneBook::table_contact[(i - 1) % 8].GetNickName() << "\n";
	std::cout << "PhoneNumber : " << PhoneBook::table_contact[(i - 1) % 8].GetPhoneNumber() << "\n";
	std::cout << "DarkestSecret : " << PhoneBook::table_contact[(i - 1) % 8].GetDarkestSecret() << std::endl;
}
