#include "../../inc/CgiHandler.hpp"

CgiHandler::CgiHandler()
{
    this->query_string = "";
}

CgiHandler::~CgiHandler() {}

pid_t CgiHandler::getPid() const
{
    return (this->pid);
}

int CgiHandler::getWriteFd() const
{
    return (this->to_cgi[1]);
}

int CgiHandler::getReadFd() const
{
    return (this->from_cgi[0]);
}

void CgiHandler::executeChildProcess(const Request &request)
{
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

    if (pipe(this->to_cgi) < 0 || pipe(this->from_cgi) < 0)
        ;
        // throw std::runtime_error("pipe failed");

    this->pid = fork();
    if (this->pid == -1)
        throw std::runtime_error("fork failed");
    else if (this->pid == 0)
    {
        // Child process (CGI script)
        close(this->to_cgi[1]);
        close(this->from_cgi[0]);

        // Redirect stdin and stdout
        dup2(this->to_cgi[0], STDIN_FILENO);
        dup2(this->from_cgi[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(this->to_cgi[0]);
        close(this->from_cgi[1]);

        fillEnv(request);

		if (request.getPath().find(".bla") != std::string::npos)
			execve("./cgi_tester", NULL, this->envp.data());
		else
        	execve(this->cgi_path.c_str(), NULL, this->envp.data());
        // throw std::runtime_error("cgi execute failed");
    }
    else
    {
        /*
        // Parent process (Server)
        close(to_cgi[0]);
        close(from_cgi[1]);

        // Send POST data to CGI script through to_cgi pipe
        if (request.getMethod() == "POST")
        {
            std::vector<char> v = request.getBody();
            std::string s(v.begin(), v.end());
            std::cerr << s << std::endl;
            write(to_cgi[1], s.c_str(), s.length());
            close(to_cgi[1]);
        }

        char buff[4096];
        ssize_t bytesRead;
        std::vector<char> body;

        // Read CGI script's output from from_cgi pipe
        while ((bytesRead = read(from_cgi[0], buff, sizeof(buff))) > 0)
        {
            for (int i = 0; i < bytesRead; i++)
                body.push_back(buff[i]);
        }
        close(from_cgi[0]);
        */
    }
}

void CgiHandler::fillEnv(const Request &request)
{
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

void CgiHandler::convertEnv()
{
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

// void CgiHandler::sendCgiResult()
// {

// }