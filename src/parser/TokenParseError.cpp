#include "../../inc/BlockParser.hpp"

int		ConfigParser::PrintParseError(std::string filename){
	if (get_errorbit()) {
		if (get_errorline() == -1)
			std::cout << "error" << std::endl;
		else if (get_errorbit() == 2)
			std::cout << "\"http\" directive is not allowed here in " << filename << ":" << get_errorline() << std::endl;
		else if (get_errorbit() == 3)
			std::cout << "\"server\" directive is not allowed here in " << filename << ":" << get_errorline() << std::endl;
		else if (get_errorbit() == 4)
			std::cout << "\"location\" directive is not allowed here in " << filename << ":" << get_errorline() << std::endl;
		else
			std::cout << filename << " line " << get_errorline() << " error" << std::endl;
		return (-1);
	}
	if (check_.http_ == true || check_.server_ == true || check_.location_ == true) {
		std::cout << "error" << std::endl;
		return (-1);
	}
	return (0);
}
