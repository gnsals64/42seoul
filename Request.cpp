#include "Request.hpp"

Request::Request()
{
	this->httpMethod = "";
	this->path = "";
	this->scheme = "";
	this->connection = "";
	this->contentLength = "";
	this->body = "";
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
	this->path = path;
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

void	Request::setBody(std::string body)
{
	this->body = body;
}

void	Request::setState(int data)
{
	this->state = data;
}

void	Request::setHeaders(std::string data)
{
	this->headers = data;
}

std::string	Request::getMethod()
{
	return (this->httpMethod);
}

std::string	Request::getPath()
{
	return (this->path);
}

std::string	Request::getScheme()
{
	return (this->scheme);
}

std::vector<std::string>	Request::getHost()
{
	return (this->host);
}

std::string	Request::getConnection()
{
	return (this->connection);
}

std::string	Request::getContentLength()
{
	return (this->contentLength);
}

std::string Request::getBody()
{
	return (this->body);
}

std::string Request::getHeaders()
{
	return (this->headers);
}

int	Request::getState()
{
	return (this->state);
}

std::vector<char> Request::getPostBody()
{
	return (this->post_body);
}

void	Request::appendHeader(std::string data)
{
	this->headers.append(data);
}

void	Request::appendBody(std::string data)
{
	this->body.append(data);
}

void	Request::pushPostBody(char data)
{
	this->post_body.push_back(data);
}

void	Request::postBodyAppendVec(std::vector<char> data)
{
	this->post_body.insert(this->post_body.end(), data.begin(), data.end());
}

void	Request::removeCRLF()
{
	std::vector <char>::iterator it;
	for (it = this->post_body.begin(); it != this->post_body.end(); it++)
	{
		if (*it == '\r')
		{
			if (*(it + 1) == '\n')
			{
				if (*(it + 2) == '\r')
				{
					if (*(it + 3) == '\n')
					{
						this->post_body.erase(this->post_body.begin(), it + 4);
						break;
					}
				}
			}
		}
	}
}