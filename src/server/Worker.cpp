#include "../../inc/Worker.hpp"

Worker::Worker() : server_socket(0), port(80), root("default"), index("index.html"), server_names(0), client_max_body_size(0)
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	const int value = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	this->error_pages[404] = "404.html";
}

Worker::~Worker() {}

void Worker::set_server_socket(int server_socket) {
    this->server_socket = server_socket;
}

int Worker::get_server_socket() {
    return this->server_socket;
}

void Worker::set_port(int port) {
    this->port = port;
}

int Worker::get_port() {
    return this->port;
}

void	Worker::set_root(std::string& root)
{
	this->root = root;
}

const	std::string& Worker::get_root() const
{
	return this->root;
}

void	Worker::set_index(std::string& index)
{
	this->index = index;
}

const	std::string& Worker::get_index() const
{
	return this->index;
}


void Worker::add_server_name(std::string& server_name) {
    this->server_names.push_back(server_name);
}

const std::vector<std::string>& Worker::get_server_names() const {
    return this->server_names;
}

void Worker::set_client_max_body_size(size_t size) {
    this->client_max_body_size = size;
}

size_t Worker::get_client_max_body_size() const {
    return this->client_max_body_size;
}

void Worker::add_locations(const Location& location) {
    this->locations.push_back(location);
}

const std::vector<Location>& Worker::get_locations() const {
    return this->locations;
}

void	Worker::add_error_page(int err_no, std::string& error_page)
{
	this->error_pages[err_no] =  error_page;
}

const	std::map<int, std::string>& Worker::get_error_page() const
{
	return this->error_pages;
}

std::vector<std::string> Worker::splitArgs(std::string line, std::string sep)
{
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

size_t Worker::myStoi(std::string str)
{
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

size_t	Worker::checkContentLength(std::string headers)
{
	size_t	len = 0;
	std::string length = "";
	std::vector <std::string> tmp = this->splitArgs(headers, "\r\n");
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].find("Content-Length: ") != std::string::npos)
		{
			length = tmp[i].substr(tmp[i].find(':') + 2);
		}
	}
	if (length != "")
		len = this->myStoi(length);
	return (len);
}

std::vector <std::string> Worker::split(std::string input, char dlim, int &result_cnt)
{
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

void	Worker::reqFirstLineParse(Request &req, std::string first_line)
{
	int	tmp = 0;
	std::vector <std::string> fir_line_parse;
	fir_line_parse = this->split(first_line, ' ', tmp);
	req.setMethod(fir_line_parse[0]);
	// for (int i = 0; i < this->get_locations().size(); i++)
	// {
	// 	if (req.getPath() == get_locations()[i].get_uri())
	// 		break ;
	// 	else
	// }
	req.setPath(fir_line_parse[1]);
    req.setFullPath(this->root + req.getPath());
	req.setScheme(fir_line_parse[2]);
}

void	Worker::parseHost(Request &req, std::vector<std::string> colon_parse)
{
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

void	Worker::parseConnection(Request &req, std::vector<std::string> colon_parse)
{
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

void	Worker::parseContentLength(Request &req, std::vector<std::string> colon_parse)
{
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

void	Worker::parseOther(Request &req, std::vector<std::string> line_parse, int line_cnt)
{
	int tmp;
	std::vector <std::string> colon_parse;
	for (int i = 1; i < line_cnt; i++)
	{
		tmp = 0;
		colon_parse = this->split(line_parse[i], ':', tmp);
		if (colon_parse.size() == 0)
			continue ;
		if (colon_parse[0] == "Host")
			this->parseHost(req, colon_parse);
		else if (colon_parse[0] == "Connection")
			this->parseConnection(req, colon_parse);
		else if (colon_parse[0] == "Content-Length")
			this->parseContentLength(req, colon_parse);
		else if (colon_parse[0] == "Content-Type")
			req.setContentType(colon_parse[1]);
	}
}

void	Worker::requestHeaderParse(Request &req)
{
	int	line_cnt = 0;
	std::vector <std::string> line_parse;
	std::string header = req.getHeaders();

	line_parse = this->splitArgs(header, "\r\n");
	this->reqFirstLineParse(req, line_parse[0]);
	line_cnt = line_parse.size();
	this->parseOther(req, line_parse, line_cnt);
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

// 	for(int i = 0; i < this->get_locations().size(); i++)
// 	{
// 		if (this->get_locations()[i].get_root() == req.getPath())
// 		break ;
// 	}
// 	if (req.getMethod() == "GET")
// 		method = 0;
// 	else if (req.getMethod() == "POST")
// 		method = 1;
// 	else if (req.getMethod() == )
// }

void	Worker::chunkBodyParse(Request &req, Response &res)
{
	size_t	byte;
	std::vector <std::string> line_parse;
	std::vector <char> body = req.getBody();
	std::string tmp_body(body.begin(), body.end());

	line_parse = this->splitArgs(tmp_body, "\r\n");
	req.setBodyClear();
	for (int i = 0; i < line_parse.size(); i++)
	{
		if (i % 2 == 0)
		{
			byte = this->myStoi(line_parse[i]);
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
// 	std::vector<Location> locations = this->get_locations();

// 	for (i = 0; i < locations.size(); i++)
// 	{
// 		if (locations[i].get_uri() == this->getRequest().getPath())
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

// 	for (i = 0; i < this->get_locations().size(); i++)
// 	{
// 		pos = this->getRequest()[event_fd].getPath().find(this->get_locations()[i].get_uri());
// 		if (pos != std::string::npos && this->get_locations()[i].get_uri().size() > slen)
// 		{
// 			str = this->get_locations()[i].get_uri();
// 			slen = this->get_locations()[i].get_uri().size();
// 			file = this->getRequest()[event_fd].getPath().substr(pos + this->get_locations()[i].get_uri().size());
// 		}
// 	}
// 	std::cout << str << std::endl;
// 	std::cout << file << std::endl;

// 	this->getRequest()[event_fd].setPath(str);
// 	this->getRequest()[event_fd].setBody(file);
// }