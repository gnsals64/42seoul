#include "../../inc/Webserv.hpp"
#include "../../inc/Transaction.hpp"
#include <iostream>

void	Webserv::Run(void)
{
	for (int i = 0; i < workers.size(); i++)
		server_sockets.push_back(workers[i].get_server_socket());
	while (true)
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
			eventData = (WorkerData *)curr_event->udata;

			if (curr_event->flags & EV_ERROR)
				continue ;
			if (eventData == NULL && curr_event->filter == EVFILT_READ)
			{

				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData->getEventType() == CLIENTEVENT && curr_event->filter == EVFILT_READ)
			{
//				std::cerr << "-- CLI READ event triggered --" << std::endl;
				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData->getEventType() == CLIENTEVENT && curr_event->filter == EVFILT_WRITE)
			{
//				std::cerr << "-- CLI WRITE event triggered --" << std::endl;
				SockSendData();
			}
			else if (eventData->getEventType() == CGIEVENT && curr_event->filter == EVFILT_READ)
			{
//				std::cerr << "-- CGI READ event triggered --" << std::endl;
				ReadCgiResponse();
			}
			else if (eventData->getEventType() == CGIEVENT && curr_event->filter == EVFILT_WRITE)
			{
//				std::cerr << "-- CGI WRITE event triggered --" << std::endl;
				WriteCgiInput();
			}
			else
			{
				std::cerr << "BAD : " << eventData->getEventType() << " " << curr_event->filter << std::endl;
			}
		}
	}
}

void Webserv::WriteCgiInput(void)
{
	eventData->getCgiHandler().closePipeBeforeWrite();

	if (eventData->getRequest().getMethod() == "POST")
	{
		std::vector<char> v = eventData->getRequest().getBody();
		std::string s(v.begin(), v.end());
	//  생각해보니 eventData의 fd 가져오면 되는거 아닌가?
	//  write(curr_event->ident, s.c_str(), s.length());
		write(eventData->getCgiHandler().getWriteFd(), s.c_str(), s.length());
	}
	eventData->getCgiHandler().closePipeAfterWrite();
	eventData->getCgiHandler().setState(WRITE_PIPE);
//	delete ((struct workerData *)curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close(curr_event->ident);
}

void Webserv::ReadCgiResponse(void)
{
	eventData->getCgiHandler().closePipeBeforeRead();

	char buff[4096];
	ssize_t bytesRead;
	std::vector<char> body;

	// Read CGI script's output from from_cgi pipe
	// 생각해보니 eventData의 fd 가져오면 되는거 아닌가?
	while ((bytesRead = read(eventData->getCgiHandler().getReadFd(), buff, sizeof(buff))) > 0)
	{
		for (int i = 0; i < bytesRead; i++) {
			eventData->getResponse().pushBackBody(buff[i]);
		}
	}

	eventData->getCgiHandler().closePipeAfterRead();
	eventData->getCgiHandler().setState(READ_PIPE);

	uintptr_t write_ident = eventData->getCgiHandler().getClientWriteIdent();
	WorkerData *udata = new WorkerData(eventData->getRequest(), eventData->getResponse(), eventData->getCgiHandler(), CLIENTEVENT);
	ChangeEvent(change_list, write_ident, EVFILT_READ, EV_DISABLE, 0, 0, udata);
	ChangeEvent(change_list, write_ident, EVFILT_WRITE, EV_ENABLE, 0, 0, udata);

//	delete ((struct workerData *)curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, NULL);
	close (curr_event->ident);
}

Webserv::Webserv() {}

Webserv::~Webserv() {}