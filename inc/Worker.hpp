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
    int		get_server_socket();
    void	set_port(int port);
    int		get_port();
	void	set_root(std::string& root);
    const	std::string& get_root() const;
	void	set_index(std::string& index);
    const	std::string& get_index() const;
    void	add_server_name(std::string& server_name);
    const	std::vector<std::string>& get_server_names() const;
    void	set_client_max_body_size(size_t size);
    size_t	get_client_max_body_size() const;
    void	add_locations(const Location& location);
    const	std::vector<Location>& get_locations() const;
	void	add_error_page(int error_code, std::string& error_page);
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

void	exit_error(std::string msg);
std::vector<std::string>::iterator set_worker(Worker& worker, std::vector<std::string> lines, std::vector<std::string>::iterator& lineIt);
Worker set_worker_info(std::vector<std::string>& lines);
void parse_listen(Worker& worker, const std::string& line);
void parse_error_page(Worker& worker, std::vector<std::string>& lines, std::vector<std::string>::iterator& lineIt);
void parse_client_max_body_size(Worker& worker, const std::string& line);

#endif