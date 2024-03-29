#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "argv error" << std::endl;
		return 0;
	}

	Rpn cal;

	try {
		cal.init(std::string(av[1]));
		cal.start();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
