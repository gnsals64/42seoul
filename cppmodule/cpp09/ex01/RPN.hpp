#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <queue>
# include <stack>

class RPN {
private:
	std::queue<char> _db;

public:
	RPN();
	~RPN();
	RPN(const RPN &cpy);
	RPN& operator=(const RPN &cpy);

	void	init(std::string input);
	void	start();
	bool	isopration(char c);
	int		sum(int a, int b);
	int		sub(int a, int b);
	int		mul(int a, int b);
	int		div(int a, int b);
};


#endif