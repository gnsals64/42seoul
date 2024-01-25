#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>

class Pmergeme {
private:
	std::vector<std::pair<int, int> >	_v;
	std::list<std::pair<int, int> >		_li;
	bool	_odd;
	int		_lastnum;

public:
	Pmergeme();
	~Pmergeme();
	Pmergeme(const Pmergeme &cpy);
	Pmergeme& operator=(const Pmergeme &cpy);
	void	init_v(int ac, char **av);
	void	init_li(int ac, char **av);
	void	oddCheck(int *ac, char **av);
	void	fillVector(int ac, char **av);
	void	fillList(int ac, char **av);
	void	swapPairV();
	void	swapPairLi();
	void	sortPairV();
	void	sortPairLi();
};

void	swap(int &a, int &b);

#endif