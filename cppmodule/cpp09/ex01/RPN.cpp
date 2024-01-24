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

void RPN::start() {
	std::stack<int> tmp;

	while (true) {
		if (isnumber(_db.front())) {
			tmp.push(_db.front() - 48);
			_db.pop();
		}
		else if (tmp.size() >= 2 && isopration(_db.front())) {
				int num1 = tmp.top();
				tmp.pop();
				int num2 = tmp.top();
				tmp.pop();
				int num3;

				if (_db.front() == '+')
					num3 = this->sum(num2, num1);
				else if (_db.front() == '-')
					num3 = this->sub(num2, num1);
				else if (_db.front() == '*')
					num3 = this->mul(num2, num1);
				else if (_db.front() == '/')
					num3 = this->div(num2, num1);
				tmp.push(num3);
				_db.pop();
		}
		else
			throw std::runtime_error("Error");
		if (tmp.size() == 1 && _db.empty() == true) {
			std::cout << tmp.top() << std::endl;
			break ;
		}

	}
}

bool	RPN::isopration(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int		RPN::sum(int a, int b) {
	return a + b;
}

int		RPN::sub(int a, int b) {
	return a - b;
}

int		RPN::mul(int a, int b) {
	return a * b;
}

int		RPN::div(int a, int b) {
	if (b == 0)
		throw std::runtime_error("cannot be divided by 0");
	return a / b;
}