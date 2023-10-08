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

enum HttpStatusCode
{
	OK = 200,
	CREATED = 201,
	NO_CONTENT = 204,
	MOVED_PERMANENTLY = 301,
	BAD_REQUEST = 400,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,
	LENGTH_REQUIRED = 411,
	PAYLOAD_TOO_LARGE = 413,
	URL_TOO_LONG = 414,
	UNSUPPORTED_MEDIA_TYPE = 415,
	NOT_IMPLEMENTED = 501,
	HTTP_VERSION_NOT_SUPPORTED = 505
};

class Response {
    private:
		ResponseType    type_;
        HttpStatusCode  status_code_;
        std::string     http_version_;
   	 	std::string     connection_;
   		std::string     location_; // 300번대 응답에서 redirect 시 사용.
   		std::string     content_type_;
		std::vector     <char> body_;

        std::string GetStatusMessage(int code);
        void ReadFileToBody(const std::string &path);
        void GenerateBodyAutoIndexing(const Request &request);
        int CheckPath(const std::string path);
        std::vector<std::string> GetFilesInDirectory(const std::string &dirPath);

		void Set505Response();

    public:
        Response();
        ~Response();
		Response& operator=(const Response& response);

		HttpStatusCode GetStatusCode() const;
        void SetStatusCode(HttpStatusCode status);
        void ParsingFromRequest(Worker &worker, const Request &request);
        void HandleBodySizeLimit();
        void HandleBadRequest();
        void SetBody(const std::string body);
        void SendResponse(int fd);
		ResponseType GetResponseType(void) const;
		void SetResponseType(ResponseType type);

        void HandleGet(const Request &request, const std::string index);
        void HandlePost(const Request &request);
        void HandlePut(const Request &request);
        void HandleDelete(const Request &request);
        void SetHttpVersion(std::string version);
		void PushBackBody(char c);
        std::string DeleteCheck(std::string path) const;
		void PrintBody() const;

		void MakeStatusResponse(int status);
};

#endif
