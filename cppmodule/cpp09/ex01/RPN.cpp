#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &cpy) {
	this->_db = cpy._db;
}

RPN& RPN::operator=(const RPN &cpy) {
	if (this == &cpy)
		return *this;
	this->_db = cpy._db;
	return *this;
}

void RPN::init(std::string input) {
	if (input == "")
		throw std::runtime_error("input is empty");
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == ' ')
			continue ;
		if (isnumber(input[i]) == false && input[i] != '+' &&
			input[i] != '-' && input[i] != '/' && input[i] != '*')
			throw std::runtime_error("invalid arguments");
		_db.push(input[i]);
	}
}