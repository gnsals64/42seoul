#include "../../inc/Webserv.hpp"
#include "../../inc/Transaction.hpp"
#include <iostream>

void	Webserv::Run(void) {
	for (int i = 0; i < workers_.size(); i++)
		server_sockets_.push_back(workers_[i].getServerSocket());
	while (true) {
		int	n = kevent(kq_, &change_list_[0], change_list_.size(), events_, 1024, NULL);
		if (n == -1) {
			for (int j = 0; j < workers_.size(); j++)
				close(workers_[j].getPort());
			throw Worker::keventError();
		}
		change_list_.clear();

		for (int i = 0; i < n; i++) {
			curr_event_ = &events_[i];
			eventData_ = (WorkerData *)curr_event_->udata;

			if (curr_event_->flags & EV_ERROR)
				continue ;
			if (eventData_ == NULL && curr_event_->filter == EVFILT_READ) {
				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData_->getEventType() == CLIENTEVENT && curr_event_->filter == EVFILT_READ) {
//				std::cerr << "-- CLI READ event triggered --" << std::endl;
				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData_->getEventType() == CLIENTEVENT && curr_event_->filter == EVFILT_WRITE) {
//				std::cerr << "-- CLI WRITE event triggered --" << std::endl;
				SockSendData();
			}
			else if (eventData_->getEventType() == CGIEVENT && curr_event_->filter == EVFILT_READ) {
//				std::cerr << "-- CGI READ event triggered --" << std::endl;
				ReadCgiResponse();
			}
			else if (eventData_->getEventType() == CGIEVENT && curr_event_->filter == EVFILT_WRITE) {
//				std::cerr << "-- CGI WRITE event triggered --" << std::endl;
				WriteCgiInput();
			}
			else {
				std::cerr << "BAD : " << eventData_->getEventType() << " " << curr_event_->filter << std::endl;
			}
		}
	}
}

void Webserv::WriteCgiInput(void) {
	eventData_->getCgiHandler().closePipeBeforeWrite();

	if (eventData_->getRequest().getMethod() == "POST")
	{
		std::vector<char> v = eventData_->getRequest().getBody();
		std::string s(v.begin(), v.end());
	//  생각해보니 eventData의 fd 가져오면 되는거 아닌가?
	//  write(curr_event_->ident, s.c_str(), s.length());
		write(eventData_->getCgiHandler().getWriteFd(), s.c_str(), s.length());
	}
	eventData_->getCgiHandler().closePipeAfterWrite();
	eventData_->getCgiHandler().setState(WRITE_PIPE);
//	delete ((struct workerData *)curr_event_->udata);
	ChangeEvent(change_list_, curr_event_->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close(curr_event_->ident);
}

void Webserv::ReadCgiResponse(void) {
	eventData_->getCgiHandler().closePipeBeforeRead();

	char buff[4096];
	ssize_t bytesRead;
	std::vector<char> body;

	// Read CGI script's output from from_cgi pipe
	// 생각해보니 eventData의 fd 가져오면 되는거 아닌가?
	while ((bytesRead = read(eventData_->getCgiHandler().getReadFd(), buff, sizeof(buff))) > 0)
	{
		for (int i = 0; i < bytesRead; i++) {
			eventData_->getResponse().pushBackBody(buff[i]);
		}
	}

	eventData_->getCgiHandler().closePipeAfterRead();
	eventData_->getCgiHandler().setState(READ_PIPE);

	uintptr_t write_ident = eventData_->getCgiHandler().getClientWriteIdent();
	WorkerData *udata = new WorkerData(eventData_->getRequest(), eventData_->getResponse(), eventData_->getCgiHandler(), CLIENTEVENT);
	ChangeEvent(change_list_, write_ident, EVFILT_READ, EV_DISABLE, 0, 0, udata);
	ChangeEvent(change_list_, write_ident, EVFILT_WRITE, EV_ENABLE, 0, 0, udata);

//	delete ((struct workerData *)curr_event_->udata);
	ChangeEvent(change_list_, curr_event_->ident, EVFILT_READ, EV_DISABLE, 0, 0, NULL);
	close (curr_event_->ident);
}

Webserv::Webserv() {}

Webserv::~Webserv() {}