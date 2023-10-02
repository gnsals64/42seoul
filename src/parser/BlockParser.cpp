#include "../../inc/BlockParser.hpp"

int	CheckExtension(std::string filename) {
	std::string	extention;
	int			index;

	index = filename.find(".");
	if (index == -1)
		return (-1);
	extention = filename.substr(index);
	if (extention.compare(".conf") != 0)
		return (-1);
	return (1);
}

int	CheckBlock(std::string filename, ConfigParser *parser) {
	std::ifstream	ifs(filename, std::ifstream::in);

	if (ifs.is_open() == false)
		return (-1);
	parser->InitParserClass();
	parser->StartParsing(&ifs);
	parser->PrintParseError(filename);
	return (0);
}