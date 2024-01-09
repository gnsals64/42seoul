#include "Span.hpp"

Span::Span(unsigned int N) {
	this->_max_store = N;
}

Span::~Span() {}

Span::Span(const Span &cpy) {
	this->_max_store = cpy._max_store;
	this->_vec = cpy._vec;
}

Span& Span::operator=(const Span &cpy) {
	if (this == &cpy)
		return *this;
	this->_max_store = cpy._max_store;
	this->_vec = cpy._vec;
	return *this;
}

void	Span::addNumber(int num) {
	if (this->_max_store == _vec.size())
		throw Span::sizeover();
	if (std::find(_vec.begin(), _vec.end(), num) != _vec.end()) {
		throw Span::dup_num();
	}
	_vec.push_back(num);
}

unsigned int Span::longestSpan() {
	if (_vec.size() == 0 || _vec.size() == 1)
		throw Span::membererr();
	return *std::max_element(_vec.begin(), _vec.end()) - *std::min_element(_vec.begin(), _vec.end());
}

unsigned int Span::shortestSpan() {
	std::vector<int> cpy = _vec;

	std::sort(cpy.begin(), cpy.end());
	int min = cpy[1] - cpy[0];
	for (std::vector<int>::iterator it = cpy.begin(); it != cpy.end() - 1; it++) {
		if (min > *(it + 1) - *it)
			min = *(it + 1) - *it;
	}
	return min;
}

const char *Span::dup_num::what() const throw() {
	return "The same number is already in the span";
}
const char *Span::sizeover::what() const throw() {
	return "sizeover";
}
const char *Span::membererr::what() const throw() {
	return "There must be at least 2 members";
}