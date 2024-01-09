#include "easyfind.hpp"

int main() {
	std::vector<int> v;

	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	try {
		std::cout << *easyfind(v, 9) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}