#include "../../inc/Worker.hpp"

Worker::Worker() : server_socket_(0), port_(80), root_("default"), index_("index.html"), server_names_(0), client_max_body_size_worker_(0) {
	server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	const int value = 1;
	setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	this->error_pages_[404] = "404.html";
}

Worker::~Worker() {}

void Worker::SetServerSocket(int server_socket_) {
    this->server_socket_ = server_socket_;
}

int Worker::GetServerSocket() {
    return this->server_socket_;
}

void Worker::SetPort(int port) {
    this->port_ = port;
}

int Worker::GetPort() {
    return this->port_;
}

void	Worker::SetRoot(std::string& root) {
	this->root_ = root;
}

const	std::string& Worker::GetRoot() const {
	return this->root_;
}

void	Worker::SetIndex(std::string& index) {
	this->index_ = index;
}

const	std::string& Worker::GetIndex() const {
	return this->index_;
}


void Worker::AddServerName(std::string& server_name) {
    this->server_names_.push_back(server_name);
}

const std::vector<std::string>& Worker::GetServerNames() const {
    return this->server_names_;
}

void Worker::SetClientMaxBodySize(size_t size) {
    this->client_max_body_size_worker_ = size;
}

size_t Worker::GetClientMaxBodySize() const {
    return this->client_max_body_size_worker_;
}

void Worker::AddLocations(const Location& location) {
    this->locations_.push_back(location);
}

const std::vector<Location>& Worker::GetLocations() const {
    return this->locations_;
}

void	Worker::AddErrorPage(int err_no, std::string& error_page) {
	this->error_pages_[err_no] =  error_page;
}

const	std::map<int, std::string>& Worker::GetErrorPage() const {
	return this->error_pages_;
}

std::vector<std::string> Worker::SplitArgs(std::string line, std::string sep) {
	std::vector<std::string> str;
	size_t	start = 0;
	size_t	end = 0;

	while (1)
	{
		end = line.find_first_of(sep, start);
		if (end == std::string::npos)
			break ;
		std::string parsed = line.substr(start, end - start);
		str.push_back(parsed);
		start = line.find_first_not_of(sep, end);
		if (start == std::string::npos)
			break ;
	}
	return (str);
}

size_t Worker::MyStoi(std::string str) {
	int len = str.size();
	int sum = 0;
	for (int i = len - 1, p = 1; i >= 0; i--, p *= 10)
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		str[i] -= 48;
		sum += str[i] * p;
	}
	return  sum;
}

size_t	Worker::CheckContentLength(std::string headers) {
	size_t	len = 0;
	std::string length = "";
	std::vector <std::string> tmp = this->SplitArgs(headers, "\r\n");
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].find("Content-Length: ") != std::string::npos)
		{
			length = tmp[i].substr(tmp[i].find(':') + 2);
		}
	}
	if (length != "")
		len = this->MyStoi(length);
	return (len);
}

std::vector <std::string> Worker::Split(std::string input, char dlim, int &result_cnt) {
	std::vector<std::string> result;

	std::stringstream ss;
	std::string stringBuffer;
	ss.str(input);

	while (getline(ss, stringBuffer, dlim))
	{
		result.push_back(stringBuffer);
		result_cnt++;
	}
	return result;
}

void	Worker::ReqFirstLineParse(Request &req, std::string first_line) {
	int	tmp = 0;
	std::vector <std::string> fir_line_parse;
	fir_line_parse = this->Split(first_line, ' ', tmp);
	req.setMethod(fir_line_parse[0]);
	// for (int i = 0; i < this->GetLocations().size(); i++)
	// {
	// 	if (req.getPath() == GetLocations()[i].GetUri())
	// 		break ;
	// 	else
	// }
	req.setPath(fir_line_parse[1]);
    req.setFullPath(this->root_ + req.getPath());
	req.setScheme(fir_line_parse[2]);
}

void	Worker::ParseHost(Request &req, std::vector<std::string> colon_parse) {
	int	i = 1;
	std::string	tmp;
	while (colon_parse[1][i])
	{
		if (colon_parse[1][i] == ' ')
			break ;
		tmp += colon_parse[1][i];
		i++;
	}
	req.pushBackHost(tmp);
	req.pushBackHost(colon_parse[2]);
}

void	Worker::ParseConnection(Request &req, std::vector<std::string> colon_parse) {
	int	i = 1;
	std::string	tmp;
	while (colon_parse[1][i])
	{
		if (colon_parse[1][i] == ' ')
			break ;
		tmp += colon_parse[1][i];
		i++;
	}
	req.setConnection(tmp);
}

void	Worker::ParseContentLength(Request &req, std::vector<std::string> colon_parse) {
	int	i = 1;
	std::string tmp;
	while (colon_parse[1][i])
	{
		if (colon_parse[1][i] == ' ')
			break ;
		tmp += colon_parse[1][i];
		i++;
	}
	req.setContentLength(tmp);
}

void	Worker::ParseOther(Request &req, std::vector<std::string> line_parse, int line_cnt) {
	int tmp;
	std::vector <std::string> colon_parse;
	for (int i = 1; i < line_cnt; i++)
	{
		tmp = 0;
		colon_parse = this->Split(line_parse[i], ':', tmp);
		if (colon_parse.size() == 0)
			continue ;
		if (colon_parse[0] == "Host")
			this->ParseHost(req, colon_parse);
		else if (colon_parse[0] == "Connection")
			this->ParseConnection(req, colon_parse);
		else if (colon_parse[0] == "Content-Length")
			this->ParseContentLength(req, colon_parse);
		else if (colon_parse[0] == "Content-Type")
			req.setContentType(colon_parse[1]);
	}
}

void	Worker::RequestHeaderParse(Request &req) {
	int	line_cnt = 0;
	std::vector <std::string> line_parse;
	std::string header = req.getHeaders();

	line_parse = this->SplitArgs(header, "\r\n");
	this->ReqFirstLineParse(req, line_parse[0]);
	line_cnt = line_parse.size();
	this->ParseOther(req, line_parse, line_cnt);
	//std::cout << "head = " << req.getHeaders() << std::endl;
	// std::cout << "method : " << req.getMethod() << std::endl;
	// std::cout << "path : " << req.getPath() << std::endl;
	// std::cout << "scheme : " << req.getScheme() << std::endl;
	// std::cout << "host[0] : " << req.getHost()[0] << std::endl;
	// std::cout << "host[1] : " << req.getHost()[1] << std::endl;
	// std::cout << "connection : " << req.getConnection() << std::endl;
	// std::cout << "content-length : " << req.getContentLength() << std::endl;
	// std::cout << "body : ";
	// for(int i = 0; i < req.getBody().size(); i++)
	// 	std::cout << req.getBody()[i];
	// std::cout << std::endl;
	//여기서 바디랑 길이 맞는지 확인하고 아니면 에러
}

// void	Worker::CheckPossibleMethod(Request &req)
// {
// 	int	method;

// 	for(int i = 0; i < this->GetLocations().size(); i++)
// 	{
// 		if (this->GetLocations()[i].GetRoot() == req.getPath())
// 		break ;
// 	}
// 	if (req.getMethod() == "GET")
// 		method = 0;
// 	else if (req.getMethod() == "POST")
// 		method = 1;
// 	else if (req.getMethod() == )
// }

void	Worker::ChunkBodyParse(Request &req, Response &res) {
	size_t	byte;
	std::vector <std::string> line_parse;
	std::string tmp_body = req.getBodyStr();
	// std::vector <char> body = req.getBody();
	// std::string tmp_body(body.begin(), body.end());

	line_parse = this->SplitArgs(tmp_body, "\r\n");
	req.setBodyClear();
	for (int i = 0; i < line_parse.size(); i++)
	{
		if (i % 2 == 0)
		{
			byte = this->MyStoi(line_parse[i]);
			if (byte == -1)
			{
				res.setStatusCode(400);
				break ;
			}
			if (byte == 0)
				break ;
		}
		else if (i % 2 == 1)
		{
			size_t	body_size = line_parse[i].size();
			if (byte != body_size)
				res.setStatusCode(400);
			for (int j = 0; j < line_parse[i].size(); j++)
				req.pushPostBody(line_parse[i][j]);
			// req.pushPostBody('\r');
			// req.pushPostBody('\n');
		}
	}
}
// std::string Worker::checkReturnVal()
// {
// 	std::string result = "";
// 	size_t i;
// 	std::vector<Location> locations = this->GetLocations();

// 	for (i = 0; i < locations.size(); i++)
// 	{
// 		if (locations[i].GetUri() == this->getRequest().getPath())
// 			Location	target = locations[i];
// 			if (target.getRe)
// 	}
// }

// void	Worker::urlSearch(int event_fd)
// {
// 	std::string str = "";
// 	std::string file = "";
// 	size_t	slen = 0;
// 	size_t	i;
// 	size_t	pos;

// 	for (i = 0; i < this->GetLocations().size(); i++)
// 	{
// 		pos = this->getRequest()[event_fd].getPath().find(this->GetLocations()[i].GetUri());
// 		if (pos != std::string::npos && this->GetLocations()[i].GetUri().size() > slen)
// 		{
// 			str = this->GetLocations()[i].GetUri();
// 			slen = this->GetLocations()[i].GetUri().size();
// 			file = this->getRequest()[event_fd].getPath().substr(pos + this->GetLocations()[i].GetUri().size());
// 		}
// 	}
// 	std::cout << str << std::endl;
// 	std::cout << file << std::endl;

// 	this->getRequest()[event_fd].setPath(str);
// 	this->getRequest()[event_fd].setBody(file);
// }