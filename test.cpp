#include <iostream>

int main() {
	try{
	int p = std::find(10, 20, 1);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	
}