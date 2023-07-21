#include "ClapTrap.hpp"

int main() {
	ClapTrap a("a");
	ClapTrap b("b");
	ClapTrap c;

	c = a;
	a.attack("b");
	a.takeDamage(3);
	a.beRepaired(5);
	a.takeDamage(19);
	a.attack("b");
	a.beRepaired(10);
	b.attack("a");
	b.takeDamage(5);
	b.beRepaired(3);
	b.takeDamage(10);
	b.attack("a");
	b.beRepaired(10);
}
