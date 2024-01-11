#include "BitcoinExchange.hpp"

int main() {
	btc wallet;

	try {
		wallet.db_init();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}