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
			eventData = (struct workerData *)curr_event->udata;

			if (curr_event->flags & EV_ERROR)
				continue ;
			if (eventData->event == CLIENTEVENT && curr_event->filter == EVFILT_READ)
			{
				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData->event == CLIENTEVENT && curr_event->filter == EVFILT_WRITE)
				SockSendData();
			else if (eventData->event == CGIEVENT && curr_event->filter == EVFILT_READ)
			;
			else if (eventData->event == CGIEVENT && curr_event->filter == EVFILT_WRITE)
			;
			else
			;
		}
	}
}

Webserv::Webserv() {}

Webserv::~Webserv() {}