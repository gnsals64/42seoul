#include "Pmergeme.hpp"

int main(int ac, char **av) {
	if (ac == 1) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	PmergemeV vec((ac - 1) / 2);
	PmergemeDe deq((ac - 1) / 2);

	try {
		clock_t vec_start = clock();
		vec.init(ac, av);
		vec.sort();
		vec_start = clock() - vec_start;

		clock_t list_start = clock();
		deq.init(ac, av);
		deq.sort();
		list_start = clock() - list_start;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}