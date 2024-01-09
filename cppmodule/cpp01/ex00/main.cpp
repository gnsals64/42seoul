#include "Zombie.hpp"

int main()
{
	Zombie	zombie_1("hunpark");
	Zombie	*zombie_2 = newZombie("park");

	zombie_1.announce();
	zombie_2->announce();
	randomChump("foo");
	delete(zombie_2);
	return (0);
}
