#include "../inc/Webserv.hpp"
#include "../inc/Worker.hpp"
#include "../inc/Location.hpp"

int main(int ac, char *av[]) {
	char a[100] = "bb.conf";
	if (ac != 1 && ac != 2) {
		std::cerr << RED << "Invalid number of arguments." << RESET << std::endl;
		return 1;
	}

	Webserv	app;
	try {
		//configfile 파싱
		if (ac == 1)
			app.ConfParse(a);
		else if (ac == 2)
			app.ConfParse(av[1]);
		app.Init();
		app.Run();
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
