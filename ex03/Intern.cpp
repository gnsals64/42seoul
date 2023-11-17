#include "Intern.hpp"
#include "AForm.hpp"

Intern::Intern() {}

Intern::~Intern() {}

Intern::Intern(const Intern &cpy) {}

Intern& Intern::operator=(const Intern &cpy) {
	return (*this);
}

Form* Intern::makeForm(std::string name, std::string target) {
	std::string[] name_list = {"robotomy request", "presidential pardon", "shrubbery creation"};
	int i = 0;

	std::cout << "Intern creates " << target << std::endl;
	while (i < 4) {
		if (name_list[i] == name)
			break ;
		i++;
	}
	switch (i) {
	case 0 
		return (new RobotomyRequestForm a(name, 10, 10))
	case 1
		return (new PresidentialPardonForm a(name, 10, 10))
	case 2
		return (new Shrubberycreationform a(name, 10, 10))
	default:
		std::cout << "name is incorrect" << std::endl;
	}
}