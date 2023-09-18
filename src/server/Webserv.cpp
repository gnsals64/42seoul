#include "../../inc/Webserv.hpp"
#include "../../inc/Transaction.hpp"

void	Webserv::ConfParse(char *conf_file)
{
	ConfigParser 	parser;

	//확장자 체크
	if (CheckExtension(conf_file) == -1) {
		std::cout << "File is not configuration file." << std::endl;
		return ;
	}
	//블럭 토큰화 밑 오류체크
	if (CheckBlock(conf_file, &parser) == -1) {
		std::cout << "configuration file is not vaild" << std::endl;
		return ;
	}
	//토큰 바탕으로 해석 후 worker class 인스턴스화
    for (int i = 0; i < parser.get_server().size(); i++) {
        Worker worker = set_worker_info(parser.server_[i]);
		this->workers.push_back(worker);
        print_worker_info(worker);
    }
}

void	Webserv::Init(void)
{
	for(int i = 0; i < this->workers.size(); i++)
		ReadyToConnect(i);
	this->kq = kqueue();
	if (kq == -1)
	{
		for (int j = 0; j < this->workers.size(); j++)
			close(this->workers[j].get_port());
		throw Worker::kqueueError();
	}
	for (int i = 0;  i < this->workers.size(); i++)
		ChangeEvent(change_list, this->workers[i].get_server_socket(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

int	Webserv::ConnectNewClient(void) {
	it = find(server_sockets.begin(),  server_sockets.end(), curr_event->ident);
	int tmp_cli_sock = accept(*it, NULL, NULL);
	if (tmp_cli_sock== -1)
		return -1 ;
	fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
	struct workerData	*udata = new (struct workerData);
	ChangeEvent(change_list, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, udata);
	ChangeEvent(change_list, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, udata);
	find_fd[tmp_cli_sock] = curr_event->ident;
	return 0;
}

void	Webserv::Run(void)
{
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
					if (ConnectNewClient() == -1)
						continue ;
				}
				else if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) == server_sockets.end())
				{
					ReadData	data;
					for (wit = workers.begin(); wit != workers.end(); ++wit)
						if (wit->get_server_socket() == mapter->second)
							break ;
					ssize_t len = readData(curr_event->ident, data.buffer.data(), BUFFER_SIZE);
					if (len > 0)
					{
						data.buffer.resize(len);
						if (data.eventData->request.getState() == HEADER_READ)
						{
							std::string temp_data(data.buffer.begin(), data.buffer.end());
							data.eventData->request.appendHeader(temp_data);
							data.eventData->request.BodyAppendVec(data.buffer);
							size_t pos = data.eventData->request.getHeaders().find("\r\n\r\n");
							if (pos == std::string::npos)
								continue ;
							else
							{
								std::string temp = data.eventData->request.getHeaders();
								data.eventData->request.setHeaders(data.eventData->request.getHeaders().substr(0, pos + 4));
								data.eventData->request.removeCRLF();
								if (data.eventData->request.getHeaders().find("Content-Length") != std::string::npos)
								{
									size_t body_size = wit->checkContentLength(data.eventData->request.getHeaders());
									if (body_size <= data.eventData->request.getBody().size())
										data.eventData->request.setState(READ_FINISH);
									else
										data.eventData->request.setState(BODY_READ);
								}
								else if (data.eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
								{
									if (data.eventData->request.Findrn0rn() == 1)
										data.eventData->request.setState(READ_FINISH);
									else
										data.eventData->request.setState(BODY_READ);
								}
								else
									data.eventData->request.setState(READ_FINISH);
							}
						}
						else if (data.eventData->request.getState() == BODY_READ)
						{
							data.eventData->request.BodyAppendVec(data.buffer);
							if (data.eventData->request.getHeaders().find("Content-Length") != std::string::npos)
							{
								size_t body_size = wit->checkContentLength(data.eventData->request.getHeaders());
								if (body_size <= data.eventData->request.getBody().size())	//본문을 다 읽으면
									data.eventData->request.setState(READ_FINISH);
							}
							else if (data.eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
								if (data.eventData->request.Findrn0rn() == 1)
									data.eventData->request.setState(READ_FINISH);
						}
					}
					else if (len == 0)
					{
						std::cout << "Client " << curr_event->ident << " disconnected." << std::endl;
						close (curr_event->ident);
					}
					else
						continue ;
					if (data.eventData->request.getState() == READ_FINISH)
					{
						wit->requestHeaderParse(data.eventData->request);
						if (data.eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
							wit->chunkBodyParse(data.eventData->request, data.eventData->response);
						ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event->udata);
						ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event->udata);	//write 이벤트 발생
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
							ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
							ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
							close (curr_event->ident);
					// }
				// }
			}
		}
	}
}

Webserv::Webserv() {}

Webserv::~Webserv() {}

ReadData::ReadData() : buffer(BUFFER_SIZE) {
	eventData = (struct workerData *)curr_event->udata;
	mapter = find_fd.find(curr_event->ident);
}

ReadData::~ReadData() {}