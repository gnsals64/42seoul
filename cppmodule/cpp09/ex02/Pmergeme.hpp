#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <ctime>
# include <sys/time.h>

class PmergemeV {
private:
	std::vector<std::pair<int, int> > _v1;
	std::vector<std::pair<int, int> > _v2;

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
	void	fillVector(int ac, char **av);
	void	swapPair();
	void	mergesortPair();
	void	partition(int left, int right);
	void	merge(int left, int right);
};

class PmergemeDe {
private:
	std::deque<std::pair<int, int> >	 _de1;
	std::deque<std::pair<int, int> >	 _de2;
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
	void	fillDeque(int ac, char **av);
	void	swapPair();
	void	mergesortPair();
	void	partition(int left, int right);
	void	merge(int left, int right);
};

void	swap(int &a, int &b);

#endif