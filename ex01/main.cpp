#include "Zombie.hpp"

int main()
{
	int		num = 5;
	Zombie *array = zombieHorde(num, "hunpark");

	for (int i = 0; i < num; i++){
		std::cout << "zombie " << i << " : ";
		array[i].announce();
	}
}
