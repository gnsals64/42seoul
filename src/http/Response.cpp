#include "../../inc/Response.hpp"


Response::Response()
{
}

Response::~Response()
{

}

std::string Response::getStatusMessage(int code)
{
    switch (code)
    {
        case OK:
            return "OK";
        case CREATED:
            return "Created";
        case ACCEPTED:
            return "Accepted";
        case NO_CONTENT:
            return "No Content";
        case BAD_REQUEST:
            return "Bad Request";
        case UNAUTHORIZED:
            return "Unauthorized";
        case FORBIDDEN:
            return "Forbidden";
        case NOT_FOUND:
            return "Not Found";
        case INTERNAL_SERVER_ERROR:
            return "Internal Server Error";
        case NOT_IMPLEMENTED:
            return "Not Implemented";
        case SERVICE_UNAVAILABLE:
            return "Service Unavailable";
        case CONTENT_TOO_LARGE:
            return "Content Too Large";
        default:
            return "Unknown";
    }
}

void Response::readFileToBody(const std::string &filePath)
{
    std::ifstream fin;
    fin.open(filePath.c_str());
    if (fin.fail())
        throw std::runtime_error("file open error");
    std::string line;
    while (getline(fin, line))
    {
        line += "\r\n";
		for (int i = 0; i < line.length(); i++)
			this->body.push_back(line[i]);
        // this->body += line;
    }
    fin.close();
}

void Response::generateBody(Worker &worker, const Request &request)
{
    std::string filePath = worker.get_root();
    filePath += request.getPath();

    if (this->checkPath(filePath) == 1) // autoindex 해야하는 상황
    {
        this->generateBody_AutoIndexing(filePath, request);
        return;
    }
    this->readFileToBody(filePath);
}

void Response::generateBody_AutoIndexing(const std::string &path, const Request &request)
{
    this->readFileToBody(AUTO_INDEX_HTML_PATH); // 템플릿 전부 읽기

	std::vector<char> v = this->body;
	std::string string_body(v.begin(), v.end());
    size_t toInsert;

    //title 지정
    toInsert = string_body.find("</title>");
    string_body.insert(toInsert, "Index of " + request.getPath());

    //head 지정
    toInsert = string_body.find("</h1>");
    string_body.insert(toInsert, "Index of " + request.getPath());

    // files 이름 지정
    std::string requestPath = request.getPath();
    if (requestPath.back() != '/') // request path가 '/'로 끝나지 않는 directory일 때 버그 방지
        requestPath.push_back('/');
    std::vector<std::string> fileNames = getFilesInDirectory(path);
    for (size_t i = 0; i < fileNames.size(); i++)
    {
        toInsert = string_body.rfind("<hr>");
        string_body.insert(toInsert,std::string() +
                                   "\t<pre>" + "<a href=\"" + requestPath
                                   + fileNames[i] + "\">" + fileNames[i] + "</a></pre>\r\n");
    }
	std::vector<char> v1(string_body.begin(), string_body.end());
	this->body = v1;
}

// void Response::parsingFromRequest(Worker &worker, const Request &request)
// {
//     if (request.getPath().find("cgi") != std::string::npos)
//     {
//         CgiHandler cgi;
//         this->statusCode = OK;
//         this->connection = "keep-alive";
//         this->contentType = "text/html";
//         this->httpVersion = "1.1";
//         this->location = "";
// //       this->body = "hello";
//         this->body = cgi.executeCgi(request);
//         return ;
//     }

//     std::string method = request.getMethod();

//     switch (method)
//     {
//         case GET:
//             handleGET(worker, request);
//             break;
//         case POST:
//             handlePOST(worker, request);
//             break;
//         case PUT:
//             handlePUT(worker, request);
//             break;
//         case DELETE:
//             handleDELETE(worker, request);
//             break;
//         default:
//             // 올바르지 않은 http 메서드에 대한 에러 처리 함수 (인자는 아직 미정)
//             // handleInvalidMethod();
//             break;
//     }
// }

int Response::checkPath(std::string &filePath)
{
    struct stat buf;

    if (stat(filePath.c_str(), &buf) == -1) // 해당 경로에 파일이 존재 안하면 404Page
    {
        filePath = ERROR_PAGE_404_PATH;
        this->statusCode = NOT_FOUND;
    } else if (S_ISDIR(buf.st_mode)) // 경로일 때
    {
        if (/* directoryListing  == */ true) // 나중에 directory listing 추가해야 함.
        {
            return 1;// directory listing 추후 처리
        } else
        {
            filePath = ERROR_PAGE_404_PATH;
            this->statusCode = NOT_FOUND;
        }
    }
    return 0;
}

std::vector<std::string> Response::getFilesInDirectory(const std::string &dirPath)
{
    DIR *dir_info;
    struct dirent *dir_entry;
    std::vector<std::string> ret;

    if ((dir_info = opendir(dirPath.c_str())) == NULL)
        throw std::runtime_error("opendir error");
    while ((dir_entry = readdir(dir_info)))
    {
        if (std::strcmp(dir_entry->d_name, ".") == 0)
            continue;
        if (dir_entry->d_type == DT_DIR) // directory 일 경우 뒤에 / 추가.
            ret.push_back(std::string(dir_entry->d_name) + "/");
        else
            ret.push_back(dir_entry->d_name);
    }
    closedir(dir_info);

    return ret;
}

void Response::handleBodySizeLimit()
{
    this->statusCode = CONTENT_TOO_LARGE;
    this->connection = "close";
    this->readFileToBody(ERROR_PAGE_413_PATH);
    this->contentLength = this->body.size();
    this->contentType = "text/html";
}

void Response::handleBadRequest()
{
    this->httpVersion = "HTTP/1.1";
    this->statusCode = NOT_FOUND;
    this->connection = "close";
    this->readFileToBody(ERROR_PAGE_404_PATH);
    this->contentLength = this->body.size();
    this->contentType = "text/html";
}

// void Response::setBody(const std::string body) {
//     this->body = body;
// }


void Response::handleGET(Worker &worker, const Request &request)
{
    this->statusCode = OK;
    this->connection = "keep-alive";
    this->contentType = "text/html";
    this->httpVersion = request.getScheme();
    this->location = "";
    try
    {
        generateBody(worker, request);
    }
    catch (std::runtime_error &e)
    {
        // 에러 처리 필요
    }
}

void Response::handlePOST(Worker &worker, const Request &request) {
    DIR *dir_info;

    if ((dir_info = opendir(request.getPath().c_str())) != NULL) {
        this->setHttpVersion("HTTP/1.1");
        this->setStatusCode(405);
        this->contentType = request.getContentType();
        this->connection = "Close";
        closedir(dir_info);
        return ;
    }
    closedir(dir_info);
    this->SetCgiResponse(request);
}

void Response::handlePUT(Worker &worker, const Request &request) {}

void Response::handleDELETE(Worker &worker, const Request &request) {
	this->statusCode = OK;
    this->connection = "keep-alive";
    this->contentType = "text/html";
    this->httpVersion = request.getScheme();
    this->location = "";

	std::string path = "./html" + request.getPath();
	try
	{
		std::string body = deleteCheck(path);
		std::vector<char> v(body.begin(), body.end());
		this->body = v;
	}
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
		this->statusCode = NOT_FOUND;
		std::string failed = "delete failed\n";
		std::vector<char> v(failed.begin(), failed.end());
		this->body = v;
    	return ;
    }
}

void Response::setStatusCode(int data)
{
	this->statusCode = data;
}

void    Response::SetCgiResponse(const Request &request) {
    CgiHandler cgi;
    this->statusCode = OK;
    this->connection = "keep-alive";
    this->contentType = "text/html";
    this->httpVersion = request.getScheme();
    this->location = "";
    this->body = cgi.executeCgi(request);
}

void    Response::SendResponse(int fd) {
    std::string toSend;


    // 임시 하드코딩
    toSend += this->httpVersion;
    toSend += " " + std::to_string(this->statusCode);
    toSend += " " + this->getStatusMessage(this->statusCode);
    toSend += "\r\n";

    if (!this->contentType.empty())
	    toSend += "Content-Type: " + this->contentType + "\r\n";
	if (!this->body.empty())
        toSend += "Content-Length: " + std::to_string(this->body.size()) + "\r\n";
	if (!this->connection.empty())
        toSend += "Connection: " + this->connection + "\r\n";
	//header end
    // std::cout << "body : ";
	// for(int i = 0; i < this->body.size(); i++)
	// 	std::cout << this->body[i];
	// std::cout << std::endl;


    toSend += "\r\n";

    std::string tmp(this->body.begin(), this->body.end());


    toSend += tmp;
    std::cout << "response\n" << toSend << std::endl;
   // std::cout << toSend << std::endl;
    fcntl(fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC); // write함수 non-block으로 변환
    if (send(fd, toSend.c_str(), toSend.size(), 0) == -1)
        throw std::runtime_error("write error");
}

std::string Response::deleteCheck(std::string path) const
{
	if (access(path.c_str(), F_OK) == 0)
	{
		if (access(path.c_str(), W_OK) == 0)
		{
			if (unlink(path.c_str()) == 0)
				return path + " deleted\n";
			throw std::runtime_error("unlink error");
		}
		throw std::runtime_error("permission error");
	}
	else
		throw std::runtime_error("404 not found");
}

void    Response::setHttpVersion(std::string version) {
    this->httpVersion = version;
}