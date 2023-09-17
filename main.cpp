#include "Master.hpp"
#include "Worker.hpp"
#include "Location.hpp"

int main(int ac, char *av[])
{
	if (ac == 1 || ac == 2)
	{
		int	kqueue;
		std::vector <struct kevent> change_list;
		std::vector<Worker>	workers;
		std::map<int, int> find_fd;
		char a[100] = "bb.conf";
		try
		{
			if (ac == 1)
				conf_parse(a, workers);
			else if (ac == 2)
				conf_parse(av[1], workers);
			init(workers, kqueue, change_list);
			run(workers, kqueue, change_list, find_fd);
			// clean(workers);
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
