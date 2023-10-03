#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
// #include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

class Transaction {
protected:
    std::string httpversion;
    std::string connection;
    std::string location; // 300번대 응답에서 redirect 시 사용.
    std::string contentType;
	std::vector <char> body;

public:
};


#endif