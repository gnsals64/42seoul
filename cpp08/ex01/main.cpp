#include "Span.hpp"

int main()
{
	try {
	std::cout << "standard span" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
	try {
	std::cout << "range span" << std::endl;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(10);
	v.push_back(100);
	v.push_back(19);
	v.push_back(55);
	v.push_back(79);

	Span sp2 = Span(9);
	sp2.addNumrange(v.begin(), v.end());
	std::cout << sp2.shortestSpan() << std::endl;
	std::cout << sp2.longestSpan() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}