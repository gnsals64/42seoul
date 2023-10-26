#include "Bureaucrat.hpp" 

void	Run(Bureaucrat &a) {
	std::cout << a.getName() << "'s grade is " << a.getGrade() << std::endl;
	std::cout << "You can use '+' or '-'" << std::endl;
	while (true) {
		char c;

		std::cin >> c;
		if(c == '+')
			a.IncreasingGrade();
		else if (c == '-')
			a.DecreasingGrade();
		else {
			std::cout << "You can use '+' or '-'" << std::endl;
			continue ;
		}
		a.CheckArgument();
		std::cout << a.getName() << "'s grade is " << a.getGrade() << std::endl;
	}
}

int	CheckArgv(int ac, char **av){
	if (ac != 3) {
		std::cerr << "error" << std::endl;
		return 1;
	}

	for (unsigned long i = 0; i < strlen(av[2]); i++) {
		if (i == 0 && (av[2][i] == '-' || av[2][i] == '+'))
			continue ;
		if (isdigit(av[2][i]) == 0 || i > 8) {
			std::cerr << "error" << std::endl;
			return 1;
		}
	}
	return 0;
}

int main(int ac, char **av) {
	if (CheckArgv(ac, av) == 1)
		return 1;

	int	grade = atoi(av[2]);

	try {
		Bureaucrat a(av[1], grade);
		Run(a);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}