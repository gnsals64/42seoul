#include "ClapTrap.hpp"

int	main() {
	ClapTrap	A("A");
	ClapTrap	B("B");

	A.attack("B");
	A.beRepaired(5);
	A.takeDamage(5);
	B.attack("A");
	B.beRepaired(3);
	B.takeDamage(4);
	return (0);
}
