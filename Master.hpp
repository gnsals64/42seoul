#ifndef MASTER_HPP
# define MASTER_HPP

#include "Worker.hpp"
#include "Transaction.hpp"
#include "Request.hpp"
#include "block_parser.hpp"

# define BUFFER_SIZE 7
# define RED "\033[31m"
# define RESET "\033[0m"

void	conf_parse(char *conf_file, std::vector<Worker> &workers)
{
	ConfigParser 	parser;

	//확장자 체크
	if (check_extension(conf_file) == -1) {
		std::cout << "File is not configuration file." << std::endl;
		return ;
	}
	//블럭 토큰화 밑 오류체크
	if (check_block(conf_file, &parser) == -1) {
		std::cout << "configuration file is not vaild" << std::endl;
		return ;
	}
	//토큰 바탕으로 해석 후 worker class 인스턴스화
    for (int i = 0; i < parser.get_server().size(); i++) {
        Worker worker = set_worker_info(parser.server_[i]);
		workers.push_back(worker);
        print_worker_info(worker);
    }
}

const std::string CRLF = "\r\n";

std::map<int, std::string> status_messages;

void send_response(int client_socket, int status_code, const std::string &content) {
	std::stringstream response;
	response << "HTTP/1.1 " << status_code << " " << status_messages[status_code] << CRLF;
	response << "Content-Type: text/html" << CRLF;
	response << "Content-Length: " << content.size() << CRLF;
	response << CRLF;
	response << content;
	// std::cout << (char *)response.str().c_str() << std::endl;

	send(client_socket, response.str().c_str(), response.str().size(), 0);
	// close (client_socket);
}

void handle_request(int client_socket) {
    const std::string response_content = "<html><body><h1>Hello, HTTP 1.1 Server!</h1></body></html>";
    send_response(client_socket, 200, response_content);
}

void change_events(std::vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
		uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

void	init(std::vector<Worker> &workers, int &kq, std::vector <struct kevent> &change_list)
{
	sockaddr_in	server_address;

	for(int i = 0; i < workers.size(); i++)
	{
		memset(&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(workers[i].get_port());
		if (bind(workers[i].get_server_socket(), (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
		{
			for (int j = 0; j < workers.size(); j++)
				close(workers[j].get_port());
			throw Worker::bindError();
		}
		if (listen(workers[i].get_server_socket(), 15) == -1)
		{
			for (int j = 0; j < workers.size(); j++)
				close(workers[j].get_port());
			throw Worker::listenError();
		}
	}
	kq = kqueue();
	if (kq == -1)
	{
		for (int j = 0; j < workers.size(); j++)
			close(workers[j].get_port());
		throw Worker::kqueueError();
	}
	for (int i = 0;  i < workers.size(); i++)
		change_events(change_list, workers[i].get_server_socket(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

ssize_t readData(int fd, char *buffer, size_t buffer_size) {
    ssize_t len = recv(fd, buffer, buffer_size, 0);
    if (len == 0) {
        return (0);
    } else if (len > 0) {
        return len;
    }
    return -1;
}

void	run(std::vector<Worker> &workers, int &kq, std::vector <struct kevent> &change_list, std::map<int, int>find_fd)
{
	struct kevent *curr_event;
	std::vector<int> server_sockets;
	std::vector<int>::iterator it;
	std::vector<Worker>::iterator wit;
	std::map<int, int>::iterator mapter;
	struct kevent events[1024];

	for (int i = 0; i < workers.size(); i++)
		server_sockets.push_back(workers[i].get_server_socket());
	while (1)
	{
		int	n = kevent(kq, &change_list[0], change_list.size(), events, 1024, NULL);
		if (n == -1)
		{
			for (int j = 0; j < workers.size(); j++)
				close(workers[j].get_port());
			throw Worker::keventError();
		}
		change_list.clear();
		for (int i = 0; i < n; i++)
		{
			curr_event = &events[i];
			if (curr_event->flags & EV_ERROR)
				continue ;
			if (curr_event->filter == EVFILT_READ)
			{
				if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) != server_sockets.end())
				{
					it = find(server_sockets.begin(), server_sockets.end(), curr_event->ident);
					int tmp_cli_sock = accept(*it, NULL, NULL);
					if (tmp_cli_sock== -1)
						continue ;
					for (wit = workers.begin(); wit != workers.end(); ++wit)
						if (wit->get_server_socket() == *it)
							break ;
					fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
					change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
					Request req;
					wit->getRequest()[tmp_cli_sock] = req;
					find_fd[tmp_cli_sock] = curr_event->ident;
				}
				else if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) == server_sockets.end())
				{
					std::vector<char> buffer(BUFFER_SIZE);
					ssize_t len = readData(curr_event->ident, buffer.data(), BUFFER_SIZE);
					mapter = find_fd.find(curr_event->ident);
					for (wit = workers.begin(); wit != workers.end(); ++wit)
						if (wit->get_server_socket() == mapter->first)
							break ;
					if (len > 0)
					{
						buffer.resize(len);
						if (wit->getRequest()[curr_event->ident].getState() == HEADER_READ)
						{
							std::string temp_data(buffer.begin(), buffer.end());
							size_t pos = temp_data.find("\r\n\r\n");
							if (pos == std::string::npos)
								wit->getRequest()[curr_event->ident].appendHeader(temp_data);
							else
							{
								wit->getRequest()[curr_event->ident].appendHeader(temp_data.substr(0, pos));
								wit->getRequest()[curr_event->ident].appendHeader("\n");
								if (wit->getRequest()[curr_event->ident].getHeaders().find("POST") != std::string::npos)
								{
									for (int i = pos + 4; i < len; i++)
										wit->getRequest()[curr_event->ident].pushPostBody(buffer[i]);
								}
								size_t body_size = wit->checkContentLength(wit->getRequest()[curr_event->ident].getHeaders());
								std::string temp_body = temp_data.substr(pos + 4);
								wit->getRequest()[curr_event->ident].appendBody(temp_body);
								if (body_size == temp_body.size())	//본문을 다 읽으면
								{
									wit->getRequest()[curr_event->ident].setState(READ_FINISH);
								}
								else	//다 못 읽었으면
								{
									wit->getRequest()[curr_event->ident].setState(BODY_READ);
								}
							}
						}
						else if (wit->getRequest()[curr_event->ident].getState() == BODY_READ)
						{
							if (wit->getRequest()[curr_event->ident].getHeaders().find("POST") != std::string::npos)
								for (int i = 0; i < len; i++)
									wit->getRequest()[curr_event->ident].pushPostBody(buffer[i]);
							size_t body_size = wit->checkContentLength(wit->getRequest()[curr_event->ident].getHeaders());
							std::string temp_body(buffer.begin(), buffer.end());
							wit->getRequest()[curr_event->ident].appendBody(temp_body);
							if (body_size == wit->getRequest()[curr_event->ident].getBody().size())
								wit->getRequest()[curr_event->ident].setState(READ_FINISH);
						}
					}
					else if (len == 0)
					{
						std::cout << "Client " << curr_event->ident << " disconnected." << std::endl;
						close (curr_event->ident);
					}
					else
						continue ;
					if (wit->getRequest()[curr_event->ident].getState() == READ_FINISH)
					{
						std::string tmp_buf;
						std::string return_val;
						size_t	contentLength;
						tmp_buf += wit->getRequest()[curr_event->ident].getHeaders();
						tmp_buf += wit->getRequest()[curr_event->ident].getBody();
						for (std::vector<Worker>::iterator wit = workers.begin(); wit != workers.end(); ++wit) {
							if (wit->get_server_socket() == *it) {
								wit->requestParse(tmp_buf, curr_event->ident);
							}
						}
						contentLength = wit->myStoi(wit->getRequest()[curr_event->ident].getContentLength());
						if (wit->getRequest()[curr_event->ident].getMethod() == "POST" && (contentLength != wit->getRequest()[curr_event->ident].getPostBody().size()))
						{
							std::cout << "body size is not matched with content length" << std::endl;
							continue ;
						}
						if (contentLength != wit->getRequest()[curr_event->ident].getBody().size())
						{
							std::cout << "body size is not matched with content length" << std::endl;
							continue ;
						}
						// return_val = wit->checkReturnVal();
						if (wit->getRequest()[curr_event->ident].getMethod() == "DELETE")
							wit->urlSearch(curr_event->ident);
						change_events(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, NULL);
						change_events(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, NULL);
						wit->getRequest()[curr_event->ident].clearAll();
					}
				}
			}
			else if (events[i].filter == EVFILT_WRITE)
			{
				// std::map<int, std::string>::iterator that = clients_buf.find(curr_event->ident);
				// if (that != clients_buf.end())
				// {
					// if (clients_buf[curr_event->ident] != "")
				// 	{
							int	client_sock = curr_event->ident;
							handle_request(client_sock);
							// change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
							// change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
							wit->getRequest()[curr_event->ident].clearAll();
					// }
				// }
			}
		}
	}
}

void	clean(std::vector<Worker> &workers)
{
	for (int i = 0; i < workers.size(); i++)
		close(workers[i].get_port());
}

#endif