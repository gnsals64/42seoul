#include "Request.hpp"

Request::Request()
{

}

Request::~Request()
{

}

std::string Request::getPath() const
{
    return this->path;
}