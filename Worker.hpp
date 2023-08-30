#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include "Location.hpp"
#include "Request.hpp"

class Worker {
private:
    int server_socket;
    int port;
		std::string root;
		std::string index;
    std::vector<std::string> server_names;
    std::map<int, std::string> error_pages;
    size_t client_max_body_size;
	Request	request;

    // std::vector<Location> locations;

public:
    Worker();
    ~Worker();
    // Worker(const Worker& worker);
    // Worker& operator=(const Worker& worker);
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
    // void	add_locations(const Location& location);
    // const	std::vector<Location>& get_locations() const;
		void	add_error_page(int error_code, std::string& error_page);
    const	std::map<int, std::string>& get_error_page() const;
	Request	&getRequest();
	std::vector<std::string> split(std::string input, char dlim, int &result_cnt);
	void	reqFirstLineParse(std::string first_line);
	void	parseHost(std::vector<std::string> colon_parse);
	void	parseConnection(std::vector<std::string> colon_parse);
	void	parseContentLength(std::vector<std::string> colon_parse);
	void	parseOther(std::vector <std::string> line_parse, int line_cnt);
	void	requestParse(std::string request);
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

#endif