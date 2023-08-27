#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Transaction.hpp"

class Request : public Transaction{
private:
	std::string httpMethod;
	std::string path;
	std::string	scheme;
	std::string host;

public:
    Request();
    ~Request();
	void	setMethod(std::string method);
	void	setPath(std::string path);
	void	setScheme(std::string scheme);

};

#endif