#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <ctime>
# include <sys/time.h>
# include <sstream>

class PmergemeV {
private:
	std::vector<std::pair<int, int> > _pair_num1;
	std::vector<std::pair<int, int> > _pair_num2;
	std::vector<int> _before_sort;
	std::vector<int> _after_sort;
	std::vector<int> _jacobsthal;

	bool	_odd;
	int		_lastnum;

public:
	PmergemeV();
	PmergemeV(int ac);
	~PmergemeV();
	PmergemeV(const PmergemeV &cpy);
	PmergemeV& operator=(const PmergemeV &cpy);
	void	init(int ac, char **av);
	void	oddCheck(int *ac, char **av);
	void	numCheck(int ac, char **av);
	void	makeJacobnum();
	void	fillVector(int ac, char **av);
	void	swapPair();
	void	mergesortPair();
	void	partition(int left, int right);
	void	merge(int left, int right);
	int		BinarySearch(int target);
	void	sort();
};

class PmergemeDe {
private:
	std::deque<std::pair<int, int> > _pair_num1;
	std::deque<std::pair<int, int> > _pair_num2;
	std::deque<int> _before_sort;
	std::deque<int> _after_sort;
	std::deque<int> _jacobsthal;
	bool	_odd;
	int		_lastnum;

public:
	PmergemeDe();
	PmergemeDe(int ac);
	~PmergemeDe();
	PmergemeDe(const PmergemeDe &cpy);
	PmergemeDe& operator=(const PmergemeDe &cpy);
	void	init(int ac, char **av);
	void	oddCheck(int *ac, char **av);
	void	numCheck(int ac, char **av);
	void	makeJacobnum();
	void	fillDeque(int ac, char **av);
	void	swapPair();
	void	mergesortPair();
	void	partition(int left, int right);
	void	merge(int left, int right);
	void	sort();
};

void	swap(int &a, int &b);

#endif