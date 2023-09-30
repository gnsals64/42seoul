#include "Bureaucrat.hpp" 

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "error" << std::endl;
		return 1;
	}

	for (int i = 0; i < strlen(av[2]); i++) {
		if (i == 0 && (av[2][i] == '-' || av[2][i] == '+'))
			continue ;
		if (isdigit(av[2][i]) == 0 || i > 8) {
			std::cerr << "error" << std::endl;
			return 1;
		}
	}
	
	int	grade = atoi(av[2]);
	Bureaucrat a(av[1], grade);
	try {
		a.CheckArgument();
	} catch (std::string& s) {
		if (s == "high")
			a.GradeTooHighException();
		else if (s == "low")
			a.GradeTooLowException();
	}
	while (true) {
		std::string	cmd;
		std::cout << "Name : " << a.getName() << std::endl;
		std::cout << "Grade : " << a.getGrade() << "\n" << std::endl;
		std::cin >> cmd;
		if (cmd == "+")
			a.IncreasingGrade();
		else if (cmd == "-")
			a.DecreasingGrade();
		try {
			a.CheckArgument();
		} catch (std::string& s) {
			if (s == "high")
				a.GradeTooHighException();
			else if (s == "low")
				a.GradeTooLowException();
		}
	}
}