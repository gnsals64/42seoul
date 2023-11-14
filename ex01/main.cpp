#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	try {
		Bureaucrat 	a("a", 5);
		Form		form("form", 10, 5);
		
		form.beSigned(a);
		a.signForm(form);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}