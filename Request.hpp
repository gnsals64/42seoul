#ifndef REQUEST_HPP
#define REQUEST_HPP

# define HEADER_READ 0
# define BODY_READ 1
# define READ_FINISH 2
#include "Transaction.hpp"
#include <sys/time.h>

class Request : public Transaction{
private:
	std::string headers;
	std::string httpMethod;
	std::string path;
	std::string	scheme;
	std::vector <std::string> host;
	std::string	connection;
	std::string	contentLength;
	std::string	body;
	std::vector<char> post_body;
	int	state;

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
	void	setState(int setstate);

	std::string	getMethod();
	std::string	getPath();
	std::string	getScheme();
	std::vector<std::string>	getHost();
	std::string	getConnection();
	std::string getContentLength();
	std::string getBody();
	std::string getHeaders();
	int	getState();
	std::vector<char> getPostBody();

	void	appendHeader(std::string data);
	void	appendBody(std::string data);
	void	pushPostBody(char data);
	void	clearAll();
};

#endif