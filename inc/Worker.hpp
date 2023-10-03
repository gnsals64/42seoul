#ifndef WORKER_HPP
#define WORKER_HPP

#define PORT_NUM_MAX 65535

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include "Location.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Location;
class Request;
class Response;

class Worker {
private:
    int server_socket;
    int port;
	std::string root;
	std::string index;
    std::vector<std::string> server_names;
    std::map<int, std::string> error_pages;
    size_t client_max_body_size;
	std::vector<Location> locations;

public:
    Worker();
    ~Worker();
    void	set_server_socket(int server_socket);
    int		getServerSocket();
    void	setPort(int port);
    int		getPort();
	void	setRoot(std::string& root);
    const	std::string& getRoot() const;
	void	setIndex(std::string& index);
    const	std::string& getIndex() const;
    void	AddServerName(std::string& server_name);
    const	std::vector<std::string>& get_server_names() const;
    void	setClientMaxBodySize(size_t size);
    size_t	get_client_max_body_size() const;
    void	AddLocations(const Location& location);
    const	std::vector<Location>& get_locations() const;
	void	AddErrorPage(int error_code, std::string& error_page);
    const	std::map<int, std::string>& get_error_page() const;
	size_t	myStoi(std::string str);
	std::vector<std::string> splitArgs(std::string line, std::string sep);
	size_t	checkContentLength(std::string headers);
	std::vector<std::string> split(std::string input, char dlim, int &result_cnt);
	void	reqFirstLineParse(Request &req, std::string first_line);
	void	parseHost(Request &req, std::vector<std::string> colon_parse);
	void	parseConnection(Request &req, std::vector<std::string> colon_parse);
	void	parseContentLength(Request &req, std::vector<std::string> colon_parse);
	void	parseOther(Request &req, std::vector <std::string> line_parse, int line_cnt);
	// void	CheckPossibleMethod(Request &req);
	void	requestHeaderParse(Request &req);
	void	chunkBodyParse(Request &req, Response &res);
	// void	urlSearch(int event_fd);
	// std::string checkReturnVal();
	class	bindError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("bind error");
			}
	};
	class	listenError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("listen error");
			}
	};
	class	kqueueError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("kqueue error");
			}
	};
	class	keventError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("kevent error");
			}
	};
	class	acceptError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("accept error");
			}
	};
	class	readError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("read error");
			}
	};
	class	unkownError: public std::exception
	{
		public:
			virtual const char	*what() const throw()
			{
				return ("unkown error");
			}
	};
};

void	exitError(std::string msg);
std::vector<std::string>::iterator setWorker(Worker& worker, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
Worker setWorker_info(std::vector<std::string>& lines);
void ParseListen(Worker& worker, const std::string& line);
void ParseErrorPage(Worker& worker, std::vector<std::string>& lines, std::vector<std::string>::iterator& lineIt);
void ParseClientMaxBodySize(Worker& worker, const std::string& line);

#endif