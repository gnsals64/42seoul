#include "BitcoinExchange.hpp"



int main(int ac, char **av) {
	btc wallet;

	if (ac != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 0;
	}
	std::string input(av[1]);
	if (input != "input.txt") {
		std::cerr << "invalid file" << std::endl;
		return 0;
	}

	try {
		wallet.db_init();
		wallet.input_check(std::string(av[1]));
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}