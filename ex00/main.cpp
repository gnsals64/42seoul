#include "ClapTrap.hpp"

<<<<<<< HEAD
int main() {
	ClapTrap a("a");
	ClapTrap b("b");

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
=======
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
>>>>>>> abd886be1a70202cec27662e26718dbae19c9a19
}
