#ifndef REQUEST_HPP
#define REQUEST_HPP

# define HEADER_READ 0
# define BODY_READ 1
# define READ_FINISH 2
#include "Worker.hpp"
#include <sys/time.h>

class Request {
	private:
		std::string headers_;
		std::string http_method_;
        std::string path_;
        std::string full_path_;
        std::string	scheme_;
        std::vector <std::string> host_;
        std::string	connection_;
        int	        content_length_;
		std::string	body_str_;
		int			state_;
		std::string http_version_;
   		std::string location_; 
   		std::string content_type_;
		std::vector <char> body_;

	public:
		Request();
		~Request();
		Request& operator=(const Request& request);

		void	SetMethod(std::string method);
		void	SetPath(std::string path);
        void    SetFullPath(std::string full_path);
		void	SetScheme(std::string scheme);
		void	PushBackHost(std::string host);
		void	SetConnection(std::string connection);
		void	SetContentLength(int length);
		void	SetState(int SetState);
		void	SetHeaders(std::string data);
		void	SetBodyClear();
		void	SetContentType(std::string type);
		std::string	GetMethod() const;
		std::string	GetPath() const;
        std::string GetFullPath() const;
		std::string	GetScheme() const;
		std::vector<std::string>	GetHost() const;
		std::string	GetConnection() const;
		int GetContentLength() const;
		std::string GetHeaders() const;
		int	GetState() const;
		std::vector<char> GetBody() const;
        std::string GetContentType() const;
		std::string GetBodyStr() const;
		std::string GetBodyCharToStr() const;

		void	AppendHeader(std::string data);
		void	AppendBodyStr(std::string data);
		void	PushPostBody(char data);
		void	BodyAppendVec(std::vector<char> data);
		void	RemoveCRLF();

		int		Findrn0rn(std::string temp);
		void	AddRNRNOneTime();
		void	RemoveRNRNOneTime();
};

#endif