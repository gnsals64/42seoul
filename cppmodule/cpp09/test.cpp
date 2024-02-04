#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>

int main() {
	std::tm t{};
	t.tm_year = 2020 - 1900;
	t.tm_mday = 32;
	t.tm_mon = 2;
	std::mktime(&t);
	std::cout << std::asctime(&t);

}
