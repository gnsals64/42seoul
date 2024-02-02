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

		clock_t deque_start = clock();
		deq.init(ac, av);
		deq.sort();
		deque_start = clock() - deque_start;

		vec.printBefore();
		vec.printAfter();

		std::cout << "Time to process a range of " << ac - 1 << " elements with std::[vector] : " << (double)vec_start / 1000 << " us" << std::endl;
		std::cout << "Time to process a range of " << ac - 1 << " elements with std::[deque] : " << (double) deque_start / 1000 << " us" << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
