#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>

class Span {
private:
	int max_store;
	std::vector<int> v;
public:
	Span(unsigned int N);
	~Span();
	Span(const Span &cpy);
	Span &operator=(const Span &cpy);
	void addNumber(int num);
	unsigned int shortestSpan();
	unsigned int longestSpan();
};

#endif