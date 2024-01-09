#include "FlagTrap.hpp"

int main() {
	FlagTrap a("a");

	std::cout << "\n";
	a.attack("b");
	a.highFivesGuys();
	std::cout << "\n";
	return (0);
}
