#include "Request.hpp"

Request::Request()
{

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