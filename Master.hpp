#ifndef MASTER_HPP
# define MASTER_HPP

#include "Worker.hpp"
#include "Transaction.hpp"
#include "Request.hpp"
#include "BlockParser.hpp"

const std::string CRLF = "\r\n";



void send_response(int client_socket, int status_code, const std::string &content) {
	std::stringstream response;
	response << "HTTP/1.1 " << status_code << " " << status_messages[status_code] << CRLF;
	response << "Content-Type: text/html" << CRLF;
	response << "Content-Length: " << content.size() << CRLF;
	response << CRLF;
	response << content;

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
					it = find(server_sockets.begin(),  server_sockets.end(), curr_event->ident);
					int tmp_cli_sock = accept(*it, NULL, NULL);
					if (tmp_cli_sock== -1)
						continue ;
					fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
					struct workerData	*udata = new (struct workerData);
					change_events(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, udata);
					change_events(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, udata);
					find_fd[tmp_cli_sock] = curr_event->ident;
				}
				else if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) == server_sockets.end())
				{
					struct workerData *eventData = (struct workerData *)curr_event->udata;
					std::vector<char> buffer(BUFFER_SIZE);
					mapter = find_fd.find(curr_event->ident);
					for (wit = workers.begin(); wit != workers.end(); ++wit)
						if (wit->get_server_socket() == mapter->second)
							break ;
					ssize_t len = readData(curr_event->ident, buffer.data(), BUFFER_SIZE);
					if (len > 0)
					{
						buffer.resize(len);
						if (eventData->request.getState() == HEADER_READ)
						{
							std::string temp_data(buffer.begin(), buffer.end());
							eventData->request.appendHeader(temp_data);
							eventData->request.BodyAppendVec(buffer);
							size_t pos = eventData->request.getHeaders().find("\r\n\r\n");
							if (pos == std::string::npos)
								continue ;
							else
							{
								std::string temp = eventData->request.getHeaders();
								eventData->request.setHeaders(eventData->request.getHeaders().substr(0, pos + 4));
								eventData->request.removeCRLF();
								if (eventData->request.getHeaders().find("Content-Length") != std::string::npos)
								{
									size_t body_size = wit->checkContentLength(eventData->request.getHeaders());
									if (body_size <= eventData->request.getBody().size())
										eventData->request.setState(READ_FINISH);
									else
										eventData->request.setState(BODY_READ);
								}
								else if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
								{
									if (eventData->request.Findrn0rn() == 1)
										eventData->request.setState(READ_FINISH);
									else
										eventData->request.setState(BODY_READ);
								}
								else
									eventData->request.setState(READ_FINISH);
							}
						}
						else if (eventData->request.getState() == BODY_READ)
						{
							eventData->request.BodyAppendVec(buffer);
							if (eventData->request.getHeaders().find("Content-Length") != std::string::npos)
							{
								size_t body_size = wit->checkContentLength(eventData->request.getHeaders());
								if (body_size <= eventData->request.getBody().size())	//본문을 다 읽으면
									eventData->request.setState(READ_FINISH);
							}
							else if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
								if (eventData->request.Findrn0rn() == 1)
									eventData->request.setState(READ_FINISH);
						}
					}
					else if (len == 0)
					{
						std::cout << "Client " << curr_event->ident << " disconnected." << std::endl;
						close (curr_event->ident);
					}
					else
						continue ;
					if (eventData->request.getState() == READ_FINISH)
					{
						wit->requestHeaderParse(eventData->request);
						if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
							wit->chunkBodyParse(eventData->request, eventData->response);
						change_events(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event->udata);
						change_events(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event->udata);	//write 이벤트 발생
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
							std::map<int, int>::iterator tmp_fd_iter = find_fd.find(curr_event->ident);
							find_fd.erase(tmp_fd_iter);
							delete ((struct workerData *)curr_event->udata);
							// std::map<int, Request>::iterator tmp_req_iter = wit->getRequest().find(curr_event->ident);
							// wit->getRequest().erase(tmp_req_iter);
							change_events(change_list, curr_event->ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
							change_events(change_list, curr_event->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
							close (curr_event->ident);
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