#include "../../inc/Response.hpp"


Response::Response() {
	this->type_ = GENERAL;
	this->status_code_ = OK;
	this->connection_ = "keep-alive";
	this->contentType_ = "text/html";
	this->httpversion_ = "HTTP/1.1";
	this->location_ = "";
}

Response::~Response() {

}

Response& Response::operator=(const Response& response) {
	this->status_code_ = response.status_code_;
	this->connection_ = response.connection_;
	this->contentType_ = response.contentType_;
	this->httpversion_ = response.httpversion_;
	this->location_ = response.location_;
	return *this;
}

std::string Response::GetStatusMessage(int code) {
	switch (code)
	{
		case OK:
			return "OK";
		case CREATED:
			return "Created";
		case NO_CONTENT:
			return "No Content";
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
		case URL_TOO_LONG:
			return "URL Too Long";
		case UNSUPPORTED_MEDIA_TYPE:
			return "Unsupported Media Type";
		case NOT_IMPLEMENTED:
			return "Not Implemented";
		case HTTP_VERSION_NOT_SUPPORTED:
			return "Http Version Not Supported";
		default:
			return "Unknown";
	}
}

void Response::ReadFileToBody(const std::string &path) {
	std::ifstream fin;
	fin.open(path.c_str());
	if (fin.fail())
		std::cerr << "file open error" << std::endl;
	std::string line;
	while (getline(fin, line))
	{
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

int Response::CheckPath(const std::string path) {
	struct stat buf;

	if (stat(path.c_str(), &buf) == -1) // 해당 경로에 파일이 존재 안하면 404Page
		return 0;
	else if (S_ISDIR(buf.st_mode)) // 경로일 때
	{
		if (path.back() == '/')
			return 1;
		else
			return 2;
	}
	return 3;
}

std::vector<std::string> Response::GetFilesInDirectory(const std::string &dirPath) {
	DIR *dir_info;
	struct dirent *dir_entry;
	std::vector<std::string> ret;

	if ((dir_info = opendir(dirPath.c_str())) == NULL)
		std::cerr << "opendir error" << std::endl;
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

// void Response::handleBodySizeLimit()
// {
// 	this->status_code_ = CONTENT_TOO_LARGE;
// 	this->connection = "close";
// 	this->ReadFileToBody(ERROR_PAGE_413_PATH);
// 	this->contentLength_ = this->body_.size();
// 	this->contentType_ = "text/html";
// }

// void Response::handleBadRequest()
// {
// 	this->httpversion_ = "HTTP/1.1";
// 	this->status_code_ = NOT_FOUND;
// 	this->connection = "close";
// 	this->ReadFileToBody(ERROR_PAGE_404_PATH);
// 	this->contentLength_ = this->body_.size();
// 	this->contentType_ = "text/html";
// }

void Response::HandleGet(const Request &request, const std::string index) {
	std::string final_path = request.GetFullPath();
	int check_res = this->CheckPath(final_path);
	if (check_res == 1) // autoindex 해야하는 상황
	{
		this->GenerateBodyAutoIndexing(request);
		return;
	}
	else if (check_res == 2) // 파일이 없거나 디렉토리인데 구조 이상한 경우
	{
		final_path += "/";
		int last_slash = final_path.find_last_of("/");
		std::string last_dir = final_path.substr(0, last_slash + 1);
		final_path = last_dir + index;
		int second_check = this->CheckPath(final_path);
		if (second_check == 0)
		{
			/* 바로 404 응답 보내는 함수 필요 */
			this->status_code_ = NOT_FOUND;
			final_path = ERROR_PAGE_404_PATH;
		}
	}
	else if (check_res == 0) // youpi.bad_extension 파일조차 없거나 원래부터 유효하지 않은 파일인 경우
	{
		/* 바로 404 응답 보내는 함수 필요 */
		this->status_code_ = NOT_FOUND;
		final_path = ERROR_PAGE_404_PATH;
	}
	this->ReadFileToBody(final_path);
}

void Response::HandlePost(const Request &request) {
	DIR *dir_info;

	/* 405 응답 보내는 함수 필요 */
	if ((dir_info = opendir(request.GetPath().c_str())) != NULL) {
		this->Sethttpversion("HTTP/1.1");
		this->SetStatusCode(405);
		this->contentType_ = request.GetContentType();
		this->connection_ = "Close";
		closedir(dir_info);
		return ;
	}
}

void Response::HandlePut(const Request &request) {}

void Response::HandleDelete(const Request &request) {
	std::string path = request.GetFullPath();
//	try
//	{
		std::string body_ = DeleteCheck(path);
		std::vector<char> v(body_.begin(), body_.end());
		this->body_ = v;
//	}
//	catch (std::runtime_error &e)
//	{
//		std::cout << e.what() << std::endl;
//		this->status_code_ = NOT_FOUND;
//		std::string failed = "delete failed\n";
//		std::vector<char> v(failed.begin(), failed.end());
//		this->body_ = v;
//		return ;
//	}
}

void Response::SetStatusCode(int data) {
	this->status_code_ = data;
}

void    Response::SendResponse(int fd) {
	std::string toSend;

	// 임시 하드코딩
	toSend += this->httpversion_;
	toSend += " " + std::to_string(this->status_code_);
	toSend += " " + this->GetStatusMessage(this->status_code_);
	toSend += "\r\n";

	if (!this->contentType_.empty())
		toSend += "Content-Type: " + this->contentType_ + "\r\n";
	if (!this->body_.empty())
		toSend += "Content-Length: " + std::to_string(this->body_.size()) + "\r\n";
	if (!this->connection_.empty())
		toSend += "Connection: " + this->connection_ + "\r\n";
	toSend += "\r\n";

	std::string tmp(this->body_.begin(), this->body_.end());

	toSend += tmp;
	// write error 처리 필요
	if (send(fd, toSend.c_str(), toSend.size(), 0) == -1)
		std::cerr << "write error" << std::endl;
}

std::string Response::DeleteCheck(std::string path) const {
	if (access(path.c_str(), F_OK) == 0)
	{
		if (access(path.c_str(), W_OK) == 0)
		{
			if (unlink(path.c_str()) == 0)
				return path + " deleted\n";
			return "unlink error";
		}
		return "permission error";
	}
	else
		return "404 not found";
}

void    Response::Sethttpversion(std::string version) {
	this->httpversion_ = version;
}

void    Response::PushBackBody(char c) {
	this->body_.push_back(c);
}

void    Response::PrintBody() const {
	std::cerr << "-- print body_ --" << std::endl;
	for(int i=0; i<this->body_.size(); i++)
		std::cerr << this->body_[i];
	std::cerr << "-- finish --" << std::endl;
}

ResponseType Response::GetResponseType() const {
	return (this->type_);
}

void    Response::SetResponseType(ResponseType type) {
	this->type_ = type;
}