#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

class Transaction {
protected:
    std::string httpVersion;
    int contentLength;
    std::string connection;
    std::string location; // 300번대 응답에서 redirect 시 사용.
    std::string contentType;
    std::string body;

public:

};


#endif