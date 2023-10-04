#include "../../inc/Request.hpp"

Request::Request() {
	this->httpmethod_ = "";
	this->path_ = "";
	this->scheme_ = "";
	this->connection_ = "";
	this->contentLength_ = "0";
	this->state_ = HEADER_READ;
}

Request::~Request() {

}

Request& Request::operator=(const Request& request) {
	this->headers_ = request.headers_;
	this->httpmethod_ = request.httpmethod_;
	this->path_ = request.path_;
	this->full_path_ = request.full_path_;
	this->scheme_ = request.scheme_;
	this->host_ = request.host_;
	this->connection_ = request.connection_;
	this->contentLength_ = request.contentLength_;
	this->body_str_ = request.body_str_;
	this->state_ = request.state_;
	return *this;
}

void	Request::SetMethod(std::string method) {
	this->httpmethod_ = method;
}

void	Request::SetPath(std::string path) {
	if (path[0] == '/') {
		while(true) {
			if (path[1] != '/')
				break ;
			if (path[1] == '/')
				path.erase(1, 1);
		}
	}
	this->path_ = path;
}

void    Request::SetFullPath(std::string full_path) {
    this->full_path_ = full_path;
}

void	Request::SetScheme(std::string scheme) {
	this->scheme_ = scheme;
}

void	Request::PushBackHost(std::string host) {
	this->host_.push_back(host);
}

void	Request::SetConnection(std::string connection) {
	this->connection_ = connection;
}

void	Request::SetContentLength(std::string contentLength_) {
	this->contentLength_ = contentLength_;
}

void	Request::SetState(int data) {
	this->state_ = data;
}

void	Request::SetHeaders(std::string data) {
	this->headers_ = data;
}

void	Request::SetBodyClear() {
	this->body_.clear();
}

std::string	Request::GetMethod() const {
	return (this->httpmethod_);
}

std::string Request::GetFullPath() const {
    return (this->full_path_);
}

std::string	Request::GetPath() const {
	return (this->path_);
}

std::string	Request::GetScheme() const {
	return (this->scheme_);
}

std::vector<std::string>	Request::GetHost() const {
	return (this->host_);
}

std::string	Request::GetConnection() const {
	return (this->connection_);
}

std::string	Request::GetContentLength() const {
	return (this->contentLength_);
}

std::vector<char> Request::GetBody() const {
	return (this->body_);
}

std::string Request::GetBodyStr() const {
	return (this->body_str_);
}

std::string Request::GetBodyCharToStr() const {
	std::string temp(this->body_.begin(), this->body_.end());
	return (temp);
}

std::string Request::GetHeaders() const {
	return (this->headers_);
}

int	Request::GetState() const {
	return (this->state_);
}

std::string Request::GetContentType() const {
    return this->contentType_;
}

void	Request::AppendHeader(std::string data) {
	this->headers_.append(data);
}

void	Request::PushPostBody(char data) {
	this->body_.push_back(data);
}

void	Request::BodyAppendVec(std::vector<char> data) {
	this->body_.insert(this->body_.end(), data.begin(), data.end());
}

void	Request::AppendBodyStr(std::string data) {
	this->body_str_.append(data);
}

void	Request::SetContentType(std::string type) {
	this->contentType_ = type;
}

void	Request::RemoveCRLF() {
	std::vector <char>::iterator it;
	for (it = this->body_.begin(); it != this->body_.end(); it++)
	{
		if (*it == '\r')
		{
			if (*(it + 1) == '\n')
			{
				if (*(it + 2) == '\r')
				{
					if (*(it + 3) == '\n')
					{
						this->body_.erase(this->body_.begin(), it + 4);
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
	this->body_.insert(this->body_.begin(), '\n');
	this->body_.insert(this->body_.begin(), '\r');
}

void	Request::RemoveRNRNOneTime() {
	this->body_.erase(this->body_.begin());
	this->body_.erase(this->body_.begin());
}