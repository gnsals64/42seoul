#include "Worker.hpp"

void	exit_error(std::string msg)
{
	std::cerr << msg << std::endl;
	exit(1);
}

Worker set_worker_info(std::vector<std::string>& lines)
{
	Worker worker;

	//insert server tokens string : config, bool : appearance
	std::map<std::string, bool> server_tokens;
	server_tokens["listen"] = false;
	server_tokens["server_name"] = false;
	server_tokens["error_page"] = false;
	server_tokens["client_max_body_size"] = false;
	server_tokens["root"] = false;
	server_tokens["index"] = false;
	server_tokens["location"] = false;

	std::vector<std::string>::iterator lineIt;
	for (lineIt = lines.begin() + 2; lineIt != lines.end(); ++lineIt) {
		std::string line = *lineIt;

		if (line == "location")
		{
			lineIt = set_location(worker, lines, ++lineIt);
			line = *lineIt;
		}

		//find token
		std::map<std::string, bool>::iterator tokenIt;
		tokenIt = server_tokens.find(line);

		if (lineIt == lines.end() - 1 || lineIt == lines.end())
			break ;

		if (tokenIt != server_tokens.end()) {
			if (tokenIt->second && tokenIt->first != "location")
				exit_error("Error: Duplicate server token : " + line);
			else {
				lineIt = set_worker(worker, lines, lineIt);
				tokenIt->second = true;
			}
		}
		else
			exit_error("Error: Invalid server token : " + line);
	}
	return worker;
}

void parse_listen(Worker& worker, const std::string& line)
{
	std::stringstream ss(line);
	double value = 0.0;
	char suffix = '\0';

	ss >> value >> suffix;

	if (value && !suffix && value >= 0 && value <= PORT_NUM_MAX)
		worker.set_port((int)value);
	else
		exit_error("Error: invalid port");
}

void parse_error_page(Worker& worker, std::vector<std::string>& lines, std::vector<std::string>::iterator& lineIt)
{
	while (lineIt != lines.end() && (*lineIt).compare(";"))
	{
		std::stringstream ss(*lineIt);
		double value = 0.0;
		char suffix = '\0';

		ss >> value >> suffix;

		if (value && !suffix)
			worker.add_error_page((int)value, *(++lineIt));
		else
			exit_error("Error: invalid err_no");
		lineIt++;
	}
	lineIt--;
}

void parse_client_max_body_size(Worker& worker, const std::string& line)
{
	std::stringstream ss(line);
	double value = 0.0;
	char suffix = '\0';

	ss >> value >> suffix;

	if (!suffix && value)
		worker.set_client_max_body_size(value);
	else if (tolower(suffix) == 'm')
		worker.set_client_max_body_size(value * 1000000);
	else
		exit_error("[client_max_body_size] directive invalid value");
}

std::vector<std::string>::iterator set_worker(Worker& worker, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt)
{
	const std::string& line = *lineIt;

	if (line == "location")
        return --lineIt;

	if (line == "listen")
		parse_listen(worker, *(++lineIt));
	else if (line == "error_page")
		parse_error_page(worker, lines, ++lineIt);
	else if (line == "server_name")
		worker.add_server_name(*(++lineIt));
	else if (line == "client_max_body_size")
		parse_client_max_body_size(worker, *(++lineIt));
	else if (line == "root")
		worker.set_root(*(++lineIt));
	else if (line == "index")
		worker.set_index(*(++lineIt));

	lineIt++;
	if ((*lineIt) != ";")
		exit_error("Error : semicolon not exist");
	return lineIt;
}
