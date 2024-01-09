#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	try {
		Bureaucrat 	a("john", 5);
		Shrubberycreationform form_shr("shruberry");
		RobotomyRequestForm form_rob("robotomy");
		PresidentialPardonForm form_pre("presidential");

		form_shr.beSigned(a);
		form_rob.beSigned(a);
		form_pre.beSigned(a);

		a.executeForm(form_shr);
		a.executeForm(form_rob);
		a.executeForm(form_pre);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}