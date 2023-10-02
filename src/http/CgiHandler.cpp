#include "../../inc/CgiHandler.hpp"

CgiHandler::CgiHandler() {
	this->state = NOT_CALLED;
    this->query_string = "";
	this->client_write_ident = -1;
}

CgiHandler::~CgiHandler() {}

CgiHandler& CgiHandler::operator=(const CgiHandler& cgi) {
	this->pid = cgi.pid;
	this->to_cgi[0] = cgi.to_cgi[0];
	this->to_cgi[1] = cgi.to_cgi[1];
	this->from_cgi[0] = cgi.from_cgi[0];
	this->from_cgi[1] = cgi.from_cgi[1];
	this->cgi_path = cgi.cgi_path;
	this->query_string = cgi.query_string;
	this->envp = cgi.envp;
	this->env = cgi.env;
	return *this;
}

pid_t CgiHandler::getPid() const {
    return (this->pid);
}

int CgiHandler::getWriteFd() const {
    return (this->to_cgi[1]);
}

int CgiHandler::getReadFd() const {
    return (this->from_cgi[0]);
}

void CgiHandler::executeChildProcess(const Request &request) {
    this->cgi_path = request.getFullPath();

    if (request.getMethod() == "GET") {
        int query_index = this->cgi_path.find("?", 0);
        if (query_index != std::string::npos)
        {
            this->query_string = this->cgi_path.substr(query_index + 1, this->cgi_path.size() - query_index);
            this->cgi_path = this->cgi_path.substr(0, query_index);
        }
    }

    /* should be handled right after reading request */
    // if (access(this->cgi_path.c_str(), F_OK) != 0)
    //     throw std::runtime_error("404 not found");

	/* should be handled with function */
	// if (pipe(this->to_cgi) < 0 || pipe(this->from_cgi) < 0)
	//      throw std::runtime_error("pipe failed");
	pipe(this->to_cgi);
	pipe(this->from_cgi);
	this->state = CREATE_PIPE;

    this->pid = fork();
    if (this->pid == -1)
        std::cerr << "fork failed" << std::endl;
    else if (this->pid == 0)
    {
        close(this->to_cgi[1]);
        close(this->from_cgi[0]);

        dup2(this->to_cgi[0], STDIN_FILENO);
        dup2(this->from_cgi[1], STDOUT_FILENO);

        close(this->to_cgi[0]);
        close(this->from_cgi[1]);

        fillEnv(request);

		if (request.getPath().find(".bla") != std::string::npos)
			execve("./cgi_tester", NULL, this->envp.data());
		else
        	execve(this->cgi_path.c_str(), NULL, this->envp.data());
    }
}

void CgiHandler::fillEnv(const Request &request) {
    if (request.getMethod() == "POST")
    {
        env["CONTENT_LENGTH"] = "1000000000";
        env["CONTENT_TYPE"] = request.getContentType();
    }
	env["PATH_INFO"] = this->cgi_path;
	if (request.getMethod() == "GET")
		env["QUERY_STRING"] = this->query_string;
	env["REQUEST_METHOD"] = request.getMethod();
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
  	convertEnv();
}

void CgiHandler::convertEnv() {
    std::map<std::string, std::string>::iterator it;
    for (it = env.begin(); it != env.end(); it++)
    {
        std::string concat = it->first + "=" + it->second;
        char *str = new char[concat.length() + 1];
        strcpy(str, concat.c_str());
        envp.push_back(str);
    }
    envp.push_back(0);
	// 끝나고 envp 돌면서 delete 해주기 (+ 구조 바꿀 생각도...)
}

void CgiHandler::closePipeBeforeRead() {
//	close(to_cgi[0]);
//	close(to_cgi[1]);
//	close(from_cgi[1]);
}

void CgiHandler::closePipeBeforeWrite() {
	close(to_cgi[0]);
	close(from_cgi[1]);
}

void CgiHandler::closePipeAfterRead() {
	close(from_cgi[0]);
}

void CgiHandler::closePipeAfterWrite() {
	close(to_cgi[1]);
//	close(from_cgi[0]);
}

CgiState CgiHandler::getState() const {
	return (this->state);
}

void CgiHandler::setState(CgiState state) {
	this->state = state;
}

void CgiHandler::setClientWriteIdent(uintptr_t ident) {
	this->client_write_ident = ident;
}

uintptr_t CgiHandler::getClientWriteIdent() const {
	return (this->client_write_ident);
}