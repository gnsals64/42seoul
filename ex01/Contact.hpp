#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <iomanip>
# include <string>

class Contact {
	private:
		std::string	firstName;
		std::string	lastName;
		std::string	nickName;
		std::string	phoneNumber;
		std::string	darkestSecret;
		std::string	index;

	public:
		Contact();
		~Contact();
		std::string	GetFirstName();
		std::string	GetLastName();
		std::string	GetNickName();
		std::string	GetPhoneNumber();
		std::string	GetDarkestSecret();
		std::string	GetIndex();
		void		WriteFirstName(std::string input);
		void		WriteLastName(std::string input);
		void		WriteNickName(std::string input);
		void		WritePhoneNumber(std::string input);
		void		WriteDarkestSecret(std::string input);
		void		SetIndex(int index);
};

#endif
