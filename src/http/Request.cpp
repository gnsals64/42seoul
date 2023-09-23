#include "../../inc/Request.hpp"

Request::Request()
{
	this->httpMethod = "";
	this->path = "";
	this->scheme = "";
	this->connection = "";
	this->contentLength = "";
	this->state = HEADER_READ;
}

Request::~Request()
{

}

void	Request::setMethod(std::string method)
{
	this->httpMethod = method;
}

void	Request::setPath(std::string path)
{
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

void    Request::setFullPath(std::string full_path)
{
    this->full_path = full_path;
}

void	Request::setScheme(std::string scheme)
{
	this->scheme = scheme;
}

void	Request::pushBackHost(std::string host)
{
	this->host.push_back(host);
}

void	Request::setConnection(std::string connection)
{
	this->connection = connection;
}

void	Request::setContentLength(std::string contentLength)
{
	this->contentLength = contentLength;
}

void	Request::setState(int data)
{
	this->state = data;
}

void	Request::setHeaders(std::string data)
{
	this->headers = data;
}

void	Request::setBodyClear()
{
	this->body.clear();
}

std::string	Request::getMethod() const
{
	return (this->httpMethod);
}

std::string Request::getFullPath() const
{
    return (this->full_path);
}

std::string	Request::getPath() const
{
	return (this->path);
}

std::string	Request::getScheme() const
{
	return (this->scheme);
}

std::vector<std::string>	Request::getHost() const
{
	return (this->host);
}

std::string	Request::getConnection() const
{
	return (this->connection);
}

std::string	Request::getContentLength() const
{
	return (this->contentLength);
}

std::vector<char> Request::getBody() const
{
	return (this->body);
}

std::string Request::getHeaders() const
{
	return (this->headers);
}

int	Request::getState() const
{
	return (this->state);
}

std::string Request::getContentType() const
{
    return this->contentType;
}

void	Request::appendHeader(std::string data)
{
	this->headers.append(data);
}

void	Request::pushPostBody(char data)
{
	this->body.push_back(data);
}

void	Request::BodyAppendVec(std::vector<char> data)
{
	this->body.insert(this->body.end(), data.begin(), data.end());
}

void	Request::setContentType(std::string type) {
	this->contentType = type;
}

void	Request::removeCRLF()
{
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
	// this->body.insert(body.begin(), '\n');
	// this->body.insert(body.begin(), '\r');
}

int	Request::Findrn0rn(std::string temp)
{
	if (temp.find("\r\n0\r\n") != std::string::npos)
		return (1);
	else
		return (0);
	// std::vector <char>::iterator it;
	// for (it = this->body.begin(); it != this->body.end(); it++)
	// {
	// 	if (*it == '\r')
	// 	{
	// 		if (it + 1 < this->body.end() && *(it + 1) == '\n')
	// 		{
	// 			if (it + 2 < this->body.end() && *(it + 2) == '0')
	// 			{
	// 				if (it + 3 < this->body.end() && *(it + 3) == '\r')
	// 				{
	// 					if (it + 4 < this->body.end() && *(it + 4) == '\n')
	// 					{
	// 						return (1);
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// return (0);
}

void	Request::AddRNRNOneTime()
{
	this->body.insert(this->body.begin(), '\n');
	this->body.insert(this->body.begin(), '\r');
}

void	Request::RemoveRNRNOneTime()
{
	this->body.erase(this->body.begin());
	this->body.erase(this->body.begin());
}

// void Request::parsingFromData(std::string data)
// {
//     // max size_error 가정
//     //throw std::runtime_error("client body size error");

//     //test code
// 	std::stringstream stream;
// 	stream.str(data);

//     std::string method;
//     stream >> method;
//     stream >> this->path;

// 	std::string s;
// 	while (stream >> s)
// 	{
// 		if (s == "Content-Length:")
// 			stream >> this->contentLength;
// 		if (s == "Content-Type:")
// 			stream >> this->contentType;
// 	}

// 	size_t bodyStart = data.find("\r\n\r\n") + 4; // 빈 줄 다음부터 본문
//     this->body = data.substr(bodyStart, this->contentLength);


//     this->host.push_back("localhost:8080");
//     if (method == "GET")
//         this->httpMethod = "GET";
//     else if (method == "POST")
//         this->httpMethod = "POST";
//     else if (method == "PUT")
//         this->httpMethod = "PUT";
//     else if (method == "DELETE")
//         this->httpMethod = "DELETE";
// }