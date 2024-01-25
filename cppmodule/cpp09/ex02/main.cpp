#include "Pmergeme.hpp"

int main(int ac, char **av) {
	if (ac == 1) {
		std::cerr << "Error" << std::endl;
		return 0;
	}

	Pmergeme db;

	try {
		db.init_v(ac, av);
		db.init_li(ac, av);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}