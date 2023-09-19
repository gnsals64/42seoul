#include "../../inc/Webserv.hpp"

void	Webserv::ChangeEvent(std::vector<struct kevent>& change_list, uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

ssize_t	Webserv::readData(int fd, char *buffer, size_t buffer_size) {
    ssize_t len = recv(fd, buffer, buffer_size, 0);
    if (len == 0) {
        return (0);
    } else if (len > 0) {
        return len;
    }
    return -1;
}

void	Webserv::send_response(int client_socket, int status_code, const std::string &content) {
	std::stringstream response;
	response << "HTTP/1.1 " << status_code << " " << status_messages[status_code] << CRLF;
	response << "Content-Type: text/html" << CRLF;
	response << "Content-Length: " << content.size() << CRLF;
	response << CRLF;
	response << content;
	// std::cout << (char *)response.str().c_str() << std::endl;

	send(client_socket, response.str().c_str(), response.str().size(), 0);
	// close (client_socket);
}

void	Webserv::handle_request(int client_socket) {
    const std::string response_content = "<html><body><h1>Hello, HTTP 1.1 Server!</h1></body></html>";
    send_response(client_socket, 200, response_content);
}