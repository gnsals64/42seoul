#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Transaction.hpp"

class Request : public Transaction{
private:
    std::string httpMethod;
    std::string host;
    std::string path;

public:
    Request();
    ~Request();

    std::string getPath() const;
    //void parsingFromData(std::string);
};

#endif