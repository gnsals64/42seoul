#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <fcntl.h>
#include <fstream>

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

class Response {
    private:
        int             status_code_;
		ResponseType    type_;
        std::string     httpversion_;
   	 	std::string     connection_;
   		std::string     location_; // 300번대 응답에서 redirect 시 사용.
   		std::string     contentType_;
		std::vector     <char> body_;

        std::string GetStatusMessage(int code);
        void ReadFileToBody(const std::string &path);
        void GenerateBodyAutoIndexing(const Request &request);
        int CheckPath(const std::string path);
        std::vector<std::string> GetFilesInDirectory(const std::string &dirPath);

    public:
        Response();
        ~Response();
		Response& operator=(const Response& response);

        void ParsingFromRequest(Worker &worker, const Request &request);
        void HandleBodySizeLimit();
        void HandleBadRequest();
        void SetBody(const std::string body);
        void SendResponse(int fd);
		ResponseType GetResponseType(void) const;
		void SetResponseType(ResponseType type);

        void HandleGET(const Request &request, const std::string index);
        void HandlePOST(const Request &request);
        void HandlePUT(const Request &request);
        void HandleDELETE(const Request &request);
        void SetStatusCode(int data);
        void Sethttpversion(std::string version);
		void PushBackBody(char c);
        std::string DeleteCheck(std::string path) const;
		void PrintBody() const;

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
