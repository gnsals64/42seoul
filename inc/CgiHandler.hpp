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

class CgiHandler {
private:
    pid_t pid;
    int to_cgi[2];
    int from_cgi[2];
    std::string cgi_path;
    std::string query_string;
    std::vector<char*> envp;
    std::map<std::string, std::string> env;

public:
    CgiHandler();
    ~CgiHandler();

    pid_t getPid() const;
    int getWriteFd() const;
    int getReadFd() const;
    void executeChildProcess(const Request &request);
    void fillEnv(const Request &request);
    void convertEnv();
};

#endif
