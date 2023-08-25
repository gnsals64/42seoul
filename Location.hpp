#ifndef LOCATION_HPP
# define LOCATION_HPP

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

class Location
{
	private:
		std::map<std::string, bool> limit_except;
		std::string	root;
		bool	autoindex;
		std::string index;
	public:
		Location();
		~Location();
		Location(const Location &obj);
		Location &operator=(const Location &obj);
		std::string	&getRoot();
};

#endif