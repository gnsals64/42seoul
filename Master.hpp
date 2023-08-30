#ifndef MASTER_HPP
# define MASTER_HPP

#include "Worker.hpp"
#include "Transaction.hpp"
#include "Request.hpp"

# define BUFFER_SIZE 100
# define RED "\033[31m"
# define RESET "\033[0m"

void	conf_parse(char *conf_file)
{

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
		// server_address.sin_port = htons(workers[i].get_port());
		server_address.sin_port = htons(8080);
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

std::vector<std::string> splitArgs(std::string line, std::string sep)
{
	std::vector<std::string> str;
	size_t	start = 0;
	size_t	end = 0;

	while (1)
	{
		end = line.find_first_of(sep, start);
		if (end == std::string::npos)
			break ;
		std::string parsed = line.substr(start, end - start);
		str.push_back(parsed);
		start = line.find_first_not_of(sep, end);
		if (start == std::string::npos)
			break ;
	}
	return (str);
}

size_t	checkContentLength(std::string headers)
{
	size_t	len = 0;
	std::string length = "";
	std::vector <std::string> tmp = splitArgs(headers, "\r\n");
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].find("Content-Length: ") != std::string::npos)
		{
			length = tmp[i].substr(tmp[i].find(':') + 2);
		}
	}
	if (length != "")
		len = std::stoi(length);
	return (len);
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

void	run(std::vector<Worker> &workers, int &kq, std::vector <struct kevent> &change_list)
{
	std::vector<int> server_sockets;
	std::vector<int>::iterator it;
	std::vector<Worker>::iterator wit;
	int	tmp_cli_sock;
	struct kevent events[32];

	for (int i = 0; i < workers.size(); i++)
		server_sockets.push_back(workers[i].get_server_socket());
	while (1)
	{
		int	n = kevent(kq, &change_list[0], change_list.size(), events, 32, NULL);
		if (n == -1)
		{
			for (int j = 0; j < workers.size(); j++)
				close(workers[j].get_port());
			throw Worker::keventError();
		}
		change_list.clear();
		for (int i = 0; i < n; i++)
		{
			if (events[i].flags & EV_ERROR)
				continue ;
			if (events[i].filter == EVFILT_READ)
			{
				if (find(server_sockets.begin(), server_sockets.end(), events[i].ident) != server_sockets.end())
				{
					it = find(server_sockets.begin(), server_sockets.end(), events[i].ident);
					if ((tmp_cli_sock = accept(*it, NULL, NULL)) == -1)
						continue ;
					fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
					change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
				}
				else if (find(server_sockets.begin(), server_sockets.end(), events[i].ident) == server_sockets.end())
				{
					std::vector<char> buffer(BUFFER_SIZE);
					ssize_t len = readData(events[i].ident, buffer.data(), BUFFER_SIZE);
					for (wit = workers.begin(); wit != workers.end(); ++wit)
						if (wit->get_server_socket() == *it)
							break ;
					if (len > 0)
					{
						buffer.resize(len);
						if (wit->getRequest().getState() == HEADER_READ)
						{
							std::string temp_data(buffer.begin(), buffer.end());
							size_t pos = temp_data.find("\r\n\r\n");
							if (pos == std::string::npos)
								wit->getRequest().appendHeader(temp_data);
							else
							{
								wit->getRequest().appendHeader(temp_data.substr(0, pos));
								wit->getRequest().appendHeader("\n");
								size_t body_size = checkContentLength(wit->getRequest().getHeaders());
								std::string temp_body = temp_data.substr(pos + 4);
								wit->getRequest().appendBody(temp_body);
								if (body_size == temp_body.size())	//본문을 다 읽으면
								{
									wit->getRequest().setState(READ_FINISH);
								}
								else	//다 못 읽었으면
								{
									wit->getRequest().setState(BODY_READ);
								}
							}
						}
						else if (wit->getRequest().getState() == BODY_READ)
						{
							size_t body_size = checkContentLength(wit->getRequest().getHeaders());
							std::string temp_body(buffer.begin(), buffer.end());
							wit->getRequest().appendBody(temp_body);
							if (body_size == wit->getRequest().getBody().size())
								wit->getRequest().setState(READ_FINISH);
						}
					}
					else if (len == 0)
					{
						std::cout << "Client " << events[i].ident << " disconnected." << std::endl;
						close (events[i].ident);
					}
					else
						continue ;
					if (wit->getRequest().getState() == READ_FINISH)
					{
						std::string tmp_buf;
						tmp_buf += wit->getRequest().getHeaders();
						tmp_buf += wit->getRequest().getBody();
						for (std::vector<Worker>::iterator wit = workers.begin(); wit != workers.end(); ++wit) {
							if (wit->get_server_socket() == *it) {
								wit->requestParse(tmp_buf);
							}
						}
						//파싱 완료 후 이벤트 변경
						change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_DISABLE, 0, 0, NULL);
						change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
						wit->getRequest().clearAll();
					}
				}
			}
			else if (events[i].filter == EVFILT_WRITE)
			{
				// std::map<int, std::string>::iterator that = clients_buf.find(events[i].ident);
				// if (that != clients_buf.end())
				// {
				// 	if (clients_buf[events[i].ident] != "")
				// 	{
						int	client_sock = events[i].ident;
						handle_request(client_sock);
						change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
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