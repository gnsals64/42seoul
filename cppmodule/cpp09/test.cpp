#include <iostream>
#include <fstream>

int main() {
	std::ifstream file;
	file.open("data.csv");
	if (file.is_open()) {
		while (!file.eof()) {
			std::string str;
			getline(file, str);
			std::cout << str << std::
		}
	}
}