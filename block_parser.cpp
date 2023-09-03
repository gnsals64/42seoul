#include "block_parser.hpp"
#include "Location.hpp"
#include "Worker.hpp"

int	check_extension(std::string filename) {
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

int	check_block(std::string filename, ConfigParser *parser) {
	std::ifstream	ifs(filename, std::ifstream::in);

	if (ifs.is_open() == false)
		return (-1);
	parser->init_parserclass();
	parser->start_parsing(&ifs);
	parser->print_parse_error(filename);
	return (0);
}

void	run(std::string	filename) {
	ConfigParser	parser;
    std::vector<Worker>  workers;

	if (check_extension(filename) == -1) {
		std::cout << "File is not configuration file." << std::endl;
		return ;
	}
	if (check_block(filename, &parser) == -1) {
		std::cout << "configuration file is not vaild" << std::endl;
		return ;
	}
    for (int i = 0; i < parser.get_server().size(); i++) {
        Worker worker = set_worker_info(parser.server_[i]);
		workers.push_back(worker);
        print_worker_info(worker);
    }
}
