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
		void	setState(int setstate);
		void	setHeaders(std::string data);
		void	setBodyClear();
		void	setContentType(std::string type);
		std::string	getMethod() const;
		std::string	getPath() const;
		std::string	getScheme() const;
		std::vector<std::string>	getHost() const;
		std::string	getConnection() const;
		std::string getContentLength() const;
		std::string getHeaders() const;
		int	getState() const;
		std::vector<char> getBody() const;
        std::string getContentType() const;

		void	appendHeader(std::string data);
		void	pushPostBody(char data);
		void	BodyAppendVec(std::vector<char> data);
		void	removeCRLF();
		void	parsingFromData(std::string data);

		int	Findrn0rn();
};

#endif