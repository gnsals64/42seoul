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
		buffer.clear();
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
			eventData->request.AddRNRNOneTime();
			if (eventData->request.Findrn0rn(eventData->request.getBodyCharToStr()) == 1)
				eventData->request.setState(READ_FINISH);
			else
				eventData->request.setState(BODY_READ);
			// eventData->request.appendBodyStr(temp_data);
			// std::string temp_str = eventData->request.getBodyStr();
			// if (eventData->request.Findrn0rn(temp_str) == 1)
			// 	eventData->request.setState(READ_FINISH);
			// else
			// 	eventData->request.setState(BODY_READ);

		}
		else
			eventData->request.setState(READ_FINISH);
	}
	return 0;
}

void	Webserv::ReadBody(void) {
	eventData->request.BodyAppendVec(buffer);
	std::string temp(buffer.begin(), buffer.end());
	if (eventData->request.getHeaders().find("Content-Length") != std::string::npos)
	{
		size_t body_size = wit->checkContentLength(eventData->request.getHeaders());
		if (body_size <= eventData->request.getBody().size())	//본문을 다 읽으면
			eventData->request.setState(READ_FINISH);
	}
	else if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
	{
		std::cout << "body_size = " << eventData->request.getBody().size() << std::endl;
		if (eventData->request.Findrn0rn(temp) == 1)
			eventData->request.setState(READ_FINISH);
}

void	Webserv::ReadFinish(void) {
	wit->requestHeaderParse(eventData->request);
	if (eventData->request.getHeaders().find("Transfer-Encoding") != std::string::npos)
		wit->chunkBodyParse(eventData->request, eventData->response);
	ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event->udata);	//write 이벤트 발생
	try
	{
	    MakeResponse(eventData->request);
    }
	catch (std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << eventData->request.getMethod() << " " << eventData->request.getFullPath() << std::endl;
	}
}

void    Webserv::MakeResponse(const Request &request) {
    if (this->eventData->request.getPath().find(".py") != std::string::npos)
    {
        this->eventData->response.SetCgiResponse(request);
        return ;
    }

    std::string method = this->eventData->request.getMethod();

	int location_idx = 0;
	for(int i = 0; i < wit->get_locations().size(); i++)
	{
		if (request.getPath().find(wit->get_locations()[i].get_uri()) != std::string::npos) {
			if (wit->get_locations()[i].get_uri().length() != 1)
			{
				location_idx = i;
				break ;
			}
			location_idx = i;
		}
	}
	if (request.getScheme().find("1.1") == std::string::npos)
	{
		this->eventData->response.setStatusCode(Response::BAD_REQUEST);
		throw std::runtime_error("wrong http version");
	}

	std::map<int, bool> limit_excepts = wit->get_locations()[location_idx].get_limit_excepts();
    if (method == "GET" &&  limit_excepts[METHOD_GET])
        this->eventData->response.handleGET(eventData->request, wit->get_locations()[location_idx].get_index());
    else if (method == "POST" && limit_excepts[METHOD_POST])
        this->eventData->response.handlePOST(eventData->request);
    else if (method == "PUT" && limit_excepts[METHOD_PUT])
        this->eventData->response.handlePOST(eventData->request);
    else if (method == "DELETE" && limit_excepts[METHOD_DELETE])
        this->eventData->response.handleDELETE(eventData->request);
    else {
		this->eventData->response.setStatusCode(Response::METHOD_NOT_ALLOWED);
		this->eventData->response.setHttpVersion("HTTP/1.1");
	    throw std::runtime_error("wrong http method : " + request.getMethod());
	}
}