#include "Convert.hpp"

void	check_num(std::string param, ScalarConverter& converter) {
	int dot = 0;
	int minus = 0;
	int	num_cnt = 0;

	for (int i = 0; i < param.length(); i++) {
		if (param[i] == '.')
			dot++;
		else if (param[i] == '-')
			minus++;
		else if (isdigit(param[i]) == false)
			throw "invalid arguments";
		else
			num_cnt++;
	}
	converter.setNumcnt(num_cnt);
	if (dot != 0 && dot != 1)
		throw "invalid arguments";
	if (minus != 0 && minus != 1)
		throw "invalid arguments";
	if (minus == 1) {
		if (param[0] != '-')
			throw "invalid arguments";
	}
}

void	check_param(std::string param, ScalarConverter& converter) {
	if (param == "+inf" || param == "+inff") {
		converter.setFlag("+inf");
		return ;
	}
	else if (param == "-inf" || param == "-inff") {
		converter.setFlag("-inf");
		return ;
	}
	else if (param == "nan" || param == "nanf") {
		converter.setFlag("nan");
		return ;
	}
	if (param.back() == 'f')
		param.pop_back();
	check_num(param, converter);
}

void	check_arg(int ac, char **av, ScalarConverter& converter) {
	if (ac != 2)
		throw "usage: ./Convert parameter";
	check_param(std::string(av[1]), converter);	
}

int main(int ac, char **av){
	try {
		ScalarConverter converter;
		check_arg(ac, av, converter);
		converter.convert((std::string)av[1]);
	}
	catch (const char *s) {
		std::cerr << s << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}