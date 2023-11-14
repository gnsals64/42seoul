#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public Form {
	public:
		PresidentialPardonForm();
		~PresidentialPardonForm();
		PresidentialPardonForm(std::string name, int grade_to_sign, int grade_to_execute);
		PresidentialPardonForm(const PresidentialPardonForm& cpy);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& cpy);
		void execute(Bureaucrat const &executor) const;
};

#endif