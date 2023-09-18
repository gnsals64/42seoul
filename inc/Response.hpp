#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <fcntl.h>

#include "Transaction.hpp"
// #include "Worker.hpp"
#include "Request.hpp"

class Worker;

class Response : public Transaction
{
	private:
		// 임시.. 나중에 다 추가해야 함.
		enum HttpStatusCode
		{
			OK = 200,
			CREATED = 201,
			ACCEPTED = 202,
			NO_CONTENT = 204,
			BAD_REQUEST = 400,
			UNAUTHORIZED = 401,
			FORBIDDEN = 403,
			NOT_FOUND = 404,
			CONTENT_TOO_LARGE = 413,
			INTERNAL_SERVER_ERROR = 500,
			NOT_IMPLEMENTED = 501,
			SERVICE_UNAVAILABLE = 503,
		};

		int statusCode;
	//   void readFileToBody(const std::string &filePath);
	// 	void generateBody(Worker &worker, const Request &request);
	//   void generateBody_AutoIndexing(const std::string &path, const Request &request);
	//   int checkPath(std::string &filePath);
	//   std::vector<std::string> getFilesInDirectory(const std::string &dirPath);

	public:
		Response();
		~Response();
		std::string getStatusMessage(int code);
		int	getStatusCode();

		// void parsingFromRequest(Worker &worker, const Request &request);
		// void send(int fd);
		// void handleBodySizeLimit();

		// void handleGET(Worker &worker, const Request &request);
		// void handlePOST(Worker &worker, const Request &request);
		// void handlePUT(Worker &worker, const Request &request);
		// void handleDELETE(Worker &worker, const Request &request);
		void setStatusCode(int data);
};

#endif