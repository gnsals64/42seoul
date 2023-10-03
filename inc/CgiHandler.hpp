#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unistd.h>

#include "Request.hpp"

class Request;
class Webserv;

enum CgiState {
	NOT_CALLED,
	CREATE_PIPE,
	WRITE_PIPE,
	READ_PIPE
};

class CgiHandler {
private:
    pid_t pid;
    int to_cgi[2];
    int from_cgi[2];
    std::string cgi_path;
    std::string query_string;
    std::vector<char*> envp;
    std::map<std::string, std::string> env;
	CgiState state;
	uintptr_t client_write_ident;

public:
    CgiHandler();
    ~CgiHandler();
	CgiHandler& operator=(const CgiHandler& cgi);

    pid_t getPid() const;
    int getWriteFd() const;
    int getReadFd() const;
	void closePipeBeforeRead();
	void closePipeBeforeWrite();
	void closePipeAfterRead();
	void closePipeAfterWrite();
    void executeChildProcess(const Request &request);
    void fillEnv(const Request &request);
    void convertEnv();
	CgiState getState() const;
	void setState(CgiState state);
	void setClientWriteIdent(uintptr_t ident);
	uintptr_t getClientWriteIdent(void) const;
};

#endif
