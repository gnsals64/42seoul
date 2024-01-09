#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <algorithm>

class Span {
private:
	unsigned int _max_store;
	std::vector<int> _vec;
public:
	Span(unsigned int N);
	~Span();
	Span(const Span &cpy);
	Span &operator=(const Span &cpy);
	void addNumber(int num);
	unsigned int shortestSpan();
	unsigned int longestSpan();

	template<typename iter>
	void addNumrange(iter begin, iter end) {
		while (*begin != *end) {
			this->addNumber(*begin);
			begin++;
		}
	}

	
	class dup_num : public std::exception {
		public:
			const char *what() const throw();
	};
	class sizeover : public std::exception {
		public:
			const char *what() const throw();
	};
	class membererr : public std::exception {
		public:
			const char *what() const throw();
	};
};

#endif