#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	try {
		Bureaucrat 	a("john", 5);
		Intern		i;
		Form		*f;

		f = i.makeForm("shrubbery creation", "Bender");
		f->beSigned(a);
		a.executeForm(*f);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}