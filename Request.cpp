#include "Request.hpp"

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

std::vector<char> Request::getBody()
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
}

int	Request::Findrn0rn()
{
	std::vector <char>::iterator it;
	for (it = this->body.begin(); it != this->body.end(); it++)
	{
		if (*it == '\r')
		{
			if (*(it + 1) == '\n')
			{
				if (*(it + 2) == '0')
				{
					if (*(it + 3) == '\r')
					{
						if (*(it + 4) == '\n')
						{
							return (1);
						}
					}
				}
			}
		}
	}
	return (0);
}