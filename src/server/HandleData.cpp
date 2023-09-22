#include "../../inc/Webserv.hpp"
#include "../../inc/CgiHandler.hpp"
#include "../../inc/Transaction.hpp"

int	Webserv::SockReceiveData(void) {
	//새로운 클라이언트 접속 및 등록
	if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) != server_sockets.end())
	{
		if (ConnectNewClient() == -1)
			return -1;
	}
	//클라이언트 등록이 되어있을때 read
	else if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) == server_sockets.end())
	{
		eventData = (struct workerData *)curr_event->udata;
		buffer.resize(BUFFER_SIZE);
		mapter = find_fd.find(curr_event->ident);
		for (wit = workers.begin(); wit != workers.end(); ++wit)
			if (wit->get_server_socket() == mapter->second)
				break ;
		ssize_t len = readData(curr_event->ident, buffer.data(), BUFFER_SIZE);
		//std::cout << buffer.data() << "\n" << std::endl;
		//데이터 읽기
		if (len > 0)
		{
			if (StartReceiveData(len) == -1)
				return -1;
		}
		//클라이언트 끊어짐
		else if (len == 0)
		{
			std::cout << "Client " << curr_event->ident << " disconnected." << std::endl;
			close (curr_event->ident);
		}
		//read 오류
		else
			return -1;
		//데이터 다 읽음
		if (eventData->request.getState() == READ_FINISH)
			ReadFinish();
	}
	return 0;
}

void	Webserv::SockSendData(void) {
	int	client_sock = curr_event->ident;
	this->eventData->response.SendResponse(client_sock);
	std::map<int, int>::iterator tmp_fd_iter = find_fd.find(curr_event->ident);
	find_fd.erase(tmp_fd_iter);
	delete ((struct workerData *)curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
	ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close (curr_event->ident);
}

int	Webserv::StartReceiveData(int len) {
	buffer.resize(len);
	//해더파싱
	if (eventData->request.getState() == HEADER_READ)
	{
		if (ReadHeader() == -1)
			return -1;
	}
	//바디파싱
	else if (eventData->request.getState() == BODY_READ)
		ReadBody();
	
	return 0;
}

int	Webserv::ReadHeader(void) {
	std::string temp_data(buffer.begin(), buffer.end());
	// std::cout << "read = " << temp_data << std::endl;
	// std::cout << "fuck" << std::endl;
	eventData->request.appendHeader(temp_data);
	eventData->request.BodyAppendVec(buffer);
	size_t pos = eventData->request.getHeaders().find("\r\n\r\n");
	if (pos == std::string::npos)
		return -1;
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
	return 0;
}

void	Webserv::ReadBody(void) {
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

void	Webserv::ReadFinish(void) {
	wit->requestHeaderParse(eventData->request);
	if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
		wit->chunkBodyParse(eventData->request, eventData->response);
	ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event->udata);	//write 이벤트 발생
	std::cout << "request header" << std::endl;
	std::cout << this->eventData->request.getHeaders() << std::endl;
    MakeResponse(eventData->request);
}

void    Webserv::MakeResponse(const Request &request) {
    if (this->eventData->request.getPath().find(".py") != std::string::npos)
    {
        this->eventData->response.SetCgiResponse(request);
        return ;
    }

    std::string method = this->eventData->request.getMethod();

	int i;
	if (request.getPath().back() == '/' && request.getPath().size() != 1) {
		for(i = 0; i < wit->get_locations().size(); i++)
		{
			if (request.getPath().find(wit->get_locations()[i].get_uri()) == 0)
				break ;
		}
	}
	if (i == wit->get_locations().size()) {
		this->eventData->response.handleBadRequest();
		return ;
	}
	if (request.getScheme().find("1.1") == std::string::npos)
	{
		this->eventData->response.setStatusCode(Response::BAD_REQUEST);
		std::cout << "wrong http version" << std::endl;
	}

	std::map<int, bool> limit_excepts = wit->get_locations()[i].get_limit_excepts();
    if (method == "GET" && limit_excepts[0])
        this->eventData->response.handleGET(*wit, eventData->request);
    else if (method == "POST" && limit_excepts[1])
        this->eventData->response.handlePOST(*wit, eventData->request);
    else if (method == "PUT" && limit_excepts[2])
        this->eventData->response.handlePOST(*wit, eventData->request);
    else if (method == "DELETE" && limit_excepts[3])
        this->eventData->response.handleDELETE(*wit, eventData->request);
    else {
		this->eventData->response.setStatusCode(Response::METHOD_NOT_ALLOWED);
		this->eventData->response.setHttpVersion("HTTP/1.1");
        std::cout << "wrong method" << std::endl;
	}
}