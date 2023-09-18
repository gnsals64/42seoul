#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Worker.hpp"
# include "Transaction.hpp"
# include "Request.hpp"
# include "BlockParser.hpp"

# define BUFFER_SIZE 1024
# define RED "\033[31m"
# define RESET "\033[0m"

const std::string CRLF = "\r\n";

struct workerData
{
	Request	request;
	Response response;
};

class Webserv
{
	private:
		int								kq;
		std::vector<struct kevent>		change_list;
		std::map<int, int>				find_fd;
		std::vector<Worker>				workers;

		struct kevent					*curr_event;
		std::vector<int>				server_sockets;
		std::vector<int>::iterator		it;
		std::vector<Worker>::iterator	wit;
		std::map<int, int>::iterator	mapter;
		std::map<int, std::string>		status_messages;
		struct kevent events[1024];
		// struct workerData	udata;
    
		ssize_t	readData(int fd, char *buffer, size_t buffer_size);
		void	ReadyToConnect(int i);
		void	send_response(int client_socket, int status_code, const std::string &content);
		void	handle_request(int client_socket);
		int		ConnectNewClient(void);
		void	ChangeEvent(std::vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,	uint16_t flags, uint32_t fflags, intptr_t data, void *udata);

    public:
		void	ConfParse(char *conf_file);
		void	Init(void);
		void	Run(void);

};

#endif