#ifndef MASTER_HPP
# define MASTER_HPP

#include "Worker.hpp"

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

void	run(std::vector<Worker> &workers, int &kq, std::vector <struct kevent> &change_list)
{
	std::map <int, std::string> clients_buf;
	std::vector<int> client_socket;
	std::vector<int> server_sockets;
	std::vector<int>::iterator it;
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
			{
				if (find(server_sockets.begin(), server_sockets.end(), events[i].ident) != server_sockets.end())
					throw Worker::unkownError();
				else
				{
					std::cerr << "client socket error" << std::endl;
					close(events[i].ident);
					clients_buf.erase(events[i].ident);
				}
			}
			if (events[i].filter == EVFILT_READ)
			{
				if (find(server_sockets.begin(), server_sockets.end(), events[i].ident) != server_sockets.end())
				{
					it = find(server_sockets.begin(), server_sockets.end(), events[i].ident);
					if ((tmp_cli_sock = accept(*it, NULL, NULL)) == -1)
					{
						for (int j = 0; j < workers.size(); j++)
							close(workers[j].get_port());
						for (int j = 0; j < client_socket.size(); j++)
							close(client_socket[j]);
						throw Worker::acceptError();
					}
					fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
					change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
					client_socket.push_back(tmp_cli_sock);
					clients_buf[tmp_cli_sock] = "";
				}
				else if (find(server_sockets.begin(), server_sockets.end(), events[i].ident) == server_sockets.end())
				{
					char buf[1024];
					int n = read(events[i].ident, buf, sizeof(buf));
					std::cout << "buf = " << buf << std::endl;
					if (n <= 0)
					{
						if (n < 0)
						{
							std::cerr << "client read error!" << std::endl;
							continue ;
						}
							close(events[i].ident);
							clients_buf.erase(events[i].ident);
							client_socket.pop_back();
					}
					else
					{
						buf[n] = '\0';
						clients_buf[events[i].ident] += buf;
					}
					change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_DISABLE, 0, 0, NULL);
					change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
				}
			}
			else if (events[i].filter == EVFILT_WRITE)
			{
				std::map<int, std::string>::iterator that = clients_buf.find(events[i].ident);
				if (that != clients_buf.end())
				{
					if (clients_buf[events[i].ident] != "")
					{
						int	client_sock = events[i].ident;
						handle_request(client_sock);
						change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
					}
				}
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