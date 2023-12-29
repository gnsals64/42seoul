#include "Array.hpp"

int main() {
	Array<int> a(20);
	try {
		std::cout << a[0] << std::endl;
		std::cout << a.size() << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}