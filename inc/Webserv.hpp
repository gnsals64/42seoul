#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Worker.hpp"
# include "WorkerData.hpp"
# include "Transaction.hpp"
# include "Request.hpp"
# include "BlockParser.hpp"
# include "CgiHandler.hpp"

# define BUFFER_SIZE 100000
# define RED "\033[31m"
# define RESET "\033[0m"

const std::string CRLF = "\r\n";

class Webserv {
	private:
		int								kq_;
		std::vector<struct kevent>		change_list_;
		std::map<int, int>				find_fd_;
		std::vector<Worker>				workers_;
		struct kevent					*curr_event_;
		std::vector<int>				server_sockets_;
		std::vector<int>::iterator		it;
		std::vector<Worker>::iterator	wit_;
		std::map<int, int>::iterator	mapter_;
		std::map<int, std::string>		status_messages_;
		WorkerData	        			*eventData_;
		std::vector<char>				buffer_;
		struct kevent					events_[1024];

		ssize_t	readData(int fd, char *buffer_, size_t buffer_size);
		void	ReadyToConnect(int i);
		void	send_response(int client_socket, int status_code, const std::string &content);
		void	handle_request(int client_socket);
		int		ConnectNewClient(void);
		int		StartReceiveData(int len);
		int		SockReceiveData(void);
		int		ReadHeader(void);
		void	ReadBody(void);
		void	ReadFinish(void);
		void    AddCgiEvent(void);
		void    CheckRequestError(void);
		void	SockSendData(void);
		void	MakeResponse(const Request &request);
		void	ChangeEvent(std::vector<struct kevent>& change_list_, uintptr_t ident, int16_t filter,	uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
		void	SetCgiEvent(void);
		void    WriteCgiInput(void);
		void    ReadCgiResponse(void);

    public:
		Webserv();
		~Webserv();
		void	ConfParse(char *conf_file);
		void	Init(void);
		void	Run(void);

};

#endif