#ifndef LOCATION_HPP
# define LOCATION_HPP

#define METHOD_GET 0
#define METHOD_POST 1
#define METHOD_PUT 2
#define METHOD_DELETE 3

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
// #include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <string>

class Worker;

#include "Worker.hpp"

class Location {
private:
	std::string uri;
    std::string root;
    std::string index;
    bool auto_index;
	int	redir_status_code;
	std::string redir_uri;
    std::map<int, bool> limit_excepts;

public:
    Location();
    ~Location();
	void setUri(const std::string& uri);
	void setRoot(const std::string& root);
	void setIndex(const std::string& index);
	void set_redir_status_code(int status);
	void set_redir_uri(const std::string& uri);
	void set_limit_excepts(int method, bool access);
	void set_auto_index(bool access);
	const std::string& get_uri() const;
	const std::string& getRoot() const;
	const std::string& getIndex() const;
	int get_redir_status_code() const;
	const std::string& get_redir_uri() const;
	std::map<int, bool> get_limit_excepts() const;
	bool get_auto_index() const;
};

std::vector<std::string>::iterator setLocation_token(Location& location, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
std::vector<std::string>::iterator setLocation(Worker& worker, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
void	CheckLocationToken(Location& location, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
void	parse_limit_except(Location& location, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
void	parse_auto_index(Location& location, const std::string line);
void	parse_redirection(Location& location, std::vector<std::string>::iterator& lineIt);
void	print_worker_info(Worker& worker);

#endif