#include "../../inc/Webserv.hpp"
#include "../../inc/CgiHandler.hpp"
#include "../../inc/Transaction.hpp"

int	Webserv::SockReceiveData(void) {
	if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) != server_sockets.end())
	{
		if (ConnectNewClient() == -1)
			return -1;
	}
	else if (find(server_sockets.begin(), server_sockets.end(), curr_event->ident) == server_sockets.end())
	{
		buffer.clear();
		buffer.resize(BUFFER_SIZE);
		mapter = find_fd.find(curr_event->ident);
		for (wit = workers.begin(); wit != workers.end(); ++wit)
			if (wit->get_server_socket() == mapter->second)
				break ;
		ssize_t len = readData(curr_event->ident, buffer.data(), BUFFER_SIZE);
		if (len > 0)
		{
			if (StartReceiveData(len) == -1)
				return -1;
		}
		else if (len == 0)
		{
			std::cout << "Client " << curr_event->ident << " disconnected." << std::endl;
			close (curr_event->ident);
		}
		else
			return -1;
		if (eventData->getRequest().getState() == READ_FINISH)
		{
			ReadFinish();
			CheckRequestError();
			if (this->eventData->getRequest().getPath().find(".py") != std::string::npos || (this->eventData->getRequest().getMethod() == "POST" && this->eventData->getRequest().getPath().find(".bla") != std::string::npos))
			{
				this->eventData->getResponse().setResponseType(CGI);
				this->eventData->getCgiHandler().setClientWriteIdent(curr_event->ident);
				AddCgiEvent();
			}
			else
			{
				ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event->udata);
				ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event->udata);
			}
		}
	}
	return 0;
}

void	Webserv::SockSendData(void) {
	if (this->eventData->getResponse().getResponseType() == GENERAL)
		MakeResponse(this->eventData->getRequest());
	this->eventData->getResponse().SendResponse(curr_event->ident);
	std::map<int, int>::iterator tmp_fd_iter = find_fd.find(curr_event->ident);
	find_fd.erase(tmp_fd_iter);
	delete ((WorkerData *)curr_event->udata);
	ChangeEvent(change_list, curr_event->ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
	ChangeEvent(change_list, curr_event->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close (curr_event->ident);
}

int	Webserv::StartReceiveData(int len) {
	buffer.resize(len);
	if (eventData->getRequest().getState() == HEADER_READ)
	{
		if (ReadHeader() == -1)
			return -1;
	}
	else if (eventData->getRequest().getState() == BODY_READ)
		ReadBody();

	return 0;
}

int	Webserv::ReadHeader(void) {
	std::string temp_data(buffer.begin(), buffer.end());
	eventData->getRequest().appendHeader(temp_data);
	eventData->getRequest().BodyAppendVec(buffer);
	size_t pos = eventData->getRequest().getHeaders().find("\r\n\r\n");
	if (pos == std::string::npos)
		return -1;
	else
	{
		std::string temp = eventData->getRequest().getHeaders();
		eventData->getRequest().setHeaders(eventData->getRequest().getHeaders().substr(0, pos + 4));
		eventData->getRequest().removeCRLF();
		if (eventData->getRequest().getHeaders().find("Content-Length") != std::string::npos)
		{
			size_t body_size = wit->checkContentLength(eventData->getRequest().getHeaders());
			if (body_size <= eventData->getRequest().getBody().size())
				eventData->getRequest().setState(READ_FINISH);
			else
				eventData->getRequest().setState(BODY_READ);
		}
		else if (eventData->getRequest().getHeaders().find("Transfer-Encoding") != std::string::npos)
		{
			eventData->getRequest().AddRNRNOneTime();
			std::string temp = eventData->getRequest().getBodyCharToStr();
			if (eventData->getRequest().Findrn0rn(temp) == 1)
				eventData->getRequest().setState(READ_FINISH);
			else
				eventData->getRequest().setState(BODY_READ);
		}
		else
			eventData->getRequest().setState(READ_FINISH);
	}
	return 0;
}

void	Webserv::ReadBody(void) {
	eventData->getRequest().BodyAppendVec(buffer);
	std::string temp(buffer.begin(), buffer.end());
	if (eventData->getRequest().getHeaders().find("Content-Length") != std::string::npos)
	{
		size_t body_size = wit->checkContentLength(eventData->getRequest().getHeaders());
		if (body_size <= eventData->getRequest().getBody().size())	//본문을 다 읽으면
			eventData->getRequest().setState(READ_FINISH);
	}
	else if (eventData->getRequest().getHeaders().find("Transfer-Encoding") != std::string::npos)
	{
		if (eventData->getRequest().Findrn0rn(temp) == 1)
			eventData->getRequest().setState(READ_FINISH);
	}
}

void	Webserv::ReadFinish(void) {
	wit->requestHeaderParse(eventData->getRequest());
	if (eventData->getRequest().getHeaders().find("Transfer-Encoding") != std::string::npos)
	{
		eventData->getRequest().RemoveRNRNOneTime();
		wit->chunkBodyParse(eventData->getRequest(), eventData->getResponse());
	}
}

void    Webserv::AddCgiEvent(void)
{
	this->eventData->getCgiHandler().executeChildProcess(this->eventData->getRequest());
	this->SetCgiEvent();
}

void    Webserv::CheckRequestError(void)
{
	/*
	 * 요청을 다 읽은 시점에서 예외처리 필요
	 * 1) 경로가 올바른지?
	 * 2) 파일 및 폴더 열 수 있는지?
	 * 3) 지원하지 않는 요청 메서드인지?
	 * 4) http 버전이 잘못되었는지?
	 * 5) content length 관련 : client_max_body_size를 넘는지?
	 * -> Request에 집어넣은 헤더 모두 검사한다고 생각하면 될 듯
	 *
	 * 그리고 이 여러 에러를 처리하기 위해서 각 에러를 처리해주는 함수들을 만들면 좋을듯
	 * 이 함수들은 generateResponse 같은 함수로 이미 들어가있는 헤더를 패킷의 형식으로 만들어서 보내면 될 듯
	 * -> 찾아보니 우리의 sendResponse 함수를 사용하면 됨, 그러나 수정이 매우 필요해보임
	 * 즉, 헤더의 값들은 각 함수 내에서 각자의 값으로 바꾼뒤 패킷 만들어서 전송
	 * ex) Send404Response(), Send405Response()
	 */
}

void	Webserv::SetCgiEvent(void) {
	WorkerData *udata = new WorkerData(eventData->getRequest(), eventData->getResponse(), eventData->getCgiHandler(), CGIEVENT);

	ChangeEvent(change_list, this->eventData->getCgiHandler().getReadFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, udata);
	ChangeEvent(change_list, this->eventData->getCgiHandler().getWriteFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, udata);

	fcntl(this->eventData->getCgiHandler().getReadFd(), F_SETFL, O_NONBLOCK, FD_CLOEXEC);
	fcntl(this->eventData->getCgiHandler().getWriteFd(), F_SETFL, O_NONBLOCK, FD_CLOEXEC);
}

/*
 * 응답 헤더의 흐름
 * - Response 객체를 만드는 시점에서 헤더 값 default로 두기
 * - request 파싱이 끝난 시점에서 예외처리 + 헤더값 일부 변경하기
 * - 또 처리하는 과정에서 헤더 값 수정이 필요한 경우 setter로 변경하기
 */
void    Webserv::MakeResponse(const Request &request) {
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
	/* should be handled right after reading request */
	// if (request.getScheme().find("1.1") == std::string::npos)
	// {
	// 	this->eventData->response.setStatusCode(Response::BAD_REQUEST);
	// 	throw std::runtime_error("wrong http version");
	// }

	std::map<int, bool> limit_excepts = wit->get_locations()[location_idx].get_limit_excepts();
    if (request.getMethod() == "GET" &&  limit_excepts[METHOD_GET])
        this->eventData->getResponse().handleGET(eventData->getRequest(), wit->get_locations()[location_idx].get_index());
    else if (request.getMethod() == "POST" && limit_excepts[METHOD_POST])
        this->eventData->getResponse().handlePOST(eventData->getRequest());
    // else if (method == "PUT" && limit_excepts[METHOD_PUT])
    //     this->eventData->response.handlePOST(eventData->request);
    else if (request.getMethod() == "DELETE" && limit_excepts[METHOD_DELETE])
        this->eventData->getResponse().handleDELETE(eventData->getRequest());
    else {
		/* 이런것도 함수로 빼자 (send405Response) */
		this->eventData->getResponse().setStatusCode(Response::METHOD_NOT_ALLOWED);
		this->eventData->getResponse().setHttpVersion("HTTP/1.1");
	    std::cerr << "wrong http method : " + request.getMethod() << std::endl;
	}
}