#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public Form {
	public:
		PresidentialPardonForm();
		~PresidentialPardonForm();
		PresidentialPardonForm(std::string name);
		PresidentialPardonForm(const PresidentialPardonForm& cpy);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& cpy);
		void execute(Bureaucrat const &executor) const;
};

#endif