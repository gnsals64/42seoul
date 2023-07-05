#include <iostream>
#include <fstream>

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "The number of arguments is wrong" << std::endl;
		return (1);
	}
	std::ifstream	ifs(av[1]);
	if (ifs.fail())
	{
		std::cout << "open error" << std::endl;
		return (1);
	}
	std::ofstream	ofs(av[2]);
	if (ofs.fail())
	{
		std::cout << "open error" << std::endl;
		return (1);
	}


}
