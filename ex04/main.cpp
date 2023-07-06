#include <iostream>
#include <fstream>

int	main(int ac, char **av)
{
	char		buf[256];
	std::string	s1;
	std::string	s2;
	std::string	filename;
	std::string	tmp;
	std::string::size_type	pos;

	if (ac != 4)
	{
		std::cout << "The number of arguments is wrong" << std::endl;
		return (1);
	}
	filename = av[1];
	s1 = av[2];
	s2 = av[3];
	std::ifstream	ifs(filename);
	if (ifs.fail())
	{
		std::cout << "open error" << std::endl;
		return (1);
	}
	std::ofstream	ofs(filename.append(".replace"));
	if (ofs.fail())
	{
		std::cout << "open error" << std::endl;
		return (1);
	}
	while(ifs.getline(buf, sizeof(buf)))
	{
		tmp = buf;
		pos = 0;
		while (true)
		{
			pos = tmp.find(s1, pos);
			if (pos == std::string::npos)
				break ;
			tmp.erase(pos, s1.length());
			tmp.insert(pos, s2);
		}
		ofs << tmp << std::endl;
	}
	return (0);
}
