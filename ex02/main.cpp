#include "Array.hpp"

int main() {
	Array<char> a(20);
	try {
		a[10] = 48;
		std::cout << a[10] << std::endl;
		std::cout << a.size() << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}