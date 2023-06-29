#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook{
	private:
		Contact	table_contact[8];
		int		index;

	public:
		PhoneBook();
		~PhoneBook();
		void	AddContact();
		void	SearchContact();
		void	PrintHead();
		void	PrintTable();
		void	PrintRow(Contact table);
		void	GetIndexInfo();
		void	PrintIndexInfo(int i);
};

#endif
