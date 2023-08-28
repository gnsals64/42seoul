#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Transaction.hpp"

class Request : public Transaction{
private:
	std::string httpMethod;
	std::string path;
	std::string	scheme;
	std::vector <std::string> host;
	std::string	connection;
	std::string	contentLength;
	std::string	body;

public:
    Request();
    ~Request();
	void	setMethod(std::string method);
	void	setPath(std::string path);
	void	setScheme(std::string scheme);
	void	pushBackHost(std::string host);
	void	setConnection(std::string connection);
	void	setContentLength(std::string contentLength);
	void	setBody(std::string body);

	std::string	getMethod();
	std::string	getPath();
	std::string	getScheme();
	std::vector<std::string>	getHost();
	std::string	getConnection();
	std::string getContentLength();
	std::string getBody();
};

#endif