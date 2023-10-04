#include "../../inc/Webserv.hpp"
#include "../../inc/CgiHandler.hpp"

int	Webserv::SockReceiveData(void) {
	if (find(server_sockets_.begin(), server_sockets_.end(), curr_event_->ident) != server_sockets_.end()) {
		if (ConnectNewClient() == -1)
			return -1;
	}
	else if (find(server_sockets_.begin(), server_sockets_.end(), curr_event_->ident) == server_sockets_.end()) {
		buffer_.clear();
		buffer_.resize(BUFFER_SIZE);
		mapter_ = find_fd_.find(curr_event_->ident);
		for (wit_ = workers_.begin(); wit_ != workers_.end(); ++wit_)
			if (wit_->GetServerSocket() == mapter_->second)
				break ;
		ssize_t len = ReadData(curr_event_->ident, buffer_.data(), BUFFER_SIZE);
		if (len > 0) {
			if (StartReceiveData(len) == -1)
				return -1;
		}
		else if (len == 0) {
			std::cout << "Client " << curr_event_->ident << " disconnected." << std::endl;
			close (curr_event_->ident);
		}
		else
			return -1;
		if (eventData_->GetRequest().GetState() == READ_FINISH) {
			ReadFinish();
			CheckRequestError();
			if (this->eventData_->GetRequest().GetPath().find(".py") != std::string::npos || (this->eventData_->GetRequest().GetMethod() == "POST" && this->eventData_->GetRequest().GetPath().find(".bla") != std::string::npos)) {
				this->eventData_->GetResponse().SetResponseType(CGI);
				this->eventData_->GetCgiHandler().SetClientWriteIdent(curr_event_->ident);
				AddCgiEvent();
			}
			else {
				ChangeEvent(change_list_, curr_event_->ident, EVFILT_READ, EV_DISABLE, 0, 0, curr_event_->udata);
				ChangeEvent(change_list_, curr_event_->ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curr_event_->udata);
			}
		}
	}
	return 0;
}

void	Webserv::SockSendData(void) {
	if (this->eventData_->GetResponse().GetResponseType() == GENERAL)
		MakeResponse(this->eventData_->GetRequest());
	this->eventData_->GetResponse().SendResponse(curr_event_->ident);
	std::map<int, int>::iterator tmp_fd_iter = find_fd_.find(curr_event_->ident);
	find_fd_.erase(tmp_fd_iter);
	delete ((WorkerData *)curr_event_->udata);
	ChangeEvent(change_list_, curr_event_->ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL);
	ChangeEvent(change_list_, curr_event_->ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
	close (curr_event_->ident);
}

int	Webserv::StartReceiveData(int len) {
	buffer_.resize(len);
	if (eventData_->GetRequest().GetState() == HEADER_READ)
	{
		if (ReadHeader() == -1)
			return -1;
	}
	else if (eventData_->GetRequest().GetState() == BODY_READ)
		ReadBody();

	return 0;
}

int	Webserv::ReadHeader(void) {
	std::string temp_data(buffer_.begin(), buffer_.end());
	eventData_->GetRequest().AppendHeader(temp_data);
	eventData_->GetRequest().BodyAppendVec(buffer_);
	size_t pos = eventData_->GetRequest().GetHeaders().find("\r\n\r\n");
	if (pos == std::string::npos)
		return -1;
	else
	{
		std::string temp = eventData_->GetRequest().GetHeaders();
		eventData_->GetRequest().SetHeaders(eventData_->GetRequest().GetHeaders().substr(0, pos + 4));
		eventData_->GetRequest().RemoveCRLF();
		if (eventData_->GetRequest().GetHeaders().find("Content-Length") != std::string::npos)
		{
			size_t body_size = wit_->CheckContentLength(eventData_->GetRequest().GetHeaders());
			if (body_size <= eventData_->GetRequest().GetBody().size())
				eventData_->GetRequest().SetState(READ_FINISH);
			else
				eventData_->GetRequest().SetState(BODY_READ);
		}
		else if (eventData_->GetRequest().GetHeaders().find("Transfer-Encoding") != std::string::npos)
		{
			eventData_->GetRequest().AddRNRNOneTime();
			std::string temp = eventData_->GetRequest().GetBodyCharToStr();
			if (eventData_->GetRequest().Findrn0rn(temp) == 1)
				eventData_->GetRequest().SetState(READ_FINISH);
			else
				eventData_->GetRequest().SetState(BODY_READ);
		}
		else
			eventData_->GetRequest().SetState(READ_FINISH);
	}
	return 0;
}

void	Webserv::ReadBody(void) {
	eventData_->GetRequest().BodyAppendVec(buffer_);
	std::string temp(buffer_.begin(), buffer_.end());
	if (eventData_->GetRequest().GetHeaders().find("Content-Length") != std::string::npos)
	{
		size_t body_size = wit_->CheckContentLength(eventData_->GetRequest().GetHeaders());
		if (body_size <= eventData_->GetRequest().GetBody().size())	//본문을 다 읽으면
			eventData_->GetRequest().SetState(READ_FINISH);
	}
	else if (eventData_->GetRequest().GetHeaders().find("Transfer-Encoding") != std::string::npos)
	{
		if (eventData_->GetRequest().Findrn0rn(temp) == 1)
			eventData_->GetRequest().SetState(READ_FINISH);
	}
}

void	Webserv::ReadFinish(void) {
	wit_->RequestHeaderParse(eventData_->GetRequest());
	if (eventData_->GetRequest().GetHeaders().find("Transfer-Encoding") != std::string::npos)
	{
		eventData_->GetRequest().RemoveRNRNOneTime();
		wit_->ChunkBodyParse(eventData_->GetRequest(), eventData_->GetResponse());
	}
}

void    Webserv::AddCgiEvent(void) {
	this->eventData_->GetCgiHandler().ExecuteChildProcess(this->eventData_->GetRequest());
	this->SetCgiEvent();
}

void    Webserv::CheckRequestError(void) {
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
	WorkerData *udata = new WorkerData(eventData_->GetRequest(), eventData_->GetResponse(), eventData_->GetCgiHandler(), CGIEVENT);

	ChangeEvent(change_list_, this->eventData_->GetCgiHandler().GetReadFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, udata);
	ChangeEvent(change_list_, this->eventData_->GetCgiHandler().GetWriteFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, udata);

	fcntl(this->eventData_->GetCgiHandler().GetReadFd(), F_SETFL, O_NONBLOCK, FD_CLOEXEC);
	fcntl(this->eventData_->GetCgiHandler().GetWriteFd(), F_SETFL, O_NONBLOCK, FD_CLOEXEC);
}

/*
 * 응답 헤더의 흐름
 * - Response 객체를 만드는 시점에서 헤더 값 default로 두기
 * - request 파싱이 끝난 시점에서 예외처리 + 헤더값 일부 변경하기
 * - 또 처리하는 과정에서 헤더 값 수정이 필요한 경우 setter로 변경하기
 */
void    Webserv::MakeResponse(const Request &request) {
	int location_idx = 0;
	for(int i = 0; i < wit_->GetLocations().size(); i++)
	{
		if (request.GetPath().find(wit_->GetLocations()[i].GetUri()) != std::string::npos) {
			if (wit_->GetLocations()[i].GetUri().length() != 1)
			{
				location_idx = i;
				break ;
			}
			location_idx = i;
		}
	}
	/* should be handled right after reading request */
	// if (request.GetScheme().find("1.1") == std::string::npos)
	// {
	// 	this->eventData_->response.SetStatusCode(Response::BAD_REQUEST);
	// 	throw std::runtime_error("wrong http version");
	// }

	std::map<int, bool> limit_excepts = wit_->GetLocations()[location_idx].GetLimitExcepts();
    if (request.GetMethod() == "GET" &&  limit_excepts[METHOD_GET])
        this->eventData_->GetResponse().HandleGET(eventData_->GetRequest(), wit_->GetLocations()[location_idx].GetIndex());
    else if (request.GetMethod() == "POST" && limit_excepts[METHOD_POST])
        this->eventData_->GetResponse().HandlePOST(eventData_->GetRequest());
    // else if (method == "PUT" && limit_excepts[METHOD_PUT])
    //     this->eventData_->response.HandlePOST(eventData_->request);
    else if (request.GetMethod() == "DELETE" && limit_excepts[METHOD_DELETE])
        this->eventData_->GetResponse().HandleDELETE(eventData_->GetRequest());
    else {
		/* 이런것도 함수로 빼자 (send405Response) */
		this->eventData_->GetResponse().SetStatusCode(Response::METHOD_NOT_ALLOWED);
		this->eventData_->GetResponse().Sethttpversion("HTTP/1.1");
	    std::cerr << "wrong http method : " + request.GetMethod() << std::endl;
	}
}