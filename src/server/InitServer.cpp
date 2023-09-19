#include "../../inc/Webserv.hpp"

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

void	Webserv::Init(void) {
	// configfile에서 지정해준 정보로 소켓을 열어서 데이터 받을 준비
	for(int i = 0; i < this->workers.size(); i++)
		ReadyToConnect(i);
	this->kq = kqueue();
	// kq실패시 오류처리부분 생각좀 더 해봐야할듯
	if (kq == -1) {
		for (int j = 0; j < this->workers.size(); j++)
			close(this->workers[j].get_port());
		throw Worker::kqueueError();
	}
	//worker fd 등록
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

void	Webserv::ReadyToConnect(int i) {
	sockaddr_in	server_address;

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(workers[i].get_port());
	if (bind(this->workers[i].get_server_socket(), (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
	{
		for (int j = 0; j < this->workers.size(); j++)
			close(this->workers[j].get_port());
		throw Worker::bindError();
	}
	if (listen(this->workers[i].get_server_socket(), 15) == -1)
	{
		for (int j = 0; j < this->workers.size(); j++)
			close(this->workers[j].get_port());
		throw Worker::listenError();
	}
}