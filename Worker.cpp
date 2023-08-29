#include "Worker.hpp"

//port의 default 값 80
//root는 default root 존재함 (우리가 설정)
//index의 default 값 "index.html", "index.htm"
//server_name은 비어있을 경우 default server 찾아감, default server는 첫 번째 server(Worker.at(0))
//client_max_body_size가 0일 경우 제한 X
//location이 0일 경우 기본 경로인 '/' 경로에 대한 모든 요청에 적용

Worker::Worker() : server_socket(0), port(80), root("default"), index("index.html"), server_names(0), client_max_body_size(0)
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	const int value = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	//default error page setting
	// this->error_pages.insert({404, "404.html"});
}

Worker::~Worker() {}

// Worker::Worker(const Worker& worker) {
//     *this = worker;
// }

// Worker& Worker::operator=(const Worker& worker) {
//     if (this != &worker) {
//         this->port = worker.port;
//         std::vector<std::string> new_server_names;
//         for (int i = 0; i < worker.server_names.size(); i++)
//             new_server_names.push_back(worker.server_names.at(i));
//         this->server_names = new_server_names;
//         //error page 복사는 나중에 할랭
//         client_max_body_size = worker.client_max_body_size;
//         std::vector<Location> new_locations;
//         for (int i = 0; i < worker.locations.size(); i++) {
//             Location location(worker.locations.at(i));
//             new_locations.push_back(location);
//         }
//         this->locations = new_locations;
//     }
//     return *this;
// }

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

// void Worker::add_locations(const Location& location) {
//     this->locations.push_back(location);
// }

// const std::vector<Location>& Worker::get_locations() const {
//     return this->locations;
// }

// void	Worker::add_error_page(int errno, std::string& error_page)
// {
// 	this->error_pages.insert({errno, error_page});
// }

const	std::map<int, std::string>& Worker::get_error_page() const
{
	return this->error_pages;
}

Request	Worker::getRequest()
{
	return this->request;
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

void	Worker::reqFirstLineParse(std::string first_line)
{
	int	tmp = 0;
	std::vector <std::string> fir_line_parse;
	fir_line_parse = this->split(first_line, ' ', tmp);
	this->request.setMethod(fir_line_parse[0]);
	this->request.setPath(fir_line_parse[1]);
	this->request.setScheme(fir_line_parse[2]);
}

void	Worker::parseHost(std::vector<std::string> colon_parse)
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
	this->request.pushBackHost(tmp);
	this->request.pushBackHost(colon_parse[2]);
}

void	Worker::parseConnection(std::vector<std::string> colon_parse)
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
	this->request.setConnection(tmp);
}

void	Worker::parseContentLength(std::vector<std::string> colon_parse)
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
	this->request.setContentLength(tmp);
}

void	Worker::parseOther(std::vector<std::string> line_parse, int line_cnt)
{
	int tmp;
	std::vector <std::string> colon_parse;
	for (int i = 1; i < line_cnt; i++)
	{
		tmp = 0;
		colon_parse = this->split(line_parse[i], ':', tmp);
		std::cout << "parse = " << colon_parse[0] << std::endl;
		if (colon_parse[0] == "Host")
			this->parseHost(colon_parse);
		else if (colon_parse[0] == "Connection")
			this->parseConnection(colon_parse);
		else if (colon_parse[0] == "Content-Length")
			this->parseContentLength(colon_parse);
	}
	// this->request.setBody(colon_parse[0]);
}

void	Worker::requestParse(std::string request)
{
	int	line_cnt = 0;
	std::vector <std::string> line_parse;
	line_parse = this->split(request, '\n', line_cnt);
	// for (int i = 0; i < line_cnt; i++)
	// {
	// 	std::cout << "line_parse = " << line_parse[i] << std::endl;
	// }
	this->reqFirstLineParse(line_parse[0]);
	this->parseOther(line_parse, line_cnt);
	std::cout << "headers : " << this->request.getHeaders() << std::endl;
	std::cout << "method : " << this->request.getMethod() << std::endl;
	std::cout << "path : " << this->request.getPath() << std::endl;
	std::cout << "scheme : " << this->request.getScheme() << std::endl;
	std::cout << "host[0] : " << this->request.getHost()[0] << std::endl;
	std::cout << "host[1] : " << this->request.getHost()[1] << std::endl;
	std::cout << "connection : " << this->request.getConnection() << std::endl;
	std::cout << "content-length : " << this->request.getContentLength() << std::endl;
	std::cout << "body : " << this->request.getBody() << std::endl;
}