#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	try {
		Bureaucrat 	a("john", 9);
		Intern		i;
		Form		*f;

		f = i.makeForm("robotomy requet", "Bender");
		f->beSigned(a);
		a.executeForm(*f);
		// Shrubberycreationform form_shr("form_shr", 10, 10);
		// RobotomyRequestForm form_rob("form_ro", 10, 10);
		// PresidentialPardonForm form_pre("form_pre", 10, 5);

		// form_shr.beSigned(a);
		// form_rob.beSigned(a);
		// form_pre.beSigned(a);
		// a.executeForm(form_shr);
		// a.executeForm(form_rob);
		// a.executeForm(form_pre);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}