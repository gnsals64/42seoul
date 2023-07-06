#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl	ha;

	if (ac != 2)
	{
		std::cout << "argc is not 2" << std::endl;
		return (1);
	}
	ha.complain(av[1]);
	return (0);
}
