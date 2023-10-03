#include "../../inc/Request.hpp"

Request::Request() {
	this->httpmethod_ = "";
	this->path = "";
	this->scheme = "";
	this->connection = "";
	this->contentLength = "0";
	this->state = HEADER_READ;
}

Request::~Request() {

}

Request& Request::operator=(const Request& request) {
	this->headers_ = request.headers_;
	this->httpmethod_ = request.httpmethod_;
	this->path = request.path;
	this->full_path = request.full_path;
	this->scheme = request.scheme;
	this->host = request.host;
	this->connection = request.connection;
	this->contentLength = request.contentLength;
	this->body_str = request.body_str;
	this->state = request.state;
	return *this;
}

void	Request::setMethod(std::string method) {
	this->httpmethod_ = method;
}

void	Request::setPath(std::string path) {
	if (path[0] == '/') {
		while(true) {
			if (path[1] != '/')
				break ;
			if (path[1] == '/')
				path.erase(1, 1);
		}
	}
	this->path = path;
}

void    Request::setFullPath(std::string full_path) {
    this->full_path = full_path;
}

void	Request::setScheme(std::string scheme) {
	this->scheme = scheme;
}

void	Request::pushBackHost(std::string host) {
	this->host.push_back(host);
}

void	Request::setConnection(std::string connection) {
	this->connection = connection;
}

void	Request::setContentLength(std::string contentLength) {
	this->contentLength = contentLength;
}

void	Request::setState(int data) {
	this->state = data;
}

void	Request::setHeaders(std::string data) {
	this->headers_ = data;
}

void	Request::setBodyClear() {
	this->body.clear();
}

std::string	Request::getMethod() const {
	return (this->httpmethod_);
}

std::string Request::getFullPath() const {
    return (this->full_path);
}

std::string	Request::getPath() const {
	return (this->path);
}

std::string	Request::getScheme() const {
	return (this->scheme);
}

std::vector<std::string>	Request::getHost() const {
	return (this->host);
}

std::string	Request::getConnection() const {
	return (this->connection);
}

std::string	Request::getContentLength() const {
	return (this->contentLength);
}

std::vector<char> Request::getBody() const {
	return (this->body);
}

std::string Request::getBodyStr() const {
	return (this->body_str);
}

std::string Request::getBodyCharToStr() const {
	std::string temp(this->body.begin(), this->body.end());
	return (temp);
}

std::string Request::getHeaders() const {
	return (this->headers_);
}

int	Request::getState() const {
	return (this->state);
}

std::string Request::getContentType() const {
    return this->contentType;
}

void	Request::appendHeader(std::string data) {
	this->headers_.append(data);
}

void	Request::pushPostBody(char data) {
	this->body.push_back(data);
}

void	Request::BodyAppendVec(std::vector<char> data) {
	this->body.insert(this->body.end(), data.begin(), data.end());
}

void	Request::appendBodyStr(std::string data) {
	this->body_str.append(data);
}

void	Request::setContentType(std::string type) {
	this->contentType = type;
}

void	Request::removeCRLF() {
	std::vector <char>::iterator it;
	for (it = this->body.begin(); it != this->body.end(); it++)
	{
		if (*it == '\r')
		{
			if (*(it + 1) == '\n')
			{
				if (*(it + 2) == '\r')
				{
					if (*(it + 3) == '\n')
					{
						this->body.erase(this->body.begin(), it + 4);
						break;
					}
				}
			}
		}
	}
}

int	Request::Findrn0rn(std::string temp) {
	if (temp.find("\r\n0\r\n") != std::string::npos)
		return (1);
	else
		return (0);
}

void	Request::AddRNRNOneTime() {
	this->body.insert(this->body.begin(), '\n');
	this->body.insert(this->body.begin(), '\r');
}

void	Request::RemoveRNRNOneTime() {
	this->body.erase(this->body.begin());
	this->body.erase(this->body.begin());
}