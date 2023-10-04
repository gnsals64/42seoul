#include "../../inc/Webserv.hpp"

void	Webserv::ConfParse(char *conf_file) {
	ConfigParser 	parser;

	//확장자 체크
	CheckExtension(conf_file);
	//블럭 토큰화 밑 오류체크
	CheckBlock(conf_file, &parser);
	//토큰 바탕으로 해석 후 worker class 인스턴스화
    for (int i = 0; i < parser.GetServer().size(); i++) {
        Worker worker = SetWorkerInfo(parser.server_[i]);
		this->workers_.push_back(worker);
    }
}

void	Webserv::Init(void) {
	// configfile에서 지정해준 정보로 소켓을 열어서 데이터 받을 준비
	for(int i = 0; i < this->workers_.size(); i++)
		ReadyToConnect(i);
	kq_ = kqueue();
	// kq실패시 오류처리부분 생각좀 더 해봐야할듯
	if (kq_ == -1) {
		for (int j = 0; j < this->workers_.size(); j++)
			close(this->workers_[j].GetPort());
		throw Worker::KqueueError();
	}
	//worker fd 등록
	for (int i = 0;  i < this->workers_.size(); i++)
		ChangeEvent(change_list_, this->workers_[i].GetServerSocket(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

int	Webserv::ConnectNewClient(void) {
	it = find(server_sockets_.begin(),  server_sockets_.end(), curr_event_->ident);
	int tmp_cli_sock = accept(*it, NULL, NULL);
	if (tmp_cli_sock== -1)
		return -1 ;
	fcntl(tmp_cli_sock, F_SETFL, O_NONBLOCK);
	WorkerData *udata = new WorkerData(*new Request(), *new Response(), *new CgiHandler(), CLIENTEVENT);
	ChangeEvent(change_list_, tmp_cli_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, udata);
	ChangeEvent(change_list_, tmp_cli_sock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, udata);
	find_fd_[tmp_cli_sock] = curr_event_->ident;
	return 0;
}

void	Webserv::ReadyToConnect(int i) {
	sockaddr_in	server_address;

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(workers_[i].GetPort());
	if (bind(this->workers_[i].GetServerSocket(), (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		for (int j = 0; j < this->workers_.size(); j++)
			close(this->workers_[j].GetPort());
		throw Worker::BindError();
	}
	if (listen(this->workers_[i].GetServerSocket(), 15) == -1) {
		for (int j = 0; j < this->workers_.size(); j++)
			close(this->workers_[j].GetPort());
		throw Worker::ListenError();
	}
	fcntl(this->workers_[i].GetServerSocket(), F_SETFL, O_NONBLOCK);
}