#include "Master.hpp"
#include "Worker.hpp"
#include "Location.hpp"

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int	kqueue;
		std::vector <struct kevent> change_list;
		std::vector<Worker>	workers;
		Worker	first;
		workers.push_back(first);
		try
		{
			conf_parse(av[1]);
			init(workers, kqueue, change_list);
			run(workers, kqueue, change_list);
			clean(workers);
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return (1);
	}
	return (0);
}
