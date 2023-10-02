#include "../../inc/Worker.hpp"

void	exitError(std::string msg) {
	std::cerr << msg << std::endl;
	exit(1);
}

Worker setWorker_info(std::vector<std::string>& lines) {
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
		
		if (line == "location") {
			lineIt = setLocation(worker, lines, ++lineIt);
			line = *lineIt;
		}

		//find token
		std::map<std::string, bool>::iterator tokenIt;
		tokenIt = server_tokens.find(line);

		if (lineIt == lines.end() - 1 || lineIt == lines.end())
			break ;

		if (tokenIt != server_tokens.end()) {
			if (tokenIt->second && tokenIt->first != "location")
				exitError("Error: Duplicate server token : " + line);
			else {
				lineIt = setWorker(worker, lines, lineIt);
				tokenIt->second = true;
			}
		}
		else
			exitError("Error: Invalid server token : " + line);
	}
	return worker;
}

void ParseListen(Worker& worker, const std::string& line) {
	std::stringstream ss(line);
	double value = 0.0;
	char suffix = '\0';

	ss >> value >> suffix;

	if (value && !suffix && value >= 0 && value <= PORT_NUM_MAX)
		worker.setPort((int)value);
	else
		exitError("Error: invalid port");
}

void ParseErrorPage(Worker& worker, std::vector<std::string>& lines, std::vector<std::string>::iterator& lineIt) {
	while (lineIt != lines.end() && (*lineIt).compare(";"))
	{
		std::stringstream ss(*lineIt);
		double value = 0.0;
		char suffix = '\0';

		ss >> value >> suffix;

		if (value && !suffix)
			worker.AddErrorPage((int)value, *(++lineIt));
		else
			exitError("Error: invalid err_no");
		lineIt++;
	}
	lineIt--;
}

void ParseClientMaxBodySize(Worker& worker, const std::string& line) {
	std::stringstream ss(line);
	double value = 0.0;
	char suffix = '\0';

	ss >> value >> suffix;

	if (!suffix && value)
		worker.setClientMaxBodySize(value);
	else if (tolower(suffix) == 'm')
		worker.setClientMaxBodySize(value * 1000000);
	else
		exitError("[client_max_body_size] directive invalid value");
}

std::vector<std::string>::iterator setWorker(Worker& worker, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt) {
	const std::string& line = *lineIt;

	if (line == "location")
        return --lineIt;

	if (line == "listen")
		ParseListen(worker, *(++lineIt));
	else if (line == "error_page")
		ParseErrorPage(worker, lines, ++lineIt);
	else if (line == "server_name")
		worker.AddServerName(*(++lineIt));
	else if (line == "client_max_body_size")
		ParseClientMaxBodySize(worker, *(++lineIt));
	else if (line == "root")
		worker.setRoot(*(++lineIt));
	else if (line == "index")
		worker.setIndex(*(++lineIt));

	lineIt++;
	if ((*lineIt) != ";")
		exitError("Error : semicolon not exist");
	return lineIt;
}
