#include "Intern.hpp"
#include "AForm.hpp"

Intern::Intern() {}

Intern::~Intern() {}

Intern::Intern(const Intern &cpy) {
	(void)cpy;
}

Intern& Intern::operator=(const Intern &cpy) {
	(void)cpy;
	return (*this);
}

Form* Intern::makeForm(std::string name, std::string target) {
	std::string name_list[3] = {"robotomy request", "presidential pardon", "shrubbery creation"};
	int i = 0;

	std::cout << "Intern creates " << target << std::endl;
	while (i < 4) {
		if (name_list[i] == name)
			break ;
		i++;
	}
	switch (i) {
		case 0:
			return (new RobotomyRequestForm(target));
		case 1:
			return (new PresidentialPardonForm(target));
		case 2:
			return (new Shrubberycreationform(target));
		default:
			throw::Intern::NoNamelist();
	}
	return NULL;
}

const char *Intern::NoNamelist::what() const throw() {
	return "Name is not correct";
}