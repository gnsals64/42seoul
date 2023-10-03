#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <fcntl.h>
#include <fstream>

#include "Transaction.hpp"
#include "Worker.hpp"
#include "Request.hpp"
#include "CgiHandler.hpp"

#define ERROR_PAGE_404_PATH "./templates/404error.html"
#define ERROR_PAGE_413_PATH "./templates/413error.html"
#define AUTO_INDEX_HTML_PATH "./templates/autoindex.html"

class Worker;
class Request;

enum ResponseType {
	GENERAL,
	CGI
};

class Response : public Transaction {
    private:
        int statusCode;
		ResponseType type;
        std::string getStatusMessage(int code);
        void readFileToBody(const std::string &path);
        void generateBody_AutoIndexing(const Request &request);
        int checkPath(const std::string path);
        std::vector<std::string> getFilesInDirectory(const std::string &dirPath);

    public:
        Response();
        ~Response();
		Response& operator=(const Response& response);

        void parsingFromRequest(Worker &worker, const Request &request);
        void handleBodySizeLimit();
        void handleBadRequest();
        void setBody(const std::string body);
        void SendResponse(int fd);
		ResponseType getResponseType(void) const;
		void setResponseType(ResponseType type);

        void handleGET(const Request &request, const std::string index);
        void handlePOST(const Request &request);
        void handlePUT(const Request &request);
        void handleDELETE(const Request &request);
        void setStatusCode(int data);
        void sethttpversion(std::string version);
		void pushBackBody(char c);
        std::string deleteCheck(std::string path) const;
		void printBody() const;

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
            METHOD_NOT_ALLOWED = 405,
            CONTENT_TOO_LARGE = 413,
            INTERNAL_SERVER_ERROR = 500,
            NOT_IMPLEMENTED = 501,
            SERVICE_UNAVAILABLE = 503,
        };
};

#endif
