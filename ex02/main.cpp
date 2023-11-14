#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	try {
		Bureaucrat 	a("john", 9);
		Shrubberycreationform form_shr("form_shr", 10, 10);
		RobotomyRequestForm form_rob("form_ro", 10, 10);
		PresidentialPardonForm form_pre("form_pre", 10, 10);

		form_shr.beSigned(a);
		form_shr.execute(a);
		form_rob.beSigned(a);
		form_rob.execute(a);
		form_pre.beSigned(a);
		form_pre.execute(a);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}