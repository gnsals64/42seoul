#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN {
private:
	std::stack<char> _db;

public:
	RPN();
	~RPN();
	RPN(const RPN &cpy);
	RPN& operator=(const RPN &cpy);

	void	init(std::string input);

};

#endif