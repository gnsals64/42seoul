#include "ScavTrap.hpp"

int main() {
	ScavTrap a("a");
	ScavTrap b = a;

	std::cout << "\n";
	a.attack("B");
	a.takeDamage(10);
	a.beRepaired(1);
	a.guardGate();
	b.attack("B");
	std::cout << "\n";
}
