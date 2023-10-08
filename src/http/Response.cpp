#include "../../inc/Response.hpp"


Response::Response() {
	this->type_ = GENERAL;
	this->status_code_ = OK;
	this->http_version_ = "HTTP/1.1";
	this->allow_ = "";
	this->connection_ = "keep-alive";
	this->location_ = "";
	this->content_type_ = "text/html";
}

Response::~Response() {}

Response& Response::operator=(const Response& response) {
	this->type_ = response.type_;
	this->status_code_ = response.status_code_;
	this->http_version_ = response.http_version_;
	this->allow_ = response.allow_;
	this->connection_ = response.connection_;
	this->location_ = response.location_;
	this->content_type_ = response.content_type_;
	return *this;
}

std::string Response::GetStatusMessage(int code) {
	switch (code) {
		case OK:
			return "OK";
		case CREATED:
			return "Created";
		case MOVED_PERMANENTLY:
			return "Moved Permanently";
		case BAD_REQUEST:
			return "Bad Request";
		case NOT_FOUND:
			return "Not Found";
		case METHOD_NOT_ALLOWED:
			return "Method Not Allowed";
		case LENGTH_REQUIRED:
			return "Length Required";
		case PAYLOAD_TOO_LARGE:
			return "Payload Too Large";
		case URI_TOO_LONG:
			return "URI Too Long";
		case UNSUPPORTED_MEDIA_TYPE:
			return "Unsupported Media Type";
		case INTERNAL_SERVER_ERROR:
			return "Internal Server Error";
		case NOT_IMPLEMENTED:
			return "Not Implemented";
		case HTTP_VERSION_NOT_SUPPORTED:
			return "Http Version Not Supported";
		default:
			return "Unknown Status Message";
	}
}

void Response::ReadFileToBody(const std::string &path) {
	this->body_.clear();
	if (access(path.c_str(), F_OK) != 0)
		return MakeErrorResponse(NOT_FOUND);
	std::ifstream fin;
	fin.open(path.c_str());
	if (fin.fail())
		return MakeErrorResponse(INTERNAL_SERVER_ERROR);
	std::string line;
	while (getline(fin, line)) {
		line += "\r\n";
		for (int i = 0; i < line.length(); i++)
			this->body_.push_back(line[i]);
	}
	fin.close();
}

void Response::GenerateBodyAutoIndexing(const Request &request) {
	this->ReadFileToBody(AUTO_INDEX_HTML_PATH); // 템플릿 전부 읽기

	std::vector<char> v = this->body_;
	std::string string_body(v.begin(), v.end());
	size_t toInsert;

	//title 지정
	toInsert = string_body.find("</title>");
	string_body.insert(toInsert, "Index of " + request.GetPath());

	//head 지정
	toInsert = string_body.find("</h1>");
	string_body.insert(toInsert, "Index of " + request.GetPath());

	// files 이름 지정
	std::string requestPath = request.GetPath();
	if (requestPath.back() != '/') // request path가 '/'로 끝나지 않는 directory일 때 버그 방지
		requestPath.push_back('/');
	std::vector<std::string> fileNames = GetFilesInDirectory(request.GetFullPath());
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		toInsert = string_body.rfind("<hr>");
		string_body.insert(toInsert,std::string() +
		                            "\t<pre>" + "<a href=\"" + requestPath
		                            + fileNames[i] + "\">" + fileNames[i] + "</a></pre>\r\n");
	}
	std::vector<char> v1(string_body.begin(), string_body.end());
	this->body_ = v1;
}

std::vector<std::string> Response::GetFilesInDirectory(const std::string &dirPath) {
	DIR *dir_info;
	struct dirent *dir_entry;
	std::vector<std::string> ret;

	if ((dir_info = opendir(dirPath.c_str())) == NULL)
		MakeErrorResponse(INTERNAL_SERVER_ERROR);
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

void Response::HandleGet(const Request &request, const std::string index_path, const bool autoindex) {
	std::string path = request.GetFullPath();

	if (request.GetPathInfo() == NOT_EXIST)
		return MakeIndexResponse(path, index_path);
	else if (request.GetPathInfo() == IS_DIRECTORY) {
		if (path.back() != '/')
			return MakeIndexResponse(path, index_path);
		else {
			if (autoindex)
				return GenerateBodyAutoIndexing(request);
			else
				return MakeIndexResponse(path, index_path);
		}
	}
	else if (request.GetPathInfo() == IS_FILE)
		return ReadFileToBody(path);
}

void Response::HandlePost(const Request &request) {
	this->body_ = request.GetBody();
	this->content_type_ = request.GetContentType();
	this->status_code_ = CREATED;
}

void Response::HandleDelete(const Request &request) {
	std::string path = request.GetFullPath();
	if (access(path.c_str(), F_OK) == 0)
	{
		if (access(path.c_str(), W_OK) == 0)
		{
			if (unlink(path.c_str()) == 0)
				return;
			return MakeErrorResponse(INTERNAL_SERVER_ERROR);
		}
		return MakeErrorResponse(INTERNAL_SERVER_ERROR);
	}
	else
		return MakeErrorResponse(NOT_FOUND);
}

void Response::SetErrorPages(std::map<int, std::string> error_pages) {
	this->error_pages_ = error_pages;
}

void Response::SetAllow(std::string allow) {
	this->allow_ = allow;
}

HttpStatusCode Response::GetStatusCode() const {
	return this->status_code_;
}

void Response::SetStatusCode(HttpStatusCode status) {
	this->status_code_ = status;
}

void    Response::SendResponse(int fd) {
	std::string toSend;

	toSend += this->http_version_;
	toSend += " " + std::to_string(this->status_code_);
	toSend += " " + this->GetStatusMessage(this->status_code_);
	toSend += "\r\n";

	if (this->status_code_ == METHOD_NOT_ALLOWED)
		toSend += "Allow: " + this->allow_ + "\r\n";
	if (this->status_code_ == MOVED_PERMANENTLY)
		toSend += "Location: " + this->location_ + "\r\n";
	if (!this->content_type_.empty())
		toSend += "Content-Type: " + this->content_type_ + "\r\n";
	if (!this->body_.empty())
		toSend += "Content-Length: " + std::to_string(this->body_.size()) + "\r\n";
	if (!this->connection_.empty())
		toSend += "Connection: " + this->connection_ + "\r\n";
	toSend += "\r\n";

	std::string tmp(this->body_.begin(), this->body_.end());

	toSend += tmp;
	if (send(fd, toSend.c_str(), toSend.size(), 0) == -1)
		std::cerr << "write error" << std::endl;
}

void    Response::SetHttpVersion(std::string version) {
	this->http_version_ = version;
}

void    Response::PushBackBody(char c) {
	this->body_.push_back(c);
}

void Response::MakeIndexResponse(std::string full_path, std::string index_path) {
	int last_slash = full_path.find_last_of("/");
	std::string last_dir = full_path.substr(0, last_slash + 1);
	this->ReadFileToBody(last_dir + index_path);
}

ResponseType Response::GetResponseType() const {
	return (this->type_);
}

void    Response::SetResponseType(ResponseType type) {
	this->type_ = type;
}

void    Response::MakeErrorResponse(int status) {
    ReadFileToBody(error_pages_[status]);
}

void    Response::MakeRedirectionResponse(std::string redir_path) {
	this->location_ = redir_path;
	ReadFileToBody(REDIRECTION_HTML_PATH);
}

int     Response::FindStringInBody(std::string str) {
	std::string s(body_.begin(), body_.end());
	if (s.find(str) != std::string::npos)
		return 1;
	else
		return 0;
}