#include "../../inc/Webserv.hpp"
#include <iostream>

void	Webserv::Run(void) {
	for (int i = 0; i < workers_.size(); i++)
		server_sockets_.push_back(workers_[i].GetServerSocket());
	while (true) {
		int	n = kevent(kq_, &change_list_[0], change_list_.size(), events_, 1024, NULL);
		if (n == -1) {
			for (int j = 0; j < workers_.size(); j++)
				close(workers_[j].GetPort());
			throw Worker::KeventError();
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
			else if (eventData_->GetEventType() == CLIENTEVENT && curr_event_->filter == EVFILT_READ) {
//				std::cerr << "-- CLI READ event triggered --" << std::endl;
				if (SockReceiveData() == -1 && i != 1)
					continue ;
			}
			else if (eventData_->GetEventType() == CLIENTEVENT && curr_event_->filter == EVFILT_WRITE) {
//				std::cerr << "-- CLI WRITE event triggered --" << std::endl;
				SockSendData();
			}
			else if (eventData_->GetEventType() == CGIEVENT && curr_event_->filter == EVFILT_READ) {
//				std::cerr << "-- CGI READ event triggered --" << std::endl;
				ReadCgiResponse();
			}
			else if (eventData_->GetEventType() == CGIEVENT && curr_event_->filter == EVFILT_WRITE) {
//				std::cerr << "-- CGI WRITE event triggered --" << std::endl;
				WriteCgiInput();
			}
			else {
				std::cerr << "BAD : " << eventData_->GetEventType() << " " << curr_event_->filter << std::endl;
			}
		}
	}
}

void Webserv::WriteCgiInput(void) {
	eventData_->GetCgiHandler().ClosePipeBeforeWrite();

	if (eventData_->GetRequest().GetMethod() == "POST")
	{
		std::vector<char> v = eventData_->GetRequest().GetBody();
		std::string s(v.begin(), v.end());
		write(eventData_->GetCgiHandler().GetWriteFd(), s.c_str(), s.length());
	}
	eventData_->GetCgiHandler().ClosePipeAfterWrite();
	eventData_->GetCgiHandler().SetState(WRITE_PIPE);
	ChangeEvent(change_list_, curr_event_->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close(curr_event_->ident);
}

void Webserv::ReadCgiResponse(void) {
	eventData_->GetCgiHandler().ClosePipeBeforeRead();

	char buff[4096];
	ssize_t bytesRead;
	std::vector<char> body;

	while ((bytesRead = read(eventData_->GetCgiHandler().GetReadFd(), buff, sizeof(buff))) > 0)
	{
		for (int i = 0; i < bytesRead; i++) {
			eventData_->GetResponse().PushBackBody(buff[i]);
		}
	}

	eventData_->GetCgiHandler().ClosePipeAfterRead();
	eventData_->GetCgiHandler().SetState(READ_PIPE);

	uintptr_t write_ident = eventData_->GetCgiHandler().GetClientWriteIdent();
	eventData_->SetEventType(CLIENTEVENT);
	ChangeEvent(change_list_, write_ident, EVFILT_READ, EV_DISABLE, 0, 0, eventData_);
	ChangeEvent(change_list_, write_ident, EVFILT_WRITE, EV_ENABLE, 0, 0, eventData_);

	ChangeEvent(change_list_, curr_event_->ident, EVFILT_READ, EV_DISABLE, 0, 0, NULL);
	close (curr_event_->ident);
}

Webserv::Webserv() {}

Webserv::~Webserv() {}